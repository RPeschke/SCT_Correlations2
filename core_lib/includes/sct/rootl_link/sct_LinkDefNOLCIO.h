#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;



#pragma link C++ class hit;
#pragma link C++ class fitterHit;

#pragma link C++ class plane;
#pragma link C++ class xy_plane;
#pragma link C++ class FitterPlane;

#pragma link C++ class axis;

#pragma link C++ class collection;
#pragma link C++ enum  SaveOption;

#pragma link C++ class EUTFile;
#pragma link C++ class generic_plane;

#pragma link C++ class processor;
#pragma link C++ enum  end_returns;
#pragma link C++ enum  process_returns;
#pragma link C++ enum  init_returns;

#pragma link C++ class ProcessorCollection;

#pragma link C++ class processorPlaneVSPlane;
#pragma link C++ class processor_prob;
#pragma link C++ class Xladder;
#pragma link C++ class Xsensitive;
#pragma link C++ class Xlayer;
#pragma link C++ class Xdetector;
#pragma link C++ class XBField;
#pragma link C++ class Xgear;
#pragma link C++ function load_gear;




#pragma link C++ class MinMaxRange;
#pragma link C++ class xml_globalConfig;
#pragma link C++ class xml_file;
#pragma link C++ class XML_imput_file;
#pragma link C++ class S_Cut;
#pragma link C++ class S_YCut;
#pragma link C++ class S_XCut;
#pragma link C++ class S_CutCoollection;
#pragma link C++ class S_Cut_BinContent;
#pragma link C++ class S_NoCut;

#pragma link C++ function Draw;
#pragma link C++ class DrawOption;
#pragma link C++ class xy_pro;
#pragma link C++ class find_nearest;
#pragma link C++ class find_nearest_strip;
#pragma link C++ enum axis_def;
#pragma link C++ class THE;
#pragma link C++ class truehitExtractor;
#pragma link C++ class TH_param;
#pragma link C++ class D2T;
#pragma link C++ class DUT_2_Track_correlator;
#pragma link C++ class D2T_prob;

#pragma link C++ class FFile;
#pragma link C++ class fitterFile;
#pragma link C++ class FileProcessorsBase;
#pragma link C++ class FileProcessors_standard;
#pragma link C++ class SCT_helpers;

#pragma link C++ class convert;
#pragma link C++ function saveWithRandomName;
#pragma link C++ function DontsaveWithRandomName;
#pragma link C++ class efficiency;
#pragma link C++ class efficiency2D;
#pragma link C++ class residual_efficiency;
#pragma link C++ function Print;
#pragma link C++ class instrip_efficiency;
#pragma link C++ class Cluster_strip;


#pragma link C++ typedef  modulo_x;
#pragma link C++ typedef modulo_y;
#pragma link C++ typedef modulo_t;
#pragma link C++ typedef max_cl_t;


#pragma link C++ typedef ID_t;
#pragma link C++ typedef stripNr_t;
#pragma link C++ typedef residualCut_t;
#pragma link C++ typedef rot_angle_t;

#pragma link C++ typedef move_t;
#pragma link C++ typedef collectionName_t;
#pragma link C++ typedef axesName_t;
#pragma link C++ typedef processorName_t;
#pragma link C++ typedef procent_t;
#pragma link C++ typedef x_offset_t;
#pragma link C++ typedef x_slope_t;
#pragma link C++ typedef cutValue_t;
#pragma link C++ function cut_op;
#pragma link C++ class cutNote;
#pragma link C++ class generic_plane_slice_handler;
#pragma link C++ class CSV_File;

#pragma link C++ function unique_of;
#pragma link C++ function correlation;
#pragma link C++ function generic_append_plane;
#pragma link C++ class lambda_Note;
#pragma link C++ class unique_ax;
#pragma link C++ class _correlation__generic_plane_wraper;
#pragma link C++ enum  _correlation_;
//#pragma link C++ function operator*(generic_plane& const, _correlation_);
//#pragma link C++ function operator*(_correlation__generic_plane_wraper&&, const generic_plane&);

#pragma link C++ function  operator&&(const cutNote& , const cutNote& );



#pragma link C++ class axCut;

#pragma link C++ function x_def;
#pragma link C++ function y_def;
#pragma link C++ function operator+(const cutNote&, double);
#pragma link C++ function operator+(double, const cutNote&);
#pragma link C++ function operator+(const cutNote&, const cutNote&);

#pragma link C++ function operator-(const cutNote&,double);
#pragma link C++ function operator-(double, const cutNote&);
#pragma link C++ function operator-(const cutNote&, const cutNote&);

#pragma link C++ function operator*(const cutNote&, double);
#pragma link C++ function operator*(double, const cutNote&);
#pragma link C++ function operator*(const cutNote&, const cutNote&);

#pragma link C++ function operator/(const cutNote&, double);
#pragma link C++ function operator/(double, const cutNote&);
#pragma link C++ function operator/(const cutNote&, const cutNote&);



#pragma link C++ function operator< (const cutNote& , const cutNote&  );
#pragma link C++ function operator< (const cutNote& , double  );
#pragma link C++ function operator< (double , const cutNote&  );

#pragma link C++ function operator<=(const cutNote& , const cutNote&  );
#pragma link C++ function operator<=(const cutNote& , double  );
#pragma link C++ function operator<=(double , const cutNote&  );


#pragma link C++ function operator> (const cutNote& , const cutNote&  );
#pragma link C++ function operator> (const cutNote& , double  );
#pragma link C++ function operator> (double , const cutNote&  );

#pragma link C++ function operator>=(const cutNote& , const cutNote&  );
#pragma link C++ function operator>=(const cutNote& , double );
#pragma link C++ function operator>=(double , const cutNote&  );


#pragma link C++ function operator==(const cutNote& , const cutNote&  );
#pragma link C++ function operator==(const cutNote& , double  );
#pragma link C++ function operator==(double , const cutNote&  );

#pragma link C++ function operator!=(const cutNote& , const cutNote&);
#pragma link C++ function operator!=(const cutNote& , double);
#pragma link C++ function operator!=(double , const cutNote&);






#pragma link C++ function  operator!(const cutNote& );



#pragma link C++ function operator||(const cutNote& , const cutNote& );

#endif //__CINT__