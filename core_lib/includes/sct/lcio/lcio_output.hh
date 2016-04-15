#ifndef lcio_output_h__
#define lcio_output_h__
#include <string>
#include <vector>
#include "sct/internal/factory.hh"

#define register_lcio_output(classType,className) registerClass(lcio_output,classType,className)

class lcio_collection;


namespace EVENT {
  class LCEvent;
  class LCCollection;
}

class lcio_output_prob {
public:
  lcio_output_prob();
  lcio_output_prob(const std::string& name, const std::string& type, lcio_collection* mcoll);
  lcio_output_prob& setName(const std::string& name);
  lcio_output_prob& setType(const std::string& type);
  lcio_output_prob& set_lcio_collection(lcio_collection* mcoll);
  std::string m_name,m_type;
  lcio_collection* m_coll = nullptr;

};

class lcio_output {
public:
  typedef std::string MainType;
  typedef lcio_output_prob Parameter_t;
  typedef const Parameter_t& Parameter_ref;
  virtual void eventStart(int eventNR);
  virtual void pushEvent(const EVENT::LCEvent* col) = 0;
  virtual void eventEnd();
  lcio_output(Parameter_ref param_);
  virtual ~lcio_output();

  const std::string& get_Name() const;
  const std::string& get_type() const;

protected:
  virtual void newEvent(int eventNR) {}
  virtual void FinnishEvent() {};
  void push_hit(double x, double y, double ID);

  int m_event_nr;
  lcio_output_prob m_prob;
  std::vector<double> *m_x, *m_y, *m_id;
};

std::shared_ptr<lcio_output> create_lcio_ouput(lcio_output::Parameter_ref);

#endif // lcio_output_h__
