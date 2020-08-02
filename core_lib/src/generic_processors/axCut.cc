#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/planeCut.hh"
#include "sct/platform.hh"
#include <algorithm>





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




unique_ax::unique_ax() :m_name(axesName_t(""))
{

}

unique_ax::unique_ax(const unique_ax& rhs) : m_name(rhs.m_name), m_hit(rhs.m_hit)
{

}

unique_ax::unique_ax(const axesName_t& name) : m_name(name)
{

}

bool unique_ax::register_plane(planeCut& pl) 
{
  m_hit = pl.getAxis(m_name);
  return true;
}

void unique_ax::onNewEvent() 
{
  m_elements.clear();
}

bool contains_element1(std::vector<double> const& items, double const& item)
{
  return std::find(items.begin(), items.end(), item) != items.end();
}
double unique_ax::get_value() const 
{
  if (!contains_element1(m_elements, *m_hit)) {
    m_elements.push_back(*m_hit);
    return 1;
  }
  return 0;
}

unique_ax::~unique_ax() 
{

}

std::shared_ptr<cutNote> unique_ax::copy() const 
{
  return Snew unique_ax(*this);
}
