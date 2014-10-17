// zDentalChartDoc.cpp : implementation of the CzDentalChartDoc class
//

#include "stdafx.h"
#include "zDentalChart.h"

#include "zDentalChartDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CzDentalChartDoc

IMPLEMENT_DYNCREATE(CzDentalChartDoc, CDocument)

BEGIN_MESSAGE_MAP(CzDentalChartDoc, CDocument)
END_MESSAGE_MAP()


// CzDentalChartDoc construction/destruction

CzDentalChartDoc::CzDentalChartDoc()
{
	// TODO: add one-time construction code here

}

CzDentalChartDoc::~CzDentalChartDoc()
{
}

BOOL CzDentalChartDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CzDentalChartDoc serialization

void CzDentalChartDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CzDentalChartDoc diagnostics

#ifdef _DEBUG
void CzDentalChartDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CzDentalChartDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CzDentalChartDoc commands
