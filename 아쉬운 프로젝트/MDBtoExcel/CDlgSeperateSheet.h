#pragma once
#include "afxdialogex.h"


// CDlgSeperateSheet 대화 상자

class CDlgSeperateSheet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSeperateSheet)

public:
	CDlgSeperateSheet(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgSeperateSheet();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Seperate };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
