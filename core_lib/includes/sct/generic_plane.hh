#ifndef plane_h__
#define plane_h__

#include "sct/platform.hh"

#include "sct/axis.hh"


class generic_plane;
class cutNote;
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
#endif

class generic_plane_slice_handler;
class DllExport generic_plane_slice_handler {
public:
  generic_plane* m_plane;
  axesName_t m_name;
  generic_plane_slice_handler(axesName_t name, generic_plane* plane);
  void  operator= (const cutNote &ax);
};
#include "sct/internal/strong_types.h"



class   ProcessorCollection;
class axis;
class TTree;

class DllExport generic_plane{
public:
#ifndef __CINT__
  generic_plane(ID_t planeID, std::vector<double> *ID, ProcessorCollection* pc,TTree* tree, collectionName_t collectionName );
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

  std::vector<axesName_t> get_axes_names() const;
  void set_name(const  std::string& name);
  collectionName_t get_name() const;
#ifndef __CINT__
  generic_plane_slice_handler operator[](axesName_t ax);
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
  collectionName_t m_collectionName = collectionName_t("");
#endif // !__CINT__


};

#endif // plane_h__
