
#include "sct/legacy/xml_input_file.hh"
#include "TFile.h"
#include "TError.h"
#include "TCanvas.h"
#include "tclap/CmdLine.h"
#include "TH2.h"
#include "sct/predef/fitterFile.hh"
#include "sct/legacy/setup_description.hh"
#include "sct/xy_processors/converters.hh"
#include "sct/processor_prob.hh"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/ProcessorCollection.h"
#include "sct/legacy/Draw.h"
#include "sct/legacy/SCT_helpers.hh"
#include "TApplication.h"
#include "sct/internal/strong_types.h"
#include "sct/legacy/xml_print.hh"



#include "sct/EUTFile.h"
#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "sct/ref_ptr.hh"
#include "sct/generic_processors/processor_cut_axis.hh"
#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/generic_operator.hh"
#include "sct/generic_processors/processor_generic_correlation.hh"
#include "sct/generic_processors/processor_normalize_on_first_plane.hh"

#include "sct/generic_processors/processor_generic_append_plane.hh"
#include "TMath.h"
#include "sct/generic_processors/processor_generic_make_unique_axis.hh"

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

TApplication* get_TApplication() {
  auto argc_asdasddsa =  new  int(1);
  char **argv_sadsda = new char*[1];
  argv_sadsda[0] = "dummy";
  return new TApplication("App", argc_asdasddsa, argv_sadsda);
}




int main(int argc, char **argv) {

#ifdef _DEBUG
  
 // auto theApp = get_TApplication();
#endif // _DEBUG

  auto m_file = Snew TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/t_2020-07-28.root");
  auto m_file2 = Snew TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/t23_2020-07-28.root");
  
  TFile * out_file1 = new TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/tout_2020-07-28_h.root", "recreate");


  auto m_generic = Snew EUTFile(m_file);
  auto mcparticle_file = Snew EUTFile(m_file2, m_generic->getProcessorCollection());
  
  var(all_layers_xy)  = xy_plane( m_generic->getCollection(collectionName_t("KLM_Digits"))->getPlane(ID_t(0)));
  var(all_layers) = m_generic->getCollection(collectionName_t("KLM_Digits"))->getPlane(ID_t(0));
  var(mcparticles) = mcparticle_file->getCollection(collectionName_t("t3"))->getPlane(ID_t(0));

  //auto corr_zz1 = xy_pro::correlations(p0.get_z(), p0.get_z());

  var(muons) = mcparticles[(axCut(axesName_t("PDG")) == 13 || axCut(axesName_t("PDG")) == -13) && axCut(axesName_t("mass")) <1];
  

  muons[axesName_t("theta")] = lambda3(px, py, pz) {
    return TMath::ACos(pz / TMath::Sqrt(px*px + py * py + pz * pz));
  };
  muons[axesName_t("phi")] =  lambda3(px, py, pz) {
    return TMath::ATan2(py, px);
  };
  muons[axesName_t("pseudo_z")] = lambda3(theta, py, pz) {
    return  -328.268 + 311.889 * theta;
  };
  muons[axesName_t("pseudo_y_sector1")] = lambda3(phi, py, pz) {
    return  527.05 + 241.804 * phi;
  };

  var(layer_7) = all_layers[axCut(axesName_t("layer")) == 7];
  var(layer_0) = all_layers_xy[axCut(axesName_t("layer")) == 0];
  var(layer_1) = all_layers_xy[axCut(axesName_t("layer")) == 1];
  var(layer_8) = all_layers_xy[axCut(axesName_t("layer")) == 8];
  var(cor_0_vs_8) = layer_0 cross layer_8;

  var(cor_1_vs_8) = layer_1 cross layer_8;
  
  
  var(norm_all_with_0) = all_layers normalize_with layer_0;
  var(norm_all_with_8) = all_layers normalize_with layer_8;

  var(pl3) = layer_0[ axCut(axesName_t("y")) < 0 ];

  var(corr_zz1) = xy_pro::correlations(layer_0.get_z(), layer_8.get_z());
  

  var(corr_pz_z) = xy_pro::correlations(muons.get_axis(axesName_t("pz")), all_layers.get_axis(axesName_t("z")));
  
  var(corr_pz_z_1) = muons cross all_layers;


  var(corr_yy1) = xy_pro::correlations(layer_0.get_y(), layer_8.get_y());

  var( res_yy) = xy_pro::residual(layer_0.get_y(), layer_8.get_y());
  var(res_zz) = xy_pro::residual(layer_0.get_z(), layer_8.get_z());


  var(res_yy_zz) = xy_pro::hitmap(res_yy.get_x(), res_zz.get_x());
  //m_generic->getProcessorCollection()->loop();

  //pl3 = pl[axCut(axesName_t("y")) < -10];


  var(corr_pz_z_3_lose_cut_temp) = cut_op(corr_pz_z_1,
    lambda2(phi1, sector2) {
    if (sector2 == 0 && (phi1 >2.5 || phi1 <-2)) {
      return 1;
    }
    if (sector2 == 1 && ( -3 < phi1 && phi1 < -1.6)) {
      return 1;
    }
    if (sector2 == 2 && (-2 < phi1 && phi1 < -1)) {
      return 1;
    }
    if (sector2 == 3 && (-1 < phi1 && phi1 < 0)) {
      return 1;
    }
    if (sector2 == 4 && (-0.5 < phi1 && phi1 < 0.6)) {
      return 1;
    }
    if (sector2 == 5 && ( 0.5 < phi1 && phi1 < 1.4)) {
      return 1;
    }
    if (sector2 == 6 && (1 < phi1 && phi1 < 2.1)) {
      return 1;
    }
    if (sector2 == 7 && (1.5 < phi1 && phi1 < 3)) {
      return 1;
    }
    return 0;
  });
  var(corr_pz_z_3_lose_cut) = cut_op(corr_pz_z_3_lose_cut_temp,
    lambda2(theta1, section2) {
    if (section2 == 0 && theta1 < 1.3) {
      return 1;
    }
    if (section2 == 1 && theta1 > 1.) {
      return 1;
    }
    
    return 0;
  });

  var(corr_pz_z_3_z_tight) = cut_op(corr_pz_z_3_lose_cut,
    lambda2(pseudo_z1, z2) {
      return abs(pseudo_z1 - z2) < 50;
  });


  var(corr_pz_z_3_z_tight_u) = corr_pz_z_3_z_tight[unique_ax(axesName_t("index1"))];
  m_generic->getProcessorCollection()->loop();

  out_file1->Write();
  Draw(pl3,DrawOption().draw_axis("y:z").title("pl3"));
  new TCanvas();
  Draw(layer_0, DrawOption().title("pl"));
  new TCanvas();
  Draw(corr_yy1, DrawOption().title("corr_yy1"));
  new TCanvas();
  Draw(corr_zz1, DrawOption().title("corr_zz1"));
  new TCanvas();

  Draw(res_yy.get_x(), DrawOption().title("res_yy"));
  new TCanvas();
  Draw(res_zz.get_x(), DrawOption().title("res_zz"));
  new TCanvas();
  Draw(res_yy_zz, DrawOption().title("res_yy_zz"));
#ifdef _DEBUG
 //theApp->Run();




#endif // _DEBUG
  
  return 0;
}




