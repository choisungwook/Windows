//2. 가상메모리
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
int main()
{
	const int size = 1024 * 1024 * 100;

	char *p1 = (char*)VirtualAlloc((void*)0x0,  //원하는 주소(64k배수) 뒤의 4개가 0으로 끝나야한다.
												//0은 가능한 가장 낮은 주소를 자동할당
		size * 10, //원하는 크기(4k배수)
		MEM_RESERVE, //예약만
		PAGE_READWRITE); //보호 속성

	printf("예약된 주소 : %p\n", p1);
	//*p1 = 'a'; // 예약된 주소 사용. 아직 물리공간이 연결된것은 아니다.
	char *p2 = p1;
	for (int i = 0; i < 10; i++){
		//주소를 물리메모리와 연결한다.
		_getch();
		char *p3 = (char*)VirtualAlloc(p2, size, MEM_COMMIT, PAGE_READWRITE);
		printf("확정된 주소 : %p\n", p3);
		p2 = p2 + size;
	}

	VirtualFree(p2, size * 10, MEM_DECOMMIT);
	VirtualFree(p2, 0, MEM_RELEASE);
	//while (1){};
	return 0;
}

//프로젝트 메뉴 -> 속성 -> 구성속성 - 링커 - 고급에서
//임의 주소 사용을 아니오로 해주세요
