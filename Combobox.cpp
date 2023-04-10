// mfc create combobox in listcontrol cell [한글]
// 열 추가
m_listctrl.InsertColumn(0, _T("Combo"), LVCFMT_LEFT, 100);
m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

// 셀 추가 및 콤보박스 스타일로 만들기
m_listctrl.InsertItem(0, _T(""));
m_listctrl.SetItemState(0, LVIS_FOCUSED, LVIS_FOCUSED);
CComboBox* pCombo = new CComboBox();
pCombo->Create(CBS_DROPDOWN | CBS_SORT | WS_VISIBLE | WS_VSCROLL, CRect(0, 0, 0, 0), &m_listctrl, 1000);
pCombo->AddString(_T("Item 1"));
pCombo->AddString(_T("Item 2"));
pCombo->AddString(_T("Item 3"));
pCombo->SetCurSel(0);
m_listctrl.SetItemData(0, (DWORD_PTR)pCombo);

// OnLButtonDown() 이벤트 처리
void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    LVHITTESTINFO lvHitTestInfo;
    lvHitTestInfo.pt = point;
    m_listctrl.SubItemHitTest(&lvHitTestInfo);
    if (lvHitTestInfo.iSubItem == 0 && lvHitTestInfo.flags == LVHT_ONITEMICON)
    {
        CComboBox* pCombo = (CComboBox*)m_listctrl.GetItemData(lvHitTestInfo.iItem);
        if (pCombo)
            pCombo->ShowDropDown();
    }
    CDialog::OnLButtonDown(nFlags, point);
}

void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    LVHITTESTINFO lvHitTestInfo;
    lvHitTestInfo.pt = point;
    m_listctrl.SubItemHitTest(&lvHitTestInfo);
    if (lvHitTestInfo.iSubItem == 0 && lvHitTestInfo.flags == LVHT_ONITEMICON)
    {
        CDateTimeCtrl* pDateTime = (CDateTimeCtrl*)m_listctrl.GetItemData(lvHitTestInfo.iItem);
        if (pDateTime)
            pDateTime->SetFocus();
    }
    CDialog::OnLButtonDown(nFlags, point);
}

// 콤보박스 값 설정
void CMyDialog::OnComboSelectionChange(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMCODE pNMCode = reinterpret_cast<LPNMCODE>(pNMHDR);
    if (pNMCode->code == CBN_SELCHANGE)
    {
        int nIndex = ((CComboBox*)pNMHDR->hwndFrom)->GetCurSel();
        CString strText;
        ((CComboBox*)pNMHDR->hwndFrom)->GetLBText(nIndex, strText);
        m_listctrl.SetItemText(pNMHDR->idFrom - 1000, 0, strText);
    }
    *pResult = 0;
}

// mfc Create combobox in multiple rows of list control [한글]
// 열 추가
m_listctrl.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 100);
m_listctrl.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 100);
m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

// 행 추가
m_listctrl.InsertItem(0, _T("Row 1"));
m_listctrl.InsertItem(1, _T("Row 2"));
m_listctrl.InsertItem(2, _T("Row 3"));

// 콤보박스 스타일로 만들기
CComboBox* pCombo = new CComboBox();
pCombo->Create(CBS_DROPDOWN | CBS_SORT | WS_VISIBLE | WS_VSCROLL, CRect(0, 0, 0, 0), &m_listctrl, 1000);
pCombo->AddString(_T("Item 1"));
pCombo->AddString(_T("Item 2"));
pCombo->AddString(_T("Item 3"));
pCombo->SetCurSel(0);

// 2번 행의 2번 열에 콤보박스 넣기
m_listctrl.SetItemData(1, 1, (DWORD_PTR)pCombo);

// 3번 행의 2번 열에 콤보박스 넣기
m_listctrl.SetItemData(2, 1, (DWORD_PTR)pCombo);

// 콤보박스 위치 조정
CRect rect;
m_listctrl.GetSubItemRect(1, 1, LVIR_BOUNDS, rect);
pCombo->MoveWindow(rect);

// 콤보박스에서 선택한 값을 저장하는 이벤트 처리기
void CMyDialog::OnComboSelectionChange(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMCODE pNMCode = reinterpret_cast<LPNMCODE>(pNMHDR);
    if (pNMCode->code == CBN_SELCHANGE)
    {
        int nIndex = ((CComboBox*)pNMHDR->hwndFrom)->GetCurSel();
        CString strText;
        ((CComboBox*)pNMHDR->hwndFrom)->GetLBText(nIndex, strText);
        int nRow = m_listctrl.GetNextItem(-1, LVNI_SELECTED);
        if (nRow >= 0)
            m_listctrl.SetItemText(nRow, 1, strText);
    }
    *pResult = 0;
}

// Handling left mouse button event on combobox in list control MFC
/*
1. 해당 리스트 컨트롤의 WM_LBUTTONDOWN 이벤트를 처리하는 함수를 작성합니다.
2. LVHITTESTINFO 구조체를 사용하여 마우스 클릭 위치를 확인합니다.
3. 마우스 클릭 위치에서 셀과 하위 항목 인덱스를 가져옵니다.
4. 셀과 하위 항목 인덱스가 콤보 박스가 있는 셀의 인덱스와 일치하는지 확인합니다.
5. 콤보 박스를 가져와서 드롭다운을 표시합니다.
6. 콤보 박스에서 항목을 선택하면 콤보 박스의 값을 셀에 설정합니다.
*/
void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    LVHITTESTINFO lvHitTestInfo;
    lvHitTestInfo.pt = point;
    m_listctrl.SubItemHitTest(&lvHitTestInfo);
    if (lvHitTestInfo.iItem != -1 && lvHitTestInfo.iSubItem == 1)
    {
        CComboBox* pCombo = (CComboBox*)m_listctrl.GetItemData(lvHitTestInfo.iItem);
        if (pCombo)
        {
            pCombo->ShowDropDown();
        }
    }
    CDialog::OnLButtonDown(nFlags, point);
}

void CMyDialog::OnComboSelectionChange(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMCODE pNMCode = reinterpret_cast<LPNMCODE>(pNMHDR);
    if (pNMCode->code == CBN_SELCHANGE)
    {
        int nIndex = ((CComboBox*)pNMHDR->hwndFrom)->GetCurSel();
        CString strText;
        ((CComboBox*)pNMHDR->hwndFrom)->GetLBText(nIndex, strText);
        int nItem = m_listctrl.GetNextItem(-1, LVNI_SELECTED);
        int nSubItem = 1; // 콤보 박스가 있는 열 인덱스
        m_listctrl.SetItemText(nItem, nSubItem, strText);
    }
    *pResult = 0;
}


// 열 추가
m_gridctrl.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 100);
m_gridctrl.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 100);
m_gridctrl.SetExtendedStyle(m_gridctrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

// 행 추가
m_gridctrl.InsertItem(0, _T("Row 1"));
m_gridctrl.InsertItem(1, _T("Row 2"));
m_gridctrl.InsertItem(2, _T("Row 3"));

// 콤보박스 스타일로 만들기
CComboBox* pCombo;
for (int row = 1; row <= 3; row++) {
    for (int col = 1; col <= 3; col++) {
        pCombo = new CComboBox();
        pCombo->Create(CBS_DROPDOWN | CBS_SORT | WS_VISIBLE | WS_VSCROLL, CRect(0, 0, 0, 0), &m_gridctrl, 1000);
        pCombo->AddString(_T("Item 1"));
        pCombo->AddString(_T("Item 2"));
        pCombo->AddString(_T("Item 3"));
        pCombo->SetCurSel(0);
        m_gridctrl.SetCellType(row, col, GV_CELL_TYPE::CELL_COMBOBOX);
        m_gridctrl.SetCellData(row, col, (LPARAM)pCombo);
    }
}

void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    int row, col;
    m_gridctrl.CellFromPt(point, row, col);
    if (m_gridctrl.GetCellType(row, col) == GV_CELL_TYPE::CELL_COMBOBOX) {
        CComboBox* pCombo = (CComboBox*)m_gridctrl.GetCellData(row, col);
        if (pCombo) {
            pCombo->ShowDropDown();
        }
    }
    CDialog::OnLButtonDown(nFlags, point);
}