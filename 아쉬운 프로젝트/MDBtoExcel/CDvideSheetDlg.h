#pragma once
#include "afxdialogex.h"
#include "CSheet.h"
#include <vector>
using namespace std;

// CDvideSheetDlg 대화 상자

class CDvideSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDvideSheetDlg)

public:
	CDvideSheetDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDvideSheetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIVIDE_SHEET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnNMClickListSheet(NMHDR* pNMHDR, LRESULT* pResult);
	
	CListCtrl m_ctrlListSheet;
	CString m_strStandardField;
	
	int m_nISavedItem;
	int m_nISavedSubitem;
	int m_nSheetCount;
	vector<CSheet> m_arrSheet;
	CEdit m_ctrlEditSheet;
};
