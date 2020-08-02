#ifndef ref_ptr_h__
#define ref_ptr_h__

#include <memory>
#include "sct/platform.hh"

namespace sct {
  template <typename T>
  class DllExport ref_ptr {
  public:
    ref_ptr(T* t) : m_ptr(t){

    }


    ref_ptr(T& t) : m_ptr(&t) {

    }
    ref_ptr(std::shared_ptr<T>& t) : m_ptr(t.get()) {

    }
    ref_ptr(std::unique_ptr<T>& t) : m_ptr(t.get()) {

    }
    T* operator->() const noexcept
    {	// return pointer to resource
      return (get());
    }
    T* get() const noexcept
    {	// return pointer to resource
      return m_ptr;
    }
  private:
    T* m_ptr = nullptr;
  };
}
#endif // ref_ptr_h__
