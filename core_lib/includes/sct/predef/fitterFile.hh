#ifndef fitterFile_h__
#define fitterFile_h__


#include "sct/predef/plane.hh"
#include "sct/internal/factory.hh"
#include <string>
#include "sct/platform.hh"
#define registerFitterFile(FitterFileType,FitterFileName) registerClass(fitterFile,FitterFileType,FitterFileName)

class EUTFile;
class DllExport fitterFile  {
public:
  
  using MainType = std::string;
  using Parameter_t = std::string;
  using Parameter_ref = const Parameter_t&;
  virtual xy_plane  apix_hit_local() const = 0;
  virtual xy_plane  apix_hit() const = 0;
  virtual xy_plane  apix_zs_data() const = 0;
  virtual xy_plane  apix_fitted() const = 0;
  virtual xy_plane  apix_fitted_local() const = 0;
                   
  virtual xy_plane  DUT_hit_local() const = 0;
  virtual xy_plane  DUT_hit() const = 0;
  virtual xy_plane  DUT_zs_data() const = 0;
  virtual xy_plane  DUT_fitted() const = 0;
  virtual xy_plane  DUT_fitted_local() const = 0;
                   
                   
  virtual xy_plane  tel_hit_local(double ID) const = 0;
  virtual xy_plane  tel_hit(double ID) const = 0;
  virtual xy_plane  tel_zs_data(double ID) const = 0;
  virtual xy_plane  tel_fitted(double ID) const = 0;
  virtual xy_plane  tel_fitted_local(double ID) const = 0;

  virtual FitterPlane DUT_fitted_local_GBL() const = 0;
  virtual FitterPlane tel_fitted_local_GBL(double ID) const = 0;


  virtual EUTFile* getGenericFile() =0;
  virtual ProcessorCollection* getProcessorCollection() = 0;
  
};

DllExport std::unique_ptr<fitterFile> create_Fitter_file(fitterFile::Parameter_ref name, const fitterFile::MainType& type = "MAY15");
DllExport void register_file_reader(const std::string& name, fitterFile* (fun)(fitterFile::Parameter_ref param_));
#endif // fitterFile_h__
