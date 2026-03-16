#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int count_threads_for_pid(DWORD pid){
	int count =0;
	
	HANDLE hThreadSnap = CreateToolhelp32Sbapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return 0;
		
	THREADENTRY32 te32;
	te32.dwSize = sizeof (THREADENTRY32);
	
	if (Thread32First(hThreadSnap.&te32)){
		do {
			if(te32.th32OwnerProcessID == pid){
				count ++;
			}
		}while(Thread32Next(hThreadSnap.&te32));
	}
	
	ClosedHandle(hThreadSnap):
	return count;
}

int main(void){
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	
	InpProcesSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("Failed to create process snapshot\n");
		return 1;
	}
	
	pe2.dwSize = sizeof(PROCESSENTRY32);
	
	if (!Process32First(hProcessSnap.&pe32)) {
		printf("Failed to retrieve first process \n");
		CloseHandle(InProcessSnap);
		return 1;
	}
	
	printf("%-6s %-6s %-8s %-10s %s \n,
		"PID", "PPID", "Threads","Priority","Name");
	printf("----------------------------------------------------------")
	
	do {
		DWORD pid = pe32.th32ProcessID;
		DWORD ppid = pe32.th32ParentProcessID;
		DWORD basePriority = pe32.pcPriClassBase;
		
		int threadCount = count_threads_for_pid(pid);
		
		printf("%-6lu %-6lu %-8d %-10ld %ws \n",
			pid, ppid, threadCount, basePriority, pe32.szExeFile);
	}while (Process32Next(hProcessSnap, &pe32));
	
	CloseHandle(hProcessSnap);
	return 0;
}
