#include "sct/lcio/lcio_output.hh"
#include "sct/lcio/lcio_collection.hh"
#include "sct/internal/factoryDef.hh"

registerBaseClassDef(lcio_output);
void lcio_output::eventEnd()
{
  FinnishEvent();
}

void lcio_output::eventStart(int eventNR)
{
  m_event_nr = eventNR;
  m_id->clear();
  m_x->clear();
  m_y->clear();
  newEvent(eventNR);
}

void lcio_output::push_hit(double x, double y, double ID)
{
  m_x->push_back(x);
  m_y->push_back(y);
  m_id->push_back(ID);
}



lcio_output::lcio_output(Parameter_ref param_):m_prob(param_)
{
  m_x = m_prob.m_coll->m_storage["x"].get();
  m_y = m_prob.m_coll->m_storage["y"].get();
  m_id = m_prob.m_coll->m_storage["ID"].get();
}

lcio_output::~lcio_output()
{

}

const std::string& lcio_output::get_Name() const
{
  return m_prob.m_name;
}

const std::string& lcio_output::get_type() const
{
  return m_prob.m_type;
}

lcio_output_prob::lcio_output_prob()
{

}

lcio_output_prob::lcio_output_prob(const std::string& name, const std::string& type, lcio_collection* mcoll) :m_name(name), m_type(type), m_coll(mcoll)
{

}

lcio_output_prob& lcio_output_prob::setName(const std::string& name)
{
  m_name = name; 
  return *this;
}

lcio_output_prob& lcio_output_prob::setType(const std::string& type)
{
  m_type = type;
  return *this;
}

lcio_output_prob& lcio_output_prob::set_lcio_collection(lcio_collection* mcoll)
{
  m_coll = mcoll;
  return  *this;
}


 bool isIgnored(const std::string & name) {
  if (name == "TrackFORselTrack") {
    return true;
  }
  if (name == "StatesFORselTrack")
  {
    return true;
  }
  if (name == "StateHitFORselTrack") {
    return true;
  }
  if (name.find("FOR") != std::string::npos) {
    return true;
  }
  return false;
}


std::shared_ptr<lcio_output> create_lcio_ouput(lcio_output::Parameter_ref param)
{

  if (isIgnored(param.m_name)) {
    return nullptr;
  }
  return Class_factory_Utilities::Factory<lcio_output>::Create(param.m_type, param);
}
