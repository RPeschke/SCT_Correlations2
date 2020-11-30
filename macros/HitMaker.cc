


TFile* HitMaker(std::string InputFile, std::string outputFile, int runNumber, double AnalysisNr, std::string configFile="../macros/analisys_db.csv") {
  auto m_file2 = Snew TFile(InputFile.c_str());
  auto raw_file = Snew EUTFile(m_file2);
  TFile * out_file1 = new TFile(outputFile.c_str(), "recreate");
  

  auto analisys_db = CSV_File(configFile, raw_file->getProcessorCollection(), "configFile");
  temp_var(analisys_db_pl) = analisys_db.get_plane();
  temp_var(analisys_db_cut) = analisys_db_pl[analisys_db_pl["AnalysisNr"] == AnalysisNr];
  temp_var(trueHits_proto) = raw_file->getCollection(collectionName_t("trueHits"))->getPlane(ID_t(0));
  temp_var(trigger) = raw_file->getCollection(collectionName_t("trigger"))->getPlane(ID_t(0));
  
  var(trigger_unqiue) = sct::first_occurrence(trigger, {"TimeStamp" });
  var(trueHits_proto_unqiue) = sct::first_occurrence(trueHits_proto, {"TimeStamp" });


  temp_var(trigger_2)  =trigger[trigger["PlaneID"] ==2 ];
  temp_var(trigger_12) =trigger[trigger["PlaneID"] ==12 ];

  var(trigger_2_unqiue) = sct::first_occurrence(trigger_2, {"TimeStamp" });
  var(trigger_12_unqiue) = sct::first_occurrence(trigger_12, {"TimeStamp" });


  var(trueHits_proto_2) =  trueHits_proto[trueHits_proto["PlaneID"] == 2];
  var(trueHits_proto_2_unqiue) = sct::first_occurrence(trueHits_proto_2, {"TimeStamp" });
  var(trueHits_proto_12) =  trueHits_proto[trueHits_proto["PlaneID"] == 12];
  var(trueHits_proto_12_unqiue) = sct::first_occurrence(trueHits_proto_12, {"TimeStamp" });


  temp_var(trueHits_proto1) = join(trueHits_proto, analisys_db_cut, {"PlaneID","RunNumber"});
  

  trueHits_proto1["axis"] = lambda1(y) { return y > 5;};
  trueHits_proto1["position"] = lambda2(x, y) { return x+ 16*(y  -6*(y > 5));  };

  trueHits_proto1["TimeStamp_c"] = lambda3(TimeStamp,TS_offset,TS_slope){ 
      return  TimeStamp   + (TS_offset +  TS_slope*TimeStamp) ; 
  };

  var(trueHits) = sct::select(trueHits_proto1, {
        "RunNumber",
        "EventNumber",
        "PlaneID", "x",
        "y","Charge","TimeStamp",
        "AnalysisNr","axis","position","TS_Cut",
        "TimeStamp_c"}  
   );

  temp_var(trueHits_x) = trueHits[trueHits["axis"] ==0];
  temp_var(trueHits_y) = trueHits[trueHits["axis"] == 1];


    var(trueHits_x_2_unqiue) = sct::first_occurrence(trueHits_x[trueHits_x["PlaneID"] == 2], {"TimeStamp" });
    var(trueHits_x_12_unqiue) = sct::first_occurrence(trueHits_x[trueHits_x["PlaneID"] == 12], {"TimeStamp" });

    var(trueHits_y_2_unqiue) = sct::first_occurrence(trueHits_y[trueHits_y["PlaneID"] == 2], {"TimeStamp" });
    var(trueHits_y_12_unqiue) = sct::first_occurrence( trueHits_y[trueHits_y["PlaneID"] == 12], {"TimeStamp" });

  temp_var(trueHits_2d_canditates_prot) = join(trueHits_x, trueHits_y, {"PlaneID" , "Charge" ,"RunNumber","EventNumber","AnalysisNr"});

  temp_var(trueHits_2d_canditates)  =  trueHits_2d_canditates_prot[lambda2(TimeStamp1,TimeStamp2){ return TMath::Abs(TimeStamp1 - TimeStamp2) <10; } ];
  
  
  trueHits_2d_canditates["pos_x"] = lambda1(position1){ return position1; };
  
  trueHits_2d_canditates["pos_y"] = lambda1(position2){ return position2; };

  trueHits_2d_canditates["TimeStamp_c"] = lambda1(TimeStamp_c1){ return TimeStamp_c1; };
  trueHits_2d_canditates["TimeStamp"] = lambda1(TimeStamp1){ return TimeStamp1; };

  var(trueHits_2d) = sct::drop(trueHits_2d_canditates, {
        "position1","position2",
        "TimeStamp1", "TimeStamp2",
        "TimeStamp_c1", "TimeStamp_c2",
        "axis11","axis12","RunNumber11",
        "RunNumber12","EventNumber11",
        "EventNumber12","index1","index2" }  
        );

  var(trueHits_2d_plane_2) = trueHits_2d[trueHits_2d["PlaneID"] ==2];
  var(trueHits_2d_plane_2_unique) = sct::first_occurrence( trueHits_2d_plane_2, {"TimeStamp" });
  var(trueHits_2d_plane_12) = trueHits_2d[trueHits_2d["PlaneID"] == 12];
  var(trueHits_2d_plane_12_unique) = sct::first_occurrence( trueHits_2d_plane_12, {"TimeStamp" });



  var(trueHits_2plane_2d_canditates) = join(
      trueHits_2d_plane_2, trueHits_2d_plane_12, 
      {"RunNumber","EventNumber","AnalysisNr"}
    );



//  trueHits_2plane_2d_canditates["isInTime"] = lambda3(TimeStamp1,TimeStamp2,TS_Cut111){ 
//      return  TMath::Abs(TimeStamp1 - TimeStamp2) <  TS_Cut111 ; 
//  }; 
      
  var(trueHits_2plane_2d) = trueHits_2plane_2d_canditates[lambda3(TimeStamp_c1,TimeStamp_c2,TS_Cut11){ 
      return  TMath::Abs(TimeStamp_c1 - TimeStamp_c2) <  TS_Cut11 ; 
  }];
/*
  var(trueHits_2plane_2d_unique) = sct::enumerate_occurrence(
                                    trueHits_2plane_2d, 
                                    {"TimeStamp1", "TimeStamp2" ,"pos_x2","pos_x1","pos_y1","pos_y2" }
                                );
*/
 //var(trueHits_2plane_2d_unique ) = trueHits_2plane_2d_unique_proto[trueHits_2plane_2d_unique_proto["occurrence"] == 1];
temp_var(trueHits_2plane_2d_unique_2) = trueHits_2plane_2d;
trueHits_2plane_2d_unique_2["TimeStamp"] = lambda1(TimeStamp1){ return TimeStamp1; }; 
trueHits_2plane_2d_unique_2["x"] = lambda1(x11){ return x11; };
trueHits_2plane_2d_unique_2["y"] = lambda1(y11){ return y11; };

temp_var(trueHits_2plane_2d_unique_12) = trueHits_2plane_2d;
trueHits_2plane_2d_unique_12["TimeStamp"] = lambda1(TimeStamp2){ return TimeStamp2; };
trueHits_2plane_2d_unique_12["x"] = lambda1(x12){ return x12; };
trueHits_2plane_2d_unique_12["y"] = lambda1(y12){ return y12; };

 var(trigger_with_2_proto) = join(trigger, trueHits_2plane_2d_unique_2, {"TimeStamp"});
 var(trigger_with_2) = sct::select(trigger_with_2_proto, {
        "RunNumber",
        "EventNumber",
        "PlaneID", "x",
        "y","Charge","TimeStamp",
        }  
   );

 var(trigger_with_12_proto) = join(trigger, trueHits_2plane_2d_unique_12, {"TimeStamp"});
 var(trigger_with_12) = sct::select(trigger_with_12_proto, {
        "RunNumber",
        "EventNumber",
        "PlaneID", "x",
        "y","Charge","TimeStamp",
        }  
   );
  var(trigger_with_12_unique) = sct::first_occurrence(trigger_with_12, {"TimeStamp" });
  var(trigger_with_2_unique) = sct::first_occurrence(trigger_with_2, {"TimeStamp" });
  //var(trigger_with_12_unique) = sct::enumerate_occurrence(trigger_with_12, {"TimeStamp" });
  raw_file->getProcessorCollection()->loop();
  out_file1->Write();

  std::ofstream out("Hitmaker.csv",std::ofstream::out | std::ofstream::app);


  out <<runNumber<<","<< AnalysisNr<<",trigger_2_unqiue,2,0," << Draw(trigger_2_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;
  out <<runNumber<<","<< AnalysisNr<<",trigger_12_unqiue,12,0," << Draw(trigger_12_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;

    out <<runNumber<<","<< AnalysisNr<<",trueHits_proto_2_unqiue,2,1," << Draw(trueHits_proto_2_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;
  out <<runNumber<<","<< AnalysisNr<<",trueHits_proto_12_unqiue,12,1," << Draw(trueHits_proto_12_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;

    out <<runNumber<<","<< AnalysisNr<<",trueHits_x_2_unqiue,2,2," << Draw(trueHits_x_2_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;
  out <<runNumber<<","<< AnalysisNr<<",trueHits_x_12_unqiue,12,2," << Draw(trueHits_x_12_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;

    
  out <<runNumber<<","<< AnalysisNr<<",trueHits_y_2_unqiue,2,3," << Draw(trueHits_y_2_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;
  out <<runNumber<<","<< AnalysisNr<<",trueHits_y_12_unqiue,12,3," << Draw(trueHits_y_12_unqiue,DrawOption().draw_axis("TimeStamp")) << std::endl;
  
  out <<runNumber<<","<< AnalysisNr<<",trueHits_2d_plane_2_unique,2,4," << Draw(trueHits_2d_plane_2_unique,DrawOption().draw_axis("TimeStamp")) << std::endl;
  out <<runNumber<<","<< AnalysisNr<<",trueHits_2d_plane_12_unique,12,4," << Draw(trueHits_2d_plane_12_unique,DrawOption().draw_axis("TimeStamp")) << std::endl;


  out <<runNumber<<","<< AnalysisNr<<",trigger_with_2_unique,2,5," << Draw(trigger_with_2_unique,DrawOption().draw_axis("TimeStamp")) << std::endl;
  out <<runNumber<<","<< AnalysisNr<<",trigger_with_12_unique,12,5," << Draw(trigger_with_12_unique,DrawOption().draw_axis("TimeStamp")) << std::endl;
  return out_file1;
}

void run_all_Hitmaker(std::string dataFolder,  int AnalysisNr,std::vector<int> RunNumbers  ){

    {
        std::ofstream out("Hitmaker.csv",std::ofstream::out );
        out << "RunNumber,AnalysisNr,Collection,PlaneID,Type,Count\n";
    }
  for (int i=0; i< RunNumbers.size() ; ++i){
    std::cout << "Hitmaker file: " << RunNumbers[i] << std::endl;
    std::string runNr_str =  std::to_string(RunNumbers[i]);
    auto outfile =  HitMaker(dataFolder+ "/eudaq_out_" +runNr_str +"_clustering.root", dataFolder+ "/eudaq_out_" + runNr_str + "_Hitmaker.root",RunNumbers[i], AnalysisNr); 
    delete outfile;
  }
}