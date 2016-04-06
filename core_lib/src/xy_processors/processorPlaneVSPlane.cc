#include "sct/xy_processors/processorPlaneVSPlane.h"
#include "sct/predef/plane.hh"


processorPlaneVSPlane::processorPlaneVSPlane(
  const xy_plane & plane_A, 
  const xy_plane& plane_b,
  processor_prob& plot_prob)
    :m_input_plane_A(*plane_A.get_generic_plane()),
     m_input_plane_B(*plane_b.get_generic_plane())
{

  m_output_coll= std::make_shared<collection>(plot_prob.setAxis(xy_names()).setProcessorCollection(plane_A.get_ProcessorCollection()));
  m_outputPlane=std::make_shared<xy_plane>(m_output_coll->getPlane(0));
  m_inputHit_A = m_input_plane_A.get_hit();
  m_inputHit_B = m_input_plane_B.get_hit();
  m_outhit = m_outputPlane->get_hit();

}



init_returns processorPlaneVSPlane::init(){
  return i_sucess;
}

process_returns processorPlaneVSPlane::processEvent(){

  ++m_current;
  m_size_x = 0;
  m_size_y = 0;
  m_output_coll->clear();
  
  bool first = true;
  processEventStart();
  while (m_input_plane_B.next()) {
    ++m_size_y;
    while (m_input_plane_A.next()) {
      if (first) {
        ++m_size_x;
      }
      processHit(*m_inputHit_A, *m_inputHit_B);
    }
    first = false;
    processHit_2(*m_inputHit_B);
  }

  while (m_input_plane_A.next()) {
    processHit_1(*m_inputHit_A);

  }



  return processEventEnd();
}

process_returns processorPlaneVSPlane::fill(){
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processorPlaneVSPlane::end(){
  return e_success;
}





std::string processorPlaneVSPlane::get_name()
{
  return m_plot_prob.name;
}






process_returns processorPlaneVSPlane::processEventEnd()
{
  return p_sucess;
}



void processorPlaneVSPlane::pushHit(double x, double y, double ID)
{
  m_outhit->x = x;
  m_outhit->y = y;
  m_outputPlane->get_generic_plane()->push(ID);
}

void processorPlaneVSPlane::pushHit(const hit& hit, double ID)
{
  m_outhit->x = hit.x;
  m_outhit->y = hit.y;
  m_outputPlane->get_generic_plane()->push(ID);
}

collection* processorPlaneVSPlane::get_output_collection(){
  return m_output_coll.get();
}
