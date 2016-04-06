#ifndef processor_prob_h__
#define processor_prob_h__
#include <string>
#include <vector>
#include "sct/collection.h"
#include "sct/platform.hh"
class ProcessorCollection;
class DllExport processor_prob {
public:
  processor_prob& save2Disk();
  processor_prob& dontSave2Disk();
  processor_prob& setName(const std::string& name);
  processor_prob& addAxis(const std::string& AxisName);
  processor_prob& setAxis(const std::vector<std::string>& AxisNames);
  processor_prob& setProcessorCollection(ProcessorCollection* PC);
  std::string name;
  SaveOption save = DontSave2Disk;
  ProcessorCollection* ProcessorColl = nullptr;
  std::vector<std::string> axisNames;
};

DllExport processor_prob saveWithRandomName(const std::string& name="random__");
DllExport processor_prob DontsaveWithRandomName(const std::string& name = "random__");
#endif // processor_prob_h__
