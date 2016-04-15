#include "sct/lcio/lcio_output.hh"
#include "UTIL/CellIDDecoder.h"

#include "EVENT/LCEvent.h"
#include "EVENT/LCCollection.h"
#include "EVENT/TrackerPulse.h"
#include "IMPL/TrackerHitImpl.h"
class TrackerHit_output :public lcio_output {
public:
  typedef const EVENT::TrackerHit data_t;


  virtual void pushEvent(const EVENT::LCEvent* evt) override{
    
    try {
      LCCollection* col = evt->getCollection(m_prob.m_name);
      pushCollection(col);
    } catch (...) {

    }
  }
  void pushCollection(const EVENT::LCCollection* col) {

    data_t* hit = NULL;
    for (size_t i = 0; i < col->getNumberOfElements(); ++i) {

      hit = dynamic_cast<data_t*>(col->getElementAt(i));
      if (!hit) {
        std::cout << "unable to cast the pointer" << std::endl;
        continue;

      }
      UTIL::CellIDDecoder<data_t> hitDecoder(col);
      int sensorID = hitDecoder(hit)["sensorID"];
      push_hit(hit->getPosition()[0], hit->getPosition()[1], sensorID);
    }
  }

  TrackerHit_output(Parameter_ref param) : lcio_output(param) {

  }
};

register_lcio_output(TrackerHit_output, LCIO::TRACKERHIT);