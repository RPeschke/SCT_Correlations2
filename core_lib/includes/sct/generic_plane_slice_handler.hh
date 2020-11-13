#ifndef generic_plane_slice_handler_h__
#define generic_plane_slice_handler_h__


#include "sct/internal/strong_types.h"
#include "generic_processors/cutNote.hh"


class generic_plane_slice_handler;
class generic_plane;
class cutNote;

class generic_plane_slice_handler_multi {
public:

  std::vector<generic_plane_slice_handler> m_data;
  generic_plane_slice_handler_multi operator&(const generic_plane_slice_handler& rhs) {
    generic_plane_slice_handler_multi ret;
    ret.m_data = m_data;
    ret.m_data.push_back(rhs);
    return ret;
  }
};

DllExport void Draw(const generic_plane_slice_handler_multi& pl);

class DllExport generic_plane_slice_handler: public cutNote {
public:

  generic_plane* m_plane;
  axesName_t m_name;
  void print_ax();
  generic_plane_slice_handler(axesName_t name, generic_plane* plane);
  generic_plane_slice_handler(const char * name, generic_plane* plane);
  void  operator= (const cutNote &ax);
  generic_plane_slice_handler_multi operator&(const generic_plane_slice_handler& rhs) {
    generic_plane_slice_handler_multi ret;
    ret.m_data.push_back(*this);
    ret.m_data.push_back(rhs);
    return ret;
  }



  bool register_plane(planeCut& pl) ;


  double get_value() const ;


  std::shared_ptr<cutNote> copy() const ;

private:
  const double * m_hit = nullptr;
};


DllExport void Draw(const generic_plane_slice_handler& pl);
#endif // generic_plane_slice_handler_h__
