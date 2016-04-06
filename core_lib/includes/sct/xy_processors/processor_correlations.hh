#ifndef processor_correlations_h__
#define processor_correlations_h__
#include "sct/xy_processors/processor_corr2d.hh"
#include "sct/predef/plane.hh"

class processor_correlations :public processor_corr2d {
public:   
  processor_correlations(const axis& x_, const axis& y_, processor_prob& pprob);
  virtual void processHit(double x, double y) ;

};


#endif // processor_correlations_h__
