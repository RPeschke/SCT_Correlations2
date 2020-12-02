#ifndef lambda_Note_h__
#define lambda_Note_h__

#include "sct/generic_processors/cutNote.hh"
#include <memory>
#include <vector>
#include "axCut.hh"
#include "../generic_plane.hh"

class DllExport lambda_Note : public cutNote {
public:
  lambda_Note();
  virtual bool register_plane(planeCut& pl);;
  virtual double get_value() const;
#ifndef __CINT__
  virtual std::vector<generic_plane*> get_planes() ;
  lambda_Note(register_plane_f reg_, Predicate_f0  cut_, get_plane_f pl);
  virtual std::shared_ptr<cutNote> copy() const;
  register_plane_f m_reg;
  Predicate_f0 m_cut;
  generic_plane m_plane;
  get_plane_f m_get_pl;
  std::vector<std::shared_ptr<cutNote>> m_notes;
#endif
};
#ifndef __CINT__
template<typename... Axes_t>
void dummy(Axes_t... ax) {

}


inline void append_gen_plane_list(std::vector<generic_plane*> & pl_list) {

}

template<typename T1, typename... Axes_t>
void append_gen_plane_list(std::vector<generic_plane*> & pl_list,T1 ax1,  Axes_t... ax) {
  auto p1 = ax1->get_planes();
  for (auto & e : p1) {
    pl_list.push_back(e);
  }
  append_gen_plane_list(pl_list, ax...);
}

template<typename Func_t, typename... Axes_t>
lambda_Note  make_lambda_Node_sp(Func_t&& f, std::shared_ptr<Axes_t>&&... ax) {
  auto reg_ = register_plane_f([=](planeCut& pl) {dummy(ax->register_plane(pl)...);});
  auto func_ = Predicate_f0([=]() { return f(ax->get_value()...);});
  auto get_pl = get_plane_f([=]() {
    std::vector<generic_plane*> ret; 
    append_gen_plane_list(ret,  ax...);
    return ret; }
   );
  return lambda_Note(reg_, func_, get_pl);
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
struct lamda_note_helper_4 {
  lamda_note_helper_4(axesName_t names1, axesName_t names2, axesName_t names3, axesName_t names4) :m_names1(names1), m_names2(names2), m_names3(names3), m_names4(names4) {}
  axesName_t  m_names1;
  axesName_t  m_names2;
  axesName_t  m_names3;
  axesName_t  m_names4;
  template<typename T>
  lambda_Note operator*(T&& t) {
    return make_lambda_Node(std::forward<T>(t), axCut(m_names1), axCut(m_names2), axCut(m_names3), axCut(m_names4));
  }
};

struct lamda_note_helper_5 {
  lamda_note_helper_5(axesName_t names1, axesName_t names2, axesName_t names3, axesName_t names4, axesName_t names5) 
    :m_names1(names1), m_names2(names2), m_names3(names3), m_names4(names4), m_names5(names5) {}
  axesName_t  m_names1;
  axesName_t  m_names2;
  axesName_t  m_names3;
  axesName_t  m_names4;
  axesName_t  m_names5;
  template<typename T>
  lambda_Note operator*(T&& t) {
    return make_lambda_Node(std::forward<T>(t), axCut(m_names1), axCut(m_names2), axCut(m_names3), axCut(m_names4), axCut(m_names5));
  }
};


struct lamda_note_helper_6 {
  lamda_note_helper_6(axesName_t names1, axesName_t names2, axesName_t names3, axesName_t names4, axesName_t names5, axesName_t names6)
    :m_names1(names1), m_names2(names2), m_names3(names3), m_names4(names4), m_names5(names5), m_names6(names6) {}
  axesName_t  m_names1;
  axesName_t  m_names2;
  axesName_t  m_names3;
  axesName_t  m_names4;
  axesName_t  m_names5;
  axesName_t  m_names6;
  template<typename T>
  lambda_Note operator*(T&& t) {
    return make_lambda_Node(std::forward<T>(t), axCut(m_names1), axCut(m_names2), axCut(m_names3), axCut(m_names4), axCut(m_names5), axCut(m_names6));
  }
};


#define  lambda1(name1) lamda_note_helper_1(axesName_t(#name1)) * [&](double name1)  
#define  lambda2(name1, name2) lamda_note_helper_2(axesName_t(#name1),axesName_t(#name2)) * [&](double name1,double name2)  
#define  lambda3(name1, name2, name3) lamda_note_helper_3(axesName_t(#name1),axesName_t(#name2),axesName_t(#name3)) * [&](double name1,double name2,double name3)  
#define  lambda4(name1, name2, name3, name4) lamda_note_helper_4(axesName_t(#name1),axesName_t(#name2),axesName_t(#name3),axesName_t(#name4)) * [&](double name1,double name2,double name3,double name4)  
#define  lambda5(name1, name2, name3, name4, name5) lamda_note_helper_5(axesName_t(#name1),axesName_t(#name2),axesName_t(#name3),axesName_t(#name4),axesName_t(#name5)) * [&](double name1,double name2,double name3,double name4,double name5)  
#define  lambda6(name1, name2, name3, name4, name5, name6) lamda_note_helper_6(axesName_t(#name1),axesName_t(#name2),axesName_t(#name3),axesName_t(#name4),axesName_t(#name5),axesName_t(#name6)) * [&](double name1,double name2,double name3,double name4,double name5,double name6)  


#endif
#endif // lambda_Note_h__
