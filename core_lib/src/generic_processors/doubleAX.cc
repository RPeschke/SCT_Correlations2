#include "sct/generic_processors/doubleAX.hh"

doubleAX::doubleAX(axCut nameA, axCut nameB, Predicate_f2 fun) :m_axA(_MAKE_SHARED1(axCut,nameA)), m_axB(_MAKE_SHARED1(axCut, nameB)),m_predicate(fun) {

}




doubleAX::doubleAX(const doubleAX& rhs):m_axA(_MAKE_SHARED1(axCut, *rhs.m_axA)) , m_axB(_MAKE_SHARED1(axCut,*rhs.m_axB)) , m_predicate(rhs.m_predicate) {

}



doubleAX doubleAX::operator=(const doubleAX& rhs) {
  m_axA= _MAKE_SHARED1(axCut, *rhs.m_axA);
  m_axB= _MAKE_SHARED1(axCut, *rhs.m_axB);
  m_predicate=rhs.m_predicate;
  return *this;
}

void doubleAX::register_plane(planeCut& pl) {
  m_axA->register_plane(pl);
  m_axB->register_plane(pl);
}

bool doubleAX::operator()() const {
  return m_predicate(m_axA->getValue(), m_axB->getValue());
}

std::shared_ptr<cutNote> doubleAX::copy() const {
  return _MAKE_SHARED1(doubleAX, *this);
}

doubleAX operator<(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA < hitB;});
}



doubleAX operator<=(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA <= hitB;});
}



doubleAX operator>(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA > hitB;});
}



doubleAX operator>=(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA >= hitB;});
}

doubleAX operator==(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA == hitB;});
}


doubleAX operator!=(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA != hitB;});
}

