#ifndef planes_h__
#define planes_h__
#include "sct/generic_plane.hh"
#include "sct/predef/hit.hh"
#include "sct/platform.hh"
#include "sct/generic_processors/cutNote.hh"

#ifndef __CINT__
#include <memory>
#endif // !__CINT__
#include <vector>
#include <string>

DllExport std::vector<axesName_t> xy_names();

class DllExport plane {
public:
  plane(const generic_plane& pl);
  plane();
  plane(const plane& rhs);
  plane& operator=(const plane& rhs);
  virtual hit* get_hit() = 0;
  bool next();
  ProcessorCollection* get_ProcessorCollection() const;
  const generic_plane* get_generic_plane() const;
  generic_plane* get_generic_plane();
protected:
  generic_plane m_plane;
};

class DllExport xy_plane :public plane {
public:
  xy_plane(const generic_plane& pl);
  xy_plane();
  xy_plane(const xy_plane& rhs);
  xy_plane& operator=(const xy_plane& rhs);
  xy_plane operator[](const cutNote& ax);
  virtual hit* get_hit();
  axis get_x() const;
  axis get_y() const;
  axis get_z() const;
  void set_name(const  std::string& name);
private:
#ifndef __CINT__
  std::shared_ptr<hit> Hit = std::make_shared<hit>();
#endif
};






class DllExport FitterPlane :public xy_plane {
public:
  FitterPlane(const generic_plane& pl);
  FitterPlane();
  FitterPlane(const FitterPlane& rhs);
  FitterPlane& operator=(const FitterPlane& rhs);
  virtual hit* get_hit();
  fitterHit* get_fitterHit();
private:
#ifndef __CINT__
  std::shared_ptr<fitterHit> F_Hit = std::make_shared<fitterHit>();
#endif
};


#endif // planes_h__
