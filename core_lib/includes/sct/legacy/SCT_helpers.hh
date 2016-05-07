#ifndef SCT_helpers_h__
#define SCT_helpers_h__
#include "sct/platform.hh"
#include "TF1.h"
#include "sct/legacy/s_cuts.h"
#include "sct/xy_processors/find_nearest_strip.hh"
#include "sct/internal/strong_types.h"
class TObject;
class TH1;
class TH2;
class TProfile;
class DllExport SCT_helpers {
public:
  static void CutTH2(TH2* h2, const S_Cut& cut_);
  static void CutTH1(TH1* h1, const S_Cut& cut_);
  static TH1* HistogrammSilhouette(TH2* h2, axis_def ax);

  static TF1 LinearFit_Of_Profile(TH2* h2, procent_t cut_prozent);
  static TH1* calc_efficiency(TH1* trueHits, TH1* dutHits);
  static TH2* calc_efficiency(TH2* trueHits, TH2* dutHits);
  static void saveTH1_as_txt(const TH1& h1, const char* nameTXT);
  static void saveTH2_as_txt(const TH2& h1, const char* nameTXT);


  static void saveTH1_as_txt(const TProfile& h1, const char* nameTXT);

};
#endif // SCT_helpers_h__
