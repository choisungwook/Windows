 윈도우 시스템 프로그래밍

윈도우의 정체 : 결국은 OS 입장에서는 구조체이다.
                Windows OS는 대부분의 요소를 구조체를 만들어서 관리한다.
                "객체 기반 OS"

핵심 1. 윈도우의 핸들(번호)만 알면 윈도우를 조작 할 수 있다.
핵심 2. typedef를 많이 쓰는 이유는 호환성 유지
핵심 3. 핸들 : 객체에 접근하기 위한 번호
        윈도우 핸들 : 누구나 바로 얻어서 사용할 수 있다.
        프로세스 핸들 : 먼저 모든 프로세스가 갖는 고유한 ID값을 얻는다.
                        HWND를 구해서 PID를 얻거나 모든 프로세스를 열거해서 얻거나
                        PID를 얻은후에 OpenProcess()함수로 OS에게 핸들을 요청
                        --> 보안 문제로 이렇게 설계
        #if MACHINE_16
        typedef int int16;
        #elif MACHINE_32
        typedef short int16;
        #endif
//P : 포인터  //C : const //W :unicod //STR : char //H : 핸들타입 //U unsigned
PUINT : unsigned int*
PSTR : char *
PCSTR : const char*
PWSTR : wchar_t*
PCWSTR: const wchar_t*
