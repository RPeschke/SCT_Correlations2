class make_mean{
    public:
void push(double newValue){
    m_val = (m_val * m_count + newValue) / (m_count +1);
    m_count+= 1;
}
double get() const{
    return m_val;
}

double m_val= 0,m_count=0;
};

TFile* eventMaker(std::string InputFile, std::string outputFile, int runNumber, double AnalysisNr, std::string configFile="../macros/analisys_db.csv") {
  auto m_file2 = Snew TFile(InputFile.c_str());
  auto raw_file = Snew EUTFile(m_file2);
  TFile * out_file1 = new TFile(outputFile.c_str(), "recreate");
  

  auto analisys_db = CSV_File(configFile, raw_file->getProcessorCollection(), "configFile");
  temp_var(analisys_db_pl) = analisys_db.get_plane();

  temp_var(analisys_db_cut) = analisys_db_pl[analisys_db_pl["AnalysisNr"] == AnalysisNr];
  temp_var(trueHits_proto) = raw_file->getCollection(collectionName_t("trueHits"))->getPlane(ID_t(0));
  temp_var(trigger) = raw_file->getCollection(collectionName_t("trigger"))->getPlane(ID_t(0));


  var(trigger_2)  =trigger[trigger["PlaneID"]==2];
  var(trigger_12)  =trigger[trigger["PlaneID"]==12];
  var(trigger_2_cross_12) = join(trigger_2, trigger_12, {"EventNumber","RunNumber"});

bool is_first=true;
make_mean TimeStamp1_first, TimeStamp2_first;
    trigger_2_cross_12["delta_mean"] = lambda3(TimeStamp1,TimeStamp2,EventNumber ){
        if (EventNumber <100){
            TimeStamp1_first.push(TimeStamp1-TimeStamp2);
        } else if ( TMath::Abs(TimeStamp1_first.get()  - (TimeStamp1-TimeStamp2)) < 1e8 ){
            TimeStamp1_first.push(TimeStamp1-TimeStamp2);
        }
        //TimeStamp2_first.push(TimeStamp2);

        return TimeStamp1_first.get();
    };
    trigger_2_cross_12["delta"] = lambda3(TimeStamp1,TimeStamp2,EventNumber ){
       

        return (TimeStamp1 )-  (TimeStamp2  ) ;
    };
  
  raw_file->getProcessorCollection()->loop();
  out_file1->Write();

  return out_file1;
}

void run_all_eventMaker(std::string dataFolder,  int AnalysisNr,std::vector<int> RunNumbers  ){


  for (int i=0; i< RunNumbers.size() ; ++i){
    std::cout << "eventMaker file: " << RunNumbers[i] << std::endl;
    std::string runNr_str =  std::to_string(RunNumbers[i]);
    auto outfile =  eventMaker(dataFolder+ "/eudaq_out_" +runNr_str +"_clustering.root", dataFolder+ "/eudaq_out_" + runNr_str + "_eventMaker.root",RunNumbers[i], AnalysisNr); 
    delete outfile;
  }
}