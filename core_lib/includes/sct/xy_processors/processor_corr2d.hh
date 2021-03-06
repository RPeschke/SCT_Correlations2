#ifndef processor_corr2d_h__
#define processor_corr2d_h__
#include "sct/xy_processors/processor_2d.hh"

class axis;
class processor_corr2d :public processor_2d {
public:
  processor_corr2d(const axis& x_, const axis& y_, processor_prob& pprob);
  virtual void processEventStart();
  virtual void processHit(double x, double y) = 0;
  virtual process_returns processEventEnd();
  virtual process_returns processCurrentEvent();
};


#endif // processor_corr2d_h__
