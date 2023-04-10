// Access to shared folder c++
#include <Windows.h>

int main()
{
    // 공유 폴더 경로와 사용자 인증 정보 설정
    LPCWSTR path = L"\\\\server\\shared_folder";
    LPCWSTR username = L"username";
    LPCWSTR password = L"password";

    // 인증 정보로 로그인
    DWORD result = WNetAddConnection2W(&NETRESOURCEW{
        .dwType = RESOURCETYPE_DISK,
        .lpLocalName = NULL,
        .lpRemoteName = (LPWSTR)path,
        .lpProvider = NULL
    }, (LPCWSTR)password, (LPCWSTR)username, CONNECT_UPDATE_PROFILE);

    if (result != NO_ERROR) {
        // 오류 처리
        return 1;
    }

    // 공유 폴더에 대한 액세스 권한이있는 코드 실행
    // ...

    // 로그 아웃
    result = WNetCancelConnection2W(path, 0, TRUE);

    if (result != NO_ERROR) {
        // 오류 처리
        return 1;
    }

    return 0;
}

// Check the list of files in the shared folder c++
#include <Windows.h>
#include <iostream>

int main()
{
    LPCWSTR path = L"\\\\server\\shared_folder\\*.*"; // 공유 폴더 경로
    WIN32_FIND_DATAW data;
    HANDLE hFind = FindFirstFileW(path, &data); // 첫 번째 파일 찾기

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // 파일 이름 출력
            std::wcout << data.cFileName << std::endl;
        } while (FindNextFileW(hFind, &data)); // 다음 파일 찾기

        FindClose(hFind); // 검색 핸들 닫기
    }

    return 0;
}

#include <afx.h>
#include <iostream>

int main()
{
    CString path = L"\\\\server\\shared_folder\\*.*"; // 공유 폴더 경로
    CFileFind finder;
    BOOL bWorking = finder.FindFile(path); // 첫 번째 파일 찾기

    while (bWorking) {
        bWorking = finder.FindNextFileW(); // 다음 파일 찾기

        if (!finder.IsDots() && !finder.IsDirectory()) {
            // 파일 이름 출력
            std::wcout << finder.GetFileName() << std::endl;
        }
    }

    return 0;
}

// Get windows Caption use pid
#include <afxwin.h>
#include <iostream>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);

    if (processId == (DWORD)lParam) {
        wchar_t buffer[1024];
        GetWindowTextW(hwnd, buffer, 1024);

        if (wcslen(buffer) > 0) {
            // 캡션 출력
            std::wcout << buffer << std::endl;
        }
    }공유 폴더에 있는 파일 목록 확인

    return TRUE;
}

int main()
{
    DWORD processId = 1234; // 프로세스 ID
    EnumWindows(EnumWindowsProc, (LPARAM)processId);

    return 0;
}


