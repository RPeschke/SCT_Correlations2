#include "sct/lcio/lcio_output.hh"
#include "EVENT/Track.h"
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

class Tracks_output : public lcio_output {
public:
  typedef const EVENT::Track* data_t;
  static const char* TypeName() {
    return LCIO::TRACK;
  }
  Tracks_output(Parameter_ref param) : lcio_output(param) {}
  virtual void pushEvent(const EVENT::LCEvent* col) {

    if (warning)
    {
      std::cout << "not implemented type: " << TypeName() << std::endl;
      warning = false;
    }
  };
  bool warning = true;
};

register_lcio_output(Tracks_output, LCIO::TRACK);