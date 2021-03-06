#include "sct//predef/DUT_2_Track_correlator.hh"

#ifdef _DEBUG
#define Class_factory_Utilities_THROW(msg, inPutVar)  std::cout << "[Factory<baseClassType>::Create" << ":" << __LINE__ << "]: \n " << msg << " <" << necessary_CONVERSION(inPutVar) << ">" << std::endl;
#endif // _DEBUG

#include "sct/internal/factoryDef.hh"
registerBaseClassDef(DUT_2_Track_correlator);

D2T_prob::D2T_prob():m_prob(saveWithRandomName(processorName_t("DUT2Track__")))
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

D2T_prob& D2T_prob::set_xmlFile(const XML_imput_file& xml_file_)
{
  m_xml_file_ = xml_file_;
  return *this;
}

D2T_prob& D2T_prob::set_processor_pro(const processor_prob& pprob)
{
  m_prob = pprob;
  return *this;
}

D2T_prob& D2T_prob::set_gear(const Xgear* gear_)
{
  m_gear = gear_;
  return *this;
}

const Xgear* D2T_prob::get_gear() const
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

XML_imput_file D2T_prob::get_xmlFile() const
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

 D2T::D2T(const DUT_2_Track_correlator::MainType& name,DUT_2_Track_correlator::Parameter_ref param_)
 {
   m_d2t = std::move(create_DUT_2_Track_correlator(param_, name));
 }

 xy_plane D2T::getResidual()
 {
   return m_d2t->getResidual();
 }

 xy_plane D2T::getResidualVsMissing()
 {
   return m_d2t->getResidualVsMissing();
 }

 xy_plane D2T::getTotalTrueHits()
 {
   return m_d2t->getTotalTrueHits();
 }

 xy_plane D2T::getTrueHitsWithDUT()
 {
   return m_d2t->getTrueHitsWithDUT();
 }

 xy_plane D2T::getDUT_Hits()
 {
   return m_d2t->getDUT_Hits();
 }
