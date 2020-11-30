void converter2() {

  TFile * out_file1 = new TFile("../data/eudaq_out_239a.root", "recreate");
  auto csv = CSV_File("../data/run239.csv");
  var(all_layers) = csv.getCollection()->getPlane(ID_t(0));
  var(all_dump) = all_layers[axCut(axesName_t("PlaneID")) >= 0];
  
  
  csv.getProcessorCollection()->loop();
  out_file1->Write();
}