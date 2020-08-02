
#include "TSystem.h"
#include "TInterpreter.h"

#include <iostream>
#include <string>



#ifndef WIN32



struct __dummy_lib_load1 {
  __dummy_lib_load1() {

    gInterpreter->ProcessLine("#define  var(x)  ___set_GName( processorName_t(#x)); auto x ");


    gInterpreter->ProcessLine("namespace ArggLib { namespace ArggLib_impl {  enum _unew_1 { __unew_start1  };  template <typename T> auto operator<<(_unew_1, T* in_) ->decltype(std::unique_ptr<T>(in_)) {  return std::unique_ptr<T>(in_); } enum _Snew_1 { __Snew_start1 };       template <typename T>       auto operator<<(_Snew_1, T* in_) -> decltype(std::shared_ptr<T>(in_)) {         return std::shared_ptr<T>(in_);       }    }  }");
  
    gInterpreter->ProcessLine("#define Unew ArggLib::ArggLib_impl::__unew_start1 << new ");
    gInterpreter->ProcessLine("#define Snew ArggLib::ArggLib_impl::__Snew_start1 << new ");



    

    gInterpreter->ProcessLine("#define  cross *__correlation_start*");

/*
    gInterpreter->ProcessLine(R"(


#ifndef __CINT__
template<typename... Axes_t>
void dummy(Axes_t... ax) {

}


template<typename Func_t, typename... Axes_t>
lambda_Note  make_lambda_Node_sp(Func_t&& f, std::shared_ptr<Axes_t>&&... ax) {
  auto reg_ = register_plane_f([=](planeCut& pl) {dummy(ax->register_plane(pl)...);});
  auto func_ = Predicate_f0([=]() { return f(ax->get_value()...);});
  return lambda_Note(reg_, func_);
}

template<typename Func_t,typename... Axes_t>
lambda_Note  make_lambda_Node(Func_t&& func_, Axes_t&&... ax) {
  return make_lambda_Node_sp(func_, ax.copy()...);
}

struct lamda_note_helper_1 {
  lamda_note_helper_1(axesName_t names) :m_names(names) {}
  axesName_t  m_names;
  template<typename T>
  lambda_Note operator*(T&& t) {
    return make_lambda_Node(std::forward<T>(t), axCut(m_names));
  }
};

struct lamda_note_helper_2 {
  lamda_note_helper_2(axesName_t names1, axesName_t names2) :m_names1(names1), m_names2(names2) {}
  axesName_t  m_names1;
  axesName_t  m_names2;
  template<typename T>
  lambda_Note operator*(T&& t) {
    return make_lambda_Node(std::forward<T>(t), axCut(m_names1), axCut(m_names2));
  }
};

struct lamda_note_helper_3 {
  lamda_note_helper_3(axesName_t names1, axesName_t names2, axesName_t names3) :m_names1(names1), m_names2(names2), m_names3(names3) {}
  axesName_t  m_names1;
  axesName_t  m_names2;
  axesName_t  m_names3;
  template<typename T>
  lambda_Note operator*(T&& t) {
    return make_lambda_Node(std::forward<T>(t), axCut(m_names1), axCut(m_names2), axCut(m_names3));
  }
};
#define  lambda1(name1) lamda_note_helper_1(axesName_t(#name1)) * [](double name1)  
#define  lambda2(name1, name2) lamda_note_helper_2(axesName_t(#name1),axesName_t(#name2)) * [](double name1,double name2)  
#define  lambda3(name1, name2, name3) lamda_note_helper_3(axesName_t(#name1),axesName_t(#name2),axesName_t(#name3)) * [](double name1,double name2,double name3)  

)");
*/
  }

}___asdkl__;

#endif // !WIN32