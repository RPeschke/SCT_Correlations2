#ifndef NOT_note_h__
#define NOT_note_h__
#include "sct/generic_processors/cutNote.hh"


#ifndef __CINT__
#include <memory>
#endif

class DllExport NOT_note :public cutNote {
public:
  NOT_note(const NOT_note&) DEFAULT_OP;
  NOT_note& operator=(const NOT_note&) DEFAULT_OP;
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
  DllExport friend NOT_note operator!(const cutNote& note_);
#ifndef __CINT__
  NOT_note(std::shared_ptr<cutNote> note_);
  virtual std::shared_ptr<cutNote> copy() const;
private:
  std::shared_ptr<cutNote> m_note;
#endif
};

#endif // NOT_note_h__
