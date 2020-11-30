#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/generic_processors/processor_generic_correlation.hh"
#include "sct/internal/vector_helpers.hh"

class processor_generic_select :public processor {
public:
  processor_generic_select(const generic_plane& pl, const generic_plane& p2, const std::vector<axesName_t>& ax, const processor_prob& pprob);

  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  generic_plane m_plane1;
  generic_plane m_plane2;
  std::vector<axesName_t> m_names;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;

  std::map<axesName_t,std::shared_ptr<double>> m_p1;
  std::map<axesName_t, std::shared_ptr<double>> m_p2;
  std::shared_ptr<double> m_index1;
  std::shared_ptr<double> m_index2;

  std::vector<std::pair<double*, double*>> join_axis;
};

processor_generic_select::processor_generic_select(const generic_plane& pl, const generic_plane& p2,const std::vector<axesName_t>& ax, const processor_prob& pprob)
                 :
  m_plane1(pl),
  m_plane2(p2),
  m_names(pl.get_axes_names()), 
  m_pprob(pprob)
{
  auto plane1_axis_names = m_plane1.get_axes_names();
  auto plane2_axis_names = m_plane2.get_axes_names();
  std::vector<axesName_t> outNames;
  for (auto &e: plane1_axis_names){
    if (sct::contains(ax, e)) {
      outNames.push_back(axesName_t(necessary_CONVERSION(e) ));
    } else if ( !sct::contains(plane2_axis_names, e)) {
      outNames.push_back(axesName_t(necessary_CONVERSION(e)));
    }else {
      outNames.push_back(axesName_t(necessary_CONVERSION(e) + "1"));
    }
  }

  for (auto &e : plane2_axis_names) {
    if (!sct::contains(ax, e)) {
      if (!sct::contains(plane1_axis_names, e)) {
        outNames.push_back(axesName_t(necessary_CONVERSION(e)));
      } else {
        outNames.push_back(axesName_t(necessary_CONVERSION(e) + "2"));
      }
    }
  }

  m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
  m_pprob.setAxis(outNames);
  m_pprob.addAxis(axesName_t("ID"));
  m_pprob.addAxis(axesName_t("index1"));
  m_pprob.addAxis(axesName_t("index2"));
  m_output_coll = Snew collection(m_pprob);
  m_outputPlane = Snew generic_plane (m_output_coll->getPlane(ID_t(0)));

  for (auto & e : plane1_axis_names) {
    auto d  = Snew double();
    m_plane1.setHitAxisAdress(e, d.get());
    m_p1[e] = d;
    
    if (sct::contains(ax, e)) {
      m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e)), d.get());
    } else if (!sct::contains(plane2_axis_names, e)) {
      m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e) ), d.get());
    }  else {
      m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e) + "1"), d.get());
    }
  }
  
  for (auto & e : plane2_axis_names) {
    auto d = Snew double();
    m_plane2.setHitAxisAdress(e, d.get());
    m_p2[e] = d;
    if (!sct::contains(ax, e)) {
      if (!sct::contains(plane1_axis_names, e)) {
        m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e)), d.get());
      } else {
        m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e) + "2"), d.get());
      }
    }
  }
  m_index1 = Snew double();
  m_outputPlane->setHitAxisAdress(axesName_t("index1"), m_index1.get());
  m_index2 = Snew double();
  m_outputPlane->setHitAxisAdress(axesName_t("index2"), m_index2.get());

  for (const auto& e : ax) {
    join_axis.push_back({ m_p1[e].get() , m_p2[e].get() });
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



