#ifndef sct_root_h__
#define sct_root_h__
#include "TSystem.h"

#include <iostream>
#include <string>

struct __dummy_lib_load{
  __dummy_lib_load() {
    gSystem->Load("libSCT_plot.so");
    auto  f_location= std::string(__FILE__);
    std::cout << f_location << std::endl;

    gInterpreter->ProcessLine("#include \"../core_lib/includes/sct/platform.hh\"");
    gInterpreter->ProcessLine("#include \"../core_lib/includes/sct/generic_processors/lambda_Note.hh\"");
    gInterpreter->ProcessLine("#include \"../core_lib/includes/sct/generic_processors/processor_generic_correlation.hh\"");
    gInterpreter->ProcessLine("#include \"../core_lib/includes/sct/generic_processors/processor_normalize_on_first_plane.hh\"");
  }
}___asdkl__;

#endif // sct_root_h__
