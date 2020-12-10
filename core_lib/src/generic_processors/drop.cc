#include "sct/generic_processors/drop.hh"
#include "sct/processor.h"
#include "sct/processor_prob.hh"
#include <map>
#include "sct/generic_plane.hh"
#include "sct/ProcessorCollection.h"
#include <iostream>


namespace sct {


  class processor_generic_drop :public processor {
  public:
    processor_generic_drop(const generic_plane& pl,const  std::vector<axesName_t>& ax, const processor_prob& pprob);

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

  processor_generic_drop::processor_generic_drop(const generic_plane& pl,const  std::vector<axesName_t>& ax, const processor_prob& pprob) :m_plane1(pl), m_pprob(pprob)
  {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      if (std::find(ax.begin(), ax.end(), e) != ax.end()) {
        continue;
      }
      outNames.push_back(e);
    }

    m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));

    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));

    for (auto & e : m_plane1.get_axes_names()) {
      if (std::find(ax.begin(), ax.end(), e) != ax.end()) {
        continue;
      }
      auto d = Snew double();
      m_plane1.setHitAxisAdress(e, d.get());
      m_p1[e] = d;
      m_outputPlane->setHitAxisAdress(e, d.get());
    }

    
  }


  init_returns processor_generic_drop::init()
  {
    return i_sucess;
  }

  process_returns processor_generic_drop::processEvent()
  {
    ++m_current;
    m_output_coll->clear_event();
    
    while (m_plane1.next()) {
      m_outputPlane->push(ID_t(0));
    }

    return p_sucess;
  }

  process_returns processor_generic_drop::fill()
  {
    m_output_coll->set_Event_Nr(m_current);
    m_output_coll->save();
    return p_sucess;
  }

  end_returns processor_generic_drop::end()
  {
    return e_success;
  }

  processorName_t processor_generic_drop::get_name()
  {
    return m_pprob.name;
  }

  collection* processor_generic_drop::get_output_collection()
  {
    return m_output_coll.get();
  }

  generic_plane drop(const generic_plane & pl,const  std::vector<axesName_t>& ax, const processor_prob& pprob) {

    std::shared_ptr<processor> p(new processor_generic_drop(pl, std::move(ax), pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_generic_drop*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }

  generic_plane select(const generic_plane & pl, const  std::vector<axesName_t>& ax, const processor_prob& pprob) {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      if (std::find(ax.begin(), ax.end(), e) != ax.end()) {
        continue;
      }
      outNames.push_back(e);
    }
    std::shared_ptr<processor> p(new processor_generic_drop(pl, std::move(outNames), pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_generic_drop*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }

}