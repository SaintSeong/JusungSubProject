
// MDBtoExcelDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MDBtoExcel.h"
#include "MDBtoExcelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_IDX 6

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMDBtoExcelDlg 대화 상자

CMDBtoExcelDlg::CMDBtoExcelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MDBTOEXCEL_DIALOG, pParent)
	, m_strPath(_T(""))
	, m_strPW(_T("B1594C47"))
	, m_tbRecordSet(&m_db)
	, m_strCurrentTable(_T(""))
	, m_strSelectedField(_T(""))
	, m_workbook{0}
	, m_nTotalRecord(0)
	, m_bListCheckState(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_JUSUNG);
}

CMDBtoExcelDlg::~CMDBtoExcelDlg()
{
}

void CMDBtoExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
	DDX_Control(pDX, IDC_COMBO_TABLE, m_ctrlComboTable);
	DDX_Control(pDX, IDC_PROGRESS_SAVE, m_ctrlProgSave);
	DDX_Control(pDX, IDC_EDIT_TotalRows, m_ctrlEditTotalRows);
	DDX_Control(pDX, IDC_CHECK_Seperate, m_ctrlCheckSeperate);
	DDX_Control(pDX, IDC_EDIT_Rows, m_ctrlEditRows);
	DDX_Control(pDX, IDC_EDIT_FILE, m_ctrlEditFileName);
	DDX_Control(pDX, IDC_LIST_COLUMN, m_ctrlListColumn);
}

BEGIN_MESSAGE_MAP(CMDBtoExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMDBtoExcelDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CMDBtoExcelDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMDBtoExcelDlg::OnBnClickedButtonSave)
	ON_CBN_SELCHANGE(IDC_COMBO_TABLE, &CMDBtoExcelDlg::OnCbnSelchangeComboTable)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CMDBtoExcelDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_CHECK_Seperate, &CMDBtoExcelDlg::OnBnClickedCheckSeperate)
	ON_BN_CLICKED(IDC_BUTTON_Seperate, &CMDBtoExcelDlg::OnBnClickedButtonSeperate)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CMDBtoExcelDlg::OnHdnItemclickListColumn)
END_MESSAGE_MAP()


// CMDBtoExcelDlg 메시지 처리기

BOOL CMDBtoExcelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	m_ctrlProgSave.SetRange(1, 100);
	m_ctrlEditRows.SetCueBanner(_T("Input Rows"));

	m_ctrlListColumn.SetExtendedStyle(m_ctrlListColumn.GetExtendedStyle()
		| LVS_EX_GRIDLINES 
		| LVS_EX_CHECKBOXES);

	CRect rect;
	m_ctrlListColumn.GetWindowRect(&rect);
	ScreenToClient(rect);
	m_ctrlListColumn.InsertColumn(0, _T("Column"), 0, rect.Width() / 2 + 70);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMDBtoExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMDBtoExcelDlg::OnPaint()
{
	CPaintDC ViewDC(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(ViewDC.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		ViewDC.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		CDC MemDC;
		MemDC.CreateCompatibleDC(&ViewDC);

		CBitmap bmp;
		CBitmap* pOldBmp = NULL;
		bmp.LoadBitmap(IDB_BITMAP_LOGO);
		pOldBmp = MemDC.SelectObject(&bmp);

		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		ViewDC.TransparentBlt(0, 0, 380, 130,
			&MemDC,
			0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight,
			RGB(255,255,255));
		MemDC.SelectObject(pOldBmp);
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMDBtoExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// MDB 열기
void CMDBtoExcelDlg::OnBnClickedBtnOpen()
{
	CFileDialog dlgfile(1, _T("*.mdb"), 0, 0, _T("MS Acess (*.mdb)|*.mdb|"));
	if (dlgfile.DoModal() == IDOK)
	{
		
		if (m_strPath == _T(""))
		{
			m_strPath = dlgfile.GetPathName();
			m_ctrlEditFileName.SetWindowText(dlgfile.GetFileName());
			GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PW)->EnableWindow(TRUE);
		}
		else if (m_strPath == dlgfile.GetPathName())
		{
			AfxMessageBox(_T("이미 개방된 DB 입니다."), MB_OK);
		}

		else
		{
			m_strPath = dlgfile.GetPathName();
			m_ctrlEditFileName.SetWindowText(dlgfile.GetFileName());
			GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PW)->EnableWindow(TRUE);
			GetDlgItem(IDC_COMBO_TABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_Seperate)->EnableWindow(FALSE);
			GetDlgItem(IDC_LIST_COLUMN)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_TotalRows)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_Rows)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_Seperate)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(FALSE);		
			if (m_db.IsOpen())
			{
				m_db.Close();
			}
			m_arrCColumn.clear();
			m_ctrlListColumn.DeleteAllItems();
		}
		
	}
}

// MDB 연결
void CMDBtoExcelDlg::OnBnClickedBtnConnect()
{

	CString strConnection;
	strConnection.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)}; DBQ=%s;PWD=%s")
		, m_strPath, m_strPW);

	if (!(m_db.OpenEx(strConnection, 0)))
	{
		AfxMessageBox(_T("연결이 실패하였습니다."));
		return;
	}

	AfxMessageBox(_T("연결이 성공하였습니다."));
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_TABLE)->EnableWindow(TRUE);
	//GetDlgItem(IDC_CHECK_Seperate)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_COLUMN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TotalRows)->EnableWindow(TRUE);
	//GetDlgItem(IDC_EDIT_Rows)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BUTTON_Seperate)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(TRUE);
	
	// ---------------------------------------------------------------------------------
	// 기본적인 ODBC API를 이용하여 MDB 파일의 Table List 가져오기
	HSTMT hStmt;
	SQLLEN lLen;
	CString strUnicode;

	char pcName[256];
	int nIdx = 0;

	SQLAllocStmt(m_db.m_hdbc, &hStmt);
	if (SQLTables(hStmt, NULL, 0, NULL, 0, NULL, 0, _T("TABLE"), SQL_NTS) != SQL_ERROR)
	{ /* OK */
		if (SQLFetch(hStmt) != SQL_NO_DATA_FOUND)
		{ /* Data found */
			while (!SQLGetData(hStmt, 3, SQL_C_CHAR, pcName, 256, &lLen))
			{ /* We have a name */
				if (pcName[0] != '~')
				{
					// Do something with the name here
					strUnicode = pcName; // Char to CString
					m_ctrlComboTable.InsertString(nIdx, strUnicode);
					nIdx++;
				}
				SQLFetch(hStmt);
			}
		}
	}
	SQLFreeStmt(hStmt, SQL_CLOSE);
	// ---------------------------------------------------------------------------------

	m_ctrlComboTable.SetCurSel(0);
	m_ctrlComboTable.GetLBText(0, m_strCurrentTable);

	CString strSQLCommand; // sql 명령
	CString strTotalRecord;

	// -----------------------------------------------------------------------------
	// Count Total Record
	CDBVariant vtval;
	strSQLCommand.Format(_T("Select count(*) from %s"), m_strCurrentTable);
	m_tbRecordSet.Open(CRecordset::forwardOnly, strSQLCommand);
	m_tbRecordSet.GetFieldValue((short)0, vtval);
	m_nTotalRecord = vtval.m_lVal;
	m_tbRecordSet.Close();
	// -----------------------------------------------------------------------------

	strTotalRecord.Format(_T("%d"), m_nTotalRecord);
	m_ctrlEditTotalRows.SetWindowText(strTotalRecord);

	// -----------------------------------------------------------------------------
	// Show Field on the CheckListBox
	m_ctrlComboTable.GetLBText(m_ctrlComboTable.GetCurSel(), m_strCurrentTable);
	strSQLCommand.Format(_T("Select * From %s"), m_strCurrentTable);

	m_tbRecordSet.Open(CRecordset::dynaset, strSQLCommand);

	// 해당 테이블의 Field의 개수 가져오기
	short nFieldCount = m_tbRecordSet.GetODBCFieldCount();
	m_arrCColumn.resize(nFieldCount);
	CODBCFieldInfo fieldInfo = { 0 };

	for (short i = 0; i < nFieldCount; i++)
	{
		m_tbRecordSet.GetODBCFieldInfo(i, fieldInfo);
		m_ctrlListColumn.InsertItem(i, fieldInfo.m_strName);
		m_arrCColumn[i].m_bCheck = FALSE;
		m_arrCColumn[i].m_strOriginName = fieldInfo.m_strName;
		m_arrCColumn[i].m_strChangeName = fieldInfo.m_strName;
	}
	
	m_tbRecordSet.Close();
	// -----------------------------------------------------------------------------
}

// 테이블 변경 시
void CMDBtoExcelDlg::OnCbnSelchangeComboTable()
{
	// 역으로 순환하여 모든 데이터 빠짐없이 삭제 -> CCheckBoxList 였을때
	//for (short i = m_ctrlCheckList.GetCount() - 1; i >= 0; i--)
	//{
	//	m_ctrlCheckList.DeleteString(i);
	//}
	//-------------------------------------------
	m_ctrlListColumn.DeleteAllItems();
	m_arrCColumn.clear();
	
	CString strSQLCommand; // SQL 명령
	CString strTotalRecord;

	m_ctrlComboTable.GetLBText(m_ctrlComboTable.GetCurSel(), m_strCurrentTable);
	
	// -----------------------------------------------------------------------------
	// 총 레코드 값 가져오기
	CDBVariant vtval;
	strSQLCommand.Format(_T("Select count(*) from %s"), m_strCurrentTable);
	m_tbRecordSet.Open(CRecordset::forwardOnly, strSQLCommand);
	m_tbRecordSet.GetFieldValue((short)0, vtval);
	m_nTotalRecord = vtval.m_lVal;
	m_tbRecordSet.Close();
	// -----------------------------------------------------------------------------

	strTotalRecord.Format(_T("%d"), m_nTotalRecord);
	m_ctrlEditTotalRows.SetWindowText(strTotalRecord);

	// -----------------------------------------------------------------------------
	// CheckListBox에 필드 표시
	strSQLCommand.Format(_T("Select * From %s"), m_strCurrentTable);
	m_tbRecordSet.Open(CRecordset::dynaset, strSQLCommand);

	// 해당 테이블의 Field의 개수 가져오기
	short nFieldCount = m_tbRecordSet.GetODBCFieldCount();
	m_arrCColumn.resize(nFieldCount);
	CODBCFieldInfo fieldInfo = { 0 };

	for (short i = 0; i < nFieldCount; i++)
	{
		m_tbRecordSet.GetODBCFieldInfo(i, fieldInfo);
		m_ctrlListColumn.InsertItem(i, fieldInfo.m_strName);
		m_arrCColumn[i].m_bCheck = FALSE;
		m_arrCColumn[i].m_strOriginName = fieldInfo.m_strName;
		m_arrCColumn[i].m_strChangeName = fieldInfo.m_strName;
	}

	m_tbRecordSet.Close();
	// -----------------------------------------------------------------------------
}

// Column 클릭시 전체 선택
void CMDBtoExcelDlg::OnHdnItemclickListColumn(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	int nCount = m_ctrlListColumn.GetItemCount();
	if (m_bListCheckState)
	{
		for (int idx = 0; idx < nCount; idx++)
		{
			m_ctrlListColumn.SetCheck(idx, FALSE);
			m_arrCColumn[idx].m_bCheck = FALSE;
		}
		m_bListCheckState = FALSE;
	}

	else
	{
		for (int idx = 0; idx < nCount; idx++)
		{
			m_ctrlListColumn.SetCheck(idx, TRUE);
			m_arrCColumn[idx].m_bCheck = TRUE;
		}
		m_bListCheckState = TRUE;
	}

	*pResult = 0;
}

void CMDBtoExcelDlg::OnBnClickedButtonSave()
{

	int nLen = 0;
	char strUtf8[1024] = { 0, };
	CString strPathName;

	UpdateCheckState();
	GetFieldString();

	CFileDialog dlgSaveFile(0, _T("*.xlsx")
		, 0
		, OFN_OVERWRITEPROMPT | OFN_LONGNAMES
		, _T("Excel Files (*.xlsx)|*.xlsx||")
	);

	if (m_strSelectedField == _T(""))
	{
		AfxMessageBox(_T("선택된 Column이 없습니다."));
	}

	else if (dlgSaveFile.DoModal() == IDOK)
	{
		strPathName = dlgSaveFile.GetPathName();
		nLen = WideCharToMultiByte(CP_UTF8, 0, strPathName, lstrlenW(strPathName), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, strPathName, lstrlenW(strPathName), strUtf8, nLen, NULL, NULL);

		m_workbook = workbook_new(strUtf8);
		m_arrPtSheet.push_back(workbook_add_worksheet(m_workbook, "test1"));

		CString strQuery;
		strQuery.Format(_T("select %s from %s"), m_strSelectedField, m_strCurrentTable);

		m_tbRecordSet.Open(CRecordset::dynaset, strQuery);
		// -----------------------------------------------------------------------------
		// 엑셀 첫 번째 라인 Column 이름으로 설정
		CODBCFieldInfo info;
		CString strUnicode;
		int nCount = (int)m_arrCColumn.size();
		int nxlsxCol = 0;

		vector<SWORD> arrDtype;
		arrDtype.resize(0);

		for (int nIdx = 0; nIdx < nCount; nIdx++)
		{
			if (m_arrCColumn[nIdx].m_bCheck)
			{
				strUnicode.Empty();
				memset(strUtf8, 0, sizeof(strUtf8));

				m_tbRecordSet.GetODBCFieldInfo(m_arrCColumn[nIdx].m_strOriginName, info);
				arrDtype.push_back(info.m_nSQLType);
				// -----------------------------------------------------------------------------
				strUnicode = m_arrCColumn[nIdx].m_strChangeName;
				nLen = WideCharToMultiByte(CP_UTF8, 0, strUnicode, lstrlenW(strUnicode)
					, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_UTF8, 0, strUnicode, lstrlenW(strUnicode)
					, strUtf8, nLen, NULL, NULL);
				// -----------------------------------------------------------------------------
				// worksheet_set_column(m_arrPtSheet[0], 0, nxlsxCol, info.m_nPrecision, NULL);
				worksheet_write_string(m_arrPtSheet[0], 0, nxlsxCol, strUtf8, NULL);
				nxlsxCol++;
			}
		}
		// -----------------------------------------------------------------------------

		// -----------------------------------------------------------------------------
		//  엑셀에 데이터 작성
		CString strValue;
		int nRow = 1;
		int nValue = 0;
		while (!(m_tbRecordSet.IsEOF()))
		{
			for (int nCol = 0; nCol < nxlsxCol; nCol++)
			{
				m_tbRecordSet.GetFieldValue(short(nCol), strUnicode);
				
				if (arrDtype[nCol] == SQL_NUMERIC || arrDtype[nCol] == SQL_INTEGER
					|| arrDtype[nCol] == SQL_SMALLINT)
				{
					nValue = _ttoi(strUnicode);
					worksheet_write_number(m_arrPtSheet[0], nRow, nCol, nValue, NULL);
				}
				else
				{
					// -----------------------------------------------------------------------------
					nLen = WideCharToMultiByte(CP_UTF8, 0, strUnicode, lstrlenW(strUnicode)
						, NULL, 0, NULL, NULL);
					WideCharToMultiByte(CP_UTF8, 0, strUnicode, lstrlenW(strUnicode)
						, strUtf8, nLen, NULL, NULL);;
					// ---------------------------------------------------------------------------
					worksheet_write_string(m_arrPtSheet[0], nRow, nCol, strUtf8, NULL);
					strUnicode.Empty();
					memset(strUtf8, 0, sizeof(strUtf8));
				}	
			}
			nRow++;
			m_ctrlProgSave.SetPos(nRow);
			m_tbRecordSet.MoveNext();
		}
		// -----------------------------------------------------------------------------

		lxw_error error_state = workbook_close(m_workbook);
		if (!(strcmp(lxw_strerror(error_state), "No error.")))
		{
			AfxMessageBox(_T("파일이 생성되었습니다."));
		}
		else
		{
			MessageBoxA(NULL, lxw_strerror(error_state), "Error", MB_OK);
		}
	}

	m_ctrlProgSave.SetPos(0);
	m_tbRecordSet.Close();
	
}

void CMDBtoExcelDlg::OnBnClickedButtonChange()
{
	UpdateCheckState();
	m_dlgChange.DoModal();
}

// -----------------------------------------------------------------------
// CheckListBox에서 체크된 필드를 합치는 곳
void CMDBtoExcelDlg::GetFieldString()
{
	m_strSelectedField.Empty();
	int nCount = (int)m_arrCColumn.size();

	for (int nfield = 0; nfield < nCount; nfield++)
	{
		if (m_arrCColumn[nfield].m_bCheck)
		{
			m_strSelectedField += m_arrCColumn[nfield].m_strChangeName;
			m_strSelectedField += _T(",");
		}
	}
	m_strSelectedField.Delete(m_strSelectedField.GetLength() - 1);
}
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Vector에 있는 CColumnName의 bState 상태 확인
void CMDBtoExcelDlg::UpdateCheckState()
{
	int nCount = (int)m_arrCColumn.size();
	for (int idx = 0; idx < nCount; idx++)
	{
		if (m_ctrlListColumn.GetCheck(idx))
		{
			m_arrCColumn[idx].m_bCheck = TRUE;
		}
	}

}
// -----------------------------------------------------------------------

void CMDBtoExcelDlg::OnBnClickedCheckSeperate()
{
	if (m_ctrlCheckSeperate.GetCheck() == BST_CHECKED)
	{
		GetDlgItem(IDC_BUTTON_Seperate)->EnableWindow(TRUE);
		m_ctrlEditRows.EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_Seperate)->EnableWindow(FALSE);
		m_ctrlEditRows.EnableWindow(FALSE);
	}
}


void CMDBtoExcelDlg::OnBnClickedButtonSeperate()
{
	m_dlgSeperate.DoModal();
}
