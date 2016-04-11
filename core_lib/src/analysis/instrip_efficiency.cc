#include "sct/analysis/instrip_efficiency.hh"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/lagacy/Draw.h"
#include "sct/lagacy/SCT_helpers.hh"

instrip_efficiency::instrip_efficiency(const xy_plane& trueHits, const xy_plane& trueHits_with_dut, double x_mod, double y_mod, processor_prob& plot_prob_ /*= saveWithRandomName("instrip_efficiency__") */)
{
  m_true_hits_plane = xy_pro::modulo(trueHits, x_mod, y_mod, plot_prob_);
  
  
  plot_prob_.setName(plot_prob_.name + "_with_DUT");
  
    
  m_true_w_dut_plane = xy_pro::modulo(trueHits_with_dut, x_mod, y_mod, plot_prob_);

}

TH1D* instrip_efficiency::Draw_true_hits()
{
  m_true_hits = std::make_shared<TH1D>(
    "total",
    "total",
    100, -5, 5
    );

  Draw(
    m_true_hits_plane,
    DrawOption()
    .draw_x()
    .output_object(m_true_hits.get())
    );
  return m_true_hits.get();
}

TH1D* instrip_efficiency::Draw_true_hits_with_dut()
{
  m_true_hits_with_dut = std::make_shared<TH1D>(
    "DUT",
    "DUT",
    100, -5, 5
    );

  Draw(
    m_true_w_dut_plane,
    DrawOption()
    .draw_x()
    .output_object(m_true_hits_with_dut.get())
    );
  return m_true_hits_with_dut.get();
}

TH1D* instrip_efficiency::Draw_Efficiency()
{
  m_efficiency_trueHits = std::make_shared<TH1D>(
    "total",
    "total",
    100, -5, 5
    );

  Draw(
    m_true_hits_plane,
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
    m_true_w_dut_plane,
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

xy_plane instrip_efficiency::get_true_hits()
{
  return m_true_hits_plane;
}

xy_plane instrip_efficiency::get_true_hits_with_dut()
{
  return m_true_w_dut_plane;
}

