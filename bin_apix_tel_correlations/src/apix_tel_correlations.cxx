
#include "sct/legacy/xml_input_file.hh"
#include "TFile.h"
#include "TError.h"
#include "TCanvas.h"
#include "TGraph.h"

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


#include "sct/CSV_File.hh"
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
#include "sct/generic_processors/processor_generic_extend_base.hh"
#include "TTree.h"
#include "sct/generic_processors/group_events.hh"

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


class TSIM_calculate_chisqXZ : public processor_generic_extend_base {
public:
  double chisqXZ_ab_approx ;
  double chisqXZ_approx_redo ;
  double chisqXZ_exact_int ;
  double trackID ;
  double SlopeXZ;
  double InterceptXZ ;
  double x_int ;
  double z_int ;
  double a_slope_XZ ;
  double b_intercept_XZ;
  TSIM_calculate_chisqXZ(const generic_plane& pl, const processor_prob& pprob = saveWithRandomName(processorName_t("chisq"))) 
    : processor_generic_extend_base(pl, pprob) {
    register_new_axis(chisqXZ_ab_approx);
    register_new_axis(chisqXZ_approx_redo);
    register_new_axis(chisqXZ_exact_int);
    register_axis(trackID);
    register_axis(InterceptXZ);
    register_axis(SlopeXZ);
    register_axis(x_int);
    register_axis(z_int);
    register_new_axis(a_slope_XZ);
    register_new_axis(b_intercept_XZ);
  }

  std::map<int, double> chisqXZ_per_track_ab_approximated;
  std::map<int, double> chisqXZ_per_track1_exact_int;
  std::map<int, double> sumXX;
  std::map<int, double> sumZZ;
  std::map<int, double> sumX;
  std::map<int, double> sumZ;
  std::map<int, double> sumXZ;
  std::map<int, double> nHits;
  std::map<int, double> a_slope;
  std::map<int, double> b_intercept;

  process_returns processEvent() override
  {
    clear();
    m_current++;
    //std::cout << "Event: " << m_current << "\n";
    int index = 0;
    chisqXZ_per_track_ab_approximated.clear();
    sumXX.clear();
    sumZZ.clear();
    sumX.clear();
    sumZ.clear();
    sumXZ.clear();
    nHits.clear();
    a_slope.clear();
    b_intercept.clear();
    chisqXZ_per_track1_exact_int.clear();
    index = 0;
    double maxTrackID = 0;
    while (next()) {
      double chi = (z_int - ((x_int) *(SlopeXZ) + (InterceptXZ)));
      chisqXZ_per_track_ab_approximated[trackID] += chi * chi;
      sumXX[trackID] += x_int * x_int;
      sumZZ[trackID] += z_int * z_int;
      sumX[trackID] += x_int;
      sumZ[trackID] += z_int;
      sumXZ[trackID] += x_int * z_int;
      nHits[trackID] += 1;
      //std::cout << "process: " << index++ << "\n";
      maxTrackID = max(maxTrackID, trackID);
    }
    

    for (double d = 0; d <= maxTrackID; d += 1) {
      double denom = sumX[d] * sumX[d] - nHits[d] * sumXX[d];
      if (denom != 0) {
        a_slope[d] = (sumX[d] * sumZ[d] - nHits[d] * sumXZ[d])/denom;

        b_intercept[d] = (sumX[d] * sumXZ[d] - sumZ[d] * sumXX[d])/denom;

      }
    }
    while (next()) {
      double chi = (z_int - ((x_int) *(a_slope[trackID]) + b_intercept[trackID] ));
      chisqXZ_per_track1_exact_int[trackID] += chi * chi;
    }

    while (next()) {
      a_slope_XZ = a_slope[trackID];
      b_intercept_XZ= b_intercept[trackID];

      chisqXZ_exact_int = chisqXZ_per_track1_exact_int[trackID];
      chisqXZ_ab_approx = chisqXZ_per_track_ab_approximated[trackID] ;
      chisqXZ_approx_redo = (SlopeXZ) * (SlopeXZ) * sumXX[trackID] 
        + (InterceptXZ) * (InterceptXZ) * nHits[trackID] 
        + sumZZ[trackID] 
        + 2.0 * (SlopeXZ)  * (InterceptXZ) * sumX[trackID] 
        - 2.0 * (SlopeXZ)  * sumXZ[trackID]
        - 2.0 * (InterceptXZ) *  sumZ[trackID];
      push();
      //std::cout << "Fill: " << index++ << "\n";
    }
    return p_sucess;
  }

};


class TSIM_back2Back : public processor_generic_extend_base {
public:
  double px;
  double py;
  double pz;
  int trackID;
  double b2b_angle;


  std::map<int, double> px_first;
  std::map<int, double> py_first;
  std::map<int, double> pz_first;


  TSIM_back2Back(const generic_plane& pl, const processor_prob& pprob = saveWithRandomName(processorName_t("b2b")))
    : processor_generic_extend_base(pl, pprob) {
    register_new_axis(b2b_angle);
    register_axis(px);
    register_axis(py);
    register_axis(pz);
    
  }



  process_returns processEvent() override
  {
    clear();
    px_first.clear();
    py_first.clear();
    pz_first.clear();
    trackID = 0;
    while (next()) {
      px_first[trackID] = px;
      py_first[trackID] = py;
      pz_first[trackID] = pz;
      double p_first = TMath::Sqrt(px_first[0] * px_first[0] + py_first[0]* py_first[0] + pz_first[0]* pz_first[0]);
      double p_now = TMath::Sqrt(px * px + py * py + pz * pz);
      double p_first_times_p_now = px_first[0] * px + py_first[0] * py + pz_first[0] * pz;

      b2b_angle = TMath::ACos(p_first_times_p_now / (p_now*p_first));

      push();
      trackID += 1;
    }


    return p_sucess;
  }

};



double pfit1(double x) {
  return 0.845523 - 0.000302713 *x + 0.00040593*x*x;

}

double pfit2(double x) {
  return  11.46 - 32.3147 *x + 33.8224*x*x - 15.5669*x*x*x + 2.65602*x*x*x*x;

}


double pfit3(double x) {
  return  0.00262558 - 0.142606 *x - 3.04213*x*x + 3.2212*x*x*x + 40.1586*x*x*x*x;

}

#include <type_traits>
template<class U, class T = typename std::remove_cv<U>::type>
struct remove_all { typedef T type; };
template<class U, class T> struct remove_all<U, T*> : remove_all<T> {};
template<class U, class T> struct remove_all<U, T&> : remove_all<T> {};
template<class U, class T> struct remove_all<U, T&&> : remove_all<T> {};
template<class U, class T> struct remove_all<U, T[]> : remove_all<T> {};
template<class U, class T, int n> struct remove_all<U, T[n]> : remove_all<T> {};

enum _else_helper_ {
  else_helper_start
};
template<typename T>
struct else_struct_proto {

  T t;

};

template<typename T>
struct else_struct {
  T t;
  bool condition = false;
  constexpr operator bool() const {
    return condition;
  }
};

template <typename T>
constexpr auto operator|=(_else_helper_, T&& t) {
  return else_struct_proto<T>{ std::forward<T>(t) };
}


template <typename T, typename U>
constexpr auto operator|=(T&& t, else_struct_proto<U>&& else_str) {
  return else_struct<U>{std::forward<U>(else_str.t), t};
}


enum _if_helper_ {
  if_helper_start
};

template<typename T>
struct if_struct{
  T t;
};

template <typename T>
constexpr auto operator|=(_if_helper_, T&& t) {
  return if_struct<T>{ std::forward<T>(t) };
}


#include <optional>


template <typename T, typename U>
constexpr auto operator|=(T&& t, if_struct<U>&& is_str)  {
  if (is_str.t){
    return std::optional<remove_all<T>::type>(t);
  }
  
  return  std::optional<remove_all<T>::type>{} ;
}

template <typename T, typename U>
constexpr auto operator|=(T&& t, if_struct<else_struct<U>>&& if_str) {
  if  (if_str.t) {
    return std::forward<T>(t);
  }
  
  return  if_str.t.t;
}




#define if_ |=if_helper_start|=
#define  when if_
#define else_ |=else_helper_start|=

#include <array>


void readin_csv() {
  TFile * out_file1 = new TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/eudaq_out_52.root", "recreate");
  auto csv = CSV_File("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/test_52.csv");
  var(all_layers) = csv.getCollection()->getPlane(ID_t(0));
  var(all_dump) = all_layers[axCut(axesName_t("PlaneID")) >= 0];
  var(all_grouped) =  sct::group_events(all_dump, axesName_t("EventNumber"));
  var(layer_2) = all_grouped[axCut(axesName_t("PlaneID")) == 2];
  var(layer_12) = all_grouped[axCut(axesName_t("PlaneID")) == 12];
  var(cor_2_vs_12) = layer_2 cross layer_12;

  csv.getProcessorCollection()->loop();
  out_file1->Write();
}

int main(int argc, char **argv) {

#ifdef _DEBUG
  
 // auto theApp = get_TApplication();
#endif // _DEBUG

  readin_csv();
  return 1;

  constexpr  auto i = 123 when  1 > 2;
  constexpr auto i2 = 123 when  1 < 2;

  auto i3 = 123 if_  1 > 2 else_ 321 if_ 1 > 3 else_ 234;
  auto i4 = 123 if_  1 > 2 else_ 456;

  auto i5 = std::array<int, 10 when 1 < 2 else_ 30>();

  auto m_file = Snew TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/t_2020-08-16a.root");
  auto m_file2 = Snew TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/t23_2020-08-16a.root");
  
  TFile * out_file1 = new TFile("C:/Users/Peschke/Documents/xilinx_share2/GitHub/SCT_Correlations2/debug/tout_2020-08-16a.root", "recreate");



  auto m_generic1 = Snew TSIMFile(m_file.get());
  
  auto mcparticle_file = Snew EUTFile(m_file2, m_generic1->getProcessorCollection());
  
  

  var(all_layers) = m_generic1->KLM_Tracks();
  all_layers[axesName_t("theta")] = lambda3(x, y, z) {
    return TMath::ACos(z / TMath::Sqrt(x*x + y*y + z*z));
  };
  all_layers[axesName_t("phi")] = lambda3(x, y, z) {
    return TMath::ATan2(y, x);
  };


  var(new_chi_square) =  Pnew  TSIM_calculate_chisqXZ(all_layers);
  var(mcparticles) = mcparticle_file->getCollection(collectionName_t("t3"))->getPlane(ID_t(0));

  //auto corr_zz1 = xy_pro::correlations(p0.get_z(), p0.get_z());

  //var(muons_temp) = mcparticles[(axCut(axesName_t("PDG")) == 13 || axCut(axesName_t("PDG")) == -13) && axCut(axesName_t("mass")) <1];
  var(muons_temp) = mcparticles[axCut(axesName_t("mass")) < 1];

  var(muons) = Pnew  TSIM_back2Back(muons_temp);

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
  var(layer_0) = all_layers[axCut(axesName_t("layer")) == 0];
  var(layer_1) = all_layers[axCut(axesName_t("layer")) == 1];
  var(layer_8) = all_layers[axCut(axesName_t("layer")) == 8];
  var(cor_0_vs_8) = layer_0 cross layer_8;

  var(cor_1_vs_8) = layer_1 cross layer_8;
  
  
  var(norm_all_with_0) = all_layers normalize_with layer_0;
  var(norm_all_with_8) = all_layers normalize_with layer_8;

  var(pl3) = layer_0[ axCut(axesName_t("y")) < 0 ];


  

  
  var(corr_pz_z_1) = muons cross all_layers;




  //m_generic->getProcessorCollection()->loop();

  //pl3 = pl[axCut(axesName_t("y")) < -10];

  var(corr_pz_z_3_lose_cut_temp) = corr_pz_z_1[
    lambda2(theta1, theta2) {
    return abs(theta1 - theta2) < 0.1;
  }]; 

  var(corr_pz_z_3_lose_cut) = cut_op(corr_pz_z_3_lose_cut_temp,
    lambda2(phi1, sector2) {
    if (sector2 == 0 && (-1 < phi1 && phi1 < 1)) {
      return 1;
    }
    if (sector2 == 1 && ( 0 < phi1 && phi1 < 1.8)) {
      return 1;
    }
    if (sector2 == 2 && (0.5 < phi1 && phi1 < 2.5)) {
      return 1;
    }
    if (sector2 == 3 && ( 1.5 < phi1 && phi1 < 3.5)) {
      return 1;
    }
    if (sector2 == 4 && ( 2. < phi1 || phi1 < -2)) {
      return 1;
    }
    if (sector2 == 5 && ( -3.5 < phi1 && phi1 < -1.5)) {
      return 1;
    }
    if (sector2 == 6 && (-2.5 < phi1 && phi1 < -0.5)) {
      return 1;
    }
    if (sector2 == 7 && (-2 < phi1 && phi1 < 0.5)) {
      return 1;
    }
    return 0;
  });





  var(corr_pz_z_3_z_tight_u) = corr_pz_z_3_lose_cut[unique_ax(axesName_t("index1"))];

  corr_pz_z_3_z_tight_u[axesName_t("muonness")] = lambda1(nHits2) {
    return  TMath::Gaus(nHits2, 4.43839e+001, 3.11240e+001) * 7.81049e-001;
  };

  corr_pz_z_3_z_tight_u[axesName_t("KLongness")] = lambda1(nHits2) {
    double slope = -0.0439238;
    double constant = -0.844198;
    return  TMath::Exp(nHits2* slope+constant);
  };

  corr_pz_z_3_z_tight_u[axesName_t("pseudo_energy")] = lambda3(nHits2, theta2, phi2) {
    return (pfit1(nHits2) + pfit2(theta2) + pfit3(phi2));
  };

  m_generic1->getProcessorCollection()->loop();

  out_file1->Write();
  Draw(pl3,DrawOption().draw_axis("y:z").title("pl3"));
  new TCanvas();
  Draw(layer_0, DrawOption().title("pl"));
  new TCanvas();


  

#ifdef _DEBUG
 //theApp->Run();




#endif // _DEBUG
  
  return 0;
}





