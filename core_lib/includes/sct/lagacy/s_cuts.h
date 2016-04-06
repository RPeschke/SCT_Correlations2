#ifndef s_cuts_h__
#define s_cuts_h__

#include "sct/platform.hh"
#ifndef __CINT__
#include <memory>
#include <vector>
#endif

class DllExport S_Cut
{
public:

  virtual ~S_Cut(){}

#ifndef __CINT__
  virtual std::shared_ptr<S_Cut> copy()const { 
    return  std::shared_ptr<S_Cut>(new S_Cut(*this));
  }
#endif // __CINT__

  virtual bool isOutOfRange(double BinContent, double x, double y) const { return false; }
  virtual bool isOutOfRange(double BinContent, double x)  const { return false; }
  virtual bool isOutOfRange(double BinContent)  const { return false; }
 
};
class DllExport S_NoCut:public S_Cut
{
public:

  virtual ~S_NoCut(){}

#ifndef __CINT__
  virtual std::shared_ptr<S_Cut> copy()const {
    return  std::shared_ptr<S_Cut>(new S_NoCut(*this));
  }
#endif // __CINT__

  
};
class DllExport S_Cut_min_max : public S_Cut
{
public:
  virtual ~S_Cut_min_max(){}
  S_Cut_min_max(double min_, double max_);
  S_Cut_min_max(double min_);

protected:
#ifndef __CINT__

  double m_min, m_max;
  bool m_cut_min, m_cut_max;
  bool isOutOfRange_intern(double val)  const;
#endif // !__CINT__

  
};

class DllExport  S_XCut :public S_Cut_min_max
{
public:
  S_XCut(double min_, double max_);
  S_XCut(double min_);
#ifndef __CINT__
  virtual std::shared_ptr<S_Cut> copy()const {
    return  std::shared_ptr<S_Cut>(new S_XCut(*this));
  }
#endif // __CINT__
  virtual bool isOutOfRange(double BinContent, double x, double y) const;
  virtual bool isOutOfRange(double BinContent, double x) const;
  virtual bool isOutOfRange(double BinContent)  const;

 
};
class DllExport S_YCut :public S_Cut_min_max
{
public:
  S_YCut(double min_, double max_);
  S_YCut(double min_);
#ifndef __CINT__
  virtual std::shared_ptr<S_Cut> copy()const {
    return  std::shared_ptr<S_Cut>(new S_YCut(*this));
  }
#endif // __CINT__
  virtual bool isOutOfRange(double BinContent, double x, double y) const;
  virtual bool isOutOfRange(double BinContent, double x) const;
  virtual bool isOutOfRange(double BinContent) const;
 
};
class  DllExport S_Cut_BinContent :public S_Cut_min_max
{
public:
  S_Cut_BinContent(double min_, double max_);
  S_Cut_BinContent(double min_);
#ifndef __CINT__
  virtual std::shared_ptr<S_Cut> copy()const override{
    return  std::shared_ptr<S_Cut>(new S_Cut_BinContent(*this));
  }
#endif // __CINT__
  virtual bool isOutOfRange(double BinContent, double x, double y) const ;
  virtual bool isOutOfRange(double BinContent, double x) const ;
  virtual bool isOutOfRange(double BinContent) const ;

 
};

class  DllExport S_CutCoollection :public S_Cut
{
public:

#ifndef __CINT__
  virtual std::shared_ptr<S_Cut> copy()const {
    return  std::shared_ptr<S_Cut>(new S_CutCoollection(*this));
  }
#endif // __CINT__
  S_CutCoollection();
  virtual bool isOutOfRange(double BinContent, double x, double y) const;
  virtual bool isOutOfRange(double BinContent, double x) const;
  virtual bool isOutOfRange(double BinContent) const;
  void add_Cut(const S_Cut& cut_);
  void add_Cut(const S_CutCoollection& cut_);
#ifndef __CINT__
  std::vector<std::shared_ptr<S_Cut> > m_cuts;
#endif // !__CINT__

};
DllExport S_CutCoollection operator+(const S_Cut& cut_a, const S_Cut& cut_b);



#endif // s_cuts_h__
