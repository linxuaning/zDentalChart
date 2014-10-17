// zDentalChartDoc.h : interface of the CzDentalChartDoc class
//


#pragma once


class CzDentalChartDoc : public CDocument
{
protected: // create from serialization only
	CzDentalChartDoc();
	DECLARE_DYNCREATE(CzDentalChartDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CzDentalChartDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


