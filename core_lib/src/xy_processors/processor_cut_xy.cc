#include "sct/xy_processors/processor_cut_xy.hh"
#include "sct/legacy/s_cuts.h"
#include "sct/predef/plane.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
processor_cut_xy::processor_cut_xy(const S_Cut& cut_, const axis& x_, const axis& y_, processor_prob& pprob):processor_hit2d(x_,y_,pprob)
{
  m_cut = cut_.copy();
}

void processor_cut_xy::processHit(double x, double y){
  if (m_cut->isOutOfRange(1, x, y))
  {
    return;
  }


  pushHit(x, y);
}


 xy_plane xy_pro::cut_xy(const xy_plane& pl, const S_Cut& cut_, processor_prob& pprob /*= saveWithRandomName("cut_xy_")*/)
{
  std::shared_ptr<processor> p(new processor_cut_xy(cut_,pl.get_x(), pl.get_y(), pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_cut_xy*>(p.get())->get_output_collection()->getPlane(0);
}
