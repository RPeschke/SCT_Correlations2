#ifndef group_events_h__
#define group_events_h__

#include "sct/generic_plane.hh"
#include "sct/internal/strong_types.h"
#include "sct/processor_prob.hh"
#include <vector>
namespace sct {

  
 DllExport generic_plane group_events(const generic_plane & pl, const axesName_t & ax, const processor_prob& pprob = saveWithRandomName(processorName_t("group_evets__")));
 DllExport generic_plane accumulate_groups(const generic_plane & pl, const std::vector<axesName_t> & ax, const processor_prob& pprob = saveWithRandomName(processorName_t("accumulate_groups__")));
 DllExport generic_plane enumerate_occurrence(const generic_plane & pl, const std::vector<axesName_t> & ax, const processor_prob& pprob = saveWithRandomName(processorName_t("enumerate_occurrence___")));
 DllExport generic_plane first_occurrence(const generic_plane & pl, const std::vector<axesName_t> & ax, const processor_prob& pprob = saveWithRandomName(processorName_t("first_occurrence___")));
}

#endif // group_events_h__
