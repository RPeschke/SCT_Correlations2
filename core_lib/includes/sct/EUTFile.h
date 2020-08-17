#ifndef EUTFile_h__
#define EUTFile_h__


namespace sct {
  template <typename T>
  class ref_ptr;
}
#ifndef __CINT__
#include <memory>
#include <vector>
#include "sct/ref_ptr.hh"
#endif


#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "generic_plane.hh"
#include "collection.h"
class TTree;
class TFile;
class ProcessorCollection;
class collection;

class DllExport EUTFile {
public:

  EUTFile(TFile* inputFile, ProcessorCollection* pc=nullptr);
  collection* getCollection(const collectionName_t& name);
  ProcessorCollection* getProcessorCollection();
#ifndef __CINT__
  EUTFile(sct::ref_ptr<TFile> inputFile, sct::ref_ptr<ProcessorCollection> pc);
  EUTFile(sct::ref_ptr<TFile> inputFile);
private:
  TFile *m_inputFile;
  ProcessorCollection* m_pc;
  std::vector<collection*> m_collections;
  std::shared_ptr< ProcessorCollection> m_pc_owned;
#endif

};
class DllExport TSIMFile : public EUTFile {
public:
  TSIMFile(TFile* inputFile, ProcessorCollection* pc = nullptr) : EUTFile (inputFile,pc) {
      
  }
  generic_plane KLM_Digits() {
    return getCollection(collectionName_t("KLM_Digits"))->getPlane(ID_t(0));
  }
  generic_plane KLM_Tracks() {
    return getCollection(collectionName_t("KLM_Tracks"))->getPlane(ID_t(0));
  }
  

};
#endif // EUTFile_h__
