#include "sct/predef/fitterFile.hh"


#ifdef _DEBUG
#define Class_factory_Utilities_THROW(msg, inPutVar)  std::cout << "[Factory<baseClassType>::Create" << ":" << __LINE__ << "]: \n " << msg << " <" << necessary_CONVERSION(inPutVar) << ">" << std::endl;
#endif // _DEBUG


#include "sct//internal/factoryDef.hh"
#include "sct/internal/sct_exceptions.hh"
registerBaseClassDef(fitterFile);



std::unique_ptr<fitterFile> create_Fitter_file(fitterFile::Parameter_ref name, const fitterFile::MainType& type /*= ""*/)
{
  return Class_factory_Utilities::Factory<fitterFile>::Create(type, name);
}

void register_file_reader(const fitterFile::MainType& name, fitterFile* (fun)(fitterFile::Parameter_ref param_))
{
   Class_factory_Utilities::Factory<fitterFile>::do_register( name ,fun);
}

FFile::FFile(fitterFile::Parameter_ref name, const fitterFile::MainType& type /*= "MAY15"*/)
{
 auto dummy = std::move(create_Fitter_file(name, type));
  if (!dummy->isOpen()) {
    SCT_THROW("Unable to open File: <" + necessary_CONVERSION(name) + ">");
  }
  m_file = std::move(dummy);
}

FFile::FFile()
{

}

xy_plane FFile::apix_hit_local() const
{
 return m_file->apix_hit_local();
}

xy_plane FFile::apix_hit() const
{
 return m_file->apix_hit();
}

xy_plane FFile::apix_zs_data() const
{
  return m_file->apix_zs_data();
}

xy_plane FFile::apix_fitted() const
{
  return m_file->apix_fitted();
}

xy_plane FFile::apix_fitted_local() const
{
  return m_file->apix_fitted_local();
}

xy_plane FFile::DUT_hit_local() const
{
  return m_file->DUT_hit_local();
}

xy_plane FFile::DUT_hit() const
{
  return m_file->DUT_hit();
}

xy_plane FFile::DUT_zs_data() const
{
  return m_file->DUT_zs_data();
}

xy_plane FFile::DUT_fitted() const
{
  return m_file->DUT_fitted();
}

xy_plane FFile::DUT_fitted_local() const
{
  return m_file->DUT_fitted_local();
}

xy_plane FFile::tel_hit_local(ID_t ID) const
{
  return m_file->tel_hit_local(ID);
}

xy_plane FFile::tel_hit(ID_t ID) const
{
  return m_file->tel_hit(ID);
}

xy_plane FFile::tel_zs_data(ID_t ID) const
{
  return m_file->tel_zs_data(ID);
}

xy_plane FFile::tel_fitted(ID_t ID) const
{
  return m_file->tel_fitted(ID);
}

xy_plane FFile::tel_fitted_local(ID_t ID) const
{
  return m_file->tel_fitted_local(ID);
}

FitterPlane FFile::DUT_fitted_local_GBL() const
{
  return m_file->DUT_fitted_local_GBL();
}

FitterPlane FFile::tel_fitted_local_GBL(ID_t ID) const
{
  return m_file->tel_fitted_local_GBL(ID);
}

EUTFile* FFile::getGenericFile()
{
  return m_file->getGenericFile();
}

ProcessorCollection* FFile::getProcessorCollection()
{
  return m_file->getProcessorCollection();
}

fitterFile* FFile::get_file()
{
  return m_file.get();
}

bool FFile::isOpen() const
{
  return m_file->isOpen();
}
