//4_핸들의정채
//HWND 핸들의 정체는 뭘까요

//핸들은 사물의 고유한 번호이다
// 32bit 정수이므로 int면 될꺼 같다.
// 문제점.. 타입안정성이 떨어진다. 잘못사용해도 컴파일 에러가 나지 않는다.

/*
typedef int HWND;
typedef int HFONT;

void MoveWindow(HWND hwnd, int x, int y){}

int main()
{
	HFONT h = 0; //CreateFont()로 만들었다고 가정하고 
	MoveWindow(h, 0, 0); //잘못사용했다. 에러가 날까?
}

*/


//해결책.. 서로다른 구조체의 주소는 암시적 변환되지 않는다.
struct HWND__{
};

typedef HWND__ *HWND;

struct HFONT__{
};

typedef HFONT__ *HFONT;


void MoveWindow(HWND hwnd, int x, int y){}

int main()
{
	HWND hwnd = (HWND)100;
	HFONT h = (HFONT)0; //CreateFont()로 만들었다고 가정하고 
	MoveWindow(hwnd, 0, 0); //잘못사용했다. 에러가 날까?
}
