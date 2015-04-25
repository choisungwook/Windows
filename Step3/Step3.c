// 3_윈도우객체

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

int main()
{
	HWND hwnd = FindWindowA(0, "계산기");
	printf("계산기 번호 : %x\n", hwnd);

	//윈도우는 결국 구조체입니다
	//구조체 항목중 style 필드를 얻어 옵니다
	//핸들만 알면 됩니다.
	int style = GetWindowLong(hwnd, GWL_STYLE);

	//style필드를 조작합니다. 각스타일은 1비트입니다
	//비트 연산으로 합니다
	style = style | WS_THICKFRAME;
	style = style | WS_CAPTION;

	SetWindowLong(hwnd, GWL_STYLE, style);

	//스타일을 변경한 경우는 반드시 강제로 다시 그리게 해야 합니다.
	SetWindowPos(hwnd, 0, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);

	//함수 이름에 너무 신경쓰지 말고 흐름을 파악하세요
	//계산기 실행한 후에 size조절 안되는거 확인하세요
	// 이 프로그램 실행 한 후에 다시 size를 조절해보세요
}
