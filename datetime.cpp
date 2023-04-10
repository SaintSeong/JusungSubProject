// mfc input datetimepicker to listcontrol[한글 번역] 예시 1
// 열 추가
m_listctrl.InsertColumn(0, _T("Date"), LVCFMT_LEFT, 100);
m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

// DateTimePicker 스타일로 만들기
m_listctrl.SetColumnStyle(0, LVCS_DPI_SCALE | LVCS_WIDE | LVCS_NORESIZE | LVCS_ALIGN_LEFT, true);

// 빈 행 추가
m_listctrl.InsertItem(0, _T(""));

// DateTimePicker 삽입
CRect rect;
m_listctrl.GetSubItemRect(0, 0, LVIR_BOUNDS, rect);
CDateTimeCtrl* pDateTime = new CDateTimeCtrl();
pDateTime->Create(WS_CHILD | WS_VISIBLE | DTS_LONGDATEFORMAT, rect, &m_listctrl, 1000);
pDateTime->SetTime(COleDateTime::GetCurrentTime());
m_listctrl.SetItemData(0, (DWORD_PTR)pDateTime);

// OnLButtonDown() 이벤트 처리
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

// DateTimePicker 값 설정
void CMyDialog::OnDateTimeChange(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    COleDateTime dateTime;
    ((CDateTimeCtrl*)pNMHDR->hwndFrom)->GetTime(dateTime);
    CString strDate = dateTime.Format(_T("%Y/%m/%d"));
    m_listctrl.SetItemText(pDTChange->nmhdr.idFrom - 1000, 0, strDate);
    *pResult = 0;
}


// 예시 2
m_listctrl.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 100);
m_listctrl.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 100);
m_listctrl.InsertColumn(2, _T("Column 3"), LVCFMT_LEFT, 100);

//DateTime Picker 컨트롤을 위한 셀 에디트 스타일 설정
m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_FLATSB);

m_listctrl.InsertItem(0, _T("Row 1"));
m_listctrl.InsertItem(1, _T("Row 2"));

// Datetime Picker 컨트롤 생성 및 초기화
CDateTimeCtrl* pDateTime = new CDateTimeCtrl();
pDateTime->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | DTS_SHORTDATEFORMAT, CRect(0, 0, 0, 0), &m_listctrl, 1000);
pDateTime->SetTime(COleDateTime::GetCurrentTime());

// DateTime Picker 컨트롤을 삽입할 행 및 열 설정
int nRow = 0;
int nCol = 2;

// DateTime Picker 컨트롤을 삽입할 셀의 인덱스 구하기
int nItemIndex = m_listctrl.InsertItem(LVIF_PARAM | LVIF_STATE, nRow, _T(""), LVIS_SELECTED, LVIS_SELECTED, 0, (LPARAM)pDateTime);

// DateTime Picker 컨트롤을 삽입할 셀에 포커스 설정
m_listctrl.SetItemState(nItemIndex, LVIS_FOCUSED, LVIS_FOCUSED);

// DateTime Picker 컨트롤을 삽입할 셀에 컨트롤 삽입
m_listctrl.SetItem(nItemIndex, nCol, LVIF_STATE | LVIF_PARAM, _T(""), 0, 0, LVIS_SELECTED, LVIS_SELECTED, 0, (LPARAM)pDateTime);

// 마우스 왼쪽 버튼 다운 이벤트 처리하기
void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    LVHITTESTINFO lvHitTestInfo;
    lvHitTestInfo.pt = point;
    m_listctrl.SubItemHitTest(&lvHitTestInfo);
    if (lvHitTestInfo.iItem >= 0 && lvHitTestInfo.iSubItem == 2 && lvHitTestInfo.flags == LVHT_ONITEMICON)
    {
        CDateTimeCtrl* pDateTime = (CDateTimeCtrl*)m_listctrl.GetItemData(lvHitTestInfo.iItem);
        if (pDateTime)
            pDateTime->SendMessage(WM_LBUTTONDOWN, (WPARAM)nFlags, MAKELPARAM(point.x, point.y));
    }
    CDialog::OnLButtonDown(nFlags, point);
}


LVHITTESTINFO 구조체를 이용하여 마우스 클릭한 위치에 해당하는 아이템과 하위 아이템 정보를 구합니다. SubItemHitTest() 함수는 LVHITTESTINFO 구조체를 인자로 받아 마우스 클릭한 위치에 해당하는 정보를 반환합니다.

반환된 LVHITTESTINFO 구조체를 이용하여 마우스 클릭한 위치가 세 번째 열(인덱스 2)에 있는 DateTime Picker 아이콘인지 확인합니다. iItem 멤버 변수는 클릭한 아이템의 인덱스를, iSubItem 멤버 변수는 클릭한 아이템의 하위 열(서브 아이템) 인덱스를 나타냅니다. flags 멤버 변수는 마우스 클릭한 위치에 대한 추가 정보를 담고 있습니다. 이 코드에서는 LVHT_ONITEMICON 플래그를 사용하여 DateTime Picker 아이콘을 클릭했는지 확인합니다.

DateTime Picker 아이콘을 클릭한 경우, 클릭한 아이템의 데이터로부터 DateTime Picker 컨트롤의 포인터를 가져와 SendMessage() 함수를 이용하여 DateTime Picker 컨트롤의 WM_LBUTTONDOWN 메시지를 보냅니다. SendMessage() 함수의 첫 번째 인자는 전달할 메시지를 나타내는 정수 값이며, 두 번째 인자는 메시지와 관련된 부가적인 정보를 담고 있는 정수 값입니다. 마지막 인자는 클릭한 위치를 나타내는 좌표 값을 담고 있습니다.

마지막으로, 기존의 OnLButtonDown() 함수를 호출하여 이벤트를 처리합니다. 이 함수는 다른 이벤트나 메시지를 처리하는 함수들과 같이 작동합니다.



DateTimePicker 컨트롤의 이벤트 처리
DateTimePicker 컨트롤의 이벤트는 List Control의 메시지 처리 함수에서 처리됩니다. 이때, List Control의 SubItemHitTest 함수와 GetItemData 함수를 사용하여 클릭된 셀과 DateTimePicker 컨트롤의 포인터를 찾습니다. 그리고, DateTimePicker 컨트롤의 이벤트를 처리합니다.
void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    LVHITTESTINFO lvHitTestInfo;
    lvHitTestInfo.pt = point;
    m_listctrl.SubItemHitTest(&lvHitTestInfo);
    if (lvHitTestInfo.iItem >= 0 && lvHitTestInfo.iSubItem == 0 && lvHitTestInfo.flags == LVHT_ONITEMICON)
    {
        CDateTimeCtrl* pDateTimeCtrl = (CDateTimeCtrl*)m_listctrl.GetItemData(lvHitTestInfo.iItem);
        if (pDateTimeCtrl)
            pDateTimeCtrl->SendMessage(WM_LBUTTONDOWN, (WPARAM)nFlags, MAKELPARAM(point.x, point.y));
    }
    CDialog::OnLButtonDown(nFlags, point);
}
위 코드에서 m_listctrl은 MFC List Control의 컨트롤 변수입니다. CDateTimeCtrl은 DateTimePicker 컨트롤의 클래스입니다. LVHITTESTINFO 구조체는 List Control에서 마우스 클릭 위치 정보를 저장하는 구조체입니다.

DateTimePicker 컨트롤 값 설정
DateTimePicker 컨트롤의 값은 List Control의 메시지 처리 함수에서 처리됩니다. 이때, DateTimePicker 컨트롤의 GetTime 함수를 사용하여 값을 가져옵니다. 그리고, List Control의 SetItemText 함수를 사용하여 셀의 값을 변경합니다.
void CMyDialog::OnDateTimeChange(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    COleDateTime dateTime;
    ((CDateTimeCtrl*)pNMHDR->hwndFrom)->GetTime(dateTime);
    CString strDate = dateTime.Format(_T("%Y/%m/%d"));
    m_listctrl.SetItemText(pDTChange->nmhdr.idFrom - 1000, 0, strDate);
    *pResult = 0;
}
위 코드에서 CDateTimeCtrl은 DateTimePicker 컨트롤의 클래스입니다. LPNMDATETIMECHANGE은 DateTimePicker 컨트롤의 값을 변경하는 이벤트 정보를 저장하는 구조체입니다. 