#ifndef processor_normalize_on_first_plane_h__
#define processor_normalize_on_first_plane_h__

#include "sct/platform.hh"
#include "sct/internal/strong_types.h"
#include "sct/generic_plane.hh"
#include "sct/processor_prob.hh"
#include "sct/predef/plane.hh"



#include "sct/generic_processors/axCut.hh"
#include "sct/generic_processors/axCutHandle.hh"
#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/lambda_Note.hh"
#include "sct/generic_processors/planeCut.hh"
#include "sct/generic_processors/generic_operator.hh"


DllExport generic_plane normalize_with__(const generic_plane& pl1, const generic_plane& p2, const processor_prob& pprob = saveWithRandomName(processorName_t("norm_")));

enum _normalize_ {
  __normalize_start
};

struct __normalize___generic_plane_wraper {
  generic_plane pl1;
};

inline __normalize___generic_plane_wraper operator*(const generic_plane& pl, _normalize_) {
  return __normalize___generic_plane_wraper{ pl };
}

inline generic_plane operator*(__normalize___generic_plane_wraper&& pl, const generic_plane& p2) {
  return normalize_with__(pl.pl1, p2);
}




inline __normalize___generic_plane_wraper operator*(const xy_plane& pl, _normalize_) {
  return __normalize___generic_plane_wraper{ *pl.get_generic_plane() };
}

inline generic_plane operator*(__normalize___generic_plane_wraper&& pl, const xy_plane& p2) {
  return normalize_with__(pl.pl1, *p2.get_generic_plane());
}


#define  normalize_with *__normalize_start*


#endif // processor_normalize_on_first_plane_h__
