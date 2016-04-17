#include "sct/xy_processors/processor_transform.hh"
#include "sct/ProcessorCollection.h"
#include "sct/predef/plane.hh"
#include "sct/xy_processors/xy_pro.hh"

processor_transform::processor_transform(double x_slope, double x_offset, double y_slope, double y_offset, const axis& x_, const axis& y_, processor_prob& pprob):processor_hit2d(x_,y_,pprob),m_x_slope(x_slope),m_x_offset(x_offset),m_y_slope(y_slope),m_y_offset(y_offset)
{

}

void processor_transform::processHit(double x, double y)
{
  pushHit(x*m_x_slope + m_x_offset, y*m_y_slope + m_y_offset);
}

xy_plane xy_pro::transform(const xy_plane& pl, double x_slope, double x_offset, double y_slope, double y_offset, processor_prob& pprob /*= saveWithRandomName("transform__")*/)
{
  std::shared_ptr<processor> p(new processor_transform( x_slope,  x_offset,  y_slope,  y_offset, pl.get_x(), pl.get_y(), pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_transform*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}

 xy_plane xy_pro::transform_move(const xy_plane& pl, double x_offset, double y_offset, processor_prob& pprob /*= saveWithRandomName("transform__")*/)
{
  return transform(pl, 1, x_offset, 1, y_offset, pprob);
}
