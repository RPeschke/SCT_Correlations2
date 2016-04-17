#include "sct/processor.h"

std::string processor::get_lastError(){
  auto dummy = "<errorList>\n" + m_errors + "\n</errorList>\n";
  resetErrors();
  return dummy;
}

void processor::addError(const std::string& error_discription){
  m_errors += "<error processorName=\"" + necessary_CONVERSION(get_name()) + "\">\n" + error_discription + "\n</error>\n";
}

void processor::resetErrors(){
  m_errors.clear();
}
