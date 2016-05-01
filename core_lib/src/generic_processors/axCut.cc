#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/planeCut.hh"
#include "sct/platform.hh"





 axCut::axCut():m_name(axesName_t("")) {

 }



 axCut::axCut(const axesName_t& name):m_name(name) {

 }



 axCut::axCut(const axCut& rhs) : m_name(rhs.m_name), m_hit(rhs.m_hit) {

 }


 bool axCut::register_plane(planeCut& pl)  {
   m_hit = pl.getAxis(m_name);
   return true;
 }

 double axCut::get_value()  const {
   return *m_hit;
 }

 axCut::~axCut() {

 }









 std::shared_ptr<cutNote> axCut::copy() const  {
   return _MAKE_SHARED1(axCut, *this);
 }


axCut x_def() {
  return axCut(axesName_t("x"));
}

axCut y_def() {
  return axCut(axesName_t("y"));
}




