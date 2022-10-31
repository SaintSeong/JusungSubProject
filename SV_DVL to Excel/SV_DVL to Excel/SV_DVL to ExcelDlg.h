
// SV_DVL to ExcelDlg.h: 헤더 파일
//

#pragma once
#include <afxdb.h>
#include <vector>
using namespace std;

typedef struct Field
{
	CString m_strOriginName;
	CString m_strChangeName;
}Field;

typedef struct Range
{
	int m_nMin;
	int m_nMax;
}Range;


// CSVDVLtoExcelDlg 대화 상자
class CSVDVLtoExcelDlg : public CDialogEx
{
// 생성입니다.
public:
	CSVDVLtoExcelDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SV_DVL_TO_EXCEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSave();

	CString m_strFilePath;

	CDatabase m_db;
	CRecordset m_tbRecordSet;
	CEdit m_ctrlEditFile;

	CString m_strPW;
	CString m_strTable;

	vector<Field> m_arrField;
	vector<Range> m_arrRange;
	CProgressCtrl m_ctrlProgSave;
};
