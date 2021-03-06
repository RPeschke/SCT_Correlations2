#ifndef axCut_h__
#define axCut_h__

#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "cutNote.hh"
#ifndef __CINT__
#include <memory>
#endif // !__CINT__

#include "sct/platform.hh"
#include <vector>
class planeCut;


class DllExport axCut:public cutNote {
public:

  
  axCut();
  axCut(const axCut& rhs);
  axCut(const axesName_t& name);
  virtual bool register_plane(planeCut& pl) __OVERIDE__;
  virtual double get_value() const __OVERIDE__;
  virtual ~axCut() __OVERIDE__;
#ifndef __CINT__
  virtual std::shared_ptr<cutNote> copy() const __OVERIDE__;
private:  
  axesName_t m_name;
  const double * m_hit = nullptr;
 // std::vector<generic_plane *> get_planes() const override;
#endif

  


  


  axesName_t get_name() const ;

};






DllExport axCut x_def();
DllExport axCut y_def();




class DllExport unique_ax :public cutNote {
public:


  unique_ax();
  unique_ax(const unique_ax& rhs);
  unique_ax(const axesName_t& name);
  virtual bool register_plane(planeCut& pl) __OVERIDE__;
  virtual void onNewEvent() __OVERIDE__;
  virtual double get_value() const __OVERIDE__;
  virtual ~unique_ax() __OVERIDE__;
#ifndef __CINT__
  virtual std::shared_ptr<cutNote> copy() const __OVERIDE__;
//  std::vector<generic_plane *> get_planes() const override;
  axesName_t get_name() const __OVERIDE__;
private:
  axesName_t m_name;
  const double * m_hit = nullptr;
  mutable std::vector<double> m_elements;
  
#endif




  




};

#endif // axCut_h__
