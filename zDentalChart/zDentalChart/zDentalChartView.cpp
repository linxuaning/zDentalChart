// zDentalChartView.cpp : implementation of the CzDentalChartView class
//

#include "stdafx.h"
#include "zDentalChart.h"

#include "zDentalChartDoc.h"
#include "zDentalChartView.h"
#include "MainFrm.h"
#include "NoteDlg.h"
#include "SceneConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CzDentalChartView

IMPLEMENT_DYNCREATE(CzDentalChartView, CView)

BEGIN_MESSAGE_MAP(CzDentalChartView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CzDentalChartView construction/destruction

CzDentalChartView::CzDentalChartView()
{
	// TODO: add construction code here
}

CzDentalChartView::~CzDentalChartView()
{
	CScene::Instance()->ClearAll();
}

BOOL CzDentalChartView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	InitScene();
	return CView::PreCreateWindow(cs);
}

// CzDentalChartView drawing

void CzDentalChartView::OnDraw(CDC* /*pDC*/)
{
	CzDentalChartDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CzDentalChartView printing

BOOL CzDentalChartView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CzDentalChartView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CzDentalChartView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


#ifdef _DEBUG
void CzDentalChartView::AssertValid() const
{
	CView::AssertValid();
}

void CzDentalChartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CzDentalChartDoc* CzDentalChartView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CzDentalChartDoc)));
	return (CzDentalChartDoc*)m_pDocument;
}
#endif //_DEBUG



void CzDentalChartView::OnTimer(UINT_PTR nIDEvent)
{
	//switch(nIDEvent)  
 //   {
 //   case TIMER_PAINT:OnPaint();//�����ػ涨ʱ������ִ��OnPaint����  
	//	break;  
 //   }

	CView::OnTimer(nIDEvent);    

}

void CzDentalChartView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);

	//int xPosBox = point.x/100;
	//int yPosBox = point.y/100;

	//CCanvas* canTemp = NULL;
	//BOOL bRet;
	//canTemp = CScene::Instance()->GetLayer(0)->Hit(point, bRet);

	//if(bRet == FALSE || canTemp->GetFixed())
	//{
	//	RefreshScene();
	//	CzDentalChartView::OnPaint();
	//	return;
	//}

	//CRect temp = canTemp->GetImgRect();

	//if(!canTemp->GetIsSel())
	//{
	//	canTemp->SetImgRect(temp.left - 15, temp.right + 15, temp.top - 15, temp.bottom + 15);
	//	canTemp->SetSel();
	//}
	//else
	//{
	//	canTemp->SetImgRect(temp.left + 15, temp.right - 15, temp.top + 15, temp.bottom - 15);
	//	canTemp->SetSel(FALSE);
	//}
	CzDentalChartView::OnPaint();
}

void CzDentalChartView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

void CzDentalChartView::OnClose()
{
	CView::OnClose();
}

void CzDentalChartView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	
	CDC *cDC=this->GetDC();   //��õ�ǰ���ڵ�DC

	GetClientRect(&m_rectClient);   //��ô��ڵĳߴ�

	CScene::Instance()->Draw(cDC);

	ReleaseDC(cDC);           //�ͷ�DC
}

void CzDentalChartView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	BOOL bRet = FALSE;
	CCanvas * temp = CScene::Instance()->GetLayer(0)->Hit(point, bRet);
	if(bRet == FALSE || temp->GetNote() == L"")
	{

		CString str;  
		str.Format(L"��ǰ�������: ( %d, %d )", point.x, point.y);  
		((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);  
		CView::OnMouseMove(nFlags, point);
	}
	else
	{
		CString str = temp->GetNote().c_str();  
		((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);  
		CView::OnMouseMove(nFlags, point);
	}
}

void CzDentalChartView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch(nChar)  
    {  
    case 'd':        
    case 'D':
		RefreshScene();
        break;
    }  
	CzDentalChartView::OnPaint();
}

void CzDentalChartView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);
	
		//�����Ҽ��˵�
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, 1, L"�������أ������ϵ����£� ��ֵΪ30%");
	menu.AppendMenu(MF_STRING, 2, L"�������أ������ϵ����£� ��ֵΪ70%");
	menu.AppendMenu(MF_STRING, 3, L"�������أ����ϵ��£� ��ֵΪ30%");
	menu.AppendMenu(MF_STRING, 4, L"�������أ����ϵ��£� ��ֵΪ70%");
	menu.AppendMenu(MF_STRING, 5, L"����Ϳɫ�������ϵ����£���ɫΪ��ɫ, ��ֵΪ30%");
	menu.AppendMenu(MF_STRING, 6, L"����Ϳɫ�������ϵ����£���ɫΪ��ɫ, ��ֵΪ70%");
	menu.AppendMenu(MF_STRING, 7, L"����Ϳɫ�����ϵ��£���ɫΪ��ɫ, ��ֵΪ30%");
	menu.AppendMenu(MF_STRING, 8, L"����Ϳɫ�����ϵ��£���ɫΪ��ɫ, ��ֵΪ70%");
	menu.AppendMenu(MF_STRING, 9, L"���ֱ�ע����ע����ʾ�����½�");
	menu.AppendMenu(MF_STRING, 10, L"����Ϳɫ, ��ĳ��ͼ��ӳ�䵽�ײ�ͼ��");
	menu.AppendMenu(MF_STRING, 11, L"�����滻");
	menu.AppendMenu(MF_STRING, 12, L"�����Ѻ�(���������滻)");
	//menu.AppendMenu(MF_STRING, 13, L"������θ���PlgBlt");

	CPoint pt(point);
	ClientToScreen(&pt);
	long nSelection = 0;
	nSelection = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL | TPM_NONOTIFY | TPM_RETURNCMD, pt.x, pt.y, this);


	switch(nSelection)
	{
	case 1 :
		CScene::Instance()->GetLayer(0)->LocationHide(point);
		break;
	case 2:
		CScene::Instance()->GetLayer(0)->LocationHide(point, 0, 70);
		break;
	case 3 :
		CScene::Instance()->GetLayer(0)->LocationHide(point, 1);
		break;
	case 4:
		CScene::Instance()->GetLayer(0)->LocationHide(point, 1, 70);
		break;
	case 5 :
		CScene::Instance()->GetLayer(0)->LocationColoring(point);
		break;
	case 6:
		CScene::Instance()->GetLayer(0)->LocationColoring(point, 0, 70);
		break;
	case 7 :
		CScene::Instance()->GetLayer(0)->LocationColoring(point, 1);
		break;
	case 8:
		CScene::Instance()->GetLayer(0)->LocationColoring(point, 1, 70);
		break;
	case 9:
		{
			BOOL bRet = FALSE;
			CCanvas * temp = CScene::Instance()->GetLayer(0)->Hit(point, bRet);
			if(bRet == FALSE)
				break;

			CNoteDlg dlg;
			dlg.SetNode(temp->GetNote().c_str());
			if(dlg.DoModal() == IDOK)
			{
				CScene::Instance()->GetLayer(0)->TextAnnotation(point, dlg.GetNote().GetString());
			}
		}
		break;
	//case 10:
	//	{
	//		BOOL bRet = FALSE;
	//		CScene::Instance()->GetLayer(0)->Hit(point, bRet);
	//		if(bRet == FALSE)
	//			break;
	//		CRect rect;
	//		rect.left = 4 *100 + 40;
	//		rect.right= rect.left + 30;
	//		rect.top = 3 * 100;
	//		rect.bottom = rect.top + 34;
	//		CScene::Instance()->GetLayer(0)->RegionalColour(point, L"luomu.png", rect);
	//	}
	//	break;
	//case 11:
	//	{
	//		CRect rect;
	//		rect.left = 4 *100 + 40;
	//		rect.right= rect.left + 30;
	//		rect.top = 3 * 100;
	//		rect.bottom = rect.top + 34;
	//		CScene::Instance()->GetLayer(1)->Add(L"luomu.png", rect, TRUE);
	//	}
	//	break;
	//case 12:
	//	{
	//		CRect rect;
	//		rect.left = 4 *100 + 40;
	//		rect.right= rect.left + 190;
	//		rect.top = 3 * 100;
	//		rect.bottom = rect.top + 60;
	//		CScene::Instance()->GetLayer(1)->Add(L"liehen.png", rect, TRUE);
	//	}
	//	break;
	case 13:
		break;
	default:
		break;
	}
	CzDentalChartView::OnPaint();
}

void CzDentalChartView::InitScene()
{
	RefreshScene();
}

void CzDentalChartView::RefreshScene()
{
	CScene::Instance()->ClearAll();

	map<size_t, SLayer>mapScene = CSceneConfig::Instance()->GetConfig();
	if(mapScene.size() == size_t(0))
		return;

	for(size_t i = 0; i < mapScene.size(); i++)
	{
		CLayer* Layer = CLayer::Create();
		CScene::Instance()->AddScene(Layer, i);
		for(size_t j = 0; j < mapScene[i].vecCanvas.size(); j++)
		{
			int x = mapScene[i].vecCanvas.at(j).x;
			int y= mapScene[i].vecCanvas.at(j).y;
			int nWidth =  mapScene[i].vecCanvas.at(j).nWidth;
			int nHeight =  mapScene[i].vecCanvas.at(j).nHeight;
			wstring strPath = mapScene[i].vecCanvas.at(j).strImgPath;
			BOOL bFixed = mapScene[i].vecCanvas.at(j).bFixed;
			int nOrder = mapScene[i].vecCanvas.at(j).nOrder;
			if(strPath != L"")
			{
				CScene::Instance()->GetLayer(0)->Add(strPath, x, y, nWidth, nHeight, bFixed, nOrder);
			}
		}
	}
}