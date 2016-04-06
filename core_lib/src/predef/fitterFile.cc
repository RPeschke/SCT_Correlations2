#include "sct/predef/fitterFile.hh"
#include "sct//internal/factoryDef.hh"
registerBaseClassDef(fitterFile);



std::unique_ptr<fitterFile> create_Fitter_file(fitterFile::Parameter_ref name, const fitterFile::MainType& type /*= ""*/)
{
  return Class_factory_Utilities::Factory<fitterFile>::Create(type, name);
}

void register_file_reader(const std::string& name, fitterFile* (fun)(fitterFile::Parameter_ref param_))
{
   Class_factory_Utilities::Factory<fitterFile>::do_register( name ,fun);
}
