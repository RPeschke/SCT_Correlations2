TFile* converter(std::string InputFile, std::string outputFile, int runNumber, double AnalysisNr, std::string configFile="../macros/analisys_db.csv") {

  TFile * out_file1 = new TFile(outputFile.c_str(), "recreate");
  auto csv = CSV_File(InputFile.c_str());
  temp_var(all_layers) = csv.getCollection()->getPlane(ID_t(0));
  temp_var(all_dump) = all_layers[all_layers["PlaneID"] >= 0];
  
  //all_dump["axis"] = lambda1(y) { return y > 5;};
  //all_dump["position"] = lambda2(x, y) { return x+ 16*(y  -6*(y > 5));  };
  var(all_grouped) =  sct::group_events(all_dump, "EventNumber");
  csv.getProcessorCollection()->loop();
  out_file1->Write();
  return out_file1;
}


void run_all_converter(std::string dataFolder, std::vector<int> RunNumbers, int AnalysisNr ){
  for (int i=0; i< RunNumbers.size() ; ++i){
    std::cout << "converting file: " << RunNumbers[i] << std::endl;
    std::string runNr_str =  std::to_string(RunNumbers[i]);

    auto outfile =  converter(dataFolder+ "/run" +runNr_str +".csv", dataFolder+ "/eudaq_out_" + runNr_str + ".root",RunNumbers[i], AnalysisNr); 
    delete outfile;
  }
  


}