#include "StdAfx.h"
#include "Scene.h"
#include<gdiPlus.h>
using namespace Gdiplus;
//场景层构造函数
CScene::CScene(void)
{
}

//场景层析构函数
CScene::~CScene(void)
{
	ClearAll();
}

//清空所有
void CScene::ClearAll()
{
	for(vector<CLayer*>::iterator itor = m_vecLayer.begin(); itor != m_vecLayer.end(); itor++)
	{
		(*itor)->ClearAll();
		SAFE_DEL_PTR(*itor);
	}
	static CScene* pScene;
	if(pScene != NULL)
	{
		delete pScene;
	}
}

BOOL CScene::Draw( CDC *cDC)
{
	Graphics graphics(cDC->m_hDC);

	//双缓冲
	Image img(L"ya.jpg");
	Graphics cache(&img);

	vector<CLayer*>::iterator itor = m_vecLayer.begin();
	for(; itor != m_vecLayer.end(); itor++)
	{
		(*itor)->Draw(&cache);
	}
	
	graphics.DrawImage(&img, 0, 0, 800, 400);

	
	return TRUE;
}

//添加层
void CScene::AddScene( CLayer * Layer )
{
	m_vecLayer.push_back(Layer);
}

//添加顺序层
void CScene::AddScene( CLayer * Layer, size_t order )
{
	if(order >= m_vecLayer.size())
	{
		AddScene(Layer);
		return;
	}

	size_t count = 0;
	for(vector<CLayer*>::iterator itor = m_vecLayer.begin(); itor != m_vecLayer.end(); itor++)
	{
		if(count == order)
		{
			m_vecLayer.insert(itor, Layer);
			return;
		}
		count++;
	}

	return;
}

//层单件
CScene* CScene::Instance()
{
	static CScene* pScene;
	if(pScene == NULL)
	{
		pScene = new CScene();
		return pScene;
	}
	return pScene;
}

//获取某一层
CLayer* CScene::GetLayer( size_t num )
{
	return m_vecLayer.at(num);
}
