
#include <string>
#include "TFile.h"
#include "TTree.h"

#include "sct/EUTFile.h"
#include "sct/collection.h"
#include "sct/internal/collectionReader_proc.hh"
#include "sct/ProcessorCollection.h"


collection* get_known_collection(const char* name, std::vector<collection*>& collections) {

  std::string name_(name);
  for (auto& e:collections)  {
    if (e->get_name()==name_) {
      return e;
    }

  }
  return nullptr;
}

EUTFile::EUTFile(TFile *inputFile, ProcessorCollection* pc):m_inputFile(inputFile),m_pc(pc){

}

collection* EUTFile::getCollection(const char* name){
  collection* ret = get_known_collection(name, m_collections);
  if (ret){
    return ret;
  }

  auto tree = dynamic_cast<TTree*>(m_inputFile->Get(name));
  if (!tree) {
    return nullptr;
  }

  auto coll_proc = collectionReader_proc::create(tree,m_pc);

  m_collections.push_back(coll_proc->get_collection());

  return coll_proc->get_collection();

}

ProcessorCollection* EUTFile::getProcessorCollection(){
  return m_pc;
}
