#include <stdio.h>
#include <Windows.h>
#include <conio.h>
void error_handling(char *msg);
void printAttribute(char *msg);

int main()
{
	char *findClass = "지뢰 찾기";
	HWND hwnd = NULL;
	DWORD pid = NULL;
	DWORD tid = NULL;
	HANDLE hProcess = NULL;
	char *windowWidth = (char*)0x01005334;
	char *signature = (char*)0x01005330;
	char *windowHeight = (char*)0x01005338;
	char *arrBase = (char*)0x01005360;
	int i;
	int cnt = 0;

	//지뢰찾기 윈도우핸들을 얻어온다.
	if (!(hwnd = FindWindowA(findClass, 0)))
		error_handling("지뢰를 찾지 못했습니다\n");

	if (!(tid = GetWindowThreadProcessId(hwnd, &pid)))
		error_handling("fail to GetWindowThreadProcessID()\n");

	if (!(hProcess = OpenProcess(PROCESS_VM_READ, 0, pid)))
		error_handling("fail to OpenProcess()\n");

	//_getch();
	char buffer[550] = { 0, };
	char width, height, sig;
	DWORD len = 0;
	ReadProcessMemory(hProcess, windowWidth, &width, sizeof(width), &len); // 가로값 읽기
	ReadProcessMemory(hProcess, windowHeight, &height, sizeof(height), &len); // 세로값 읽기
	ReadProcessMemory(hProcess, signature, &sig, sizeof(sig), &len); // 시그값 읽기

	printf("sig : %x width : %d height : %d\n", sig,width, height);
	
	
	/*
	for (i = 0; i < len; i++){
		if (cnt == 16){
			printf("\n");
			cnt = 0;
		}
		printf("%x ", buffer[i]);
		cnt++;
	}
	*/
	//초급
	if (sig == 0x0a){
		printf("초급\n");
		ReadProcessMemory(hProcess, arrBase, buffer, 288, &len);
	}
	
	//중급
	else if (sig == 0x28){
		printf("중급\n");
		ReadProcessMemory(hProcess, arrBase, buffer, 512, &len);
	}
	//고급
	else{
		printf("고급\n");
		ReadProcessMemory(hProcess, arrBase, buffer, 512, &len);
	}
	
	printAttribute(buffer);
	CloseHandle(hProcess);
	return 0;
}

void printAttribute(char *msg)
{
	int i;
	int cnt = 0;
	int flag = 0;
	for (i = 0; i < strlen(msg); i++){
		if (msg[i] == 0x10){
			if (flag){
				flag = 0;
				printf("\n");
			}
			else
				flag = 1;
			continue;
		}
		if (flag){
			if (msg[i] == 0xffffff8f)
				printf("X");
			else
				printf("O");
		}
		
	}
	
}
void error_handling(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(-1);
}
