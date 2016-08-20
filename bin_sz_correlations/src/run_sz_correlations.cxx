#include "TCanvas.h"
#include "tclap/CmdLine.h"
#include "TError.h"
#include "TFile.h"
#include "TH2D.h"
#include "sct/legacy/s_cuts.h"
#include "sct/predef/fitterFile.hh"
#include "sct/processor_prob.hh"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/legacy/SCT_helpers.hh"

#include "sct/ProcessorCollection.h"
#include "sct/legacy/Draw.h"
#include "TApplication.h"
#include "TBrowser.h"





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

  remove_root_printouts();
#ifdef _DEBUG
  int argc_asdasddsa = 1;
  char **argv_sadsda = new char*[1];
  argv_sadsda[0] = "dummy";
  TApplication theApp("App", &argc_asdasddsa, argv_sadsda);
#endif // _DEBUG



  CmdLine cmd("ProcessFile", ' ', "0.1");
  ValueArg<std::string> FileNameArg("i", "inFile", "root filename", true, "", "string");
  cmd.add(FileNameArg);


  ValueArg<std::string> outFileNameArg("o", "outFile", "output root file", false, "dummy.root", "string");
  cmd.add(outFileNameArg);
  SwitchArg forceSave("f", "forceToSave", "Force all Collections To be stored to disk", false);
  cmd.add(forceSave);

  cmd.parse(argc, argv);  //terminates on error

  if (forceSave.getValue()) {
    processor_prob::EnableDebugSave();
  }

  FFile file_(FileName_t(FileNameArg.getValue()));

  TFile * file_1 = new TFile(outFileNameArg.getValue().c_str(), "recreate");




  auto sz_dut = file_.DUT_zs_data();
  auto sz_tel = file_.tel_zs_data(ID_t(3));
  auto apix = file_.apix_zs_data();
  auto cuted = xy_pro::cut_xy(sz_tel, S_XCut(300) + S_YCut(300), DontsaveWithRandomName(processorName_t("cutted")));


  auto corr = xy_pro::correlations(sz_dut.get_x(), apix.get_y(), processor_prob().setName(processorName_t("correlation_x_y")).save2Disk());
  auto corryx = xy_pro::correlations(sz_dut.get_y(), apix.get_x(), processor_prob().setName(processorName_t("correlation_x_y")).save2Disk());
  auto corrxx = xy_pro::correlations(sz_dut.get_x(), apix.get_x(), processor_prob().setName(processorName_t("correlation_x_y")).save2Disk());
  auto corryy = xy_pro::correlations(sz_dut.get_y(), apix.get_y(), processor_prob().setName(processorName_t("correlation_x_y")).save2Disk());




  auto sz_dut_normalized = xy_pro::transform(sz_dut, x_slope_t(0.0745), x_offset_t(0), y_slope_t(1), y_offset_t(0), DontsaveWithRandomName(processorName_t("sz_dut_normalized")));
  auto sz_tel_normalized = xy_pro::transform(apix, x_slope_t(2.500000000e-01), x_offset_t(0),y_slope_t(5.000000000e-02), y_offset_t(0), DontsaveWithRandomName(processorName_t("sz_tel_normalized")));
  auto res = xy_pro::residual(sz_dut_normalized.get_x(), sz_tel_normalized.get_x());
  file_.getProcessorCollection()->loop();
  new TCanvas();
  TH2D th_x_y("correlation_DUT_X_vs_Tel_Y", "correlation_DUT_X_vs_Tel_Y", 100, 0, 0, 100, 0, 0);
  Draw(corr, DrawOption().output_object(&th_x_y));
  add2File(file_1, &th_x_y, "correlation_DUT_X_vs_Tel_Y");



  new TCanvas();
  TH2D th_y_x("correlation_DUT_Y_vs_Tel_X", "correlation_DUT_Y_vs_Tel_X", 100, 0, 0, 100, 0, 0);
  Draw(corryx, DrawOption().output_object(&th_y_x));
  add2File(file_1, &th_y_x, "correlation_DUT_Y_vs_Tel_X");


  new TCanvas();
  TH2D th_x_x("DUT_X_vs_Tel_X", "DUT_X_vs_Tel_X", 100, 0, 0, 100, 0, 0);
  Draw(corrxx, DrawOption().output_object(&th_x_x));
  add2File(file_1, &th_x_x, "correlation DUT_X_vs_Tel_X");

  new TCanvas();

  TH2D th_y_y("correlation_DUT_Y_vs_Tel_Y", "correlation_DUT_Y_vs_Tel_Y", 100, 0, 0, 100, 0, 0);
  Draw(corryy, DrawOption().output_object(&th_x_x));
  add2File(file_1, &th_y_y, "correlation_DUT_Y_vs_Tel_Y");

  new TCanvas();

  TH2D th2("correlation_over_time", "correlation_over_time", 100, 0, 0, 100, 0, 0);
  Draw(res, DrawOption().output_object(&th_x_x));
  add2File(file_1, &th2, "correlation_over_time");

  file_1->Write();
#ifdef _DEBUG
  new TBrowser();
  theApp.Run();
#endif // _DEBUG
  return 0;
}








