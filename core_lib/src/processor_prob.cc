#include "sct/processor_prob.hh"

processor_prob& processor_prob::save2Disk(){
  save = SaveOption::save2Disk;
  return *this;
}

processor_prob& processor_prob::dontSave2Disk(){
  save = SaveOption::DontSave2Disk;
  return *this;
}

processor_prob& processor_prob::setName(const std::string& name_){
  name = name_;
  return *this;
}

processor_prob& processor_prob::addAxis(const std::string& AxisName_){
  axisNames.push_back(AxisName_);
  return *this;
}

processor_prob& processor_prob::setAxis(const std::vector<std::string>& AxisNames_){
  axisNames = AxisNames_;
  return *this;
}

processor_prob& processor_prob::setProcessorCollection(ProcessorCollection* PC){
  ProcessorColl = PC;
  return *this;
}

int gcounter = 0;

processor_prob saveWithRandomName(const std::string& name)
{
  auto ret = processor_prob();
  ret.save2Disk();
  ret.setName(name + std::to_string(++gcounter));
  return ret;
}

 processor_prob DontsaveWithRandomName(const std::string& name /*= "random"*/)
{
  auto ret = processor_prob();
  ret.dontSave2Disk();
  ret.setName(name + std::to_string(++gcounter));
  return ret;
}
