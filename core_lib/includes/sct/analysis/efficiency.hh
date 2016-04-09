#ifndef efficiency_h__
#define efficiency_h__
#include "sct/platform.hh"
#include "sct/predef/plane.hh"
#include "TH1.h"
#include "TH2.h"
#ifndef __CINT__
#include <memory>
#endif

class DllExport efficiency {
public:

  efficiency(const xy_plane& trueHits,const xy_plane& trueHitsWithDUT);
  TH1D* DrawTrueHits(Int_t nbinsx, Double_t xlow, Double_t xup);
  TH1D* DrawDUTHits(Int_t nbinsx, Double_t xlow, Double_t xup);
  TH1D* DrawEfficiency(Int_t nbinsx, Double_t xlow, Double_t xup);
private:
#ifndef __CINT__
  std::shared_ptr<TH1D> m_true_hits;
  std::shared_ptr<TH1D> m_true_hits_with_dut;
  std::shared_ptr<TH1D> m_efficiency;
  std::shared_ptr<TH1D> m_efficiency_trueHits;
  xy_plane m_truehits_plane, m_true_hits_with_dut_plane;
#endif // !__CINT__

};

class DllExport efficiency2D {
public:

  efficiency2D(const xy_plane& trueHits, const xy_plane& trueHitsWithDUT);
  TH2D* DrawTrueHits(Int_t nbinsx, Double_t xlow, Double_t xup,
                     Int_t nbinsy, Double_t ylow, Double_t yup);

  TH2D* DrawDUTHits(Int_t nbinsx, Double_t xlow, Double_t xup,
                    Int_t nbinsy, Double_t ylow, Double_t yup);
  TH2D* DrawEfficiency(Int_t nbinsx, Double_t xlow, Double_t xup,
                       Int_t nbinsy, Double_t ylow, Double_t yup);
private:
#ifndef __CINT__
  std::shared_ptr<TH2D> m_true_hits;
  std::shared_ptr<TH2D> m_true_hits_with_dut;
  std::shared_ptr<TH2D> m_efficiency;
  std::shared_ptr<TH2D> m_efficiency_trueHits;
  xy_plane m_truehits_plane, m_true_hits_with_dut_plane;
#endif // !__CINT__

};



#endif // efficiency_h__
