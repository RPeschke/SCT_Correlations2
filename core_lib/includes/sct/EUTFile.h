#ifndef EUTFile_h__
#define EUTFile_h__

#ifndef __CINT__
#include <memory>
#include <vector>
#endif
#include "sct/platform.hh"
class TTree;
class TFile;
class ProcessorCollection;
class collection;

class DllExport EUTFile {
public:

  EUTFile(TFile *inputFile, ProcessorCollection* pc);
  collection* getCollection(const char* name);
  ProcessorCollection* getProcessorCollection();
private:
#ifndef __CINT__
  TFile *m_inputFile;
  ProcessorCollection* m_pc;
  std::vector<collection*> m_collections;
#endif

};

#endif // EUTFile_h__
