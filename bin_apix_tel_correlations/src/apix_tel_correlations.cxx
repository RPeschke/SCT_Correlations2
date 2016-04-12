
#include "sct/lagacy/xml_input_file.hh"
#include "TFile.h"
#include "TError.h"
#include "TCanvas.h"
#include "tclap/CmdLine.h"
#include "TH2.h"
#include "sct/predef/fitterFile.hh"
#include "sct/lagacy/setup_description.hh"
#include "sct/xy_processors/converters.hh"
#include "sct/processor_prob.hh"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/ProcessorCollection.h"
#include "sct/lagacy/Draw.h"
#include "sct/lagacy/SCT_helpers.hh"


std::vector<TCanvas*> gCanvas;
TBrowser* gBrowser = NULL;


using namespace std;
using namespace TCLAP;

void remove_root_printouts() {
  gErrorIgnoreLevel = kError;  // ignoring root printouts (replace of histograms) 
}

struct  inParam {
  int argc;
  char **argv;
};


void add2File(TFile* file_, TH2* h, const char* name) {
  h->SetTitle(name);
  h->SetName(name);
  file_->Add(h);
}

int main(int argc, char **argv) {
  int argc_asdasddsa = 1;
  char **argv_sadsda = new char*[1];
  argv_sadsda[0] = "dummy";
#ifdef _DEBUG
  TApplication theApp("App", &argc_asdasddsa, argv_sadsda);
#endif // _DEBUG




  CmdLine cmd("ProcessFile", ' ', "0.1");

  ValueArg<std::string> FileNameArg("i", "inFile", "xml filename", true, "", "string");
  cmd.add(FileNameArg);
  ValueArg<std::string>  inPath("p", "inPath", "path to the root files", true, ".", "string");
  cmd.add(inPath);
  ValueArg<std::string>  output_path("o", "outPath", "output path", false, "output.root", "string");
  ValueArg<int> element("e", "element", "element of interest  in the XML file", true, 1, "int");
  cmd.add(element);
  cmd.parse(argc, argv);  //terminates on error


  auto m_input_files_xml = std::make_shared<XML_imput_file>(FileNameArg.getValue().c_str());


  auto file_path = (inPath.getValue() + "/" + m_input_files_xml->get_File(element.getValue()).name);
  std::cout << "opening file path: " << file_path << std::endl;
    FFile fitter_file_(file_path.c_str());

    Xgear gear(m_input_files_xml->globalConfig.gearFile.c_str());

  TFile * out_file = new TFile(output_path.getValue().c_str(), "recreate");

  auto apix_local = convert::zs_data_to_hits_GBL(
    fitter_file_.apix_zs_data(),
    *gear.detector.layer_by_ID(20),
    DontsaveWithRandomName("apix_local")
    );
  auto apix_global = convert::local_to_global(
    apix_local,
    *gear.detector.layer_by_ID(20),
    DontsaveWithRandomName("apix_global")
    );
  auto apix_local_8 = convert::global_to_local(
    apix_global,
    *gear.detector.layer_by_ID(8),
    DontsaveWithRandomName("apix_local_8")
    );
  
  auto corr_xx = xy_pro::correlations(apix_local_8.get_x(), fitter_file_.DUT_fitted_local_GBL().get_x());
  auto corr_yy = xy_pro::correlations(apix_local_8.get_y(), fitter_file_.DUT_fitted_local_GBL().get_y());

  fitter_file_.getProcessorCollection()->loop();

  TH2D h_local("corr_xx", "corr_xx", 100, 0, 0, 100, 0, 0);
  Draw(corr_xx, DrawOption().output_object(&h_local));
  

//   auto h =SCT_helpers::Draw<TH2>(corr_xx,S_DrawOption());
//   auto h_local = (TH2*)h->Clone("corr_xx");
   auto p = SCT_helpers::LinearFit_Of_Profile(&h_local, 20);
   h_local.Draw("colz");
   p.Draw("same");
   p.Print();


  new TCanvas();

  TH2D h1_local("corr_yy", "corr_yy", 100, 0, 0, 100, 0, 0);
  Draw(corr_yy,DrawOption().output_object(&h1_local));
//   auto h1 = SCT_helpers::Draw<TH2>(corr_yy, S_DrawOption());
//   auto h1_local = (TH2*)h1->Clone("corr_yy");
   auto p1 = SCT_helpers::LinearFit_Of_Profile(&h1_local, 20);
   h1_local.Draw("colz");
   p1.Draw("same");
   p1.Print();
//   
   out_file->Add(&h_local);
   out_file->Add(&h1_local);
   out_file->Write(); 
#ifdef _DEBUG
  theApp.Run();
#endif // _DEBUG
  return 0;
}




