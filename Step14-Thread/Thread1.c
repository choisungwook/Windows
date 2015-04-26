//멀티쓰레드
#include <stdio.h>
#include <Windows.h>

void delay()
{
	for (int i = 0; i < 50000000; i++);
}

DWORD __stdcall foo(void *p)
{
	int x = 0;
	for (int i = 0; i < 10; i++)
	{
		x = 100; delay();
		x = x + 1; delay();
		printf("%s : %d\n", p, x); delay();
	}
	
	printf("%s finish\n", p);
	return 0;
}

int main()
{
	//foo("A");
	HANDLE h = CreateThread(0, 0, //보안, 스택크기(0:1M)
		foo, "A", //스레드 함수, 인자
		0, 0); //플래그, ID를 담을변수

	printf("주 스레드는 다른작업 ..\n");

	// return 0; //주쓰레드가 return 0 ==> 프로세스의 종료
				//return 0을 적지 않아도 return 0이 있는것과 동일
				//표준정의에 main함수는 안적으면 자동으로 적는다.

	ExitThread(0); //주쓰레드만 종료
					//다른쓰레드는 계속 실행된다.
}
