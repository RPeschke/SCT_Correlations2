#include "sct/generic_processors/processor_generic_extend_base.hh"
#include "sct/processor.h"
#include "sct/generic_plane.hh"
#include "sct/processor_prob.hh"
#include "sct/ProcessorCollection.h"
#include "sct/internal/sct_exceptions.hh"

processor_generic_extend_base::processor_generic_extend_base(const generic_plane& pl, const processor_prob& pprob)
  :m_plane1(pl),
  m_pprob(pprob)
{


  auto p = std::shared_ptr<processor>(this);
  pl.get_ProcessorCollection()->addProcessor(p);

}


bool contains_element123(std::vector<axesName_t> const& items, axesName_t const& item)
{
  return std::find(items.begin(), items.end(), item) != items.end();
}

init_returns processor_generic_extend_base::init()
{


  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}


process_returns processor_generic_extend_base::fill()
{
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_generic_extend_base::end()
{
  return e_success;
}

processorName_t processor_generic_extend_base::get_name()
{
  return m_pprob.name;
}

collection* processor_generic_extend_base::get_output_collection()
{
  return m_output_coll.get();
}


void processor_generic_extend_base::add_axis(const axesName_t& name, double* ax){
  m_external_connections[name] = ax;
}

void processor_generic_extend_base::get_axis(const axesName_t& name, double* ax)
{
  if (!contains_element123(m_plane1.get_axes_names(), name)) {
    SCT_THROW("axis not found");
  }
  m_external_connections[name] = ax;
}

bool processor_generic_extend_base::next()
{
  return m_plane1.next();
}

void processor_generic_extend_base::push()
{
  m_outputPlane->push();
}

void processor_generic_extend_base::clear()
{
  m_output_coll->clear_event();
}

void processor_generic_extend_base::Finish_constructing()
{
  if (!m_output_coll) {
    std::vector<axesName_t> outNames;
    for (auto &e : m_plane1.get_axes_names()) {
      outNames.push_back(e);
    }
    for (auto& e : m_external_connections) {
      if (!contains_element123(outNames, e.first)) {
        outNames.push_back(e.first);
        m_appended_axis.push_back(e.first);
      }
    }

    m_pprob.setProcessorCollection(m_plane1.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));
    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));


    for (auto& e : m_appended_axis) {
      m_outputPlane->setHitAxisAdress(e, m_external_connections[e]);
    }

    for (auto & e : m_plane1.get_axes_names()) {
      auto ex_pointer = m_external_connections[e];
      if (ex_pointer) {

        m_plane1.setHitAxisAdress(e, ex_pointer);
        m_outputPlane->setHitAxisAdress(e, ex_pointer);

      }
      else {
        m_internal_connections[e] = Snew double();
        m_plane1.setHitAxisAdress(e, m_internal_connections[e].get());
        m_outputPlane->setHitAxisAdress(e, m_internal_connections[e].get());
      }
    }

  }
}
