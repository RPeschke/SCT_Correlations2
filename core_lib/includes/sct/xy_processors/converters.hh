#ifndef converters_h__
#define converters_h__
#include "sct/predef/plane.hh"
#include "sct/lagacy/setup_description.hh"
#include "sct/processor_prob.hh"
#include "sct/platform.hh"


class DllExport convert {
public:
  static void test();
 static xy_plane local_to_global(
    const xy_plane& local_hits,
    const Xlayer& layer,
    processor_prob& pprob_ = saveWithRandomName("local2global__")
    );
 static xy_plane global_to_local(
    const xy_plane& global_hits,
    const Xlayer&,
    processor_prob&  pprob_ = saveWithRandomName("global2local__")
    );
 static xy_plane hits_to_zs_data_GBL(
    const xy_plane& hits,
    const Xlayer&,
    processor_prob& pprob_ = saveWithRandomName("hits_to_zs_data_GBL__")
    );


 static xy_plane zs_data_to_hits_GBL(
    const xy_plane& sz_data,
    const Xlayer&,
    processor_prob& pprob_ = saveWithRandomName("zs_data_to_hits_GBL___")
    );

 static xy_plane zs_data_to_hits_DAF(
    const xy_plane& sz_data,
    const Xlayer&,
    processor_prob& pprob_ = saveWithRandomName("zs_data_to_hits_DAF___")
    );

 static xy_plane hits_to_zs_data_DAF(
    const xy_plane& hits,
    const Xlayer&,
    processor_prob& pprob_ = saveWithRandomName("hits_to_zs_data_DAF___")
    );


};
#endif // converters_h__
