#ifndef factory_h__
#define factory_h__

#include <map>
#include <vector>
#include <memory>
#ifdef WIN32
  #define CLASSFACTORY_DLLEXPORT  __declspec( dllexport ) 
  #include <stdint.h>
#else
  #define CLASSFACTORY_DLLEXPORT  
#endif

#define registerClass(baseClass,derivedClass,identifier)    namespace {static Class_factory_Utilities::Registerbase<baseClass,derivedClass> reg##derivedClass(identifier); } int Class_factory_DUMMY_VARIABLE_DO_NOT_USE##derivedClass=0 


#define RegisterSmartClass(baseClass,derivedClass)  registerClass(baseClass,derivedClass,derivedClass::id())
//#define RegisterBaseClass(baseClass) baseClass::u_pointer create_##baseClass(const baseClass::Parameter_t & par){return EUDAQ_Utilities::Factory<baseClass>::Create(par);}



namespace Class_factory_Utilities{

  template <typename baseClassType>
  class CLASSFACTORY_DLLEXPORT Factory {
  public:

    using MainType = typename baseClassType::MainType;
    using MainType_V = std::vector < MainType > ;
    using Parameter_t = typename baseClassType::Parameter_t;
    using Parameter_ref = typename baseClassType::Parameter_ref;
    using u_pointer = std::unique_ptr < baseClassType > ;

    typedef baseClassType* (*factoryfunc_raw)(Parameter_ref);
#ifdef WIN32
    using map_t = std::map <typename MainType,typename  Factory<baseClassType>::factoryfunc_raw > ;
#else
    using map_t = std::map < MainType, Factory<baseClassType>::factoryfunc >;
#endif


    static u_pointer Create(const MainType & name, Parameter_ref params);
    template <typename T>
    static void Register(const MainType &  name) {
      do_register(name, basefactory<T>);
    }
    static MainType_V GetTypes();

    template <typename T>
    static baseClassType* basefactory(Parameter_ref params) {
      return new T(params);
    }


    static void do_register(const MainType & name, factoryfunc_raw func) {
      getInstance()[name] = func;
    }

    static map_t& getInstance(); 

  };


  template <typename baseClass, typename DerivedClass>
  class CLASSFACTORY_DLLEXPORT Registerbase {
  public:
    using MainType = typename baseClass::MainType;

    Registerbase(const MainType & name) {
      Factory<baseClass>::template Register<DerivedClass>(name);
    }
  };

//   template<typename BaseClass>
//   typename BaseClass::u_pointer create(typename BaseClass::MainType& name, 
//                                        typename BaseClass::Parameter_ref param){
// 
//     return Factory<BaseClass>::Create(name, param);
//   }
}
#endif // factory_h__
