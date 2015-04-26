//3_heap
#include <Windows.h>
#include <stdio.h>

int main()
{
	//모든 프로세스는 기본 힙을 하나씩 갖고 있다.
	HANDLE h1 = GetProcessHeap();

	//힙을 추가로 만들 수도 있다.
	HANDLE h2 = HeapCreate(0, 1024 * 1024, //초기크기
		0); //최대크기(자동증가)

	void *p1 = HeapAlloc(h1, HEAP_ZERO_MEMORY, 100); //100바이트 할당하고 0으로 초기화
	void *p2 = HeapAlloc(h2, HEAP_ZERO_MEMORY, 100);
	void* p3 = malloc(100);
	void *p4 = new char[100];

	printf("기본 힙 핸들(주소) : %p\n", h1);
	printf("새로운 힙 핸들(주소) : %p\n", h2);

	printf("기본힙에서 할당된 메모리 : %p\n", p1);
	printf("새로운힙에서 할당된 메모리 : %p\n", p2);
	printf("malloc 할당된 메모리 : %p\n", p3);
	printf("new 할당된 메모리 : %p\n", p4);

	printf("===========================================================\n");
	//현재 프로세스의 모든 힙을 열거한다
	HANDLE h[10];
	int cnt = GetProcessHeaps(10, h);
	for (int i = 0; i < cnt; i++)
		printf("%d : %p\n", i + 1, h[i]);

	//메모리해제
	HeapFree(h1, 0, p1);
	HeapFree(h2, 0, p2);
	free(p3);
	delete p4;

	//사용자가 만든 힙 파괴
	HeapDestroy(h2);

	//기본힙은 파괴할 필요가 없다.
	return 0;
}
