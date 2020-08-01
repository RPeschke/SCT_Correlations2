
#include <string>
#include "TFile.h"
#include "TTree.h"

#include "sct/EUTFile.h"
#include "sct/collection.h"
#include "sct/internal/collectionReader_proc.hh"
#include "sct/ProcessorCollection.h"
#include "sct/internal/strong_types.h"
#include "sct/internal/sct_exceptions.hh"
#include "sct/ref_ptr.hh"

collection* get_known_collection(const collectionName_t& name, std::vector<collection*>& collections) {

  
  for (auto& e:collections)  {
    if (e->get_name()==name) {
      return e;
    }

  }
  return nullptr;
}

EUTFile::EUTFile(sct::ref_ptr<TFile> inputFile, sct::ref_ptr<ProcessorCollection> pc):m_inputFile(inputFile.get()),m_pc(pc.get()){

}


EUTFile::EUTFile(sct::ref_ptr<TFile> inputFile) : m_inputFile(inputFile.get()) {
  
  m_pc_owned = Snew ProcessorCollection();
  m_pc = m_pc_owned.get();

}

collection* EUTFile::getCollection(const collectionName_t&  name){
  collection* ret = get_known_collection(name, m_collections);
  if (ret){
    return ret;
  }

  auto tree = dynamic_cast<TTree*>(m_inputFile->Get(necessary_CONVERSION(name).c_str()));
  if (!tree) {
    SCT_THROW("unknown collection: <" + necessary_CONVERSION(name) + ">");
  }

  auto coll_proc = collectionReader_proc::create(tree,m_pc);

  m_collections.push_back(coll_proc->get_collection());

  return coll_proc->get_collection();

}

ProcessorCollection* EUTFile::getProcessorCollection(){
  return m_pc;
}
