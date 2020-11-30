

TFile* clustering(std::string InputFile, std::string outputFile, int runNumber, double AnalysisNr, std::string configFile="../macros/analisys_db.csv") {


  auto m_file2 = Snew TFile(InputFile.c_str());
  auto raw_file = Snew EUTFile(m_file2);
  TFile * out_file1 = new TFile(outputFile.c_str(), "recreate");
  temp_var(raw_data) = raw_file->getCollection("all_grouped")->getPlane(0);
  auto analisys_db = CSV_File(configFile, raw_file->getProcessorCollection(), "configFile");

  temp_var(analisys_db_pl) = analisys_db.get_plane();
  temp_var(analisys_db_cut) = analisys_db_pl[analisys_db_pl["AnalysisNr"] == AnalysisNr];
  temp_var(raw_data_join_proto)  =  join(raw_data, analisys_db_cut, {"PlaneID","RunNumber"});

 // raw_data_join_proto["TimeStamp_corrected"] = lambda3(TimeStamp,TS_offset,TS_slope){ 
 //     return  TimeStamp   + (TS_offset +  TS_slope*TimeStamp) ; 
 // };
  temp_var(raw_data_join) = sct::drop(raw_data_join_proto, {"TS_offset", "TS_slope"}  );

  temp_var(trigger_prot) = raw_data_join[ raw_data_join["TriggerASIC"] ==raw_data_join["y"]   && raw_data_join["TriggerChannel"] ==raw_data_join["x"] ];
  
  var(trigger) = sct::select(trigger_prot, {"TimeStamp","PlaneID",
                                            "Charge","RunNumber",
                                            "EventNumber",}  );

 // var(trigger_unique) = sct::enumerate_occurrence( trigger, {"TimeStamp"});

  temp_var(data) =raw_data_join[ !(raw_data_join["TriggerASIC"] ==raw_data_join["y"]   && raw_data_join["TriggerChannel"] ==raw_data_join["x"]) ];

  temp_var(data_joined_with_trigger_valid_planes) = join(data, trigger, {"PlaneID" , "Charge","RunNumber","EventNumber"});
  

  data_joined_with_trigger_valid_planes["isTriggered"] = lambda6(
            TimeStamp2, TimeStamp1, 
            LookbackStart_fine, LookbackStop_fine, 
            LookbackStart, LookbackStop  ) {

    auto delta = TimeStamp2-TimeStamp1;
    if(LookbackStart_fine < delta && delta < LookbackStop_fine){
        return 1;
    }
    if(LookbackStart < delta &&  delta < LookbackStop){
        return 2;
    }
    return 0;
  };
  temp_var(ref_hits_proto) = data_joined_with_trigger_valid_planes[data_joined_with_trigger_valid_planes["isTriggered"] > 0];
  var(ref_hits) = sct::select(ref_hits_proto, {"x","y","TimeStamp1","TimeStamp2","isTriggered", "Charge","PlaneID"}  );

  //var(ref_hits_unique) = sct::enumerate_occurrence( ref_hits, {"TimeStamp2"});


  temp_var(trueHits_proto) = data_joined_with_trigger_valid_planes[data_joined_with_trigger_valid_planes["isTriggered"] == 1];
  trueHits_proto["TimeStamp"] = lambda1(TimeStamp2) {return TimeStamp2;};


  var(trueHits) = sct::select(trueHits_proto, {"RunNumber","EventNumber","PlaneID","x","y",
                                            "Charge","TimeStamp"}  );

//  var(clustered) = sct::clustering(trueHits, 
//                       cl_conf("position1", 1)+ 
//                        cl_conf("axis1", 0) +  
//                        cl_conf("PlaneID", 0)+
//                        cl_conf("Charge", 0)
//                    );
  raw_file->getProcessorCollection()->loop();
  out_file1->Write();
  return out_file1;
}

void run_all_clustering(std::string dataFolder, std::vector<int> RunNumbers, int AnalysisNr ){
  for (int i=0; i< RunNumbers.size() ; ++i){
    std::cout << "clustering file: " << RunNumbers[i] << std::endl;
    std::string runNr_str =  std::to_string(RunNumbers[i]);
    auto outfile =  clustering(dataFolder+ "/eudaq_out_" +runNr_str +".root", dataFolder+ "/eudaq_out_" + runNr_str + "_clustering.root",RunNumbers[i], AnalysisNr); 
    delete outfile;
  }
}