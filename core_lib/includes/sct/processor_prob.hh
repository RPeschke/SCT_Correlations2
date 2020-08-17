#ifndef processor_prob_h__
#define processor_prob_h__
#include <string>
#include <vector>
#include "sct/collection.h"
#include "sct/platform.hh"
class ProcessorCollection;
class DllExport processor_prob {
public:
  processor_prob();
  processor_prob& save2Disk();
  processor_prob& dontSave2Disk();
  processor_prob& setName(const processorName_t& name);
  processor_prob& addAxis(const axesName_t& AxisName);
  processor_prob& setAxis(const std::vector<axesName_t>& AxisNames);
  processor_prob& setProcessorCollection(ProcessorCollection* PC);
  processorName_t name = processorName_t("");
  SaveOption getSave() const;
  ProcessorCollection* ProcessorColl = nullptr;
  std::vector<axesName_t> axisNames;
  static void EnableDebugSave();
  static void DisableDebugSave();
private:
  SaveOption save = DontSave2Disk;
};

DllExport void ___set_GTemp();
DllExport bool ___get_GTemp();
DllExport void ___set_GName(processorName_t name);
DllExport processorName_t ___get_GName();

DllExport processor_prob saveWithRandomName(const processorName_t& name= processorName_t("random__"));
DllExport processor_prob DontsaveWithRandomName(const processorName_t& name = processorName_t("random__"));


#endif // processor_prob_h__
