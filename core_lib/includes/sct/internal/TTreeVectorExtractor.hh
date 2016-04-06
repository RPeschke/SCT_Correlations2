#ifndef TTreeVectorExtractor_h__
#define TTreeVectorExtractor_h__

#include <string>
#include <vector>
#include <memory>
#include "sct/platform.hh"

class TTree;
class ReleaseVectorDef;
namespace sct_type {
  using AxesName_t = std::string;
}

class DllExport  TTreeVectorExtractor {
public:
  TTreeVectorExtractor(const sct_type::AxesName_t& name, TTree* tree);
  TTreeVectorExtractor(const sct_type::AxesName_t& name);
  TTreeVectorExtractor();
  bool push2TTree(TTree* tree);
  ~TTreeVectorExtractor();
  std::vector<double>* getVec() const;
  sct_type::AxesName_t getName() const;
  void reset();
#ifdef _DEBUG
  void loadFromVector();
  void PushToVector() const;
  std::shared_ptr<ReleaseVectorDef> m_vecRel;
#endif // _DEBUG

private:
  sct_type::AxesName_t m_name = sct_type::AxesName_t("");
  std::shared_ptr<std::vector<double>> m_owend_vector;
  std::vector<double>* m_vec = NULL;

};


#endif // TTreeVectorExtractor_h__
