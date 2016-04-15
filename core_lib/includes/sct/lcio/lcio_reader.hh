#ifndef lcio_reader_h__
#define lcio_reader_h__

#ifndef __CINT__
#include <memory>
#include <vector>
#endif
#include "sct/platform.hh"
#include <string>


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
  ~lcio_reader();
  lcio_collection* getCollection(const char* name);
  ProcessorCollection* getProcessorCollection();
private:
#ifndef __CINT__
  lcio_reader_processor* m_reader_processor = nullptr;
  ProcessorCollection* m_pc;
  std::vector<collection*> m_collections;
  IO::LCReader* m_reader;
#endif

};
#endif // lcio_reader_h__
