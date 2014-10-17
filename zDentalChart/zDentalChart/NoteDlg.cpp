// NoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "zDentalChart.h"
#include "NoteDlg.h"


// CNoteDlg dialog

IMPLEMENT_DYNAMIC(CNoteDlg, CDialog)

CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoteDlg::IDD, pParent)
	, m_strValue(_T(""))
{

}

CNoteDlg::~CNoteDlg()
{
}

void CNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strValue);
}


BEGIN_MESSAGE_MAP(CNoteDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNoteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNoteDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNoteDlg message handlers

void CNoteDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CNoteDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

CString CNoteDlg::GetNote()
{
	return m_strValue;			 
}

void CNoteDlg::SetNode( CString str )
{
	m_strValue = str;
}

BOOL CNoteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
