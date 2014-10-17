#pragma once
#include "Layer.h"

class CScene
{
public:	
	//单件入口
	static CScene* Instance();

	~CScene(void);
	void ClearAll();
	BOOL Draw(CDC *cDC);
	void AddScene( CLayer * Layer, size_t order);
	void AddScene( CLayer * Layer);

	CLayer* GetLayer(size_t num);
private:
	CScene(void);

private:
	vector<CLayer*>m_vecLayer;
};
