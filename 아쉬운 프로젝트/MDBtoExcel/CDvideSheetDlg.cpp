// CDvideSheetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MDBtoExcel.h"
#include "afxdialogex.h"
#include "CDvideSheetDlg.h"
#include "MDBtoExcelDlg.h"


// CDvideSheetDlg 대화 상자

IMPLEMENT_DYNAMIC(CDvideSheetDlg, CDialogEx)

CDvideSheetDlg::CDvideSheetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIVIDE_SHEET, pParent)
	, m_strStandardField(_T(""))
	, m_nISavedItem(0)
	, m_nISavedSubitem(0)
	, m_nSheetCount(1)
{
	m_arrSheet.resize(1);
	m_arrSheet[0].m_strSheetOrigin = _T("sheet1");
	m_arrSheet[0].m_strSheetChange = _T("sheet1");
	m_arrSheet[0].m_nMin = 0;
	m_arrSheet[0].m_nMax = 9999999;
}

CDvideSheetDlg::~CDvideSheetDlg()
{
}

void CDvideSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHEET, m_ctrlListSheet);
	DDX_Text(pDX, IDC_EDIT_STANDARD, m_strStandardField);
	DDX_Control(pDX, IDC_EDIT_SHEET_VALUE, m_ctrlEditSheet);
}


BEGIN_MESSAGE_MAP(CDvideSheetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CDvideSheetDlg::OnBnClickedButtonDivide)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SHEET, &CDvideSheetDlg::OnNMClickListSheet)
	ON_BN_CLICKED(IDOK, &CDvideSheetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDvideSheetDlg 메시지 처리기


BOOL CDvideSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect rect;
	m_ctrlListSheet.GetWindowRect(&rect);
	ScreenToClient(rect);

	m_ctrlListSheet.SetExtendedStyle(m_ctrlListSheet.GetExtendedStyle() 
		| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlListSheet.InsertColumn(0, _T("SheetBasicName"), 0, rect.Width() / 6 * 2);
	m_ctrlListSheet.InsertColumn(1, _T("SheetChangeName"), 0, rect.Width() / 6 * 2);
	m_ctrlListSheet.InsertColumn(2, _T("Min"), 0, rect.Width() / 6);
	m_ctrlListSheet.InsertColumn(3, _T("Max"), 0, rect.Width() / 6);

	CMDBtoExcelDlg* dlgParent = (CMDBtoExcelDlg*)GetParent();
	dlgParent->m_ctrlComboStandard.GetLBText(dlgParent->m_nStandardIdx, m_strStandardField);
	m_ctrlEditSheet.SetWindowText(_T("0"));
	UpdateData(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDvideSheetDlg::OnBnClickedButtonDivide()
{
	m_arrSheet.clear();
	CString strSheetNumber;
	m_ctrlEditSheet.GetWindowText(strSheetNumber);
	m_nSheetCount = _ttoi(strSheetNumber);
	m_arrSheet.resize(m_nSheetCount);
	
	int nMin = 1;
	int nMax = 100000;
	int nRange = 100000;

	CString strSheetName;
	CString strNumber;
	for (int nRow = 0; nRow < m_nSheetCount; nRow++)
	{
		strSheetName.Format(_T("Sheet%d"), nRow + 1);
		m_arrSheet[nRow].m_strSheetOrigin = strSheetName;
		m_arrSheet[nRow].m_strSheetChange = strSheetName;
		m_arrSheet[nRow].m_nMin = nMin;
		m_arrSheet[nRow].m_nMax = nMax - 1;

		m_ctrlListSheet.InsertItem(nRow, m_arrSheet[nRow].m_strSheetOrigin);
		m_ctrlListSheet.SetItemText(nRow, 1, m_arrSheet[nRow].m_strSheetChange);
		strNumber.Format(_T("%d"), m_arrSheet[nRow].m_nMin);
		m_ctrlListSheet.SetItemText(nRow, 2, strNumber);
		strNumber.Format(_T("%d"), m_arrSheet[nRow].m_nMax);
		m_ctrlListSheet.SetItemText(nRow, 3, strNumber);

		nMin = nMax;
		nMax = nMax + nRange;

		if (nRow == 2)
		{
			nRange = 1000000;
			nMin = nRange;
			nMax = nRange * 2;
		}
	}

	m_ctrlListSheet.EnableWindow(TRUE);
}

void CDvideSheetDlg::OnNMClickListSheet(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_nISavedItem = pNMItemActivate->iItem; // Row 인덱스 번호
	m_nISavedSubitem = pNMItemActivate->iSubItem; // Col 인덱스 번호

	if (m_nISavedItem != -1 && m_nISavedSubitem != 0) {

		CRect rect;
		m_ctrlListSheet.GetSubItemRect(m_nISavedItem, m_nISavedSubitem, LVIR_BOUNDS, rect);
		m_ctrlListSheet.ClientToScreen(rect);
		this->ScreenToClient(rect);

		GetDlgItem(IDC_EDIT_MODIFY_SHEETDLG)
			->SetWindowText(m_ctrlListSheet.GetItemText(m_nISavedItem, m_nISavedSubitem));
		GetDlgItem(IDC_EDIT_MODIFY_SHEETDLG)->SetWindowPos(NULL, rect.left
			, rect.top
			, rect.right - rect.left - 3
			, rect.bottom - rect.top
			, SWP_SHOWWINDOW);
		GetDlgItem(IDC_EDIT_MODIFY_SHEETDLG)->SetFocus();
	}
	*pResult = 0;
}


BOOL CDvideSheetDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // Enter 키
		{
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT_MODIFY_SHEETDLG)->GetSafeHwnd())
				// GetSafeHwnd() : 창의 창 핸들을 반환(부모창 반환)
			{
				CString str;
				GetDlgItemText(IDC_EDIT_MODIFY_SHEETDLG, str);
				m_ctrlListSheet.SetItemText(m_nISavedItem, m_nISavedSubitem, str);
				GetDlgItem(IDC_EDIT_MODIFY_SHEETDLG)->ShowWindow(SW_HIDE);
			}
			return TRUE;
		}

		if (pMsg->wParam == VK_ESCAPE) // ESC 키
		{
			GetDlgItem(IDC_EDIT_MODIFY_SHEETDLG)->ShowWindow(SW_HIDE);
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDvideSheetDlg::OnBnClickedOk()
{
	for (int nRow = 0; nRow < m_nSheetCount; nRow++)
	{
		m_arrSheet[nRow].m_strSheetChange = m_ctrlListSheet.GetItemText(nRow, 1);
		m_arrSheet[nRow].m_nMin = _ttoi(m_ctrlListSheet.GetItemText(nRow, 2));
		m_arrSheet[nRow].m_nMax = _ttoi(m_ctrlListSheet.GetItemText(nRow, 3));
	}
	CDialogEx::OnOK();
}
