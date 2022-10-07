// ColourPickerCB.cpp
//
// Copyright (C)2000 Mark Jackson
//   e-mail: mark@mjsoft.co.uk
// web-site: http://www.mjsoft.co.uk
//
// based on the control by James R. Twine.

#include "pch.h"
#include "ColourPickerCB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Colour g_arrColours[] =
{
	Colour( RGB( 000, 000, 000 ), _T("Black")),
	Colour( RGB( 255, 255, 255 ), _T("White")),
	Colour( RGB( 127, 127, 127 ), _T("Grey")),
	Colour( RGB( 255, 000, 000 ), _T("Red")),
	Colour( RGB( 255, 127, 000 ), _T("Orange")),
	Colour( RGB( 255, 255, 000 ), _T("Yellow")),
	Colour( RGB( 000, 255, 000 ), _T("Green")),
	Colour( RGB( 000, 255, 255 ), _T("Cyan")),
	Colour( RGB( 000, 000, 255 ), _T("Blue")),
	Colour( RGB( 255, 000, 255 ), _T("Fuchsia"))
};

CColourPickerCB::CColourPickerCB()
{
}

CColourPickerCB::~CColourPickerCB()
{
}

void DDX_ColourPickerCB( CDataExchange *pDX, int nIDC, COLORREF& rgbColor )
{
	HWND hWndCtrl = pDX->PrepareCtrl( nIDC );
	ASSERT( hWndCtrl );

	CColourPickerCB *pPicker = (CColourPickerCB*)CWnd::FromHandle( hWndCtrl );
	ASSERT( pPicker );

	// only support getting of colour.
	if( pDX->m_bSaveAndValidate )
	{
		rgbColor = pPicker->GetSelectedColourValue();
	}
}


BEGIN_MESSAGE_MAP(CColourPickerCB, CComboBox)
	//{{AFX_MSG_MAP(CColourPickerCB)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColourPickerCB message handlers

void CColourPickerCB::PreSubclassWindow() 
{
	CComboBox::PreSubclassWindow();

	Initialise();
}

void CColourPickerCB::Initialise()
{
	// add colours.
	int iNumColours = sizeof( g_arrColours ) / sizeof( g_arrColours[0] );

	for( int iNum = 0; iNum < iNumColours; iNum++ )
	{
		Colour& colour = g_arrColours[iNum];
		AddColour( colour.m_strName, colour.m_crColour );
	}

	// add a custom item on the end.
	//AddColour( _T("Custom..."), RGB( 255, 255, 255 ) );

	SetCurSel( 0 );
}

void CColourPickerCB::DrawItem( LPDRAWITEMSTRUCT pDIStruct )
{
	CString strColour;
	CDC dcContext;
	CRect rItemRect( pDIStruct->rcItem );
	CRect rBlockRect( rItemRect );
	CRect rTextRect( rBlockRect );
	CBrush brFrameBrush;
	int iFourthWidth = 0;
	int iItem = pDIStruct->itemID;
	int iAction = pDIStruct->itemAction;
	int iState = pDIStruct->itemState;
	COLORREF crColour = NULL;
	COLORREF crNormal = GetSysColor( COLOR_WINDOW );
	COLORREF crSelected = GetSysColor( COLOR_HIGHLIGHT );
	COLORREF crText = GetSysColor( COLOR_WINDOWTEXT );

	if( !dcContext.Attach( pDIStruct->hDC ) )
	{
		return;
	}

	iFourthWidth = ( rBlockRect.Width() / 4 );
	brFrameBrush.CreateStockObject( BLACK_BRUSH );

	if( iState & ODS_SELECTED )
	{
		dcContext.SetTextColor(	( 0x00FFFFFF & ~( crText ) ) );
		dcContext.SetBkColor( crSelected );
		dcContext.FillSolidRect( &rBlockRect, crSelected );
	}
	else
	{
		dcContext.SetTextColor( crText );
		dcContext.SetBkColor( crNormal );
		dcContext.FillSolidRect( &rBlockRect, crNormal );
	}

	if( iState & ODS_FOCUS )
	{
		dcContext.DrawFocusRect( &rItemRect );
	}

	// calculate text area.
	rTextRect.left += ( iFourthWidth + 2 );
	rTextRect.top += 2;

	// calculate colour block area.
	rBlockRect.DeflateRect( CSize( 2, 2 ) );
	rBlockRect.right = iFourthWidth;

	// draw colour text and block.
	if( iItem != -1 )
	{
		GetLBText( iItem, strColour );

		if( iState & ODS_DISABLED )
		{
			crColour = GetSysColor( COLOR_INACTIVECAPTIONTEXT );
			dcContext.SetTextColor( crColour );
		}
		else
		{
			crColour = GetItemData( iItem );
		}

		dcContext.SetBkMode( TRANSPARENT );
		dcContext.TextOut( rTextRect.left, rTextRect.top,	strColour );

		dcContext.FillSolidRect( &rBlockRect, crColour );
				
		dcContext.FrameRect( &rBlockRect, &brFrameBrush );
	}

	dcContext.Detach();
}

COLORREF CColourPickerCB::GetSelectedColourValue()
{
	return GetItemData( GetCurSel() );
}

void CColourPickerCB::AddColour( CString strName, COLORREF crColour )
{
	int iIndex = AddString( strName );

	if( iIndex >= 0 )
	{
		SetItemData( iIndex, crColour );
	}
}

void CColourPickerCB::OnSelchange() 
{
	// the last item is "Custom...".
	CString strText;
	GetLBText( GetCurSel(), strText );

	if( strText == "Custom..." )
	{
		CColorDialog dlg;

		if( dlg.DoModal() == IDOK )
		{
			SetItemData( GetCurSel(), dlg.GetColor() );
		}
	}
}
