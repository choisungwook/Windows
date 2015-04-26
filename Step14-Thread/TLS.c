#include <stdio.h>
#include <Windows.h>
#include <conio.h>

//3의 배수를 차례대로 리턴하는 함수를 생각해 봅시다
int next3times()
{
	//int n = 0;
	//static int n = 0; //함수 종료시 남아있다
					  //모든 쓰레드가 공유

	//TLS(Thread local Sotrage), TSS(Thread Specific Sotrage)
	//스레드당 한개의 static 메모리 공간
	//모든 OS가 지원한다.(java,c#등에도 있는 개념)
	__declspec(thread) static int n = 0;
	n = n + 3;
	return n;
}

DWORD __stdcall foo(void *p)
{
	printf("%s : %d\n", p, next3times());
	printf("%s : %d\n", p, next3times());
	printf("%s : %d\n", p, next3times());
	printf("\n");
	return 0;
}

int main()
{
	HANDLE h1 = CreateThread(0, 0, foo, "A", 0, 0);
	HANDLE h2 = CreateThread(0, 0, foo, "B", 0, 0);
	HANDLE h[2] = { h1, h2 };
	WaitForMultipleObjects(sizeof(h)/sizeof(h[1]), h, TRUE, INFINITE);
	return 0;
}
