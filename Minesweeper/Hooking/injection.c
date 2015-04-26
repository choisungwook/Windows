#include <stdio.h>
#include <Windows.h>

void DLL_Injection(DWORD pid, const char* dllname)
{
	// 프로세스 ID ==> 프로세스 핸들
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	//printf("핸들 :%x\n", hProcess);
	
	//-----------------------------
	//LoadLibrary의 주소를 찾는다
	HMODULE hMod = GetModuleHandleA("kernel32.dll");
	typedef DWORD(__stdcall *F)(void*);

	F f = (F)GetProcAddress(hMod, "LoadLibraryA");
	printf("LoadLibraryA의 주소 %p\n", f);

	//지뢰 찾기에 가상메모리를 할당한다
	void* addr = VirtualAllocEx(hProcess, 0, 4096,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	DWORD len;
	WriteProcessMemory(hProcess, addr, dllname, strlen(dllname) + 1, &len);
	printf("addr : %x\n", addr);
	//-------------------------------------------
	//지뢰찾기에서 새로운 스레드를 생성한다.
	HANDLE hThread = CreateRemoteThread(hProcess, 0, 0,
		f, addr, //스레드함수, 인자
		0, 0);
}

int main()
{
	HWND hwnd = FindWindowA(0, "지뢰 찾기");
	
	DWORD pid;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	printf("지뢰찾기 : pid : %d\n", pid);
	DLL_Injection(pid, "c:\\spy.dll");

	return 0;
}
