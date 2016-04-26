#ifndef cutNote_h__
#define cutNote_h__
#include "sct/platform.hh"


#ifndef __CINT__
#include <functional>
#include <memory>
#define  DEFAULT_OP =default
#include "sct/generic_processors/planeCut.hh"
#else
#define  DEFAULT_OP 
class planeCut;
#endif // __CINT__


class DllExport cutNote {
public:
  cutNote() {}
  virtual void register_plane(planeCut& pl) = 0;
  virtual bool operator()() const = 0;
  virtual ~cutNote() {}
#ifndef __CINT__
  virtual std::shared_ptr<cutNote> copy() const = 0;
#endif
};


typedef double cutValue_t;
typedef double hitVale_t;
#ifndef __CINT__
using register_plane_f = std::function<void(planeCut& pl)>;
using Predicate_f0 = std::function<bool()>;
using Predicate_f = std::function<bool(hitVale_t)>;
using Predicate_f2 = std::function<bool(hitVale_t,cutValue_t)>;

template<typename... Args>
using Predicate_fv = std::function<bool(Args... args)>;
#endif

#endif // cutNote_h__
