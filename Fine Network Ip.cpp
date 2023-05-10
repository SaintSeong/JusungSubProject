#include <iphlpapi.h>
#include <winsock2.h>

먼저, GetAdaptersAddresses 함수를 사용하여 현재 시스템에서 사용 가능한 모든 네트워크 어댑터의 정보를 가져옵니다. 
이 함수는 IP 주소, 서브넷 마스크, 기본 게이트웨이 등의 정보를 포함합니다.
PIP_ADAPTER_ADDRESSES adapterAddresses = nullptr;
ULONG bufferSize = 0;
DWORD result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapterAddresses, &bufferSize);

if (result == ERROR_BUFFER_OVERFLOW)
{
    adapterAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(new char[bufferSize]);
    result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapterAddresses, &bufferSize);
}
/*
GetAdaptersAddresses 함수가 반환한 PIP_ADAPTER_ADDRESSES 구조체의 목록에서 로컬 IP 주소를 찾습니다. 
이를 위해 각 어댑터의 FriendlyName 속성을 비교하여 원하는 네트워크를 찾습니다. 
찾은 어댑터의 FirstUnicastAddress 속성을 사용하여 첫 번째 유니캐스트 주소를 가져옵니다.
*/
std::wstring networkName = L"MyNetwork"; // 원하는 네트워크 이름
PIP_ADAPTER_ADDRESSES adapter = adapterAddresses;
while (adapter != nullptr)
{
    if (wcscmp(adapter->FriendlyName, networkName.c_str()) == 0)
    {
        PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
        while (address != nullptr)
        {
            if (address->Address.lpSockaddr->sa_family == AF_INET)
            {
                // IPv4 주소를 가져옵니다.
                char ipAddress[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in*>(address->Address.lpSockaddr)->sin_addr, ipAddress, INET_ADDRSTRLEN);
                std::string ipAddressString(ipAddress);
                break;
            }

            address = address->Next;
        }

        break;
    }

    adapter = adapter->Next;
}

// 마지막으로, 사용이 끝난 adapterAddresses 메모리를 해제합니다.
delete[] reinterpret_cast<char*>(adapterAddresses);


#include <iphlpapi.h>
#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int main()
{
    const wchar_t* networkName = L"MyNetwork"; // 확인할 네트워크 이름
    PIP_ADAPTER_ADDRESSES adapterAddresses = nullptr;
    ULONG bufferSize = 0;
    DWORD result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapterAddresses, &bufferSize);

    if (result == ERROR_BUFFER_OVERFLOW)
    {
        adapterAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(new char[bufferSize]);
        result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapterAddresses, &bufferSize);
    }

    if (result == NO_ERROR)
    {
        PIP_ADAPTER_ADDRESSES adapter = adapterAddresses;

        while (adapter != nullptr)
        {
            if (wcscmp(adapter->FriendlyName, networkName) == 0)
            {
                PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;

                while (address != nullptr)
                {
                    if (address->Address.lpSockaddr->sa_family == AF_INET)
                    {
                        char ipAddress[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in*>(address->Address.lpSockaddr)->sin_addr, ipAddress, INET_ADDRSTRLEN);
                        std::cout << "IP Address: " << ipAddress << std::endl;
                    }

                    address = address->Next;
                }
            }

            adapter = adapter->Next;
        }
    }

    delete[] reinterpret_cast<char*>(adapterAddresses);
    return 0;
}

위 코드에서 GetAdaptersAddresses 함수를 호출하여 모든 어댑터의 정보를 가져옵니다. 
그런 다음, while 루프를 사용하여 각 어댑터의 FriendlyName 속성과 비교하여 원하는 네트워크를 찾습니다. 
찾은 어댑터의 FirstUnicastAddress 속성을 사용하여 해당 어댑터의 첫 번째 유니캐스트 주소를 가져옵니다. 
마지막으로, inet_ntop 함수를 사용하여 IP 주소를 문자열로 변환하고, 이를 출력합니다.