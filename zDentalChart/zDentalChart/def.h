#pragma once
typedef struct structOper
{
	int nCode;
	wstring mark;
	int nThreshold;
	wstring strImgPath;
	int x;
	int y;
}SOper;

typedef struct structCanvas
{
	int x;
	int y;
	int nWidth;
	int nHeight;
	BOOL bSel;
	wstring strNote;
	BOOL bFixed;
	wstring strImgPath;
	int nOrder;
	vector<SOper>vecOper;
}SCanvas;


typedef struct structLayer
{
	wstring strNote;
	vector<SCanvas>vecCanvas;
}SLayer;