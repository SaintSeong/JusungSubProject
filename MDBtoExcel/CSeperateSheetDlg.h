#pragma once
#include "afxdialogex.h"
#include "ColourPickerCB.h"
#include <vector>

// CSeperateSheetDlg 대화 상자

class CSeperateSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSeperateSheetDlg)

public:
	CSeperateSheetDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSeperateSheetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SeperateSheet };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetColorCombo(CColourPickerCB *pColourPicker, int idx);
	CListCtrl m_ctrlListSheetModify;
	std::vector<CColourPickerCB*> m_arrColor;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
