#ifndef FileProcessorsBase_h__
#define FileProcessorsBase_h__
#include "sct/lagacy/xml_input_file.hh"
#include "sct/lagacy/setup_description.hh"
#include "TFile.h"
#include "sct/platform.hh"

#ifndef __CINT__
#include "sct/FileProcessors/rootEventRunOutput.hh"
#include "sct/FileProcessors/FileProberties.hh"
#include <memory>
#include "sct/internal/factory.hh"
#endif

template <typename T>
void xml_print(const std::string& tag, const T& value) {
  std::cout << tag << ":  " << value << std::endl;
}
#define register_file_processor(class_type,class_name) registerClass(FileProcessorsBase,class_type,class_name)

class DllExport FileProcessorsBase {
public:
  typedef std::string MainType;
  typedef std::string Parameter_t;
  typedef const std::string& Parameter_ref;
  FileProcessorsBase();
  virtual ~FileProcessorsBase();
  void setOutputName(const char* name);
  void push_files(const char* _fileName, double Threshold, double runNumber, double HV);

  int Add_XML_RunList(const std::string& xmlInputFileName, std::string path__, std::string outputPath = ".", int element = -1);

  void setGearFile(const char* name);
  void setPrintout(bool print);
  bool process();
  virtual void saveHistograms(TFile* outPutFile , double residual_min, double residual_max) = 0;

  const XML_imput_file* get_xml_input() const;
  const Xgear* get_gear() const;
protected:
#ifndef __CINT__
  std::shared_ptr<rootEventRunOutput> m_outputl;


private:
  virtual std::string get_suffix() const = 0;

  std::shared_ptr<XML_imput_file> m_input_files_xml;

  void process_set_run_prob(const FileProberties& fileP);


  std::shared_ptr<Xgear> m_gear;


  void start_collection(TFile* file__);
  virtual  bool process_file(FileProberties* fileP) = 0;
  virtual void end_collection() {}


  std::vector<FileProberties> m_files;



  std::string m_outname;

#endif
};


DllExport std::unique_ptr<FileProcessorsBase> create_processor(const FileProcessorsBase::MainType& type ="standard",FileProcessorsBase::Parameter_ref param_="");
#endif // FileProcessorsBase_h__
