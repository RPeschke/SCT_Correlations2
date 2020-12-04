#include "sct/generic_processors/lambda_Note.hh"
#include "sct/generic_processors/cutNote.hh"
#include <vector>
#include "sct/generic_plane.hh"
#include "sct/generic_processors/planeCut.hh"




std::vector<generic_plane*> lambda_Note::get_planes() 
{
  return m_get_pl();
}

lambda_Note::lambda_Note(register_plane_f reg_, Predicate_f0 cut_, get_plane_f pl) :m_reg(reg_), m_cut(cut_), m_get_pl(std::move(pl)){

}

lambda_Note::lambda_Note() {

}

bool lambda_Note::register_plane(planeCut& pl) {

  m_reg(pl);
  return true;
}

double lambda_Note::get_value() const {
  return m_cut();
}




std::shared_ptr<cutNote> lambda_Note::copy() const {
  return _MAKE_SHARED1(lambda_Note, *this);
}

axesName_t lambda_Note::get_name() const
{
  throw std::logic_error("The method or operation is not implemented.");
}
