#include "StdAfx.h"
#include "Layer.h"

//���캯��
CLayer::CLayer(void)
{
}

//��������
CLayer::~CLayer(void)
{
	ClearAll();

}


//���Ʋ��е�ͼ��cDC
BOOL CLayer::Draw(Graphics* gra)
{
	vector<CCanvas*>::iterator itor = m_vecCanvas.begin();
	for(; itor != m_vecCanvas.end(); itor++)
	{
		gra->DrawImage((*itor), (*itor)->GetX(), (*itor)->GetY(), (*itor)->GetWidth(), (*itor)->GetHeight());
	}
	return TRUE;
}

//��ղ���ͼ��
void CLayer::ClearAll()
{

	vector<CCanvas*>::iterator itor = m_vecCanvas.begin();
	for(; itor != m_vecCanvas.end(); itor++)
	{
		SAFE_DEL_PTR(*itor);
	}
	m_vecCanvas.clear();
}

//��������, nThresholdΪ��ֵ����ʾ���ض�������, ��ֵ��ΧΪ0-100
void CLayer::LocationHide( CPoint point, int nMode /*= 0*/, int nThreshold/* = 30*/)
{
	//if(nThreshold < 0)nThreshold = 0;
	//if(nThreshold > 100)nThreshold = 100;

	//CCanvas* canTemp = NULL;
	//BOOL bRet;
	//canTemp = Hit(point, bRet);

	//if(bRet == FALSE)
	//	return;

	//if(nMode == 0)
	//{

	//	UpperLeftToLowerRight(canTemp, 0, nThreshold);
	//}
	//else 
	//{		
	//	int nThresholdCount = canTemp->GetWidth() * canTemp->GetHeight() * nThreshold / 100;
	//	int nCount = 0;
	//	//�����ң����ϵ���
	//	for(int i = 0; i < canTemp->GetWidth(); i++)
	//		for(int j = 0; j < canTemp->GetHeight() * nThreshold / 100; j++)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(i , j));
	//			pucColor[3] = 0;
	//			nCount++;
	//		}
	//}


}

//����Ϳɫ
void CLayer::LocationColoring(CPoint point, int nMode/* = 0*/, int nThreshold /*= 30*/)
{
	//if(nThreshold < 0)nThreshold = 0;
	//if(nThreshold > 100)nThreshold = 100;

	//CCanvas* canTemp = NULL;
	//BOOL bRet;
	//canTemp = Hit(point, bRet);

	//if(bRet == FALSE)
	//	return;


	//if(nMode == 0)
	//{

	//	UpperLeftToLowerRight(canTemp, 1, nThreshold);
	//}
	//else 
	//{		
	//	int nThresholdCount = canTemp->GetWidth() * canTemp->GetHeight() * nThreshold / 100;
	//	int nCount = 0;
	//	//�����ң����ϵ���
	//	for(int i = 0; i < canTemp->GetWidth(); i++)
	//		for(int j = 0; j < canTemp->GetHeight() * nThreshold / 100; j++)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(i , j));
	//			if(pucColor[3] == 0)continue;
	//			pucColor[0] = 0;
	//			pucColor[1] = 255;
	//			pucColor[2] = 0;
	//			nCount++;
	//		}
	//}


}

//���ֱ�ע
void CLayer::TextAnnotation(CPoint point, const wstring& strNote)
{
	//CCanvas* canTemp = NULL;
	//BOOL bRet;
	//canTemp = Hit(point, bRet);

	//if(bRet == FALSE)
	//	return;

	//canTemp->SetNote(strNote);
}

//ͼ��ɨ������ϵ����£�mode = 0��ʾ���أ�mode = 1��ʾͿ��ɫ128.128.128
void CLayer::UpperLeftToLowerRight( CCanvas *canTemp, int mode, int nThreshold)
{
	////ͼ��������ϵ������ڸǵķ���, ��Ҫע�����ͼƬ����һ����ȣ���ֵ�ж�����б�Խ�
	//////row�����м��У�col�����м���
	//////����ڳ�
	//int row = canTemp->GetWidth();
	//int col = canTemp->GetHeight();
	//int nThresholdCount = row * col * nThreshold / 100;
	//int nCount = 0;
	//int t, x, y;
	//if(row > col)
	//{
	//	t = col;//б������ 
	//	for(int j = 0; j < t; j++)//ѭ������ÿһ��б�� 
	//	{
	//		y = j;//ÿ��б�ŵ�һ����Ԫ�������� 
	//		x = 0;//ÿ��б�ŵ�һ����Ԫ�ĺ����� 
	//		for(int i = 0; i <= j; i++, x++, y--)//i����ÿ��б���ڲ���Ԫ�ĸ��� 
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}

	//	t = row - col;
	//	for(int j = 1; j <= t; j++)
	//	{
	//		y = col-1;
	//		x = j;
	//		for(int i = 1;i <= col;i ++,x ++,y --)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}

	//	if(nThreshold <= 50 )
	//	{
	//		t = col - 1;
	//		for(int j = t;j > 0;j --)
	//		{
	//			y = col - 1;
	//			x = row - j;
	//			for(int i = 0;i < j; i++, x++, y--)
	//			{
	//				if(nCount > nThresholdCount)break;
	//				nCount++;
	//				unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//				if(mode == 0)
	//				{
	//					pucColor[3] = 0;
	//				}
	//				else if(mode == 1)
	//				{
	//					if(pucColor[3] == 0)continue;
	//					pucColor[0] = 128;
	//					pucColor[1] = 128;
	//					pucColor[2] = 128;
	//				}
	//			}
	//		}
	//	}
	//}
	////�����ڿ�
	//else if(row < col)
	//{
	//	t = row;
	//	for(int i = 1;i <= t; i++)
	//	{
	//		x = 0;
	//		y = i - 1;
	//		for(int j = 1;j <= i; j++, x++, y--)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}

	//	t = col - row;
	//	for(int i = 1; i <= t; i++)
	//	{
	//		x = 0;
	//		y = row + i - 1;
	//		for(int j = 1; j <= row; j++,x++,y--)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}

	//	t = row - 1;
	//	for(int i = t; i > 0; i--)
	//	{
	//		x = row-i;
	//		y = col-1;
	//		for(int j = 1; j <= i; j++, x++, y--)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}
	//}
	////�����ڿ�
	//else
	//{
	//	t = row;
	//	for(int i = 1; i <= t; i++)
	//	{
	//		x = 0;
	//		y = i - 1;
	//		for(int j = 1; j <= i; j++, x++, y--)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}

	//	t = row - 1;
	//	for(int i = t; i > 0; i--)
	//	{
	//		x = row - i;
	//		y = col - 1;
	//		for(int j = 1; j <= i; j++, x++, y--)
	//		{
	//			if(nCount > nThresholdCount)break;
	//			nCount++;
	//			unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(x , y));
	//			if(mode == 0)
	//			{
	//				pucColor[3] = 0;
	//			}
	//			else if(mode == 1)
	//			{
	//				if(pucColor[3] == 0)continue;
	//				pucColor[0] = 128;
	//				pucColor[1] = 128;
	//				pucColor[2] = 128;
	//			}
	//		}
	//	}
	//}
}

//����Ϳɫ�������ɰ�
void CLayer::RegionalColour( CPoint point, const wstring &strPath, CRect rect)
{
	//CCanvas* canTemp = new CCanvas;
	//canTemp->loadImg(strPath, rect);

	//BOOL bRet = FALSE;
	//CCanvas* canTarget = this->Hit(point, bRet);
	//if(bRet == FALSE)
	//	return;

	//CRect tempRect = canTemp->GetImgRect();
	//int nTopX = tempRect.TopLeft().x;
	//int nTopY = tempRect.TopLeft().y;

	//for(int i = 0; i < canTemp->GetWidth(); i++)
	//	for(int j = 0; j < canTemp->GetHeight(); j++)
	//	{
	//		unsigned char* pucColor = reinterpret_cast<unsigned char *>(canTemp->GetPixelAddress(i, j));
	//		if(pucColor[3] != 0)
	//		{
	//			if(
	//				(i < canTarget->GetWidth()) &&
	//				(j < canTarget->GetHeight()) &&
	//				((i * j % 2) == 0)
	//				)
	//			{
	//				unsigned char* pucTargetColor = reinterpret_cast<unsigned char *>(canTarget->GetPixelAddress(i, j));
	//				pucTargetColor[0] = 128;
	//				pucTargetColor[1] = 128;
	//				pucTargetColor[2] = 128;
	//			}
	//		}
	//	}
	//	canTemp->clear();
	//	delete canTemp;
}

//������
CLayer* CLayer::Create()
{
	CLayer* pLayer = new CLayer();
	return pLayer;
}

//��Ӳ��е�ͼ��bIsFiexdΪTURE��ͼ�񲻿��޸Ĵ�С
void CLayer::Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, BOOL bIsFiexd /* = FALSE*/, int nOrder)
{
	
	if(size_t(nOrder) >= m_vecCanvas.size())
	{
		this->Add(strImgPath, x, y, nWidth, nHeight, bIsFiexd);
		return;
	}

	CCanvas* can = new CCanvas(strImgPath, x, y, nWidth, nHeight);
	if(bIsFiexd)
	{
		can->SetFixed(TRUE);
	}
	vector<CCanvas*>::iterator itor = m_vecCanvas.begin() + nOrder;

	m_vecCanvas.insert(itor, can);
}

//��Ӳ��е�ͼ��bIsFiexdΪTURE��ͼ�񲻿��޸Ĵ�С
void CLayer::Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, BOOL bIsFiexd /* = FALSE*/)
{
	CCanvas* can = new CCanvas(strImgPath, x, y, nWidth, nHeight);
	if(bIsFiexd)
	{
		can->SetFixed(TRUE);
	}
	m_vecCanvas.push_back(can);
}

//ͼ����У���bRtΪTRUE������ͼ��
CCanvas * CLayer::Hit( CPoint point, BOOL &bRt)
{
	//bRt = FALSE;
	//vector<CCanvas*>::reverse_iterator itor = m_vecCanvas.rbegin();
	//for(; itor != m_vecCanvas.rend(); itor++)
	//{
	//	if((*itor)->IsHit(point))
	//	{
	//		bRt = TRUE;
	//		return *itor;
	//	}
	//}
	return NULL;
}
