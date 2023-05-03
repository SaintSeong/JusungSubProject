UINT ReceiveThread(LPVOID lpParameter)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        // 소켓 생성 실패 처리
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        // 연결 실패 처리
        closesocket(sock);
        return 1;
    }

    // 소켓 연결 성공

    char buffer[1024];
    int recvSize = 0;
    while (1)
    {
        // 데이터를 수신합니다.
        recvSize = recv(sock, buffer, sizeof(buffer), 0);
        if (recvSize == SOCKET_ERROR)
        {
            // 수신 에러 처리
            break;
        }

        // 수신한 데이터를 처리합니다.
        // ...
    }

    // 소켓을 닫습니다.
    closesocket(sock);

    return 0;
}


DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    HWND hWnd = (HWND)lpParameter;

    // TODO: 쓰레드에서 수행할 작업을 작성합니다.
    // ...

    SendMessage(hWnd, WM_THREAD_COMPLETE, 0, 0);

    return 0;
}

int main()
{
    // 메인 윈도우 핸들
    HWND hWnd = GetSafeHwnd();

    // 쓰레드 핸들
    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, hWnd, 0, NULL);

    // 쓰레드가 실행 중일 때, 메인 윈도우가 종료되지 않도록 함
    while (MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT) != WAIT_OBJECT_0)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    CloseHandle(hThread);

    return 0;
}
