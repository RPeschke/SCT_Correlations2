#ifndef processor_generic_correlation_h__
#define processor_generic_correlation_h__

#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "sct/generic_plane.hh"
#include "sct/processor_prob.hh"
#include "sct/predef/plane.hh"



#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/axCutHandle.hh"
#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/lambda_Note.hh"
#include "sct/generic_processors/planeCut.hh"
#include "sct/generic_processors/generic_operator.hh"


DllExport generic_plane correlation(const generic_plane& pl1, const generic_plane& p2, const processor_prob& pprob = saveWithRandomName(processorName_t("corr_")));

enum _correlation_ {
  __correlation_start
};

struct DllExport _correlation__generic_plane_wraper {
  generic_plane pl1;
};

DllExport _correlation__generic_plane_wraper operator*(const generic_plane& pl, _correlation_);

DllExport generic_plane operator*(_correlation__generic_plane_wraper&& pl, const generic_plane& p2);




DllExport _correlation__generic_plane_wraper operator*(const xy_plane& pl, _correlation_);

DllExport generic_plane operator*(_correlation__generic_plane_wraper&& pl, const xy_plane& p2);


#define  cross *__correlation_start*

#endif // processor_generic_correlation_h__
