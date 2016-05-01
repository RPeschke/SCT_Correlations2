#include "sct/generic_processors/planeCut.hh"
#include "sct/generic_processors/AND_note.hh"

 bool AND_note::register_plane(planeCut& pl) {
   for (auto&e : m_storage){
     e->register_plane(pl);
   }
   return true;
 }



 double AND_note::get_value() const {
   for (auto& e : m_storage) {
     if (!e->get_value()) {
       return false;
     }
   }
   return true;
 }

 std::shared_ptr<cutNote> AND_note::copy() const {
   return _MAKE_SHARED1(AND_note, *this);
 }

 void AND_note::add(std::shared_ptr<cutNote> cut_) {
   m_storage.push_back(cut_);
 }



AND_note operator&&(const cutNote& NoteA, const cutNote& NoteB) {
  AND_note ret;
  ret.add(NoteA.copy());
  ret.add(NoteB.copy());
  return ret;
}

AND_note operator&&(AND_note NoteA, const cutNote& NoteB) {
  NoteA.add(NoteB.copy());
  return NoteA;
}

AND_note operator&&(const cutNote& NoteA, AND_note NoteB) {
  AND_note ret;
  for (auto e:NoteB.m_storage)
 {
   ret.add(e);
 }
  return ret;
}

AND_note operator&&(AND_note NoteA, AND_note NoteB) {
  for (auto e : NoteB.m_storage) {
    NoteA.add(e);
  }
  return NoteA;
}