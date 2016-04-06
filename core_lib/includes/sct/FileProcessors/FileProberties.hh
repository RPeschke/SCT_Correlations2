#ifndef FileProberties_h__
#define FileProberties_h__
#include "TFile.h"
#include <memory>

class FileProberties {
public:
  TFile* getTfile() const;
  void setTFile(TFile* file);
  void setTFile(std::shared_ptr<TFile> file);
  double m_Threshold = 0;
  double m_runNumber = 0;
  double m_HV = 0;

private:
  std::shared_ptr<TFile> m_fileOwnd;
  TFile* m_file = nullptr;
};
#endif // FileProberties_h__
