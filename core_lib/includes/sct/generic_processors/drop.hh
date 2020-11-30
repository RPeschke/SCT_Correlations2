#ifndef drop_h__
#define drop_h__



#include "sct/generic_plane.hh"
#include "sct/internal/strong_types.h"
#include "sct/processor_prob.hh"
class select_conf {
public:
  select_conf(axesName_t orign, axesName_t newName= axesName_t("")) : m_orign(orign), m_newName(newName) {
    if (necessary_CONVERSION(m_newName).empty()) {
      m_newName = m_orign;
  }
  }
  axesName_t m_orign, m_newName;
};
namespace sct {


  DllExport generic_plane drop(const generic_plane & pl,const std::vector<axesName_t>& ax, const processor_prob& pprob = saveWithRandomName(processorName_t("drop__")));
  DllExport generic_plane select(const generic_plane & pl, const std::vector<axesName_t>& ax, const processor_prob& pprob = saveWithRandomName(processorName_t("select__")));
  
  DllExport generic_plane flatten(const generic_plane & pl, const processor_prob& pprob = saveWithRandomName(processorName_t("flatten__")));
}



#endif // drop_h__
