#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <tchar.h>

int main(void){
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("Failed to take snapshot of processes.\n");
        return 1;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnapshot, &pe32)) {
        printf("Failed to retrieve information about the first process.\n");
        CloseHandle(hSnapshot);
        return 1;
    }

    do {
        printf("Process ID: %u, Process Name: %s\n", pe32.th32ProcessID, pe32.szExeFile);
    }while(Process32Next(hSnapshot, &pe32)));
    CloseHandle(hSnapshot);
    return 0;
}