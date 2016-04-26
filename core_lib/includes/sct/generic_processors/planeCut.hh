#ifndef planeCut_h__
#define planeCut_h__
#include "sct/generic_plane.hh"
#ifndef __CINT__
#include <map>
#include <memory>
#endif

class planeCut {
public:
  planeCut(const generic_plane& pl);
  double* getAxis(axesName_t ax);
  bool next();

private:
#ifndef __CINT__
  std::map<axesName_t, std::shared_ptr<double>> m_storage;

  generic_plane m_pl;
  #endif
};
#endif // planeCut_h__
