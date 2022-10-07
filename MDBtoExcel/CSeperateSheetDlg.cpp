// CSeperateSheetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MDBtoExcel.h"
#include "afxdialogex.h"
#include "CSeperateSheetDlg.h"


// CSeperateSheetDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeperateSheetDlg, CDialogEx)

CSeperateSheetDlg::CSeperateSheetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SeperateSheet, pParent)
{

}

CSeperateSheetDlg::~CSeperateSheetDlg()
{
}

void CSeperateSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SheetModify, m_ctrlListSheetModify);
}


BEGIN_MESSAGE_MAP(CSeperateSheetDlg, CDialogEx)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDCANCEL, &CSeperateSheetDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CSeperateSheetDlg 메시지 처리기
void CSeperateSheetDlg::SetColorCombo(CColourPickerCB *pColourPicker, int idx)
{
	pColourPicker->Create(WS_CHILD | WS_VISIBLE
		| CBS_OWNERDRAWFIXED | CBS_DROPDOWNLIST | CBS_HASSTRINGS
		, CRect(0, 0, 0, 0), this, IDC_Combo_Color + idx);
	pColourPicker->AddColour(_T("Black"), RGB(000, 000, 000));
	pColourPicker->AddColour(_T("White"), RGB(255, 255, 255));
	pColourPicker->AddColour(_T("Grey"), RGB(127, 127, 127));
	pColourPicker->AddColour(_T("RED"), RGB(255, 000, 000));
	pColourPicker->AddColour(_T("Orange"), RGB(255, 127, 000));
	pColourPicker->AddColour(_T("Yellow"), RGB(255, 255, 000));
	pColourPicker->AddColour(_T("Green"), RGB(000, 255, 000));
	pColourPicker->AddColour(_T("Cyan"), RGB(000, 255, 255));
	pColourPicker->AddColour(_T("Blue"), RGB(000, 000, 255));
	pColourPicker->AddColour(_T("Fuchsia"), RGB(255, 000, 255));
}

BOOL CSeperateSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect rect;
	m_ctrlListSheetModify.GetWindowRect(rect);
	ScreenToClient(rect);
	//m_ctrlListSheetModify.ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
	m_ctrlListSheetModify.SetExtendedStyle(m_ctrlListSheetModify.GetExtendedStyle() | LVS_EX_GRIDLINES);
	m_ctrlListSheetModify.InsertColumn(0, _T("Sheet"), LVCFMT_CENTER, rect.Width() / 4);

	LV_COLUMN lv_col;
	m_ctrlListSheetModify.GetColumn(0, &lv_col);
	lv_col.fmt = LVCFMT_CENTER;
	lv_col.mask = LVCF_FMT;
	m_ctrlListSheetModify.SetColumn(0, &lv_col);

	m_ctrlListSheetModify.InsertColumn(1, _T("Change"), LVCFMT_CENTER, rect.Width() / 4);
	m_ctrlListSheetModify.InsertColumn(2, _T("Color"), LVCFMT_CENTER, rect.Width() / 2 - 2);

	m_ctrlListSheetModify.InsertItem(0, _T("123"));
	m_ctrlListSheetModify.InsertItem(1, _T("123"));
	m_ctrlListSheetModify.InsertItem(2, _T("123"));

	m_ctrlListSheetModify.SetItemText(0, 1, _T("123"));
	m_ctrlListSheetModify.SetItemText(1, 1, _T("123"));
	m_ctrlListSheetModify.SetItemText(2, 1, _T("123"));

	m_arrColor.resize(3);

	//for (int idx = 0; idx < 3; idx++)
	//{
	//	m_ctrlListSheetModify.GetSubItemRect(idx, 2, LVIR_BOUNDS, rect);
	//	m_ctrlListSheetModify.ClientToScreen(rect); // 클라이언트 좌표를 화면 좌표로 변환
	//	this->ScreenToClient(rect); //  화면 좌표를 클라이언트 좌표로 변환
	//	m_arrColor[idx] = new CColourPickerCB();
	//	//SetColorCombo(m_arrColor[idx], idx);
	//	m_arrColor[idx]->Create(
	//		WS_CHILD | WS_VISIBLE| CBS_OWNERDRAWFIXED | CBS_DROPDOWNLIST | CBS_HASSTRINGS
	//		, CRect(0, 0, 0, 0), this, IDC_Combo_Color + idx);
	//	m_arrColor[idx]->AddColour(_T("Black"), RGB(000, 000, 000));
	//	m_arrColor[idx]->AddColour(_T("White"), RGB(255, 255, 255));
	//	m_arrColor[idx]->AddColour(_T("Grey"), RGB(127, 127, 127));
	//	m_arrColor[idx]->AddColour(_T("RED"), RGB(255, 000, 000));
	//	m_arrColor[idx]->AddColour(_T("Orange"), RGB(255, 127, 000));
	//	m_arrColor[idx]->AddColour(_T("Yellow"), RGB(255, 255, 000));
	//	m_arrColor[idx]->AddColour(_T("Green"), RGB(000, 255, 000));
	//	m_arrColor[idx]->AddColour(_T("Cyan"), RGB(000, 255, 255));
	//	m_arrColor[idx]->AddColour(_T("Blue"), RGB(000, 000, 255));
	//	m_arrColor[idx]->AddColour(_T("Fuchsia"), RGB(255, 000, 255));
	//	m_arrColor[idx]->SetWindowPos(NULL, rect.left
	//		, rect.top
	//		, rect.right - rect.left
	//		, rect.bottom - rect.top
	//		, SWP_SHOWWINDOW);
	//	m_arrColor[idx]->SetCurSel(0);
	//}

	//RedrawWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSeperateSheetDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

}

void CSeperateSheetDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}



int CSeperateSheetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CColourPickerCB* test;
	test = new CColourPickerCB();
	BOOL btest = test->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS
		, CRect(0, 0, 40, 40), this, 13432);

	return 0;
}
