#include "sct/lcio/lcio_reader.hh"
#include <iostream>
#ifdef USE_LCIO
#include "lcio.h"
#include "IO/LCReader.h"
#include "IMPL/LCTOOLS.h"
#include "EVENT/LCRunHeader.h" 
#include "EVENT/SimCalorimeterHit.h" 
#include "EVENT/CalorimeterHit.h" 
#include "EVENT/RawCalorimeterHit.h" 


#include "UTIL/CellIDDecoder.h"





#include "sct/processor.h"
#include "sct/ProcessorCollection.h"
#include "sct/lcio/lcio_collection.hh"
#include "EVENT/LCEvent.h"
#include "sct/lcio/lcio_output.hh"
#include <algorithm>





class lcio_reader_processor : public  processor {
public:
  lcio_reader_processor(const std::string& reader_name, ProcessorCollection * pc);
  ~lcio_reader_processor();
  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;
  void pushMissingOutputCollection(LCEvent* evt);
  IO::LCReader* m_reader = nullptr;
  std::string m_name;

  std::vector<std::shared_ptr<lcio_collection>> m_requested_collections;
  lcio_collection* get_collection(const collectionName_t& name);
  std::vector<std::string> m_missingCollection;


  bool m_requested_collections_found = false;
  std::vector<std::shared_ptr<lcio_output>> m_out;
  int m_eventNR =0;
};

lcio_reader_processor::lcio_reader_processor(const std::string& reader_name, ProcessorCollection * pc) :m_name(reader_name)
{
  mpc = pc;
}

lcio_reader_processor::~lcio_reader_processor() {
  if (m_reader) {
    m_reader->close();
    delete m_reader;
  }
}

init_returns lcio_reader_processor::init() {
  m_out.clear();
  m_requested_collections_found = false;
  for (auto&e : m_requested_collections)
  {
    m_missingCollection.push_back(necessary_CONVERSION(e->m_name));
  }
  if (m_reader) {
    m_reader->close();
    delete m_reader;
  }

  m_reader = LCFactory::getInstance()->createLCReader();
  m_reader->open(m_name);

  return i_sucess;
}


template<typename T1, typename T2>
bool contains(const T1& t1, const T2& t2) {
  return std::find(t1.begin(), t1.end(), t2) != t1.end();
}

void remove_element(std::vector<std::string>& vec, const std::string& name) {
  vec.erase(std::remove(vec.begin(), vec.end(), name), vec.end());
}

void lcio_reader_processor::pushMissingOutputCollection(LCEvent* evt) {
  if (m_requested_collections_found == true) {
    return;
  }
  const std::vector<std::string>*  names = evt->getCollectionNames();

  for (auto&e : *names) {
    if (contains(m_missingCollection, e)) {


      m_out.push_back(create_lcio_ouput(lcio_output_prob().setName(e).setType(evt->getCollection(e)->getTypeName()).set_lcio_collection(get_collection(collectionName_t(e)))));

      remove_element(m_missingCollection, e);
    }

  }
  if (m_missingCollection.empty()) {
    m_requested_collections_found = true;
  }

}

lcio_collection* lcio_reader_processor::get_collection(const collectionName_t& name)
{
  for (auto&e : m_requested_collections) {
    if (e->m_name == name) {
      return e.get();
    }
  }

  return nullptr;
}
bool isEndOfRunEvent(LCEvent* evt) {
  return evt->getDetectorName().find("kEORE") != std::string::npos;
}
process_returns lcio_reader_processor::processEvent() {
    auto evt = m_reader->readNextEvent();
    if (!evt) {
      return p_stop;
    }
    if (isEndOfRunEvent(evt)){
      return p_stop;
    }
    pushMissingOutputCollection(evt);
    for (auto&e : m_out) {
      e->eventStart(evt->getEventNumber());
      e->pushEvent(evt);
      e->eventEnd();
    }
    return p_sucess;
}

process_returns lcio_reader_processor::fill() {
  return p_sucess;
}

end_returns lcio_reader_processor::end()
{
  if (m_reader) {
    m_reader->close();
    delete m_reader;
  }
  return e_success;
}

processorName_t lcio_reader_processor::get_name()
{
  return processorName_t("lcio_reder");
}








lcio_reader::lcio_reader(const std::string& inputFile, ProcessorCollection* pc) :m_pc(pc)
{
  auto ret = std::shared_ptr<lcio_reader_processor>(new lcio_reader_processor(inputFile, m_pc));
  m_pc->addProcessor(ret);

  m_reader_processor = ret.get();


}

lcio_reader::lcio_reader(const std::string& inputFile)
{

  m_owned_pc = _MAKE_SHARED0(ProcessorCollection);
  m_pc = m_owned_pc.get();
  auto ret = std::shared_ptr<lcio_reader_processor>(new lcio_reader_processor(inputFile, m_pc));
  m_pc->addProcessor(ret);

  m_reader_processor = ret.get();
}

lcio_reader::~lcio_reader() {

}

lcio_collection* lcio_reader::getCollection(const collectionName_t& name) {

  auto ret = m_reader_processor->get_collection(name);
  if (ret) {
    return ret;
  }

  m_reader_processor->m_requested_collections.push_back( _MAKE_SHARED1(lcio_collection,name, m_pc));

  return  m_reader_processor->get_collection(name);
}

ProcessorCollection* lcio_reader::getProcessorCollection()
{
  return m_pc;
}

xy_plane lcio_reader::getPlane(const collectionName_t& CollectionName, ID_t planeID)
{
  return xy_plane(getCollection(CollectionName)->getPlane(planeID));
}
#else




lcio_reader::lcio_reader(const std::string& inputFile, ProcessorCollection* pc) :lcio_reader(inputFile)
{

}

lcio_reader::lcio_reader(const std::string& inputFile)
{

  std::cout << "LCIO reader not supported " << std::endl;
}

lcio_reader::~lcio_reader() {

}

lcio_collection* lcio_reader::getCollection(const collectionName_t& name) {
  return nullptr;

}

ProcessorCollection* lcio_reader::getProcessorCollection()
{
  return nullptr;
}

xy_plane lcio_reader::getPlane(const collectionName_t& CollectionName, int planeID)
{
  return xy_plane();
}

#endif // USE_LCIO
