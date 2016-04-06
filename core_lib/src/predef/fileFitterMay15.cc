#include "sct/predef/fitterFile.hh"
#include "TFile.h"
#include "sct/ProcessorCollection.h"
#include "sct/EUTFile.h"
#include "sct/predef/hit.hh"
#include "sct/collection.h"
#include <memory>


class fitterFileMay15 : public fitterFile{
public:
  fitterFileMay15(fitterFile::Parameter_ref params);
  virtual xy_plane  apix_hit_local() const ;
  virtual xy_plane  apix_hit() const ;
  virtual xy_plane  apix_zs_data() const ;
  virtual xy_plane  apix_fitted() const ;
  virtual xy_plane  apix_fitted_local() const ;

  virtual xy_plane  DUT_hit_local() const ;
  virtual xy_plane  DUT_hit() const ;
  virtual xy_plane  DUT_zs_data() const ;
  virtual xy_plane  DUT_fitted() const ;
  virtual xy_plane  DUT_fitted_local() const ;


  virtual xy_plane  tel_hit_local(double ID) const ;
  virtual xy_plane  tel_hit(double ID) const ;
  virtual xy_plane  tel_zs_data(double ID) const ;
  virtual xy_plane  tel_fitted(double ID) const ;
  virtual xy_plane  tel_fitted_local(double ID) const ;

  virtual FitterPlane DUT_fitted_local_GBL() const ;
  virtual FitterPlane tel_fitted_local_GBL(double ID) const ;

  virtual EUTFile* getGenericFile();
  virtual ProcessorCollection* getProcessorCollection();
  std::shared_ptr<TFile> m_file;
  std::shared_ptr<ProcessorCollection> m_pc;
  std::shared_ptr<EUTFile> m_generic;
  
};

registerFitterFile(fitterFileMay15, "MAY15");



// fitterFile* create_may(fitterFile::Parameter_ref params) {
//   return new fitterFileMay15(params);
// }
// 
// 
// class reg{
// public:
//   reg() {
//     register_file_reader("MAY15", create_may);
//   }
// } reg_;
fitterFileMay15::fitterFileMay15(fitterFile::Parameter_ref params)
{
  m_file = std::make_shared<TFile>(params.c_str());
  m_pc = std::make_shared<ProcessorCollection>();
  m_generic = std::make_shared<EUTFile>(m_file.get(), m_pc.get());

}


static const char*  local_hits = "local_hit";
static const char*  global_hits = "hit";

static const char*  zsdata_m26 = "zsdata_m26";
static const char*  zsdata_apix = "zsdata_apix";
static const char*  fitpoints   ="fitpoints";
static const char*  fitpoints_local = "fitpoints_local";
static const char*  GBL_tracks = "GBL_tracks";
static const char*  zsdata_strip = "zsdata_strip";

xy_plane fitterFileMay15::apix_hit_local() const
{
  return xy_plane(m_generic->getCollection(local_hits)->getPlane(20));
}

xy_plane fitterFileMay15::apix_hit() const
{
  return xy_plane(m_generic->getCollection(global_hits)->getPlane(20));
}

xy_plane fitterFileMay15::apix_zs_data() const
{
  return xy_plane(m_generic->getCollection(zsdata_apix)->getPlane(20));
}

xy_plane fitterFileMay15::apix_fitted() const
{
  return xy_plane(m_generic->getCollection(fitpoints)->getPlane(20));
}

xy_plane fitterFileMay15::apix_fitted_local() const
{
  return xy_plane(m_generic->getCollection(fitpoints_local)->getPlane(20));
}

xy_plane fitterFileMay15::DUT_hit_local() const
{
  return xy_plane(m_generic->getCollection(local_hits)->getPlane(8));
}

xy_plane fitterFileMay15::DUT_hit() const
{
  return xy_plane(m_generic->getCollection(global_hits)->getPlane(8));
}

xy_plane fitterFileMay15::DUT_zs_data() const
{
  return xy_plane(m_generic->getCollection(zsdata_strip)->getPlane(8));
}

xy_plane fitterFileMay15::DUT_fitted() const
{
  return xy_plane(m_generic->getCollection(fitpoints)->getPlane(8));
}

xy_plane fitterFileMay15::DUT_fitted_local() const
{
  return xy_plane(m_generic->getCollection(fitpoints_local)->getPlane(8));
}

xy_plane fitterFileMay15::tel_hit_local(double ID) const
{
  return xy_plane(m_generic->getCollection(local_hits)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_hit(double ID) const
{
  return xy_plane(m_generic->getCollection(global_hits)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_zs_data(double ID) const
{
  return xy_plane(m_generic->getCollection(zsdata_m26)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_fitted(double ID) const
{
  return xy_plane(m_generic->getCollection(fitpoints)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_fitted_local(double ID) const
{
  return xy_plane(m_generic->getCollection(fitpoints_local)->getPlane(ID));
}

FitterPlane fitterFileMay15::DUT_fitted_local_GBL() const
{
  return FitterPlane(m_generic->getCollection(GBL_tracks)->getPlane(8));
}

FitterPlane fitterFileMay15::tel_fitted_local_GBL(double ID) const
{
  return FitterPlane(m_generic->getCollection(GBL_tracks)->getPlane(ID));
}

EUTFile* fitterFileMay15::getGenericFile()
{
  return m_generic.get();
}

ProcessorCollection* fitterFileMay15::getProcessorCollection()
{
  return m_pc.get();
}
