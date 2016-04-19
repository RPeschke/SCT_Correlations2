#include "sct/xy_processors/converters.hh"
#include "sct/xy_processors/processor_linear_trans.hh"
#include "sct/xy_processors/processor_transform.hh"

#include <iostream>
#include "TMath.h"
#include "sct/xy_processors/xy_pro.hh"
#include "sct/xy_processors/modulo.hh"
#include "sct/internal/strong_types.h"

void convert::test()
{
  std::cout << "test" << std::endl;
}

xy_plane convert::local_to_global(const xy_plane& local_hits, const Xlayer& layer, processor_prob pprob/*= saveWithRandomName("local2global__") */)
{


  auto rot = xy_pro::rotate(
    local_hits,
    layer.ladder.rotationXY / 360 * TMath::Pi() * 2,
    DontsaveWithRandomName()
    );
  auto a = xy_pro::linear_trans(
    rot,
    layer.sensitive.rotation1,
    layer.sensitive.rotation2,
    layer.sensitive.rotation3,
    layer.sensitive.rotation4,
    DontsaveWithRandomName()
    );


  auto b = xy_pro::transform_move(
    a,
    x_offset_t(layer.ladder.positionX),
    y_offset_t(layer.ladder.positionY),
    pprob
    );

  return b;
}

xy_plane convert::global_to_local(const xy_plane& global_hits, const Xlayer& layer, processor_prob pprob/*= saveWithRandomName("global2local__") */)
{

  auto b = xy_pro::transform_move(
    global_hits,
    x_offset_t(-layer.ladder.positionX),
    y_offset_t(-layer.ladder.positionY),
    DontsaveWithRandomName()
    );

  auto det_A = layer.sensitive.rotation1*layer.sensitive.rotation4
    - layer.sensitive.rotation2*layer.sensitive.rotation3;

  if (det_A == 0) {
    std::cout << "[convert_global_to_local]: unable to invert matrix : Det_A ==0  " << std::endl;

  }


  auto a = xy_pro::linear_trans(
    b,
    layer.sensitive.rotation4 / det_A,
    -layer.sensitive.rotation2 / det_A,
    -layer.sensitive.rotation3 / det_A,
    layer.sensitive.rotation1 / det_A,
    DontsaveWithRandomName()
    );

  auto local_hits = xy_pro::rotate(
    a,
    -layer.ladder.rotationXY / 360 * TMath::Pi() * 2,
    pprob
    );

  return local_hits;
}

xy_plane convert::hits_to_zs_data_GBL(const xy_plane& hits, const Xlayer& layer, processor_prob pprob/*= saveWithRandomName("hits_to_zs_data_GBL__") */)
{

  return xy_pro::transform(
    hits,
    x_slope_t(1 / layer.sensitive.pitchX),
    x_offset_t(-(layer.sensitive.positionX - layer.sensitive.sizeX / 2) / layer.sensitive.pitchX),
    y_slope_t(1 / layer.sensitive.pitchY),
    y_offset_t(-(layer.sensitive.positionY - layer.sensitive.sizeY / 2) / layer.sensitive.pitchY),
    pprob
    );
}

xy_plane convert::zs_data_to_hits_GBL(const xy_plane& sz_data, const Xlayer& layer, processor_prob pprob/*= saveWithRandomName("zs_data_to_hits_GBL___") */)
{
  return xy_pro::transform(
    sz_data,
    x_slope_t(layer.sensitive.pitchX),
    x_offset_t(layer.sensitive.positionX - layer.sensitive.sizeX / 2),
    y_slope_t(layer.sensitive.pitchY),
    y_offset_t(layer.sensitive.positionY - layer.sensitive.sizeY / 2),
    pprob
    );
}

xy_plane convert::zs_data_to_hits_DAF(const xy_plane& sz_data, const Xlayer& layer, processor_prob  pprob/*= saveWithRandomName("zs_data_to_hits_DAF___") */)
{
  return xy_pro::transform(
    sz_data,
    x_slope_t(layer.sensitive.pitchX),
    x_offset_t(-layer.sensitive.sizeX / 2),
    y_slope_t(layer.sensitive.pitchY),
    y_offset_t(-layer.sensitive.sizeY / 2),
    pprob
    );
}

xy_plane convert::hits_to_zs_data_DAF(const xy_plane& hits, const Xlayer& layer, processor_prob pprob/*= saveWithRandomName("hits_to_zs_data_DAF___") */)
{
  return xy_pro::transform(
    hits,
    x_slope_t(1 / layer.sensitive.pitchX),
    x_offset_t((layer.sensitive.sizeX / 2) / layer.sensitive.pitchX),
    y_slope_t(1 / layer.sensitive.pitchY),
    y_offset_t((layer.sensitive.sizeY / 2) / layer.sensitive.pitchY),
    pprob
    );
}

