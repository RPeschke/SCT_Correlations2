#ifndef processorPlaneVSPlane_h__
#define processorPlaneVSPlane_h__
#include "sct/processor.h"
#include "sct/predef/hit.hh"
#include "sct/predef/plane.hh"
#include "sct/collection.h"
#include "sct/processor_prob.hh"



class DllExport processorPlaneVSPlane:public processor {
public:

  processorPlaneVSPlane(const xy_plane & plane_A, const  xy_plane& plane_b, processor_prob& plot_prob);

  virtual init_returns init() ;
  virtual process_returns processEvent() ;
  virtual process_returns fill() ;
  virtual end_returns end();
  
  virtual std::string get_name();

  virtual void processEventStart() {}
  virtual void processHit(const hit&  p1, const hit&  p2) {};
  virtual void processHit_1(const hit&  p1) {}
  virtual void processHit_2(const hit&  p2) {}
  virtual process_returns processEventEnd();

  void pushHit(double x, double y, double ID=0);
  void pushHit(const hit& hit, double ID);
  int m_size_x = 0, m_size_y = 0;
  int m_current = 0;
  collection* get_output_collection();
private:  
#ifndef __CINT__
// storage
  processor_prob m_plot_prob;

//input 

  hit* m_inputHit_A=nullptr, *m_inputHit_B = nullptr;
  xy_plane m_input_plane_A, m_input_plane_B;
//output
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<xy_plane> m_outputPlane;
  hit* m_outhit;

#endif // !__CINT__
};




#endif // processorPlaneVSPlane_h__
