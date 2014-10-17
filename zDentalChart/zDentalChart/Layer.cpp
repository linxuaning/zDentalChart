#include "StdAfx.h"
#include "Layer.h"

//构造函数
CLayer::CLayer(void)
{
}

//析构函数
CLayer::~CLayer(void)
{
	ClearAll();

}


//绘制层中的图像到cDC
BOOL CLayer::Draw(Graphics* gra)
{
	vector<CCanvas*>::iterator itor = m_vecCanvas.begin();
	for(; itor != m_vecCanvas.end(); itor++)
	{
		gra->DrawImage((*itor), (*itor)->GetX(), (*itor)->GetY(), (*itor)->GetWidth(), (*itor)->GetHeight());
	}
	return TRUE;
}

//清空层中图像
void CLayer::ClearAll()
{

	vector<CCanvas*>::iterator itor = m_vecCanvas.begin();
	for(; itor != m_vecCanvas.end(); itor++)
	{
		SAFE_DEL_PTR(*itor);
	}
	m_vecCanvas.clear();
}

//区域隐藏, nThreshold为阈值，表示隐藏多大的区域, 阈值范围为0-100
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
	//	//从左到右，从上到下
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

//区域涂色
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
	//	//从左到右，从上到下
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

//文字标注
void CLayer::TextAnnotation(CPoint point, const wstring& strNote)
{
	//CCanvas* canTemp = NULL;
	//BOOL bRet;
	//canTemp = Hit(point, bRet);

	//if(bRet == FALSE)
	//	return;

	//canTemp->SetNote(strNote);
}

//图像扫描从左上到右下，mode = 0表示隐藏，mode = 1表示涂灰色128.128.128
void CLayer::UpperLeftToLowerRight( CCanvas *canTemp, int mode, int nThreshold)
{
	////图像采用左上到右下遮盖的方法, 需要注意的是图片长宽不一定相等，阈值判定加上斜对角
	//////row代表有几列，col代表有几行
	//////宽大于长
	//int row = canTemp->GetWidth();
	//int col = canTemp->GetHeight();
	//int nThresholdCount = row * col * nThreshold / 100;
	//int nCount = 0;
	//int t, x, y;
	//if(row > col)
	//{
	//	t = col;//斜排数量 
	//	for(int j = 0; j < t; j++)//循环处理每一个斜排 
	//	{
	//		y = j;//每个斜排第一个单元的纵坐标 
	//		x = 0;//每个斜排第一个单元的横坐标 
	//		for(int i = 0; i <= j; i++, x++, y--)//i控制每个斜排内部单元的个数 
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
	////长大于宽
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
	////长等于宽
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

//区域涂色，采用蒙版
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

//创建层
CLayer* CLayer::Create()
{
	CLayer* pLayer = new CLayer();
	return pLayer;
}

//添加层中的图像，bIsFiexd为TURE则图像不可修改大小
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

//添加层中的图像，bIsFiexd为TURE则图像不可修改大小
void CLayer::Add(const wstring &strImgPath, int x, int y, int nWidth, int nHeight, BOOL bIsFiexd /* = FALSE*/)
{
	CCanvas* can = new CCanvas(strImgPath, x, y, nWidth, nHeight);
	if(bIsFiexd)
	{
		can->SetFixed(TRUE);
	}
	m_vecCanvas.push_back(can);
}

//图像击中，则bRt为TRUE，返回图像
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
