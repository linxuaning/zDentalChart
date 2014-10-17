#ifndef XMLTREENODEPRIVATE_H
#define XMLTREENODEPRIVATE_H

#include <msxml2.h>
#include <atlcomcli.h>
#include "../include/zglobal.h"

BEGIN_ZEMR_NAMESPACE

class CXMLTree;

class ZCORE_API CXMLTreeNodePrivate
{
public:
	CXMLTreeNodePrivate(CXMLTree* pXT, IXMLDOMNode* pNode);
	CXMLTreeNodePrivate(const CXMLTreeNodePrivate& node);
	~CXMLTreeNodePrivate();

public:
	CXMLTreeNodePrivate& operator=(const CXMLTreeNodePrivate& rhs);

public:
	bool IsValid();
	void ValidateNode();

public:
	CXMLTree* m_pXT;						// 仅引用,不要删除该对象
	CComPtr<IXMLDOMNode> m_spNode;

	wstring m_errorInfo;					// 错误信息
};

END_ZEMR_NAMESPACE

#endif