#include "sct/lcio/lcio_collection.hh"
#include "sct/generic_plane.hh"

lcio_collection::lcio_collection(const std::string& name, ProcessorCollection* pc):m_name(name),m_pc(pc)
{
  m_storage["ID"] = std::make_shared< std::vector<double>>();
  m_storage["x"] = std::make_shared< std::vector<double>>();
  m_storage["y"] = std::make_shared< std::vector<double>>();
}

generic_plane lcio_collection::getPlane(double planeID)
{
  auto ID = m_storage["ID"].get();

  auto ret = generic_plane(planeID, ID, m_pc, nullptr);

  for (auto&e : m_storage) {
    if (e.first != "ID") {
      ret.add_axis(e.first, e.second.get());
    }
  }

  return ret;
}

axis lcio_collection::getAxis(double planeID, const std::string& axis_name)
{
  auto ID = m_storage["ID"].get();
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
