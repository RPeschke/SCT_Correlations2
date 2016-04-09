#include "sct/analysis/efficiency.hh"
#include "sct/lagacy/Draw.h"
#include "sct/lagacy/SCT_helpers.hh"

efficiency::efficiency(const xy_plane& trueHits, const xy_plane& trueHitsWithDUT)
{
  m_truehits_plane = trueHits;
  m_true_hits_with_dut_plane = trueHitsWithDUT;

}

TH1D* efficiency::DrawTrueHits(Int_t nbinsx, Double_t xlow, Double_t xup)
{
  m_true_hits = std::make_shared<TH1D>(
    "total",
    "total",
    nbinsx, xlow, xup
    );

   Draw(
    m_truehits_plane,
    DrawOption()
    .draw_x()
    .output_object(m_true_hits.get())
    );
   return m_true_hits.get();
}

TH1D* efficiency::DrawDUTHits(Int_t nbinsx, Double_t xlow, Double_t xup)
{
  m_true_hits_with_dut = std::make_shared<TH1D>(
    "DUT",
    "DUT",
    nbinsx, xlow, xup
    );

  Draw(
    m_true_hits_with_dut_plane,
    DrawOption()
    .draw_x()
    .output_object(m_true_hits_with_dut.get())
    );
  return m_true_hits_with_dut.get();

}

TH1D* efficiency::DrawEfficiency(Int_t nbinsx, Double_t xlow, Double_t xup)
{
  m_efficiency_trueHits = std::make_shared<TH1D>(
    "total",
    "total",
    nbinsx, xlow, xup
    );

  Draw(
    m_truehits_plane,
    DrawOption()
    .draw_x()
    .output_object(m_efficiency_trueHits.get())
    );

  m_efficiency = std::make_shared<TH1D>(
    "Efficiency",
    "Efficiency",
    nbinsx, xlow, xup
    );

  auto n = Draw(
    m_true_hits_with_dut_plane,
    DrawOption()
    .draw_x()
    .output_object(m_efficiency.get())
    );

  auto e = SCT_helpers::calc_efficiency(m_efficiency_trueHits.get(), m_efficiency.get());
  auto eth2d = dynamic_cast<TH1D*>(e);

  m_efficiency = std::shared_ptr<TH1D>(eth2d);
  // m_Efficieny_map->Divide(m_Efficieny_trueHits.get());

  m_efficiency->Draw();
  return m_efficiency.get();
}

efficiency2D::efficiency2D(const xy_plane& trueHits, const xy_plane& trueHitsWithDUT)
{
  m_truehits_plane = trueHits;
  m_true_hits_with_dut_plane = trueHitsWithDUT;

}

TH2D* efficiency2D::DrawTrueHits(Int_t nbinsx, Double_t xlow, Double_t xup,
                                 Int_t nbinsy, Double_t ylow, Double_t yup)
{
  m_true_hits = std::make_shared<TH2D>(
    "total",
    "total",
    nbinsx, xlow, xup,
    nbinsy, ylow, yup
    );

  Draw(
    m_truehits_plane,
    DrawOption()
    .draw_y_VS_x()
    .output_object(m_true_hits.get())
    );
  return m_true_hits.get();
}

TH2D* efficiency2D::DrawDUTHits(Int_t nbinsx, Double_t xlow, Double_t xup,
                                Int_t nbinsy, Double_t ylow, Double_t yup)
{
  m_true_hits_with_dut = std::make_shared<TH2D>(
    "total",
    "total",
    nbinsx, xlow, xup,
    nbinsy, ylow, yup
    );

  Draw(
    m_true_hits_with_dut_plane,
    DrawOption()
    .draw_y_VS_x()
    .output_object(m_true_hits_with_dut.get())
    );
  return m_true_hits_with_dut.get();
}

TH2D* efficiency2D::DrawEfficiency(Int_t nbinsx, Double_t xlow, Double_t xup,
                                   Int_t nbinsy, Double_t ylow, Double_t yup)
{
  m_efficiency_trueHits = std::make_shared<TH2D>(
    "total",
    "total",
    nbinsx, xlow, xup,
    nbinsy, ylow, yup
    );

  Draw(
    m_truehits_plane,
    DrawOption()
    .draw_y_VS_x()
    .output_object(m_efficiency_trueHits.get())
    );

  m_efficiency = std::make_shared<TH2D>(
    "Efficiency",
    "Efficiency",
    nbinsx, xlow, xup,
    nbinsy, ylow, yup
    );

  auto n = Draw(
    m_true_hits_with_dut_plane,
    DrawOption()
    .draw_y_VS_x()
    .output_object(m_efficiency.get())
    );

  auto e = SCT_helpers::calc_efficiency(m_efficiency_trueHits.get(), m_efficiency.get());
  auto eth2d = dynamic_cast<TH2D*>(e);

  m_efficiency = std::shared_ptr<TH2D>(eth2d);
  // m_Efficieny_map->Divide(m_Efficieny_trueHits.get());

  m_efficiency->Draw();
  return m_efficiency.get();
}
