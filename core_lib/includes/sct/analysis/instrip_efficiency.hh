#ifndef instrip_efficiency_h__
#define instrip_efficiency_h__
#include "sct/predef/plane.hh"
#include <memory>
#include "TH1.h"
#include "sct/collection.h"
#include "sct/processor_prob.hh"
#include "sct/platform.hh"
#include "sct/internal/strong_types.h"


class DllExport instrip_efficiency {
public:

public:
  instrip_efficiency(
    const xy_plane& trueHits,
    const xy_plane& trueHits_with_dut,
    modulo_x x_mod,
    modulo_y y_mod,
    processor_prob& plot_prob_ = saveWithRandomName("instrip_efficiency__")
    );

  TH1D* Draw_true_hits();
  TH1D* Draw_true_hits_with_dut();
  TH1D* Draw_Efficiency();

  xy_plane get_true_hits();
  xy_plane get_true_hits_with_dut();
private:
#ifndef __CINT__
  std::shared_ptr<TH1D> m_true_hits;
  std::shared_ptr<TH1D> m_true_hits_with_dut;
  std::shared_ptr<TH1D> m_efficiency;
  std::shared_ptr<TH1D> m_efficiency_trueHits;
  xy_plane m_true_hits_plane, m_true_w_dut_plane;
#endif // !__CINT__
};

#endif // instrip_efficiency_h__
