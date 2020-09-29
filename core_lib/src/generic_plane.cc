#include "sct/generic_plane.hh"
#include "sct/axis.hh"
#include "TTree.h"
#include "sct/internal/sct_exceptions.hh"
#include "sct/generic_processors/processor_cut_axis.hh"
double zero = 0;


std::vector<double> *getAxisByName(const axesName_t& name,const std::vector<storage>& data) {
  for (auto&e : data) {
    if (e.axisName == name) {
      return e.vec;
    }
  }
  return nullptr;
}

void Draw(const generic_plane_slice_handler& pl)
{
  pl.m_plane->get_tree()->Draw(necessary_CONVERSION(pl.m_name).c_str());
}


void Draw(const generic_plane_slice_handler_multi& pl)
{
  std::string ax = necessary_CONVERSION(pl.m_data[0].m_name) +":" + necessary_CONVERSION(pl.m_data[1].m_name);
  pl.m_data[0].m_plane->get_tree()->Draw(ax.c_str());
}

generic_plane::generic_plane(ID_t planeID, std::vector<double> *ID, ProcessorCollection*pc, TTree* tree, collectionName_t collectionName):plane_id(planeID),m_id(ID),m_pc(pc),m_tree(tree), m_collectionName(collectionName){
 
}

generic_plane::generic_plane(const generic_plane& pl): m_pc(pl.m_pc), m_id(pl.m_id), m_storage(pl.m_storage), plane_id(pl.plane_id),m_tree(pl.m_tree), m_collectionName(pl.m_collectionName) {
  for (auto&e:m_storage){
    e.value = &zero;
  }
 
}

generic_plane& generic_plane::operator=(const generic_plane& pl)  {
  m_pc = pl.m_pc;
  m_id = pl.m_id;
  m_storage = pl.m_storage;
  plane_id = pl.plane_id;
  m_tree = pl.m_tree;
  m_collectionName = pl.m_collectionName;
  for (auto&e : m_storage) {
    e.value = &zero;
  }

  return *this;
}
generic_plane generic_plane::operator[](const cutNote& ax) {
  return cut_op(*this, ax);
}


generic_plane_slice_handler generic_plane::operator[](axesName_t ax)
{
  return generic_plane_slice_handler(ax, this);
}

void generic_plane::add_axis(const axesName_t& axisName, std::vector<double> *axis_) {

  m_storage.push_back(storage( axis_, axisName));
}

bool generic_plane::setHitAxisAdress(const axesName_t& name, double* outVar) {


  for (auto&e : m_storage) {
    if (e.axisName == name) {
      e.value = outVar;
      m_usedstorage.push_back(e);
      return true;
    }
  }
  SCT_THROW("unknown Axes: " + necessary_CONVERSION(name));
  return false;
}

bool generic_plane::next() {
  while (++curr < m_id->size()) {
    if (m_id->at(curr) ==  necessary_CONVERSION(plane_id)){
      for (auto& e : m_usedstorage) {
        *(e.value) = e.vec->at(curr);
      }
      return true;
    }

  }
  curr = -1;
  return false;
}

void generic_plane::push() {
  push(plane_id);
}

void generic_plane::push(ID_t planeID){
  m_id->push_back(necessary_CONVERSION( planeID));
  for (auto& e : m_storage) {
    e.vec->push_back(*e.value);
  }
}

axis generic_plane::get_axis(const axesName_t& axisName)const {
  auto axis_ = getAxisByName(axisName, m_storage);
  
 return axis(plane_id,m_id, axisName, axis_, get_ProcessorCollection(),m_tree);

}


double generic_plane::get_value(const axesName_t& axisName) const
{
  for (auto& e : m_usedstorage) {
    if (e.axisName == axisName) {
      return *e.value;
    }
  }
  SCT_THROW("axis not found");
}

ProcessorCollection* generic_plane::get_ProcessorCollection() const{
  return m_pc;
}

TTree* generic_plane::get_tree(){
  return m_tree;
}

ID_t generic_plane::get_ID() const
{
  return plane_id;
}



std::vector<axesName_t> generic_plane::get_axes_names() const
{
  std::vector<axesName_t> ret;
  for (auto&e : m_storage)
  {
    ret.push_back(e.axisName);
  }


  return ret;
}


void generic_plane::set_name(const std::string& name)
{
  m_tree->SetName(name.c_str());
  m_collectionName = collectionName_t(name);
}


collectionName_t generic_plane::get_name() const
{
  return m_collectionName;
}

void generic_plane::clear_event()
{
  
}

storage::storage(std::vector<double>* vec_, const axesName_t& axisName_) :vec(vec_), axisName(axisName_), value(&zero)
{

}


#include "sct/generic_processors/processor_generic_append_plane.hh"
void generic_plane_slice_handler::operator=(const cutNote &ax)
{

  
  auto mm = m_plane->get_name();

  auto pl = generic_append_plane(*m_plane, m_name, ax, saveWithRandomName(processorName_t( necessary_CONVERSION( mm))));
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

}

