#include "sct//lagacy/xml_input_file.hh"
#include "sct/lagacy/xml_util.hh"
#include "rapidxml_utils.hpp"

const S_Cut& xml_globalConfig::cut() const
{
  return  m_cut;
}



const char* xml_file::NodeName()
{
  return "file";
}

XML_imput_file::XML_imput_file(const char* name) 
{
  rapidxml::file<> file_(name);
  rapidxml::xml_document<> doc_;
  doc_.parse<0>(file_.data());    // 0 means default parse flags

  rapid_xml_node gconfig(doc_.first_node("RunCollection")->first_node("globalConfig"));
  globalConfig = xml_globalConfig( &gconfig);

  m_files = xml_util::getVectorOfT<xml_file>(doc_.first_node("RunCollection")->first_node("fileList"));
}

xml_file& XML_imput_file::get_File(int id)
{
  return m_files.at(id);
}

const xml_file& XML_imput_file::get_File(int id) const
{
  return m_files.at(id);
}

int XML_imput_file::size() const
{
  return  m_files.size();
}

xml_globalConfig::xml_globalConfig(rapid_xml_node* xIn)
{
  CollectionName = xml_util::getAtribute_string(xIn->value->first_node("CollectionName"), "value");

  NumberOfBins = xml_util::getAtribute<int>(xIn->value->first_node("NumberOfBins"), "value");
  NumberOfStrips = xml_util::getAtribute<int>(xIn->value->first_node("NumberOfStrips"), "value");


  Device = xml_util::getAtribute<int>(xIn->value->first_node("Device"), "value");


  auto min_ = xml_util::getAtribute<int>(xIn->value->first_node("AvtiveStrips"), "min");
  auto max_ = xml_util::getAtribute<int>(xIn->value->first_node("AvtiveStrips"), "max");

  AvtiveStrips = MinMaxRange(min_, max_);

  Rotation = xml_util::getAtribute<double>(xIn->value->first_node("Rotation"), "value");

  Position_name = xml_util::getAtribute_string(xIn->value->first_node("Position"), "name");

  Position_value = xml_util::getAtribute<double>(xIn->value->first_node("Position"), "value");
  residual_cut = xml_util::getAtribute<double>(xIn->value->first_node("residual_cut"), "value");
  gearFile = xml_util::getAtribute_string(xIn->value->first_node("gearFile"), "name");


  auto ymin_ = xml_util::getAtribute<double>(xIn->value->first_node("YCut"), "min");
  auto ymax_ = xml_util::getAtribute<double>(xIn->value->first_node("YCut"), "max");
  auto xmin_ = xml_util::getAtribute<double>(xIn->value->first_node("XCut"), "min");
  auto xmax_ = xml_util::getAtribute<double>(xIn->value->first_node("XCut"), "max");
  m_cut = S_YCut(ymin_, ymax_) + S_XCut(xmin_, xmax_);
  
}

xml_globalConfig::xml_globalConfig()
{

}

xml_file::xml_file(rapid_xml_node* xIn)
{
  name = xml_util::getAtribute_string(xIn->value->first_node("name"), "value");
  threshold = xml_util::getAtribute<double>(xIn->value->first_node("threshold"), "value");

  HV = xml_util::getAtribute<double>(xIn->value->first_node("HV"), "value");
  runNumber = xml_util::getAtribute<int>(xIn->value->first_node("runNumber"), "value");


}

xml_file::xml_file()
{

}

MinMaxRange::MinMaxRange() :m_min(0), m_max(0), m_stepSize(0)
{

}

MinMaxRange::MinMaxRange(int min_, int step_, int max_) : m_min(min_), m_max(max_), m_stepSize(step_)
{

}

MinMaxRange::MinMaxRange(int min_, int max_) : m_min(min_), m_max(max_), m_stepSize(1)
{

}

int MinMaxRange::getMin() const
{
  return m_min;
}

int MinMaxRange::getMax() const
{
  return m_max;
}

int MinMaxRange::getStep() const
{
  return m_stepSize;
}
