#include "sct//legacy/xml_input_file.hh"
#include "sct/legacy/xml_util.hh"
#include "rapidxml_utils.hpp"
#include "sct/internal/sct_exceptions.hh"
#include "rapidxml.hpp"
#include "sct/internal/ScopeGuard.hh"


template<typename T>
auto getNode(T* inNote, const char* name) {
  auto outNode = inNote->first_node(name);
  if (!outNode) SCT_THROW("Node not found! nodeName: <" + std::string(name) + "> ");
  return outNode;
}

template<typename T>
T getAtributeFromNote(rapid_xml_node* xIn, const std::string& NodeName, const std::string& AtributeName) {
  auto node = getNode(xIn->value, NodeName.c_str());
  return xml_util::getAtribute<T>(node, AtributeName.c_str());

}
template<>
std::string getAtributeFromNote<std::string>(rapid_xml_node* xIn, const std::string& NodeName, const std::string& AtributeName) {
  auto node = getNode(xIn->value, NodeName.c_str());
  return  xml_util::getAtribute_string(node, AtributeName.c_str());
}



const S_Cut& xml_globalConfig::cut() const {
  return  m_cut;
}



const char* xml_file::NodeName() {
  return "file";
}


XML_imput_file::XML_imput_file(const char* name) {
  SCOPE_GUARD_START{
    rapidxml::file<> file_(name);
    rapidxml::xml_document<> doc_;
    doc_.parse<0>(file_.data());    // 0 means default parse flags

    auto RunCollection_n = getNode(&doc_, "RunCollection");
    auto node2 = getNode(RunCollection_n, "globalConfig");

    rapid_xml_node gconfig(node2);
    globalConfig = xml_globalConfig(&gconfig);


    auto fileList_n = getNode(RunCollection_n, "fileList");

    m_files = xml_util::getVectorOfT<xml_file>(fileList_n);
  }SCOPE_GUARD_END_CONTINUE
}

XML_imput_file::XML_imput_file() {

}

XML_imput_file::XML_imput_file(const XML_imput_file& rhs) {
  globalConfig = rhs.globalConfig;

  m_files = rhs.m_files;
}

XML_imput_file& XML_imput_file::operator=(const XML_imput_file& rhs) {
  globalConfig = rhs.globalConfig;

  m_files = rhs.m_files;
  return *this;
}

xml_file& XML_imput_file::get_File(int id) {
  return m_files.at(id);
}

const xml_file& XML_imput_file::get_File(int id) const {
  return m_files.at(id);
}

int XML_imput_file::size() const {
  return  m_files.size();
}


xml_globalConfig::xml_globalConfig(rapid_xml_node* xIn) {
  SCOPE_GUARD_START{
    if (!xIn) SCT_THROW("Input is nullptr");
    CollectionName = getAtributeFromNote<std::string>(xIn,"CollectionName", "value");

    NumberOfBins = getAtributeFromNote<int>(xIn,"NumberOfBins", "value");
    NumberOfStrips = getAtributeFromNote<int>(xIn, "NumberOfStrips", "value");


    Device == getAtributeFromNote<int>(xIn, "Device", "value");


    auto min_ = getAtributeFromNote<int>(xIn, "AvtiveStrips", "min");
    auto max_ = getAtributeFromNote<int>(xIn, "AvtiveStrips", "max");

    AvtiveStrips = MinMaxRange(min_, max_);

    Rotation = getAtributeFromNote<double>(xIn, "Rotation", "value");

    Position_name = getAtributeFromNote<std::string>(xIn, "Position", "name");

    Position_value = getAtributeFromNote<double>(xIn, "Position", "value");
    residual_cut = getAtributeFromNote<double>(xIn, "residual_cut", "value");
    gearFile = getAtributeFromNote<std::string>(xIn, "gearFile", "name");


    auto ymin_ = getAtributeFromNote<double>(xIn, "YCut", "min");
    auto ymax_ = getAtributeFromNote<double>(xIn, "YCut", "max");
    auto xmin_ = getAtributeFromNote<double>(xIn, "XCut", "min");
    auto xmax_ = getAtributeFromNote<double>(xIn, "XCut", "max");
    m_cut = S_YCut(ymin_, ymax_) + S_XCut(xmin_, xmax_);



    FitterFileType = getAtributeFromNote<std::string>(xIn, "FitterFileType", "name");
    DUT2TrackCorrelator = getAtributeFromNote<std::string>(xIn, "DUT2TrackCorrelator", "name");
    TrueHitExtractor = getAtributeFromNote<std::string>(xIn, "TrueHitExtractor", "name");
  }SCOPE_GUARD_END_CONTINUE
}

xml_globalConfig::xml_globalConfig() {

}

xml_globalConfig::xml_globalConfig(const xml_globalConfig& rhs) {
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

xml_globalConfig& xml_globalConfig::operator=(const xml_globalConfig& rhs) {
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

xml_file::xml_file(rapid_xml_node* xIn) {
  name = getAtributeFromNote<std::string>(xIn, "name", "value");

  threshold = getAtributeFromNote<double>(xIn, "threshold", "value");

  HV = getAtributeFromNote<double>(xIn, "HV", "value");
  runNumber = getAtributeFromNote<int>(xIn, "runNumber", "value");


}

xml_file::xml_file() {

}

xml_file::xml_file(const xml_file& rhs) {
  name = rhs.name;
  threshold = rhs.threshold;

  HV = rhs.HV;
  runNumber = rhs.runNumber;
}

xml_file& xml_file::operator=(const xml_file& rhs) {
  name = rhs.name;
  threshold = rhs.threshold;

  HV = rhs.HV;
  runNumber = rhs.runNumber;
  return *this;
}

MinMaxRange::MinMaxRange() :m_min(0), m_max(0), m_stepSize(0) {

}

MinMaxRange::MinMaxRange(int min_, int step_, int max_) : m_min(min_), m_max(max_), m_stepSize(step_) {

}

MinMaxRange::MinMaxRange(int min_, int max_) : m_min(min_), m_max(max_), m_stepSize(1) {

}

int MinMaxRange::getMin() const {
  return m_min;
}

int MinMaxRange::getMax() const {
  return m_max;
}

int MinMaxRange::getStep() const {
  return m_stepSize;
}
