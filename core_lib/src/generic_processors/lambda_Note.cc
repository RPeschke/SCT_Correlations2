#include "sct/generic_processors/lambda_Note.hh"
#include "sct/generic_processors/cutNote.hh"
#include <vector>
using Predicate_f0 = std::function<bool()>;



lambda_Note::lambda_Note(register_plane_f reg_, Predicate_f0 cut_) :m_reg(reg_), m_cut(cut_) {

}

void lambda_Note::register_plane(planeCut& pl) {
  m_reg(pl);
}

bool lambda_Note::operator()() const {
  return m_cut();
}

std::shared_ptr<cutNote> lambda_Note::copy() const {
  return _MAKE_SHARED1(lambda_Note, *this);
}
