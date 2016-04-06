#include "sct/xy_processors/processor_hitmap.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"

processor_hitmap::processor_hitmap(const axis& x_, const axis& y_, processor_prob& pprob):processor_hit2d(x_,y_,pprob){

}

void processor_hitmap::processHit(double x, double y)
{
  pushHit(x, y);
}



xy_plane xy_pro::hitmap(const axis& x_, const axis& y_, processor_prob& pprob)
{
  std::shared_ptr<processor> p(new processor_hitmap(x_, y_, pprob));
  x_.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_hitmap*>(p.get())->get_output_collection()->getPlane(0);
}
