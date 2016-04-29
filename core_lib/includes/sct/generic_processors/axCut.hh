#ifndef axCut_h__
#define axCut_h__

#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "cutNote.hh"
#ifndef __CINT__
#include <memory>
#endif // !__CINT__

class planeCut;


class DllExport axCut {
public:

  
  axCut(axesName_t name_);
  axCut(axesName_t name_, x_slope_t slope_, x_offset_t offset_);
  
  axCut(const axCut&);

  double getValue() const;
  bool register_plane(planeCut& pl);
  axesName_t getName() const;

  axCut add(double value);
  axCut multiply(double value);
  
#ifndef __CINT__
   virtual std::shared_ptr<axCut> copy() const ;
   axCut(axesName_t name_, x_slope_t slope_, x_offset_t offset_ , const double* hit_);
#endif // !__CINT__

private:
  const axesName_t m_name;
  const double* m_hit = nullptr;
  const x_slope_t m_slope = x_slope_t(1);
  const x_offset_t m_offset = x_offset_t(0);
};

DllExport axCut operator+(axCut , double);
DllExport axCut operator+(double, axCut);
DllExport axCut operator*(axCut, double);
DllExport axCut operator*(double, axCut);

DllExport axCut x_def();
DllExport axCut y_def();

#endif // axCut_h__
