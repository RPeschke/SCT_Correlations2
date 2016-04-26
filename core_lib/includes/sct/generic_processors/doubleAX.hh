#ifndef doubleAX_h__
#define doubleAX_h__
#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/axCut.hh"

class DllExport doubleAX :public cutNote {
public:
  doubleAX(const doubleAX&) ;
  doubleAX operator=(const doubleAX&);
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
#ifndef __CINT__
  doubleAX(axCut nameA, axCut nameB, Predicate_f2 fun);
  virtual std::shared_ptr<cutNote> copy() const;
private:
  Predicate_f2 m_predicate;
  std::shared_ptr<axCut> m_axA;
  std::shared_ptr<axCut> m_axB;
#endif
};

DllExport doubleAX operator<(axCut A, axCut B);
DllExport doubleAX operator<=(axCut A, axCut B);
DllExport doubleAX operator>(axCut A, axCut B);
DllExport doubleAX operator>=(axCut A, axCut B);
DllExport doubleAX operator==(axCut A, axCut B);
DllExport doubleAX operator!=(axCut A, axCut B);

#endif // doubleAX_h__
