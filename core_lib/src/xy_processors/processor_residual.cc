#include "sct/xy_processors/processor_residual.hh"
#include "sct/predef/plane.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
processor_residual::processor_residual(const axis& x_, const axis& y_, processor_prob& pprob):processor_corr2d(x_,y_,pprob)
{

}

void processor_residual::processHit(double x, double y)
{
  pushHit(x - y, getEventNr());
}


xy_plane xy_pro::residual(const axis& x_, const axis& y_, processor_prob pprob) {
  std::shared_ptr<processor> p(new processor_residual(x_, y_, pprob));
  x_.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_residual*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}