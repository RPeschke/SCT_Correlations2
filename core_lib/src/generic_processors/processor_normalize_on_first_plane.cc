#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/generic_processors/processor_generic_correlation.hh"

class processor_normalize_on_first_plane :public processor {
public:
  processor_normalize_on_first_plane(const generic_plane& pl, const generic_plane& p2, const processor_prob& pprob);

  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  generic_plane m_plane1;
  generic_plane m_normalisation_plane;
  std::vector<axesName_t> outNames;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;

  std::map<axesName_t, std::shared_ptr<double>> m_p1;
  std::map<axesName_t, std::shared_ptr<double>> m_p_norm;
  std::map<axesName_t, std::shared_ptr<double>> m_p_out;

};

processor_normalize_on_first_plane::processor_normalize_on_first_plane(const generic_plane& pl, const generic_plane& p_norm, const processor_prob& pprob)
  :
  m_plane1(pl),
  m_normalisation_plane(p_norm),
  m_pprob(pprob)
{
  
  for (auto &e : pl.get_axes_names()) {
    outNames.push_back(axesName_t(necessary_CONVERSION(e)));
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
  }

  for (auto & e : m_normalisation_plane.get_axes_names()) {
    auto d = Snew double();
    m_normalisation_plane.setHitAxisAdress(e, d.get());
    m_p_norm[e] = d;
  }

  for (auto & e : outNames) {
    auto d = Snew double();
    m_p_out[e] = d;
    m_outputPlane->setHitAxisAdress(e, d.get());

  }

}

init_returns processor_normalize_on_first_plane::init()
{
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}


process_returns processor_normalize_on_first_plane::processEvent()
{
  ++m_current;
  m_output_coll->clear_event();
  std::map<axesName_t, std::map<int, double> > m_summ;
  std::map<axesName_t, std::map<int, int>> m_count;

  while (m_normalisation_plane.next()){
    double sector = *m_p_norm[axesName_t("sector")];
    double section = *m_p_norm[axesName_t("section")];
    for (auto &e : outNames){
      m_summ[e][sector*100 + section] = (m_summ[e][sector * 100 + section] * m_count[e][sector * 100 + section] + (*m_p_norm[e]) ) / (m_count[e][sector * 100 + section]+1);
      m_count[e][sector * 100 + section] += 1;
    }

  }


  while (m_plane1.next()) {
    
    double sector = *m_p1[axesName_t("sector")];
    double section = *m_p1[axesName_t("section")];

    for (auto &e : outNames) {
      *m_p_out[e] = *m_p1[e];
    }
    *m_p_out[axesName_t("x")] -= m_summ[axesName_t("x")][sector * 100 + section];
    *m_p_out[axesName_t("y")] -= m_summ[axesName_t("y")][sector * 100 + section];
    *m_p_out[axesName_t("z")] -= m_summ[axesName_t("z")][sector * 100 + section];
    m_outputPlane->push(ID_t(0));
  }


  return p_sucess;
}

process_returns processor_normalize_on_first_plane::fill()
{
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_normalize_on_first_plane::end()
{
  return e_success;
}

processorName_t processor_normalize_on_first_plane::get_name()
{
  return m_pprob.name;
}

collection* processor_normalize_on_first_plane::get_output_collection()
{
  return m_output_coll.get();
}



DllExport generic_plane normalize_with__(const generic_plane& pl1, const generic_plane& p2, const processor_prob& pprob /*= saveWithRandomName(processorName_t("norm_"))*/)
{
  std::shared_ptr<processor> p(new processor_normalize_on_first_plane(pl1, p2, pprob));
  pl1.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_normalize_on_first_plane*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}
