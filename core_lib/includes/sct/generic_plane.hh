#ifndef plane_h__
#define plane_h__

#include "sct/platform.hh"

#include "sct/axis.hh"


class generic_plane;

#ifndef __CINT__

#include <vector>
#include <string>

class storage{
public:
  storage(std::vector<double>* vec_, const axesName_t& axisName_);
  double* value = nullptr;
  std::vector<double>* vec = nullptr;
  axesName_t axisName;
};

class generic_plane_slice_handler {
public:
  generic_plane* m_plane;
  generic_plane_slice_handler(generic_plane* plane) :m_plane(plane) {}
  void operator = (const cutNote &ax) {
    feet = D.feet;
    inches = D.inches;
  }
};
#endif
#include "sct/internal/strong_types.h"

class cutNote;

class   ProcessorCollection;
class axis;
class TTree;

class DllExport generic_plane{
public:
#ifndef __CINT__
  generic_plane(ID_t planeID, std::vector<double> *ID, ProcessorCollection* pc,TTree* tree);
#endif
  generic_plane(const generic_plane& pl);
  generic_plane& operator=(const generic_plane& pl);
  generic_plane() {}
  void add_axis(const axesName_t& axisName, std::vector<double> *axis_);
  bool setHitAxisAdress(const axesName_t& name, double* outVar);
  bool next();
  void push();
  void push(ID_t planeID);
  axis get_axis(const axesName_t& axisName) const;
  double get_value(const axesName_t& axisName) const;
  ProcessorCollection* get_ProcessorCollection() const;
  TTree* get_tree();
  ID_t get_ID() const;
  
  generic_plane operator[](const cutNote& ax);

  generic_plane operator[](axesName_t ax);
  std::vector<axesName_t> get_axes_names() const;
  void set_name(const  std::string& name);

#ifndef __CINT__
  void clear_event();
  void clear_event(axesName_t ax);

private:
  ProcessorCollection* m_pc = nullptr;
  std::vector<double> *m_id = nullptr;
  std::vector<storage> m_storage;
  std::vector<storage> m_usedstorage;
  ID_t plane_id = ID_t(0);
  int curr = -1;
  TTree* m_tree = nullptr;
#endif // !__CINT__


};

#endif // plane_h__
