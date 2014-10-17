#include "StdAfx.h"
#include "SceneConfig.h"
#include "XMLTree.h"
#include "..\zcore\include\StringUtility.h"

CSceneConfig::CSceneConfig(void)
{
	m_bInit = FALSE;
}

CSceneConfig::~CSceneConfig(void)
{
}

CSceneConfig* CSceneConfig::Instance()
{
	static CSceneConfig pSceneConfig;
	if(pSceneConfig.m_bInit == FALSE)
	{
		pSceneConfig.loadConfig();
		pSceneConfig.m_bInit = TRUE;
	}
	return &pSceneConfig;
}

void CSceneConfig::loadConfig()
{
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);

	USES_CONVERSION;
	wstring strPath = T2W(szPath);
	size_t t_pos = strPath.find_last_of(L"\\", strPath.length());

	wstring strConfigFile = strPath.substr(0, t_pos);
	strConfigFile += L"\\";
	strConfigFile += L"config.xml";

	CXMLTree xml;
	xml.Load(strConfigFile);
	
	int nLayerCount = xml.GetRootNode().GetChildCount();
	for(int i = 0; i < nLayerCount; i++)
	{
		CXMLTreeNode node = xml.GetRootNode()[i];
		wstring strNode = node.GetAttribute(L"note");
		m_mapScene[i].strNote = strNode;

		int nCanvas = node.GetChildCount();
		for(int j = 0; j < nCanvas; j++)
		{
			CXMLTreeNode nodeCanvas = node[j];
			SCanvas can;
			can.x = SU::ToInt(nodeCanvas.GetAttribute(L"x"));
			can.y = SU::ToInt(nodeCanvas.GetAttribute(L"y"));
			can.nHeight = SU::ToInt(nodeCanvas.GetAttribute(L"height"));
			can.nWidth = SU::ToInt(nodeCanvas.GetAttribute(L"width"));
			can.bSel = (nodeCanvas.GetAttribute(L"sel") == L"1") ? TRUE : FALSE;
			can.strNote = nodeCanvas.GetAttribute(L"note");
			can.bFixed = (nodeCanvas.GetAttribute(L"fixed") == L"1") ? TRUE : FALSE;
			can.strImgPath = nodeCanvas.GetAttribute(L"img_path");
			can.nOrder = SU::ToInt(nodeCanvas.GetAttribute(L"order"));

			int nOper = nodeCanvas.GetChildCount();
			for(int k = 0; k < nOper; k++)
			{
				CXMLTreeNode nodeOper = nodeCanvas[j];
				SOper oper;
				oper.nCode = SU::ToInt(nodeOper.GetData());
				oper.mark = SU::ToInt(nodeOper.GetAttribute(L"mark"));
				oper.nThreshold = SU::ToInt(nodeOper.GetAttribute(L"threshold"));
				oper.strImgPath = SU::ToInt(nodeOper.GetAttribute(L"img_path"));
				oper.x = SU::ToInt(nodeOper.GetAttribute(L"x"));
				oper.y = SU::ToInt(nodeOper.GetAttribute(L"y"));
				can.vecOper.push_back(oper);
			}
			m_mapScene[i].vecCanvas.push_back(can);
		}
	}
}

map<size_t, SLayer> CSceneConfig::GetConfig()
{
	return m_mapScene;
}
