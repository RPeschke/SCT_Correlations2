#ifndef AND_note_h__
#define AND_note_h__
#include "sct/generic_processors/cutNote.hh"


class DllExport AND_note :public cutNote {
public:
  AND_note() DEFAULT_OP;
  AND_note(const AND_note&) DEFAULT_OP;
  AND_note& operator=(const AND_note&) DEFAULT_OP;
  virtual bool register_plane(planeCut& pl) __OVERIDE__;
  virtual double get_value() const __OVERIDE__;


  
#ifndef __CINT__
  void add(std::shared_ptr<cutNote> cut_);
  virtual std::shared_ptr<cutNote> copy() const;
  std::vector<std::shared_ptr<cutNote>> m_storage;
#endif
};


DllExport AND_note operator&&(AND_note NoteA, AND_note NoteB);
DllExport AND_note operator&&(const cutNote& NoteA, AND_note NoteB);
DllExport AND_note operator&&(const cutNote& NoteA, const cutNote& NoteB);
DllExport AND_note operator&&(AND_note NoteA, const cutNote& NoteB);
#endif // AND_note_h__
