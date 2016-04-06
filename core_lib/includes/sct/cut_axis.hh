#ifndef cut_axis_h__
#define cut_axis_h__
#include <string>


class cut_axis {
public:
  cut_axis(const std::string& axisName);
  std::string m_name;
};

class cut_axis_min {
public:
  cut_axis_min(const std::string& axisName, double min_);
  std::string m_name;
  double m_min;
};
class cut_axis_min_max {
public:
  cut_axis_min_max(const std::string& axisName, double min_,double max_);
  std::string m_name;
  double m_min,m_max;
};
class cut_axis_max {
public:
  cut_axis_max(const std::string& axisName,  double max_);
  std::string m_name;
  double m_max;
};

cut_axis_min operator<(double min_, const cut_axis& ax);
cut_axis_max operator<(const cut_axis& ax,double max_);
cut_axis_min_max operator<(const cut_axis_min& ax, double max_);
cut_axis_min_max operator<(double min_,const cut_axis_max& ax);


#endif // cut_axis_h__
