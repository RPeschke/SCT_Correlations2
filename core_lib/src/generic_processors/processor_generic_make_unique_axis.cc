#include "sct/generic_processors/processor_cut_axis.hh"
#include "sct/generic_plane.hh"
#include "sct/platform.hh"
#include "sct/collection.h"
#include "sct/processor_prob.hh"
#include "sct/ProcessorCollection.h"
#include "sct/generic_processors/planeCut.hh"
#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/processor_generic_make_unique_axis.hh"
#include <algorithm>

class processor_generic_make_unique_axis :public processor {
public:
  processor_generic_make_unique_axis(const generic_plane& pl, axesName_t ax, const processor_prob& pprob);

  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  planeCut m_plane;

  const std::vector<axesName_t> m_names;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;
  double* m_axis;
  std::vector <double> m_elements;
};

processor_generic_make_unique_axis::processor_generic_make_unique_axis(const generic_plane& pl, axesName_t ax,const processor_prob& pprob)
      :
  m_plane(pl),
  m_names(pl.get_axes_names()),
  m_pprob(pprob) {

    m_pprob.setProcessorCollection( pl.get_ProcessorCollection());
    m_pprob.setAxis(m_names);
    m_pprob.addAxis(axesName_t("ID"));
    m_output_coll = _MAKE_SHARED1(collection, m_pprob);
    m_outputPlane = _MAKE_SHARED1(generic_plane, m_output_coll->getPlane(ID_t(0)));
    for (auto &e : m_names) {
      m_outputPlane->setHitAxisAdress(e, m_plane.getAxis(e));
    }

    m_axis = m_plane.getAxis(ax);
}


init_returns processor_generic_make_unique_axis::init() {
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}

bool contains_element(std::vector<double> const& items, double const& item)
{
  return std::find(items.begin(), items.end(), item) != items.end();
}
process_returns processor_generic_make_unique_axis::processEvent() {
  ++m_current;
  m_output_coll->clear_event();
  m_elements.clear();
  while (m_plane.next()) {

    if (!contains_element(m_elements, *m_axis)) {
      m_elements.push_back(*m_axis);
      m_outputPlane->push(ID_t(0));
    }
   
  }


 return p_sucess;
}

process_returns processor_generic_make_unique_axis::fill() {
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_generic_make_unique_axis::end() {
  return e_success;
}

processorName_t processor_generic_make_unique_axis::get_name() {
 return m_pprob.name;
}

collection* processor_generic_make_unique_axis::get_output_collection() {
  return m_output_coll.get();
}



generic_plane unique_of(const generic_plane& pl, axesName_t ax, const processor_prob& pprob) {
  std::shared_ptr<processor> p(new processor_generic_make_unique_axis(pl,ax, pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_generic_make_unique_axis*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}





