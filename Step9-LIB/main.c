//4_정적라이브러리사용하기.c

#include <stdio.h>
//정적라이브러리를 사용하는 2단계 규칙
#include "math.h" //컴파일시 필요

#pragma comment(lib,"math.lib") // 2.lib 포함
								// 링킹시 필요

int main()
{
	int n = add(10, 20);
	printf("결과 :%d\n", n);
}
