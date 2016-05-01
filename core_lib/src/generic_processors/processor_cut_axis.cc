#include "sct/generic_processors/processor_cut_axis.hh"
#include "sct/generic_plane.hh"
#include "sct/platform.hh"
#include "sct/collection.h"
#include "sct/processor_prob.hh"
#include "sct/ProcessorCollection.h"
#include "sct/generic_processors/planeCut.hh"
#include "sct/generic_processors/cutNote.hh"

class processor_cut_axis :public processor {
public:
  processor_cut_axis(const generic_plane& pl, const cutNote& ax, const processor_prob& pprob);

  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  planeCut m_plane;
  std::shared_ptr<cutNote> m_note;
  const std::vector<axesName_t> m_names;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;

};

processor_cut_axis::processor_cut_axis(const generic_plane& pl, const cutNote& ax,const processor_prob& pprob) :m_note(ax.copy()), m_plane(pl),m_names(pl.get_axes_names()),m_pprob(pprob) {
  m_pprob.setAxis(m_names);
  m_pprob.addAxis(axesName_t("ID"));
  m_output_coll = _MAKE_SHARED1(collection, m_pprob);
  m_note->register_plane(m_plane);
  m_outputPlane = _MAKE_SHARED1(generic_plane, m_output_coll->getPlane(ID_t(0)));
  for (auto &e : m_names) {
    m_outputPlane->setHitAxisAdress(e, m_plane.getAxis(e));
  }
  
}


init_returns processor_cut_axis::init() {
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}

process_returns processor_cut_axis::processEvent() {
  ++m_current;
  m_output_coll->clear_event();

  while (m_plane.next()) {
    if (m_note->get_value()) {
      m_outputPlane->push(ID_t(0));
    }
  }


 return p_sucess;
}

process_returns processor_cut_axis::fill() {
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_cut_axis::end() {
  return e_success;
}

processorName_t processor_cut_axis::get_name() {
 return m_pprob.name;
}

collection* processor_cut_axis::get_output_collection() {
  return m_output_coll.get();
}

xy_plane cut_op(const xy_plane& pl, const cutNote& ax, const processor_prob& pprob) {
  return cut_op(*pl.get_generic_plane(), ax, pprob);
}

generic_plane cut_op(const generic_plane& pl, const cutNote& ax, const processor_prob& pprob) {
  std::shared_ptr<processor> p(new processor_cut_axis(pl,ax, pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_cut_axis*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}





