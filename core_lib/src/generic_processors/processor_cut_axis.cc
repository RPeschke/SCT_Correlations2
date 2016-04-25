#include "sct/generic_processors/processor_cut_axis.hh"
#include "sct/generic_plane.hh"
#include "sct/platform.hh"
#include "sct/collection.h"
#include "sct/processor_prob.hh"
#include "sct/ProcessorCollection.h"


processor_cut_axis::processor_cut_axis(const generic_plane& pl, const cutNote& ax,const processor_prob& pprob) :m_note(ax.copy()), m_plane(pl),m_names(pl.get_axes_names()),m_pprob(pprob) {
  m_pprob.setAxis(m_names);
  m_pprob.addAxis(axesName_t("ID"));
  m_output_coll = _MAKE_SHARED1(collection, m_pprob);
  m_note->register_plane(m_plane);
  m_outputPlane = _MAKE_SHARED1(generic_plane, m_output_coll->getPlane(ID_t(0)));
  for (auto &e : m_names) {
    m_outputPlane->setHitAxisAdress(e, m_plane.getAxis(e));
  }
  
}


init_returns processor_cut_axis::init() {
  m_current = 0;
  m_output_coll->clear_collection();
  return i_sucess;
}

process_returns processor_cut_axis::processEvent() {
  ++m_current;
  m_output_coll->clear_event();

  while (m_plane.next()) {
    if (m_note->operator()()) {
      m_outputPlane->push(ID_t(0));
    }
  }


 return p_sucess;
}

process_returns processor_cut_axis::fill() {
  m_output_coll->set_Event_Nr(m_current);
  m_output_coll->save();
  return p_sucess;
}

end_returns processor_cut_axis::end() {
  return e_success;
}

processorName_t processor_cut_axis::get_name() {
 return m_pprob.name;
}

collection* processor_cut_axis::get_output_collection() {
  return m_output_coll.get();
}

xy_plane cut_op(const xy_plane& pl, const cutNote& ax, const processor_prob& pprob) {
  return cut_op(*pl.get_generic_plane(), ax, pprob);
}

generic_plane cut_op(const generic_plane& pl, const cutNote& ax, const processor_prob& pprob) {
  std::shared_ptr<processor> p(new processor_cut_axis(pl,ax, pprob));
  pl.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<processor_cut_axis*>(p.get())->get_output_collection()->getPlane(ID_t(0));
}



void axCutHandle::register_plane(planeCut& pl) {
  m_Ax.register_plane(pl);
  
}

bool axCutHandle::operator()() const {
  return m_predicate(m_Ax.getValue());
}



std::shared_ptr<cutNote> axCutHandle::copy() const {
  return _MAKE_SHARED1(axCutHandle, *this);
}

axCutHandle::axCutHandle(axCut name, Predicate_f fun) :m_Ax(std::move(name)), m_predicate(std::move(fun)) {

}


axCutHandle operator<(cutValue_t min_, axCut ax) {
  return axCutHandle(ax, [min_](hitVale_t hitValue) { return min_ < hitValue;});
}

axCutHandle operator<(axCut ax, cutValue_t val) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue < val;});

}

doubleAX operator<(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA < hitB;});
}

axCutHandle operator<=(cutValue_t min_, axCut ax) {
  return axCutHandle(ax, [min_](hitVale_t hitValue) { return min_ <= hitValue;});
}

axCutHandle operator<=(axCut ax, cutValue_t val) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue <= val;});
}

doubleAX operator<=(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA <= hitB;});
}

axCutHandle operator>(cutValue_t val, axCut ax) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return val > hitValue;});
}

axCutHandle operator>(axCut ax, cutValue_t val) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue > val;});
}

doubleAX operator>(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA > hitB;});
}

axCutHandle operator>=(cutValue_t val, axCut ax) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return val >= hitValue;});
}

axCutHandle operator>=(axCut ax, cutValue_t val) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue >= val;});
}

doubleAX operator>=(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA >= hitB;});
}

doubleAX operator==(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA == hitB;});
}

axCutHandle operator==(axCut ax, cutValue_t val) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue == val;});
}

axCutHandle operator==(cutValue_t val, axCut ax) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue == val;});
}

doubleAX operator!=(axCut A, axCut B) {
  return doubleAX(A, B, [](double hitA, double hitB) {return hitA != hitB;});
}

axCutHandle operator!=(axCut ax, cutValue_t val) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue != val;});
}

axCutHandle operator!=(cutValue_t val, axCut ax) {
  return axCutHandle(ax, [val](hitVale_t hitValue) { return hitValue != val;});
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



NOT_note operator!(const cutNote& note_) {
  return NOT_note(note_.copy());
}

planeCut::planeCut(const generic_plane& pl):m_pl(pl) {

}

double* planeCut::getAxis(axesName_t ax) {
  auto p = m_storage[ax];
  if (p) {
    return p.get();
  }

  m_storage[ax] = _MAKE_SHARED0(double);
  m_pl.setHitAxisAdress(ax, m_storage[ax].get());
  return m_storage[ax].get();
}



bool planeCut::next() {
  return m_pl.next();
}



doubleAX::doubleAX(axCut nameA, axCut nameB, Predicate_f2 fun) :m_axA(nameA), m_axB(nameB),m_predicate(fun) {

}




void doubleAX::register_plane(planeCut& pl) {
  m_axA.register_plane(pl);
  m_axB.register_plane(pl);
}

bool doubleAX::operator()() const {
  return m_predicate(m_axA.getValue(), m_axB.getValue());
}

std::shared_ptr<cutNote> doubleAX::copy() const {
  return _MAKE_SHARED1(doubleAX, *this);
}






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

 void OR_note::register_plane(planeCut& pl) {
   for (auto&e : m_storage) {
     e->register_plane(pl);
   }
 }

 bool OR_note::operator()() const {
   for (auto& e : m_storage) {
     if (e->operator()()) {
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

 void AND_note::register_plane(planeCut& pl) {
   for (auto&e : m_storage){
     e->register_plane(pl);
   }
 }

 bool AND_note::operator()() const {
   for (auto& e : m_storage) {
     if (!e->operator()()) {
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

 axCut::axCut(axesName_t name_, x_slope_t slope_, x_offset_t offset_) :m_name(std::move(name_)), m_slope(slope_), m_offset(offset_) {

 }

 axCut::axCut(axesName_t name_) : m_name(std::move(name_)) {

 }

 double axCut::getValue() const {
   return necessary_CONVERSION(m_slope)* (*m_hit) + necessary_CONVERSION(m_offset);
 }

 bool axCut::register_plane(planeCut& pl) {
   m_hit = pl.getAxis(m_name);
   return true;
 }

 axesName_t axCut::getName() const {
   return m_name;
 }

 axCut operator+(axCut ax, double offset_) {
   return axCut(ax.getName(), ax.m_slope, ax.m_offset + x_offset_t( offset_));
 }

axCut operator+(double offset_, axCut ax) {
  return axCut(ax.getName(), ax.m_slope, ax.m_offset + x_offset_t( offset_));
}

axCut operator*(axCut ax, double slope_) {
  return axCut(ax.getName(), x_slope_t(slope_*  necessary_CONVERSION(ax.m_slope)), x_offset_t(slope_*  necessary_CONVERSION(ax.m_offset)));
}

axCut operator*(double slope_, axCut ax) {
  return axCut(ax.getName(), x_slope_t(slope_*  necessary_CONVERSION(ax.m_slope)), x_offset_t(slope_*  necessary_CONVERSION(ax.m_offset)));
}

axCut x_def() {
  return axCut(axesName_t("x"));
}

axCut y_def() {
  return axCut(axesName_t("y"));
}

