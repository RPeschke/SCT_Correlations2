#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/generic_processors/processor_generic_append_plane.hh"

class processor_generic_append_plane :public processor {
public:
  processor_generic_append_plane(const generic_plane& pl, axesName_t  axName , const cutNote& ax, const processor_prob& pprob);

  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();
  
  
  std::shared_ptr<cutNote> m_note;

  planeCut m_plane;
  std::vector<axesName_t> m_names;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;

  std::map<axesName_t, std::shared_ptr<double>> m_p1;

  std::shared_ptr<double> ret;
};

processor_generic_append_plane::processor_generic_append_plane(const generic_plane& pl, axesName_t  axName, const cutNote& ax , const processor_prob& pprob)
  :
  m_note(ax.copy()),
  m_plane(pl),
  m_names(pl.get_axes_names()),
  m_pprob(pprob)
{
  std::vector<axesName_t> outNames;
  for (auto &e : pl.get_axes_names()) {
    outNames.push_back(e);
  }
  outNames.push_back(axName);
  m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
  m_pprob.setAxis(outNames);
  m_pprob.addAxis(axesName_t("ID"));
  m_output_coll = Snew collection(m_pprob);
  m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));
  m_note->register_plane(m_plane);
  for (auto & e : m_names) {
    m_outputPlane->setHitAxisAdress(e, m_plane.getAxis(e));
  }
  ret = Snew double();
  m_outputPlane->setHitAxisAdress(axName, ret.get());




}

init_returns processor_generic_append_plane::init()
{
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}


process_returns processor_generic_append_plane::processEvent()
{
  ++m_current;
  m_output_coll->clear_event();

  while (m_plane.next()) {
    *ret = m_note->get_value();
    m_outputPlane->push(ID_t(0));
  }


  return p_sucess;
}

process_returns processor_generic_append_plane::fill()
{
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_generic_append_plane::end()
{
  return e_success;
}

processorName_t processor_generic_append_plane::get_name()
{
  return m_pprob.name;
}

collection* processor_generic_append_plane::get_output_collection()
{
  return m_output_coll.get();
}

generic_plane generic_append_plane(const generic_plane& pl, axesName_t  axName, const cutNote& ax, const processor_prob& pprob) {
  std::shared_ptr<processor> p(new processor_generic_append_plane(pl, axName, ax, pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_generic_append_plane*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}
