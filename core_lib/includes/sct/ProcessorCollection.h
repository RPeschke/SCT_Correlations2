#ifndef ProcessorCollection_h__
#define ProcessorCollection_h__


#ifndef __CINT__
#include <memory>
#include <vector>
#endif // !__CINT__

#include "sct/processor.h"
#include "sct/platform.hh"
class DllExport ProcessorCollection {
public:
  ProcessorCollection();
#ifndef __CINT__
  void addProcessor(std::shared_ptr<processor> processor_);
#endif
  init_returns init();
  end_returns end();
  void loop();
  void loop(int last);

  bool next();
  bool next_debug();
private:
#ifndef __CINT__
  std::vector<std::shared_ptr<processor>> m_processors;
#endif
};

#endif // ProcessorCollection_h__
