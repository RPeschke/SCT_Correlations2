
#include "sct/FileProcessors/FileProcessorsBase.hh"

#include "TError.h"

#include "TApplication.h"
#include "TBrowser.h"

#include "TF1.h"
#include "TProfile.h"


#include "tclap/CmdLine.h"
#include <iostream>
#include "TCanvas.h"
#include <thread>

#include "TSystem.h"
#include "sct/processor_prob.hh"


using namespace TCLAP;
using namespace std;







std::string trim(const std::string &s) {
  static const std::string spaces = " \t\n\r\v";
  size_t b = s.find_first_not_of(spaces);
  size_t e = s.find_last_not_of(spaces);
  if (b == std::string::npos || e == std::string::npos) {
    return "";
  }
  return std::string(s, b, e - b + 1);
}

std::vector<std::string> split(const std::string &str,
  const std::string &delim, bool dotrim) {
  std::string s(str);
  std::vector<std::string> result;
  if (str == "")
    return result;
  size_t i;
  while ((i = s.find_first_of(delim)) != std::string::npos) {
    result.push_back(dotrim ? trim(s.substr(0, i)) : s.substr(0, i));
    s = s.substr(i + 1);
  }
  result.push_back(s);
  return result;
}

class min_max {
public:   
  double m_min = 0, m_max=0;
};
min_max make_range(const std::string& r_) {
  auto r = split(r_, ":", true);

  if (r.size() == 3) {
    min_max ret;
    ret.m_min = stof(r[0]);
    ret.m_max = stof(r[2]);
    return ret;
  }
  else if (r.size() == 2) {
    min_max ret;
    ret.m_min = stof(r[0]);
    ret.m_max = stof(r[1]);
    return ret;
  }

  std::cout << "error processing range " << r_ << std::endl;
  return     min_max();


}



std::string getPath(ValueArg<std::string>& fileName,   ValueArg<std::string> & path_) {

  if (path_.isSet()) {
    return path_.getValue();
  }

  std::string ret = "./";
  if (fileName.isSet()) {
    ret = fileName.getValue();

    auto last = ret.find_last_of("/\\");
    ret = ret.substr(0,last+1);
    
  }

  return ret;
}


int main(int argc, char **argv) {
  


    CmdLine cmd("ProcessFile", ' ', "0.1");
    ValueArg<std::string> FileNameArg("i", "inFile", "xml filename", true, "", "string");
    cmd.add(FileNameArg);
    ValueArg<std::string>  inPath("p", "inPath", "path to the root files",false, "", "string");
    cmd.add(inPath);
    ValueArg<std::string>  output_path("o", "outPath", "output path", false, "dummy.root", "string");
    cmd.add(output_path);
    ValueArg<std::string>  processor_type("s", "Processor", "which processor to use Standard or Modulo", false, "standard", "string");
    cmd.add(processor_type);
    ValueArg<int> element("e", "element", "element of interest  in the XML file", true, 1, "int");
    cmd.add(element);

    ValueArg<std::string> residualRange("c", "residualCut", "range for the residual -r -10:10 => min =-10 , max = 10  ", false, "-10:10", "range");

    cmd.add(residualRange);
    SwitchArg forceSave("f", "forceToSave", "Force all Collections To be stored to disk", false);
    cmd.add(forceSave);

    cmd.parse(argc, argv);  //terminates on error
    if (forceSave.getValue()) {
      processor_prob::EnableDebugSave();
    }
    TFile * __file1 = new TFile(output_path.getValue().c_str(), "recreate");


    auto p= create_processor(processor_type.getValue());
    if (!p)
    {
      return -1;
    }
    p->setPrintout(true);

    gErrorIgnoreLevel = kError;  // ignoring root printouts (replace of histograms) 

    auto path_ = getPath(FileNameArg, inPath);
    
    p->Add_XML_RunList(FileNameArg.getValue(), path_, ".", element.getValue());

#ifdef _DEBUG
  //  TApplication theApp("App", &argc, argv);
#endif // _DEBUG

    p->process();

    auto  r = make_range(residualRange.getValue());
    p->saveHistograms(__file1, r.m_min,r.m_max);

    __file1->Write();


#ifdef _DEBUG
    new TBrowser();

  //  theApp.Run();
#endif // _DEBUG







  return 0;


}
