//math2.h


#ifdef DLLSOURCE
	#define DLLAPI __declspec(dllexport)
#else
	#define DLLAPI __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif
	DLLAPI int add(int a, int b);
#ifdef __cplusplus
}
#endif

//www.dependencywalker.com
