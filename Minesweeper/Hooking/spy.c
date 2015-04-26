//Spy.cpp

#include <stdio.h>
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "DbgHelp.lib")

// Replace 복사 해오기

void Replace(HMODULE hExe, const char* dllname, DWORD api, DWORD func)
{
	//1. 실행파일 주소(hExe)에서 IAT의 주소를 찾는다.
	ULONG size = 0;
	IMAGE_IMPORT_DESCRIPTOR* pImage = (IMAGE_IMPORT_DESCRIPTOR*)::ImageDirectoryEntryToData(hExe, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &size);

	printf("IAT의 주소 :%p\n", pImage);
	//------------------------------------------------------------
	//원하는 DLL의 항목을 관리하는 곳을 찾는다. 
	for (; pImage->Name != 0; pImage++)
	{
		char* s = ((char*)hExe + pImage->Name); //실행파일주소 + 주소

		if (strcmpi(s, dllname) == 0) break;  // 대소문자 상관없이 비교

	}

	if (pImage->Name == 0)
	{
		printf("%s DLL을 사용하지 않습니다\n", dllname);
	}
	else
	{
		printf("%s DLL을 관리하는 항목 : %p\n", dllname, pImage);
	}

	//--------------------------------------------------------------
	// 함수주소 Table에서 원하는 항목을 찾아서 덮어 쓴다.

	IMAGE_THUNK_DATA* pThunk =
		(IMAGE_THUNK_DATA*)((char*)hExe + pImage->FirstThunk);

	for (; pThunk->u1.Function != 0; pThunk++)
	{
		if (pThunk->u1.Function == api)
		{
			DWORD* p = &(pThunk->u1.Function);

			// p 메모리의 보호속성을 변경합니다.
			DWORD old;
			VirtualProtect(p, sizeof(DWORD), PAGE_READWRITE, &old);

			*p = func; // 덮어쓴다.

			// 예전 보호속성으로 다시 변경
			VirtualProtect(p, sizeof(DWORD), old, &old);
		}
	}
}

// cl Spy.cpp /LD /link user32.lib kernel32.lib
// spy.dll을 c:\\spy.dll 로 복사해 놓으세요

//지뢰찾기 싫ㅇ하세요
//vc에서 spy.cpp 빌드 막고, DLLinjection 소스 실행하세요

//지뢰찾기에서 아무 블럭이나 클릭 후 시간 보세요.


int __stdcall MySetTimer(HWND hwnd, int id, int ms, TIMERPROC timerproc)
{
	//원래 함수를 다시 호출
	typedef int(__stdcall *F)(HWND, int, int, TIMERPROC);

	HMODULE h = GetModuleHandleA("user32.dll");

	F f = (F)GetProcAddress(h, "SetTimer");

	return f(hwnd, id, ms / 50, timerproc);  //핵심 ms/50
}


//모든 DLL은 프로세스의 Load 될때 아래 함수가 호출 됩니다.
BOOL __stdcall DllMain(HANDLE hDll, DWORD r, LPVOID h)
{
	if (r == DLL_PROCESS_ATTACH)
	{
		Replace(GetModuleHandle(0), //지뢰찾기의 실행파일 주소를 찾아서
			"user32.dll",         // user32.dll 관리하는 곳에 가서
			(DWORD)SetTimer,      // SetTimer 를  MySetTimer로 바꿔라.
			(DWORD)MySetTimer
			);
	}
	return TRUE;
}
