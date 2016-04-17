#ifndef processor_transform_h__
#define processor_transform_h__
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/platform.hh"
#include "sct/internal/strong_types.h"

class processor_transform:public processor_hit2d {
public:
  processor_transform(x_slope_t x_slope, x_offset_t x_offset, y_slope_t y_slope, y_offset_t y_offset, const axis& x_, const axis& y_, processor_prob& pprob);
  x_slope_t m_x_slope = x_slope_t(0);
  y_slope_t m_y_slope = y_slope_t(0);
  x_offset_t m_x_offset = x_offset_t(0);
  y_offset_t m_y_offset = y_offset_t(0);
  virtual void processHit(double x, double y) ;
};



#endif // processor_transform_h__
