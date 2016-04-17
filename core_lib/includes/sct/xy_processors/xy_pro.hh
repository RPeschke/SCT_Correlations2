#ifndef xy_pro_h__
#define xy_pro_h__
#include "sct/platform.hh"
#include "sct/predef/plane.hh"
#include "sct/processor_prob.hh"
#include "sct/axis.hh"
#include "sct/legacy/s_cuts.h"
#include "sct/internal/strong_types.h"

class TH1;
class TH2;
class DllExport xy_pro {
public:
  static xy_plane correlations(
    const axis& x_,
    const axis& y_,
    processor_prob& pprob = saveWithRandomName(processorName_t("correlation_"))
    );

  static void fill2Hist(
    const axis& x_,
    TH1* h1,
    processor_prob& pprob = DontsaveWithRandomName(processorName_t("fill2hist1d__"))
    );
  static void fill2Hist(
    const xy_plane& x_,
    TH2* h2,
    processor_prob& pprob = DontsaveWithRandomName(processorName_t("fill2hist2d__"))
    );
  static xy_plane cut_xy(
    const xy_plane& pl, 
    const S_Cut& cut_, 
    processor_prob& pprob = saveWithRandomName(processorName_t("cut_xy_"))
    );

  static xy_plane hitmap(
    const axis& x_, 
    const axis& y_, 
    processor_prob& pprob = saveWithRandomName(processorName_t("hitmap__"))
    );
  
  static xy_plane linear_trans(
    const xy_plane& pl, 
    double a11, double a12, 
    double a21, double a22, 
    processor_prob pprob = saveWithRandomName(processorName_t("linear_trans__"))
    );

  static xy_plane rotate(
    const xy_plane& pl, 
    double angle, 
    processor_prob pprob = saveWithRandomName(processorName_t("rotate__"))
    );

  static xy_plane residual(
    const axis& x_, 
    const axis& y_, 
    processor_prob& pprob = saveWithRandomName(processorName_t("residual__"))
    );

  static xy_plane transform(
    const xy_plane& pl, 
    x_slope_t x_slope, x_offset_t x_offset,
    y_slope_t y_slope, y_offset_t y_offset,
    processor_prob& pprob = saveWithRandomName(processorName_t("transform__"))
    );

  static xy_plane transform_move(
    const xy_plane& pl, 
    x_offset_t x_offset,
    y_offset_t y_offset,
    processor_prob& pprob = saveWithRandomName(processorName_t("transform_move__"))
    );
 
  static xy_plane modulo(
    const xy_plane& hits,
    modulo_x x_mod,
    modulo_y y_mod,
    processor_prob& pprob_ = saveWithRandomName(processorName_t("modulo__"))
    );
};


#endif // xy_pro_h__
