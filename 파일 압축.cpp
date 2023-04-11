// mfc zlib.h를 이용하여 폴더 압축

MFC(Microsoft Foundation Class)는 Microsoft에서 제공하는 C++ 라이브러리입니다. MFC를 사용하면 Windows 프로그래밍을 쉽게 할 수 있으며, 폴더를 압축하는 기능을 구현할 수도 있습니다.

MFC에서 폴더를 압축하는 방법은 다음과 같습니다.

1. 폴더의 모든 파일을 찾아야 합니다. 이를 위해 CFileFind 클래스를 사용할 수 있습니다. CFileFind 클래스는 FindFirstFile(), FindNextFile() 및 FindClose()와 같은 함수를 제공하여 파일 및 디렉토리를 검색할 수 있습니다.

2. 압축할 파일을 하나씩 읽어서 압축합니다. 이를 위해 zlib이나 gzip과 같은 무손실 압축 알고리즘을 사용할 수 있습니다. 이러한 알고리즘은 텍스트 파일의 크기를 매우 효과적으로 줄일 수 있습니다.

3. 모든 파일을 압축한 후, 결과 파일을 생성합니다. 결과 파일을 만드는 방법은 여러 가지가 있지만, MFC에서는 CFile 클래스를 사용하여 파일을 작성할 수 있습니다.

#include <afx.h>
#include <zlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <direct.h>

bool CompressFolder(const CString& strFolderPath, const CString& strOutputFilePath)
{
    // 압축할 파일 리스트를 저장할 벡터를 생성합니다.
    std::vector<CString> fileList;

    // 폴더 내의 모든 파일을 찾아내기 위해 CFileFind 클래스를 사용합니다.
    CString strSearchPath = strFolderPath + _T("\\*.*");
    CFileFind finder;
    BOOL bWorking = finder.FindFile(strSearchPath);
    while (bWorking)
    {
        bWorking = finder.FindNextFile();

        // 파일이 아닌 폴더일 경우, 처리하지 않습니다.
        if (finder.IsDots() || finder.IsDirectory())
        {
            continue;
        }

        // 파일을 압축할 벡터에 추가합니다.
        fileList.push_back(finder.GetFilePath());
    }

    // 결과 파일을 생성합니다.
    CFile outputFile(strOutputFilePath, CFile::modeCreate | CFile::modeWrite);

    // 압축 알고리즘을 초기화합니다.
    z_stream stream = { 0 };
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    deflateInit(&stream, Z_BEST_COMPRESSION);

    // 각 파일을 하나씩 압축합니다.
    for (int i = 0; i < fileList.size(); i++)
    {
        // 파일을 읽어들입니다.
        CString strFilePath = fileList[i];
        CFile inputFile(strFilePath, CFile::modeRead);
        ULONGLONG nFileSize = inputFile.GetLength();
        char* pBuffer = new char[nFileSize];
        inputFile.Read(pBuffer, nFileSize);
        inputFile.Close();

        // 파일을 압축합니다.
        stream.avail_in = nFileSize;
        stream.next_in = (Bytef*)pBuffer;
        while (true)
        {
            char outputBuffer[1024];
            stream.avail_out = sizeof(outputBuffer);
            stream.next_out = (Bytef*)outputBuffer;
            int result = deflate(&stream, Z_FINISH);
            if (result == Z_STREAM_END)
            {
                outputFile.Write(outputBuffer, sizeof(outputBuffer) - stream.avail_out);
                break;
            }
            outputFile.Write(outputBuffer, sizeof(outputBuffer) - stream.avail_out);
        }

        // 메모리 누수를 방지하기 위해 버퍼를 삭제합니다.
        delete[] pBuffer;
    }

    // 압축 알고리즘을 정리합니다.
    deflateEnd(&stream);

    return true;
}

int main()
{
    CString strFolderPath = _T("C:\\Users\\username\\Documents\\folder");
    CString strOutputFilePath = _T("C:\\Users\\username\\Documents\\folder.zip");
    CompressFolder(strFolderPath, strOutputFilePath);

    return 0;
}


#include <afx.h>
#include <zlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <direct.h>

const int CHUNK_SIZE = 1024 * 1024 * 20; // 20MB

bool CompressFolder(const CString& strFolderPath, const CString& strOutputFolderPath)
{
    // 폴더 이름을 추출합니다.
    CString strFolderName = strFolderPath.Right(strFolderPath.GetLength() - strFolderPath.ReverseFind('\\') - 1);

    // 압축할 파일 리스트를 저장할 벡터를 생성합니다.
    std::vector<CString> fileList;

    // 폴더 내의 모든 파일을 찾아내기 위해 CFileFind 클래스를 사용합니다.
    CString strSearchPath = strFolderPath + _T("\\*.*");
    CFileFind finder;
    BOOL bWorking = finder.FindFile(strSearchPath);
    while (bWorking)
    {
        bWorking = finder.FindNextFile();

        // 파일이 아닌 폴더일 경우, 처리하지 않습니다.
        if (finder.IsDots() || finder.IsDirectory())
        {
            continue;
        }

        // 파일을 압축할 벡터에 추가합니다.
        fileList.push_back(finder.GetFilePath());
    }

    // 결과 파일을 생성합니다.
    CString strOutputFilePath;
    strOutputFilePath.Format(_T("%s\\%s.zip"), strOutputFolderPath, strFolderName);
    CFile outputFile(strOutputFilePath, CFile::modeCreate | CFile::modeWrite);

    // 압축 알고리즘을 초기화합니다.
    z_stream stream = { 0 };
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    deflateInit(&stream, Z_BEST_COMPRESSION);

    // 각 파일을 하나씩 압축합니다.
    int nFileIndex = 0;
    ULONGLONG nTotalFileSize = 0;
    for (int i = 0; i < fileList.size(); i++)
    {
        // 파일을 읽어들입니다.
        CString strFilePath = fileList[i];
        CFile inputFile(strFilePath, CFile::modeRead);
        ULONGLONG nFileSize = inputFile.GetLength();
        char* pBuffer = new char[nFileSize];
        inputFile.Read(pBuffer, nFileSize);
        inputFile.Close();

        // 파일을 압축합니다.
        stream.avail_in = nFileSize;
        stream.next_in = (Bytef*)pBuffer;
        while (true)
        {
            char outputBuffer[CHUNK_SIZE];
            stream.avail_out = sizeof(outputBuffer);
            stream.next_out = (Bytef*)outputBuffer;
            int result = deflate(&stream, Z_FINISH);
            if (result == Z_STREAM_END)
            {
                outputFile.Write(outputBuffer, sizeof(outputBuffer) - stream.avail_out);
                break;
            }
            outputFile.Write(outputBuffer, sizeof(outputBuffer) - stream.avail_out);
        }

        // 메모리 누수를 방지하기 위해 버퍼를 삭제합니다.
        delete[] pBuffer;

        // 파일 크기를 누적합니다.
        nTotalFileSize += nFileSize;

        // 지정한 용량을 넘은 경우, 새로운 파일로 분할합니다.
        if (nTotalFileSize > CHUNK_SIZE)
        {
             // 파일 인덱스를 증가시키고, 새로운 파일 이름을 생성합니다.
            nFileIndex++;
            CString strNewFilePath;
            strNewFilePath.Format(_T("%s\\%s_%d.zip"), strOutputFolderPath, strFolderName, nFileIndex);

            // 이전 파일을 닫고, 새로운 파일을 엽니다.
            outputFile.Close();
            outputFile.Open(strNewFilePath, CFile::modeCreate | CFile::modeWrite);

             // 압축 알고리즘을 초기화합니다.
            stream.avail_in = 0;
            stream.next_in = Z_NULL;
            deflateInit(&stream, Z_BEST_COMPRESSION);

            // 파일 크기를 초기화합니다.
            nTotalFileSize = 0;
        }
    }
}

// MFC CString convert CTime
// CString을 CTime으로 변환하는 예시 코드
CString strDate = _T("2022년 4월 12일 12시 30분 45초");
CTime time;
time.ParseDateTime(strDate, 0, MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN));

// CTime을 CString으로 변환하는 예시 코드
CTime time = CTime::GetCurrentTime();
CString strDate;
strDate.Format(_T("%04d년 %02d월 %02d일 %02d시 %02d분 %02d초"),
    time.GetYear(), time.GetMonth(), time.GetDay(),
    time.GetHour(), time.GetMinute(), time.GetSecond());


// CString 값이 2023-04-11일 경우 CTime 변환
CString strDate = _T("2023-04-11");
CTime time;
sscanf_s(strDate, _T("%d-%d-%d"), &time.GetYear(), &time.GetMonth(), &time.GetDay());

CString strDate = _T("2023-04-11");
COleDateTime oleDateTime;
oleDateTime.ParseDateTime(strDate);
CTime time = oleDateTime.GetTime();


FindWindow 함수의 두 번째 인자는 LPCTSTR 타입입니다. 따라서 CString을 인자로 직접 전달할 수는 없습니다.

하지만 CString 클래스는 LPCTSTR 타입으로 암시적으로 변환될 수 있기 때문에 CString 객체의 GetBuffer 함수를 사용하여 해당 CString의 LPCTSTR 타입 포인터를 얻어내고, 이를 FindWindow 함수의 두 번째 인자로 전달할 수 있습니다.

예를 들어, 다음과 같이 CString 변수 strTitle을 FindWindow 함수의 두 번째 인자로 전달할 수 있습니다.

CString strTitle = _T("Window Title");
HWND hWnd = FindWindow(NULL, strTitle.GetBuffer());
strTitle.ReleaseBuffer();

// MFC를 이용해 다른 Process의 메세지 읽기
// 다른 프로세스의 메시지를 읽기 위한 핸들
HWND hOtherWnd = ::FindWindow(nullptr, _T("Other Window Title"));

// 핸들이 존재하는 경우
if (hOtherWnd != nullptr)
{
    // 해당 프로세스의 핸들 가져오기
    DWORD dwOtherProcessId = 0;
    ::GetWindowThreadProcessId(hOtherWnd, &dwOtherProcessId);
    HANDLE hOtherProcess = ::OpenProcess(PROCESS_VM_READ, FALSE, dwOtherProcessId);

    // 핸들과 프로세스 핸들이 존재하는 경우
    if (hOtherWnd != nullptr && hOtherProcess != nullptr)
    {
        // 메시지 큐의 주소 가져오기
        DWORD dwOtherThreadId = ::GetWindowThreadProcessId(hOtherWnd, nullptr);
        HMODULE hUser32 = ::GetModuleHandle(_T("user32.dll"));
        DWORD dwOffset = (DWORD)::GetProcAddress(hUser32, "GetMessageW") - (DWORD)hUser32;
        DWORD dwQueueOffset = *(DWORD*)((DWORD)hOtherWnd + dwOffset + 2);
        DWORD dwQueueAddress = (DWORD)hOtherProcess + dwQueueOffset;

        // 메시지 큐 읽기
        MSG msg;
        SIZE_T nBytesRead = 0;
        ::ReadProcessMemory(hOtherProcess, (LPVOID)dwQueueAddress, &msg, sizeof(MSG), &nBytesRead);
        if (nBytesRead == sizeof(MSG))
        {
            // 메시지 읽기 성공
            // 이제 msg 변수에 읽어들인 메시지가 저장되어 있습니다.
            // 처리하고자 하는 작업을 수행합니다.
        }
    }

    // 프로세스 핸들 닫기
    if (hOtherProcess != nullptr)
    {
        ::CloseHandle(hOtherProcess);
    }
}


MSG msg;
// 메시지 큐에서 메시지를 읽어들인 후 msg 변수에 저장
// ...

// 메시지 박스로 메시지 출력
CString strMsg;
strMsg.Format(_T("메시지: 0x%X, wParam: 0x%X, lParam: 0x%X"), msg.message, msg.wParam, msg.lParam);
AfxMessageBox(strMsg);
