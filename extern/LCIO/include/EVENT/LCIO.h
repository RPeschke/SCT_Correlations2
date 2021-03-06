// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef EVENT_LCIO_H
#define EVENT_LCIO_H 1
#include "LCPlatform.hh"



#ifdef WIN32
#define LCEVENT _LCEVENT()
#define LCRUNHEADER                        _LCRUNHEADER()
#define LCCOLLECTION                       _LCCOLLECTION()
#define MCPARTICLE                         _MCPARTICLE()
#define SIMCALORIMETERHIT                  _SIMCALORIMETERHIT()
#define RAWCALORIMETERHIT                  _RAWCALORIMETERHIT()
#define CALORIMETERHIT                     _CALORIMETERHIT()
#define SIMTRACKERHIT                     _SIMTRACKERHIT()
#define TPCHIT                            _TPCHIT()
#define TRACKERRAWDATA                    _TRACKERRAWDATA()
#define TRACKERDATA                       _TRACKERDATA()
#define TRACKERPULSE                      _TRACKERPULSE()
#define TRACKERHIT                        _TRACKERHIT()
#define TRACKERHITPLANE                   _TRACKERHITPLANE()
#define TRACKERHITZCYLINDER               _TRACKERHITZCYLINDER()
#define LCSTRVEC                          _LCSTRVEC()
#define LCFLOATVEC                        _LCFLOATVEC()
#define LCINTVEC                          _LCINTVEC()
#define TRACK                             _TRACK()
#define TRACKSTATE                        _TRACKSTATE()
#define CLUSTER                           _CLUSTER()
#define RECONSTRUCTEDPARTICLE             _RECONSTRUCTEDPARTICLE()
#define LCRELATION                        _LCRELATION()
#define LCGENERICOBJECT                   _LCGENERICOBJECT()
#define PARTICLEID                        _PARTICLEID()
#define VERTEX                            _VERTEX()
#define CellIDEncoding                    _CellIDEncoding()

#endif // WIN32



namespace EVENT {


#define LCIO_MAJOR_VERSION 2
#define LCIO_MINOR_VERSION 4
#define LCIO_PATCH_LEVEL 2

#define LCIO_VERSION_GE( MAJV , MINV )  ( (  LCIO_MAJOR_VERSION  > MAJV ) || ( (LCIO_MAJOR_VERSION==MAJV) && ( LCIO_MINOR_VERSION >= MINV ) ) )

#define LCIO_PATCHVERSION_GE( MAJV , MINV , PLEV)  ( (  LCIO_MAJOR_VERSION  > MAJV ) ||   ( (LCIO_MAJOR_VERSION==MAJV) && ( LCIO_MINOR_VERSION > MINV ) ) ||   ( (LCIO_MAJOR_VERSION==MAJV) && ( LCIO_MINOR_VERSION == MINV ) && ( LCIO_PATCH_LEVEL >= PLEV ) ) )

/** Global constants used in LCIO.
 *
 * @author gaede
 * @version $Id: LCIO.aid,v 1.77 2010-10-29 10:26:09 gaede Exp $
 * @see LCObject
 * @see LCIO
 */
  

  class DLLEXPORT_LCIO LCIO {

public: 
    /// Destructor.
    virtual ~LCIO() { /* nop */; }

    // it seems to be impossible to have one declaration for
    // static constants in Java and C++ - so we need to define
    // the same constants twice !!

  public:
    enum :int {
    // current version number of lcio
      MAJORVERSION = LCIO_MAJOR_VERSION,
      MINORVERSION = LCIO_MINOR_VERSION,
    // bits in flag words
    // SimCalorimeterHit (CH)
         CHBIT_LONG =31, // long(1) - short(0), (position)
         CHBIT_BARREL  = 30,  // barrel(1) - endcap(0)
         CHBIT_ID1     =29 ,  // cellid1 stored
         CHBIT_PDG   = 28,   // PDG(1) - no PDG(0) (detailed shower contributions) // DEPRECATED use: CHBIT_STEP
         CHBIT_STEP   = 28,   // detailed shower contributions 
    // (raw) calorimeter hit
     RCHBIT_LONG   =31,  // long(1) - short(0) , incl./excl. position
     RCHBIT_BARREL =30,  // barrel(1) - endcap(0)
     RCHBIT_ID1    =29,  // cellid1 stored
     RCHBIT_NO_PTR =28, // 1: pointer tag not added
     RCHBIT_TIME   =27, // 1: time information stored
     RCHBIT_ENERGY_ERROR =26,     // 1: store energy error

    // raw tracker data (pulses)
     TRAWBIT_ID1  =31,  //  cellid1 stored
     TRAWBIT_CM   =30,  //  cov matrix stored(1) - not stored(0)

    // raw tracker hit
         RTHBIT_ID1 =31     ,  //  cellid1 stored
      
    // TrackerHitPlane
        RTHPBIT_ID1 =31 , // cellid1 stored
      
    // TrackerHitZCylinder
          RTHZBIT_ID1  =31, // cellid1 stored
      
    // SimTrackerHit
         THBIT_BARREL   =31 , // barrel(1) - endcap(0)
         THBIT_MOMENTUM  =30, // momentum of particle stored(1) - not stored(0)
         THBIT_ID1       =29, // cellid1 stored
     
    // Tracks
         TRBIT_HITS =31 , // hits stored(1) - not stored(0)

    // Cluster
         CLBIT_HITS =31, // hits stored(1) - not stored(0)

    // TPCHit
         TPCBIT_RAW =31, // raw data stored(1) - not stored(0)
         TPCBIT_NO_PTR  =30, // 1: pointer tag not added (needed for TrackerHit)


    // LCRelation
    //         static const int LCREL_ONE2MANY = 31 ; // relation is one to many
         LCREL_WEIGHTED =31, // relations has weights


    // LCGenericObject
         GOBIT_FIXED =31, // is fixed size

         READ_ONLY  =0,
         UPDATE   =1,
    // error handling
         RETURN_ERROR  =0 ,
         RETURN_SUCCESS = 1,

    //write modes
           WRITE_NEW = 0, 
           WRITE_APPEND =1
         };
         //static const int WRITE_NEW = 0;
         //static const int WRITE_APPEND  ;

    // type names:
    static const char* LCEVENT__ ;
#ifndef WIN32

    // type names:
    static const char* LCEVENT ;
    static const char* LCRUNHEADER ;
    static const char* LCCOLLECTION ;
    static const char* MCPARTICLE;
    static const char* SIMCALORIMETERHIT;
    static const char* RAWCALORIMETERHIT;
    static const char* CALORIMETERHIT;
    static const char* SIMTRACKERHIT;
    static const char* TPCHIT;
    static const char* TRACKERRAWDATA;
    static const char* TRACKERDATA;
    static const char* TRACKERPULSE;
    static const char* TRACKERHIT;
    static const char* TRACKERHITPLANE;
    static const char* TRACKERHITZCYLINDER;
    static const char* LCSTRVEC;
    static const char* LCFLOATVEC;
    static const char* LCINTVEC;
    static const char* TRACK;
    static const char* TRACKSTATE;
    static const char* CLUSTER;
    static const char* RECONSTRUCTEDPARTICLE;
    static const char* LCRELATION;
    static const char* LCGENERICOBJECT;
    static const char* PARTICLEID;
    static const char* VERTEX;

    // reserved names, e.g. name of event/collections parameters

    static const char* CellIDEncoding;
#else 




         static const char* _LCEVENT ();
         static const char* _LCRUNHEADER ();
         static const char* _LCCOLLECTION ();
         static const char* _MCPARTICLE ();
         static const char* _SIMCALORIMETERHIT ();
         static const char* _RAWCALORIMETERHIT ();
         static const char* _CALORIMETERHIT ();
         static const char* _SIMTRACKERHIT ();
         static const char* _TPCHIT ();
         static const char* _TRACKERRAWDATA ();
         static const char* _TRACKERDATA ();
         static const char* _TRACKERPULSE ();
         static const char* _TRACKERHIT ();
         static const char* _TRACKERHITPLANE ();
         static const char* _TRACKERHITZCYLINDER ();
         static const char* _LCSTRVEC ();
         static const char* _LCFLOATVEC ();
         static const char* _LCINTVEC ();
         static const char* _TRACK ();
         static const char* _TRACKSTATE ();
         static const char* _CLUSTER ();
         static const char* _RECONSTRUCTEDPARTICLE ();
         static const char* _LCRELATION ();
         static const char* _LCGENERICOBJECT ();
         static const char* _PARTICLEID();
         static const char* _VERTEX();

    // reserved names, e.g. name of event/collections parameters

         static const char* _CellIDEncoding ();
#endif // WIN32
}; // class
} // namespace EVENT
#endif /* ifndef EVENT_LCIO_H */
