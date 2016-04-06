#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/axis.hh"

processor_hit2d::processor_hit2d(const axis& x_, const axis& y_, processor_prob& pprob):processor_2d(x_,y_,pprob)
{

}

void processor_hit2d::processEventStart()
{

}

process_returns processor_hit2d::processEventEnd()
{
  return p_sucess;
}

process_returns processor_hit2d::processCurrentEvent(){
  processEventStart();
  while (m_y->next()) {
    if (!m_x->next())
    {
      addError("vector have different length");
      
      return p_error;
    }
    //      std::cout << m_x->get()<< "  "<< m_y->get() << std::endl;
    processHit(m_x->getValue(), m_y->getValue());

  }

  if (m_x->next())
  {
    addError("vector have different length");
    return p_error;
  }
  return processEventEnd();
}
