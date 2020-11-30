#include "sct/generic_processors/group_events.hh"
#include "sct/processor.h"
#include "sct/processor_prob.hh"
#include <map>
#include "sct/generic_plane.hh"
#include "sct/ProcessorCollection.h"
#include "sct/internal/vector_helpers.hh"

namespace sct {


  class processor_generic_group_events  :public processor {
  public:
    processor_generic_group_events(const generic_plane& pl, const axesName_t ax , const processor_prob& pprob);

    virtual init_returns init() override;

    virtual process_returns processEvent() override;

    virtual process_returns fill() override;

    virtual end_returns end() override;

    virtual processorName_t get_name() override;

    collection* get_output_collection();

    generic_plane m_plane1;

    std::shared_ptr<collection> m_output_coll;
    std::shared_ptr<generic_plane> m_outputPlane;
    processor_prob m_pprob;
    int m_current = 0;

    std::map<axesName_t, std::shared_ptr<double>> m_p1;
    std::map<axesName_t, std::shared_ptr<double>> m_p2;
    std::map<axesName_t, std::vector<double> > m_buffer;
    double* m_group_axis;
    double m_group_axis_last = 0;
	bool isEmpty = true;
  };

  processor_generic_group_events::processor_generic_group_events(const generic_plane& pl,  const axesName_t ax,  const processor_prob& pprob):m_plane1(pl), m_pprob(pprob)
  {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      outNames.push_back(e);
    }

    m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));
    
    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));

    for (auto & e : m_plane1.get_axes_names()) {
      auto d = Snew double();
      m_plane1.setHitAxisAdress(e, d.get());
      m_p1[e] = d;
      m_buffer[e] = std::vector<double>();
    }

    for (auto & e : m_plane1.get_axes_names()) {
      auto d = Snew double();
      m_p2[e] = d;
      m_outputPlane->setHitAxisAdress(e, d.get());
    }
    
    m_group_axis = m_p1[ax].get();
  }


  init_returns processor_generic_group_events::init()
  {
    return i_sucess;
  }

  process_returns processor_generic_group_events::processEvent()
  {
    ++m_current;
    m_output_coll->clear_event();
	  isEmpty = true;
    while (m_plane1.next()) {
      if (m_group_axis_last != *m_group_axis) {
		    isEmpty = false;
        for (int i = 0; i < m_buffer.begin()->second.size(); ++i) {
          for (const auto& e : m_buffer) {
            *m_p2[e.first] = e.second[i];
          }
          m_outputPlane->push(ID_t(0));
        }

        for (auto& e : m_buffer) {
          e.second.clear();
        }
      }

      for (auto& e : m_buffer) {
        e.second.push_back(*m_p1[e.first]);
      }
    }
    m_group_axis_last = *m_group_axis;
    return p_sucess;
  }

  process_returns processor_generic_group_events::fill()
  {
    m_output_coll->set_Event_Nr(m_current);
    if (isEmpty) {
      return p_skip;
    }
    
    m_output_coll->save();
    return p_skip;
  }

  end_returns processor_generic_group_events::end()
  {
    return e_success;
  }

  processorName_t processor_generic_group_events::get_name()
  {
    return m_pprob.name;
  }

  collection* processor_generic_group_events::get_output_collection()
  {
    return m_output_coll.get();
  }

  generic_plane group_events(const generic_plane & pl, const axesName_t & ax, const processor_prob& pprob) {

    std::shared_ptr<processor> p(new processor_generic_group_events(pl, ax, pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_generic_group_events*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }



  class processor_accumulate_groups :public processor {
  public:
    processor_accumulate_groups(const generic_plane& pl, const std::vector<axesName_t> & ax, const processor_prob& pprob);

    virtual init_returns init() override;

    virtual process_returns processEvent() override;

    virtual process_returns fill() override;

    virtual end_returns end() override;

    virtual processorName_t get_name() override;

    collection* get_output_collection();

    generic_plane m_plane1;

    std::shared_ptr<collection> m_output_coll;
    std::shared_ptr<generic_plane> m_outputPlane;
    processor_prob m_pprob;
    int m_current = 0;

    std::map<axesName_t, std::shared_ptr<double>> m_p1;
    std::map<axesName_t, std::shared_ptr<double>> m_p2;
    std::map<axesName_t, std::vector<double> > m_buffer;
    double* m_group_axis;
    double m_group_axis_last = 0;
    bool isEmpty = true;
  };

  processor_accumulate_groups::processor_accumulate_groups(const generic_plane& pl, const std::vector<axesName_t> & ax, const processor_prob& pprob)
  {

  }









  init_returns processor_accumulate_groups::init()
  {
    return i_sucess;
  }


  process_returns processor_accumulate_groups::processEvent()
  {
    return p_sucess;
  }


  process_returns processor_accumulate_groups::fill()
  {
    return p_sucess;
  }


  end_returns processor_accumulate_groups::end()
  {
    return e_success;
  }


  processorName_t processor_accumulate_groups::get_name()
  {
    return m_pprob.name;
  }


  collection* processor_accumulate_groups::get_output_collection()
  {
    return m_output_coll.get();
  }

  generic_plane accumulate_groups(const generic_plane & pl, const std::vector<axesName_t> & ax, const processor_prob& pprob /*= saveWithRandomName(processorName_t("accumulate_groups__"))*/)
  {
    std::shared_ptr<processor> p(new processor_accumulate_groups(pl, ax, pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_accumulate_groups*>(p.get())->get_output_collection()->getPlane(ID_t(0));
    
  }


  class processor_first_occurrence :public processor {
  public:
    processor_first_occurrence(const generic_plane& pl, const std::vector<axesName_t> & ax, const processor_prob& pprob);

    virtual init_returns init() override;

    virtual process_returns processEvent() override;

    virtual process_returns fill() override;

    virtual end_returns end() override;

    virtual processorName_t get_name() override;

    collection* get_output_collection();

    generic_plane m_plane1;

    std::shared_ptr<collection> m_output_coll;
    std::shared_ptr<generic_plane> m_outputPlane;
    processor_prob m_pprob;
    int m_current = 0;

    std::map<axesName_t, std::shared_ptr<double>> m_p1;
    

    std::vector<std::pair<double*, std::vector<double> >> m_buffer;

  };

  processor_first_occurrence::processor_first_occurrence(const generic_plane& pl, const std::vector<axesName_t> & ax, const processor_prob& pprob) :m_plane1(pl), m_pprob(pprob)
  {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      outNames.push_back(e);
    }

    m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));

    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));

    for (auto & e : m_plane1.get_axes_names()) {
      auto d = Snew double();
      m_plane1.setHitAxisAdress(e, d.get());
      m_p1[e] = d;
      m_outputPlane->setHitAxisAdress(e, d.get());
    }

    for (const auto& e : ax) {
      m_buffer.push_back(std::pair<double*, std::vector<double> >(m_p1[e].get(), std::vector<double>() ));
    }



  }


  init_returns processor_first_occurrence::init()
  {
    return i_sucess;
  }


  process_returns processor_first_occurrence::processEvent()
  {
    ++m_current;
    m_output_coll->clear_event();

    while (m_plane1.next()) {
      for (const auto& e: m_buffer){
        if (contains(e.second, *e.first)) {
          return p_sucess;
        }
      }
      for (auto& e : m_buffer) {
        e.second.push_back(*e.first);
      }
      m_outputPlane->push(ID_t(0));
    }

    return p_sucess;
  }


  process_returns processor_first_occurrence::fill()
  {
    m_output_coll->set_Event_Nr(m_current);
    m_output_coll->save();
    return p_sucess;
  }


  end_returns processor_first_occurrence::end()
  {
    return e_success;
  }


  processorName_t processor_first_occurrence::get_name()
  {
    return m_pprob.name;
  }


  collection* processor_first_occurrence::get_output_collection()
  {
    return m_output_coll.get();
  }

  generic_plane first_occurrence(const generic_plane & pl, const std::vector<axesName_t> & ax, const processor_prob& pprob /*= saveWithRandomName(processorName_t("first_occurrence___"))*/)
  {
    std::shared_ptr<processor> p(new processor_first_occurrence(pl, ax, pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_first_occurrence*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }

}