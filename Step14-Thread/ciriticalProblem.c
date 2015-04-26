//멀티쓰레드
#include <stdio.h>
#include <Windows.h>

CRITICAL_SECTION cs; //cs에는 하나의 스레드만 들어갈 수 있다.

void delay()
{
	for (int i = 0; i < 10000000; i++);
}

DWORD __stdcall foo(void *p)
{
//	int x = 0;
	static int x = 0;
	for (int i = 0; i < 20; i++)
	{
		//Serialization : 직렬화
		EnterCriticalSection(&cs); //cs에 들어간다
		//------------------------
		x = 100; delay();
		x = x + 1; delay();
		printf("%s : %d\n", p, x); delay();
		//--------------------
		LeaveCriticalSection(&cs); //cs에 나온다.
	}

	printf("%s finish\n", p);
	
	return 0;
}

int main()
{
	InitializeCriticalSection(&cs);
	//foo("A");
	HANDLE h1 = CreateThread(0, 0, foo, "A", 0, 0);
	HANDLE h2 = CreateThread(0, 0, foo, "B", 0, 0);

	//2개이상의 스레드를 대기하는 법
	HANDLE h[2] = { h1, h2 };
	WaitForMultipleObjects(2, h, TRUE, //모두 종료될때까지
		INFINITE);

	DeleteCriticalSection(&cs);
	//리눅스
	//pthread_join(h1)
	//pthread_join(h2)

}
