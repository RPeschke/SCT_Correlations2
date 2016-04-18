#ifndef xml_print_h__
#define xml_print_h__
#include "sct/platform.hh"
#include <string>
#include <ostream>

class DllExport xml_print {

public:
  static void setOutPutStream(std::ostream& out);
  xml_print(const char* name);

  template<typename T>
  xml_print(const char* name, const T& value) :xml_print(name)
  {
    print(value);
    close();
  }

  template <typename T>
  void print(const T& value) {
    if (!do_print()) {
      return;
    }
    if (first_element) {
      out() << std::string(m_pos + 2, ' ') << value << std::endl;
      first_element = false;
    }
    else {
      out() << std::string(m_pos + 2, ' ') << ", " << value << std::endl;
    }
  }
  virtual ~xml_print();
  void close();
private:
  bool do_print();
  std::ostream& out();
  std::string m_name;
  bool end_printed = false, first_element = true;
  int m_pos;
};

#endif // xml_print_h__
