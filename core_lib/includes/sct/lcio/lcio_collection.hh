#ifndef lcio_collection_h__
#define lcio_collection_h__
#include "sct/generic_plane.hh"
#include "sct/axis.hh"
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
namespace EVENT {
  class LCCollection;
}

class DllExport lcio_collection {
public:
  lcio_collection(const collectionName_t& name,ProcessorCollection* pc);
  generic_plane getPlane(ID_t planeID);
  axis getAxis(ID_t planeID, const axesName_t& axis_name);
  int get_Event_Nr() const;
  virtual void pushCollection(const EVENT::LCCollection* col);

  virtual void newEvent(int eventNR);
  virtual void FinnishEvent();;
  virtual void eventEnd();
  std::map<axesName_t, std::shared_ptr<std::vector<double>>> m_storage;
  ProcessorCollection* m_pc = nullptr;
  int m_eventNumber = 0;
  collectionName_t m_name;
};

#endif // lcio_collection_h__
