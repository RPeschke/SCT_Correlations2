#ifndef strong_types_h__
#define strong_types_h__


#include <string>
#include "sct/platform.hh"
#ifdef _DEBUG


#define necessary_CONVERSION(x) x.value
#define Un_necessary_CONVERSION(x) x.value

#define TYPE_CLASS(name,type) \
class DllExport name { \
public: \
  explicit name(const type& param_) :value(param_) {}\
  type value; \
  friend bool operator==(const name& lhs, const name& rhs) { return lhs.value == rhs.value;} \
  friend bool operator!=(const name& lhs, const name& rhs) { return lhs.value != rhs.value;} \
  friend bool operator<(const name& lhs, const name& rhs) { return lhs.value < rhs.value;} \
  friend bool operator>(const name& lhs, const name& rhs) { return lhs.value > rhs.value;} \
  friend name operator+(const name& lhs, const name& rhs) { return name(lhs.value + rhs.value);} \
}

template <typename out_t, typename in_t>
out_t strong_cast(const in_t& in_) {
  return out_t(necessary_CONVERSION(in_));
}


#else 
#define necessary_CONVERSION(x) x
#define Un_necessary_CONVERSION(x) x

#define TYPE_CLASS(name,type) \
typedef  type name


template <typename out_t, typename in_t>
const out_t& strong_cast(const in_t& in_) {
  return in_;
}

template <typename out_t, typename in_t>
out_t& strong_cast(in_t& in_) {
  return in_;
}
#endif // _DEBUG




  TYPE_CLASS(modulo_x, double);
  TYPE_CLASS(modulo_y, double);
  TYPE_CLASS(modulo_t, double);
  TYPE_CLASS(max_cl_t, double); // maximum cluster size 


  TYPE_CLASS(ID_t, double);
  TYPE_CLASS(stripNr_t, int);
 
   TYPE_CLASS(x_offset_t, double);
     TYPE_CLASS(x_slope_t, double);
   TYPE_CLASS(y_offset_t, double);
    TYPE_CLASS(y_slope_t, double);
  TYPE_CLASS(residualCut_t, double);
  TYPE_CLASS(residualCut_x, double);
  TYPE_CLASS(residualCut_y, double);
  TYPE_CLASS(rot_angle_t, double);

  TYPE_CLASS(move_t, double);
  TYPE_CLASS(collectionName_t, std::string);
  TYPE_CLASS(axesName_t, std::string);
  TYPE_CLASS(processorName_t, std::string);
  TYPE_CLASS(procent_t, double);

  TYPE_CLASS(FileName_t, std::string);
  TYPE_CLASS(SubClassName_t, std::string);


#endif // strong_types_h__