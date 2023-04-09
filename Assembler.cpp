// 파일 생성 시간 확인
CFileStatus status;
CString filePath = _T("C:\\example.txt");

if (CFile::GetStatus(filePath, status))
{
    CTime creationTime = status.m_ctime;
    CString strCreationTime = creationTime.Format(_T("%Y-%m-%d %H:%M:%S"));
    AfxMessageBox(strCreationTime);
}

// 폴더 내 파일 개수 찾기
CFileFind finder;
CString folderPath = _T("C:\\example");

int count = 0;
BOOL bWorking = finder.FindFile(folderPath + _T("\\*.*"));

while (bWorking)
{
    bWorking = finder.FindNextFile();

    if (!finder.IsDots() && !finder.IsDirectory())
    {
        count++;
    }
}

CString strCount;
strCount.Format(_T("The number of files in the folder is %d"), count);
AfxMessageBox(strCount);

// Files created at a specific time mfc
CFileFind finder;
CString folderPath = _T("C:\\example");

CTime searchTime = CTime::GetCurrentTime();  // 검색할 시간 설정
int count = 0;

BOOL bWorking = finder.FindFile(folderPath + _T("\\*.*"));

while (bWorking)
{
    bWorking = finder.FindNextFile();

    if (!finder.IsDots() && !finder.IsDirectory())
    {
        CTime creationTime = finder.GetCreationTime();
        if (creationTime == searchTime)
        {
            count++;
            // 원하는 작업 수행
        }
    }
}

CString strCount;
strCount.Format(_T("The number of files created at %s is %d"), searchTime.Format(_T("%Y-%m-%d %H:%M:%S")), count);
AfxMessageBox(strCount);

// CTime을 CString으로 변환하는 예제 코드
CTime currentTime = CTime::GetCurrentTime();
CString strTime = currentTime.Format(_T("%Y-%m-%d %H:%M:%S"));

// CString을 CTime으로 변환하는 예제 코드
CString strTime = _T("2022-04-09 14:30:00");
CTime time = CTime::ParseDateTime(strTime);

// find file creation time and modify time mfc
CFileFind finder;
BOOL bFound = finder.FindFile(_T("C:\\MyFolder\\MyFile.txt"));

if (bFound)
{
    finder.FindNextFile();

    // 파일 생성 시간 가져오기
    CTime createTime = finder.GetCreationTime();
    CString strCreateTime = createTime.Format(_T("Created on %Y-%m-%d %H:%M:%S"));

    // 파일 수정 시간 가져오기
    CTime modifyTime = finder.GetLastWriteTime();
    CString strModifyTime = modifyTime.Format(_T("Last modified on %Y-%m-%d %H:%M:%S"));

    // 결과 출력
    AfxMessageBox(strCreateTime + _T("\n") + strModifyTime);
}

// find folders in folder mfc
CFileFind finder;
CString folderPath = _T("C:\\MyFolder\\*.*");

BOOL bFound = finder.FindFile(folderPath);

while (bFound)
{
    bFound = finder.FindNextFile();

    if (finder.IsDots())
        continue;

    if (finder.IsDirectory())
    {
        CString folderName = finder.GetFileName();

        // 폴더 처리 코드 작성
        // ...

        CString subFolderPath = finder.GetFilePath() + _T("\\*.*");
        CFileFind subFinder;
        BOOL bSubFound = subFinder.FindFile(subFolderPath);

        while (bSubFound)
        {
            bSubFound = subFinder.FindNextFile();

            if (subFinder.IsDots())
                continue;

            if (subFinder.IsDirectory())
            {
                // 하위 폴더 처리 코드 작성
                // ...
            }
            else
            {
                // 파일 처리 코드 작성
                // ...
            }
        }
    }
    else
    {
        // 파일 처리 코드 작성
        // ...
    }
}

// listbox gridline mfc
myListBox.ModifyStyleEx(0, LBS_EX_GRIDLINES);


// how to time compare like big number and small number mfc
// 1. CTime
CTime time1(2021, 4, 9, 12, 0, 0); // 비교할 시간1
CTime time2(2021, 4, 9, 14, 0, 0); // 비교할 시간2

if (time1 < time2) {
    // 시간1이 시간2보다 작은 경우
}
else if (time1 > time2) {
    // 시간1이 시간2보다 큰 경우
}
else {
    // 시간1과 시간2가 같은 경우
}
// 2. CTimeSpan
CTime time1(2021, 4, 9, 12, 0, 0); // 비교할 시간1
CTime time2(2021, 4, 9, 14, 0, 0); // 비교할 시간2

CTimeSpan timeDiff = time1 - time2;
if (timeDiff.GetTotalSeconds() < 0) {
    // 시간1이 시간2보다 작은 경우
}
else if (timeDiff.GetTotalSeconds() > 0) {
    // 시간1이 시간2보다 큰 경우
}
else {
    // 시간1과 시간2가 같은 경우
}

//how to get click event handle other process c++
#include <Windows.h>

int main()
{
    // 대상 프로세스의 핸들 가져오기
    HWND targetWnd = FindWindow(NULL, "대상 윈도우 제목");

    if(targetWnd == NULL)
    {
        // 대상 윈도우가 없는 경우
        return 0;
    }

    // 대상 윈도우의 클릭 이벤트 핸들 가져오기
    DWORD pid;
    GetWindowThreadProcessId(targetWnd, &pid);
    HANDLE targetProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if(targetProcess == NULL)
    {
        // 대상 프로세스 핸들 가져오기 실패
        return 0;
    }

    // 클릭 이벤트 핸들 가져오기
    DWORD handleValue;
    ReadProcessMemory(targetProcess, (LPVOID)(targetWnd + 0x20), &handleValue, sizeof(handleValue), NULL);

    // 가져온 핸들 사용하기
    // ...

    return 0;
}
// how to get message event handle other process c++
#include <Windows.h>

int main()
{
    // 대상 프로세스의 핸들 가져오기
    HWND targetWnd = FindWindow(NULL, "대상 윈도우 제목");

    if(targetWnd == NULL)
    {
        // 대상 윈도우가 없는 경우
        return 0;
    }

    // 대상 윈도우의 메시지 핸들 가져오기
    DWORD pid;
    GetWindowThreadProcessId(targetWnd, &pid);
    HANDLE targetProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if(targetProcess == NULL)
    {
        // 대상 프로세스 핸들 가져오기 실패
        return 0;
    }

    // 메시지 핸들 가져오기
    DWORD handleValue;
    ReadProcessMemory(targetProcess, (LPVOID)(targetWnd + 0x14), &handleValue, sizeof(handleValue), NULL);

    // 가져온 핸들 사용하기
    // ...

    return 0;
}

// ReadProcessMemory를 통해 가져온 핸들 값을 이용하여 메세지 가져오기
#include <Windows.h>

int main()
{
    // 대상 프로세스의 핸들 가져오기
    HWND targetWnd = FindWindow(NULL, "대상 윈도우 제목");

    if(targetWnd == NULL)
    {
        // 대상 윈도우가 없는 경우
        return 0;
    }

    // 대상 윈도우의 메시지 핸들 가져오기
    DWORD pid;
    GetWindowThreadProcessId(targetWnd, &pid);
    HANDLE targetProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if(targetProcess == NULL)
    {
        // 대상 프로세스 핸들 가져오기 실패
        return 0;
    }

    // 메시지 핸들 가져오기
    DWORD handleValue;
    ReadProcessMemory(targetProcess, (LPVOID)(targetWnd + 0x14), &handleValue, sizeof(handleValue), NULL);

    // 메시지 가져오기
    MSG msg;
    typedef LRESULT (CALLBACK* WndProc)(HWND, UINT, WPARAM, LPARAM);
    WndProc lpWndProc = (WndProc)handleValue;

    while(PeekMessage(&msg, targetWnd, 0, 0, PM_REMOVE) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

