#include "sct/axis.hh"
#include "sct/ProcessorCollection.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/generic_processors/processor_generic_correlation.hh"

class processor_generic_correlation :public processor {
public:
  processor_generic_correlation(const generic_plane& pl, const generic_plane& p2, const processor_prob& pprob);

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
};

processor_generic_correlation::processor_generic_correlation(const generic_plane& pl, const generic_plane& p2, const processor_prob& pprob) 
                 :
  m_plane1(pl),
  m_plane2(p2),
  m_names(pl.get_axes_names()), 
  m_pprob(pprob)
{
  std::vector<axesName_t> outNames;
  for (auto &e: pl.get_axes_names()){
    outNames.push_back(axesName_t(necessary_CONVERSION(e) + "1"));
  }

  for (auto &e : p2.get_axes_names()) {
    outNames.push_back(axesName_t(necessary_CONVERSION(e) + "2"));
  }

  m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
  m_pprob.setAxis(outNames);
  m_pprob.addAxis(axesName_t("ID"));
  m_pprob.addAxis(axesName_t("index1"));
  m_pprob.addAxis(axesName_t("index2"));
  m_output_coll = Snew collection(m_pprob);
  m_outputPlane = Snew generic_plane (m_output_coll->getPlane(ID_t(0)));
  
  for (auto & e : m_plane1.get_axes_names()) {
    auto d  = Snew double();
    m_plane1.setHitAxisAdress(e, d.get());
    m_p1[e] = d;
    

    m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e) + "1") , d.get());

  }
  
  for (auto & e : m_plane2.get_axes_names()) {
    auto d = Snew double();
    m_plane2.setHitAxisAdress(e, d.get());
    m_p2[e] = d;
    m_outputPlane->setHitAxisAdress(axesName_t(necessary_CONVERSION(e) + "2"), d.get());

  }
  m_index1 = Snew double();
  m_outputPlane->setHitAxisAdress(axesName_t("index1"), m_index1.get());
  m_index2 = Snew double();
  m_outputPlane->setHitAxisAdress(axesName_t("index2"), m_index2.get());
}

init_returns processor_generic_correlation::init()
{
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}


process_returns processor_generic_correlation::processEvent()
{
  ++m_current;
  m_output_coll->clear_event();
  
  *m_index1 = -1;
  while (m_plane1.next()) {
    *m_index1 = *m_index1 + 1;
    *m_index2 = -1;
    while (m_plane2.next()) {
      *m_index2 = *m_index2 + 1;
      m_outputPlane->push(ID_t(0));
    }

  }


  return p_sucess;
}

process_returns processor_generic_correlation::fill()
{
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_generic_correlation::end()
{
  return e_success;
}

processorName_t processor_generic_correlation::get_name()
{
  return m_pprob.name;
}

collection* processor_generic_correlation::get_output_collection()
{
  return m_output_coll.get();
}

generic_plane correlation(const generic_plane& pl1, const generic_plane& p2,  const processor_prob& pprob) {
  std::shared_ptr<processor> p(new processor_generic_correlation(pl1, p2, pprob));
  pl1.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_generic_correlation*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}

_correlation__generic_plane_wraper operator*(const generic_plane& pl, _correlation_)
{
  return _correlation__generic_plane_wraper{ pl };
}

generic_plane operator*(_correlation__generic_plane_wraper&& pl, const generic_plane& p2)
{
  return correlation(pl.pl1, p2);
}

_correlation__generic_plane_wraper operator*(const xy_plane& pl, _correlation_)
{
  return _correlation__generic_plane_wraper{ *pl.get_generic_plane() };
}

generic_plane operator*(_correlation__generic_plane_wraper&& pl, const xy_plane& p2)
{
  return correlation(pl.pl1, *p2.get_generic_plane());
}
