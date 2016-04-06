#ifndef xml_input_file_h__
#define xml_input_file_h__


#include <string>
#include <vector>

#include "sct/platform.hh"
#include "sct/lagacy/s_cuts.h"


class rapid_xml_node;




class DllExport MinMaxRange {
public:
  MinMaxRange(int min_, int max_);
  MinMaxRange(int min_, int step_, int max_);
  MinMaxRange();
  int getMin() const;
  int getMax() const;
  int getStep() const;
private:
  int m_min, m_max, m_stepSize;

};

class DllExport xml_globalConfig {
public:
  xml_globalConfig(rapid_xml_node* xIn);
  xml_globalConfig();
  std::string CollectionName;

  int NumberOfBins;
  int NumberOfStrips;
  const S_Cut& cut() const;

  int Device;

  MinMaxRange AvtiveStrips;
  double Rotation;

  std::string Position_name;
  double Position_value;
  double residual_cut;
  std::string gearFile;

private:
#ifndef __CINT__
  mutable  S_CutCoollection m_cut = S_YCut(-10000000, 100000000000) + S_XCut(-10000, 10000);
#endif
};
class DllExport xml_file {
public:
  xml_file(rapid_xml_node* xIn);
  static const char* NodeName();
  xml_file();
  std::string name;
//    return xml_util::getAtribute_string(m_node->first_node("name"), "value");
  double threshold;
//    return xml_util::getAtribute<double>(m_node->first_node("threshold"), "value");
  
  double HV;
//    return xml_util::getAtribute<double>(m_node->first_node("HV"), "value");
  int runNumber;
//    return xml_util::getAtribute<int>(m_node->first_node("runNumber"), "value");
};
class DllExport XML_imput_file {
public:
  XML_imput_file(const char* name);

  xml_file& get_File(int id);

  const xml_file& get_File(int id) const;
  int size() const;
  xml_globalConfig globalConfig;
private:
  std::vector<xml_file> m_files;
};


#endif // xml_input_file_h__
