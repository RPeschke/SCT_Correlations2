#include "sct/xy_processors/processor_corr2d.hh"
#include "sct/axis.hh"

processor_corr2d::processor_corr2d(const axis& x_, const axis& y_, processor_prob& pprob):processor_2d(x_,y_,pprob){

}

void processor_corr2d::processEventStart()
{

}

process_returns processor_corr2d::processEventEnd()
{
  return p_sucess;
}

process_returns processor_corr2d::processCurrentEvent()
{
  processEventStart();
  while (m_y->next()) {
    while (m_x->next()) {
       processHit(m_x->getValue(), m_y->getValue());
    }
  }
  return processEventEnd();
}
