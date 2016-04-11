#ifndef fitterFile_h__
#define fitterFile_h__


#include "sct/predef/plane.hh"
#include <string>
#include "sct/platform.hh"



#ifndef __CINT__
#include "sct/internal/factory.hh"
#define registerFitterFile(FitterFileType,FitterFileName) registerClass(fitterFile,FitterFileType,FitterFileName)
#endif // !__CINT__

class EUTFile;
class DllExport fitterFile  {
public:
  
  typedef std::string MainType;
  typedef  std::string Parameter_t;
  typedef const Parameter_t& Parameter_ref;
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
  virtual bool isOpen() const = 0;
  virtual ~fitterFile() {}
};

class DllExport FFile {
public:

  typedef std::string MainType;
  typedef  std::string Parameter_t;
  typedef const Parameter_t& Parameter_ref;
  FFile(fitterFile::Parameter_ref name, const fitterFile::MainType& type = "MAY15");
  FFile();
  xy_plane  apix_hit_local() const;
  xy_plane  apix_hit() const ;
  xy_plane  apix_zs_data() const ;
  xy_plane  apix_fitted() const ;
  xy_plane  apix_fitted_local() const ;

  xy_plane  DUT_hit_local() const ;
  xy_plane  DUT_hit() const ;
  xy_plane  DUT_zs_data() const;
  xy_plane  DUT_fitted() const ;
  xy_plane  DUT_fitted_local() const ;


  xy_plane  tel_hit_local(double ID) const ;
  xy_plane  tel_hit(double ID) const ;
  xy_plane  tel_zs_data(double ID) const ;
  xy_plane  tel_fitted(double ID) const ;
  xy_plane  tel_fitted_local(double ID) const ;

  FitterPlane DUT_fitted_local_GBL() const ;
  FitterPlane tel_fitted_local_GBL(double ID) const ;


  EUTFile* getGenericFile();
  ProcessorCollection* getProcessorCollection() ;
  fitterFile* get_file();
  bool isOpen() const;
private:
#ifndef __CINT__
  std::shared_ptr <fitterFile> m_file;
#endif
};
DllExport std::unique_ptr<fitterFile> create_Fitter_file(fitterFile::Parameter_ref name, const fitterFile::MainType& type = "MAY15");
DllExport void register_file_reader(const std::string& name, fitterFile* (fun)(fitterFile::Parameter_ref param_));
#endif // fitterFile_h__
