#pragma once
#include "afxdialogex.h"


// ColumnChange 대화 상자

class CColumnChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColumnChangeDlg)

public:
	CColumnChangeDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CColumnChangeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE_COLUMN };
#endif

protected:
	HICON m_hIcon;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	
	int m_nISavedItem;
	int m_nISavedSubitem;
	CListCtrl m_ctrlCoulumnList;
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkListColumn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
};
