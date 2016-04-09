#ifndef modulo_h__
#define modulo_h__
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/axis.hh"

class modulo_processor :public processor_hit2d {
public:
  modulo_processor(const axis& x_, const axis& y_, double mod_x,double mod_y, processor_prob& pprob);
  virtual void processHit(double x, double y);
private:
 const double m_modulo_x, m_mod_y;
};
#endif // modulo_h__
