#ifndef find_nearest_h__
#define find_nearest_h__
#include "sct/platform.hh"
#include "sct/processor_prob.hh"
#include "sct/predef/plane.hh"


class DllExport find_nearest {
public:
  find_nearest(const xy_plane& plane_A,
    const xy_plane& plane_B,
    double x_cutoff,
    double y_cutoff,
    processor_prob& pprob = saveWithRandomName(processorName_t("find_nearest__"))
    );
  xy_plane getResidual() const;
  xy_plane getHitOnPlaneA() const;
  xy_plane getHitOnPlaneB() const;

private:
  collection* m_coll = nullptr;
};

#endif // find_nearest_h__
