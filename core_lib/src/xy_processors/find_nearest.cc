#include "sct/xy_processors/find_nearest.hh"
#include "sct/xy_processors/processorPlaneVSPlane.h"
#include "sct/collection.h"
#include "TMath.h"
#include "sct/predef/plane.hh"
#include "sct/collection.h"
#include "sct/ProcessorCollection.h"
#define  RESIDUAL_DEF  ID_t(0)
#define  FIRST_PLANE_DEF ID_t(1)
#define  SECOND_PLANE_DEF ID_t(2)





class find_nearest_processor :public processorPlaneVSPlane {
public:
  find_nearest_processor(const xy_plane& plane_A, const xy_plane& plane_B, double x_cutOff, double y_cutOff, processor_prob& pprob);


  virtual void processEventStart();
  virtual void processHit(const hit&  p1, const hit&  p2);
  virtual process_returns processEventEnd();


  const double m_c_noHit = 100000000000;
  double m_x_cutOff, m_y_cutOff;
  double r;
  hit  dist = hit(0, 0), h1 = hit(0, 0), h2 = hit(0, 0);
  
  process_returns m_end_of_event_return = p_sucess;
};

find_nearest_processor::find_nearest_processor(
  const xy_plane& plane_A, 
  const xy_plane& plane_B, 
  double x_cutOff, 
  double y_cutOff, 
  processor_prob& pprob)
  :processorPlaneVSPlane(plane_A,plane_B,pprob),
  m_x_cutOff(x_cutOff),
  m_y_cutOff(y_cutOff)
{

}




void find_nearest_processor::processEventStart(){
  dist = hit(0, 0);
  h1 = hit(0, 0);
  h2 = hit(0, 0);
  r = m_c_noHit;
}

void find_nearest_processor::processHit(const hit& p1, const hit& p2){
  auto e = hit((p1.x - p2.x), (p1.y - p2.y));
  auto r1 = TMath::Sqrt((e.x)*(e.x) + (e.y)*(e.y));

  if (
    r1 < r
    &&
    TMath::Abs(e.x) < m_x_cutOff
    &&
    TMath::Abs(e.y) < m_y_cutOff)
  {
    r = r1;
    dist = e;
    h1 = p1;
    h2 = p2;
  }

}

process_returns find_nearest_processor::processEventEnd()
{
  if (r < m_c_noHit)
  {
    pushHit(dist.x, dist.y, RESIDUAL_DEF);
    pushHit(h1.x, h1.y, FIRST_PLANE_DEF);
    pushHit(h2.x, h1.y, SECOND_PLANE_DEF);
  }

  return p_sucess;
}

find_nearest::find_nearest(const xy_plane& plane_A, const xy_plane& plane_B, double x_cutoff, double y_cutoff, processor_prob& pprob /*= processor_prob() */)
{
  std::shared_ptr<processor> p(new find_nearest_processor(plane_A, plane_B, x_cutoff, y_cutoff, pprob));
  plane_A.get_ProcessorCollection()->addProcessor(p);

  m_coll = dynamic_cast<find_nearest_processor*>(p.get())->get_output_collection();
}

xy_plane find_nearest::getResidual() const
{
  return m_coll->getPlane(RESIDUAL_DEF);
}

xy_plane find_nearest::getHitOnPlaneA() const
{
  return m_coll->getPlane(FIRST_PLANE_DEF);
}

xy_plane find_nearest::getHitOnPlaneB() const
{
  return m_coll->getPlane(SECOND_PLANE_DEF);
}
