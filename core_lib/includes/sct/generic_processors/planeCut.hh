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

#ifndef __CINT__
  generic_plane m_pl;
private:
  std::map<axesName_t, std::shared_ptr<double>> m_storage;
#endif
};
#endif // planeCut_h__
