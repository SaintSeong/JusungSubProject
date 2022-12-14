// ColourPickerCB.h
//
// Copyright (C)2000 Mark Jackson
//   e-mail: mark@mjsoft.co.uk
// web-site: http://www.mjsoft.co.uk
//
// based on the control by James R. Twine.

#if !defined(AFX_COLOURPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_)
#define AFX_COLOURPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

void DDX_ColourPickerCB( CDataExchange *pDX, int nIDC, COLORREF& prgbColor );

struct Colour
{
	Colour( COLORREF crColour, CString strName )
		: m_crColour( crColour )
		, m_strName( strName )
	{};

	COLORREF m_crColour;
	CString m_strName;
};


class CColourPickerCB : public CComboBox
{
// Construction
public:
	CColourPickerCB();
	virtual	~CColourPickerCB();

// Attributes
private:
	CString m_strColourName;

private:
	void Initialise();

public:
	COLORREF GetSelectedColourValue();

	void AddColour( CString strName, COLORREF crColour );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColourPickerCB)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

	// Generated message map functions
protected:
	//{{AFX_MSG(CColourPickerCB)
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_)
