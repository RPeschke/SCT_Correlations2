#ifndef processor_cut_xy_h__
#define processor_cut_xy_h__
#include "sct/xy_processors/processor_hit2d.hh"
class S_Cut;
class  processor_cut_xy:public processor_hit2d{
public:
  processor_cut_xy(const S_Cut& cut_, const axis& x_, const axis& y_, processor_prob& pprob);
  virtual void processHit(double x, double y) ;
  std::shared_ptr<S_Cut> m_cut;
};

DllExport xy_plane cut_xy(const xy_plane& pl, const S_Cut& cut_, processor_prob& pprob = saveWithRandomName("cut_xy_"));

#endif // processor_cut_xy_h__
