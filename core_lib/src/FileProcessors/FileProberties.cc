#include "sct/FileProcessors/FileProberties.hh"

TFile* FileProberties::getTfile() const
{
  if (m_fileOwnd) {
    return m_fileOwnd.get();
  }

  if (m_file) {
    return m_file;
  }
  return nullptr;
}

void FileProberties::setTFile(TFile* file)
{
  m_file = file;
}

void FileProberties::setTFile(std::shared_ptr<TFile> file)
{
  m_fileOwnd = file;
}
