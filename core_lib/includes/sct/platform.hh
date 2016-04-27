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

#ifdef WIN32
#define SCT_FUNC __FUNCSIG__
#define SCT_FUNC_SHORT  __func__
#else
#define  SCT_FUNC __PRETTY_FUNCTION__
#define SCT_FUNC_SHORT  __FUNCTION__
#endif // WIN32


#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)
#define MAKE_UNIQUE_NAME(x)  CONCATENATE(x, __LINE__)


#endif // platform_h__
