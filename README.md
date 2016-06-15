# SCT_Correlations2
Improved version of the correlation plotting framework for SCT Test Beam DATA


## Overview



The Data is Discriped in form of hits as the smallest unit. Hits Are group in planes and planes are grouped in collection. Very much the same as LCIO does it. The main differents is that in a given collection all hits must have the same fields. For example one can have a collection with only x y information and another collection with x y phi theta information. 


## Examples
``` c++


// Example 1
int main(){


  TFile tf("run00xxxx_fitter.root");  // opening ROOT file
  ProcessorCollection pc;             // creating Collection to store the processors
  
  EUTFile file(&tf,&pc);              // Generic EUtelescope root file handler
  new TFile("test.root", "recreate"); // output file name. needs to be opened before any of the processors are created


  auto collection_ =file.getCollection(collectionName_t( "local_hit")); // gets Collection handle with this name

  auto plane_= collection_->getPlane(ID_t(1));      // Get plane with specific ID
  double x, y;                                      // Preparing 2 double to store the x y coordinates
  plane_.setHitAxisAdress(axesName_t("x"), &x);     // making the data link for x variable 
  plane_.setHitAxisAdress(axesName_t("y"), &y);     // making the data link for y variable 
  pc.init();                                        // Initializing the processors
  pc.next();                                        // Executing all processors once. Return value indecates end of file
  plane_.next();                                    // getting the first hit from the plane. Return value indicates end of list 
  std::cout << "x: " << x << " y: " << y << std::endl;  // Displays x and y value from this hit 
  pc.end();                                         // Executes end statement for all Processors 

  return 0;
  }
``` 

``` c++
// example 2
int  main() {
  

  TFile tf("run00xxxx_fitter.root");
  ProcessorCollection pc;

  EUTFile file(&tf, &pc);
  new TFile("test.root", "recreate");

  
  auto collection_ = file.getCollection(collectionName_t("local_hit"));

  auto plane_ = collection_->getPlane(ID_t(1));
  double x, y;
  plane_.setHitAxisAdress(axesName_t("x"), &x);
  plane_.setHitAxisAdress(axesName_t("y"), &y);
  // same as for example 1
  
  pc.init();
  while (pc.next()) { // loop over all events 
    while (plane_.next()) {  // loop over all hits in this event 
      std::cout << "x: " << x << " y: " << y << std::endl;  // print out of individual hits from this plane 

    }
  }
  pc.end();

  
return 0;
}

```


``` c++
int main() {
  auto theApp = make_gui(); // Creates TApplication (pseudo code)

  TFile tf("run00xxxx_fitter.root");
  ProcessorCollection pc;

  EUTFile file(&tf, &pc);
  new TFile("test.root", "recreate");


  auto collection_ = file.getCollection(collectionName_t("local_hit"));

  auto plane_ = collection_->getPlane(ID_t(1));

  Draw(plane_); // Draw this plane. Default is y:x plot

  theApp->Run();
 return 0;
}

```

``` c++
int main(){
auto theApp = make_gui();

  TFile tf("run00xxxx_fitter.root");
  ProcessorCollection pc;

  EUTFile file(&tf, &pc);
  new TFile("test.root", "recreate");


  auto collection_ = file.getCollection(collectionName_t("local_hit"));

  auto plane_ = collection_->getPlane(ID_t(1));

  Draw(plane_,DrawOption().cut_x(1,3)); // plot with 1 < x < 3  cut

  theApp->Run();
  
  return 0;
  }
``` 

``` c++
int main(){
 auto theApp = make_gui();

  TFile tf("run00xxxx_fitter.root");
  ProcessorCollection pc;

  EUTFile file(&tf, &pc);
  new TFile("test.root", "recreate");


  auto collection_ = file.getCollection(collectionName_t("local_hit"));

  auto plane_1 = collection_->getPlane(ID_t(1));
  auto plane_2 = collection_->getPlane(ID_t(2));


// create correlation plot between x from first plane and x from second plane
  auto correlation_ =  xy_pro::correlations(plane_1.get_axis(axesName_t("x")), plane_2.get_axis(axesName_t("x")));
  
  pc.loop(10000);  // loop over the first x events. Default is loop over all events. 
  
  Draw(correlation_);  // Draw Correlation plot

  theApp->Run();
  
  return 0;
  }
  
```

``` c++

int main(){
  auto theApp = make_gui();

  // predefined Fitter file. Specification may 2015 test beam
  FFile file(FileName_t("run00xxxx_fitter.root"), SubClassName_t("MAY15")); 
  new TFile("test.root", "recreate");

// FFiles know which collections to expect from a given file
  auto plane_1 = file.tel_hit_local(ID_t(1)); 
  auto plane_2 = file.tel_hit_local(ID_t(2));

  auto rotated_ = xy_pro::rotate(plane_2, 15); // rotation operator. 

  auto correlation_ = xy_pro::correlations(rotated_.get_x(), plane_2.get_x()); // xy_planes know that the hits only have x y informations



  file.getProcessorCollection()->loop(10000); // loop over x events

  Draw(correlation_);  // plot correlations 

  theApp->Run();
  return 0;
  }
``` 


``` c++
int main() {
auto theApp = make_gui();


  FFile file(FileName_t("run00xxxx_fitter.root"), SubClassName_t("MAY15"));
  new TFile("test.root", "recreate");
  Xgear gear("alignedGear-run00xxxx.xml"); // Provides support for gear files

  auto plane_1_zs = file.tel_zs_data(ID_t(2));
  auto plane_2 = file.tel_hit_local(ID_t(2));


// can convert between local and global coordinate system
  auto global_2 = convert::hits_to_zs_data_GBL(plane_2,*gear.detector.layer_by_ID(2));
  auto correlation_ = xy_pro::correlations(global_2.get_x(), plane_1_zs.get_x());

  auto residual_ = xy_pro::residual(global_2.get_x(), plane_1_zs.get_x());

  file.getProcessorCollection()->loop(10000);

  Draw(correlation_);
  new TCanvas();
  Draw(residual_,DrawOption().cut_x(-10,10));

  new TCanvas();
  TH1D h1("h1", "h1", 11, -5, 5);
  Draw(residual_, DrawOption().cut_x(-10, 10).draw_x().output_object(&h1)); // can redirect plots to ROOT histograms 


  theApp->Run();
  return 0;
  }
``` 

``` c++
int main() {
 auto theApp = make_gui();
  ProcessorCollection pc;
 // Support for lcio files when LCIO libraries are present on your machine. Windows LCIO binaries are in "extern" Folder
  lcio_reader File_("run00xxxx-hitmaker.slcio", &pc); 
  
  new TFile("test.root", "recreate");



  auto collection_ = File_.getCollection(collectionName_t("local_hit")); // get Collection by name 

  auto plane_1 = collection_->getPlane(ID_t(1));

  auto plane_2 = collection_->getPlane(ID_t(2));



  auto correlation_ = xy_pro::correlations(plane_1.get_axis(axesName_t("x")), plane_2.get_axis(axesName_t("x")));



  pc.loop(10000);

  Draw(correlation_); // draw Correlation plots


  
  theApp->Run();
 }
``` 

``` c++
// Cint Examples
// Most of the examples also work in cint but keep in mint that auto is not supported in Cint.
// Strong types are only used in debug mode not in release. Therefore "collectionName_t" and so on are not needed here 
void example9() {

  ProcessorCollection pc;

  lcio_reader File_("run00xxxx-hitmaker.slcio", &pc); //debug mode!
    
  new TFile("test.root", "recreate");



  xy_plane plane_1  = File_.getPlane("local_hit",1);  // no auto kayword 
  xy_plane plane_2  = File_.getPlane("local_hit",2);




  xy_plane correlation_ = xy_pro::correlations(plane_1.get_x(), plane_2.get_x());



  pc.loop();

  Draw(correlation_);


}
```
``` c++
void example10() {

  FFile file("run00xxxx_fitter.root", "MAY15 )// no strong types
  new TFile("test.root", "recreate");


  xy_plane plane_1 = file.tel_hit_local(1);
  xy_plane plane_2 = file.tel_hit_local(2);

  xy_plane rotated_ = xy_pro::rotate(plane_2, 15); //

  xy_plane correlation_ = xy_pro::correlations(rotated_.get_x(), plane_2.get_x());



  file.getProcessorCollection()->loop();

  Draw(correlation_);

}

```


The executable work as before you need to provide a xml file which stores all information about this run. 
ProcessFile only runs over one file 
``` bash
ProcessFile.exe -i DEVICE_2_ASIC_on_Position_5_400V.xml -p /path/to/files/ -e 0
```


ProcessCollection runs over all files from one run 
```bash
ProcessCollection.exe -i DEVICE_2_ASIC_on_Position_5_400V.xml -p /path/to/files/ 
```


if you want to run non standard processor like the modulo processer you can do this like before with the flag -s 
``` bash 
ProcessCollection.exe -i DEVICE_2_ASIC_on_Position_5_400V.xml -p /path/to/files/   -s Modulo
```



``` c++
int main() {
  auto theApp = make_gui();
  FFile m_input_file(FileName_t("run00xxxx_fitter.root"));
  new TFile("test.root", "recreate");
  auto plane_ = m_input_file.tel_zs_data(ID_t(0));
  auto cutted1 = cut_op(plane_, x_def() > y_def() + 5); // cuts out all hits where x <= y+5
  m_input_file.getProcessorCollection()->loop(10000);
  Draw(cutted1);
  theApp->Run();
  return 0;
}

```
``` c++
void example15() {
  auto theApp = make_gui();
  FFile m_input_file(FileName_t("run00xxxx_fitter.root"));
  new TFile("test.root", "recreate");

  auto plane_ = m_input_file.tel_zs_data(ID_t(0));

  // It is possiple to define lamda nodes. this allows for more specific cuts. Not supported in CINT
  auto t = make_lambda_Node([](auto x, auto y) {return x > y + 5; }, x_def(), y_def());
  auto cutted = cut_op(plane_, t);  
  m_input_file.getProcessorCollection()->loop(10000);

  Draw(cutted);
  theApp->Run();
}
```
