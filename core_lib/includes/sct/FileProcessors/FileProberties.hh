#ifndef FileProberties_h__
#define FileProberties_h__
#include "TFile.h"
#include <memory>
#include <string>

class FileProberties {
public:

  double m_Threshold = 0;
  double m_runNumber = 0;
  double m_HV = 0;
  std::string m_fileName;
};
#endif // FileProberties_h__
