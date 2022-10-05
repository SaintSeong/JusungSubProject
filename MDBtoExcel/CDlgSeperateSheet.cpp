// CDlgSeperateSheet.cpp: 구현 파일
//

#include "pch.h"
#include "MDBtoExcel.h"
#include "afxdialogex.h"
#include "CDlgSeperateSheet.h"


// CDlgSeperateSheet 대화 상자

IMPLEMENT_DYNAMIC(CDlgSeperateSheet, CDialogEx)

CDlgSeperateSheet::CDlgSeperateSheet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Seperate, pParent)
{

}

CDlgSeperateSheet::~CDlgSeperateSheet()
{
}

void CDlgSeperateSheet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSeperateSheet, CDialogEx)
END_MESSAGE_MAP()


// CDlgSeperateSheet 메시지 처리기
