#ifndef processor_linear_trans_h__
#define processor_linear_trans_h__
#include "sct/xy_processors/processor_hit2d.hh"

class processor_linear_trans : public processor_hit2d {
public:
  processor_linear_trans(double a11, double a12, double a21, double a22, const axis& x_, const axis& y_, processor_prob pprob);
  double m_a11, m_a21, m_a12, m_a22;
  virtual void processHit(double x, double y) ;
};


DllExport xy_plane linear_trans(const xy_plane& pl, double a11, double a12, double a21, double a22, processor_prob pprob = saveWithRandomName("linear_trans__"));

DllExport xy_plane rotate(const xy_plane& pl, double angle, processor_prob pprob = saveWithRandomName("rotate__"));

#endif // processor_linear_trans_h__
