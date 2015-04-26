// 7_DLL의 명시적 연결
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

//DLL의 암시적 연결
//#include "math2.h "
//#pragma commnet(lib,"math2.lib") //이코드때문에 .idata 섹션에 dll의 이름을 들어가게 됩니다.
								//exe를 실행시 DLL이 따라서 Load됩니다.


//DLL의 명시적 연결
//DLL이 필요할때 LoadLibrary()함수로 load하는 것
int main()
{
	_getch();
	HMODULE h = LoadLibraryA("math2.dll");

	printf("load된 주소 %p\n", h);

	_getch();
	//Load된 DLL에서 특정 함수의 주소를 찾는방법
	//함수의 모양을 미리 알고 있어야 한다.

	typedef int(*F)(int, int);

	F f = (F)GetProcAddress(h, "add");
	printf("add 함수 주소 : %p, %d\n", f, f(1, 2));
	_getch();

	FreeLibrary(h);
	return 0;
}
