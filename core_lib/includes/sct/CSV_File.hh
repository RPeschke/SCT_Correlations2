#ifndef CSV_File_h__
#define CSV_File_h__




namespace sct {
  template <typename T>
  class ref_ptr;
}
#ifndef __CINT__
#include <memory>
#include <vector>
#include "sct/ref_ptr.hh"
#include <iostream>

#endif


#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "generic_plane.hh"
#include "collection.h"

class ProcessorCollection;
class collection;

class DllExport CSV_File {
public:

  CSV_File(std::string FileName, ProcessorCollection* pc=nullptr);
  collection* getCollection();
  ProcessorCollection* getProcessorCollection();

#ifndef __CINT__
  CSV_File(std::string FileName, sct::ref_ptr<ProcessorCollection> pc);
private:

  std::string m_FileName;
  
  ProcessorCollection* m_pc;
  collection* m_collection;
  std::shared_ptr< ProcessorCollection> m_pc_owned;
#endif

};

#endif 