#include "sct/ProcessorCollection.h"

ProcessorCollection::ProcessorCollection(){


}

void ProcessorCollection::addProcessor(std::shared_ptr<processor> processor_){
  m_processors.push_back(processor_);
  processor_->mpc = this;
}

init_returns ProcessorCollection::init(){
  for (auto&e:m_processors){
    auto ret=e->init();
    if (ret!=i_sucess){
      return ret;
    }
  }
  return i_sucess;
}

end_returns ProcessorCollection::end(){
  for (auto&e : m_processors) {
    auto ret = e->end();
    if (ret != e_success) {
      return ret;
    }
  }
  return e_success;
}

void ProcessorCollection::loop(){
  init();
  while (next())
  {

  }
  end();
}

void ProcessorCollection::loop(int last)
{
  init();
  int i = 0;
  while (next()&&++i<last)
  {

  }
  end();

}



bool ProcessorCollection::next(){
  for (auto&e : m_processors) {
    auto ret = e->processEvent();
    if (ret != p_sucess) {
      return false;
    }
  }
  for (auto&e : m_processors) {
    auto ret = e->fill();
    if (ret != p_sucess) {
      return false;
    }
  }
  return true;
}

bool ProcessorCollection::next_debug()
{
  return true;
}
