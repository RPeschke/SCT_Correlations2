#ifndef processor_generic_append_plane_h__
#define processor_generic_append_plane_h__

#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "sct/generic_plane.hh"
#include "sct/processor_prob.hh"
#include "sct/predef/plane.hh"

#include "sct/internal/strong_types.h"

#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/axCutHandle.hh"
#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/lambda_Note.hh"
#include "sct/generic_processors/planeCut.hh"
#include "sct/generic_processors/generic_operator.hh"


DllExport generic_plane generic_append_plane(const generic_plane& pl, axesName_t  axName, const cutNote& ax, const processor_prob& pprob = saveWithRandomName(processorName_t("app_")));
  


#endif // processor_generic_append_plane_h__
