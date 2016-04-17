#include "sct/xy_processors/modulo.hh"
#include <math.h>
#include "sct/xy_processors/xy_pro.hh"
#include "sct/ProcessorCollection.h"
modulo_processor::modulo_processor(const axis& x_, const axis& y_, modulo_x  mod_x, modulo_y mod_y, processor_prob& pprob):processor_hit2d(x_,y_,pprob),m_modulo_x(mod_x), m_mod_y(mod_y)
{

}

void modulo_processor::processHit(double x, double y)
{
  auto newx = fmod(x, necessary_CONVERSION( m_modulo_x));
  auto newy = fmod(y, necessary_CONVERSION(m_mod_y));
  pushHit(newx, newy);
}


xy_plane xy_pro::modulo(const xy_plane& hits, modulo_x x_mod, modulo_y y_mod, processor_prob& pprob_ )
{
  std::shared_ptr<processor> p(new modulo_processor(hits.get_x(), hits.get_y(), x_mod, y_mod, pprob_));
  
  hits.get_ProcessorCollection()->addProcessor(p);

  return dynamic_cast<modulo_processor*>(p.get())->get_output_collection()->getPlane(0);
}
