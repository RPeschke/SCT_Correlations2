#include "sct/FileProcessors/FileProcessorsBase.hh"
#include "sct/FileProcessors/FileProberties.hh"
#include "TFile.h"
#include "sct/analysis/instrip_efficiency.hh"
#include "sct/predef/DUT_2_Track_correlator.hh"
#include "sct/predef/truehitExtractor.hh"
#include "sct/predef/fitterFile.hh"
#include <iostream>
#include "sct/analysis/residual_efficiency.hh"
#include "sct/legacy/Cluster_strip.hh"
#include "sct/internal/strong_types.h"

class DllExport FileProcessorsBase_modulo : public FileProcessorsBase {
public:
  FileProcessorsBase_modulo(Parameter_ref par);
  virtual ~FileProcessorsBase_modulo();

  virtual void saveHistograms(TFile* outPutFile, double residual_min, double residual_max) override;
private:

  virtual std::string get_suffix() const override;

  virtual  bool process_file(FileProberties* fileP) override;



  TFile* m_dummy = nullptr;
  std::shared_ptr<instrip_efficiency> m_efficiency;
  std::shared_ptr<residual_efficiency> m_res_efficiency;
  std::shared_ptr<Cluster_strip> m_cluster_size;
  xy_plane m_trueHits, m_totalTrue_hits, m_truehits_withDUT;
  FFile m_input_file;
  

};
register_file_processor(FileProcessorsBase_modulo, "Modulo");

FileProcessorsBase_modulo::FileProcessorsBase_modulo(Parameter_ref par)
{
  m_dummy = new TFile("dummy.root", "recreate");
}

FileProcessorsBase_modulo::~FileProcessorsBase_modulo()
{

}

void FileProcessorsBase_modulo::saveHistograms(TFile* outPutFile, double residual_min, double residual_max)
{

  m_cluster_size->Draw_ClusterSize();
  if (outPutFile)
  {
    outPutFile->Add(m_efficiency->Draw_Efficiency());
    outPutFile->Add(m_efficiency->Draw_true_hits());
    outPutFile->Add(m_res_efficiency->Draw_residual_efficiency());
    outPutFile->Add(m_res_efficiency->Draw_true_residuals());
    outPutFile->Add(m_cluster_size->get_histogram());
    outPutFile->Add(m_cluster_size->get_profile());

  }
}

std::string FileProcessorsBase_modulo::get_suffix() const
{
  return "Modulo";
}

bool FileProcessorsBase_modulo::process_file(FileProberties* fileP)
{



  m_outputl->reset();

  auto file__ = xml_print("file");
  xml_print("fileName", fileP->m_fileName);


  m_input_file = FFile(
    FileName_t( fileP->m_fileName), 
    SubClassName_t(get_xml_input()->globalConfig.FitterFileType)
    );

  if (!m_input_file.isOpen())
  {
    return false;
  }


  m_dummy->cd();
  xml_print("fileName", fileP->m_fileName);

  xml_print("m_runNumber", fileP->m_runNumber);
  m_outputl->set_RunNumber(fileP->m_runNumber);


  xml_print("threshold", fileP->m_Threshold);
  m_outputl->set_Threshold(fileP->m_Threshold);

  xml_print("HV", fileP->m_HV);
  m_outputl->set_HV(fileP->m_HV);




  THE the(
    SubClassName_t(
    get_xml_input()->globalConfig.TrueHitExtractor), 
    TH_param()
    .set_fitterFile(m_input_file)
    .set_gear(get_gear())
    );

  m_trueHits = the.get_true_DUT_Hits();

  D2T d2t(
    SubClassName_t(
    get_xml_input()->globalConfig.DUT2TrackCorrelator), 
    D2T_prob()
    .set_gear(get_gear())
    .set_xmlFile(*get_xml_input())
    .set_trueHits(m_trueHits)
    .set_DUTHits(m_input_file.DUT_zs_data())
    );


  m_totalTrue_hits = d2t.getTotalTrueHits();
  m_truehits_withDUT = d2t.getTrueHitsWithDUT();

  m_efficiency = _MAKE_SHARED1(instrip_efficiency ,d2t.getTotalTrueHits(), d2t.getTrueHitsWithDUT(), modulo_x( 3), modulo_y(100000));

  m_res_efficiency = _MAKE_SHARED1(residual_efficiency,d2t.getTotalTrueHits(), m_input_file.DUT_zs_data(), residualCut_t(5), x_axis_def);

  m_cluster_size = _MAKE_SHARED1(Cluster_strip, d2t.getTrueHitsWithDUT(), m_input_file.DUT_zs_data(), max_cl_t(8), x_axis_def, modulo_t(3));



#ifdef _DEBUG
  m_input_file.getProcessorCollection()->loop(20000);
#else
  m_input_file.getProcessorCollection()->loop();
#endif // _DEBUG

  m_cluster_size->Draw_ClusterSize();


  push2outputEvent(*m_outputl, *m_efficiency->Draw_Efficiency(), *m_efficiency->Draw_true_hits(), ID_t(0));
  push2outputEvent(*m_outputl, *m_res_efficiency->Draw_residual_efficiency(), *m_res_efficiency->Draw_true_residuals(), ID_t(1));
  push2outputEvent(*m_outputl, *m_cluster_size->get_profile(), ID_t(2));
  m_outputl->fill();

  return true;
}
