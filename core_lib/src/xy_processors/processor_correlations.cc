#include "sct/xy_processors/processor_correlations.hh"
#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"

processor_correlations::processor_correlations(const axis& x_, const axis& y_, processor_prob& pprob):processor_corr2d(x_,y_,pprob){

}

void processor_correlations::processHit(double x, double y){
  pushHit(x, y);
}

xy_plane xy_pro::correlations(const axis& x_, const axis& y_, processor_prob& pprob /*= saveWithRandomName("correlation_")*/)
{
  std::shared_ptr<processor> p(new processor_correlations(x_, y_, pprob));
  x_.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_correlations*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}
