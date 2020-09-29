#ifndef group_events_h__
#define group_events_h__

#include "sct/generic_plane.hh"
#include "sct/internal/strong_types.h"
#include "sct/processor_prob.hh"

namespace sct {

  
 DllExport generic_plane group_events(const generic_plane & pl, const axesName_t & ax, const processor_prob& pprob = saveWithRandomName(processorName_t("group_evets__")));
}

#endif // group_events_h__
