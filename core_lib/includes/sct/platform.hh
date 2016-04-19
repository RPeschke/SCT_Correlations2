#ifndef platform_h__
#define platform_h__



#ifdef WIN32 
#ifndef __CINT__
#define DllExport   __declspec( dllexport )
#else
#define DllExport   
#endif // __CINT__
#else 
#define DllExport   
#endif // WIN32


#ifdef _DEBUG


#define _MAKE_SHARED0(x) std::shared_ptr<x>(new x())
#define _MAKE_SHARED1(x,...) std::shared_ptr<x>(new x(__VA_ARGS__))


#else
#define _MAKE_SHARED0(x) std::make_shared<x>()
#define _MAKE_SHARED1(x,...) std::make_shared<x>(__VA_ARGS__)



#endif // _DEBUG



#endif // platform_h__
