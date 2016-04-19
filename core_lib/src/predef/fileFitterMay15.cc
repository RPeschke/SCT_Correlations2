#include "sct/predef/fitterFile.hh"
#include "TFile.h"
#include "sct/ProcessorCollection.h"
#include "sct/EUTFile.h"
#include "sct/predef/hit.hh"
#include "sct/collection.h"
#include <memory>
#include <iostream>


class fitterFileMay15 : public fitterFile{
public:
  fitterFileMay15(fitterFile::Parameter_ref params);
  virtual ~fitterFileMay15();
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


  virtual xy_plane  tel_hit_local(ID_t ID) const ;
  virtual xy_plane  tel_hit(ID_t ID) const ;
  virtual xy_plane  tel_zs_data(ID_t ID) const ;
  virtual xy_plane  tel_fitted(ID_t ID) const ;
  virtual xy_plane  tel_fitted_local(ID_t ID) const ;

  virtual FitterPlane DUT_fitted_local_GBL() const ;
  virtual FitterPlane tel_fitted_local_GBL(ID_t ID) const ;

  virtual EUTFile* getGenericFile();
  virtual ProcessorCollection* getProcessorCollection();
  virtual bool isOpen() const;
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
  m_file = _MAKE_SHARED1(TFile, params.c_str());
  m_pc = _MAKE_SHARED0(ProcessorCollection);
  m_generic = _MAKE_SHARED1(EUTFile,m_file.get(), m_pc.get());

}


fitterFileMay15::~fitterFileMay15()
{

}

static const collectionName_t  local_hits = collectionName_t("local_hit");
static const collectionName_t  global_hits = collectionName_t("hit");
static const collectionName_t  zsdata_m26 = collectionName_t("zsdata_m26");
static const collectionName_t  zsdata_apix = collectionName_t("zsdata_apix");
static const collectionName_t  fitpoints   = collectionName_t("fitpoints");
static const collectionName_t  fitpoints_local = collectionName_t("fitpoints_local");
static const collectionName_t  GBL_tracks = collectionName_t("GBL_tracks");
static const collectionName_t  zsdata_strip = collectionName_t("zsdata_strip");

xy_plane fitterFileMay15::apix_hit_local() const
{
  return xy_plane(m_generic->getCollection(local_hits)->getPlane(ID_t(20)));
}

xy_plane fitterFileMay15::apix_hit() const
{
  return xy_plane(m_generic->getCollection(global_hits)->getPlane(ID_t(20)));
}

xy_plane fitterFileMay15::apix_zs_data() const
{
  return xy_plane(m_generic->getCollection(zsdata_apix)->getPlane(ID_t(20)));
}

xy_plane fitterFileMay15::apix_fitted() const
{
  return xy_plane(m_generic->getCollection(fitpoints)->getPlane(ID_t(20)));
}

xy_plane fitterFileMay15::apix_fitted_local() const
{
  return xy_plane(m_generic->getCollection(fitpoints_local)->getPlane(ID_t(20)));
}

xy_plane fitterFileMay15::DUT_hit_local() const
{
  return xy_plane(m_generic->getCollection(local_hits)->getPlane(ID_t(8)));
}

xy_plane fitterFileMay15::DUT_hit() const
{
  return xy_plane(m_generic->getCollection(global_hits)->getPlane(ID_t(8)));
}

xy_plane fitterFileMay15::DUT_zs_data() const
{
  return xy_plane(m_generic->getCollection(zsdata_strip)->getPlane(ID_t(8)));
}

xy_plane fitterFileMay15::DUT_fitted() const
{
  return xy_plane(m_generic->getCollection(fitpoints)->getPlane(ID_t(8)));
}

xy_plane fitterFileMay15::DUT_fitted_local() const
{
  return xy_plane(m_generic->getCollection(fitpoints_local)->getPlane(ID_t(8)));
}

xy_plane fitterFileMay15::tel_hit_local(ID_t ID) const
{
  return xy_plane(m_generic->getCollection(local_hits)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_hit(ID_t ID) const
{
  return xy_plane(m_generic->getCollection(global_hits)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_zs_data(ID_t ID) const
{
  return xy_plane(m_generic->getCollection(zsdata_m26)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_fitted(ID_t ID) const
{
  return xy_plane(m_generic->getCollection(fitpoints)->getPlane(ID));
}

xy_plane fitterFileMay15::tel_fitted_local(ID_t ID) const
{
  return xy_plane(m_generic->getCollection(fitpoints_local)->getPlane(ID));
}

FitterPlane fitterFileMay15::DUT_fitted_local_GBL() const
{
  return FitterPlane(m_generic->getCollection(GBL_tracks)->getPlane(ID_t(8)));
}

FitterPlane fitterFileMay15::tel_fitted_local_GBL(ID_t ID) const
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

bool fitterFileMay15::isOpen() const
{
  return m_file->IsOpen();
}
