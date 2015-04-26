//8 API후킹
#include <Windows.h>
#include <stdio.h>

//MessageBoxA를 가로챌 함수 - 함수 모양을 동일해야 합니다.
int __stdcall foo(HWND hwnd, char *s1, char *s2, int btn)
{
	printf("foo\n");
	
	//원래 함수에게 보낸다
	//MessageBoxA(hwnd, s1, s2, btn);
	//HMODULE h = GetModuleHandleA("user32.dll");
	//typedef int(__stdcall *F)(HWND, char*, char*, int);
	//F f = (F)GetProcAddress(h, "MessageBoxA");

	//원래함수 2번째 3번째 인자 변경
	//return f(hwnd, s2, s1, btn);
	return 0;
}

int main()
{
	//.exe의 .idata 섹션에 있는 IAT(import Address table)에서
	// MessageBoxA 주소를 담은 곳을 후킹합니다.
	*((int*)0x00418144) = (int)&foo;
	
	
	MessageBoxA(0, "aa", "bb", 0); //user32.dll에 있다.
}
