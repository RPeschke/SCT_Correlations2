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

class TrackerData_output :public lcio_output {
public:
  typedef const EVENT::TrackerData data_t;

  virtual void pushEvent(const LCEvent* evt)  override{

    try {
      LCCollection* col = evt->getCollection(m_prob.m_name);
      pushCollection(col);
    }
    catch (...) {

    }
  }
  virtual void pushCollection(const EVENT::LCCollection* col) {

    for (size_t i = 0; i < col->getNumberOfElements(); ++i) {



      data_t* hit = dynamic_cast< data_t*> (col->getElementAt(i));
      if (!hit)
      {
        std::cout << "unable to cast the pointer in " << m_prob.m_type << ": " << m_prob.m_name << std::endl;
        return;
      }

      for (size_t i = 0; i < hit->getChargeValues().size() / 4; i++)
      {

        UTIL::CellIDDecoder<data_t> hitDecoder(col);
        int sensorID = hitDecoder(hit)["sensorID"];
        
        push_hit(hit->getChargeValues().at(i * 4), 
          hit->getChargeValues().at(i * 4 + 1), 
          sensorID
          );

      }

    }
  }

  TrackerData_output(Parameter_ref param_) : lcio_output(param_) { }


};


register_lcio_output(TrackerData_output, LCIO::TRACKERDATA);