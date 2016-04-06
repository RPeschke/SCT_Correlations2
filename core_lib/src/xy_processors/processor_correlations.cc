#include "sct/xy_processors/processor_correlations.hh"
#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"

processor_correlations::processor_correlations(const axis& x_, const axis& y_, processor_prob& pprob):processor_corr2d(x_,y_,pprob){

}

void processor_correlations::processHit(double x, double y){
  pushHit(x, y);
}

xy_plane correlations(const axis& x_, const axis& y_, processor_prob& pprob /*= saveWithRandomName("correlation_")*/)
{
  std::shared_ptr<processor> p(new processor_correlations(x_, y_, pprob));
  x_.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_correlations*>(p.get())->get_output_collection()->getPlane(0);
}
