#ifndef lambda_Note_h__
#define lambda_Note_h__
#ifndef __CINT__
#include "sct/generic_processors/cutNote.hh"
#include <memory>
#include <vector>

class DllExport lambda_Note : public cutNote {
public:
  lambda_Note(register_plane_f reg_, Predicate_f0  cut_);
  virtual void register_plane(planeCut& pl);;
  virtual bool operator()() const;;
  virtual std::shared_ptr<cutNote> copy() const;;
  register_plane_f m_reg;
  Predicate_f0 m_cut;

  std::vector<std::shared_ptr<cutNote>> m_notes;
};

template<typename... Axes_t>
void dummy(Axes_t... ax) {

}


template<typename Func_t, typename... Axes_t>
auto  make_lambda_Note_sp(Func_t&& f, std::shared_ptr<Axes_t>&&... ax) {
  auto reg_ = register_plane_f([=](planeCut& pl) {dummy(ax->register_plane(pl)...);});
  auto func_ = Predicate_f0([=]() { return f(ax->getValue()...);});
  return lambda_Note(reg_, func_);
}

template<typename Func_t,typename... Axes_t>
auto  make_lambda_Note(Func_t&& func_, Axes_t&&... ax) {
  return make_lambda_Note_sp(func_, _MAKE_SHARED1(Axes_t, ax)...);
}


#endif
#endif // lambda_Note_h__
