#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/planeCut.hh"




 axCut::axCut(axesName_t name_, x_slope_t slope_, x_offset_t offset_) :m_name(std::move(name_)), m_slope(slope_), m_offset(offset_) {

 }

 axCut::axCut(axesName_t name_) : m_name(std::move(name_)) {

 }

 axCut::axCut(const axCut& rhs): m_name(rhs.m_name),m_hit(rhs.m_hit), m_slope(rhs.m_slope),m_offset(rhs.m_offset) {
   
 }

 

 double axCut::getValue() const {
   return necessary_CONVERSION(m_slope)* (*m_hit) + necessary_CONVERSION(m_offset);
 }

 bool axCut::register_plane(planeCut& pl) {
   m_hit = pl.getAxis(m_name);
   return true;
 }

 axesName_t axCut::getName() const {
   return m_name;
 }
 axCut axCut::add(double value) {
   return axCut(m_name, m_slope, m_offset + x_offset_t(value));
 }
 axCut axCut::multiply(double value) {
   return axCut(m_name, x_slope_t(value*  necessary_CONVERSION(m_slope)), x_offset_t(value*  necessary_CONVERSION(m_offset)));
 }







axCut operator+(axCut ax, double offset_) {
  return ax.add(offset_);
}

axCut operator+(double offset_, axCut ax) {
  return ax.add(offset_);
}

axCut x_def() {
  return axCut(axesName_t("x"));
}

axCut y_def() {
  return axCut(axesName_t("y"));
}

axCut operator*(axCut ax, double value) {
  return ax.multiply(value);
}

axCut operator*(double value, axCut ax) {
  return ax.multiply(value);
}

