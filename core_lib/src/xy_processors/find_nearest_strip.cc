#include "sct/xy_processors/find_nearest_strip.hh"
#include "sct/xy_processors/processorPlaneVSPlane.h"
#include "TMathBase.h"
#include <iostream>
#include "sct/predef/plane.hh"
#include "sct/generic_plane.hh"
#include "sct/ProcessorCollection.h"

#define  RESIDUAL_DEF ID_t(0)
#define  FIRST_PLANE_DEF ID_t(1)
#define  SECOND_PLANE_DEF ID_t(2)





class find_nearest_strip_processor :public processorPlaneVSPlane {
public:
  find_nearest_strip_processor(
    const xy_plane& planeA, 
    const xy_plane& planeB, 
    axis_def search_axis, 
    double cutOfff, 
    processor_prob& pprob);

  
  virtual void processEventStart();
  virtual void processHit(const hit&  p1, const hit&  p2);
  virtual process_returns processEventEnd();

  double m_cutOff;
  hit dist, h1, h2 ;
  double r = 10000000;
  axis_def m_axis;

  process_returns m_end_of_event_return =p_sucess;
};

find_nearest_strip_processor::find_nearest_strip_processor(
  const xy_plane& planeA, 
  const xy_plane& planeB, 
  axis_def search_axis, 
  double cutOfff, 
  processor_prob& pprob) 
  :processorPlaneVSPlane(planeA, planeB, pprob),
  m_axis(search_axis),
  m_cutOff(cutOfff)
{

}

void find_nearest_strip_processor::processEventStart()
{
  dist = hit(0,0);
  h1 = hit(0, 0);
  h2 = hit(0, 0);
  r = m_cutOff;
}




void find_nearest_strip_processor::processHit(const hit& p1, const hit& p2){
  hit e(p1.x - p2.x, p1.y - p2.y);

  double r1 = 0;
  if (m_axis == x_axis_def)
  {
    r1 = TMath::Abs(e.x);
  }
  else if (m_axis == y_axis_def) {
    r1 = TMath::Abs(e.y);
  }
  else {
    addError("unknown axis");
    m_end_of_event_return = p_error;
  }
  if (r1 > 0 && r1 < r)
  {
    r = r1;
    dist = e;
    h1 = p1;
    h2 = p2;
  }
  if (r1 == 0)
  {
    addError("error r1== 0");
    m_end_of_event_return = p_error;
  }
}

process_returns find_nearest_strip_processor::processEventEnd()
{
  if (r < m_cutOff)
  {

    pushHit(dist.x, dist.y, RESIDUAL_DEF);
    pushHit(h1.x, h1.y, FIRST_PLANE_DEF);
    pushHit(h2.x, h2.y, SECOND_PLANE_DEF);
  }

  auto ret = m_end_of_event_return;
  m_end_of_event_return = p_sucess;
  return ret;
}

find_nearest_strip::find_nearest_strip(const xy_plane& planeA, const xy_plane& planeB, axis_def search_axis, double cutOfff,  processor_prob plot_prob_ /*= processor_prob()*/)
{
  std::shared_ptr<processor> p(new find_nearest_strip_processor(planeA, planeB,search_axis,cutOfff, plot_prob_));
  planeA.get_ProcessorCollection()->addProcessor(p);

  m_coll = dynamic_cast<find_nearest_strip_processor*>(p.get())->get_output_collection();

}

xy_plane find_nearest_strip::getResidual() const{
  return m_coll->getPlane(RESIDUAL_DEF);
}

xy_plane find_nearest_strip::getHitOnPlaneA() const{
  return m_coll->getPlane(FIRST_PLANE_DEF);
}

xy_plane find_nearest_strip::getHitOnPlaneB() const{
  return m_coll->getPlane(SECOND_PLANE_DEF);
}
