#include "sct/FileProcessors/FileProcessorsBase.hh"
#include "sct//FileProcessors/FileProcessors_standard.hh"
#include "TH2D.h"
#include <iostream>
#include "sct/legacy/Draw.h"
#include "TVirtualPad.h"
#include "TCanvas.h"
#include "sct/predef/DUT_2_Track_correlator.hh"
#include "sct/predef/truehitExtractor.hh"
#include "sct/predef/fitterFile.hh"
#include "sct/xy_processors/processor_residual.hh"
#include "sct/ProcessorCollection.h"
#include "TGraph.h"
#include "TF1.h"
#include "sct/xy_processors/xy_pro.hh"
#include "TMath.h"
#include "sct/legacy/SCT_helpers.hh"
#include "sct/analysis/residual_efficiency.hh"
#include "sct/internal/sct_exceptions.hh"





register_file_processor(FileProcessors_standard, "standard");
FileProcessors_standard::FileProcessors_standard(Parameter_ref par)
{

  m_dummy = new TFile("dummy1.root", "recreate");

  if (!m_dummy->IsOpen()) {
    SCT_THROW("unable to open file: dummy1.root");
  }
}

FileProcessors_standard::~FileProcessors_standard()
{
  if (m_dummy) {
    m_dummy->Write();
   // m_dummy->Close("R");
  }

}

int FileProcessors_standard::DrawResidual(Double_t min_X, Double_t max_X)
{
  m_Residual = _MAKE_SHARED1(TH1D,
    "residual",
    "residual",
    100,
    min_X,
    max_X
    );


  return Draw(
    m_residual,
    DrawOption()
    .draw_x()
    .cut_x(min_X, max_X)
    .output_object(m_Residual.get())
    );
}

int FileProcessors_standard::DrawResidual()
{
  auto ret = Draw(
    m_residual,
    DrawOption().draw_x()
    );

  TH1* h = dynamic_cast<TH1*>(gPad->GetPrimitive("htemp"));
  h->SetTitle("residual");
  return ret;
}

int FileProcessors_standard::DrawResidualVsEvent(Double_t min_X, Double_t max_X)
{
  m_ResidualVsEvent = _MAKE_SHARED1(TH2D,
    "ResidualVsEvent",
    "Residual Vs Event",
    100, 0, 0,
    100, min_X, max_X
    );

  return Draw(
    m_residual,
    DrawOption()
    .draw_x_VS_y()
    .cut_x(min_X, max_X)
    .output_object(m_ResidualVsEvent.get())
    .opt_colz()
    );
}

int FileProcessors_standard::DrawResidualVsEvent()
{
  auto ret = Draw(
    m_residual,
    DrawOption().draw_x_VS_y()
    );

  TH2* h = dynamic_cast<TH2*>(gPad->GetPrimitive("htemp"));
  h->SetTitle("Residual Vs Event");

  return ret;
}

int FileProcessors_standard::DrawResidualVsMissingCordinate(Double_t min_X, Double_t max_X)
{
  m_resVSMissing = _MAKE_SHARED1(TH2D,
    "ResidualVsMissingCordinate",
    "Residual Vs Missing Coordinate",
    100, 0, 0,
    100, min_X, max_X
    );




  auto ret = Draw(
    m_ResidualVsMissing,
    DrawOption()
    .draw_x_VS_y()
    .cut_x(min_X, max_X)
    .output_object(m_resVSMissing.get())
    .opt_colz()
    );


  return ret;
}

int FileProcessors_standard::DrawResidualVsMissingCordinate()
{
  auto ret = Draw(
    m_ResidualVsMissing,
    DrawOption()
    .draw_x_VS_y()
    .opt_colz()
    );




  return ret;
}

int FileProcessors_standard::Draw_Efficinecy_map()
{
  m_Efficieny_map = m_efficiency->DrawEfficiency(get_xml_input()->globalConfig.NumberOfBins, 0, get_xml_input()->globalConfig.NumberOfBins);
  return 0;
}

int FileProcessors_standard::Draw_Hit_map()
{
  m_Hits_total = m_efficiency->DrawTrueHits(get_xml_input()->globalConfig.NumberOfBins, 0, get_xml_input()->globalConfig.NumberOfBins);
  return 0;
}

int FileProcessors_standard::Draw_DUT_Hits_map()
{
  m_efficiency->DrawDUTHits(get_xml_input()->globalConfig.NumberOfBins, 0, get_xml_input()->globalConfig.NumberOfBins);
  return 0;
}

TH2D* FileProcessors_standard::getResidualVsMissingCordinate()
{
  return m_resVSMissing.get();
}



void FileProcessors_standard::saveHistograms(TFile* outPutFile, double residual_min, double residual_max)
{

#ifdef _DEBUG
  new TCanvas();
#endif // _DEBUG
  DrawResidual(residual_min, residual_max);



#ifdef _DEBUG
  new TCanvas();
#endif // _DEBUG

  Draw_DUT_Hits_map();


#ifdef _DEBUG
  new TCanvas();
#endif // _DEBUG
  Draw_Hit_map();

#ifdef _DEBUG
  new TCanvas();
#endif // _DEBUG

  Draw_Efficinecy_map();

#ifdef _DEBUG
  new TCanvas();
#endif // _DEBUG

  DrawResidualVsEvent(residual_min, residual_max);

#ifdef _DEBUG
  new TCanvas();
#endif // _DEBUG


  DrawResidualVsMissingCordinate(residual_min, residual_max);

  if (outPutFile) {
    outPutFile->Add(m_Efficieny_map);

    outPutFile->Add(m_Hits_total);

    outPutFile->Add(m_ResidualVsEvent.get());
    outPutFile->Add(m_resVSMissing.get());
    outPutFile->Add(m_Residual.get());
  }

}

bool FileProcessors_standard::process_file(FileProberties* fileP)
{
  process_reset();


  auto file__ = xml_print("file"); 
  xml_print("fileName",fileP->m_fileName );



  m_input_file = FFile(
    FileName_t(fileP->m_fileName), 
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
    SubClassName_t(get_xml_input()->globalConfig.TrueHitExtractor),
    TH_param().set_fitterFile(m_input_file).set_gear(get_gear())
    );

  m_trueHits = the.get_true_DUT_Hits();

  D2T d2t(
    SubClassName_t(get_xml_input()->globalConfig.DUT2TrackCorrelator), 
    D2T_prob()
    .set_gear(get_gear())
    .set_xmlFile(*get_xml_input())
    .set_trueHits(m_trueHits)
    .set_DUTHits(m_input_file.DUT_zs_data())
    );

  m_totalTrue_hits = d2t.getTotalTrueHits();
  m_truehits_withDUT = d2t.getTrueHitsWithDUT();
  m_efficiency = _MAKE_SHARED1(efficiency, d2t.getTotalTrueHits(), d2t.getTrueHitsWithDUT());
  m_ResidualVsMissing = d2t.getResidualVsMissing();



  m_residual = xy_pro::residual(
    m_input_file.DUT_fitted_local_GBL().get_x(),
    m_input_file.DUT_hit_local().get_x(),
    processor_prob().setName(processorName_t("residualVSEvent")).save2Disk()
    );


#ifdef _DEBUG
  m_input_file.getProcessorCollection()->loop(20000);
#else
  m_input_file.getProcessorCollection()->loop();
#endif // _DEBUG


  Draw_Efficinecy_map();
  extract_hitMap();
  extract_efficiency();
  extract_residual();
  extract_rotation();
  m_outputl->fill();
  
  return true;
}

void FileProcessors_standard::extract_efficiency()
{
  double totalHits = (double)Draw(m_totalTrue_hits,
    DrawOption()
    .cut_x(get_xml_input()->globalConfig.AvtiveStrips.getMin(),
      get_xml_input()->globalConfig.AvtiveStrips.getMax())
    );

  xml_print("TotalNumOfEvents", totalHits);
  m_outputl->set_TotalNumOfEvents(totalHits);

  double DUTHits = Draw(m_truehits_withDUT,
    DrawOption()
    .cut_x(get_xml_input()->globalConfig.AvtiveStrips.getMin(),
      get_xml_input()->globalConfig.AvtiveStrips.getMax())
    );
  xml_print("DUTHits", DUTHits);

  xml_print("Efficiency", DUTHits / totalHits);
  m_outputl->set_Total_efficiency(DUTHits / totalHits);


  auto Error_efficiency = BinNomialSigma(totalHits,
    DUTHits);

  xml_print("Error_efficiency", Error_efficiency);
  m_outputl->set_Error_efficiency(Error_efficiency);

}

void FileProcessors_standard::extract_hitMap()
{
  auto eff = m_efficiency->DrawEfficiency(get_xml_input()->globalConfig.NumberOfBins, 0, get_xml_input()->globalConfig.NumberOfBins);
  auto true_hits = m_efficiency->DrawTrueHits(get_xml_input()->globalConfig.NumberOfBins, 0, get_xml_input()->globalConfig.NumberOfBins);

  push2outputEvent(*m_outputl, *eff, *true_hits, ID_t(0));
 
}

void FileProcessors_standard::extract_residual()
{
  DrawResidual(-3, 3);


  TF1 f("f1", "gaus");

  m_Residual->Fit(&f, "Q");
  {
    auto residual_sigma = f.GetParameter("Sigma");
    xml_print("residual_sigma", residual_sigma);
    m_outputl->set_residual(residual_sigma);
  }
  {
    auto residual_mean = f.GetParameter("Mean");
    xml_print("residual_mean", residual_mean);
    m_outputl->set_offset(residual_mean);
  }
}

void FileProcessors_standard::extract_rotation()
{
  DrawResidualVsMissingCordinate(-10, 10);
  auto h = getResidualVsMissingCordinate();
  auto f1 = SCT_helpers::LinearFit_Of_Profile(h, procent_t(1));
  auto rot = TMath::ATan(f1.GetParameter("p1"));
  m_outputl->set_rotation(rot);
  xml_print("rotation", rot);
}

void FileProcessors_standard::process_reset()
{
  m_outputl->reset();

}

std::string FileProcessors_standard::get_suffix() const
{
  return "_standard";
}
