#ifndef vector_helpers_h__
#define vector_helpers_h__
#include <algorithm>

namespace sct {
    template <typename T1, typename T2>
    bool contains(const T1& t1, const T2& t2) {
      return std::find(t1.begin(), t1.end(), t2) != t1.end();
  }
}

#endif // vector_helpers_h__
