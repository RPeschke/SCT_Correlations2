#ifndef axCut_h__
#define axCut_h__

#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "cutNote.hh"
#ifndef __CINT__
#include <memory>
#endif // !__CINT__
#include "lambda_Note.hh"
#include "sct/platform.hh"

class planeCut;


class DllExport axCut:public cutNote {
public:

  
  axCut();
  axCut(const axCut& rhs);
  axCut(const axesName_t& name);
  virtual bool register_plane(planeCut& pl) __OVERIDE__;
  virtual double get_value() const __OVERIDE__;
  virtual ~axCut() __OVERIDE__;
#ifndef __CINT__
  virtual std::shared_ptr<cutNote> copy() const __OVERIDE__;
private:  
  axesName_t m_name;
  const double * m_hit = nullptr;
#endif

  

};






DllExport axCut x_def();
DllExport axCut y_def();

#endif // axCut_h__
