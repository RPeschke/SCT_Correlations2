#include "sct/processor_prob.hh"


bool gForceSaveToDisk = false;

processor_prob::processor_prob()
{

}

processor_prob& processor_prob::save2Disk() {
  save = SaveOption::save2Disk;
  return *this;
}

processor_prob& processor_prob::dontSave2Disk(){
  save = SaveOption::DontSave2Disk;
  return *this;
}

processor_prob& processor_prob::setName(const processorName_t& name_){
  name = name_;
  return *this;
}

processor_prob& processor_prob::addAxis(const axesName_t& AxisName_){
  axisNames.push_back(AxisName_);
  return *this;
}

processor_prob& processor_prob::setAxis(const std::vector<axesName_t>& AxisNames_){
  axisNames = AxisNames_;
  return *this;
}

processor_prob& processor_prob::setProcessorCollection(ProcessorCollection* PC){
  ProcessorColl = PC;
  return *this;
}

SaveOption processor_prob::getSave() const {
  if (gForceSaveToDisk == true) {
    return SaveOption::save2Disk;
  }

  return save;
}

void processor_prob::EnableDebugSave() {
  gForceSaveToDisk = true;
}

void processor_prob::DisableDebugSave() {
  gForceSaveToDisk = false;

}

int gcounter = 0;

processorName_t GName= processorName_t("");

void ___set_GName(processorName_t name)
{
  GName = name;
}


processorName_t ___get_GName()
{
  return GName;
}

processor_prob saveWithRandomName(const processorName_t& name)
{
  auto n = ___get_GName();
  if ( necessary_CONVERSION(n).empty()) {
    n = name + processorName_t(std::to_string(++gcounter));
  }
  auto ret = processor_prob();
  ret.save2Disk();
  ret.setName(n);
  ___set_GName(processorName_t(""));
  return ret;
}

 processor_prob DontsaveWithRandomName(const processorName_t& name /*= "random"*/)
{
   auto n = ___get_GName();
   if (necessary_CONVERSION(n).empty()) {
     n = name + processorName_t(std::to_string(++gcounter));
   }
  auto ret = processor_prob();
  ret.dontSave2Disk();
  ret.setName(n);
  ___set_GName(processorName_t(""));
  return ret;
}



