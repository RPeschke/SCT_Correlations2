#include "sct/predef/truehitExtractor.hh"
#include "sct/internal/factoryDef.hh"
#include "sct/predef/fitterFile.hh"
registerBaseClassDef(truehitExtractor);

truehitExtractor::truehitExtractor(truehitExtractor::Parameter_ref param_) :m_param(param_)
{

}





std::unique_ptr<truehitExtractor> create_truehitExtractor(truehitExtractor::Parameter_ref param_, const truehitExtractor::MainType& type /*= ""*/)
{
  return Class_factory_Utilities::Factory<truehitExtractor>::Create(type, param_);
}



void register_truehitExtractor(const truehitExtractor::MainType& name, truehitExtractor* (fun)(truehitExtractor::Parameter_ref param_))
{
  Class_factory_Utilities::Factory<truehitExtractor>::do_register(name, fun);
}

TH_param::TH_param():m_pprob(saveWithRandomName(processorName_t("truehits_")))
{

}

TH_param& TH_param::set_fitterFile(fitterFile* file_)
{
  m_file = file_;
  return *this;
}

TH_param& TH_param::set_fitterFile(FFile& file_)
{
  m_file = file_.get_file();
  return *this;
}

TH_param& TH_param::set_gear(const Xgear* gear_)
{
  m_gear = gear_;
  return *this;
}

TH_param& TH_param::set_processor_pro(processor_prob& pprob)
{
  m_pprob = pprob;
  return *this;
}

fitterFile* TH_param::get_fitterFile()
{
  return m_file;
}

const Xgear* TH_param::get_gear() const 
{
  return m_gear;
}

processor_prob& TH_param::get_processor_pro()
{
  return m_pprob;
}

THE::THE(const truehitExtractor::MainType& name, truehitExtractor::Parameter_ref param_)
{
  m_the = std::move(create_truehitExtractor(param_, name));
}

xy_plane THE::get_true_DUT_Hits()
{
  return m_the->get_true_DUT_Hits();
}

// void THE::register_new(const truehitExtractor::MainType& name, truehitExtractor* (fun)(truehitExtractor::Parameter_ref param_))
// {
//   register_truehitExtractor(name, fun);
// }
