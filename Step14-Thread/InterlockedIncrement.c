#include <Windows.h>
#include <stdio.h>
#include <conio.h>

long x = 0; //모든 쓰레드가 공유

DWORD __stdcall foo(void *p)
{
	for (int i = 0; i < 100000; i++){
		//x = x + 1;
		//위 한줄은 아래 어셈을 생성합니다
		/*
		__asm{
			mov eax, x
			add eax, 1
			mov x, eax
		}
		*/
		/*
		//inc 명령은 실행중 context switch가 발생하지 않습니다.
		//조건 : 코어 1개일 경우
		__asm{
			inc x
		}
		*/
		//lock : 하나의 PCU가 사용하는 메모리를 
		//		다른 CPU가 사용하지 못하게 하는 prefix
		//		명령에 앞에 붙이는것
		//		다중 CPU만 사용
		/*
		__asm{
			lock inc x
		}
		*/
		//위 어셈코드로 구현;
		InterlockedIncrement(&x);
		//x = 0; 멀티스레드에서는 이렇게 도 안됩니다.
		//InterlockedExchange(&x, 0);

		//lock Free : 락(동기화객체)를 사용하지 말자는것
		//		실전 : OS의 동기화 도구를 사용하지 말자
		//		CPU의 기본 lock명령만으로 멀티스레드에 안전한
		//		자료구조를 만드는 개념
	}
	return 0;
}

int main()
{
	HANDLE h[3] = {
		CreateThread(0, 0, foo, 0, 0, 0),
		CreateThread(0, 0, foo, 0, 0, 0),
		CreateThread(0, 0, foo, 0, 0, 0)
	};

	WaitForMultipleObjects(3, h, TRUE, INFINITE);
	printf("결과 :%d\n", x);
}
