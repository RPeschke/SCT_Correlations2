#include <iostream>
#include "sct/lcio/lcio_output.hh"



class LCGenericObject_output : public lcio_output{
public:
  typedef const void* data_t;
  static const char* TypeName(){
    return "LCGenericObject";
  }
  LCGenericObject_output(Parameter_ref param) :lcio_output(param) {}

  virtual void pushEvent(const EVENT::LCEvent* col) override{
    if (warning)
    {
      std::cout << "not implemented type: " << TypeName() << std::endl;
      warning = false;
    }
  };
  
  bool warning = true;
};


register_lcio_output(LCGenericObject_output, "LCGenericObject");