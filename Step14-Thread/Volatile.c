#include <Windows.h>
#include <stdio.h>
#include <conio.h>

//volatile : 컴파일러가 함부러 최적하 하지말라
//			  멀티스레드 사이에서 공유되는 변수
//			H/W와 연결된 변수등을 만들때 사용

DWORD __stdcall foo(void *p)
{
	volatile int *pn = (int*)p;
	while (*pn); // Release모드에서는 while(1); 라고 변합니다.
	printf("foo 종료\n");
	return 0;
}

int main()
{
	int n = 1;
	HANDLE h1 = CreateThread(0, 0, foo, &n, 0, 0);
	_getch();
	n = 0;
	WaitForSingleObject(h1, INFINITE);
	printf("주스레드 종료\n");
}
