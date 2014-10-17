#pragma once
#include <atlimage.h>
#include <string>
#include<gdiPlus.h>
#include "def.h"

using namespace Gdiplus;
using namespace std;

class CCanvas : public Image
{
public:
	CCanvas(const wstring &strPath, int x, int y, int nWidth, int nHeight);
	~CCanvas(void);

public:
	
	void SetSel(BOOL bSel = TRUE);
	BOOL GetIsSel();

	void SetNote(wstring strNote);
	wstring GetNote();

	void SetFixed(BOOL IsFixed);
	BOOL GetFixed();

	int GetX(){return m_x;};
	void SetX(int x){m_x = x;};
	int GetY(){return m_y;};
	void SetY(int y){m_y = y;};
	int GetWidth(){return m_nWidth;};
	void SetWidth(int nWidth){m_nWidth = nWidth;};
	int GetHeight(){return m_nHeight;};
	void SetHeight(int nHeight){m_nHeight = nHeight;};

	//---对图像进行操作---//
	

private:
	int m_x;
	int m_y;
	int m_nWidth;
	int m_nHeight;
	BOOL m_bIsSel;
	wstring m_strNote;
	BOOL m_bIsFixed;
	vector<SOper> m_vecOper;
};
