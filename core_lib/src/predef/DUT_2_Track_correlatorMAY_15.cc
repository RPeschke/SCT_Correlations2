#include "sct/predef/DUT_2_Track_correlator.hh"
#include "sct/predef/plane.hh"
#include "sct/xy_processors/converters.hh"
#include "sct/xy_processors/processor_linear_trans.hh"
#include "sct/xy_processors/processor_transform.hh"
#include "sct/xy_processors/processor_cut_xy.hh"
#include "sct/xy_processors/find_nearest_strip.hh"
#include "sct/xy_processors/processor_hitmap.hh"
#include "sct/xy_processors/xy_pro.hh"

class DUT_2_Track_correlatorMAY15:public DUT_2_Track_correlator {
public:
  DUT_2_Track_correlatorMAY15(DUT_2_Track_correlator::Parameter_ref param_);

  virtual xy_plane getResidual() override;

  virtual xy_plane getResidualVsMissing() override;

  virtual xy_plane getTotalTrueHits() override;

  virtual xy_plane getTrueHitsWithDUT() override;

  virtual xy_plane getDUT_Hits() override;
  xy_plane m_residual, m_residualVsMissing, m_totalTrueHit_afterCut, m_trueHit_with_dut, m_dut_hits;
};
registerDUT_2_Track_correlator(DUT_2_Track_correlatorMAY15, "MAY15");

DUT_2_Track_correlatorMAY15::DUT_2_Track_correlatorMAY15(DUT_2_Track_correlator::Parameter_ref param_) :DUT_2_Track_correlator(param_)
{
  auto trueHitsInStrips = convert::hits_to_zs_data_GBL(
    param_.get_trueHits(),
    *param_.get_gear()->detector.layer_by_ID(8),
    DontsaveWithRandomName(processorName_t("hit_to_sz_data_gbl_"))
    );


  auto dut_rotated = xy_pro::rotate(
    trueHitsInStrips,
    param_.get_xmlFile().globalConfig.Rotation,
    DontsaveWithRandomName(processorName_t("rotate__"))
    );

  auto trueHitsInStrips_name = param_.get_processor_pro().name + processorName_t("_true");
  auto dut_rotated_moved = xy_pro::transform_move(
    dut_rotated,
    x_offset_t(param_.get_xmlFile().globalConfig.Position_value),
    y_offset_t(0),
    processor_prob(param_.get_processor_pro()).setName(trueHitsInStrips_name)
    );

  auto trueHitsInStrips_name_cutted = param_.get_processor_pro().name + processorName_t("_true_cutted");
  m_totalTrueHit_afterCut = xy_pro::cut_xy(
    dut_rotated_moved,
    param_.get_xmlFile().globalConfig.cut(),
    processor_prob(param_.get_processor_pro()).setName(trueHitsInStrips_name)
    );



auto find_closest_name = param_.get_processor_pro().name + processorName_t("_closest");
  auto find_closest = find_nearest_strip(
    m_totalTrueHit_afterCut,
    param_.get_DUT_Hits(),
    x_axis_def,
    residualCut_t( param_.get_xmlFile().globalConfig.residual_cut),
    processor_prob(param_.get_processor_pro()).setName(find_closest_name)
    );

  auto res_vs_missing_name = param_.get_processor_pro().name + processorName_t("_res_vs_missing");
  m_residualVsMissing = xy_pro::hitmap(
    find_closest.getResidual().get_x(),
    find_closest.getHitOnPlaneA().get_y(),
    processor_prob(param_.get_processor_pro()).setName(res_vs_missing_name)
    );


  m_residual = find_closest.getResidual();
  m_trueHit_with_dut = find_closest.getHitOnPlaneA();
  m_dut_hits = find_closest.getHitOnPlaneB();

}

xy_plane DUT_2_Track_correlatorMAY15::getResidual()
{
  return m_residual;
}

xy_plane DUT_2_Track_correlatorMAY15::getResidualVsMissing()
{

  return m_residualVsMissing;
}

xy_plane DUT_2_Track_correlatorMAY15::getTotalTrueHits()
{
  return m_totalTrueHit_afterCut;
}

xy_plane DUT_2_Track_correlatorMAY15::getTrueHitsWithDUT()
{
  return m_trueHit_with_dut;
}

xy_plane DUT_2_Track_correlatorMAY15::getDUT_Hits()
{
  return m_dut_hits;
}
