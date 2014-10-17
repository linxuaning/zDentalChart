// zDentalChartView.h : interface of the CzDentalChartView class
//


#pragma once
#include "scene.h"
#include "Layer.h"


class CzDentalChartView : public CView
{
protected: // create from serialization only
	CzDentalChartView();
	DECLARE_DYNCREATE(CzDentalChartView)

// Attributes
public:
	CzDentalChartDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


// Implementation
public:
	virtual ~CzDentalChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:
	virtual void OnInitialUpdate();

private:
	void InitScene();
	void RefreshScene();

private:
	CRect m_rectClient;
};

#ifndef _DEBUG  // debug version in zDentalChartView.cpp
inline CzDentalChartDoc* CzDentalChartView::GetDocument() const
   { return reinterpret_cast<CzDentalChartDoc*>(m_pDocument); }
#endif

