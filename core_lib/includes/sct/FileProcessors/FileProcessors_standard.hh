#ifndef FileProcessors_standard_h__
#define FileProcessors_standard_h__
#include "FileProcessorsBase.hh"
#include "sct/predef/plane.hh"
#include "sct/platform.hh"

#ifndef __CINT__
#include <memory>
#endif
#include "sct/predef/fitterFile.hh"

class TH2D;
class TH1D;
class fitterFile;
class DUT_2_Track_correlator;
class TF1;
class DllExport FileProcessors_standard :public FileProcessorsBase {
public:
  FileProcessors_standard(Parameter_ref par);
  virtual ~FileProcessors_standard();
  int DrawResidual(Double_t min_X, Double_t max_X);
  int DrawResidual();
  int DrawResidualVsEvent(Double_t min_X, Double_t max_X);
  int DrawResidualVsEvent();
  int DrawResidualVsMissingCordinate(Double_t min_X, Double_t max_X);
  int DrawResidualVsMissingCordinate();
  int Draw_Efficinecy_map();
  int Draw_Hit_map();
  int Draw_DUT_Hits_map();
  TH2D* getResidualVsMissingCordinate();
  virtual void saveHistograms(TFile* outPutFile, double residual_min, double residual_max);

private:
#ifndef __CINT__
  virtual  bool process_file(FileProberties* fileP) override;
  void extract_efficiency();
  void extract_hitMap();
  void extract_residual();
  void extract_rotation();
  void process_reset();



  virtual std::string get_suffix() const override;


  std::shared_ptr<TH1D> m_Residual;
  std::shared_ptr<TH1D> m_Hits_total;
  std::shared_ptr<TH1D> m_Hits_with_DUT_Hits;
  std::shared_ptr<TH1D> m_Efficieny_map;
  std::shared_ptr<TH1D> m_Efficieny_trueHits;
  std::shared_ptr<TH2D> m_resVSMissing;
  std::shared_ptr<TH2D> m_ResidualVsEvent;



  FFile m_input_file;
  xy_plane m_trueHits, m_residual;
  std::shared_ptr<DUT_2_Track_correlator> m_corr;




  TFile* m_dummy = nullptr;
  std::shared_ptr <TF1> m_fit;

#endif
};
#endif // FileProcessors_standard_h__
