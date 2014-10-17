#ifndef XML_TREE_PIRVATE_H
#define XML_TREE_PIRVATE_H

#include <msxml2.h>
#include "../include/zglobal.h"

BEGIN_ZEMR_NAMESPACE

class CXMLSchemaCache;

class CXMLTreePrivate
{
public:
	CXMLTreePrivate(IXMLDOMDocument2* pDom, bool readOnly, CXMLSchemaCache* pSchemaCache);
	CXMLTreePrivate(CXMLTreePrivate& rhs);
	~CXMLTreePrivate();

public:
	bool m_readOnly;

	CComPtr<IXMLDOMDocument2> m_spDom;
	
	CXMLSchemaCache *m_pSchemaCache;
};

END_ZEMR_NAMESPACE

#endif