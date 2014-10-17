#include <assert.h>
#include <msxml2.h>
#include <comdef.h>
#include "../include/StringUtility.h"
#include "../include/EMRException.h"
#include "../include/EMREventLog.h"
#include "../include/XMLSchemaCache.h"
#include "../include/XMLSchemaDebugger.h"
#include "../include/XMLTree.h"
#include "XMLTreeNodePrivate.h"
#include "XMLTreePrivate.h"

#pragma comment(lib, "msxml2.lib")


BEGIN_ZEMR_NAMESPACE

/*!
	\class CXMLTreeNode
	\inmodule ZCore
	\ingroup Utility/XmlDom

	\brief XML DOM简易包装类.

	XML DOM 规定了6种节点, 其基类都称为 Node, 为了方便使用, 该类默认操作为 Element 类型节点.
	注意到, 可以使用 GetNodeType() 来获取其节点的类型, 是一个枚举值.
*/

/*
	\enum CXMLTreeNode::DOMNodeType

	树节点类型.

	\value NODE_INVALID					无效节点
	\value NODE_ELEMENT					元素节点
	\value NODE_ATTRIBUTE				属性节点
	\value NODE_TEXT					文本节点
	\value NODE_CDATA_SECTION			CDATA节点
	\value NODE_ENTITY_REFERENCE		实体引用节点
	\value NODE_ENTITY					实体节点
	\value NODE_PROCESSING_INSTRUCTION	预处理声明
	\value NODE_COMMENT					注释
	\value NODE_DOCUMENT				文档节点
	\value NODE_DOCUMENT_TYPE			文档类型
	\value NODE_DOCUMENT_FRAGMENT		文档片段
	\value NODE_NOTATION				标注
*/

/*!
	构造函数。
*/
CXMLTreeNode::CXMLTreeNode()
	: m_data(NULL)
{
}

/*!
	构造函数. 使用XML树 \a pXT 初始化节点所属的树, 并指定 \a pNode 节点.
*/
CXMLTreeNode::CXMLTreeNode(CXMLTree* pXT, IXMLDOMNode* pNode)
	: m_data(new CXMLTreeNodePrivate(pXT, pNode))
{
}

/*!
	拷贝构造函数, 使用 \a node 节点索引.
*/
CXMLTreeNode::CXMLTreeNode(const CXMLTreeNode& node)
{
	if(NULL == node.m_data)
	{
		m_data = NULL;
	}
	else
	{
		m_data = new CXMLTreeNodePrivate(*node.m_data);
	}
}

/*!
	析构函数. 
*/
CXMLTreeNode::~CXMLTreeNode()
{
	Z_SAFE_DELETE(m_data);
}

/*!
	Returns 节点类型.
*/
DOMNodeType CXMLTreeNode::GetNodeType()
{
	if(m_data->m_spNode == NULL) return NODE_INVALID;

	DOMNodeType nodeType;
	m_data->m_spNode->get_nodeType(&nodeType);

	return nodeType;
}

/*!
	Returns 当前节点的元素内容(不包含当前节点).

	例如, XML的结构如下
	
	\code
		<config>
			<diagnostics d="3">
				<file>C:\temp\a.txt</file>
			</diagnostics>
			<diagnostics d="7">
				<file>D:\temp\a.txt</file>
				<proxy usedefault="true"/>
			</diagnostics>
		</config>
	\endcode

	并且当前节点位置为diagnostics元素, 则返回结果为

	\code
		<file>D:\temp\a.txt</file>
		<proxy usedefault="true"/>
	\endcode
*/
wstring CXMLTreeNode::GetElemContent()
{
	m_data->ValidateNode();

	wstring strSubDoc = GetSubDoc();

	size_t nBracketsBegin = strSubDoc.find(L'<');
	size_t nBracketsEnd = strSubDoc.find(L'>');
	if(nBracketsBegin != wstring::npos && nBracketsEnd != wstring::npos)
	{
		strSubDoc.replace(nBracketsBegin, nBracketsEnd - nBracketsBegin + 1, L"");
	}

	nBracketsBegin = strSubDoc.rfind(L'<');
	nBracketsEnd = strSubDoc.rfind(L'>');
	if(nBracketsBegin != wstring::npos && nBracketsEnd != wstring::npos)
	{
		strSubDoc.replace(nBracketsBegin, nBracketsEnd - nBracketsBegin + 1, L"");
	}

	return strSubDoc;
}

/*!
	设置元素的内容. \a strElemCtn 必须是是一个XML形式的片段

	\code
		<file>D:\temp\a.txt</file>
		<proxy usedefault="true"/>
	\endcode

	如果只是设置普通的字符串, 应该使用SetData()函数

	Returns 成功返回true.

	\sa SetData()
*/
bool CXMLTreeNode::SetElemContent(const wstring& strElemCtn)
{
	if(strElemCtn.empty()) return true;

	wstring strTempXml = L"<?xml version=\"1.0\" encoding=\"UTF-16\"?><root>" + strElemCtn + L"</root>";

	CXMLTree xt(strTempXml, true);
	CXMLTreeNode rootNode = xt[L"root"];
	int nChildCount = rootNode.GetChildCount();
	for(int i = 0; i < nChildCount; ++i)
	{
		RecursiveCopyNode(rootNode[i], *this);
	}

	return true;
}

/*!
	递归复制 \a src 中的元素至 \a targetParent 节点下面. 
*/
void CXMLTreeNode::RecursiveCopyNode(CXMLTreeNode& src, CXMLTreeNode& targetParent)
{
	if(src.m_data->m_spNode == NULL) return;
	if(src.GetNodeType() != NODE_ELEMENT)
	{
		wstring strData = src.GetData();
		targetParent.SetData(strData);
		return;
	}

	wstring strTagName = src.GetTagName();
	wstring value = src.GetData();
	if(src.GetChildCount()!=0)
	{
		value=L"";
	}
	else
	{
		value = src.GetData();
		if(strTagName.empty()) return;
	}
	CXMLTreeNode& newNode = targetParent.AddChildElement(strTagName, value);
	
	// copy attribute
	CComPtr<IXMLDOMNamedNodeMap> attrList = src.GetAttributeList();
	long lngLen = 0;
	attrList->get_length(&lngLen);

	for(long i = 0; i < lngLen; ++i)
	{
		CComPtr<IXMLDOMNode> spNode;
		attrList->get_item(i, &spNode);

		CComBSTR bstrNodeName;
		CComVariant varValue;
		spNode->get_nodeName(&bstrNodeName);
		spNode->get_nodeValue(&varValue);
		if(varValue.vt != VT_BSTR) continue;

		newNode.SetAttribute((BSTR)bstrNodeName, varValue.bstrVal);
	}	

	// other childs
	int nChildCount = src.GetChildCount();
	for(int i = 0; i < nChildCount; ++i)
	{
		RecursiveCopyNode(src[i], newNode);
	}
}

/*!
	Returns 属性节点数量.
*/
long CXMLTreeNode::GetAttributeCount()
{
	m_data->ValidateNode();

	CComPtr<IXMLDOMNamedNodeMap> pList = GetAttributeList();
	long lngCount = 0;
	if(!pList) return lngCount;

	pList->get_length(&lngCount);
	return lngCount;
}

/*!
	Returns \a index 索引处的节点.
*/
CXMLTreeNode CXMLTreeNode::GetAttributeAt(long index)
{
	m_data->ValidateNode();

	CComPtr<IXMLDOMNamedNodeMap> pList = GetAttributeList();
	CComPtr<IXMLDOMNode> spNode;
	pList->get_item(index, &spNode);

	return CXMLTreeNode(m_data->m_pXT, spNode);
}

/*!
	Returns 属性节点列表.
*/
CComPtr<IXMLDOMNamedNodeMap> CXMLTreeNode::GetAttributeList()
{
	CComPtr<IXMLDOMNamedNodeMap> attrList;
	m_data->m_spNode->get_attributes(&attrList);

	return attrList;
}

/*!
	返回元素的子内容(包含当前节点)片段, 含XML标记, 如下XML结构

	\code
		<config>
			<diagnostics d="3">
				<file>C:\temp\a.txt</file>
			</diagnostics>
			<diagnostics d="7">
				<file>D:\temp\a.txt</file>
				<proxy usedefault="true"/>
			</diagnostics>
		</config>
	\endcode

	若当前索引位于第一个diagnostics元素, 将返回以下内容

	\code
		<diagnostics d="3">
			<file>C:\temp\a.txt</file>
		</diagnostics>
	\endcode
*/
wstring CXMLTreeNode::GetSubDoc()
{
	CComBSTR bstrXml;
	m_data->m_spNode->get_xml(&bstrXml);

	return (BSTR)bstrXml;
}

/*!
	赋值操作, 设置节点的文本内容为 \a value.
*/
void CXMLTreeNode::operator= (const wstring& value)
{
	operator=(value.c_str());
}

/*!
	赋值操作, 设置节点的文本内容为 \a value.
*/
void CXMLTreeNode::operator= (const wchar_t* value)
{
	m_data->ValidateNode();
	if(!m_data->m_pXT->IsReadOnly())
	{
		m_data->m_spNode->put_text(CComBSTR(value));
	}	
}

/*!
	赋值操作, 设置节点的文本内容为 \a value.

	\note 根据布尔值设置节点值,真值为1,假值为0
*/
void CXMLTreeNode::operator= (bool value)
{
	operator=(value ? L"1" : L"0");
}

/*!
	赋值操作, 设置节点的文本内容为 \a value.

	\note 根据布尔值设置节点值,真值为1,假值为0
*/
void CXMLTreeNode::operator= (int value)
{
	operator=(SU::ToString(value).c_str());
}

/*!
	赋值操作, 设置节点的文本内容为 \a value.
*/
void CXMLTreeNode::operator= (long value)
{
	operator=(SU::ToString(value).c_str());
}

/*!
	赋值函数, 从 \a rhs 中复制节点的信息.
*/
CXMLTreeNode& CXMLTreeNode::operator=(const CXMLTreeNode& rhs)
{
	if(&rhs == this) return *this;
	
	if(!rhs.IsValid())
	{
		return *this;
	}

	if(m_data != NULL)
		Z_SAFE_DELETE(m_data);

	m_data = new CXMLTreeNodePrivate(rhs.m_data->m_pXT, rhs.m_data->m_spNode);
	return *this;
}

/*!
	重载索引操作符, 利用字符串索引 \a tagName 直接返回指定的节点对象, 如果有多个相同的同级节点, 那么只返回第一个.
	对于只读文档, 不自动添加空元素.

	Returns 相应名称的第一个节点.

	\note XPATH作为节点索引查找, 效率奇低, 慎用!
*/
CXMLTreeNode CXMLTreeNode::operator[] (const wstring& tagName)
{
	m_data->ValidateNode();
	
	CComPtr<IXMLDOMNode> spNode;
	m_data->m_spNode->selectSingleNode(CComBSTR(tagName.c_str()), &spNode);

	if(spNode == NULL && !m_data->m_pXT->IsReadOnly())
	{
		return AddChildElement(tagName, L"");
	}
	else
	{
		CXMLTreeNode nodeToReturn(m_data->m_pXT, spNode);

		return nodeToReturn;
	}
}

/*!
	重载索引操作符.

	Returns 使用数字 \a nIndex 作为索引, 索引从0开始, 该重载对于不存在的数字索引, 不创建任何节点, 返回一个无效节点.
*/
CXMLTreeNode CXMLTreeNode::operator[] (int nIndex)
{
	m_data->ValidateNode();

	CXMLTreeNode nodeToReturn(m_data->m_pXT, NULL);
	if(GetNodeType() == NODE_ELEMENT)
	{
		CComPtr<IXMLDOMNodeList> spNodeList;
		m_data->m_spNode->get_childNodes(&spNodeList);

		CComPtr<IXMLDOMNode> spNode;
		spNodeList->get_item(nIndex, &spNode);

		nodeToReturn.m_data->m_spNode = spNode;
	}

	return nodeToReturn;
}

/*!
	Returns \a name 属性的值.
*/
wstring CXMLTreeNode::GetAttribute(const wstring& name)
{
	m_data->ValidateNode();

	CComVariant var;
	if(GetNodeType() == NODE_ELEMENT)
	{
		CComQIPtr<IXMLDOMElement> spElem(m_data->m_spNode);
		spElem->getAttribute(CComBSTR(name.c_str()), &var);
	}
	else
	{
		CComPtr<IXMLDOMNamedNodeMap> attrList;
		m_data->m_spNode->get_attributes(&attrList);
		if(attrList == NULL) return L"";

		CComPtr<IXMLDOMNode> attrNode;
		attrList->getNamedItem(CComBSTR(name.c_str()), &attrNode);
		if(!attrNode) return L"";

		attrNode->get_nodeValue(&var);
	}

	if(var.vt != VT_BSTR) return L"";

	return wstring(var.bstrVal);
}

/*!
	为节点的 \a name 属性设置值 \a value, 如果该节点不是NODE_ELEMENT, 不会设置属性.
*/
void CXMLTreeNode::SetAttribute(const wstring& name, const wstring& value)
{
	m_data->ValidateNode();

	if(name.empty()) return;

	if(!m_data->m_pXT->IsReadOnly() && GetNodeType() == NODE_ELEMENT)
	{
		CComQIPtr<IXMLDOMElement> spElem = m_data->m_spNode;
		spElem->setAttribute(CComBSTR(name.c_str()), CComVariant(value.c_str()));
	}
}

/*!
	Returns 当前节点名
*/
wstring CXMLTreeNode::GetTagName()
{
	m_data->ValidateNode();

	CComBSTR bstrNodeName;
	m_data->m_spNode->get_nodeName(&bstrNodeName);

	return (BSTR)bstrNodeName;
}

/*!
	Returns 当前节点是否有效。
*/
bool CXMLTreeNode::IsValid() const
{
	return m_data != NULL && m_data->IsValid();
}

//2013-1-23 jzh modify 3.3.0005.0 修订内容为空返回空串
/*!
	Returns 节点的值
*/
wstring CXMLTreeNode::GetData()
{
	m_data->ValidateNode();

	CComBSTR bstrData;
	m_data->m_spNode->get_text(&bstrData);

	if(bstrData.Length() == 0)
	{
		return wstring();
	}
	
	return (BSTR)bstrData;
}

/*!
	设置节点值为 \a value . 如果想将XML片段设置进去, 应该使用 SetElemContent().

	\sa CXMLTreeNode::SetElemContent()
*/
void CXMLTreeNode::SetData(const wstring& value)
{
	m_data->ValidateNode();
	if(m_data->m_pXT->IsReadOnly()) return;

	m_data->m_spNode->put_text(CComBSTR(value.c_str()));
}

/*!
	Returns 节点的布什值.
*/
bool CXMLTreeNode::GetBoolData()
{
	return SU::ToBool(GetData());
}

/*!
	Returns 节点的整型值.
*/
int CXMLTreeNode::GetIntData()
{
	return SU::ToInt(GetData());
}

/*!
	Returns 节点的长整型值.
*/
long CXMLTreeNode::GetLongData()
{
	return SU::ToLong(GetData());
}

/*!
	在当前元素下面添加一个 \a tagName 元素,其值为 \a value.

	Returns 新添加的子元素.
*/
CXMLTreeNode CXMLTreeNode::AddChildElement(const wstring& tagName, const wstring& value)
{
	m_data->ValidateNode();

	CComPtr<IXMLDOMDocument> doc;
	m_data->m_spNode->get_ownerDocument(&doc);

	CComPtr<IXMLDOMElement> newElem;
	doc->createElement(CComBSTR(tagName.c_str()), &newElem);
	
	if(!newElem) throw CEMRException(L"子元素创建失败!");	

	if(value.length() > 0) newElem->put_text(CComBSTR(value.c_str()));

	CComPtr<IXMLDOMNode> spNewChild;
	m_data->m_spNode->appendChild(newElem, &spNewChild);

	return CXMLTreeNode(m_data->m_pXT, newElem);
}

/*!
	在当前元素下面添加一个CDATA元素, 其值为 \a value.

	Returns 新添加的CDATA节点.
*/
CXMLTreeNode CXMLTreeNode::AddChildAsCDATASection( const wstring& value )
{
	m_data->ValidateNode();

	CComPtr<IXMLDOMDocument> doc;
	m_data->m_spNode->get_ownerDocument(&doc);

	CComPtr<IXMLDOMCDATASection> spCDATASection;
	doc->createCDATASection(CComBSTR(value.c_str()), &spCDATASection);
	
	if(!spCDATASection) throw CEMRException(L"创建CDATA节点失败!");

	CComPtr<IXMLDOMNode> spNewChild;
	m_data->m_spNode->appendChild(spCDATASection, &spNewChild);

	return CXMLTreeNode(m_data->m_pXT, spCDATASection);
}

/*!
	Returns 子节点数量, 若指定标记名称 \a tagName, 只返回具有这个名称的节点数量.
*/
int CXMLTreeNode::GetChildCount(const wstring& tagName/* = L""*/)
{
	m_data->ValidateNode();

	long nCount = 0;
	if(tagName.empty())
	{
		CComPtr<IXMLDOMNodeList> nodeList;
		m_data->m_spNode->get_childNodes(&nodeList);
		nodeList->get_length(&nCount);
	}
	else
	{
		CComPtr<IXMLDOMNodeList> nodeList;
		GetChildListByTagName(tagName, &nodeList);

		nodeList->get_length(&nCount);
	}

	return (int)nCount;
}

/*!
	获取 \a tagName 名称标记的数量, 存储在 \a pNodeList 中返回.
*/
void CXMLTreeNode::GetChildListByTagName(const wstring& tagName, IXMLDOMNodeList** pNodeList)
{
	m_data->ValidateNode();

	CComBSTR bstrNodeName;
	m_data->m_spNode->get_nodeName(&bstrNodeName);
	
	wstring strQuery = tagName;
	strQuery = wstring(bstrNodeName) + _T("/") + strQuery;

	CComQIPtr<IXMLDOMElement> spElem = m_data->m_spNode;
	spElem->getElementsByTagName(CComBSTR(tagName.c_str()), pNodeList);
}

/*!
	Returns 父节点
*/
CXMLTreeNode CXMLTreeNode::GetParentNode()
{
	m_data->ValidateNode();

	CComPtr<IXMLDOMNode> spParentNode;
	m_data->m_spNode->get_parentNode(&spParentNode);

	return CXMLTreeNode(m_data->m_pXT,spParentNode);
}

/*!
	复制节点 \a src 的内容, \a bRecursive 指定是否递归复制.
*/
void CXMLTreeNode::CopyNode(CXMLTreeNode& src, bool bRecursive)
{
	if(src.m_data->m_spNode == NULL) return;
	if(src.GetNodeType() != NODE_ELEMENT)
	{
		wstring strData = src.GetData();
		this->SetData(strData);
		return;
	}

	wstring strTagName = src.GetTagName();
	if(strTagName.empty()) return;

	// copy attribute
	CComPtr<IXMLDOMNamedNodeMap> attrList = src.GetAttributeList();
	long lngLen = 0;
	attrList->get_length(&lngLen);

	for(long i = 0; i < lngLen; ++i)
	{
		CComPtr<IXMLDOMNode> spNode;
		attrList->get_item(i, &spNode);

		CComBSTR bstrNodeName;
		CComVariant varValue;
		spNode->get_nodeName(&bstrNodeName);
		spNode->get_nodeValue(&varValue);
		if(varValue.vt != VT_BSTR) continue;

		this->SetAttribute((BSTR)bstrNodeName, varValue.bstrVal);
	}	

	if(!bRecursive)
	{
		return;
	}

	//递归复制
	int nChildCount = src.GetChildCount();
	for(int i = 0; i < nChildCount; ++i)
	{
		CopyNode(src[i], bRecursive);
	}	
}

/*!
	删除 \a strTagName 子节点.\a bRemoveNodesWithSameName 指定是否删除所有同名节点.

	Returns 节点不存在或非只读模式下成功删除,返回true.失败返回false

	\note 删除具有指定名称的节点,bRemoveSameNodes为true时,会删除所有同名的节点.
		删除的节点如果存在引用,那么在解除引用时,程序会出错.
 */
bool CXMLTreeNode::RemoveChildElement(const wstring& strTagName, bool bRemoveNodesWithSameName/* = false*/)
{
	m_data->ValidateNode();

	if(m_data->m_pXT->IsReadOnly()) return false;

	CComPtr<IXMLDOMNode> spChild;
	m_data->m_spNode->selectSingleNode(CComBSTR(strTagName.c_str()), &spChild);	

	if(spChild == NULL) return true;
	
	// MSDN: removeChild() 方法若不提供第二个参数,不会真正删除节点.
	CComPtr<IXMLDOMNode> spRemoved;
	HRESULT hr = m_data->m_spNode->removeChild(spChild, &spRemoved);

	return hr == S_OK;
}

/*!
	\brief 删除 \a nChildIndex 索引处的子节点.

	Returns 节点不存在或非只读模式下成功删除,返回true.失败返回false

	\note 删除的节点如果存在引用,那么在解除引用时,程序会出错.

	\sa RemoveChildElement()
*/
bool CXMLTreeNode::RemoveChildElement(int nChildIndex)
{
	m_data->ValidateNode();

	if(m_data->m_pXT->IsReadOnly()) return false;

	if(GetNodeType() != NODE_ELEMENT) return false;

	CComPtr<IXMLDOMNodeList> spNodeList;
	m_data->m_spNode->get_childNodes(&spNodeList);

	long lngLen = 0;
	spNodeList->get_length(&lngLen);
	if(lngLen - 1 < nChildIndex) return true;

	CComPtr<IXMLDOMNode> spChild;
	spNodeList->get_item(nChildIndex, &spChild);
	if(spChild == NULL) return true;

	CComPtr<IXMLDOMNode> spRemoved;

	HRESULT hr = m_data->m_spNode->removeChild(spChild, &spRemoved);
	return hr == S_OK;
}

/*!
	\class CXMLTree
	\inmodule ZCore
	\ingroup Utility/XmlDom

	\brief XML解析树, 使用多重索引解析XML.

	目前已经支持XPATH方式的节点读取. 可使用XPATH来寻找节点, 方便高效. 接口支持从文件中直接加载
	XML文件内容或保存到本地文件上, 可用于调试XML数据.

	以下代码加载XML字符串：
	
	\code
		wstring strXML = L"<ELEM><CHELEM1>data</CHELEM1><CHELEM2/><CHELEM3 attr='hi'/></ELEM>";
		
		CXMLTree xt(strXML);
		wstring value = xt[L"ELEM"][L"CHELEM3"].GetAttribute(L"attr");
	\endcode

	访问方式类似于树的节点遍历.

	\note cboy remark 2013-6-26
	
	如果在 ::CoUninitialize() 之后析构组建对象将会导致退出时程序崩溃, COM程序退出前必须确保所有COM对象已经释放.
	在组件退出的时候系统会进行如下操作：

	\list
		\li ::CoUninitialize
		\li 释放static对象
	\endlist

	若组件里有static CXMLTree对象或成员,在组件退出时会崩溃, 因为 CXMLTree 在析构函数里调用 Release() 崩溃.
	
	解决方法:
	由于组件退出之前先调用了::CoUninitialize, 然后才开始释放组件里的static对象, static对象负责析构其成员变量CXMLTree.
	因此, 对于static情况, 请使用如下规则：
	\list
		\li 应用程序退出前需要显示调用 Release()
		\li 在异常中也要做此处理
	\endlist

	CXMLTree 如果作为static对象的成员变量必须遵守以上规则.
*/

/*!
	构造函数.
*/
CXMLTree::CXMLTree()
	: m_data(new CXMLTreePrivate(NULL, false, NULL))
{
	ResetXML(CComBSTR(L"<?xml version='1.0'?><root/>"));
}

/*!
	构造函数. 使用 \a pstrXML 构造XML树. \a bReadOnly 可指定构造一个只读的文档. 
*/
CXMLTree::CXMLTree(const wchar_t *const pstrXML, bool bReadOnly)
	: m_data(new CXMLTreePrivate(NULL, bReadOnly, NULL))
{
	ResetXML(CComBSTR(((pstrXML == NULL) ? L"<?xml version='1.0'?><root/>" : pstrXML)));
}

/*!
	构造函数. 使用 \a strXML 构造XML树. \a bReadOnly 可指定构造一个只读的文档. 
*/
CXMLTree::CXMLTree(const wstring& strXML, bool bReadOnly/* = false*/)
	: m_data(new CXMLTreePrivate(NULL, bReadOnly, NULL))
{
	ResetXML(CComBSTR(strXML.data()));
}

/*!
	构造函数. 使用 \a strXML 构造XML树. \a bReadOnly 可指定构造一个只读的文档. 
*/
CXMLTree::CXMLTree(const CString& strXML, bool bReadOnly/* = false*/)
	: m_data(new CXMLTreePrivate(NULL, bReadOnly, NULL))
{
	ResetXML(CComBSTR(strXML.GetString()));
}

/*!
	构造函数. 使用 \a bstrXML 构造XML树. \a bReadOnly 可指定构造一个只读的文档. 
*/
CXMLTree::CXMLTree(const CComBSTR &bstrXML, bool bReadOnly/* = false*/)
	: m_data(new CXMLTreePrivate(NULL, bReadOnly, NULL))
{
	ResetXML(bstrXML, bReadOnly);
}

/*!
	析构函数 
*/
CXMLTree::~CXMLTree()
{
	Release();
}
/*
	拷贝构造函数：拷贝对象
	赋值运算符：释放对象原本维护的内容，将目标对象的内容拷贝到当前对象中。
*/
/*!
	CXMLTree内部维护的XMLDOMDoc对象 \a ref 的拷贝。
	该调用会重新构建DOM对象并且拷贝原DOM对象内的内容。
	开销较大。
*/
CXMLTree::CXMLTree(const CXMLTree &ref)
	: m_data(new CXMLTreePrivate(NULL, false, NULL))
{
	CComBSTR bstrXML;
	bool bLoadOk = ref.GetXML(bstrXML);
	if(bLoadOk)
		ResetXML(bstrXML);
}

/*!
	复制 \a ref 值。
*/
CXMLTree &CXMLTree::operator=(const CXMLTree &ref)
{
	if(this == &ref)
		return *this;

	Release();

	m_data = new CXMLTreePrivate(NULL, false, NULL);
	CComBSTR bstrXML;
	bool bLoadOk = ref.GetXML(bstrXML);
	if(bLoadOk)
		ResetXML(bstrXML);
	return *this;
}
/*!
	释放m_spDOM关联的DOM对象以及SchemaCache对象
*/
void CXMLTree::Release()
{
	if(m_data != NULL)
	{
		m_data->m_spDom.Release();
		Z_SAFE_DELETE(m_data->m_pSchemaCache);
		Z_SAFE_DELETE(m_data);
	}
}

// 2011.07.30 wfj modify 2.6.0004.0 使用<?xml version="1.0" encoding="UTF-8"?>产生的XML给 xerces-c++无法解析, 只能使用UTF-16编码才行
// 2012.04.22 wfj modify 3.0.0005.0 替换字符串中的回车与换行字符,防止不可见的特殊字符导致XML解析失败
/*!
	释放原来的DOM树, 并使用 \a strXML 重新加载, \a bReadOnly 可指定是否以只读方式生成树.
	Returns 重置成功, 返回true.
*/
bool CXMLTree::ResetXML(const wstring& strXML/* = L""*/, bool bReadOnly/* = false*/)
{
	return ResetXML(CComBSTR(strXML.data()), bReadOnly);
}

/*!
	使用 \a strXML 修改内存树, 并使用 \a bReadOnly 指定是否为只读.
	Returns 成功返回 true.
*/
bool CXMLTree::ResetXML(const CString& strXML, bool bReadOnly/* = false*/)
{
	return ResetXML(CComBSTR(strXML.GetString()), bReadOnly);
}

/*!
	使用 \a strXML 修改内存树, 并使用 \a bReadOnly 指定是否为只读.
	Returns 成功返回 true.
*/
bool CXMLTree::ResetXML(const wchar_t * const strXML, bool bReadOnly)
{
	if(strXML == NULL) return false;

	return ResetXML(CComBSTR(strXML), bReadOnly);
}
/*!
	使用 \a bstrXML 重新生成DOM, 并使用 \a bReadOnly 指定是否为只读.

	Returns 成功返回 true.
*/
bool CXMLTree::ResetXML(const CComBSTR &bstrXML, bool bReadOnly/* = false*/)
{
	if(!CreateDOMDocument()) return false;
	m_data->m_readOnly = bReadOnly;

	HRESULT hr = S_FALSE;
	VARIANT_BOOL bLoadOk(VARIANT_FALSE);
	hr = m_data->m_spDom->loadXML(
		bstrXML.Length() == 0 ? CComBSTR(L"<?xml version='1.0'?><root/>") : bstrXML, 
		&bLoadOk);

	if(hr != S_OK || bLoadOk == VARIANT_FALSE)
	{
#ifdef _DEBUG
		CXMLSchemaDebugger::OutputXMLParseError(*this);
#endif
		return false;
	}

	return true;
}

// cboy remark 2014-2-17
/*!
	检测是否包含字节点 \a strTagName, \a bRecursive 为false时仅检测深度为1的字节点.

	Returns 是否含有指定的节点。
*/
bool CXMLTreeNode::HasChildNode(const wstring &strTagName, bool bRecursive)
{
	if(m_data->m_spNode == NULL || strTagName.empty()) 
		return false;

	VARIANT_BOOL bHasChildNodes(FALSE);
	HRESULT hr = m_data->m_spNode->hasChildNodes(&bHasChildNodes);
	if(SUCCEEDED(hr) && bHasChildNodes == FALSE)
		return false;

	CComPtr<IXMLDOMNodeList> spNodeList;
	hr = m_data->m_spNode->get_childNodes(&spNodeList);
	if(hr != S_OK || spNodeList == NULL)
		return false;

	long lChildCount(0);
	hr = spNodeList->get_length(&lChildCount);
	if(hr != S_OK || lChildCount == 0)
		return false;

	for(long lIndex=0; lIndex<lChildCount; ++lIndex)
	{
		CComPtr<IXMLDOMNode> spTmpNode;
		hr = spNodeList->get_item(lIndex, &spTmpNode);
		if(SUCCEEDED(hr) && spTmpNode != NULL)
		{	
			CComBSTR bstrChildTagName;
			if(SUCCEEDED(spTmpNode->get_nodeName(&bstrChildTagName)))
			{
				if(bstrChildTagName == CComBSTR(strTagName.data()))
					return true;
				
				if(bRecursive && CXMLTreeNode(m_data->m_pXT, spTmpNode).HasChildNode(strTagName))
					return true;
			}
		}
	}
	return false;
}

/*!
	开启CXMLTree对象上的XMLSchema校验支持, 
	\a bEnable 为true将开启校验支持
	\a bEnable 为false将以关闭支持,　此操作将会重建DOM对象,并会还原之前DOM对象中的文档内容,开销较大.
	如非必要请勿使用此操作,更好的方式是重新创建一个CXMLTree对象

	Returns 启用是否成功.
*/
bool CXMLTree::EnableSchemaValidation(bool bEnable)
{
	HRESULT hr = E_FAIL;
	if(m_data->m_pSchemaCache == NULL)
	{
		m_data->m_pSchemaCache = new CXMLSchemaCache();
		if(!m_data->m_pSchemaCache->Create())
			return false;
	}
	if(bEnable)
	{
		hr = m_data->m_spDom->putref_schemas(*m_data->m_pSchemaCache);
		return S_OK == hr;
	}
	else
	{
		CComBSTR  bstrXML;
		bool bOk = GetXML(bstrXML);
		m_data->m_spDom.Release();
		return ResetXML(bstrXML);
	}
}
/*!
	向当前DOM对象关联的SchemaCache内增加用于校验XML文档正确定的Schema对象
	\a	strSchema xml形式的schema描述
	\a	strNamespace schema作用的命名空间

	Returns 成功返回true.
*/
bool CXMLTree::AddSchema(const wstring &strSchema, const wstring &strNamespace)
{
	if(m_data->m_pSchemaCache == NULL)
		return false;

	return m_data->m_pSchemaCache->AddSchema(CComBSTR(strSchema.data()), CComBSTR(strNamespace.data()));
}
/*!
	解除向当前DOM对象关联的SchemaCache内增加用于校验XML文档正确定的Schema对象的绑定
	\a strNamespace schema作用的命名空间.

	Returns 删除是否成功.
*/
bool CXMLTree::RemoveSchema(const wstring &strNamespace)
{	
	if(m_data->m_pSchemaCache == NULL)
		return false;

	return  m_data->m_pSchemaCache->RemoveSchema(CComBSTR(strNamespace.data()));
}
// 2012.09.20 wfj modify 3.0.00011.0 修复索引操作符导致的内存泄漏
/*!
	重载, 返回名称为 \a tagName 的节点列表.
*/
CXMLTreeNode CXMLTree::operator[] (const wstring& tagName)
{
	if(!IsValid())
	{
		CEMREventLog log(GetXML());
		log.Write();

		CComPtr<IXMLDOMParseError> spParseErr;
		m_data->m_spDom->get_parseError(&spParseErr);

		CComBSTR bstrError;
		spParseErr->get_reason(&bstrError);

		throw CEMRException((BSTR)bstrError);
	}

	CComPtr<IXMLDOMElement> spRootElem;
	m_data->m_spDom->get_documentElement(&spRootElem);

	return CXMLTreeNode(this, spRootElem);
}

/*!
	Returns 根节点
*/
CXMLTreeNode CXMLTree::GetRootNode()
{
	if(!IsValid())
	{
		CComPtr<IXMLDOMParseError> spParseErr;
		m_data->m_spDom->get_parseError(&spParseErr);

		CComBSTR bstrError;
		if(SUCCEEDED(spParseErr->get_reason(&bstrError)))
			throw CEMRException((BSTR)bstrError);
	}

	CComPtr<IXMLDOMElement> spRootElem;
	m_data->m_spDom->get_documentElement(&spRootElem);

	return CXMLTreeNode(this, spRootElem);
}

/*!
	Returns DOM树的字符串表示,以出参形式 \a bstrXML 返回.
*/
bool CXMLTree::GetXML(CComBSTR &bstrXML) const
{
	if(m_data->m_spDom == NULL)
		return false;

	return m_data->m_spDom->get_xml(&bstrXML) == S_OK;
}

/*!
	Returns DOM树的字符串表示.
*/
wstring CXMLTree::GetXML() const
{
	CComBSTR bstrXML;
	return GetXML(bstrXML) ? wstring(bstrXML.m_str) : wstring(L"");
}

/*!
	创建成员变量m_spDOM关联的对象CLSID_DOMDocument40
	并指定不以异步的方式加载DOM文档.

	Returns 创建是否成功.
*/
bool CXMLTree::CreateDOMDocument()
{
	if(m_data->m_spDom != NULL)
		return true;

	HRESULT hr = S_FALSE;
	hr = m_data->m_spDom.CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER);
	if(S_OK == hr)
	{
		return S_OK == m_data->m_spDom->put_async(VARIANT_FALSE);
	}

#ifdef _DEBUG
	::OutputDebugStringW(_com_error(hr).ErrorMessage());
#endif
	return false;
}

/*!
	Returns 成功从 \a fileName 加载XML, 返回true.
*/
bool CXMLTree::Load(const wstring& fileName)
{
	if(!CreateDOMDocument())
		return false;

	VARIANT_BOOL bLoadOk(VARIANT_FALSE);
	HRESULT hr = m_data->m_spDom->load(CComVariant(fileName.c_str()), &bLoadOk);
	if(hr != S_OK || bLoadOk == VARIANT_FALSE)
	{
		CXMLSchemaDebugger::OutputXMLParseError(*this);
		return false;
	}

	return true;
}

/*!
	将DOM树写入到 \a strFileName 文件中, 可指定文件编码为 \a strEncoding.

	Returns 成功返回true.
*/
bool CXMLTree::WriteToFile(const wstring& strFileName, const wstring& strEncoding/* = L""*/)
{
	HRESULT hr = m_data->m_spDom->save(CComVariant(strFileName.c_str()));
	return SUCCEEDED(hr) ? true : false;
}

/*!
	Returns DOM树是否有效.
*/
bool CXMLTree::IsValid() const
{
	if(!m_data->m_spDom) return false;

	CComPtr<IXMLDOMElement> spRootElem;
	m_data->m_spDom->get_documentElement(&spRootElem);

	return NULL != spRootElem;
}

/*!
	Returns DOM树是否为只读.
*/
bool CXMLTree::IsReadOnly() const
{
	return m_data->m_readOnly;
}

/*!
	使用出参 \a pDom 返回XML DOM接口.
*/
void CXMLTree::GetDomDocument(IXMLDOMDocument2** pDom)
{
	m_data->m_spDom.CopyTo(pDom);
}

/*!
	Returns DOM 中名为 \a strTagName 的节点。
*/
CXMLTreeNode* CXMLTree::GetNode(const wstring &strTagName)
{
	if(m_data->m_spDom == NULL)
	{
		::OutputDebugString(_T("获取指定节点名称出错: XML文档对象模型尚未初始化\r\n"));
		return NULL;
	}

	if(strTagName.empty())
	{
		::OutputDebugString(_T("获取指定节点名称出错: 未指定节点名称\r\n"));
		return NULL;
	}

	CComPtr<IXMLDOMNodeList> spNodeList;
	HRESULT hr = m_data->m_spDom->getElementsByTagName(CComBSTR(strTagName.data()), &spNodeList);
	if(hr != S_OK || spNodeList == NULL)
	{
		::OutputDebugString(_T("获取指定节点名称出错: 未知错误\r\n"));
		return NULL;
	}

	long lChildCount(0);
	hr = spNodeList->get_length(&lChildCount);
	if(hr != S_OK || lChildCount != 1)
	{
		wstringstream err;
		err << L"获取指定节点名称出错: " << (lChildCount == 0 ? L"不存在该节点\r\n" : L"包含一个以上的指定节点\r\n");
		::OutputDebugString(err.str().data());
		return NULL;
	}

	CComPtr<IXMLDOMNode> spNode;
	hr = spNodeList->get_item(0, &spNode);
	if(hr != S_OK || spNode == NULL)
	{
		OutputDebugString(_T("获取指定节点名称出错: 未知错误\r\n"));
		return NULL;
	}

	return new CXMLTreeNode(this, spNode);
}
/*!
	设置XML DOM属性 \a name 的值为 \a value.
*/
HRESULT CXMLTree::SetProperty(BSTR name, VARIANT value)
{
	if(m_data == NULL || m_data->m_spDom == NULL)
	{
		return E_FAIL;
	}

	return m_data->m_spDom->setProperty(name, value);
}

/*!
	根据 \a xpath 筛选节点，并用 \a pNodeList 返回。
*/
HRESULT CXMLTree::SelectNodes(BSTR xpath, IXMLDOMNodeList** pNodeList)
{
	if(m_data == NULL || m_data->m_spDom == NULL)
	{
		return E_FAIL;
	}

	return m_data->m_spDom->selectNodes(xpath, pNodeList);
}

END_ZEMR_NAMESPACE