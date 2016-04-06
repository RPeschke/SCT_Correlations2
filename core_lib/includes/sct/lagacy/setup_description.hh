#ifndef setup_description_h__
#define setup_description_h__
#include <string>
#include <vector>

#include "sct/platform.hh"

class rapid_xml_node;

class DllExport Xladder {
public:
  Xladder(rapid_xml_node* n);
  Xladder();
  double ID,
    positionX,
    positionY,
    positionZ,
    radLength,
    rotationXY,
    rotationZX,
    rotationZY,
    sizeX,
    sizeY,
    thickness;


};
class DllExport Xsensitive {
public:
  Xsensitive(rapid_xml_node* n);
  Xsensitive();
  double ID,
    npixelX,
    npixelY,
    pitchX,
    pitchY,
    positionX,
    positionY,
    positionZ,
    radLength,
    resolution,
    rotation1,
    rotation2,
    rotation3,
    rotation4,
    sizeX,
    sizeY,
    thickness;

};
class DllExport Xlayer {
public:
  Xlayer(rapid_xml_node* n);
  Xladder ladder;
  Xsensitive  sensitive;
  static const char* NodeName();
};
struct DllExport Xdetector {
public:
  Xdetector(rapid_xml_node* n);
  Xdetector();
  std::string geartype, name;
  double siplanesID;
  std::string siplanesType;
  double siplanesNumber;
  Xlayer* layer_by_ID(double ID);
  const Xlayer* layer_by_ID(double ID) const;
  std::vector<Xlayer> layer;
};
struct DllExport XBField {
public:
  XBField(rapid_xml_node* n);
  XBField();
  std::string type;
  double x, y, z;
};

struct DllExport Xgear {

public:
  Xgear(rapid_xml_node* n);
  Xgear(const char* name);
  Xgear();

  std::string detectorName;
  XBField bfield;
  Xdetector detector;
};

DllExport Xgear load_gear(const char* name);


#endif // setup_description_h__
