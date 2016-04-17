#ifndef collectionReader_proc_h__
#define collectionReader_proc_h__

#ifndef __CINT__
#include <memory>
#include "sct/collection.h"
#endif // !__CINT__

#include "sct/processor.h"


class TTree;
class collection;
class collectionReader_proc : public processor{
  
public:
  collectionReader_proc(const collectionReader_proc& coll);
  collectionReader_proc& operator=(const collectionReader_proc& coll);
  virtual init_returns init() override;
  virtual process_returns processEvent() override;
  virtual process_returns fill() override;
  virtual end_returns end() override;
  virtual processorName_t get_name() override;


  collection* get_collection();
  static std::shared_ptr<collectionReader_proc> create(TTree* tree, ProcessorCollection* pc);
private:
  collectionReader_proc(TTree* tree,ProcessorCollection* pc);
  int m_eventNr = 0,m_max_entries=0;
  TTree* m_tree;
#ifndef __CINT__
  collection m_collection;
#endif
};




#endif // collectionReader_proc_h__
