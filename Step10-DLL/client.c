//5 동적라이브러리 사용하기

#include <stdio.h>

//동적라이브러리 사용하기 위한 2단계
#include "math2.h" 1. 헤더포함 - 컴파일 하기 위해

#pragma comment(lib,"math2.lib")

int main()
{
	int n = add(1, 2);
	printf("결과 : %d\n", n);
}

//math2.dll를 다른곳으로 옮겨놓고 test해보세요
// 1. 빌드만 해보세요(ctrl + shift + b)
