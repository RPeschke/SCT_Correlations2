#ifndef lambda_Note_h__
#define lambda_Note_h__

#include "sct/generic_processors/cutNote.hh"
#include <memory>
#include <vector>

class DllExport lambda_Note : public cutNote {
public:
  lambda_Note();
  virtual bool register_plane(planeCut& pl);;
  virtual double get_value() const;;
#ifndef __CINT__
  lambda_Note(register_plane_f reg_, Predicate_f0  cut_);
  virtual std::shared_ptr<cutNote> copy() const;;
  register_plane_f m_reg;
  Predicate_f0 m_cut;

  std::vector<std::shared_ptr<cutNote>> m_notes;
#endif
};
#ifndef __CINT__
template<typename... Axes_t>
void dummy(Axes_t... ax) {

}


template<typename Func_t, typename... Axes_t>
auto  make_lambda_Note_sp(Func_t&& f, std::shared_ptr<Axes_t>&&... ax) {
  auto reg_ = register_plane_f([=](planeCut& pl) {dummy(ax->register_plane(pl)...);});
  auto func_ = Predicate_f0([=]() { return f(ax->get_value()...);});
  return lambda_Note(reg_, func_);
}

template<typename Func_t,typename... Axes_t>
lambda_Note  make_lambda_Note(Func_t&& func_, Axes_t&&... ax) {
  return make_lambda_Note_sp(func_, ax.copy()...);
}


#endif
#endif // lambda_Note_h__
