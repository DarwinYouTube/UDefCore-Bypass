#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <WinInet.h>
#include <tchar.h>
#include <algorithm>
#include <intrin.h>
#include <vector>
#include <string>

#include "xor.h"

bool checkconnection;

#pragma comment(lib,"ntdll.lib")
#pragma comment(lib, "Wininet.lib")
EXTERN_C NTSTATUS NTAPI NtSuspendProcess(IN HANDLE ProcessHandle);

int main() {
    SetConsoleTitle(xorstr("Bypass by Darwin"));
    std::cout << "[*] Checking License UDefCore bypass...";

    Sleep(600);
    // Проверяем интернет
    checkconnection = InternetCheckConnection("https://www.google.com/", FLAG_ICC_FORCE_CONNECTION, 0);
    if (!checkconnection) return 0;

    // Обход UDefCore

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_stricmp(entry.szExeFile, xorstr("UDefCore.exe")) == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, entry.th32ProcessID);

                std::cout << xorstr("[+] UDefCore found") << std::endl;

                Sleep(1000);

                SuspendThread(hProcess);

                std::cout << xorstr("[...] UDefCore Bypassing") << std::endl;
                Sleep(2000);

                std::cout << xorstr("[+] UdefCore Bypassing Successfulled") << std::endl;
                Sleep(1000);
                CloseHandle(hProcess);
                CloseHandle(snapshot);
                return 0;
            }
        }
    }

    std::cout << xorstr("[-] UdefCore not found") << std::endl;
    Sleep(1000);
    CloseHandle(snapshot);

    return 0;
}