#ifndef plane_h__
#define plane_h__

#include "sct/platform.hh"

#include "sct/axis.hh"

#ifndef __CINT__

#include <vector>
#include <string>

class storage{
public:
  storage(std::vector<double>* vec_, const std::string& axisName_);
  double* value = nullptr;
  std::vector<double>* vec = nullptr;
  std::string axisName;
};
#endif


class   ProcessorCollection;
class axis;
class TTree;

class DllExport generic_plane{
public:
#ifndef __CINT__
  generic_plane(double planeID, std::vector<double> *ID, ProcessorCollection* pc,TTree* tree);
#endif
  generic_plane(const generic_plane& pl);
  generic_plane& operator=(const generic_plane& pl);
  generic_plane() {}
  void add_axis(const std::string& axisName, std::vector<double> *axis_);
  bool setHitAxisAdress(const std::string& name, double* outVar);
  bool next();
  void push();
  void push(double planeID);
  axis get_axis(const std::string& axisName) const;
  ProcessorCollection* get_ProcessorCollection() const;
  TTree* get_tree();
  double get_ID() const;
private:

#ifndef __CINT__
  ProcessorCollection* m_pc = nullptr;
  std::vector<double> *m_id = nullptr;
  std::vector<storage> m_storage;
  std::vector<storage> m_usedstorage;
  double plane_id;
  int curr = -1;
  TTree* m_tree = nullptr;
#endif // !__CINT__


};

#endif // plane_h__
