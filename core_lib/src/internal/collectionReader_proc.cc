#include "sct/internal/collectionReader_proc.hh"
#include "TTree.h"
#include "sct/ProcessorCollection.h"



collectionReader_proc::collectionReader_proc(TTree* tree, ProcessorCollection* pc) : m_tree(tree), m_collection(tree, pc) {
  mpc = pc;

}

collectionReader_proc::collectionReader_proc(const collectionReader_proc& coll) : m_tree(coll.m_tree), m_collection(coll.m_collection), m_eventNr(coll.m_eventNr), m_max_entries(coll.m_max_entries) {

}

collectionReader_proc& collectionReader_proc::operator=(const collectionReader_proc& coll)
{
  m_tree = coll.m_tree;
  m_collection = coll.m_collection;
  m_eventNr = coll.m_eventNr;
  m_max_entries = coll.m_max_entries;
  
  return *this;
}

init_returns collectionReader_proc::init() {
  m_eventNr = 0;
  m_max_entries = m_collection.get_tree()->GetEntries();
  
  return init_returns::i_sucess;
}

process_returns collectionReader_proc::processEvent() {
  if (++m_eventNr < m_max_entries) {
    m_tree->GetEntry(m_eventNr);
#ifdef _DEBUG
    m_collection.load();
#endif
    return process_returns::p_sucess;
  }
  return process_returns::p_stop;
}

process_returns collectionReader_proc::fill() {

  return process_returns::p_sucess; // only reading in. nothing to do.
}

end_returns collectionReader_proc::end() {
  return end_returns::e_success;
}

std::string collectionReader_proc::get_name() {
  return m_tree->GetName();
}



collection* collectionReader_proc::get_collection() {
  return &m_collection;
}

std::shared_ptr<collectionReader_proc> collectionReader_proc::create(TTree* tree, ProcessorCollection* pc) {
  auto ret = std::shared_ptr<collectionReader_proc>(new collectionReader_proc(tree, pc));
  pc->addProcessor(ret);

  return ret;
}
