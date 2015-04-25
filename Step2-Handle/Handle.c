// 2_핸들의개념

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

int main()
{
	//계산기 변경
	//HWND hwnd = FindWindowA(0, "계산기"); // 윈도우 클래스이름, 캡션 문자열

	//시작버튼을 가진 윈도우의 핸들(번호)를 얻는 방법
	HWND hwnd = FindWindowA("Shell_TrayWnd", 0);

	_getch();	MoveWindow(hwnd, 10, 10, 700, 700, true);
	_getch();	ShowWindow(hwnd, SW_HIDE);
	_getch();	ShowWindow(hwnd, SW_SHOW);
	
	_getch();	SetMenu(hwnd, 0);
	_getch();

	HRGN h = CreateEllipticRgn(0, 0, 700, 700);
	SetWindowRgn(hwnd, 0, TRUE);

	printf("계산기 윈도우 핸들(번호) : %x\n", hwnd);

}
