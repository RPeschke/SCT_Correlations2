#ifndef OR_note_h__
#define OR_note_h__
#include "sct/platform.hh"
#include "sct/generic_processors/cutNote.hh"
#include <memory>


class DllExport OR_note :public cutNote {
public:
  OR_note() DEFAULT_OP;
  OR_note(const OR_note&) DEFAULT_OP;
  OR_note& operator=(const OR_note&) DEFAULT_OP;
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;


#ifndef __CINT__

  void add(std::shared_ptr<cutNote> cut_);
  virtual std::shared_ptr<cutNote> copy() const;

  std::vector<std::shared_ptr<cutNote>> m_storage;
#endif // __CINT__
};
DllExport  OR_note operator||(OR_note NoteA, OR_note NoteB);
DllExport  OR_note operator||(const cutNote& NoteA, OR_note NoteB);
DllExport  OR_note operator||(const cutNote& NoteA, const cutNote& NoteB);
DllExport  OR_note operator||(OR_note NoteA, const cutNote& NoteB);

#endif // OR_note_h__
