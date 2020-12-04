#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/generic_processors/processor_generic_correlation.hh"
#include "sct/internal/vector_helpers.hh"
#include "sct/generic_processors/processor_generic_select.hh"
#include <iostream>

class processor_generic_select :public processor {
public:
  processor_generic_select(const std::vector<note_ref> ax_select, const  cutNote& ax_where, const processor_prob& pprob);

  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  std::vector<planeCut> m_planes;
  std::vector<  std::shared_ptr<cutNote> > m_ax_select;
  std::shared_ptr<cutNote> m_ax_where;
  std::vector<axesName_t> m_names;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;

  std::map<axesName_t,std::shared_ptr<double>> m_p1;
  std::vector<std::function<void()> > m_val_fun;
  
  
  //std::vector<generic_plane*> m_planes;
  
};

generic_plane select(const std::initializer_list<note_ref>  ax_select, const  cutNote& ax_where, const processor_prob& pprob /*= saveWithRandomName(processorName_t("select__")) */)
{
  std::vector<note_ref> ax_select1(ax_select);
  std::shared_ptr<processor> p(new processor_generic_select(ax_select1, ax_where, pprob));
  ax_select1[0].m_note->get_planes()[0]->get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_generic_select*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}


generic_plane select(const std::initializer_list<note_ref> ax_select, cutNote&& ax_where, const processor_prob& pprob /*= saveWithRandomName(processorName_t("select__")) */)
{
  std::vector<note_ref> ax_select1(ax_select);
  std::shared_ptr<processor> p(new processor_generic_select(ax_select1, ax_where, pprob));
  ax_select1[0].m_note->get_planes()[0]->get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_generic_select*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}

processor_generic_select::processor_generic_select(const std::vector<note_ref> ax_select, const  cutNote& ax_where, const processor_prob& pprob)
  :
  m_pprob(pprob)
{
  std::vector<generic_plane*> planes_ptr;
  m_ax_where = ax_where.copy();
  for (auto& e : ax_select) {
    m_ax_select.push_back(e.m_note->copy());
    
    for (auto pl : e.m_note->get_planes()) {
      if(!sct::contains(planes_ptr, pl)) {
        planes_ptr.push_back(pl);
      }
    }

  }

  for (auto pl : m_ax_where->get_planes()) {
    if (!sct::contains(planes_ptr, pl)) {
      planes_ptr.push_back(pl);
    }
  }

  for (auto pl : planes_ptr) {
    m_planes.emplace_back(*pl);
  }

  std::vector<axesName_t> outNames;
  for (const auto& e : m_ax_select) {
    outNames.push_back(e->get_name());
  }

  for (auto& pl : m_planes) {
    for (auto& e : m_ax_select) {
      e->register_plane(pl);
    }
    m_ax_where->register_plane(pl);
  }
  m_pprob.setProcessorCollection(ax_select[0].m_note->get_planes()[0]->get_ProcessorCollection());
  m_pprob.setAxis(outNames);
  m_pprob.addAxis(axesName_t("ID"));

  m_output_coll = Snew collection(m_pprob);
  m_outputPlane = Snew generic_plane (m_output_coll->getPlane(ID_t(0)));

  for (auto & e : m_ax_select) {
    auto d  = Snew double();
    m_val_fun.push_back([d, e]() {  *d = e->get_value(); });
    m_p1[e->get_name()] = d;
    m_outputPlane->setHitAxisAdress(e->get_name(), d.get());
  }

}




init_returns processor_generic_select::init()
{
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}


process_returns processor_generic_select::processEvent()
{
  ++m_current;
  m_output_coll->clear_collection();
  int counter = 0;
  for (auto& pl : m_planes) {
    while (pl.next()){
      if (m_ax_where->get_value()) {
        for (const auto & e : m_val_fun) {
          counter++;
          e();
        }
        m_outputPlane->push();
      }
    }
  }
  std::cout << m_current << necessary_CONVERSION(m_output_coll->get_name()) << "  " << counter << std::endl;
  return p_sucess;
}

process_returns processor_generic_select::fill()
{
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_generic_select::end()
{
  return e_success;
}

processorName_t processor_generic_select::get_name()
{
  return m_pprob.name;
}

collection* processor_generic_select::get_output_collection()
{
  return m_output_coll.get();
}



