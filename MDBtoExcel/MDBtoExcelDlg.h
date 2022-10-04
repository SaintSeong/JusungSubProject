
// MDBtoExcelDlg.h: 헤더 파일
//

#pragma once
#include <afxdb.h>
#include <xlsxwriter.h>
#include <vector>

#include "CColumnChangeDlg.h"

// CMDBtoExcelDlg 대화 상자
class CMDBtoExcelDlg : public CDialogEx
{
// 생성입니다.
public:
	CMDBtoExcelDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	virtual ~CMDBtoExcelDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MDBTOEXCEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
private:
	int m_nCheckedCount;

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboTable();
	afx_msg void OnBnClickedButtonChange();

	void GetFieldString();
	const char* ConvertUTF8(CString strConvert);
	int GetCheckCount() const;
	int m_nTotalRecord;

	CString m_strPath;
	CString m_strPW;
	CString m_strCurrentTable;
	CString m_strSelectedField;

	CDatabase m_db;
	CRecordset m_tbRecordSet;

	CComboBox m_ctrlComboTable;

	CCheckListBox m_ctrlCheckList;
	CProgressCtrl m_ctrlProgSave;

	CColumnChangeDlg m_dlgChange;

	std::vector<lxw_worksheet*>m_arrPtSheet;
	lxw_workbook* m_workbook;
	
	
	CEdit m_ctrlEditTotalRows;
	CButton m_ctrlRadioSeperate;
};
