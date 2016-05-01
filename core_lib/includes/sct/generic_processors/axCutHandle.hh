#ifndef axCutHandle_h__
#define axCutHandle_h__
#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/axCut.hh"

class DllExport axCutHandle :public cutNote {
public:
  axCutHandle(const axCutHandle&) ;
  axCutHandle operator=(const axCutHandle&);

  virtual bool register_plane(planeCut& pl) __OVERIDE__;
  virtual double get_value() const __OVERIDE__;

#ifndef __CINT__  
  axCutHandle(axCut name, Predicate_f fun);
  virtual std::shared_ptr<cutNote> copy() const __OVERIDE__;
private:
  Predicate_f m_predicate;
  std::shared_ptr<axCut> m_Ax;
#endif

};


DllExport axCutHandle operator<(cutValue_t min_, axCut ax);
DllExport axCutHandle operator<=(cutValue_t min_, axCut ax);
DllExport axCutHandle operator>(cutValue_t val, axCut ax);
DllExport axCutHandle operator>=(cutValue_t val, axCut ax);
DllExport axCutHandle operator<(axCut ax, cutValue_t val);
DllExport axCutHandle operator<=(axCut ax, cutValue_t val);
DllExport axCutHandle operator>(axCut ax, cutValue_t val);
DllExport axCutHandle operator>=(axCut ax, cutValue_t val);

DllExport axCutHandle operator==(axCut ax, cutValue_t val);
DllExport axCutHandle operator!=(axCut ax, cutValue_t val);

DllExport axCutHandle operator==(cutValue_t val, axCut ax);
DllExport axCutHandle operator!=(cutValue_t val, axCut ax);
#endif // axCutHandle_h__
