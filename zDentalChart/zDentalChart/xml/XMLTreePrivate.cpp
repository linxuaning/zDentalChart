#include "XMLTreePrivate.h"

BEGIN_ZEMR_NAMESPACE

/*!

*/
CXMLTreePrivate::CXMLTreePrivate(CXMLTreePrivate& rhs)
{
	m_readOnly = rhs.m_readOnly;
	m_spDom = rhs.m_spDom;
	m_pSchemaCache = rhs.m_pSchemaCache;
}

/*!

*/
CXMLTreePrivate::CXMLTreePrivate(IXMLDOMDocument2* pDom, bool readOnly, CXMLSchemaCache* pSchemaCache)
	: m_spDom(pDom)
	, m_readOnly(readOnly)
	, m_pSchemaCache(pSchemaCache)
{
}

CXMLTreePrivate::~CXMLTreePrivate()
{
}

END_ZEMR_NAMESPACE