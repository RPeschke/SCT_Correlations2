#include "sct/generic_processors/group_events.hh"
#include "sct/processor.h"
#include "sct/processor_prob.hh"
#include <map>
#include "sct/generic_plane.hh"
#include "sct/ProcessorCollection.h"


namespace sct {
  class processor_generic_enumerate_occurrence :public processor {
  public:
    processor_generic_enumerate_occurrence(const generic_plane& pl, const std::vector<axesName_t> & ax, const processor_prob& pprob);

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


    std::vector<std::vector<double>> m_occurencies;
    std::vector<double*> m_current_event;
    double* m_occurency;
    double m_group_axis_last = 0;

  };

  processor_generic_enumerate_occurrence::processor_generic_enumerate_occurrence(const generic_plane& pl, const std::vector<axesName_t> & ax, const processor_prob& pprob)
  :m_plane1(pl), m_pprob(pprob)
  {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      outNames.push_back(e);
    }

    m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));
    m_pprob.addAxis(axesName_t("occurrence"));

    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));

    for (auto & e : m_plane1.get_axes_names()) {
      auto d = Snew double();
      m_plane1.setHitAxisAdress(e, d.get());
      m_p1[e] = d;
      m_outputPlane->setHitAxisAdress(e, d.get());
    }

    
    auto d = Snew double();
    m_p2[axesName_t("occurrence")] = d;
    m_outputPlane->setHitAxisAdress(axesName_t("occurrence"), d.get());

    m_occurency = d.get();
    m_current_event.push_back(m_occurency);


    for (const auto& e : ax) {
      m_current_event.push_back(m_p1[e].get());

    }

  }


  init_returns processor_generic_enumerate_occurrence::init()
  {
    m_current = 0;
    return i_sucess;
  }

  template <typename T1, typename T2>
  bool is_same_event(const T1& e, const T2& current_event) {
    for (int i = 1; i < e.size(); ++i) {
      if (e[i] != *current_event[i]) {
        return false;
      }
    }
    return true;
  }
  template <typename T1, typename T2>
  bool push_event(T1& occurencies, T2& current_event) {
    for (auto& e : occurencies) {
      if (is_same_event(e, current_event)) {
        *current_event[0] = ++e[0];
        return true;
      }
    }
    return false;
  }
  process_returns processor_generic_enumerate_occurrence::processEvent()
  {

    ++m_current;
    m_output_coll->clear_event();


    while (m_plane1.next()) {
      if (!push_event(m_occurencies, m_current_event)) {
        std::vector<double> new_event;
        *m_current_event[0] = 1;

        for (const auto e : m_current_event) {
          new_event.push_back(*e);
        }
        m_occurencies.push_back(new_event);
      }

      m_outputPlane->push(ID_t(0));

    }
    
    return p_sucess;
  }


  process_returns processor_generic_enumerate_occurrence::fill()
  {
    m_output_coll->set_Event_Nr(m_current);
    m_output_coll->save();
    return p_sucess;
  }


  end_returns processor_generic_enumerate_occurrence::end()
  {
    return e_success;
  }


  processorName_t processor_generic_enumerate_occurrence::get_name()
  {
    return m_pprob.name;
  }


  collection* processor_generic_enumerate_occurrence::get_output_collection()
  {
    return m_output_coll.get();
  }

  generic_plane enumerate_occurrence(const generic_plane & pl, const std::vector<axesName_t> & ax, const processor_prob& pprob /*= saveWithRandomName(processorName_t("accumulate_groups__"))*/)
  {
    std::shared_ptr<processor> p(new processor_generic_enumerate_occurrence(pl, ax,pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_generic_enumerate_occurrence*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }

}