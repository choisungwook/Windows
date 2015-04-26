#include <stdio.h>
#include <Windows.h>

int a = 0;

int main()
{
	int s = 10;

	__try{
		//s = s / a;
		char *p = 0;
		*p = 'a';
	}
	__except (1){
		printf("예외 발생 : %x\n",GetExceptionCode());
	}

	return 0;
}
