#ifndef processor_2d_h__
#define processor_2d_h__

#include "sct/processor.h"
#include <memory>
#include "sct/processor_prob.hh"

class axis;
class collection;
class xy_plane;
class hit;
class processor_2d :public processor {
public:
  virtual init_returns init();
  virtual end_returns end() ;
  processor_2d(const axis& x_,const axis& y_, processor_prob& pprob);
  virtual process_returns processEvent();
  virtual process_returns processCurrentEvent() = 0;
  void pushHit(double x, double y);
  void pushHit(double x, double y, double ID);
  void pushHit(const hit& hit, double ID);
  virtual process_returns fill();

  collection* get_output_collection();
  virtual std::string get_name() ;
  int getEventNr();
protected:
  int m_current = 0;
  //input
  std::shared_ptr<axis> m_x, m_y;

  //output
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<xy_plane> m_outputPlane;
  hit* m_outhit;
  processor_prob m_prob;
};

#endif // processor_2d_h__
