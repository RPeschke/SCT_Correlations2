#include "sct/xy_processors/processor_2d.hh"
#include "sct/processor_prob.hh"
#include "sct/axis.hh"
#include "sct/predef/plane.hh"
#include "sct/collection.h"
#include <iostream>


init_returns processor_2d::init()
{
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}

end_returns processor_2d::end()
{
  return e_success;
}

processor_2d::~processor_2d()
{
 
}

processor_2d::processor_2d(const axis& x_, const  axis& y_, processor_prob& pprob) :m_prob(pprob.setAxis(xy_names()).setProcessorCollection(x_.get_ProcessorCollection())) {
  m_x = _MAKE_SHARED1(axis,x_);
  m_y = _MAKE_SHARED1(axis,y_);
  m_output_coll = _MAKE_SHARED1(collection,m_prob);
  
  m_outputPlane =_MAKE_SHARED1(xy_plane,m_output_coll->getPlane(ID_t(0)));
  m_outhit = m_outputPlane->get_hit();
}

process_returns processor_2d::processEvent(){
  ++m_current;
   m_output_coll->clear_event();

  return processCurrentEvent();
}

void processor_2d::pushHit(double x, double y) {
  pushHit(x, y, ID_t(0));
}

void processor_2d::pushHit(double x, double y, ID_t ID){
  m_outhit->x = x;
  m_outhit->y = y;
  m_outputPlane->get_generic_plane()->push(ID);
}

void processor_2d::pushHit(const hit& hit, ID_t ID){
  m_outhit->x = hit.x;
  m_outhit->y = hit.y;
  m_outputPlane->get_generic_plane()->push(ID);
}

process_returns processor_2d::fill() {
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

collection* processor_2d::get_output_collection() {
  return m_output_coll.get();
}

processorName_t processor_2d::get_name(){
  return m_prob.name;
}

int processor_2d::getEventNr()
{
  return m_current;
}
