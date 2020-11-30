#include "sct/CSV_File.hh"
#include "sct/EUTFile.h"
#include "sct/collection.h"
#include "sct/internal/collectionReader_proc.hh"
#include "sct/ProcessorCollection.h"
#include "sct/internal/strong_types.h"
#include "sct/internal/sct_exceptions.hh"
#include "sct/ref_ptr.hh"

#include <fstream>


#include "sct/processor.h"
#include "sct/processor_prob.hh"
#include <map>


class to_double_t {
public:
  to_double_t(const std::string & in) : d(std::stod(in)) {
   
  }
  operator double() const {
    return d;
  }
  double d;
};
template <typename T>
std::vector<T> split_t(const std::string& headerstr, const std::string delim = ";") {
  std::string s(headerstr);
  s.erase(s.find_last_not_of(" \n\r\t") + 1);
  std::vector<T> result;
  if (s == "") return result;
  size_t i;
  while ((i = s.find_first_of(delim)) != std::string::npos) {
    auto start_index = s.find_first_not_of(' ');
    result.push_back(T(s.substr(start_index, i - start_index)));
    s = s.substr(i + 1);
  }
  auto start_index = s.find_first_not_of(' ');
  result.push_back(T(s.substr(start_index) ));
  return result;
}

class TTree;
class collection;
class CSV_reader_proc : public processor {

public:  virtual init_returns init() override;
  virtual process_returns processEvent() override;
  virtual process_returns fill() override;
  virtual end_returns end() override;
  virtual processorName_t get_name() override;


  collection* get_collection();


  CSV_reader_proc(std::string FileName,const processor_prob& pprob);
  int m_eventNr = 0, m_max_entries = 0;
  std::string m_FileName;
  processor_prob m_pprob;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  std::shared_ptr<std::ifstream> m_in;
  std::string buffer;
  std::vector<std::shared_ptr<double>> m_p1;
  std::string m_delim;
};

init_returns CSV_reader_proc::init()
{
  m_eventNr = 0;
  m_in = Snew std::ifstream(m_FileName);
  if (!getline(*m_in, buffer)) {
    return i_error;
  }
  return i_sucess;
}

process_returns CSV_reader_proc::processEvent()
{
  ++m_eventNr;
  m_output_coll->clear_event();
  if (!getline(*m_in, buffer)) {
    return p_stop;
  }
  auto xs = split_t<to_double_t>(buffer, m_delim);
  if (xs.size() != m_p1.size()) {
    return p_stop;
  }

  int i = 0;
  for (const auto& x : xs) {
    *m_p1[i] = x;
    ++i;
  }
  m_outputPlane->push(ID_t(0));
  return p_sucess;
}

process_returns CSV_reader_proc::fill()
{

    m_output_coll->set_Event_Nr(m_eventNr);
    m_output_coll->save();
    return p_sucess;

}

end_returns CSV_reader_proc::end()
{
  return e_success;
}

processorName_t CSV_reader_proc::get_name()
{
  return m_pprob.name;
}

collection* CSV_reader_proc::get_collection()
{
  return m_output_coll.get();
}



CSV_reader_proc::CSV_reader_proc(std::string FileName, const processor_prob& pprob ) :m_FileName(std::move(FileName)), m_pprob(pprob){

  m_in = Snew std::ifstream(m_FileName);
  if (!getline(*m_in, buffer)) {
    SCT_THROW("file Empty");
  }
  m_delim = ";";
  if (buffer.find(",") != std::string::npos) {
    m_delim = ",";
  }
  auto names = split_t<axesName_t>(buffer, m_delim);
  
  m_pprob.setAxis(names);
  m_pprob.addAxis(axesName_t("ID"));
  m_output_coll = Snew collection(m_pprob);

  m_outputPlane =Snew generic_plane(m_output_coll->getPlane(ID_t(0)));
  for (auto & e : names) {
    auto d = Snew double();

    m_p1.push_back(d);
    m_outputPlane->setHitAxisAdress(e, d.get());

  }
  
}








class CSV_reader_config_file_proc : public CSV_reader_proc {

public: 
        virtual init_returns init() override;
         virtual process_returns processEvent() override;


         CSV_reader_config_file_proc(std::string FileName, const processor_prob& pprob);

};


init_returns CSV_reader_config_file_proc::init()
{
  m_output_coll->clear_event();
  while (getline(*m_in, buffer)) {
    auto xs = split_t<to_double_t>(buffer, m_delim);
    if (xs.size() != m_p1.size()) {
      return i_sucess;
    }

    int i = 0;
    for (const auto& x : xs) {
      *m_p1[i] = x;
      ++i;
    }
    m_outputPlane->push(ID_t(0));
  }
  return i_sucess;
}

process_returns CSV_reader_config_file_proc::processEvent()
{
  ++m_eventNr;
  return p_sucess;
}

CSV_reader_config_file_proc::CSV_reader_config_file_proc(std::string FileName, const processor_prob& pprob):CSV_reader_proc(std::move(FileName), pprob)
{

}

CSV_File::CSV_File(std::string FileName, ProcessorCollection* pc/*=nullptr*/, std::string option) :m_FileName(std::move(FileName))
{
  if (!pc) {
    m_pc_owned = Snew ProcessorCollection();
    m_pc = m_pc_owned.get();
  } else {
    m_pc = pc;
  }
  processor_prob m_pprob;
  m_pprob.setProcessorCollection(m_pc);
  if (option == "configFile") {
    auto pr = Snew CSV_reader_config_file_proc(m_FileName, m_pprob);
    m_pc->addProcessor(pr);
    m_collection = pr->get_collection();
  } else {
    auto pr = Snew CSV_reader_proc(m_FileName, m_pprob);
    m_pc->addProcessor(pr);
    m_collection = pr->get_collection();
  }
  
}

collection* CSV_File::getCollection(){
  return m_collection;
  
}


generic_plane CSV_File::get_plane()
{
  return getCollection()->getPlane(ID_t(0));
}

ProcessorCollection* CSV_File::getProcessorCollection()
{
  return m_pc;
}
