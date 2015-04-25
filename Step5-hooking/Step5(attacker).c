#include <stdio.h>
#include <Windows.h>
#include <conio.h>

int main()
{
  //pid is pentest process ID
	int pid = 2148;
	char *addr = (char*)0x0077FA14;

	//가상메모리를 읽기위한 핸들을 얻는다.
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, 0, pid);

	while (1)
	{
		_getch();
		char s[256] = { 0, };

		DWORD len;		
		ReadProcessMemory(hProcess, addr, s, 256, &len);
		printf("읽어온 메모리 내용 >> %s\n", s);
	}

	return 0;

}
