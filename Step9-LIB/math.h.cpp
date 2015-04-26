//math.h

//math.lib 제작자는 사용자를 위해서
//함수 선언을 담고 있는 헤더를 제공해야 한다.

//extern "C" : c++ 컴파일러에게 C함수라고 알려주는것
//심볼(함수, 변수 이름)의 name mangling을 막을때 사용
//

extern "C"
int add(int a, int b);
int sub(int a, int b);
