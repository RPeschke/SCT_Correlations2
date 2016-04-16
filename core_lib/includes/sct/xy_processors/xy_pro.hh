#ifndef xy_pro_h__
#define xy_pro_h__
#include "sct/platform.hh"
#include "sct/predef/plane.hh"
#include "sct/processor_prob.hh"
#include "sct/axis.hh"
#include "sct/legacy/s_cuts.h"

class TH1;
class TH2;
class DllExport xy_pro {
public:
  static xy_plane correlations(
    const axis& x_,
    const axis& y_,
    processor_prob& pprob = saveWithRandomName("correlation_")
    );

  static void fill2Hist(
    const axis& x_,
    TH1* h1,
    processor_prob& pprob = DontsaveWithRandomName("fill2hist1d__")
    );
  static void fill2Hist(
    const xy_plane& x_,
    TH2* h2,
    processor_prob& pprob = DontsaveWithRandomName("fill2hist2d__")
    );
  static xy_plane cut_xy(
    const xy_plane& pl, 
    const S_Cut& cut_, 
    processor_prob& pprob = saveWithRandomName("cut_xy_")
    );

  static xy_plane hitmap(
    const axis& x_, 
    const axis& y_, 
    processor_prob& pprob = saveWithRandomName("hitmap__")
    );
  
  static xy_plane linear_trans(
    const xy_plane& pl, 
    double a11, double a12, 
    double a21, double a22, 
    processor_prob pprob = saveWithRandomName("linear_trans__")
    );

  static xy_plane rotate(
    const xy_plane& pl, 
    double angle, 
    processor_prob pprob = saveWithRandomName("rotate__")
    );

  static xy_plane residual(
    const axis& x_, 
    const axis& y_, 
    processor_prob& pprob = saveWithRandomName("residual__")
    );

  static xy_plane transform(
    const xy_plane& pl, 
    double x_slope, double x_offset, 
    double y_slope, double y_offset, 
    processor_prob& pprob = saveWithRandomName("transform__")
    );

  static xy_plane transform_move(
    const xy_plane& pl, 
    double x_offset, 
    double y_offset, 
    processor_prob& pprob = saveWithRandomName("transform_move__")
    );
 
  static xy_plane modulo(
    const xy_plane& hits,
    double x_mod,
    double y_mod,
    processor_prob& pprob_ = saveWithRandomName("modulo__")
    );
};


#endif // xy_pro_h__
