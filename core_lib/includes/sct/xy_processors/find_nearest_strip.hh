#ifndef find_nearest_strip_h__
#define find_nearest_strip_h__
#include "sct/processor_prob.hh"
#include "sct/predef/plane.hh"
#include "sct/platform.hh"

enum axis_def
{
  x_axis_def, y_axis_def
};
class generic_plane;
class collection;
class DllExport find_nearest_strip {
public:
  find_nearest_strip(const xy_plane& planeA,
    const xy_plane& planeB,
    axis_def search_axis,
    residualCut_t cutOfff,
    processor_prob plot_prob_ = saveWithRandomName(processorName_t("find_nearest_strip__")));

  xy_plane getResidual() const;
  xy_plane getHitOnPlaneA() const;
  xy_plane getHitOnPlaneB() const;

private:
  collection* m_coll=nullptr;
};

#endif // find_nearest_strip_h__
