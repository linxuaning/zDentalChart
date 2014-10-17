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

	//������Դ
	void ClearAll();

	void Refresh();

	void Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, int nOrder, BOOL bIsFiexd /* = FALSE*/);
	void Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, BOOL bIsFiexd /* = FALSE*/);

	//��������, nThresholdΪ��ֵ����ʾ���ض�������, ��ֵ��ΧΪ0-100
	void LocationHide(CPoint point, int nMode = 0, int nThreshold = 30);

	//����Ϳɫ, 
	void LocationColoring(CPoint point, int nMode = 0, int nThreshold = 30);

	//���ֱ�ע
	void TextAnnotation(CPoint point, const wstring& strNote);

	//ͼ��ɨ������ϵ�����
	void UpperLeftToLowerRight(CCanvas *canTemp, int mode, int nThreshold);


	//����Ϳɫ�������ɰ�
	void RegionalColour(CPoint point, const wstring &strPath, CRect rect);

	//ѡ��
	CCanvas* Hit(CPoint point, BOOL &bRt);
	BOOL Draw(Graphics* gra);

	
private:
	vector<CCanvas*> m_vecCanvas;
};
