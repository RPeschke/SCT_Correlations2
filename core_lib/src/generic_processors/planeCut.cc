#include "sct/generic_processors/planeCut.hh"
#include "sct/platform.hh"
#include "sct/internal/ScopeGuard.hh"
#include "sct/internal/sct_exceptions.hh"

planeCut::planeCut(const generic_plane& pl):m_pl(pl) {

}

double* planeCut::getAxis(axesName_t ax) {
  SCOPE_GUARD_START {
    auto p = m_storage[ax];
    if (p) {
      return p.get();
    }

    m_storage[ax] = _MAKE_SHARED0(double);
    m_pl.setHitAxisAdress(ax, m_storage[ax].get());
    return m_storage[ax].get();
  }SCOPE_GUARD_END_RETURN

}



bool planeCut::next() {
  return m_pl.next();
}



