
//##define  var(x)  ___set_GName( processorName_t(#x)); auto x 
void process_csv() {

  TFile * out_file1 = new TFile("../debug/eudaq_out_227_raw.root", "recreate");
  auto csv = CSV_File("../debug/run227.csv");
  temp_var(all_layers) = csv.getCollection()->getPlane(ID_t(0));
  temp_var(all_dump) = all_layers[axCut(axesName_t("PlaneID")) >= 0];
  
  all_dump["axis"] = lambda1(y) { return y > 5;};
  all_dump["position"] = lambda2(x, y) {
    return x+ 16*(y  -6*(y > 5)); 
  };
  var(all_grouped) =  sct::group_events(all_dump, axesName_t("EventNumber"));
  csv.getProcessorCollection()->loop();
  out_file1->Write();
  
}