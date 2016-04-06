#ifndef processor_residual_h__
#define processor_residual_h__
#include "sct/xy_processors/processor_corr2d.hh"

class processor_residual :public processor_corr2d {
public:

  processor_residual(const axis& x_, const axis& y_, processor_prob& pprob);
  virtual void processHit(double x, double y) ;
};


#endif // processor_residual_h__
