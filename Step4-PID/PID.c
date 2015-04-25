//6.프로세스ID

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

//모든 프로세스는 실행되면 EPROCESS구조체가 만들어집니다.
//EPROCESS 구조체 안에는 고유한 ID 값이 있습니다.

int main()
{
	printf("현재 프로세스 ID : %d\n", GetCurrentProcessId());

	//다른프로세스 ID를 구하는 방법
	//1. 윈도우 핸들을 구한후에
	HWND hwnd = FindWindowA(0, "계산기");
	
	//2. 해당 윈도우를 만든 프로세스의 ID를 구합니다
	DWORD pid;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	printf("계산기의 프로세스 ID : %d\n", pid);
	
	//계산기의 PID만을 가지고는 계산기에 접근해서 많은 일을 할 수 없다.

	//계산기에 접근하기 위해 OS에게 프로세스핸들을 발급받습니다.
	//보안에 따라 거부될수있습니다.
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, pid);
	printf("발급된 핸들 : %x\n", hProcess);
	_getch();
	TerminateProcess(hProcess,0);

	//발근된 핸들은 사용한 후에는 닫아야 합니다.
	CloseHandle(hProcess);

}
