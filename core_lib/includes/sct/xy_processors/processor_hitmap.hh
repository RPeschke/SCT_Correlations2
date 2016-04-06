#ifndef processor_hitmap_h__
#define processor_hitmap_h__
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/predef/plane.hh"


DllExport xy_plane hitmap(const axis& x_, const axis& y_, processor_prob& pprob= saveWithRandomName("hitmap__"));

class processor_hitmap :public processor_hit2d{
public:  
  processor_hitmap(const axis& x_, const axis& y_, processor_prob& pprob);
  virtual void processHit(double x, double y) ;

};

#endif // processor_hitmap_h__
