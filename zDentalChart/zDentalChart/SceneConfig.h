#pragma once
#include "def.h"

class CSceneConfig
{
private:
	CSceneConfig(void);
	~CSceneConfig(void);
public:
	//�������
	static CSceneConfig* Instance();
	void loadConfig();
	map<size_t, SLayer> GetConfig();
private:
	BOOL m_bInit;
	map<size_t, SLayer>m_mapScene;
};
