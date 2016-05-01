#ifndef processor_cut_axis_h__
#define processor_cut_axis_h__

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



DllExport xy_plane cut_op(const xy_plane& pl, const cutNote& ax, const processor_prob& pprob =saveWithRandomName(processorName_t("cut__")));
DllExport generic_plane cut_op(const generic_plane& pl, const cutNote& ax, const processor_prob& pprob =saveWithRandomName(processorName_t("cut__")));

#endif // processor_cut_axis_h__
