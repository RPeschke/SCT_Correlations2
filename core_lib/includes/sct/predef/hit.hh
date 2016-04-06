#ifndef hits_h__
#define hits_h__
#include "sct/platform.hh"
class DllExport hit {
public:
  hit(double x_=0, double y_=0) :x(x_), y(y_) {}
  double x = 0, y = 0;
};

class DllExport fitterHit :public hit {
public:
  fitterHit(double x_=0, double y_=0, double theta_=0, double phi_=0, double chi2_=0, double ndf_=0) :hit(x_, y_), chi2(chi2_), ndf(ndf_), theta(theta_), phi(phi_) {}
  double chi2 = 0, ndf = 0, theta = 0, phi = 0;
};



#endif // hits_h__
