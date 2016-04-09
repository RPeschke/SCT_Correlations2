#include "sct/analysis/residual_efficiency.hh"
#include "sct/xy_processors/processorPlaneVSPlane.h"
#include "sct/predef/plane.hh"
#include "sct/xy_processors/find_nearest_strip.hh"
#include "sct/ProcessorCollection.h"
#include "sct/lagacy/Draw.h"
#include "sct/lagacy/SCT_helpers.hh"
#include "TMath.h"
#define TrueResiduals_DEF 0
#define  REFERENCE_RESIDUALS_DEF 1

class residual_efficiency_processor :public processorPlaneVSPlane {
public:
  residual_efficiency_processor(const xy_plane & plane_A, const  xy_plane& plane_b, int strips, axis_def search_axis, processor_prob& plot_prob);
  virtual void processHit(const hit&  p1, const hit&  p2) override;


  virtual void processHit_1(const hit&  p1) override;


  double  make_residual(double true_hit, double dut_hit);



  const int m_strips;
  const axis_def m_axis;

};

residual_efficiency_processor::residual_efficiency_processor(const xy_plane & plane_A, const xy_plane& plane_b, int strips, axis_def search_axis, processor_prob& plot_prob):processorPlaneVSPlane(plane_A,plane_b,plot_prob),m_axis(search_axis),m_strips(strips)
{

}

void residual_efficiency_processor::processHit(const hit& p1, const hit& p2)
{
  if (m_axis == x_axis_def) {

    auto r = make_residual(p1.x, p2.x);

    pushHit(r, p1.y, TrueResiduals_DEF);

  }
  else if (m_axis == y_axis_def) {
    auto r = make_residual(p1.y, p2.y);
    pushHit(r, p1.x, TrueResiduals_DEF);

  }
}

void residual_efficiency_processor::processHit_1(const hit& p1)
{
  double ax = 0;
  double ay = 0;
  if (m_axis == x_axis_def) {
    ax = p1.x;
    ay = p1.y;
  } else if (m_axis == y_axis_def) {
    ax = p1.y;
    ay = p1.x;
  }

  int start_ = TMath::Floor(ax - m_strips);
  int end_ = TMath::Ceil(ax + m_strips);

  for (int i = start_; i < end_; ++i) {
      auto r = make_residual(ax, i);
      pushHit(r, ay, REFERENCE_RESIDUALS_DEF);
  }
}

double residual_efficiency_processor::make_residual(double true_hit, double dut_hit)
{
  return dut_hit - true_hit;
}

residual_efficiency::residual_efficiency(const xy_plane& trueHits, const xy_plane& sz_data, int strips, axis_def search_axis, processor_prob& plot_prob_ /*= saveWithRandomName("residual_efficiency__")*/)
{
  std::shared_ptr<processor> p(new residual_efficiency_processor(trueHits, sz_data, strips, search_axis, plot_prob_));
  trueHits.get_ProcessorCollection()->addProcessor(p);

  m_coll = dynamic_cast<residual_efficiency_processor*>(p.get())->get_output_collection();
  m_reference_residuals = m_coll->getPlane(REFERENCE_RESIDUALS_DEF);
  m_true_residuals = m_coll->getPlane(TrueResiduals_DEF);
}

TH1D* residual_efficiency::Draw_true_residuals()
{
  m_true_hits = std::make_shared<TH1D>(
    "total",
    "total",
    100, -5, 5
    );

  Draw(
    m_true_residuals,
    DrawOption()
    .draw_x()
    .output_object(m_true_hits.get())
    );
  return m_true_hits.get();
}

TH1D* residual_efficiency::Draw_reference_residuals()
{
  m_true_hits_with_dut = std::make_shared<TH1D>(
    "DUT",
    "DUT",
    100, -5, 5
    );

  Draw(
    m_reference_residuals,
    DrawOption()
    .draw_x()
    .output_object(m_true_hits_with_dut.get())
    );
  return m_true_hits_with_dut.get();
}

TH1D* residual_efficiency::Draw_residual_efficiency()
{
  m_efficiency_trueHits = std::make_shared<TH1D>(
    "total",
    "total",
    100, -5, 5
    );

  Draw(
    m_reference_residuals,
    DrawOption()
    .draw_x()
    .output_object(m_efficiency_trueHits.get())
    );

  m_efficiency = std::make_shared<TH1D>(
    "Efficiency",
    "Efficiency",
    100, -5, 5
    );

  auto n = Draw(
    m_true_residuals,
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

xy_plane residual_efficiency::get_true_residuals()
{
  return m_true_residuals;
}

xy_plane residual_efficiency::get_reference_residuals()
{
  return m_reference_residuals;
}
