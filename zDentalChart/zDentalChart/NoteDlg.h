#pragma once
#include <string>


// CNoteDlg dialog

class CNoteDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoteDlg)

public:
	CNoteDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNoteDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
	CString m_strValue;

	CString GetNote();
	void SetNode(CString str);
public:
	virtual BOOL OnInitDialog();
};
