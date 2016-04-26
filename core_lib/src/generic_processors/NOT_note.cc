#include "sct/generic_processors/NOT_note.hh"

 NOT_note::NOT_note(std::shared_ptr<cutNote> note_):m_note(note_){

 }

 void NOT_note::register_plane(planeCut& pl) {
   m_note->register_plane(pl);
 }

 bool NOT_note::operator()() const {
   return !(m_note->operator()());
 }

 std::shared_ptr<cutNote> NOT_note::copy() const {
   return _MAKE_SHARED1(NOT_note, *this);
 }


NOT_note operator!(const cutNote& note_) {
  return NOT_note(note_.copy());
}
