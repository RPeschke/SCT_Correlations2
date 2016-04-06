#include "sct/cut_axis.hh"

cut_axis::cut_axis(const std::string& axisName):m_name(axisName)
{

}

cut_axis_min::cut_axis_min(const std::string& axisName, double min_):m_name(axisName),m_min(min_)
{

}

cut_axis_min_max::cut_axis_min_max(const std::string& axisName, double min_, double max_):m_name(axisName),m_min(min_),m_max(max_)
{

}

cut_axis_max::cut_axis_max(const std::string& axisName, double max_):m_name(axisName),m_max(max_)
{

}

cut_axis_min operator<(double min_, const cut_axis& ax){

  return cut_axis_min(ax.m_name, min_);
}

cut_axis_max operator<(const cut_axis& ax, double max_)
{
  return cut_axis_max(ax.m_name, max_);
}

cut_axis_min_max operator<(const cut_axis_min& ax, double max_){
  return cut_axis_min_max(ax.m_name, ax.m_min, max_);
}

cut_axis_min_max operator<(double min_, const cut_axis_max& ax){
  return cut_axis_min_max(ax.m_name, min_, ax.m_max);
}
