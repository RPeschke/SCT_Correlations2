#ifndef modulo_h__
#define modulo_h__
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/axis.hh"
#include "sct//internal/strong_types.h"



class modulo_processor :public processor_hit2d {
public:
  modulo_processor(const axis& x_, const axis& y_, modulo_x mod_x,modulo_y mod_y, processor_prob& pprob);
  virtual void processHit(double x, double y);
private:
  const modulo_x m_modulo_x;
  const modulo_y m_mod_y;
};
#endif // modulo_h__
