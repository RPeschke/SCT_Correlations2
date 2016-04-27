#include "sct/internal/sct_exceptions.hh"
#include <iostream>
#include <vector>



namespace sct_corr {

  Exception::Exception(const std::string & msg)
    : m_msg(msg) {
  }


  std::vector<std::string> split(const std::string & str, const std::string & delim) {
    std::string s(str);
    std::vector<std::string> result;
    if (str == "") return result;
    size_t i;
    while ((i = s.find_first_of(delim)) != std::string::npos) {
      result.push_back(s.substr(0, i + 1));
      s = s.substr(i + 1);
    }
    result.push_back(s);
    return result;
  }
  std::string text_formating(const std::string& inString) {
    auto splited = split(inString, " :/\\");
    std::string ret;
    std::string line;
    for (auto& e : splited) {

      if (line.length() + e.length() < 60) {
        line += e;
      } else if (e.length() >= 60) {
        line += e;
      } else {
        ret += line;
        ret += "\n  ";
        line.clear();
        line = e;
      }



    }
    ret += line;
    return ret;
  }

  void Exception::make_text() const {


    m_text = text_formating(m_msg);

    for (auto&e : m_errors) {
      m_text +=  e.to_string();
      m_text +="\n"+ std::string(60, '=');
    }
  }

  const char * Exception::what() const throw() {
    if (m_text.length() == 0) make_text();
    return m_text.c_str();
  }

  Exception::~Exception() throw() {

  }


  void Exception::addLocation(const std::string & file /*= ""*/, unsigned line /*= 0*/, const std::string & func /*= ""*/, const std::string & shortfunc /*= ""*/) const {
    m_errors.push_back(errors_container(file, line, func,shortfunc));
  }
  bool gStatusErrorPrinting = true;
  void disableErrorPrinting() {
    gStatusErrorPrinting = false;
  }

  void enableErrorPrinting() {
    gStatusErrorPrinting = true;
  }

  bool getStatusErrorPrinting() {
    return gStatusErrorPrinting;
  }


  void PrintException(const std::string& Exception__, const std::string & exec, const std::string & file, int line, const std::string func, const std::string shortfunc) {
    if (getStatusErrorPrinting()) {
      std::string ret;
      if (!Exception__.empty()) {
        ret += "exception: " + text_formating(Exception__);
      }
      if (!exec.empty()){
        ret += "\n Message: " + text_formating(exec);
      }
      if (!file.empty()) {
        ret += "\n\n  From :\n" + text_formating(file);
        if (line > 0) {
          ret += ":" + std::to_string(line);
        }
      }
      if (shortfunc.length() > 0) ret += "\n\n  In: \n" + text_formating(shortfunc);
      if (func.length() > 0) ret += "\n\n  LongName: \n" + text_formating(func);
      ret += "\n" + std::string(60, '=');
      std::cout << ret << std::endl;
    }
  }

  int handleExceptions() {
    try {
      throw;
    } catch (const Exception&e) {
      std::cerr << "Uncaught exception:\n" + std::string(e.what()) << std::endl;
      return 1;

    } catch (const std::exception & e) {
      std::cerr << "Uncaught exception:\n" + std::string(e.what()) << std::endl;
      return 1;
    } catch (...) {
      std::cerr << "Unknown exception:\n";
      return 1;
    }
    return 0;
  }


  errors_container::errors_container(const std::string & file, int line /*= 0*/, const std::string func /*= ""*/, const std::string & shortfunc /*= ""*/) : m_file(file), m_line(line), m_func(func),m_shortName(shortfunc)  {
    

  }

  std::string errors_container::to_string() const {
    std::string ret;
    if (m_file.length() > 0) {
      ret += "\n\n  From :\n" + text_formating(m_file);
      if (m_line > 0) {
        ret += ":" + std::to_string(m_line);
      }
    }
    if (m_shortName.length() > 0) ret += "\n\n  In: \n" + text_formating(m_shortName);
    if (m_func.length() > 0) ret += "\n\n  LongName: \n" + text_formating(m_func);
    
    return ret;
  }

  ScopteDisableErrorPrinting::ScopteDisableErrorPrinting():m_old_sataus(getStatusErrorPrinting()) {
    disableErrorPrinting();
  }

  ScopteDisableErrorPrinting::~ScopteDisableErrorPrinting() {

    if (m_old_sataus) {
      enableErrorPrinting();
    } else {
      disableErrorPrinting();
    }

  }

}
