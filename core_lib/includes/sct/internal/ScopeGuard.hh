#ifndef ScopeGuard_h__
#define ScopeGuard_h__
#include <type_traits>
#include <functional>

#define ____SCOPE_GUARD_CONCATENATE_DETAIL(x, y) x##y
#define ____SCOPE_GUARD_CONCATENATE(x, y) ____SCOPE_GUARD_CONCATENATE_DETAIL(x, y)
#define ____SCOPE_GUARD_MAKE_UNIQUE(x)  ____SCOPE_GUARD_CONCATENATE(x, __LINE__)



#define SCOPE_GUARD_START \
bool __SCOPE_GUARD_ERROR=false; bool RUN_FINNAL = true; auto ___SCOPE_GUARD_NAME =  [&] {


#define SCOPE_GUARD_ON_ERROR  };\
auto ____SCOPE_GUARD_MAKE_UNIQUE(__ERROR__) = sct_internal::ScopeGuard_h(&__SCOPE_GUARD_ERROR)+[&]{

#define SCOPE_GUARD_ON_FINAL  };\
auto ____SCOPE_GUARD_MAKE_UNIQUE(__FINAL___) = sct_internal::ScopeGuard_h(&RUN_FINNAL)+[&]{


#define SCOPE_GUARD_END_RETURN };\
try { return  ___SCOPE_GUARD_NAME(); } \
catch (const sct_corr::Exception& e) { __SCOPE_GUARD_ERROR=true;  ADD_LOCATION(e);  throw e; }\
catch (const std::exception & e) {__SCOPE_GUARD_ERROR =true; SCT_THROW(e.what());}\
catch (...) {__SCOPE_GUARD_ERROR =true; SCT_THROW("Unknown exception:\n"); } 




#define SCOPE_GUARD_END_CONTINUE };\
try {  ___SCOPE_GUARD_NAME(); } \
catch (const sct_corr::Exception& e) {   ADD_LOCATION(e);  throw e; }\
catch (const std::exception & e) { SCT_THROW(e.what());}\
catch (...) { SCT_THROW("Unknown exception:\n"); } 


namespace sct_internal {
  class ScopeGuard {
  public:

    template<typename T>
    ScopeGuard(T&& f, const bool* error_) :
      m_func(std::forward<T>(f)),
      m_run(error_) {
    }

    ~ScopeGuard() {
      if (*m_run) {
        m_func();
      }
    }

    const bool* m_run = nullptr;
    std::function<void()> m_func;
  };

  class ScopeGuard_h {
  public:
    ScopeGuard_h(const bool* run) :m_run(run) {}
    const bool* m_run = nullptr;
  };

  template <typename T>
  auto operator+(ScopeGuard_h&& h, T&& func_) -> decltype(ScopeGuard(std::forward<T>(func_), h.m_run)) {

    return ScopeGuard(std::forward<T>(func_), h.m_run);
  }
}
#endif // ScopeGuard_h__
