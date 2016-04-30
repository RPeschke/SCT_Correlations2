#include "sct/FileProcessors/FileProcessorsBase.hh"
#include <iostream>
#include "TCanvas.h"
#include "sct/internal/factoryDef.hh"
#include "TH1.h"
#include "TProfile.h"
#include "sct/internal/sct_exceptions.hh"
registerBaseClassDef(FileProcessorsBase);








FileProcessorsBase::FileProcessorsBase()
{

}

FileProcessorsBase::~FileProcessorsBase()
{
  //std::cout << "~FileProcessorsBase() \n";
}

void FileProcessorsBase::setOutputName(const char* name)
{
  m_outname = name;
}



void FileProcessorsBase::push_files(const char* _fileName, double Threshold, double runNumber, double HV)
{
  FileProberties p;
  p.m_fileName = _fileName;

  p.m_Threshold = Threshold;
  p.m_runNumber = runNumber;
  p.m_HV = HV;
  m_files.push_back(p);
}

int FileProcessorsBase::Add_XML_RunList(const std::string& xmlInputFileName, std::string path__, std::string outputPath /*= "."*/, int element /*= -1*/)
{
  path__ += "/";
  auto test = XML_imput_file(xmlInputFileName.c_str());
  m_input_files_xml = std::shared_ptr<XML_imput_file>(new XML_imput_file( xmlInputFileName.c_str()));

  if (get_xml_input()->size()==0) {
    SCT_THROW("no fitter files in root file");
    return -1;
  }
  auto collname = get_xml_input()->globalConfig.CollectionName;
  if (element != -1) {
    outputPath += "/" + collname + "_" + get_suffix() + "_" + std::to_string(element) + ".root";
  }
  else {
    outputPath += "/" + collname + "_" + get_suffix() + ".root";
  }


  setOutputName(outputPath.c_str());


  setGearFile(get_xml_input()->globalConfig.gearFile.c_str());


  if (element != -1) {
    if (element >= (int)get_xml_input()->size()) {
      SCT_THROW("out of boundary. Selected element number larger then file list size");
    }
    auto& e = get_xml_input()->get_File(element);
    push_files((path__ + std::string(e.name)).c_str(), e.threshold, e.runNumber, e.HV);

  }
  else {
    for (int i = 0; i < get_xml_input()->size(); ++i) {
      auto& e = get_xml_input()->get_File(i);
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
  

  m_gear = _MAKE_SHARED1(Xgear,name);
}

void FileProcessorsBase::setPrintout(bool print)
{
 // todo
}

bool FileProcessorsBase::process()
{
  TCanvas c;

  //auto files = xml_print("files1");


  m_outputfile = new TFile(m_outname.c_str(),"recreate");
  start_collection(m_outputfile);



  for (auto &e : m_files) {


    process_file(&e);
    m_outputl->fill();
  }
  end_collection();

  m_outputfile->Write();
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

}

void FileProcessorsBase::start_collection(TFile* file__)
{
  
  m_outputl = _MAKE_SHARED1(rootEventRunOutput,collectionName_t("out"), file__->GetDirectory("/"));
}

 std::unique_ptr<FileProcessorsBase> create_processor(const FileProcessorsBase::MainType& type, FileProcessorsBase::Parameter_ref param_)
{
  return Class_factory_Utilities::Factory<FileProcessorsBase>::Create(type, param_);
}

 double BinNomialSigma(double totalHits, double DUTHits) {
   return sqrt((DUTHits / totalHits)*(1 - (DUTHits / totalHits))*(1 / totalHits));
 }



 void push2outputEvent(rootEventRunOutput& outEvent, const TH1D& quantity, const TH1D& numOfEvents, ID_t ID)
 {
   for (Int_t i = 0; i < quantity.GetNbinsX(); ++i) {
  
     outEvent.push(quantity.GetBinCenter(i),
       1,
       quantity.GetBinContent(i),
       BinNomialSigma(numOfEvents.GetBinContent(i), quantity.GetBinContent(i)),
       numOfEvents.GetBinContent(i),
       ID
       );
   }
 }

 DllExport void push2outputEvent(rootEventRunOutput& outEvent, const TProfile& quantity, ID_t ID)
 {
   for (Int_t i = 0; i <quantity.GetNbinsX(); ++i) {

     outEvent.push(quantity.GetBinCenter(i),
       1,
       quantity.GetBinContent(i),
       quantity.GetBinError(i),
       0,
       ID
       );
   }
 }
