#include "sct/FileProcessors/FileProcessorsBase.hh"
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

#define  SCT_THROW(X)  std::cout<<X<<std::endl

template <typename T>
void xml_print(const std::string& tag, const T& value) {
  std::cout << tag << ":  " << value << std::endl;
}
class FileProcessors_standard:public FileProcessorsBase {
public:
  FileProcessors_standard(Parameter_ref par);
  virtual ~FileProcessors_standard();
  Long64_t DrawResidual(Double_t min_X, Double_t max_X);
  Long64_t DrawResidual();
  Long64_t DrawResidualVsEvent(Double_t min_X, Double_t max_X);
  Long64_t DrawResidualVsEvent();
  Long64_t DrawResidualVsMissingCordinate(Double_t min_X, Double_t max_X);
  Long64_t DrawResidualVsMissingCordinate();
  Long64_t Draw_Efficinecy_map();
  Long64_t Draw_Hit_map();
  Long64_t Draw_DUT_Hits_map();
  TH2D* getResidualVsMissingCordinate();
  virtual void saveHistograms(TFile* outPutFile, double residual_min, double residual_max) ;

private:

  virtual  bool process_file(FileProberties* fileP) override;
  void extract_efficiency();
  void extract_hitMap();
  void extract_residual();
  void extract_rotation();
  void process_reset();



  virtual std::string get_suffix() const override;


  std::shared_ptr<TH1D> m_Residual;
  std::shared_ptr<TH1D> m_Hits_total;
  std::shared_ptr<TH1D> m_Hits_with_DUT_Hits;
  std::shared_ptr<TH1D> m_Efficieny_map;
  std::shared_ptr<TH1D> m_Efficieny_trueHits;
  std::shared_ptr<TH2D> m_resVSMissing;
  std::shared_ptr<TH2D> m_ResidualVsEvent;
  
  
  
  std::unique_ptr<fitterFile> m_input_file;
  xy_plane m_trueHits , m_residual;
  std::unique_ptr<DUT_2_Track_correlator> m_corr;




  TFile* m_dummy = nullptr;
  std::shared_ptr <TF1> m_fit;

};

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

Long64_t FileProcessors_standard::DrawResidual(Double_t min_X, Double_t max_X)
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

Long64_t FileProcessors_standard::DrawResidual()
{
  auto ret = Draw(
    m_corr->getResidual(),
    DrawOption().draw_x()
    );

  TH1* h = dynamic_cast<TH1*>(gPad->GetPrimitive("htemp"));
  h->SetTitle("residual");
  return ret;
}

Long64_t FileProcessors_standard::DrawResidualVsEvent(Double_t min_X, Double_t max_X)
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

Long64_t FileProcessors_standard::DrawResidualVsEvent()
{
  auto ret = Draw(
    m_residual,
    DrawOption().draw_x_VS_y()
    );

  TH2* h = dynamic_cast<TH2*>(gPad->GetPrimitive("htemp"));
  h->SetTitle("Residual Vs Event");

  return ret;
}

Long64_t FileProcessors_standard::DrawResidualVsMissingCordinate(Double_t min_X, Double_t max_X)
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

Long64_t FileProcessors_standard::DrawResidualVsMissingCordinate()
{
  auto ret = Draw(
    m_corr->getResidualVsMissing(),
    DrawOption()
    .draw_x_VS_y()
    .opt_colz()
    );




  return ret;
}

Long64_t FileProcessors_standard::Draw_Efficinecy_map()
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
 // auto e = SCT_helpers::calc_efficiency(m_Efficieny_trueHits.get(), m_Efficieny_map.get());
 // auto eth2d = dynamic_cast<TH1D*>(e);

//  m_Efficieny_map = std::shared_ptr<TH1D>(eth2d);
  // m_Efficieny_map->Divide(m_Efficieny_trueHits.get());

  m_Efficieny_map->Draw();
  return n;
}

Long64_t FileProcessors_standard::Draw_Hit_map()
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

Long64_t FileProcessors_standard::Draw_DUT_Hits_map()
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



 

  XML_imput_file xfile("C:/Users/Argg/Documents/Neuer Ordner/gitHub/SCT_correlations2/DEVICE_1_ASIC_on_Position_5_150V.xml");

  m_input_file = create_Fitter_file("C:/Users/Argg/Documents/Neuer Ordner/gitHub/SCT_correlations2/run000872_fitter.root", "MAY15");
  new TFile("test.root", "recreate");

  auto gear = Xgear("C:/Users/Argg/Documents/Neuer Ordner/gitHub/SCT_correlations2/alignedGear-check-iter2-run000703_with_plane20.xml");

  auto tr = create_truehitExtractor(TH_param().set_fitterFile(m_input_file.get()).set_gear(&gear), "MAY15");
  m_trueHits = tr->get_true_DUT_Hits();


  m_corr = create_DUT_2_Track_correlator(D2T_prob().set_gear(&gear).set_xmlFile(&xfile).set_trueHits(m_trueHits).set_DUTHits(m_input_file->DUT_zs_data()), "MAY15");





  m_residual = residual(
    m_input_file->DUT_fitted_local_GBL().get_x(),
    m_input_file->DUT_hit_local().get_x(),
    processor_prob().setName("residualVSEvent")
    );



#ifdef _DEBUG
  m_input_file->getProcessorCollection()->loop(20000);
#else
  m_input_file->getProcessorCollection()->loop();
#endif // _DEBUG



  Draw_Efficinecy_map();

  extract_hitMap();
  extract_efficiency();
  extract_residual();
  extract_rotation();

  m_outputl->fill();
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
//   DrawResidualVsMissingCordinate(-10, 10);
//   auto h = getResidualVsMissingCordinate();
//   auto f1 = SCT_helpers::LinearFit_Of_Profile(h, sct_type::procent_t(1));
//   auto rot = TMath::ATan(f1.GetParameter("p1"));
//   m_outputl->set_rotation(rot);
//   xml_print("rotation", rot);
}

void FileProcessors_standard::process_reset()
{
  m_outputl->reset();
  
}

std::string FileProcessors_standard::get_suffix() const
{
  return "_standard";
}
