// 파일 경로와 이름 지정
CString filePath = "C:\\eventlog.txt";

// 파일 열기
CStdioFile file;
if (!file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText)) {
    AfxMessageBox(_T("파일 열기 실패"));
    return;
}

// 이벤트 로그 조회
CEventLog eventLog;
if (eventLog.Open(_T("Application"))) {
    EVENTLOGRECORD* pEvent = nullptr;
    DWORD bytesRead = 0;
    DWORD totalBytes = 0;
    
    // 이벤트 로그에서 데이터 읽기
    while (eventLog.ReadEventLog(EVENTLOG_SEQUENTIAL_READ | EVENTLOG_FORWARDS_READ, 0, &pEvent, 1, &bytesRead, &totalBytes)) {
        if (pEvent != nullptr) {
            // 이벤트 로그 데이터를 파일에 기록
            file.WriteString(pEvent->Data);
            file.WriteString(_T("\n"));

            // 메모리 해제
            eventLog.FreeEventLog(pEvent);
        }
    }
    
    eventLog.Close();
}
else {
    AfxMessageBox(_T("이벤트 로그 열기 실패"));
}

// 파일 닫기
file.Close();

// 특정 시간대 지정
CTime startTime(2023, 5, 25, 10, 0, 0);  // 시작 시간 (10시 0분 0초)
CTime endTime(2023, 5, 25, 11, 0, 0);   // 종료 시간 (11시 0분 0초)

// 이벤트 로그 조회
CEventLog eventLog;
if (eventLog.Open(_T("Application"))) {
    EVENTLOGRECORD* pEvent = nullptr;
    DWORD bytesRead = 0;
    DWORD totalBytes = 0;

    // 이벤트 로그에서 데이터 읽기
    while (eventLog.ReadEventLog(EVENTLOG_SEQUENTIAL_READ | EVENTLOG_FORWARDS_READ, 0, &pEvent, 1, &bytesRead, &totalBytes)) {
        if (pEvent != nullptr) {
            // 이벤트 발생 시간 가져오기
            CTime eventTime(pEvent->TimeGenerated);

            // 지정한 시간 범위에 해당하는 이벤트만 처리
            if (eventTime >= startTime && eventTime <= endTime) {
                // 이벤트 로그 데이터를 파일에 기록
                file.WriteString(pEvent->Data);
                file.WriteString(_T("\n"));
            }

            // 메모리 해제
            eventLog.FreeEventLog(pEvent);
        }
    }

    eventLog.Close();
}
else {
    AfxMessageBox(_T("이벤트 로그 열기 실패"));
}

eventLog.ReadEventLog 함수는 이벤트 로그를 읽어오는 데 사용되는 함수입니다. 각 파라미터의 역할은 다음과 같습니다:

EVENTLOG_SEQUENTIAL_READ:
이 파라미터는 이벤트 로그를 순차적으로 읽기 위한 옵션입니다. 순차적으로 읽을 경우 로그의 시작 지점부터 끝까지 연속적으로 이벤트를 읽어올 수 있습니다.

EVENTLOG_FORWARDS_READ:
이 파라미터는 이벤트 로그를 앞으로(forward) 읽기 위한 옵션입니다. 앞으로 읽을 경우 가장 이전에 읽은 이벤트 이후의 이벤트들을 읽어올 수 있습니다.

0:
이 파라미터는 이벤트 로그의 오프셋을 지정하는 값입니다. 일반적으로 0으로 설정하여 처음부터 읽기를 시작합니다.

&pEvent:
이 파라미터는 읽어온 이벤트 데이터를 받을 이벤트 구조체에 대한 포인터입니다. 이 함수를 호출하면 이벤트 로그에서 읽은 이벤트의 정보가 이 구조체에 저장됩니다.

1:
이 파라미터는 읽을 이벤트의 개수를 지정하는 값입니다. 일반적으로 1로 설정하여 한 번에 하나의 이벤트를 읽습니다.

&bytesRead:
이 파라미터는 실제로 읽어온 이벤트의 바이트 수를 받을 변수에 대한 포인터입니다. 이 값은 호출 후에 실제로 읽은 이벤트의 바이트 수로 업데이트됩니다.

&totalBytes:
이 파라미터는 이벤트 로그 전체의 바이트 수를 받을 변수에 대한 포인터입니다. 이 값은 호출 후에 전체 이벤트 로그의 바이트 수로 업데이트됩니다.

https://github.com/SergiusTheBest/plog