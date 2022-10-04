// ColumnChange.cpp: 구현 파일
//

#include "pch.h"
#include "MDBtoExcel.h"
#include "MDBtoExcelDlg.h"
#include "afxdialogex.h"
#include "CColumnChangeDlg.h"


// ColumnChange 대화 상자

IMPLEMENT_DYNAMIC(CColumnChangeDlg, CDialogEx)

CColumnChangeDlg::CColumnChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGE_COLUMN, pParent)
	, m_nISavedItem(0)
	, m_nISavedSubitem(0)
	, m_ArrStr(0)
	, m_nChecked(0)
{

}

CColumnChangeDlg::~CColumnChangeDlg()
{
	delete[] m_ArrStr;
}

void CColumnChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COLUMN, m_ctrlCoulumnList);
}


BEGIN_MESSAGE_MAP(CColumnChangeDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COLUMN, &CColumnChangeDlg::OnNMDblclkListColumn)
END_MESSAGE_MAP()

BOOL CColumnChangeDlg::OnInitDialog()
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
	m_ctrlCoulumnList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_ctrlCoulumnList.SetExtendedStyle(
		m_ctrlCoulumnList.GetExtendedStyle()
		| LVS_EX_GRIDLINES
		| LVS_EX_FULLROWSELECT
	);
	CRect rec;
	int width;

	m_ctrlCoulumnList.GetWindowRect(&rec);
	width = rec.Width() / 2;

	m_ctrlCoulumnList.InsertColumn(0, _T("Column"), 0, width);
	m_ctrlCoulumnList.InsertColumn(1, _T("Change"), 0, width);

	CMDBtoExcelDlg* dlgParent = (CMDBtoExcelDlg*)GetParent();
	CString strCoulumn;

	for (int nfield = 0; nfield < dlgParent->m_ctrlCheckList.GetCount(); nfield++)
	{
		if (dlgParent->m_ctrlCheckList.GetCheck(nfield) == BST_CHECKED)
		{
			dlgParent->m_ctrlCheckList.GetText(nfield, strCoulumn);
			m_ctrlCoulumnList.InsertItem(nfield, strCoulumn);
			m_nChecked++;
		}
	}

	for (int nIdx = 0; nIdx < m_nChecked; nIdx++)
	{
		m_ctrlCoulumnList.SetItemText(nIdx, 1, m_ctrlCoulumnList.GetItemText(nIdx, 0));
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


BOOL CColumnChangeDlg::DestroyWindow()
{
	CMDBtoExcelDlg* dlgParent = (CMDBtoExcelDlg*)GetParent();
	int nCount = 0;
	

	for (int nfield = 0; nfield < dlgParent->m_ctrlCheckList.GetCount(); nfield++)
	{
		if (dlgParent->m_ctrlCheckList.GetCheck(nfield) == BST_CHECKED)
		{
			nCount++;
		}
	}

	m_ArrStr = new CString[nCount];

	for (int idx = 0; idx < nCount; idx++)
	{
		m_ArrStr[idx] = m_ctrlCoulumnList.GetItemText(idx, 1);
	}

	return CDialogEx::DestroyWindow();
}

// ColumnChange 메시지 처리기

//--------------------------------------------------------------------------
// ListCtrl의 Cell을 Double Click하면 해당 위치 Edit 박스 생성
void CColumnChangeDlg::OnNMDblclkListColumn(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	m_nISavedItem = pNMITEM->iItem; // Row 인덱스 번호
	m_nISavedSubitem = pNMITEM->iSubItem; // Col 인덱스 번호

	if (pNMITEM->iItem != -1 && pNMITEM->iSubItem != 0) { // Row 인덱스가 -1이 아닌 경우 => Row Full Select 동작 x

		CRect rect;

		/*
		LVIR_BOUNDS : 아이콘 및 레이블을 포함하여 전체 항목의 경계 사각형을 반환합니다.
		LVIR_ICON	: 아이콘 또는 작은 아이콘의 경계 사각형을 반환합니다.
		LVIR_LABEL	: 항목 텍스트의 경계 사각형을 반환합니다.
		*/

		//if (pNMITEM->iSubItem == 0)
		//{
		//	m_ctrlCoulumnList.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
		//	rect.right = rect.left + m_ctrlCoulumnList.GetColumnWidth(0);
		//}

		m_ctrlCoulumnList.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);

		m_ctrlCoulumnList.ClientToScreen(rect); // 클라이언트 좌표를 화면 좌표로 변환
		// 리스트 컨트롤 화면에서 전체 스크린으로 전환
		this->ScreenToClient(rect); //  화면 좌표를 클라이언트 좌표로 변환
		// 전체 스크린에서 실제 창이 차지하는 크기만큼으로 전환
		// 3개의 창 존재시 small -> big -> middle 순으로 하여야 실제 창의 컨트롤들의 위치가 파악 가능

		GetDlgItem(IDC_EDIT_MODIFY)
			->SetWindowText(m_ctrlCoulumnList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		// Edit Control에 실제 ListControl에 있는 Text 넣기
		GetDlgItem(IDC_EDIT_MODIFY)->SetWindowPos(NULL, rect.left
			, rect.top
			, rect.right - rect.left
			, rect.bottom - rect.top
			, SWP_SHOWWINDOW); // Edit Control을 실제 위치에 적용

		GetDlgItem(IDC_EDIT_MODIFY)->SetFocus();
	}

	*pResult = 0;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// 키보드 이벤트가 들어오면 ListBox에 텍스트 값 설정
BOOL CColumnChangeDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // Enter 키
		{
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT_MODIFY)->GetSafeHwnd())
				// GetSafeHwnd() : 창의 창 핸들을 반환(부모창 반환)
			{
				CString str;
				GetDlgItemText(IDC_EDIT_MODIFY, str);
				m_ctrlCoulumnList.SetItemText(m_nISavedItem, m_nISavedSubitem, str);
				GetDlgItem(IDC_EDIT_MODIFY)->ShowWindow(SW_HIDE);
			}
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE) // ESC 키
		{
			GetDlgItem(IDC_EDIT_MODIFY)->ShowWindow(SW_HIDE);
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
//--------------------------------------------------------------------------
