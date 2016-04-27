#ifndef lcio_reader_h__
#define lcio_reader_h__
#ifdef USE_LCIO
#ifndef __CINT__
#include <memory>
#include <vector>
#endif
#include "sct/platform.hh"
#include <string>
#include "sct/predef/plane.hh"
#include "sct/internal/strong_types.h"


class ProcessorCollection;
class collection;
class lcio_reader_processor;
class lcio_collection;
namespace IO {
  class LCReader;
}
class DllExport lcio_reader {
public:

  lcio_reader(const std::string& inputFile, ProcessorCollection* pc);
  lcio_reader(const std::string& inputFile);
  ~lcio_reader();
  ProcessorCollection* getProcessorCollection();
  xy_plane getPlane(const collectionName_t& CollectionName, ID_t planeID);
#ifndef __CINT__
  lcio_collection* getCollection(const collectionName_t& name);
private:
  lcio_reader_processor* m_reader_processor = nullptr;
  ProcessorCollection* m_pc;
  std::shared_ptr<ProcessorCollection> m_owned_pc;
  std::vector<collection*> m_collections;
  IO::LCReader* m_reader;
#endif

};
#endif
#endif // lcio_reader_h__
