
//##define  var(x)  ___set_GName( processorName_t(#x)); auto x 
void process_227() {

  TFile * out_file1 = new TFile("../debug/eudaq_out_227.root", "recreate");
  auto csv = CSV_File("../debug/run227.csv");
  temp_var(all_layers) = csv.getCollection()->getPlane(ID_t(0));
  temp_var(all_dump) = all_layers[axCut(axesName_t("PlaneID")) >= 0];
  
  all_dump["axis"] = lambda2(y) { return y > 5;};
  all_dump["position"] = lambda2(x, y) {
    return x+ 16*(y  -6*(y > 5)); 
  };
  var(all_grouped) =  sct::group_events(all_dump, axesName_t("EventNumber"));
  csv.getProcessorCollection()->loop();
  out_file1->Write();
  
  
  temp_var(layer_2) = all_grouped[axCut(axesName_t("PlaneID")) == 2];
  temp_var(layer_12) = all_grouped[axCut(axesName_t("PlaneID")) == 12];
  temp_var(cor_2_vs_12) = layer_2 cross layer_12;
  
  temp_var(layer_12_trigger) = layer_12[axCut(axesName_t("x")) == 14 && axCut(axesName_t("y")) == 8];
  temp_var(layer_12_not_trigger) = layer_12[axCut(axesName_t("x")) != 14 || axCut(axesName_t("y")) != 8];
  temp_var(layer12_trig_vs_non_trig) = layer_12_trigger cross layer_12_not_trigger;
  
  layer12_trig_vs_non_trig[axesName_t("delta_time")] = lambda2(TimeStamp1, TimeStamp2) {
    return TimeStamp1 - TimeStamp2;
  };
  temp_var(layer_12_cut) = layer12_trig_vs_non_trig[axCut(axesName_t("delta_time")) > 118 && axCut(axesName_t("delta_time")) < 121];


  temp_var(layer_2_trigger) = layer_2[axCut(axesName_t("x")) == 15 && axCut(axesName_t("y")) == 7];
  temp_var(layer_2_not_trigger) = layer_2[axCut(axesName_t("x")) != 15 || axCut(axesName_t("y")) != 7];
  temp_var(layer2_trig_vs_non_trig) = layer_2_trigger cross layer_2_not_trigger;

  layer2_trig_vs_non_trig[axesName_t("delta_time")] = lambda2(TimeStamp1, TimeStamp2) {
    return TimeStamp1 - TimeStamp2;
  };

  temp_var(layer_2_cut) = layer2_trig_vs_non_trig[axCut(axesName_t("delta_time")) > 120 && axCut(axesName_t("delta_time")) < 123];
  temp_var(layer_cut_2_vs_12) = layer_2_cut cross layer_12_cut;
  
  var(layer_cut_2_vs_12_cut) = layer_cut_2_vs_12[axCut(axesName_t("TimeStamp11")) - (axCut(axesName_t("TimeStamp12"))   -6400e6 - 400e6 + 100e6+4000e3) < 1e6   ];
  
  csv.getProcessorCollection()->loop();
  out_file1->Write();
}