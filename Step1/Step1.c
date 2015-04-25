//가상메모리

#include <stdio.h>
#include <Windows.h>

int x = 0;
int main()
{
	printf("exe 주소 :  %p\n", GetModuleHandleA(0));
	printf("kernel32.dll 주소 :  %p\n", GetModuleHandleA("kernel32.dll"));
	printf("msvcr120d.dll 주소 :  %p\n", GetModuleHandleA("msvcr120d.dll"));
	printf("전역변수 주소 :  %p\n", &x);
	printf("main 함수 주소 : %p\n", &main);
	printf("printf 함수 주소 : %p\n", &printf);

	int n = 0;
	printf("지역변수 주소 : %p\n", &n);
}
