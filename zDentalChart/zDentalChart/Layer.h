#pragma once
#include <atltypes.h>
#include "Canvas.h"
#include <vector>
#include "Layer.h"
#include "stdafx.h"
class CLayer
{
public:
	CLayer(void);
	~CLayer(void);

public:
	static CLayer* Create();

	//清理资源
	void ClearAll();

	void Refresh();

	void Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, int nOrder, BOOL bIsFiexd /* = FALSE*/);
	void Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, BOOL bIsFiexd /* = FALSE*/);

	//区域隐藏, nThreshold为阈值，表示隐藏多大的区域, 阈值范围为0-100
	void LocationHide(CPoint point, int nMode = 0, int nThreshold = 30);

	//区域涂色, 
	void LocationColoring(CPoint point, int nMode = 0, int nThreshold = 30);

	//文字标注
	void TextAnnotation(CPoint point, const wstring& strNote);

	//图像扫描从左上到右下
	void UpperLeftToLowerRight(CCanvas *canTemp, int mode, int nThreshold);


	//区域涂色，采用蒙版
	void RegionalColour(CPoint point, const wstring &strPath, CRect rect);

	//选中
	CCanvas* Hit(CPoint point, BOOL &bRt);
	BOOL Draw(Graphics* gra);

	
private:
	vector<CCanvas*> m_vecCanvas;
};
