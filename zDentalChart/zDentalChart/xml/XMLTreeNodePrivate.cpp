#include "../include/EMRException.h"
#include "../include/XMLTree.h"
#include "XMLTreeNodePrivate.h"

BEGIN_ZEMR_NAMESPACE

CXMLTreeNodePrivate::CXMLTreeNodePrivate(CXMLTree* pXT, IXMLDOMNode* pNode)
	: m_pXT(pXT)
	, m_spNode(pNode)
	, m_errorInfo(L"")
{
}

/*!

*/
CXMLTreeNodePrivate::CXMLTreeNodePrivate(const CXMLTreeNodePrivate& node)
	: m_pXT(node.m_pXT)
	, m_spNode(node.m_spNode)
	, m_errorInfo(node.m_errorInfo)
{

}

CXMLTreeNodePrivate::~CXMLTreeNodePrivate()
{
}

/*!
	验证节点索引是否有效.

	\note 若索引无效, 使用异常方式结束节点访问. 因为对节点来讲, 无效的索引是无法进行后续操作的.
*/
void CXMLTreeNodePrivate::ValidateNode()
{
	if(!m_spNode)
	{
		throw CEMRException(L"无效XML节点, XML内容:\n" + m_pXT->GetXML());
	}

	if(!m_errorInfo.empty())
	{
		throw CEMRException(m_errorInfo);
	}
}

/*!
	Returns 节点索引的有效性.
*/
bool CXMLTreeNodePrivate::IsValid()
{
	return m_spNode!=NULL;
}

CXMLTreeNodePrivate& CXMLTreeNodePrivate::operator=( const CXMLTreeNodePrivate& rhs )
{
	if(this == &rhs) return *this;

	this->m_pXT = rhs.m_pXT;
	this->m_spNode = rhs.m_spNode;
	this->m_errorInfo = rhs.m_errorInfo;

	return *this;
}


END_ZEMR_NAMESPACE