#include "sct/generic_processors/OR_note.hh"





bool OR_note::register_plane(planeCut& pl) {
   for (auto&e : m_storage) {
     e->register_plane(pl);
   }
   return true;
 }

double OR_note::get_value() const {
   for (auto& e : m_storage) {
     if (e->get_value()) {
       return true;
     }
   }
   return false;
 }








 std::shared_ptr<cutNote> OR_note::copy() const {
   return _MAKE_SHARED1(OR_note, *this);
 }

 void OR_note::add(std::shared_ptr<cutNote> cut_) {
   m_storage.push_back(cut_);
 }

OR_note operator||(const cutNote& NoteA, const cutNote& NoteB) {
  OR_note ret;
  ret.add(NoteA.copy());
  ret.add(NoteB.copy());
  return ret;
}

OR_note operator||(OR_note NoteA, const cutNote& NoteB) {
  NoteA.add(NoteB.copy());
  return NoteA;
}

OR_note operator||(const cutNote& NoteA, OR_note NoteB) {
  OR_note ret;
  for (auto e : NoteB.m_storage) {
    ret.add(e);
  } 
  return ret;

}

OR_note operator||(OR_note NoteA, OR_note NoteB) {
  for (auto e : NoteB.m_storage) {
    NoteA.add(e);
  }
  return NoteA;
}

