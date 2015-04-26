//멀티쓰레드
#include <stdio.h>
#include <Windows.h>
bool bWait = true;

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
	bWait = false;
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

	//ExitThread(0); //주쓰레드만 종료
					//다른쓰레드는 계속 실행된다.
	
	//쓰레드가 종료될때까지 대기한다.
	// while (bWait); //절대 안됨.!! CPU를 사용하면서 대기

	///모든 스레드는 종료될떄 스레드 구조체의 signal 필드가 1로변한다
	
	//시그널 필드가 1이 될때까지 현재 스레드를 대기해달라
	//2번째 인자의 시간동안 대기해달라
	WaitForSingleObject(h, INFINITE); // 리눅스 pthread_join()
}
