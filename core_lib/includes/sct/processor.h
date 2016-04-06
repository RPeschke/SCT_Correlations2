#ifndef processor_h__
#define processor_h__
#include <string>
#include "sct/platform.hh"
class ProcessorCollection;
enum init_returns{
  i_sucess,
  i_error
};
enum process_returns {
  p_sucess,
  p_skip,
  p_stop,
  p_error,
  p_warning,
  p_dont_save_event
};
enum end_returns {
  e_success,
  e_error
};

class DllExport processor {
public:
  virtual init_returns init() =0;
  
  virtual process_returns processEvent() = 0;
  virtual process_returns fill() = 0;
  virtual end_returns end() = 0;
  virtual std::string get_name() = 0;
  
  std::string get_lastError();
  void addError(const std::string& error_discription);
  void resetErrors();
  ProcessorCollection* mpc = nullptr;
private:
  std::string m_errors;
};



#endif // processor_h__
