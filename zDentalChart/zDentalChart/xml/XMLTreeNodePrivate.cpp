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
	��֤�ڵ������Ƿ���Ч.

	\note ��������Ч, ʹ���쳣��ʽ�����ڵ����. ��Ϊ�Խڵ�����, ��Ч���������޷����к���������.
*/
void CXMLTreeNodePrivate::ValidateNode()
{
	if(!m_spNode)
	{
		throw CEMRException(L"��ЧXML�ڵ�, XML����:\n" + m_pXT->GetXML());
	}

	if(!m_errorInfo.empty())
	{
		throw CEMRException(m_errorInfo);
	}
}

/*!
	Returns �ڵ���������Ч��.
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