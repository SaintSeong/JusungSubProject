
// SV_DVL to ExcelDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SV_DVL to Excel.h"
#include "SV_DVL to ExcelDlg.h"
#include "afxdialogex.h"
#include "xlsxwriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CSVDVLtoExcelDlg 대화 상자



CSVDVLtoExcelDlg::CSVDVLtoExcelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SV_DVL_TO_EXCEL_DIALOG, pParent)
	, m_tbRecordSet(&m_db)
	, m_strFilePath(_T(""))
	, m_strPW(_T("B1594C47"))
	, m_strTable(_T("SV_DVVAL"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_arrField.resize(5);
	m_arrRange.resize(0);
}

void CSVDVLtoExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, m_ctrlEditFile);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
	DDX_Control(pDX, IDC_PROGRESS_SAVE, m_ctrlProgSave);
}

BEGIN_MESSAGE_MAP(CSVDVLtoExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSVDVLtoExcelDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSVDVLtoExcelDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT, &CSVDVLtoExcelDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CSVDVLtoExcelDlg 메시지 처리기

BOOL CSVDVLtoExcelDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSVDVLtoExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSVDVLtoExcelDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);

		CBitmap bmp;
		CBitmap* pOldBmp = NULL;
		bmp.LoadBitmap(IDB_BITMAP_LOGO);
		pOldBmp = MemDC.SelectObject(&bmp);

		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		dc.TransparentBlt(0, 5, 240, 110,
			&MemDC,
			0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight,
			RGB(255, 255, 255));
		MemDC.SelectObject(pOldBmp);

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSVDVLtoExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSVDVLtoExcelDlg::OnBnClickedButtonOpen()
{
	CFileDialog dlgfile(1, _T("*.mdb"), 0, 0, _T("MS Acess (*.mdb)|*.mdb|"));
	if (dlgfile.DoModal() == IDOK)
	{

		if (m_strFilePath == _T(""))
		{
			m_strFilePath = dlgfile.GetPathName();
			m_ctrlEditFile.SetWindowText(dlgfile.GetFileName());
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PW)->EnableWindow(TRUE);
		}
		else if (m_strFilePath == dlgfile.GetPathName())
		{
			AfxMessageBox(_T("이미 개방된 DB 입니다."), MB_OK);
		}

		else if (m_strFilePath != dlgfile.GetPathName())
		{
			m_strFilePath = dlgfile.GetPathName();
			m_ctrlEditFile.SetWindowText(dlgfile.GetFileName());
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PW)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_CONVERT)->EnableWindow(FALSE);
			if (m_db.IsOpen())
			{
				m_db.Close();
			}
		}
	}
}


void CSVDVLtoExcelDlg::OnBnClickedButtonConnect()
{
	CString strConnection;
	strConnection.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)}; DBQ=%s;PWD=%s")
		, (LPCTSTR)m_strFilePath, (LPCTSTR)m_strPW);

	if (!(m_db.OpenEx(strConnection, 0)))
	{
		AfxMessageBox(_T("연결이 실패하였습니다."));
		return;
	}

	AfxMessageBox(_T("연결이 성공하였습니다."));
	GetDlgItem(IDC_BUTTON_CONVERT)->EnableWindow(TRUE);


	m_arrField[0].m_strOriginName = _T("VID");
	m_arrField[0].m_strChangeName = _T("SVID");

	m_arrField[1].m_strOriginName = _T("NAME");
	m_arrField[1].m_strChangeName = _T("VID NAME");

	m_arrField[2].m_strOriginName = _T("Description");
	m_arrField[2].m_strChangeName = _T("VID Description");

	m_arrField[3].m_strOriginName = _T("ValueFormat");
	m_arrField[3].m_strChangeName = _T("FORMAT");

	m_arrField[4].m_strOriginName = _T("ValueSize");
	m_arrField[4].m_strChangeName = _T("Type Size");


	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(FALSE);
	// -----------------------------------------------------------------------------
}


void CSVDVLtoExcelDlg::OnBnClickedButtonSave()
{
	CString strFields;
	for (int i = 0; i < (int)m_arrField.size(); i++)
	{
		strFields += m_arrField[i].m_strOriginName;
		strFields += _T(",");
	}
	strFields.Delete(strFields.GetLength() - 1);

	int nMin = 1;
	int nMax = 100000;
	int nRange = 100000;

	for (int i = 0; i < 7; i++)
	{
		if (i == 3)
		{
			nRange = 1000000;
			nMin = nRange;
			nMax = nRange * 2;
		}

		m_arrRange.push_back({ nMin, nMax - 1});

		nMin = nMax;
		nMax = nMax + nRange;
	}

	CFileDialog dlgSaveFile(0, _T("*.xlsx")
		, 0
		, OFN_OVERWRITEPROMPT | OFN_LONGNAMES
		, _T("Excel Files (*.xlsx)|*.xlsx||")
	);

	if (dlgSaveFile.DoModal() == IDOK)
	{
		int nLen = 0;
		char strUtf8[1024] = { 0, };

		lxw_workbook* workbook;
		CString strPathName;
		strPathName = dlgSaveFile.GetPathName();
		nLen = WideCharToMultiByte(CP_UTF8, 0, strPathName, lstrlenW(strPathName), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, strPathName, lstrlenW(strPathName), strUtf8, nLen, NULL, NULL);
		workbook = workbook_new(strUtf8);

		// -----------------------------------------------------------------------------
		// 엑셀 셀 스타일 설정
		lxw_format* format4Column;
		lxw_format* format4Number;
		lxw_format* format4String;

		format4Column = workbook_add_format(workbook);
		format_set_border(format4Column, LXW_BORDER_DOTTED);
		format_set_border_color(format4Column, LXW_COLOR_WHITE);
		format_set_bold(format4Column);
		format_set_font_color(format4Column, LXW_COLOR_WHITE);
		format_set_bg_color(format4Column, LXW_COLOR_BLACK);
		format_set_align(format4Column, LXW_ALIGN_CENTER);
		format_set_text_wrap(format4Column);

		format4Number = workbook_add_format(workbook);
		format_set_align(format4Number, LXW_ALIGN_CENTER);
		format_set_align(format4Number, LXW_ALIGN_VERTICAL_CENTER);
		format_set_border(format4Number, LXW_BORDER_DOTTED);
		
		format4String = workbook_add_format(workbook);
		format_set_align(format4String, LXW_ALIGN_LEFT);
		format_set_border(format4String, LXW_BORDER_DOTTED);
		format_set_align(format4String, LXW_ALIGN_VERTICAL_CENTER);
		format_set_text_wrap(format4String);
		// -----------------------------------------------------------------------------

		vector<lxw_worksheet*> arrWorkSheet; // Sheet 포인터를 저장하는 배열
		vector<SWORD> arrDtype; // Field의 Datatype을 저장하는 배열
		vector<int> arrExistSheetIdx; // 실제 존재하는 Sheet 인덱스를 저장하는 배열
		CODBCFieldInfo info;

		// 기본적으로 포함되는 Sheet
		arrWorkSheet.push_back(workbook_add_worksheet(workbook, "FAS"));
		arrExistSheetIdx.push_back(0);
		arrWorkSheet.push_back(workbook_add_worksheet(workbook, "SCH"));
		arrExistSheetIdx.push_back(1);
		arrWorkSheet.push_back(workbook_add_worksheet(workbook, "TMC"));
		arrExistSheetIdx.push_back(2);
		
		// -----------------------------------------------------------------------------
		// 총 레코드 값 가져오기, PMC 구성 연관
		CDBVariant vtval;
		CString strQuery;
		CString strSheetName;
		for (int nSheetIdx = 3; nSheetIdx < (int)m_arrRange.size(); nSheetIdx++)
		{
			strQuery.Format(_T("select count(*) from %s where %s between %d and %d;")
				, (LPCTSTR)m_strTable, (LPCTSTR)m_arrField[0].m_strOriginName
				, m_arrRange[nSheetIdx].m_nMin, m_arrRange[nSheetIdx].m_nMax);
			
			m_tbRecordSet.Open(CRecordset::forwardOnly, strQuery);
			m_tbRecordSet.GetFieldValue((short)0, vtval);
			if (vtval.m_lVal != 0)
			{
				strSheetName.Format(_T("PMC%d"), nSheetIdx - 2);
				memset(strUtf8, 0, sizeof(strUtf8));
				// -----------------------------------------------------------------------------
				nLen = WideCharToMultiByte(CP_UTF8, 0, strSheetName, lstrlenW(strSheetName)
					, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_UTF8, 0, strSheetName, lstrlenW(strSheetName)
					, strUtf8, nLen, NULL, NULL);
				// -----------------------------------------------------------------------------
				arrWorkSheet.push_back(workbook_add_worksheet(workbook, strUtf8));
				arrExistSheetIdx.push_back(nSheetIdx);
			}
			m_tbRecordSet.Close();
		}
		// -----------------------------------------------------------------------------
		
		//추가 탭 컬러 지정
		int tabColor[] = {
		   //LXW_COLOR_WHITE, //Selected Color
		   LXW_COLOR_YELLOW,
		   LXW_COLOR_RED,
		   LXW_COLOR_BLUE,
		   LXW_COLOR_GREEN,
		   //-----------------------------
		   LXW_COLOR_BLACK,
		   LXW_COLOR_BROWN,
		   LXW_COLOR_CYAN,
		   LXW_COLOR_GRAY,
		   LXW_COLOR_LIME,

		   LXW_COLOR_MAGENTA,
		   LXW_COLOR_NAVY,
		   LXW_COLOR_ORANGE,
		   LXW_COLOR_PINK,
		   LXW_COLOR_PURPLE,

		   LXW_COLOR_SILVER,
		};
		int index = 0;
		for (int i = 0; i < arrWorkSheet.size(); i++)
		{
			worksheet_set_tab_color(arrWorkSheet[i], tabColor[index++]);
			if (index > 14) index = 0;
		}

		int nSheetCount = (int)arrExistSheetIdx.size();
		for (int nSheetIdx = 0; nSheetIdx < nSheetCount; nSheetIdx++)
		{
			strQuery.Format(_T("select %s from %s where %s between %d and %d;")
				, (LPCTSTR)strFields
				, (LPCTSTR)m_strTable
				, (LPCTSTR)m_arrField[0].m_strOriginName
				, m_arrRange[arrExistSheetIdx[nSheetIdx]].m_nMin
				, m_arrRange[arrExistSheetIdx[nSheetIdx]].m_nMax);
			m_tbRecordSet.Open(CRecordset::dynaset, strQuery);

			// -----------------------------------------------------------------------------
			// 엑셀 첫 번째 라인 Column 이름으로 설정
			int nFieldCount = (int)m_arrField.size();
			CString strField;
			for (int nColumnIdx = 0; nColumnIdx < nFieldCount; nColumnIdx++)
			{
				strField.Empty();
				memset(strUtf8, 0, sizeof(strUtf8));

				m_tbRecordSet.GetODBCFieldInfo(m_arrField[nColumnIdx].m_strOriginName, info);
				arrDtype.push_back(info.m_nSQLType);
				// -----------------------------------------------------------------------------
				strField = m_arrField[nColumnIdx].m_strChangeName;
				nLen = WideCharToMultiByte(CP_UTF8, 0, strField, lstrlenW(strField)
					, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_UTF8, 0, strField, lstrlenW(strField)
					, strUtf8, nLen, NULL, NULL);
				// -----------------------------------------------------------------------------
				if (info.m_nSQLType == SQL_NUMERIC || info.m_nSQLType == SQL_INTEGER
					|| info.m_nSQLType == SQL_SMALLINT)
				{
					worksheet_set_column(arrWorkSheet[nSheetIdx], nColumnIdx, nColumnIdx, 10, NULL);
				}
				else
				{
					worksheet_set_column(arrWorkSheet[nSheetIdx], nColumnIdx, nColumnIdx, 50, NULL);
				}
				worksheet_write_string(arrWorkSheet[nSheetIdx], 0, nColumnIdx, strUtf8, format4Column);
			}
			// -----------------------------------------------------------------------------

			// -----------------------------------------------------------------------------
			//  엑셀에 데이터 작성
			CString strFieldValue;
			int nRow = 1;
			int nValue = 0;
			while (!(m_tbRecordSet.IsEOF()))
			{
				for (int nCol = 0; nCol < nFieldCount; nCol++)
				{
					strFieldValue.Empty();
					memset(strUtf8, 0, sizeof(strUtf8));
					m_tbRecordSet.GetFieldValue(short(nCol), strFieldValue);

					if (arrDtype[nCol] == SQL_NUMERIC || arrDtype[nCol] == SQL_INTEGER
						|| arrDtype[nCol] == SQL_SMALLINT)
					{
						nValue = _ttoi(strFieldValue);
						worksheet_write_number(arrWorkSheet[nSheetIdx], nRow, nCol, nValue, format4Number);
					}
					else
					{
						// -----------------------------------------------------------------------------
						nLen = WideCharToMultiByte(CP_UTF8, 0, strFieldValue, lstrlenW(strFieldValue)
							, NULL, 0, NULL, NULL);
						WideCharToMultiByte(CP_UTF8, 0, strFieldValue, lstrlenW(strFieldValue)
							, strUtf8, nLen, NULL, NULL);;
						// ---------------------------------------------------------------------------
						worksheet_write_string(arrWorkSheet[nSheetIdx], nRow, nCol, strUtf8, format4String);
					}
				}
				nRow++;
				m_tbRecordSet.MoveNext();
			}
			// -----------------------------------------------------------------------------
			// 엑셀 사용하지 않는 구간 음영 처리
			lxw_row_col_options options = {1};
			worksheet_set_column_opt(arrWorkSheet[nSheetIdx], COLS("F:XFD"), 8.43, NULL, &options);
			worksheet_set_default_row(arrWorkSheet[nSheetIdx], 15, LXW_TRUE);
			// -----------------------------------------------------------------------------
			double dValue = (double)(nSheetIdx + 1) / (double)nSheetCount * 100.0;
			m_ctrlProgSave.SetPos((int)dValue);
			m_tbRecordSet.Close();
		}

		lxw_error error_state = workbook_close(workbook);
		if (!(strcmp(lxw_strerror(error_state), "No error.")))
		{
			AfxMessageBox(_T("파일이 생성되었습니다."));
		}
		else
		{
			MessageBoxA(NULL, lxw_strerror(error_state), "Error", MB_OK);
		}

		m_ctrlProgSave.SetPos(0);
	}
}
