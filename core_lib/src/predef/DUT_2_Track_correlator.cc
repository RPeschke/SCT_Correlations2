#include "sct//predef/DUT_2_Track_correlator.hh"


#include "sct/internal/factoryDef.hh"
registerBaseClassDef(DUT_2_Track_correlator);

D2T_prob::D2T_prob():m_prob(saveWithRandomName("DUT2Track__"))
{

}

D2T_prob& D2T_prob::set_trueHits(const xy_plane& trueHits_)
{
  m_trueHits = trueHits_;
  return *this;
}

D2T_prob& D2T_prob::set_DUTHits(const xy_plane& DUT_hits)
{
  m_DUT_hits = DUT_hits;
  return *this;
}

D2T_prob& D2T_prob::set_xmlFile(XML_imput_file* xml_file_)
{
  m_xml_file_ = xml_file_;
  return *this;
}

D2T_prob& D2T_prob::set_processor_pro(const processor_prob& pprob)
{
  m_prob = pprob;
  return *this;
}

D2T_prob& D2T_prob::set_gear(Xgear* gear_)
{
  m_gear = gear_;
  return *this;
}

Xgear* D2T_prob::get_gear() const
{
  return m_gear;
}

processor_prob D2T_prob::get_processor_pro() const
{
  return m_prob;
}

xy_plane D2T_prob::get_trueHits() const
{
  return m_trueHits;
}

xy_plane D2T_prob::get_DUT_Hits() const
{
  return m_DUT_hits;
}

XML_imput_file* D2T_prob::get_xmlFile() const
{
  return m_xml_file_;
}

DUT_2_Track_correlator::DUT_2_Track_correlator(Parameter_ref param_):m_param(param_)
{

}

void register_DUT_2_Track_correlator(const DUT_2_Track_correlator::MainType& name, DUT_2_Track_correlator* (fun)(DUT_2_Track_correlator::Parameter_ref param_))
{
  Class_factory_Utilities::Factory<DUT_2_Track_correlator>::do_register(name, fun);
}

 std::unique_ptr<DUT_2_Track_correlator> create_DUT_2_Track_correlator(DUT_2_Track_correlator::Parameter_ref param_, const DUT_2_Track_correlator::MainType& type)
{
  return Class_factory_Utilities::Factory<DUT_2_Track_correlator>::Create(type, param_);
}
