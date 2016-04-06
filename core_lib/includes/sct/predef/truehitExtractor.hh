#ifndef truehitExtractor_h__
#define truehitExtractor_h__

#include "sct/predef/plane.hh"
#include "sct/internal/factory.hh"
#include <string>
#include "sct/platform.hh"
#include "sct/processor_prob.hh"
#include "sct/lagacy/setup_description.hh"
#define registerTruehitExtractor(ClassTypeName, name) registerClass(truehitExtractor,ClassTypeName,name)

class Xgear;
class fitterFile;

class DllExport TH_param {
public:
  TH_param();
  TH_param& set_fitterFile(fitterFile* file_);
  TH_param& set_gear(Xgear* gear_);
  TH_param& set_processor_pro(processor_prob& pprob);
  fitterFile* get_fitterFile();
  processor_prob& get_processor_pro();
  Xgear* get_gear();
private:
  Xgear* m_gear;
  fitterFile* m_file;
  processor_prob m_pprob;
};

class DllExport truehitExtractor {
  
public:
  using MainType = std::string;
  using Parameter_t = TH_param;
  using Parameter_ref = TH_param&;

  truehitExtractor(Parameter_ref param_);
  virtual xy_plane get_true_DUT_Hits() =0;

 protected:
   Parameter_t m_param;
};
DllExport void register_truehitExtractor(const truehitExtractor::MainType& name, truehitExtractor* (fun)(truehitExtractor::Parameter_ref param_));
DllExport std::unique_ptr<truehitExtractor> create_truehitExtractor(truehitExtractor::Parameter_ref param_, const truehitExtractor::MainType& type);

#endif // truehitExtractor_h__
