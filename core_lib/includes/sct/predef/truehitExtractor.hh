#ifndef truehitExtractor_h__
#define truehitExtractor_h__

#include "sct/predef/plane.hh"
#include <string>
#include "sct/platform.hh"
#include "sct/processor_prob.hh"
#include "sct/lagacy/setup_description.hh"

#ifndef __CINT__
#include "sct/internal/factory.hh"
#define registerTruehitExtractor(ClassTypeName, name) registerClass(truehitExtractor,ClassTypeName,name)
#endif
class Xgear;
class fitterFile;
class FFile;
class DllExport TH_param {
public:
  TH_param();
  TH_param& set_fitterFile(fitterFile* file_);
  TH_param& set_fitterFile(FFile& file_);
  TH_param& set_gear(const Xgear* gear_);
  TH_param& set_processor_pro(processor_prob& pprob);
  fitterFile* get_fitterFile();
  processor_prob& get_processor_pro();
  const Xgear* get_gear() const;
private:
  const Xgear* m_gear;
  fitterFile* m_file;
  processor_prob m_pprob;
};

class DllExport truehitExtractor {
  
public:
  typedef std::string MainType;
  typedef TH_param Parameter_t;
  typedef TH_param& Parameter_ref;


  truehitExtractor(Parameter_ref param_);
  virtual xy_plane get_true_DUT_Hits() =0;

 protected:
   Parameter_t m_param;
};
class DllExport THE {
public:
  THE(const std::string& name, TH_param& param_);
  virtual xy_plane get_true_DUT_Hits();
  //static void register_new(const std::string& name, truehitExtractor* (fun)(truehitExtractor::Parameter_ref param_));
private:

#ifndef __CINT__
  std::shared_ptr<truehitExtractor> m_the;
#endif // !__CINT__


};
DllExport void register_truehitExtractor(const truehitExtractor::MainType& name, truehitExtractor* (fun)(truehitExtractor::Parameter_ref param_));
DllExport std::unique_ptr<truehitExtractor> create_truehitExtractor(truehitExtractor::Parameter_ref param_, const truehitExtractor::MainType& type);

#endif // truehitExtractor_h__
