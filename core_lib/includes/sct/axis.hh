#ifndef axis_h__
#define axis_h__
#include "sct/platform.hh"
#ifndef __CINT__
#include <vector>
#include <string>
#endif // !__CINT__

#include "sct/internal/strong_types.h"
class ProcessorCollection;
class TTree;
class DllExport axis {
public:
#ifndef __CINT__
  axis(ID_t planeID, std::vector<double> *ID, const axesName_t& axisName, std::vector<double> *axis_, ProcessorCollection* pc, TTree* tree);
  axesName_t getName() const;
#endif // !__CINT__
  axis(const axis& ax);
  axis& operator=(const axis& ax);
  double getValue() const;
  bool next();

  ProcessorCollection* get_ProcessorCollection()const;
  TTree* get_tree() const;
  ID_t get_ID() const;
private:
#ifndef __CINT__
  ProcessorCollection* m_pc = nullptr;
  std::vector<double> *m_id,*m_axis;
  axesName_t m_name;
  ID_t plane_id;
  int curr = -1;
  TTree* m_tree =nullptr;
#endif
};


#endif // axis_h__
