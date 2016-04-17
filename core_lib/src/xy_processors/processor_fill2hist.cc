#include "sct/xy_processors/xy_pro.hh"
#include "sct/processor_prob.hh"
#include "TH2.h"
#include "sct/processor.h"
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/ProcessorCollection.h"

class processor_fill_1d_hist : public processor {
public:
  processor_fill_1d_hist(const axis& x_, TH1* h1, processor_prob pprob):m_hist(h1), m_pprob(pprob),m_ax(x_){

  }

  virtual init_returns init() override
  {
    if (!m_hist)
    {
      return i_error;
    }
    m_hist->Reset();
    return i_sucess;
  }

  virtual process_returns processEvent() override
  {
    while (m_ax.next())
    {
      m_hist->Fill(m_ax.getValue());
    }
    return p_sucess;
  }

  virtual process_returns fill() override
  {
    return p_sucess;
  }

  virtual end_returns end() override
  {
    return e_success;

  }

  virtual processorName_t get_name() override
  {
    return m_pprob.name;
  }
  TH1* m_hist =nullptr;
  processor_prob m_pprob;
  axis m_ax;
};














class processor_fill_2d_hist :public processor_hit2d {
public:
  processor_fill_2d_hist(const xy_plane& x_, TH2* h1, processor_prob& pprob):processor_hit2d(x_.get_x(),x_.get_y(),pprob), m_hist(h1){

  }

  virtual void processHit(double x, double y) override
  {
    m_hist->Fill(x, y);
  }

  virtual init_returns init() override
  {
    processor_hit2d::init();

    if (!m_hist)
    {
      return i_error;
    }

    m_hist->Reset();

    return i_sucess;
  }
  TH2* m_hist = nullptr;

};







void xy_pro::fill2Hist(const xy_plane& x_, TH2* h1, processor_prob& pprob /* = DontsaveWithRandomName("fill2hist2d__") */) {
  std::shared_ptr<processor> p(new processor_fill_2d_hist(x_, h1, pprob));
  x_.get_ProcessorCollection()->addProcessor(p);

  
}

void xy_pro::fill2Hist(const axis& x_, TH1* h1, processor_prob& pprob /* = DontsaveWithRandomName("fill2hist1d__") */) {
  std::shared_ptr<processor> p(new processor_fill_1d_hist(x_, h1, pprob));
  x_.get_ProcessorCollection()->addProcessor(p);
}