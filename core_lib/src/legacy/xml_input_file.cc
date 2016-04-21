#include "sct//legacy/xml_input_file.hh"
#include "sct/legacy/xml_util.hh"
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

XML_imput_file::XML_imput_file()
{

}

XML_imput_file::XML_imput_file(const XML_imput_file& rhs)
{
  globalConfig =rhs.globalConfig;

  m_files =rhs.m_files;
}

XML_imput_file& XML_imput_file::operator=(const XML_imput_file& rhs)
{
  globalConfig = rhs.globalConfig;

  m_files = rhs.m_files;
  return *this;
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
  FitterFileType = xml_util::getAtribute_string(xIn->value->first_node("FitterFileType"), "name");
  DUT2TrackCorrelator = xml_util::getAtribute_string(xIn->value->first_node("DUT2TrackCorrelator"), "name");
  TrueHitExtractor = xml_util::getAtribute_string(xIn->value->first_node("TrueHitExtractor"), "name");


  m_cut = S_YCut(ymin_, ymax_) + S_XCut(xmin_, xmax_);
  
}

xml_globalConfig::xml_globalConfig()
{

}

xml_globalConfig::xml_globalConfig(const xml_globalConfig& rhs)
{
 CollectionName = rhs.CollectionName;

  NumberOfBins = rhs.NumberOfBins;
  NumberOfStrips = rhs.NumberOfStrips;

  Device = rhs.Device;

  AvtiveStrips = rhs.AvtiveStrips;
  Rotation = rhs.Rotation;

  Position_name = rhs.Position_name;
  Position_value = rhs.Position_value;
  residual_cut = rhs.residual_cut;
  gearFile = rhs.gearFile;
  m_cut = rhs.m_cut;
  FitterFileType = rhs.FitterFileType;
  DUT2TrackCorrelator = rhs.DUT2TrackCorrelator;
  TrueHitExtractor = rhs.TrueHitExtractor;
}

xml_globalConfig& xml_globalConfig::operator=(const xml_globalConfig& rhs)
{
  CollectionName = rhs.CollectionName;

  NumberOfBins = rhs.NumberOfBins;
  NumberOfStrips = rhs.NumberOfStrips;

  Device = rhs.Device;

  AvtiveStrips = rhs.AvtiveStrips;
  Rotation = rhs.Rotation;

  Position_name = rhs.Position_name;
  Position_value = rhs.Position_value;
  residual_cut = rhs.residual_cut;
  gearFile = rhs.gearFile;
  m_cut = rhs.m_cut;

  FitterFileType = rhs.FitterFileType;
  DUT2TrackCorrelator = rhs.DUT2TrackCorrelator;
  TrueHitExtractor = rhs.TrueHitExtractor;
  return *this;
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

xml_file::xml_file(const xml_file& rhs)
{
  name =rhs.name;
  threshold = rhs.threshold;

  HV =rhs.HV;
  runNumber = rhs.runNumber;
}

xml_file& xml_file::operator=(const xml_file& rhs)
{
  name = rhs.name;
  threshold = rhs.threshold;

  HV = rhs.HV;
  runNumber = rhs.runNumber;
  return *this;
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
