#include "sct/lcio/lcio_collection.hh"
#include "sct/generic_plane.hh"
#define  X_DEF axesName_t("x")
#define  Y_DEF axesName_t("y")
#define  ID_DEF axesName_t("ID")


lcio_collection::lcio_collection(const collectionName_t& name, ProcessorCollection* pc):m_name(name),m_pc(pc)
{
  m_storage[ID_DEF] = std::make_shared< std::vector<double>>();
  m_storage[X_DEF] = std::make_shared< std::vector<double>>();
  m_storage[Y_DEF] = std::make_shared< std::vector<double>>();
}

generic_plane lcio_collection::getPlane(ID_t planeID)
{
  auto ID = m_storage[ID_DEF].get();

  auto ret = generic_plane(planeID, ID, m_pc, nullptr);

  for (auto&e : m_storage) {
    if (e.first != ID_DEF) {
      ret.add_axis(e.first, e.second.get());
    }
  }

  return ret;
}

axis lcio_collection::getAxis(ID_t planeID, const axesName_t& axis_name)
{
  auto ID = m_storage[ID_DEF].get();
  auto axis_ = m_storage[axis_name].get();  
  return axis(planeID, ID, axis_name, axis_, m_pc, nullptr);
}

void lcio_collection::pushCollection(const EVENT::LCCollection* col){


}

void lcio_collection::newEvent(int eventNR){
  for (auto& e:m_storage)  {
    e.second->clear();
  }
  m_eventNumber = 0;
}

void lcio_collection::FinnishEvent()
{

}

void lcio_collection::eventEnd()
{

}
