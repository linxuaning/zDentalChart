#ifndef __XML_TREE_H
#define __XML_TREE_H

#include <string>
#include <WTypes.h>
#include <atlstr.h>
#include <msxml2.h>
#include "../include/znamespace.h"

using namespace std;

BEGIN_ZEMR_NAMESPACE

class XMLSchemaCache;
class CXMLTreePrivate;
class CXMLTreeNodePrivate;

class ZCORE_API CXMLTreeNode
{
	friend class CXMLTree;

public:
	CXMLTreeNode();
	CXMLTreeNode(CXMLTree* pXT, IXMLDOMNode* pNode);
	CXMLTreeNode(const CXMLTreeNode& node);
	~CXMLTreeNode();

public:
	void operator= (const wstring& value);
	void operator= (const wchar_t* value);
	void operator= (bool value);
	void operator= (int value);
	void operator= (long value);
	CXMLTreeNode& operator=(const CXMLTreeNode& rhs);

	CXMLTreeNode operator[] (const wstring& strNodeName);
	CXMLTreeNode operator[] (int nIndex);

public:
	wstring GetAttribute(const wstring& strAttrName);
	void SetAttribute(const wstring& strAttrName, const wstring& value);

	long GetAttributeCount();
	CXMLTreeNode GetAttributeAt(long index);
	CComPtr<IXMLDOMNamedNodeMap> GetAttributeList();

	wstring GetData();
	void SetData(const wstring& value);

	bool GetBoolData();
	int GetIntData();
	long GetLongData();

	wstring GetElemContent();
	bool SetElemContent(const wstring& strElemCtn);

	wstring GetSubDoc();
	wstring GetTagName();

	bool IsValid()const;

public:
	int GetChildCount(const wstring& strTagName = L"");

	CXMLTreeNode AddChildElement(const wstring& strTagName, const wstring& value = L"");
	CXMLTreeNode AddChildAsCDATASection(const wstring& value);
	bool RemoveChildElement(const wstring& strTagName, bool bRemoveNodesWithSameName = false);
	bool RemoveChildElement(int nChildIndex);

	bool HasChildNode(const wstring &strTagName, bool bRecursive = false);

	void GetChildListByTagName(const wstring& strTagName, IXMLDOMNodeList** pNodeList);
	DOMNodeType GetNodeType();

	void CopyNode(CXMLTreeNode& src, bool bRecursive = false);

	//获取父节点
	CXMLTreeNode GetParentNode();

protected:
	void RecursiveCopyNode(CXMLTreeNode& src, CXMLTreeNode& targetParent);
	
protected:
	CXMLTreeNodePrivate* m_data;
};

class ZCORE_API CXMLTree
{
	friend class CXMLSchemaDebugger;
	friend class CXMLSchemaCache;
	friend class CDebugHelperMSXML;

public:
	CXMLTree(const CXMLTree &ref);
	CXMLTree &operator=(const CXMLTree &ref);

public:
	CXMLTree();
	CXMLTree(const wstring& strXML,					bool bReadOnly = false);
	CXMLTree(const CString& cstrXML,				bool bReadOnly = false);
	CXMLTree(const wchar_t *const pstrXML,		bool bReadOnly = false);
	CXMLTree(const CComBSTR &bstrXML,		bool bReadOnly = false);	
	~CXMLTree();

public:
	bool ResetXML(const wstring& strXML,				bool bReadOnly = false);
	bool ResetXML(const CString& strXML,				bool bReadOnly = false);
	bool ResetXML(const wchar_t * const strXML,		bool bReadOnly = false);
	bool ResetXML(const CComBSTR &bstrXML,		bool bReadOnly = false);
	void Release();

public: //schema support
	bool EnableSchemaValidation(bool bEnable);
	bool AddSchema(const wstring &strSchema, const wstring &strNamespace);
	bool RemoveSchema(const wstring &strNamespace);

public:
	CXMLTreeNode operator[] (const wstring& strRootTagName);
	CXMLTreeNode GetRootNode();

	CXMLTreeNode* GetNode(const wstring &strTagName);

	void GetDomDocument(IXMLDOMDocument2** pDom);

public:
	bool IsValid() const;
	bool IsReadOnly() const;

public:
	bool Load(const wstring& strFileName);
	bool WriteToFile(const wstring& strFileName, const wstring& strEncoding = L"");

	HRESULT SetProperty(BSTR name, VARIANT value);
	HRESULT SelectNodes(BSTR xpath, IXMLDOMNodeList** pNodeList);

	wstring GetXML() const;
	bool GetXML(CComBSTR &bstrXML) const;

protected:
	bool CreateDOMDocument();

protected:
	CXMLTreePrivate* m_data;
};

END_ZEMR_NAMESPACE

#endif