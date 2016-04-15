#include "sct/lcio/lcio_output.hh"
#if 0

class GBL_trackOutput :lcio_output {
public:
  typedef EUTelTrack * data_t;
  GBL_trackOutput(Parameter_ref param_);
  static bool hasCollection(EVENT::LCEvent* evt);
  ~GBL_trackOutput();
  virtual void pushEvent(const EVENT::LCEvent* ev) override;;
  void beginEvent();
  void endEvent();
  void processTrack(EUTelTrack& trc);
  void processPlanes(EUTelState& pln);
  void pushHit();


  double x;
  double y;

  double ID;

  double phi;
  double theta;



  double chi2;
  double ndf;
  EUTelReaderGenericLCIO lc_reader;
  int m_event_nr;
  std::string m_name, m_type;
  std::vector<double> m_x, m_y, m_id,
    m_chi2, m_ndf, m_phi, m_theta;
};

GBL_trackOutput::GBL_trackOutput(Parameter_ref param_):lcio_output(param_)
{
  if (!gFile_)
  {
    std::cout << "create file with name: " << gStupitNameForShittyROOTFile << std::endl;
    gFile_ = new TFile(gStupitNameForShittyROOTFile.c_str(), "RECREATE");
  }
  m_tree = new TTree(name.c_str(), name.c_str());
  m_tree->SetDirectory(gFile_->GetDirectory("/"));

  m_tree->Branch("ID", &m_id);
  m_tree->Branch("x", &m_x);
  m_tree->Branch("y", &m_y);


  m_tree->Branch("chi2", &m_chi2);
  m_tree->Branch("ndf", &m_ndf);
  m_tree->Branch("phi", &m_phi);
  m_tree->Branch("theta", &m_theta);

  m_tree->Branch("event_nr", &m_event_nr);
}

bool GBL_trackOutput::hasCollection(EVENT::LCEvent* evt)
{
  const std::vector<std::string>*  names = evt->getCollectionNames();
  std::vector< std::string >::const_iterator it = std::find(names->begin(), names->end(), "GBL");

  return true;
}

GBL_trackOutput::~GBL_trackOutput()
{

}

void GBL_trackOutput::pushEvent(const EVENT::LCEvent* ev)
{
  beginEvent();
  try {
    std::vector<EUTelTrack> tr = lc_reader.getTracks(ev, "tracks");
    //        std::cout<< "Track size: " <<tr.size() << std::endl;

    for (size_t i = 0; i < tr.size();++i)
    {
      tr[i].print();
      processTrack(tr[i]);

    }
  }
  catch (DataNotAvailableException e) {
    streamlog_out(MESSAGE0) << " collection not available" << std::endl;
  }

  endEvent();
}

void GBL_trackOutput::beginEvent()
{
  m_x.clear();
  m_y.clear();
  m_id.clear();
  m_phi.clear();
  m_theta.clear();
  m_ndf.clear();
  m_chi2.clear();
  ++m_event_nr;
}

void GBL_trackOutput::endEvent()
{
  //  std::cout<<"Fill GBL"<<std::endl;

}

void GBL_trackOutput::processTrack(EUTelTrack& trc)
{
  //      std::cout<<"Track" <<std::endl;

  std::vector<EUTelState>& planes = trc.getStates();

  chi2 = trc.getChi2();
  ndf = trc.getNdf();
  //    std::cout<<"Planes size " << planes.size() << std::endl;
  for (size_t i = 0; i < planes.size(); ++i) {
    //     std::cout<<"Plane " << i  <<std::endl;

    processPlanes(planes[i]);
  }
}

void GBL_trackOutput::processPlanes(EUTelState& pln)
{
  x = pln.getPosition()[0];
  y = pln.getPosition()[1];

  ID = static_cast<double>(pln.getLocation());
  //   std::cout<<"ID " << ID <<std::endl;

  phi = pln.getDirLocalX() / pln.getDirLocalZ();
  theta = pln.getDirLocalY() / pln.getDirLocalZ();
  //  std::cout<<"Push back" <<std::endl;


  pushHit();
}

void GBL_trackOutput::pushHit()
{
  m_x.push_back(x);
  m_y.push_back(y);
  m_id.push_back(ID);
  m_phi.push_back(phi);
  m_theta.push_back(theta);

  m_ndf.push_back(ndf);
  m_chi2.push_back(chi2);
}
#endif
