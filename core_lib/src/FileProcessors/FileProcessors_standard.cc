#include "sct/FileProcessors/FileProcessorsBase.hh"
#include "sct//FileProcessors/FileProcessors_standard.hh"
#include "TH2D.h"
#include <iostream>
#include "sct/lagacy/Draw.h"
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
#include "sct/lagacy/SCT_helpers.hh"
#include "sct/analysis/residual_efficiency.hh"

#define  SCT_THROW(X)  std::cout<<X<<std::endl

template <typename T>
void xml_print(const std::string& tag, const T& value) {
  std::cout << tag << ":  " << value << std::endl;
}


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
    m_dummy->Close("R");
  }

}

int FileProcessors_standard::DrawResidual(Double_t min_X, Double_t max_X)
{
  m_Residual = std::make_shared<TH1D>(
    "residual",
    "residual",
    100,
    min_X,
    max_X
    );


  return Draw(
    m_corr->getResidual(),
    DrawOption()
    .draw_x()
    .cut_x(min_X, max_X)
    .output_object(m_Residual.get())
    );
}

int FileProcessors_standard::DrawResidual()
{
  auto ret = Draw(
    m_corr->getResidual(),
    DrawOption().draw_x()
    );

  TH1* h = dynamic_cast<TH1*>(gPad->GetPrimitive("htemp"));
  h->SetTitle("residual");
  return ret;
}

int FileProcessors_standard::DrawResidualVsEvent(Double_t min_X, Double_t max_X)
{
  m_ResidualVsEvent = std::make_shared<TH2D>(
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
  m_resVSMissing = std::make_shared<TH2D>(
    "ResidualVsMissingCordinate",
    "Residual Vs Missing Coordinate",
    100, 0, 0,
    100, min_X, max_X
    );




  auto ret = Draw(
    m_corr->getResidualVsMissing(),
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
    m_corr->getResidualVsMissing(),
    DrawOption()
    .draw_x_VS_y()
    .opt_colz()
    );




  return ret;
}

int FileProcessors_standard::Draw_Efficinecy_map()
{
  m_Efficieny_trueHits = std::make_shared<TH1D>(
    "total",
    "total",
    get_xml_input()->globalConfig.NumberOfBins, -0.5, get_xml_input()->globalConfig.NumberOfStrips - 0.5
    );

  Draw(
    m_corr->getTotalTrueHits(),
    DrawOption()
    .draw_x()
    .output_object(m_Efficieny_trueHits.get())
    );

  m_Efficieny_map = std::make_shared<TH1D>(
    "Efficiency",
    "Efficiency",
    get_xml_input()->globalConfig.NumberOfBins, -0.5, get_xml_input()->globalConfig.NumberOfStrips - 0.5
    );

  auto n = Draw(
    m_corr->getTrueHitsWithDUT(),
    DrawOption()
    .draw_x()
    .output_object(m_Efficieny_map.get())
    );
  
  auto e = SCT_helpers::calc_efficiency(m_Efficieny_trueHits.get(), m_Efficieny_map.get());
  auto eth2d = dynamic_cast<TH1D*>(e);

  m_Efficieny_map = std::shared_ptr<TH1D>(eth2d);
  // m_Efficieny_map->Divide(m_Efficieny_trueHits.get());

  m_Efficieny_map->Draw();
  return n;
}

int FileProcessors_standard::Draw_Hit_map()
{
  m_Hits_total = std::make_shared<TH1D>(
    "total",
    "total",
    get_xml_input()->globalConfig.NumberOfBins, -0.5, get_xml_input()->globalConfig.NumberOfStrips - 0.5
    );

  return  Draw(
    m_corr->getTotalTrueHits(),
    DrawOption()
    .draw_x()
    .output_object(m_Hits_total.get())
    );
}

int FileProcessors_standard::Draw_DUT_Hits_map()
{
  m_Hits_with_DUT_Hits = std::make_shared<TH1D>(
    "DUT",
    "DUT",
    get_xml_input()->globalConfig.NumberOfBins, -0.5, get_xml_input()->globalConfig.NumberOfStrips - 0.5
    );

  return Draw(
    m_corr->getTrueHitsWithDUT(),
    DrawOption()
    .draw_x()
    .output_object(m_Hits_with_DUT_Hits.get())
    );
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
    outPutFile->Add(m_Efficieny_map.get());
    outPutFile->Add(m_Efficieny_trueHits.get());
    outPutFile->Add(m_Hits_total.get());
    outPutFile->Add(m_Hits_with_DUT_Hits.get());
    outPutFile->Add(m_ResidualVsEvent.get());
    outPutFile->Add(m_resVSMissing.get());
    outPutFile->Add(m_Residual.get());
  }

}

bool FileProcessors_standard::process_file(FileProberties* fileP)
{
  process_reset();
//  auto file_PRINTOUT = xml_print("file");



  std::cout << fileP->getTfile()->GetName() << std::endl;

  XML_imput_file xfile("C:/Users/Argg/Documents/Neuer Ordner/gitHub/SCT_correlations2/DEVICE_1_ASIC_on_Position_5_150V.xml");

  std::cout << "1" << std::endl;

  m_input_file = FFile("C:/Users/Argg/Documents/Neuer Ordner/gitHub/SCT_correlations2/run000872_fitter.root", "MAY15");
  std::cout << "2" << std::endl;
  new TFile("test.root", "recreate");
  std::cout << "3" << std::endl;
  Xgear gear("D:/sct_corr_2_test/DEVICE_2_ASIC_on_Position_5_400V/alignedGear-check-iter2-run000703_with_plane20.xml");
  std::cout << "4" << std::endl;
  THE the("MAY15", TH_param().set_fitterFile(m_input_file).set_gear(&gear));
  std::cout << "5" << std::endl;
  m_trueHits = the.get_true_DUT_Hits();
  std::cout << "6" << std::endl;


  D2T d2t("MAY15", D2T_prob().set_gear(&gear).set_xmlFile(&xfile).set_trueHits(m_trueHits).set_DUTHits(m_input_file.DUT_zs_data()));



  std::cout << "7" << std::endl;

//   efficiency m(d2t.getTotalTrueHits(), d2t.getTrueHitsWithDUT());
//    m.DrawTrueHits();
  residual_efficiency rr(d2t.getTotalTrueHits(),m_input_file.DUT_zs_data(),400,x_axis_def);

  m_residual = xy_pro::residual(
    m_input_file.DUT_fitted_local_GBL().get_x(),
    m_input_file.DUT_hit_local().get_x(),
    processor_prob().setName("residualVSEvent")
    );
  std::cout << "8" << std::endl;


#ifdef _DEBUG
  m_input_file->getProcessorCollection()->loop(20000);
#else
  m_input_file.getProcessorCollection()->loop();
#endif // _DEBUG

  std::cout << "9" << std::endl;

  Draw_Efficinecy_map();
  std::cout << "10" << std::endl;
  extract_hitMap();
  std::cout << "11" << std::endl;
  extract_efficiency();
  std::cout << "12" << std::endl;
  extract_residual();
  std::cout << "13" << std::endl;
  extract_rotation();
  std::cout << "14" << std::endl;
  m_outputl->fill();
  std::cout << "15" << std::endl;
  return true;
}
double BinNomialSigma(double totalHits, double DUTHits) {
  return sqrt((DUTHits / totalHits)*(1 - (DUTHits / totalHits))*(1 / totalHits));
}
void FileProcessors_standard::extract_efficiency()
{
  double totalHits = (double)Draw(m_corr->getTotalTrueHits(),
    DrawOption()
    .cut_x(get_xml_input()->globalConfig.AvtiveStrips.getMin(),
      get_xml_input()->globalConfig.AvtiveStrips.getMax())
    );

  xml_print("TotalNumOfEvents", totalHits);
  m_outputl->set_TotalNumOfEvents(totalHits);

  double DUTHits = Draw(m_corr->getTrueHitsWithDUT(),
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
  for (Int_t i = 0; i < m_Efficieny_map->GetNbinsX(); ++i) {

    m_outputl->push(
      m_Efficieny_map->GetBinCenter(i),        //xPosition
      1,                               //yPosition   
      m_Efficieny_map->GetBinContent(i),       //Efficiency
      BinNomialSigma(
        m_Efficieny_trueHits->GetBinContent(i),
        m_Efficieny_map->GetBinContent(i)
        ),
      m_Efficieny_trueHits->GetBinContent(i)    //Total True Hits
      );
  }
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
  auto f1 = SCT_helpers::LinearFit_Of_Profile(h, 1);
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
