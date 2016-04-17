#include "sct/axis.hh"

axis::axis(ID_t planeID, std::vector<double> *ID, const axesName_t& axisName, std::vector<double> *axis_, ProcessorCollection* pc,TTree* tree):plane_id(planeID),m_id(ID),m_axis(axis_),m_name(axisName),m_pc(pc),m_tree(tree){

}

axis::axis(const axis& ax): plane_id(ax.plane_id), m_id(ax.m_id),m_axis(ax.m_axis),m_name(ax.m_name),m_pc(ax.m_pc),m_tree(ax.m_tree){


}

axis& axis::operator=(const axis& ax){
  plane_id=ax.plane_id;
  m_id=ax.m_id;
  m_axis=ax.m_axis;
  m_name=ax.m_name;
  m_pc=ax.m_pc;
  m_tree=ax.m_tree;
  return *this;
}

axesName_t axis::getName() const {
  return m_name;
}

double axis::getValue() const{
  return m_axis->at(curr);
}

bool axis::next(){
  while (++curr < m_id->size()) {
    if (m_id->at(curr) == necessary_CONVERSION(plane_id)) {
      return true;
    }

  }
  curr = -1;
  return false;

}

ProcessorCollection* axis::get_ProcessorCollection()const {
  return m_pc;
}

TTree* axis::get_tree() const{

  return m_tree;
}

ID_t axis::get_ID() const{

  return plane_id;
}

