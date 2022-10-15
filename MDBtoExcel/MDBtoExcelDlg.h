// MDBtoExcelDlg.h: 헤더 파일
//

#pragma once
#include <afxdb.h>
#include <xlsxwriter.h>
#include <vector>

#include "CColumnChangeDlg.h"
#include "CSeperateSheetDlg.h"
#include "CColumnName.h"

using namespace std;
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

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void GetFieldString();
	const char* ConvertUTF8(CString strConvert);
	int m_nTotalRecord;
	BOOL m_bListCheckState;
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboTable();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedCheckSeperate();
	afx_msg void OnBnClickedButtonSeperate();
	afx_msg void OnHdnItemclickListColumn(NMHDR* pNMHDR, LRESULT* pResult);

	CString m_strPath;
	CString m_strPW;
	CString m_strCurrentTable;
	CString m_strSelectedField;

	CDatabase m_db;
	CRecordset m_tbRecordSet;

	CColumnChangeDlg m_dlgChange;
	CSeperateSheetDlg m_dlgSeperate;

	vector<CColumnName>m_arrCColumn;
	vector<lxw_worksheet*>m_arrPtSheet;
	lxw_workbook* m_workbook;
	
	CEdit m_ctrlEditTotalRows;
	CEdit m_ctrlEditRows;
	CEdit m_ctrlEditFileName;
	CButton m_ctrlCheckSeperate;
	CComboBox m_ctrlComboTable;
	CProgressCtrl m_ctrlProgSave;
	CListCtrl m_ctrlListColumn;
};
