#include "sct/generic_processors/axCutHandle.hh"
#include "sct/generic_processors/planeCut.hh"


bool axCutHandle::register_plane(planeCut& pl) {
  m_Ax->register_plane(pl);
  return true;
}

double axCutHandle::get_value() const {
  return m_predicate(m_Ax->get_value());
}



std::shared_ptr<cutNote> axCutHandle::copy() const {
  return _MAKE_SHARED1(axCutHandle, *this);
}



axesName_t axCutHandle::get_name() const
{
  throw std::logic_error("The method or operation is not implemented.");
}

axCutHandle::axCutHandle(axCut name, Predicate_f fun) :m_Ax(_MAKE_SHARED1(axCut, name)), m_predicate(std::move(fun)) {

}

axCutHandle::axCutHandle(const axCutHandle& rhs):m_Ax(_MAKE_SHARED1(axCut, *rhs.m_Ax)),m_predicate(rhs.m_predicate) {

}





axCutHandle axCutHandle::operator=(const axCutHandle& rhs) {
  m_Ax = _MAKE_SHARED1(axCut, *rhs.m_Ax);
  m_predicate = rhs.m_predicate;
  return *this;
}

