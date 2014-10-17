#include "StdAfx.h"
#include "Canvas.h"


//构造函数
CCanvas::CCanvas(const wstring &strPath, int x, int y, int nWidth, int nHeight)
:Image(strPath.c_str())
{
	m_x = x;
	m_y = y;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_bIsSel = FALSE;
	m_strNote = L"";
	m_bIsFixed = FALSE;
}

//析构函数
CCanvas::~CCanvas(void)
{
}

//设置选中，默认bSel为TRUE
void CCanvas::SetSel(BOOL bSel/* = TRUE*/)
{
	m_bIsSel = bSel;
}

//获取选中状态
BOOL CCanvas::GetIsSel()
{
	return m_bIsSel;
}


//设置图像备注
void CCanvas::SetNote( wstring strNote )
{
	m_strNote = strNote;
}
//获取图像备注
wstring CCanvas::GetNote()
{
	return m_strNote;
}

//设置图像是否固定 不可修改
void CCanvas::SetFixed( BOOL bIsFixed )
{
	m_bIsFixed = bIsFixed;
}

//获取图像是否固定
BOOL CCanvas::GetFixed()
{
	return m_bIsFixed;
}