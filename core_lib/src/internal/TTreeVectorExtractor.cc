
#include "sct/internal/TTreeVectorExtractor.hh"

#ifdef  _DEBUG
#include "ReleaseVectorDef/ReleaseVectorDef.h"
#else
#include "TTree.h"
#endif //  _DEBUG
#include <iostream>
#include <memory>







#ifdef _DEBUG   
TTreeVectorExtractor::TTreeVectorExtractor(const sct_type::AxesName_t& name, TTree* tree) :
  m_vecRel(std::make_shared<ReleaseVectorDef>(name.c_str())),
  m_name(name)

{


  m_vecRel->load_from_TTree(tree);
  m_owend_vector = std::make_shared<std::vector<double> >();
  m_vec = m_owend_vector.get();
}


TTreeVectorExtractor::TTreeVectorExtractor(const sct_type::AxesName_t& name) :m_vecRel(std::make_shared<ReleaseVectorDef>(name.c_str())), m_name(name)
{
  m_owend_vector = std::make_shared<std::vector<double> >();
  m_vec = m_owend_vector.get();
}

TTreeVectorExtractor::TTreeVectorExtractor()
{

}

TTreeVectorExtractor::~TTreeVectorExtractor()
{


}
bool TTreeVectorExtractor::push2TTree(TTree* tree)
{
  return m_vecRel->push2TTree(tree);
}


void TTreeVectorExtractor::loadFromVector()
{


  m_vec->clear();
  for (size_t i = 0; i < m_vecRel->size();++i)
  {
    m_vec->push_back(m_vecRel->at(i));
  }
}


void TTreeVectorExtractor::PushToVector() const
{
  m_vecRel->clear();
  for (auto&e : *m_vec)
  {
    m_vecRel->push_back(e);
  }
}
std::vector<double>* TTreeVectorExtractor::getVec() const
{
  return m_vec;
}



#else  //release

TTreeVectorExtractor::TTreeVectorExtractor(const sct_type::AxesName_t&  name, TTree* tree) :
  m_name(name)
{

  tree->SetBranchAddress(m_name.c_str(), &m_vec);

  if (!m_vec) {
    std::cout << "[TTreeVectorExtractor] vector Empty\n";
  }
}


TTreeVectorExtractor::TTreeVectorExtractor(const sct_type::AxesName_t&  name) : m_name(name)
{
  m_owend_vector = std::make_shared<std::vector<double>>();
  m_vec = m_owend_vector.get();
}
TTreeVectorExtractor::~TTreeVectorExtractor()
{


}
bool TTreeVectorExtractor::push2TTree(TTree* tree)
{

  if (!tree)
  {
    std::cout << "unable to push \"" << m_name << "\" to TTree. Tree is empty " << std::endl;
    return false;
  }

  tree->Branch(m_name.c_str(), &m_vec);

  return true;
}



std::vector<double>* TTreeVectorExtractor::getVec() const
{
  return m_vec;
}



#endif


sct_type::AxesName_t TTreeVectorExtractor::getName() const
{
  return m_name;
}

void TTreeVectorExtractor::reset()
{
  if (!m_owend_vector)
  {
    std::cout << "unable to clear not owned vector \n";
  }
  m_vec->clear();

}



