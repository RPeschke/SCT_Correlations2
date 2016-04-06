#include "sct/xy_processors/converters.hh"
#include "sct/xy_processors/processor_linear_trans.hh"
#include "sct/xy_processors/processor_transform.hh"

#include <iostream>
#include "TMath.h"

xy_plane convert_local_to_global(const xy_plane& local_hits, const Xlayer& layer, processor_prob& pprob/*= saveWithRandomName("local2global__") */)
{


  auto rot = rotate(
    local_hits,
    layer.ladder.rotationXY / 360 * TMath::Pi() * 2,
    DontsaveWithRandomName()
    );
  auto a = linear_trans(
    rot,
    layer.sensitive.rotation1,
    layer.sensitive.rotation2,
    layer.sensitive.rotation3,
    layer.sensitive.rotation4,
    DontsaveWithRandomName()
    );


  auto b = transform_move(
    a,
    layer.ladder.positionX,
    layer.ladder.positionY,
    pprob
    );

  return b;
}

xy_plane convert_global_to_local(const xy_plane& global_hits, const Xlayer& layer, processor_prob& pprob/*= saveWithRandomName("global2local__") */)
{

  auto b = transform_move(
    global_hits,
    -layer.ladder.positionX,
    -layer.ladder.positionY,
    DontsaveWithRandomName()
    );

  auto det_A = layer.sensitive.rotation1*layer.sensitive.rotation4
    - layer.sensitive.rotation2*layer.sensitive.rotation3;

  if (det_A == 0) {
    std::cout << "[convert_global_to_local]: unable to invert matrix : Det_A ==0  "  << std::endl;
    
  }


  auto a = linear_trans(
    b,
    layer.sensitive.rotation4 / det_A,
    -layer.sensitive.rotation2 / det_A,
    -layer.sensitive.rotation3 / det_A,
    layer.sensitive.rotation1 / det_A,
    DontsaveWithRandomName()
    );

  auto local_hits = rotate(
    a,
    -layer.ladder.rotationXY / 360 * TMath::Pi() * 2,
    pprob
    );

  return local_hits;
}

xy_plane convert_hits_to_zs_data_GBL(const xy_plane& hits, const Xlayer& layer, processor_prob& pprob/*= saveWithRandomName("hits_to_zs_data_GBL__") */)
{

  return transform(
    hits,
    1 / layer.sensitive.pitchX,                                                         // x_slope
    -(layer.sensitive.positionX - layer.sensitive.sizeX / 2) / layer.sensitive.pitchX,  //x_offset
    1 / layer.sensitive.pitchY,                                                         //y_slope
    -(layer.sensitive.positionY - layer.sensitive.sizeY / 2) / layer.sensitive.pitchY,  //y_offset
    pprob
    );
}

xy_plane convert_zs_data_to_hits_GBL(const xy_plane& sz_data, const Xlayer& layer, processor_prob& pprob/*= saveWithRandomName("zs_data_to_hits_GBL___") */)
{
  return transform(
    sz_data,
    layer.sensitive.pitchX,                                     // x_slope
    layer.sensitive.positionX - layer.sensitive.sizeX / 2,      //x_offset
    layer.sensitive.pitchY,                                     //y_slope
    layer.sensitive.positionY - layer.sensitive.sizeY / 2,      //y_offset
    pprob
    );
}

xy_plane convert_zs_data_to_hits_DAF(const xy_plane& sz_data, const Xlayer& layer, processor_prob&  pprob/*= saveWithRandomName("zs_data_to_hits_DAF___") */)
{
  return transform(
    sz_data,
    layer.sensitive.pitchX,          // x_slope
    -layer.sensitive.sizeX / 2,      //x_offset
    layer.sensitive.pitchY,          //y_slope
    -layer.sensitive.sizeY / 2,      //y_offset
    pprob
    );
}

xy_plane convert_hits_to_zs_data_DAF(const xy_plane& hits, const Xlayer& layer, processor_prob& pprob/*= saveWithRandomName("hits_to_zs_data_DAF___") */)
{
  return transform(
    hits,
    1 / layer.sensitive.pitchX,                            // x_slope
    (layer.sensitive.sizeX / 2) / layer.sensitive.pitchX,  //x_offset
    1 / layer.sensitive.pitchY,                             //y_slope
    (layer.sensitive.sizeY / 2) / layer.sensitive.pitchY,  //y_offset
    pprob
    );
}
