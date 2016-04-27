#ifndef sct_exceptions_h__
#define sct_exceptions_h__
#include <exception>
#include <string>
#include "sct/platform.hh"
#include <iostream>
#include <vector>


#ifndef SCT_FUNC
  #define SCT_FUNC ""
#endif
#ifndef SCT_FUNC_SHORT
  #define SCT_FUNC_SHORT   "" 
#endif // !SCT_FUNC_SHORT

#define SCT_THROWX(exc, msg) throw ::sct_corr::InitException(exc(msg), __FILE__, __LINE__, SCT_FUNC,SCT_FUNC_SHORT)

#define SCT_THROW(msg) SCT_THROWX(::sct_corr::Exception, (msg))


#define ADD_LOCATION(e) e.addLocation( __FILE__, __LINE__, SCT_FUNC,SCT_FUNC_SHORT)

#define SCT_EXCEPTIONX(name, base) \
  class name : public base {         \
    public:                            \
   name(const std::string & msg)      \
    : base(msg) {}                   \
}

#define SCT_EXCEPTION(name) SCT_EXCEPTIONX(name, ::sct_corr::Exception)

namespace sct_corr {
  class errors_container {
  public:
    errors_container(const std::string & file, int line = 0, const std::string func = "", const std::string & shortfunc = "");
    std::string to_string() const;
  private:
    std::string m_file, m_func,m_shortName;
    unsigned m_line;
  };
  class DllExport Exception : public std::exception {
  public:
    Exception(const std::string & msg);
    virtual const char * what() const throw()  override;
    virtual ~Exception() throw();
    // This shouldn't really be const, but it must be callable on temporary objects...
    void addLocation(const std::string & file = "", unsigned line = 0, const std::string & func = "", const std::string & shortfunc = "") const;
  protected:
    std::string m_msg;
  private:

    mutable std::string m_text;
    void make_text() const;
    mutable std::vector<errors_container> m_errors;
  };




  template <typename T>
  const T & InitException(const T & e, const std::string & file, int line , const std::string func , const std::string shortfunc ) {
    e.addLocation(file, line, func, shortfunc);
    return e;
  }

  // Some useful predefined exceptions
  SCT_EXCEPTION(CollectionNotFound);

  DllExport int handleExceptions();
}
#endif // sct_exceptions_h__
