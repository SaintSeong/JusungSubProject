// CSeperateSheetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MDBtoExcel.h"
#include "afxdialogex.h"
#include "CSeperateSheetDlg.h"


// CSeperateSheetDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeperateSheetDlg, CDialogEx)

CSeperateSheetDlg::CSeperateSheetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SeperateSheet, pParent)
{

}

CSeperateSheetDlg::~CSeperateSheetDlg()
{
}

void CSeperateSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Sheet, m_ctrlListSheet);
}


BEGIN_MESSAGE_MAP(CSeperateSheetDlg, CDialogEx)
END_MESSAGE_MAP()


// CSeperateSheetDlg 메시지 처리기
