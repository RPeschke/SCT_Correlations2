#include "sct/legacy/Cluster_strip.hh"
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/legacy/cluster.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/legacy/s_cuts.h"
#include "sct/xy_processors/find_nearest_strip.hh"
#include <iostream>
#include "sct/legacy/Draw.h"

class processor_Cluster_strip : public processor_hit2d {
public:
  processor_Cluster_strip(const xy_plane& sz_data, double max_cluster_distance, axis_def search_axis, processor_prob pprob);
  const double m_max_cluster_distance;
  const axis_def m_search_axis;
  virtual void processEventStart() override;
  virtual void processHit(double x, double y) override;
  virtual process_returns processEventEnd() override;
  clusterMaker<double> m_cl;

};

processor_Cluster_strip::processor_Cluster_strip(const xy_plane& sz_data, double max_cluster_distance, axis_def search_axis, processor_prob pprob):processor_hit2d(sz_data.get_x(), sz_data.get_y(), pprob), m_max_cluster_distance(max_cluster_distance),m_search_axis(search_axis)
{
  m_cl = clusterMaker<Double_t>(m_max_cluster_distance);
}






void processor_Cluster_strip::processEventStart()
{
  m_cl.reset();
}

void processor_Cluster_strip::processHit(double x, double y)
{
  m_cl.push_pixel(pixelHit<Double_t>(x, y));
}

process_returns processor_Cluster_strip::processEventEnd()
{
  if (m_search_axis == x_axis_def) {
    for (size_t i = 0; i < m_cl.NumOfCluster(); ++i) {
      pushHit(m_cl.getCluster(i).x(), m_cl.getCluster(i).size(), ID_t(0));
    }

  }
  else if (m_search_axis == y_axis_def)
  {
    for (size_t i = 0; i < m_cl.NumOfCluster(); ++i) {
      pushHit(m_cl.getCluster(i).y(), m_cl.getCluster(i).size(), ID_t(0));
    }


  }

  return p_sucess;
}


xy_plane create_cluster_size(const xy_plane& sz_data, double max_cluster_distance, axis_def search_axis, processor_prob plot_prob_ = saveWithRandomName(processorName_t("Cluster_strip_maker_"))) {
  std::shared_ptr<processor> p(new processor_Cluster_strip(sz_data, max_cluster_distance, search_axis, plot_prob_));
  sz_data.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_Cluster_strip*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}










Cluster_strip::Cluster_strip(const xy_plane& trueHits_with_dut, const xy_plane& sz_data, max_cl_t max_cluster_size, axis_def search_axis, modulo_t modulo_, processor_prob plot_prob_ /*= saveWithRandomName("Cluster_strip__") */):m_mod(modulo_), m_max_cluster_size(max_cluster_size)
{


  modulo_x mod_x = modulo_x(10000000);
  modulo_y mod_y = modulo_y(10000000);
  if (search_axis == x_axis_def) {
    mod_x = strong_cast<modulo_x>( modulo_);
  }

  if (search_axis == y_axis_def) {
    mod_y =strong_cast<modulo_y>(modulo_);
  }
  auto cluster_ = create_cluster_size(
    sz_data,
    2,
    x_axis_def,
    DontsaveWithRandomName(processorName_t("Cluster_strip_maker_"))
    );
  auto cluster__cut = xy_pro::cut_xy(
    cluster_,
    S_YCut(0, necessary_CONVERSION(max_cluster_size)),
    DontsaveWithRandomName(processorName_t("cluster_cut_"))
    );

  auto cluster_closest = find_nearest_strip(
    cluster__cut,
    trueHits_with_dut, //used to be all hits 
    search_axis,
    residualCut_t( 1),
    DontsaveWithRandomName(processorName_t("cluster_find_closest_"))
    );
  auto mod_total_closest = xy_pro::modulo(
    cluster_closest.getHitOnPlaneB(),
    mod_x,
    mod_y,
    DontsaveWithRandomName(processorName_t("cluster_modulo_"))
    );
  if (search_axis == x_axis_def) {
     m_cluster_size_vs_pos = xy_pro::hitmap(
      mod_total_closest.get_x(),
      cluster_closest.getHitOnPlaneA().get_y(),
      plot_prob_
      );

    

  }
  else if (search_axis == y_axis_def) {

    m_cluster_size_vs_pos =xy_pro::hitmap(
      mod_total_closest.get_y(),
      cluster_closest.getHitOnPlaneA().get_y(),
      plot_prob_
      );


  }
  else {
    std::cout << "[inStripClusterSize]: axis not supported \n";
  }


}





int Cluster_strip::Draw_ClusterSize()
{
  m_cluster_size_hist = _MAKE_SHARED1(TH2D,
    "hist",
    "hist",
    100, 0,necessary_CONVERSION( m_mod),
    necessary_CONVERSION(m_max_cluster_size) * 100, -0.5, necessary_CONVERSION(m_max_cluster_size) - 0.5
    );

  Draw(m_cluster_size_vs_pos, DrawOption().draw_y_VS_x().opt_colz().output_object(m_cluster_size_hist.get()));



  m_profile = std::shared_ptr<TProfile>(dynamic_cast<TProfile*>(m_cluster_size_hist->ProfileX()));


  m_cluster_size_hist = _MAKE_SHARED1(TH2D,
    "hist",
    "hist",
    100, 0, necessary_CONVERSION( m_mod),
    necessary_CONVERSION(m_max_cluster_size) * 100, -0.5, necessary_CONVERSION(m_max_cluster_size) - 0.5
    );
  auto ret = Draw(m_cluster_size_vs_pos, DrawOption().draw_y_VS_x().opt_colz().output_object(m_cluster_size_hist.get()));

  m_profile->Draw("same");

  return ret;
}

xy_plane Cluster_strip::get_plane()
{
  return m_cluster_size_vs_pos;
}

TProfile* Cluster_strip::get_profile()
{
  return m_profile.get();
}

TH2D* Cluster_strip::get_histogram()
{
  return m_cluster_size_hist.get();
}
