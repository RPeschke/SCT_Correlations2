#include "sct/xy_processors/processor_linear_trans.hh"
#include "TMath.h"
#include "sct/predef/plane.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"

processor_linear_trans::processor_linear_trans(double a11, double a12, double a21, double a22, const axis& x_, const axis& y_, processor_prob pprob):
  processor_hit2d(x_,y_,pprob),
  m_a11(a11), 
  m_a21(a21), 
  m_a12(a12), 
  m_a22(a22)
{

}

void processor_linear_trans::processHit(double x, double y)
{
  pushHit(m_a11 * x + m_a12 *y, m_a21* x + m_a22* y);
}

xy_plane xy_pro::linear_trans(const xy_plane& pl, double a11, double a12, double a21, double a22, processor_prob pprob /*= saveWithRandomName("linear_trans__")*/)
{
  std::shared_ptr<processor> p(new processor_linear_trans(a11, a12, a21, a22, pl.get_x(), pl.get_y(), pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_linear_trans*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}

xy_plane xy_pro::rotate(const xy_plane& pl, double angle, processor_prob pprob /*= saveWithRandomName("rotate__")*/)
{
  return linear_trans(pl, TMath::Cos(angle), -TMath::Sin(angle), TMath::Sin(angle), TMath::Cos(angle), pprob);
}
