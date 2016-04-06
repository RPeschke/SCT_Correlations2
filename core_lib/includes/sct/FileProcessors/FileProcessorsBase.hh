#ifndef FileProcessorsBase_h__
#define FileProcessorsBase_h__
#include "sct/lagacy/xml_input_file.hh"
#include "sct/lagacy/setup_description.hh"
#include "TFile.h"
#include "sct/platform.hh"
#include <memory>
#include "sct/FileProcessors/FileProberties.hh"
#include "sct/FileProcessors/rootEventRunOutput.hh"



class DllExport FileProcessorsBase {
public:
  using MainType = std::string;
  using Parameter_t = std::string;
  using Parameter_ref = const std::string&;
  FileProcessorsBase();
  virtual ~FileProcessorsBase();
  void setOutputName(const char* name);
  void push_files(TFile* _file, double Threshold, double runNumber);
  void push_files(const char* _fileName, double Threshold, double runNumber, double HV);

  int Add_XML_RunList(const std::string& xmlInputFileName, std::string path__, std::string outputPath = ".", int element = -1);

  void setGearFile(const char* name);
  void setPrintout(bool print);
  bool process();
  virtual void saveHistograms(TFile* outPutFile , double residual_min, double residual_max) = 0;

  const XML_imput_file* get_xml_input() const;
  const Xgear* get_gear() const;
protected:
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

};

#endif // FileProcessorsBase_h__
