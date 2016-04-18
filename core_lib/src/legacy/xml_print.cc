#include "sct/legacy/xml_print.hh"
#include <iostream>

#include <ostream>
std::ostream* m_out = &std::cout;

bool gDo_print = false;
int gPos = 0;


void xml_print::setOutPutStream(std::ostream& out)
{
  m_out = &out;
}

xml_print::xml_print(const char* name) :m_name(name), m_pos(gPos)
{
  gPos += 2;
  if (!gDo_print) {
    return;
  }
  *m_out << std::string(m_pos, ' ') << "<" << m_name << ">" << std::endl;
}



xml_print::~xml_print()
{
  if (!end_printed) {
    close();
  }
}

void xml_print::close()
{
  gPos -= 2;
  if (!gDo_print) {
    return;
  }

  *m_out << std::string(m_pos, ' ') << "</" << m_name << ">" << std::endl;
  end_printed = true;
}

bool xml_print::do_print()
{
  return gDo_print;
}

std::ostream& xml_print::out()
{
  return *m_out;
}

