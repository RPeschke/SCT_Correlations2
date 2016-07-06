#ifndef fitterFile_h__
#define fitterFile_h__


#include "sct/predef/plane.hh"
#include <string>
#include "sct/platform.hh"



#ifndef __CINT__
#include "sct/internal/factory.hh"
#define registerFitterFile(FitterFileType,FitterFileName) registerClass(fitterFile,FitterFileType,fitterFile::MainType(FitterFileName))
#endif // !__CINT__

class EUTFile;
class DllExport fitterFile  {
public:
  
  typedef SubClassName_t MainType;
  typedef  FileName_t Parameter_t;
  typedef const Parameter_t& Parameter_ref;
  virtual xy_plane  apix_hit_local() const ;
  virtual xy_plane  apix_hit() const ;
  virtual xy_plane  apix_zs_data() const ;
  virtual xy_plane  apix_fitted() const;
  virtual xy_plane  apix_fitted_local() const;
                   
  virtual xy_plane  DUT_hit_local() const ;
  virtual xy_plane  DUT_hit() const;
  virtual xy_plane  DUT_zs_data() const ;
  virtual xy_plane  DUT_fitted() const ;
  virtual xy_plane  DUT_fitted_local() const ;
                   
                   
  virtual xy_plane  tel_hit_local(ID_t ID) const;
  virtual xy_plane  tel_hit(ID_t ID) const ;
  virtual xy_plane  tel_zs_data(ID_t ID) const ;
  virtual xy_plane  tel_fitted(ID_t ID) const ;
  virtual xy_plane  tel_fitted_local(ID_t ID) const ;

  virtual FitterPlane DUT_fitted_local_GBL() const ;
  virtual FitterPlane tel_fitted_local_GBL(ID_t ID) const ;


  virtual EUTFile* getGenericFile() ;
  virtual ProcessorCollection* getProcessorCollection() ;
  virtual bool isOpen() const ;
  virtual ~fitterFile() {}
};

class DllExport FFile {
public:

  typedef SubClassName_t MainType;
  typedef  FileName_t Parameter_t;
  typedef const Parameter_t& Parameter_ref;
  FFile(fitterFile::Parameter_ref name, const fitterFile::MainType& type = fitterFile::MainType("MAY15"));
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


  xy_plane  tel_hit_local(ID_t ID) const ;
  xy_plane  tel_hit(ID_t ID) const ;
  xy_plane  tel_zs_data(ID_t ID) const ;
  xy_plane  tel_fitted(ID_t ID) const ;
  xy_plane  tel_fitted_local(ID_t ID) const ;

  FitterPlane DUT_fitted_local_GBL() const ;
  FitterPlane tel_fitted_local_GBL(ID_t ID) const ;


  EUTFile* getGenericFile();
  ProcessorCollection* getProcessorCollection() ;
  fitterFile* get_file();
  bool isOpen() const;
private:
#ifndef __CINT__
  std::shared_ptr <fitterFile> m_file;
#endif
};
DllExport std::unique_ptr<fitterFile> create_Fitter_file(fitterFile::Parameter_ref name, const fitterFile::MainType& type = fitterFile::MainType("MAY15"));
DllExport void register_file_reader(const fitterFile::MainType& name, fitterFile* (fun)(fitterFile::Parameter_ref param_));
#endif // fitterFile_h__
