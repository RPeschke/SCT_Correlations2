#ifndef converters_h__
#define converters_h__
#include "sct/predef/plane.hh"
#include "sct/lagacy/setup_description.hh"
#include "sct/processor_prob.hh"


 xy_plane convert_local_to_global(
  const xy_plane& local_hits,
  const Xlayer& layer,
   processor_prob& pprob_ = saveWithRandomName("local2global__")
  );
 xy_plane convert_global_to_local(
  const xy_plane& global_hits,
   const Xlayer&,
   processor_prob& = saveWithRandomName("global2local__")
   );
xy_plane convert_hits_to_zs_data_GBL(
  const xy_plane& hits,
  const Xlayer&,
  processor_prob& = saveWithRandomName("hits_to_zs_data_GBL__")
  );


xy_plane convert_zs_data_to_hits_GBL(
  const xy_plane& sz_data,
  const Xlayer&,
  processor_prob& = saveWithRandomName("zs_data_to_hits_GBL___")
  );

xy_plane convert_zs_data_to_hits_DAF(
  const xy_plane& sz_data,
  const Xlayer&,
  processor_prob& = saveWithRandomName("zs_data_to_hits_DAF___")
  );

xy_plane convert_hits_to_zs_data_DAF(
  const xy_plane& hits,
  const Xlayer&,
  processor_prob& = saveWithRandomName("hits_to_zs_data_DAF___")
  );
#endif // converters_h__
