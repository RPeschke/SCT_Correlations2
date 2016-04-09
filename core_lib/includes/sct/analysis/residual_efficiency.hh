#ifndef residual_efficiency_h__
#define residual_efficiency_h__
#include "sct/platform.hh"
#include "TH1.h"
#include "sct/predef/plane.hh"
#include "sct/collection.h"
#include "sct/xy_processors/find_nearest_strip.hh"


class DllExport residual_efficiency {
public:
  residual_efficiency(const xy_plane& trueHits,
    const xy_plane& sz_data,
    int  strips,
    axis_def search_axis,
    processor_prob& plot_prob_ = saveWithRandomName("residual_efficiency__"));

  TH1D* Draw_true_residuals();
  TH1D* Draw_reference_residuals();
  TH1D* Draw_residual_efficiency();

  xy_plane get_true_residuals();
  xy_plane get_reference_residuals();
private:
#ifndef __CINT__
  std::shared_ptr<TH1D> m_true_hits;
  std::shared_ptr<TH1D> m_true_hits_with_dut;
  std::shared_ptr<TH1D> m_efficiency;
  std::shared_ptr<TH1D> m_efficiency_trueHits;
  collection* m_coll = nullptr;
#endif // !__CINT__
  xy_plane m_true_residuals, m_reference_residuals;
};
#endif // residual_efficiency_h__
