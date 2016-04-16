#ifdef USE_LCIO


#include "sct/lcio/lcio_output.hh"
#include "EVENT/TrackerPulse.h"
#include "EVENT/LCIO.h"
#include "sct/lcio/lcio_output.hh"
#include "EVENT/LCIO.h"
#include <iostream>
#include "UTIL/CellIDDecoder.h"
#include "EVENT/TrackerPulse.h"
#include "IMPL/TrackerHitImpl.h"
#include "IMPL/TrackImpl.h"
#include "EVENT/LCCollection.h"
#include "IMPL/LCCollectionVec.h"
#include "EVENT/Track.h"
#include "EVENT/LCObject.h"
#include "EVENT/TrackerData.h"
#include <vector>


class TrackerPulse_Output :public lcio_output {
public:
  typedef const EVENT::TrackerPulse data_t;


  virtual void pushEvent(const EVENT::LCEvent* evt) override {

    try {
      LCCollection* col = evt->getCollection(m_prob.m_name);
      pushCollection(col);
    }
    catch (...) {

    }
  }

  void pushCollection(const EVENT::LCCollection* col) {

    for (size_t i = 0; i < col->getNumberOfElements(); ++i) {
      data_t* hit = dynamic_cast<data_t*> (col->getElementAt(i));
      
      if (!hit)  {
        std::cout << "unable to cast the pointer" << std::endl;
        return;
      }


      for (size_t i = 0; i < hit->getTrackerData()->getChargeValues().size() / 4; i++) {
        UTIL::CellIDDecoder<data_t> hitDecoder(col);
        int sensorID = hitDecoder(hit)["sensorID"];
        push_hit(hit->getTrackerData()->getChargeValues().at(i * 4), hit->getTrackerData()->getChargeValues().at(i * 4 + 1), sensorID);
      }

    }
  }
  TrackerPulse_Output(Parameter_ref param) :lcio_output(param) {
  }
  virtual ~TrackerPulse_Output() {}

};

register_lcio_output(TrackerPulse_Output, LCIO::TRACKERPULSE);


#endif // USE_LCIO
