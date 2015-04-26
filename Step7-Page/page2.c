//가상메모리2
#pragma warning (disable : 4996)
#include <stdio.h>
#include <Windows.h>
#include <string.h>

struct CELL{
	char data[4091];
};

int main()
{
	//만개의 셀을 예약만 합니다.
	CELL* pTable = (CELL*)VirtualAlloc(0,
		sizeof(CELL) * 10000, MEM_RESERVE,
		PAGE_NOACCESS); //예약만할때는 보통 이속성을 사용합니다.

	printf("예약된 주소 : %p\n", pTable);
	while (1){
		int index;
		char s[4091] = { 0, };
		printf("index >> "); scanf("%d", &index);
		printf("data  >> "); scanf("%s", s);

		//table에  data복사
		__try{
			strcpy(pTable[index].data, s);
		}
		__except (1){
			//확정한 후에 다시 복사해준다.
			VirtualAlloc(&pTable[index], sizeof(CELL),
				MEM_COMMIT, PAGE_READWRITE);
			printf("할당된 주소 : %p\n", &pTable[index]);
			strcpy(pTable[index].data, s);
			printf("%d CELL확정\n", index);
		}
		
	}

	return 0;
}
