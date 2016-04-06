#ifndef xml_util_h__
#define xml_util_h__
#include <string>
#include <sstream>
#include <stdexcept>
#include "rapidxml.hpp"


class rapid_xml_node {
public:
  rapid_xml_node(rapidxml::xml_node<char>* node) :value(node) {}

  rapidxml::xml_node<char>* value = nullptr;
};


namespace xml_util{

  template <typename T>
  inline T  from_string(const std::string & x, const T & def = 0) {
    if (x == "") return def;
    T ret = def;
    std::istringstream s(x);
    s >> ret;
    char remain = '\0';
    s >> remain;
    if (remain) throw std::invalid_argument("Invalid argument: " + x);
    return ret;
  }
  template<>
  inline std::string  from_string(const std::string & x, const std::string & def) {
    return x == "" ? def : x;
  }

  template<typename T>
  inline std::vector<T> getVectorOfT(rapidxml::xml_node<char>* node_) {
    std::vector<T> ret;
    for (auto node = node_->first_node(T::NodeName()); node; node = node->next_sibling(T::NodeName()))
    {
      auto dummy = rapid_xml_node(node);
      ret.emplace_back(&dummy);
    }

    return ret;
  }
  template<typename T>
  inline std::vector<T> getVectorOfT(rapid_xml_node* node_) {
    return getVectorOfT(node_->value);
  }
  template <typename T>
inline  T getAtribute(rapidxml::xml_node<char>* node_, const char * AtributeName, T default_){
    auto n = node_->first_attribute(AtributeName);
    if (n)
    {
      return from_string(n->value(), (default_));
    }
    throw std::invalid_argument("Invalid attribute: " + std::string(AtributeName));
    return default_;
  }
template <typename T>
inline  T getAtribute(rapid_xml_node* node_, const char * AtributeName, T default_) {
  return getAtribute(node_->value, AtributeName, default_);
}
inline std::string getAtribute(rapidxml::xml_node<char>* node_, const char * AtributeName, const char* default_ = "") {
    return getAtribute(node_, AtributeName, std::string(default_));
  }

inline std::string getAtribute(rapid_xml_node* node_, const char * AtributeName, const char* default_ = "") {
  return getAtribute(node_, AtributeName, std::string(default_));
}


template <typename T>
inline  T getAtribute(rapidxml::xml_node<char>* node_, const char * AtributeName) {
  const T def = -123154647; // random number 
  
  auto ret = getAtribute(node_, AtributeName, def);
  if (ret == def) {
    throw std::invalid_argument("Invalid attribute: " + std::string(AtributeName));
  }
  return ret;
}


template <typename T>
inline  T getAtribute(rapid_xml_node* node_, const char * AtributeName) {
  return getAtribute<T>(node_->value, AtributeName);
}

inline std::string getAtribute_string(rapidxml::xml_node<char>* node_, const char * AtributeName) {
  const std::string default_("__dummy_default");

  auto ret = getAtribute(node_, AtributeName, default_);

  if (ret == default_) {
    throw std::invalid_argument("Invalid attribute: " + std::string(AtributeName));
  }
  return ret;
}


inline std::string getAtribute_string(rapid_xml_node* node_, const char * AtributeName) {
  return getAtribute_string(node_->value, AtributeName);
}
}
#endif // xml_util_h__
