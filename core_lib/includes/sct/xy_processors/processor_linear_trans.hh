#ifndef processor_linear_trans_h__
#define processor_linear_trans_h__
#include "sct/xy_processors/processor_hit2d.hh"

class processor_linear_trans : public processor_hit2d {
public:
  processor_linear_trans(double a11, double a12, double a21, double a22, const axis& x_, const axis& y_, processor_prob pprob);
  double m_a11, m_a21, m_a12, m_a22;
  virtual void processHit(double x, double y) ;
};



#endif // processor_linear_trans_h__
