#ifndef processor_generic_select_h__
#define processor_generic_select_h__

#include "sct/generic_plane.hh"
#include "sct/internal/strong_types.h"
#include "sct/processor_prob.hh"
#include <vector>

class cutNote;

class note_ref {
public:
  note_ref( cutNote& note) :m_note(&note) {}
  cutNote * m_note;
};

DllExport generic_plane select(
  const std::vector<note_ref> ax_select,
  cutNote&  ax_where, 
  const processor_prob& pprob = saveWithRandomName(processorName_t("select__"))
);


#endif // processor_generic_select_h__
