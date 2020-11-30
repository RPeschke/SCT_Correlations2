#include "sct/generic_processors/drop.hh"
#include "sct/processor.h"
#include "sct/processor_prob.hh"
#include <map>
#include "sct/generic_plane.hh"
#include "sct/ProcessorCollection.h"
#include <iostream>


namespace sct {


  class processor_generic_flatten :public processor {
  public:
    processor_generic_flatten(const generic_plane& pl, const processor_prob& pprob);

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

  processor_generic_flatten::processor_generic_flatten(const generic_plane& pl, const processor_prob& pprob)
  {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      outNames.push_back(e);
    }

    m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));
    m_pprob.addAxis(axesName_t("index"));

    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));

    for (auto & e : m_plane1.get_axes_names()) {
      auto d = Snew double();
      m_plane1.setHitAxisAdress(e, d.get());
      m_p1[e] = d;
      m_outputPlane->setHitAxisAdress(e, d.get());
    }
    auto d = Snew double();
    m_p1[axesName_t("index")] = d;
    m_outputPlane->setHitAxisAdress(axesName_t("index"), d.get());
  }


  init_returns processor_generic_flatten::init()
  {
    return i_sucess;
  }


  process_returns processor_generic_flatten::processEvent()
  {
    ++m_current;

    int index = 0;
    while (m_plane1.next()) {
      m_output_coll->clear_event();
      *m_p1[axesName_t("index")] = index++;
      m_outputPlane->push(ID_t(0));
      m_output_coll->set_Event_Nr(m_current);
      m_output_coll->save();
    }

    return p_sucess;
  }


  process_returns processor_generic_flatten::fill()
  {
    return p_sucess;
  }


  end_returns processor_generic_flatten::end()
  {
    return e_success;
  }


  processorName_t processor_generic_flatten::get_name()
  {
    return m_pprob.name;
  }


  collection* processor_generic_flatten::get_output_collection()
  {
    return m_output_coll.get();
  }


  generic_plane flatten(const generic_plane & pl, const processor_prob& pprob /*= saveWithRandomName(processorName_t("flatten__"))*/)
  {
    std::shared_ptr<processor> p(new processor_generic_flatten(pl, pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_generic_flatten*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }
}


