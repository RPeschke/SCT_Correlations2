
#include "sct/FileProcessors/FileProcessorsBase.hh"
#include "TError.h"


#include <iostream>
#include <sstream>


#include "tclap/CmdLine.h"
#include "sct/legacy/xml_input_file.hh"
#include <thread>






using namespace std;
using namespace TCLAP;

void remove_root_printouts() {
  gErrorIgnoreLevel = kError;  // ignoring root printouts (replace of histograms) 
}


int main(int argc, char **argv) {

  remove_root_printouts();



    CmdLine cmd("ProcessCollection", ' ', "0.1");

    ValueArg<std::string> FileNameArg("i", "inFile", "xml filename", true, "", "string");
    cmd.add(FileNameArg);

    ValueArg<std::string>  inPath("p", "inPath", "path to the root files", true, "", "string");
    cmd.add(inPath);

    ValueArg<std::string>  outpath("o", "outPath", "output path", false, ".", "string");
    cmd.add(outpath);
    ValueArg<std::string>  processor_type("s", "Processor", "which processor to use Standard or Modulo", false, "standard", "string");
    cmd.add(processor_type);
    TCLAP::SwitchArg regprocessor_type("r", "registeredProcessors", "shows the processors registered");
    cmd.add(regprocessor_type);
#ifdef _DEBUG
    cmd.setExceptionHandling(false);
#endif // _DEBUG

    cmd.parse(argc, argv);
    if (regprocessor_type.getValue()) {

     
      return 0;
    }

    auto p = create_processor(processor_type.getValue());

    p->Add_XML_RunList(FileNameArg.getValue(), inPath.getValue(), outpath.getValue());
    p->setPrintout(true);
    p->process();
  

    std::cout << "</main()>\n";

  return 0;










  return 0;

}

