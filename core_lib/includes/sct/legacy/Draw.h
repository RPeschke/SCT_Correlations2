#ifndef DrawOption_h__
#define DrawOption_h__

#include "sct/platform.hh"
#include "TCut.h"
#include <string>
#include "sct/axis.hh"
#include "sct/generic_plane.hh"
#include "sct/predef/plane.hh"

class TTree;
class TObject;
class DllExport DrawOption {
public:

  DrawOption(const char* options, const char* cuts = "", const char * axis = "y:x");
  DrawOption(const char* options, TCut cuts, const char * axis = "y:x");
  DrawOption();
  DrawOption& options(const char* option);
  DrawOption& opt_colz();
  DrawOption& opt_star();
  DrawOption& opt_bar();
  DrawOption& opt_same();
  DrawOption& opt_color(Color_t);
  DrawOption& color_red();


  DrawOption& color_white();
  DrawOption& color_black();
  DrawOption& color_gray();
  DrawOption& color_green();
  DrawOption& color_blue();
  DrawOption& color_yellow();
  DrawOption& color_magenta();
  DrawOption& color_cyan();
  DrawOption& color_orange();
  DrawOption& color_spring();
  DrawOption& color_teal();
  DrawOption& color_azure();
  DrawOption& color_violet();
  DrawOption& color_pink();


  DrawOption& cut(const std::string& cut_);
  DrawOption& cut_min(const std::string& ax, Double_t min_);
  DrawOption& cut_max(const std::string& ax, Double_t max_);
  DrawOption& cut(const std::string& ax, Double_t min_, Double_t max_);
  DrawOption& cut_add(const TCut& cut_);
  DrawOption& cut_x(Double_t min_, Double_t max_);
  DrawOption& cut_x_min(Double_t min_);
  DrawOption& cut_x_max(Double_t max_);
  DrawOption& cut_y(Double_t min_, Double_t max_);
  DrawOption& cut_y_min(Double_t min_);
  DrawOption& cut_y_max(Double_t max_);
  DrawOption& draw_axis(const std::string& axis_);
  DrawOption& draw_axis(const std::string& x, const std::string& y);
  DrawOption& draw_axis(const std::string& x, const std::string& y, const std::string& z);
  DrawOption& draw_x();
  DrawOption& draw_y();
  DrawOption& draw_x_VS_y();
  DrawOption& draw_y_VS_x();
  DrawOption& output_object(TObject* out_);
  TObject* get_output_object() const;
  Long64_t Draw(TTree * tree) const;
  const char* getOptions() const;
  const char* getAxis() const;
  TCut getCut() const;
private:
#ifndef __CINT__
 // void push_output_to_TGraph(Long64_t numberOfPoints, TTree* output_tree)const;
  void push_output_to_TGraphErrors(Long64_t numberOfPoints, TTree* output_tree)const;
  std::string m_options = "colz", m_axis = "y:x";
  mutable std::string  m_out_option;
  TCut m_cut;
  TObject* m_output_object = nullptr;
  mutable std::string m_axis_dummy;
  mutable int m_numOfAxis = 2;
  mutable Color_t m_color = kBlack;
  bool m_same = false;
#endif // !__CINT__


};

DllExport int Draw(const axis& ax, DrawOption drawOp = DrawOption());
DllExport int Draw(generic_plane& gp, DrawOption drawOp = DrawOption());
DllExport int Draw(xy_plane& gp, DrawOption drawOp = DrawOption());



DllExport void Print(axis& ax);
DllExport void Print(xy_plane& gp);
#endif // DrawOption_h__
