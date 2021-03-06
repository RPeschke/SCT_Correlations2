#include "sct/legacy/s_cuts.h"


S_XCut::S_XCut(double min_, double max_) :S_Cut_min_max(min_, max_)
{

}

S_XCut::S_XCut(double min_) : S_Cut_min_max(min_)
{

}



bool S_XCut::isOutOfRange(double BinContent, double x, double y) const
{
  return isOutOfRange_intern(x);
}

bool S_XCut::isOutOfRange(double BinContent) const
{
  return false;
}

bool S_XCut::isOutOfRange(double BinContent, double x) const
{
  return isOutOfRange_intern(x);
}

S_YCut::S_YCut(double min_, double max_) :S_Cut_min_max(min_, max_)
{

}

S_YCut::S_YCut(double min_) : S_Cut_min_max(min_)
{

}


bool S_YCut::isOutOfRange(double BinContent, double x) const
{
  return false;
}

bool S_YCut::isOutOfRange(double BinContent) const
{
  return false;
}

bool S_YCut::isOutOfRange(double BinContent, double x, double y) const
{
  return isOutOfRange_intern(y);
}

S_Cut_BinContent::S_Cut_BinContent(double min_, double max_) :S_Cut_min_max(min_, max_)
{

}

S_Cut_BinContent::S_Cut_BinContent(double min_) : S_Cut_min_max(min_)
{

}











bool S_Cut_BinContent::isOutOfRange(double BinContent, double y, double z) const
{
  return isOutOfRange_intern(BinContent);
}

bool S_Cut_BinContent::isOutOfRange(double BinContent, double y) const
{
  return isOutOfRange_intern(BinContent);
}

bool S_Cut_BinContent::isOutOfRange(double BinContent) const
{
  return isOutOfRange_intern(BinContent);
}

S_Cut_min_max::S_Cut_min_max(double min_, double max_) :m_min(min_), m_max(max_), m_cut_min(true), m_cut_max(true)
{

}

S_Cut_min_max::S_Cut_min_max(double min_) : m_min(min_), m_max(0), m_cut_min(true), m_cut_max(false)
{

}

bool S_Cut_min_max::isOutOfRange_intern(double val) const
{
  if (m_cut_min && m_min > val)
  {
    return true;
  }

  if (m_cut_max && m_max < val)
  {
    return true;
  }
  return false;
}

S_CutCoollection::S_CutCoollection()
{

}

bool S_CutCoollection::isOutOfRange(double BinContent, double x, double y) const
{
  for (auto&e : m_cuts)
  {
    if (e->isOutOfRange(BinContent, x, y))
    {
      return true;
    }
  }
  return false;
}

bool S_CutCoollection::isOutOfRange(double BinContent, double x) const
{
  for (auto&e : m_cuts)
  {
    if (e->isOutOfRange(BinContent, x))
    {
      return true;
    }
  }
  return false;
}

bool S_CutCoollection::isOutOfRange(double BinContent) const
{
  for (auto&e : m_cuts)
  {
    if (e->isOutOfRange(BinContent))
    {
      return true;
    }
  }
  return false;
}

void S_CutCoollection::add_Cut(const S_Cut& cut_)
{
  auto nocut = dynamic_cast<const S_NoCut*>(&cut_);
  if (nocut)
  {
    return;
  }

  auto coll = dynamic_cast<const S_CutCoollection*>(&cut_);
  if (coll)
  {
    return add_Cut(*coll);
  }
  m_cuts.push_back(cut_.copy());
}

void S_CutCoollection::add_Cut(const S_CutCoollection& cut_)
{


  m_cuts.insert(m_cuts.end(), cut_.m_cuts.begin(), cut_.m_cuts.end());


}

S_CutCoollection operator+(const S_Cut& cut_a, const S_Cut& cut_b)
{



  S_CutCoollection ret;

  ret.add_Cut(cut_a);
  ret.add_Cut(cut_b);
  return ret;
}

