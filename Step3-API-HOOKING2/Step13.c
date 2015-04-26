#pragma warning (disable : 4996)
#include <Windows.h>
#include <stdio.h>
#include <string.h>

//PE포맷을 조사하는 함수는 Dbghelp.dll에 있습니다
#include <DbgHelp.h>
#pragma comment(lib,"dbghelp.lib")

void Replace(HMODULE hExe, const char* dllname, DWORD api, DWORD func)
{
	//1.실행파일 주소(hExe)에서 IAT의 주소를 찾는다
	ULONG size = 0;
	IMAGE_IMPORT_DESCRIPTOR* pImage = (IMAGE_IMPORT_DESCRIPTOR*)
		::ImageDirectoryEntryToData(hExe, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &size);
	printf("IAT의 주소 %p\n", pImage);

	//-----------------------------------------------------------------
	//원하는 DLL의 항목을 관리하는 곳을 찾는다
	for (; pImage->Name != 0; pImage++){
		char *s = ((char*)hExe + pImage->Name);
		if (strcmpi(s, dllname) == 0)
			break;
	}

	if (pImage->Name == 0)
		printf("%s DLL을 사용하지 않습니다\n", dllname);
	else
		printf("%s DLL을 관리하는 항목 : %p\n", dllname, pImage);

	//----------------
	//함수 주소 table에서 원하는 항목을 찾아서 덮어 쓴다
	IMAGE_THUNK_DATA* pThunk = (IMAGE_THUNK_DATA*)
		((char*)hExe + pImage->FirstThunk);

	for (; pThunk->u1.Function != 0; pThunk++){
		DWORD *p = &(pThunk->u1.Function);
		//p메모리 보호속성을 변경합니다.
		DWORD old;
		VirtualProtect(p, sizeof(DWORD), PAGE_READWRITE, &old);
		*p = func; //덮어쓴다

		//예전 보호속성으로 다시 변경
		VirtualProtect(p, sizeof(DWORD), old, &old);
		
	}
}

int __stdcall foo(HWND hwnd, char *s1, char *s2, int btn)
{
	printf("foo\n");

	//MessageBoxA(hwnd, s1, s2, btn);
	HMODULE h = GetModuleHandleA("user32.dll");
	typedef int(__stdcall *F)(HWND, char*, char*, int);
	F f = (F)GetProcAddress(h, "MessageBoxA");
		
	return f(hwnd, s2, s1, btn);	
}

int main()
{
	Replace(GetModuleHandle(0), //exe주소
		"user32.dll", //후킹할 함수가 있는 dll
		(DWORD)MessageBoxA, //후킹할 API
		(DWORD)foo); //사용자 함수

	MessageBoxA(0, "aa", "bb", 0); //user32.dll에 있다.
	return 0;
}
