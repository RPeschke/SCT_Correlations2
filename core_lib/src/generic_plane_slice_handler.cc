#include "sct/generic_plane.hh"
#include "sct/axis.hh"
#include "TTree.h"
#include "sct/internal/sct_exceptions.hh"
#include "sct/generic_processors/processor_cut_axis.hh"
#include "sct/generic_processors/planeCut.hh"
#include "sct/platform.hh"
#include "sct/generic_plane_slice_handler.hh"
#include "sct/generic_processors/processor_generic_append_plane.hh"
#include "sct/internal/vector_helpers.hh"

void Draw(const generic_plane_slice_handler& pl)
{
  pl.m_plane->get_tree()->Draw(necessary_CONVERSION(pl.m_name).c_str());
}


void Draw(const generic_plane_slice_handler_multi& pl)
{
  std::string ax = necessary_CONVERSION(pl.m_data[0].m_name) + ":" + necessary_CONVERSION(pl.m_data[1].m_name);
  pl.m_data[0].m_plane->get_tree()->Draw(ax.c_str());
}



void generic_plane_slice_handler::operator=(const cutNote &ax)
{


  auto mm = m_plane->get_name();
  auto prop = saveWithRandomName(processorName_t(necessary_CONVERSION(mm)));
  if (!m_plane->is_saved_to_disk()) {
    prop.dontSave2Disk();
  }
  auto pl = generic_append_plane(*m_plane, m_name, ax, prop);
  *m_plane = pl;
}


void generic_plane_slice_handler::print_ax()
{
  std::cout << necessary_CONVERSION(m_name) << std::endl;
}

generic_plane_slice_handler::generic_plane_slice_handler(axesName_t name, generic_plane* plane) :m_plane(plane), m_name(name)
{
  

}

generic_plane_slice_handler::generic_plane_slice_handler(const char * name, generic_plane* plane) : m_plane(plane), m_name(axesName_t(name))
{
  m_hit = planeCut(*m_plane).getAxis(m_name);
}

bool generic_plane_slice_handler::register_plane(planeCut& pl)
{
  if (*m_plane == pl.m_pl) {
    m_hit = pl.getAxis(m_name);
  }
  
  return true;
}

double generic_plane_slice_handler::get_value() const
{
  return *m_hit;
}

std::shared_ptr<cutNote> generic_plane_slice_handler::copy() const
{
  return _MAKE_SHARED1(generic_plane_slice_handler, *this);
}

std::vector<generic_plane *> generic_plane_slice_handler::get_planes()
{
  return { m_plane };
}

axesName_t generic_plane_slice_handler::get_name() const
{
  return axesName_t(necessary_CONVERSION( m_plane->get_name()) + "_"+ necessary_CONVERSION(m_name));
}
