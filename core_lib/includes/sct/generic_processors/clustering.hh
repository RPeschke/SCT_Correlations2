#ifndef clustering_h__
#define clustering_h__


#include "sct/generic_plane.hh"
#include "sct/internal/strong_types.h"
#include "sct/processor_prob.hh"


struct DllExport cl_conf {
  cl_conf() {}
  cl_conf(const axesName_t& name, double val) {
    m_ax.push_back(name);
    m_value.push_back(val);
  }
  std::vector<axesName_t> m_ax;
  std::vector<double> m_value;
  void push(axesName_t name, double val) {
    m_ax.push_back(name);
    m_value.push_back(val);
  }
  cl_conf& operator+(const  cl_conf& rhs) {
    for (int i = 0; i < rhs.m_ax.size(); ++i) {
      m_ax.push_back(rhs.m_ax[i]);
      m_value.push_back(rhs.m_value[i]);
    }
    return *this;
  }

};


namespace sct {


  DllExport generic_plane clustering(const generic_plane & pl, cl_conf conf, const processor_prob& pprob = saveWithRandomName(processorName_t("clustering__")));
}


#endif // clustering_h__
