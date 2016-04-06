#include "sct/FileProcessors/FileProcessorsBase.hh"
#include <iostream>
#include "TCanvas.h"


#define  SCT_THROW(X)  std::cout<<X<<std::endl

FileProcessorsBase::FileProcessorsBase()
{

}

FileProcessorsBase::~FileProcessorsBase()
{

}

void FileProcessorsBase::setOutputName(const char* name)
{
  m_outname = name;
}

void FileProcessorsBase::push_files(TFile* _file, double Threshold, double runNumber)
{
  FileProberties p;
  p.setTFile(_file);
  p.m_Threshold = Threshold;
  p.m_runNumber = runNumber;
  m_files.push_back(p);
}

void FileProcessorsBase::push_files(const char* _fileName, double Threshold, double runNumber, double HV)
{
  FileProberties p;
  p.setTFile(std::shared_ptr<TFile>(new TFile(_fileName)));
  if (!p.getTfile()->IsOpen()) {

    return;
  }

  p.m_Threshold = Threshold;
  p.m_runNumber = runNumber;
  p.m_HV = HV;
  m_files.push_back(p);
}

int FileProcessorsBase::Add_XML_RunList(const std::string& xmlInputFileName, std::string path__, std::string outputPath /*= "."*/, int element /*= -1*/)
{
  path__ += "/";
  m_input_files_xml = std::make_shared<XML_imput_file>(xmlInputFileName.c_str());

  if (m_input_files_xml->size()==0) {
    SCT_THROW("no fitter files in root file");
    return -1;
  }
  auto collname = m_input_files_xml->globalConfig.CollectionName;
  if (element != -1) {
    outputPath += "/" + collname + "_" + get_suffix() + "_" + std::to_string(element) + ".root";
  }
  else {
    outputPath += "/" + collname + "_" + get_suffix() + ".root";
  }


  setOutputName(outputPath.c_str());


  setGearFile(m_input_files_xml->globalConfig.gearFile.c_str());


  if (element != -1) {
    if (element >= (int)m_input_files_xml->size()) {
      SCT_THROW("out of boundary. Selected element number larger then file list size");
    }
    auto& e = m_input_files_xml->get_File(element);
    push_files((path__ + std::string(e.name)).c_str(), e.threshold, e.runNumber, e.HV);

  }
  else {
    for (int i = 0; i < m_input_files_xml->size(); ++i) {
      auto& e = m_input_files_xml->get_File(i);
      push_files((path__ + std::string(e.name)).c_str(), e.threshold, e.runNumber, e.HV);
    }

  }
  if (m_files.empty()) {
    SCT_THROW("not input file found");
  }

  return 0;
}

void FileProcessorsBase::setGearFile(const char* name)
{
  

  m_gear = std::make_shared<Xgear>(name);
}

void FileProcessorsBase::setPrintout(bool print)
{
 // todo
}

bool FileProcessorsBase::process()
{
  TCanvas c;

  //auto files = xml_print("files1");


  auto _file1 = new TFile(m_outname.c_str(),"recreate");
  start_collection(_file1);



  for (auto &e : m_files) {

    process_set_run_prob(e);
    process_file(&e);
    m_outputl->fill();
  }
  end_collection();

  _file1->Write();

  return true;
}

const XML_imput_file* FileProcessorsBase::get_xml_input() const
{
  return m_input_files_xml.get();
}

const Xgear* FileProcessorsBase::get_gear() const
{
  return m_gear.get();
}

void FileProcessorsBase::process_set_run_prob(const FileProberties& fileP)
{
 // xml_print("fileName", fileP.getTfile()->GetName());
  m_outputl->reset();

  //xml_print("m_runNumber", fileP.m_runNumber);
  m_outputl->set_RunNumber(fileP.m_runNumber);


 // xml_print("threshold", fileP.m_Threshold);
  m_outputl->set_Threshold(fileP.m_Threshold);

  //xml_print("HV", fileP.m_HV);
  m_outputl->set_HV(fileP.m_HV);
}

void FileProcessorsBase::start_collection(TFile* file__)
{
  
  m_outputl = std::make_shared<rootEventRunOutput>("out", file__->GetDirectory("/"));
}
