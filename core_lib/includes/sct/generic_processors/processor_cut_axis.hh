#ifndef processor_cut_axis_h__
#define processor_cut_axis_h__
#include "sct/processor.h"
#include "sct/internal/strong_types.h"
#include "sct/generic_plane.hh"
#include "sct/processor_prob.hh"
#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <tuple>
#include "../predef/plane.hh"


#ifndef __CINT__

#define  DEFAULT_OP =default
#else
#define  DEFAULT_OP 
#endif // __CINT__

class planeCut;

class cutNote {
public:
  cutNote() {}
  virtual void register_plane(planeCut& pl) = 0;
  virtual bool operator()() const = 0;
  virtual ~cutNote() {}
  virtual std::shared_ptr<cutNote> copy() const = 0;
};





typedef double cutValue_t;
typedef double hitVale_t;
using register_plane_f = std::function<void(planeCut& pl)>;
using Predicate_f0 = std::function<bool()>;
using Predicate_f = std::function<bool(hitVale_t)>;
using Predicate_f2 = std::function<bool(hitVale_t,cutValue_t)>;

template<typename... Args>
using Predicate_fv = std::function<bool(Args... args)>;


class DllExport lambda_Note : public cutNote {
public:
  lambda_Note(register_plane_f reg_, Predicate_f0  cut_):m_reg(reg_), m_cut(cut_) {
   
  }
  virtual void register_plane(planeCut& pl) {
    m_reg(pl);
  };
  virtual bool operator()() const {
    return m_cut();
  };
  virtual std::shared_ptr<cutNote> copy() const {
    return _MAKE_SHARED1(lambda_Note, *this);
  };
  register_plane_f m_reg;
  Predicate_f0 m_cut;

  std::vector<std::shared_ptr<cutNote>> m_notes;
};


template<typename... Axes_t>
void dummy(Axes_t... ax) {

}


template<typename Func_t, typename... Axes_t>
auto  make_lambda_Note_sp(Func_t&& f, std::shared_ptr<Axes_t>&&... ax) {
  auto reg_ = register_plane_f([=](planeCut& pl) {dummy(ax->register_plane(pl)...);});
  auto func_ = Predicate_f0([=]() { return f(ax->getValue()...);});
  return lambda_Note(reg_, func_);
}

template<typename Func_t,typename... Axes_t>
auto  make_lambda_Note(Func_t&& func_, Axes_t&&... ax) {
  return make_lambda_Note_sp(func_, _MAKE_SHARED1(Axes_t, ax)...);
}




class DllExport axCut {
public:
  axCut(axesName_t name_);
  axCut(axesName_t name_,x_slope_t slope_,x_offset_t offset_);

  double getValue() const;
  bool register_plane(planeCut& pl);
  axesName_t getName() const;

 DllExport friend  axCut operator+(axCut ax, double offset_);
 DllExport friend  axCut operator+(double offset_, axCut ax);

 DllExport friend  axCut operator*(axCut ax, double slope_);
 DllExport friend  axCut operator*( double slope_, axCut ax);



private:
  const axesName_t m_name;
  const double* m_hit = nullptr;
  const x_slope_t m_slope = x_slope_t(1);
  const x_offset_t m_offset = x_offset_t(0);
};

DllExport axCut x_def();
DllExport axCut y_def();

class DllExport axCutHandle:public cutNote {
public:
  axCutHandle(const axCutHandle&) DEFAULT_OP;
  axCutHandle& operator=(const axCutHandle&) DEFAULT_OP;
  axCutHandle(axCut name, Predicate_f fun);
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
  virtual std::shared_ptr<cutNote> copy() const ;
private:
  Predicate_f m_predicate;
   axCut m_Ax;

};


DllExport axCutHandle operator<(cutValue_t min_, axCut ax);
DllExport axCutHandle operator<=(cutValue_t min_, axCut ax);
DllExport axCutHandle operator>(cutValue_t val, axCut ax);
DllExport axCutHandle operator>=(cutValue_t val, axCut ax);
DllExport axCutHandle operator<(axCut ax, cutValue_t val);
DllExport axCutHandle operator<=(axCut ax, cutValue_t val);
DllExport axCutHandle operator>(axCut ax, cutValue_t val);
DllExport axCutHandle operator>=(axCut ax, cutValue_t val);

DllExport axCutHandle operator==(axCut ax, cutValue_t val);
DllExport axCutHandle operator!=(axCut ax, cutValue_t val);

DllExport axCutHandle operator==(cutValue_t val, axCut ax);
DllExport axCutHandle operator!=(cutValue_t val, axCut ax);

class DllExport doubleAX:public cutNote{
public:
  doubleAX(const doubleAX&) DEFAULT_OP;
  doubleAX& operator=(const doubleAX&) DEFAULT_OP;
  doubleAX(axCut nameA, axCut nameB, Predicate_f2 fun);
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
  virtual std::shared_ptr<cutNote> copy() const;
private:
  Predicate_f2 m_predicate;
  axCut m_axA;
  axCut m_axB;
};

DllExport doubleAX operator<(axCut A, axCut B);
DllExport doubleAX operator<=(axCut A, axCut B);
DllExport doubleAX operator>(axCut A, axCut B);
DllExport doubleAX operator>=(axCut A, axCut B);
DllExport doubleAX operator==(axCut A, axCut B);
DllExport doubleAX operator!=(axCut A, axCut B);

class DllExport AND_note :public cutNote {
public:
  AND_note() DEFAULT_OP;
  AND_note(const AND_note&) DEFAULT_OP;
  AND_note& operator=(const AND_note&) DEFAULT_OP;
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
  virtual std::shared_ptr<cutNote> copy() const;
  DllExport friend AND_note operator&&(AND_note NoteA, AND_note NoteB);
  DllExport friend AND_note operator&&(const cutNote& NoteA, AND_note NoteB);
  void add(std::shared_ptr<cutNote> cut_ );
private:
  std::vector<std::shared_ptr<cutNote>> m_storage;
};

DllExport AND_note operator&&(const cutNote& NoteA, const cutNote& NoteB);
DllExport AND_note operator&&(AND_note NoteA, const cutNote& NoteB);

class DllExport OR_note :public cutNote {
public:
  OR_note() DEFAULT_OP;
  OR_note(const OR_note&) DEFAULT_OP;
  OR_note& operator=(const OR_note&) DEFAULT_OP;
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
  virtual std::shared_ptr<cutNote> copy() const;
  DllExport friend OR_note operator||(OR_note NoteA, OR_note NoteB);
  DllExport friend OR_note operator||(const cutNote& NoteA, OR_note NoteB);
  void add(std::shared_ptr<cutNote> cut_);
private:
  std::vector<std::shared_ptr<cutNote>> m_storage;
};

DllExport OR_note operator||(const cutNote& NoteA, const cutNote& NoteB);
DllExport OR_note operator||(OR_note NoteA, const cutNote& NoteB);


class DllExport NOT_note :public cutNote {
public:
  NOT_note(std::shared_ptr<cutNote> note_);
  NOT_note(const NOT_note&) DEFAULT_OP;
  NOT_note& operator=(const NOT_note&) DEFAULT_OP;
  virtual void register_plane(planeCut& pl);
  virtual bool operator()() const;
  virtual std::shared_ptr<cutNote> copy() const;
private:
  std::shared_ptr<cutNote> m_note;
};

DllExport NOT_note operator!(const cutNote& note_);


class planeCut {
public:
  planeCut(const generic_plane& pl);
  double* getAxis(axesName_t ax);
  bool next();

private:
  std::map<axesName_t, std::shared_ptr<double>> m_storage;

  generic_plane m_pl;
};

class processor_cut_axis :public processor {
public:
  processor_cut_axis(const generic_plane& pl,const cutNote& ax,const processor_prob& pprob);
  
  virtual init_returns init() override;

  virtual process_returns processEvent() override;

  virtual process_returns fill() override;

  virtual end_returns end() override;

  virtual processorName_t get_name() override;

  collection* get_output_collection();

  planeCut m_plane;
  std::shared_ptr<cutNote> m_note;
  const std::vector<axesName_t> m_names;
  std::shared_ptr<collection> m_output_coll;
  std::shared_ptr<generic_plane> m_outputPlane;
  processor_prob m_pprob;
  int m_current = 0;
  
};


DllExport xy_plane cut_op(const xy_plane& pl, const cutNote& ax, const processor_prob& pprob);
DllExport generic_plane cut_op(const generic_plane& pl, const cutNote& ax, const processor_prob& pprob);

#endif // processor_cut_axis_h__
