#ifndef AND_note_h__
#define AND_note_h__
#include "sct/generic_processors/cutNote.hh"


class DllExport AND_note :public cutNote {
public:
  AND_note() DEFAULT_OP;
  AND_note(const AND_note&) DEFAULT_OP;
  AND_note& operator=(const AND_note&) DEFAULT_OP;
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;

  DllExport friend AND_note operator&&(AND_note NoteA, AND_note NoteB);
  DllExport friend AND_note operator&&(const cutNote& NoteA, AND_note NoteB);
  DllExport friend AND_note operator&&(const cutNote& NoteA, const cutNote& NoteB);
  DllExport friend AND_note operator&&(AND_note NoteA, const cutNote& NoteB);
  
#ifndef __CINT__
  void add(std::shared_ptr<cutNote> cut_);
  virtual std::shared_ptr<cutNote> copy() const;
private:
  std::vector<std::shared_ptr<cutNote>> m_storage;
#endif
};

#endif // AND_note_h__
