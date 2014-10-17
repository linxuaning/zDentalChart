#include "StdAfx.h"
#include "Canvas.h"


//���캯��
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

//��������
CCanvas::~CCanvas(void)
{
}

//����ѡ�У�Ĭ��bSelΪTRUE
void CCanvas::SetSel(BOOL bSel/* = TRUE*/)
{
	m_bIsSel = bSel;
}

//��ȡѡ��״̬
BOOL CCanvas::GetIsSel()
{
	return m_bIsSel;
}


//����ͼ��ע
void CCanvas::SetNote( wstring strNote )
{
	m_strNote = strNote;
}
//��ȡͼ��ע
wstring CCanvas::GetNote()
{
	return m_strNote;
}

//����ͼ���Ƿ�̶� �����޸�
void CCanvas::SetFixed( BOOL bIsFixed )
{
	m_bIsFixed = bIsFixed;
}

//��ȡͼ���Ƿ�̶�
BOOL CCanvas::GetFixed()
{
	return m_bIsFixed;
}