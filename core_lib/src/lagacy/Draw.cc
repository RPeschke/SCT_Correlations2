#include "sct/lagacy/Draw.h"
#include "TTree.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include <iostream>
#include "TVirtualPad.h"
#include "sct/predef/plane.hh"
#include "sct/generic_plane.hh"

DrawOption::DrawOption(const char* options /*= "colz"*/, const char* cuts /*= ""*/, const char * axis /*= "y:x"*/) : m_options(options), m_cut(cuts), m_axis(axis)
{

}


DrawOption::DrawOption()
{

}








DrawOption::DrawOption(const char* options, TCut cuts, const char * axis /*= "y:x"*/) : m_options(options), m_cut(cuts), m_axis(axis)
{

}

DrawOption& DrawOption::options(const char* option)
{

  m_options = option;
  return *this;
}

DrawOption& DrawOption::opt_colz()
{

  return options("colz");
}







DrawOption& DrawOption::opt_star()
{
  return options("*");
}

DrawOption& DrawOption::opt_bar()
{
    return options("AP");
}


DrawOption& DrawOption::opt_same() {
  m_same = true;
  return *this;
}

DrawOption& DrawOption::opt_color(Color_t col) {

  m_color = col;
  return *this;
}

DrawOption& DrawOption::color_white() {
  return opt_color(kWhite);
}

DrawOption& DrawOption::color_black() {
  return opt_color(kBlack);
}

DrawOption& DrawOption::color_gray() {
  return opt_color(kGray);
}

DrawOption& DrawOption::color_green() {
  return opt_color(kGreen);
}

DrawOption& DrawOption::color_blue() {
  return opt_color(kBlue);
}

DrawOption& DrawOption::color_yellow() {
  return opt_color(kYellow);
}

DrawOption& DrawOption::color_magenta() {
  return opt_color(kMagenta);
}

DrawOption& DrawOption::color_cyan() {
  return opt_color(kCyan);
}

DrawOption& DrawOption::color_orange() {
  return opt_color(kOrange);
}

DrawOption& DrawOption::color_spring() {
  return opt_color(kSpring);
}

DrawOption& DrawOption::color_teal() {
  return opt_color(kTeal);
}

DrawOption& DrawOption::color_azure() {
  return opt_color(kAzure);

}

DrawOption& DrawOption::color_violet() {
  return opt_color(kViolet);
}

DrawOption& DrawOption::color_pink() {
  return opt_color(kPink);
}

DrawOption& DrawOption::color_red() {
  return opt_color(kRed);
}





DrawOption& DrawOption::cut(const std::string& cut_)
{
  TCut dummy = cut_.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}



DrawOption& DrawOption::cut(const std::string& ax, Double_t min_, Double_t max_)
{
  cut_min(ax, min_);
  return cut_max(ax, max_);
}

DrawOption& DrawOption::cut_min(const std::string& ax, Double_t min_)
{
  std::string dummy_str = ax + ">" + std::to_string(min_);
  TCut dummy = dummy_str.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}



DrawOption& DrawOption::cut_max(const std::string& ax, Double_t max_)
{
  std::string dummy_str = ax + "<" + std::to_string(max_);
  TCut dummy = dummy_str.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}

DrawOption& DrawOption::cut_add(const TCut& cut_)
{
  m_cut = m_cut&& cut_;
  return *this;
}

DrawOption& DrawOption::cut_x(Double_t min_, Double_t max_)
{
  cut_x_min(min_);
  return cut_x_max(max_);

}

DrawOption& DrawOption::cut_x_min(Double_t min_)
{
  std::string dummy_str = "x>" + std::to_string(min_);
  TCut dummy = dummy_str.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}

DrawOption& DrawOption::cut_x_max(Double_t max_)
{
  std::string dummy_str = "x<" + std::to_string(max_);
  TCut dummy = dummy_str.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}

DrawOption& DrawOption::cut_y(Double_t min_, Double_t max_)
{
  cut_y_min(min_);
  return cut_y_max(max_);
}

DrawOption& DrawOption::cut_y_min(Double_t min_)
{
  std::string dummy_str = "y>" + std::to_string(min_);
  TCut dummy = dummy_str.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}

DrawOption& DrawOption::cut_y_max(Double_t max_)
{
  std::string dummy_str = "y<" + std::to_string(max_);
  TCut dummy = dummy_str.c_str();
  m_cut = m_cut&& dummy;
  return *this;
}





DrawOption& DrawOption::draw_axis(const std::string& axis_)
{
  m_axis = axis_;
  return *this;
}

DrawOption& DrawOption::draw_axis(const std::string& x, const std::string& y)
{
  auto dummy = y + ":" + x;
  return draw_axis(dummy);
}

DrawOption& DrawOption::draw_axis(const std::string& x, const std::string& y, const std::string& z)
{
  auto dummy = z+ ":" +y + ":" + x;
  return draw_axis(dummy);
}

DrawOption& DrawOption::draw_x()
{
  m_numOfAxis = 1;
  return draw_axis("x");
}

DrawOption& DrawOption::draw_y()
{
  m_numOfAxis = 1;
  return draw_axis("y");
}

DrawOption& DrawOption::draw_x_VS_y()
{
  m_numOfAxis = 2;
  return draw_axis("x:y");
}

DrawOption& DrawOption::draw_y_VS_x()
{
  m_numOfAxis = 2;
  return draw_axis("y:x");
}

DrawOption& DrawOption::output_object(TObject* out_)
{
  m_output_object = out_;
  return *this;
}

TObject* DrawOption::get_output_object() const {
  return m_output_object;
}

////*********Set points to a TGraph
/*void DrawOption::push_output_to_TGraph(Long64_t numberOfPoints,TTree * tree) const
{
    if (m_output_object)
    {
        auto graph_ = dynamic_cast<TGraph*>(m_output_object);
        if (graph_)
        {
            if (m_numOfAxis == 1)
            {
                graph_->Set(0);
                TH1* h = dynamic_cast<TH1*>(gPad->GetPrimitive("htemp"));
                if (h)
                {
                    graph_->Set(0);
                    for (Int_t i = 0; i < h->GetNbinsX(); ++i)
                    {
                        graph_->SetPoint(i, h->GetBinCenter(i), h->GetBinContent(i));
                    }
                    graph_->SetEditable(false);
                }
            }
            else if (m_numOfAxis == 2)
            {
                graph_->Set(0);
                for (Int_t i = 0; i < numberOfPoints; ++i)
                {
                    graph_->SetPoint(i, tree->GetV2()[i], tree->GetV1()[i]);
                }
                graph_->SetEditable(false);
            }
        }
    }
}*/
////******** Set Points of a TGraphErrors
void DrawOption::push_output_to_TGraphErrors(Long64_t numberOfPoints,TTree * tree) const
{
    if (m_output_object)
    {
        auto graph_ = dynamic_cast<TGraphErrors*>(m_output_object);
        if (graph_)
        {
            if (m_numOfAxis == 1)
            {
                graph_->Set(0);
                TH1* h = dynamic_cast<TH1*>(gPad->GetPrimitive("htemp"));
                if (h)
                {
                    graph_->Set(0);
                    for (Int_t i = 0; i < h->GetNbinsX(); ++i)
                    {
                        graph_->SetPoint(i, h->GetBinCenter(i), h->GetBinContent(i));
                    }
                    graph_->SetEditable(false);
                }
            }
            else if (m_numOfAxis == 2)
            {
                graph_->Set(0);
                for (Int_t i = 0; i < numberOfPoints; ++i)
                {
                    graph_->SetPoint(i, tree->GetV2()[i], tree->GetV1()[i]);
                    graph_->SetPointError(i,0,tree->GetV3()[i]);//<-------------------
                }
                graph_->SetEditable(false);
            }
        }
    }
}
///////******Draw TGraphErrors / TGraph
Long64_t DrawOption::Draw(TTree * tree) const
{
    tree->SetLineColor(m_color);
    tree->SetMarkerColor(m_color);
    tree->SetFillColor(m_color);
    auto n = tree->Draw(getAxis(), getCut(), getOptions());
    
    //push_output_to_TGraph(n, tree);
    push_output_to_TGraphErrors(n, tree);
    return n;
}

const char* DrawOption::getOptions() const
{
  if (m_same) {
     m_out_option = m_options + "same";
     return m_out_option.c_str();
  }

  return m_options.c_str();
}

const char* DrawOption::getAxis() const
{
    
    
    m_axis_dummy = m_axis;
    if (m_output_object)
    {
        
        if ( dynamic_cast<TH1*>(m_output_object) )
        {
            m_axis_dummy += ">>" + std::string(m_output_object->GetName());
        }
    }
    return m_axis_dummy.c_str();
}

TCut DrawOption::getCut() const
{
  return m_cut;
}





int Draw(const axis& ax, DrawOption drawOp)
{
  drawOp.draw_axis(ax.getName());
  std::string s("ID==");
  s += std::to_string(ax.get_ID());
  drawOp.cut_add(s.c_str());


  auto tree = ax.get_tree();
  return drawOp.Draw(tree);


}

 int Draw(generic_plane& gp, DrawOption drawOp /*= DrawOption()*/)
{
  std::string s("ID==");
  s += std::to_string(gp.get_ID());
  drawOp.cut_add(s.c_str());
  auto tree = gp.get_tree();
  return drawOp.Draw(tree);
  
}

 int Draw(xy_plane& gp, DrawOption drawOp /*= DrawOption()*/)
 {
   return Draw(*gp.get_generic_plane(), drawOp);
 }
