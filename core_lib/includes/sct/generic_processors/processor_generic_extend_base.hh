#ifndef processor_generic_extend_base_h__
#define processor_generic_extend_base_h__
#include "sct/processor.h"
#include "sct/generic_plane.hh"
#include "sct/processor_prob.hh"
#include <vector>
#include <utility>
#include <map>
#include "sct/generic_processors/planeCut.hh"
#include "sct/platform.hh"


class collection;


class DllExport processor_generic_extend_base :public processor {
public:
  processor_generic_extend_base(const generic_plane& pl,   const processor_prob& pprob);

  virtual init_returns init() override;


  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  void add_axis(const axesName_t& name, double*);
  void get_axis(const axesName_t& name, double*);
  bool next();
  void push();
  void clear();

  void Finish_constructing();
  generic_plane m_plane1;
  std::vector<axesName_t>  m_appended_axis;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;

  std::map<axesName_t, std::shared_ptr<double>> m_internal_connections;
  std::map<axesName_t, double*> m_external_connections;


};


namespace ArggLib {
  namespace ArggLib_impl {

    enum _Pnew_ {
      __Pnew_start
    };

    template <typename T>
    generic_plane operator<<(_Pnew_, T* in_) {
      in_->Finish_constructing();
      return in_->get_output_collection()->getPlane(ID_t(0));
    }
  }
}
#define Pnew ArggLib::ArggLib_impl::__Pnew_start << new 


#define register_axis(x)       get_axis(axesName_t(#x), &x)
#define register_new_axis(x)   add_axis(axesName_t(#x), &x)

#endif // processor_generic_extend_base_h__
