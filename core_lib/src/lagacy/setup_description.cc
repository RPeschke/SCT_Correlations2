#include "sct/lagacy/setup_description.hh"
#include "sct/lagacy/xml_util.hh"
#include "rapidxml_utils.hpp"
#include <iostream>
#define  sct_corr_XML_ERROR_DEFAULT_VALUE  double(-666666.666666)
#define SCT_THROW(x) std::cout << x << std::endl



Xladder::Xladder(rapid_xml_node* n) : 

  ID(xml_util::getAtribute(n, "ID", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  positionX(xml_util::getAtribute(n, "positionX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  positionY(xml_util::getAtribute(n, "positionY", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  positionZ(xml_util::getAtribute(n, "positionZ", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  radLength(xml_util::getAtribute(n, "radLength", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  rotationXY(xml_util::getAtribute(n, "rotationXY", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  rotationZX(xml_util::getAtribute(n, "rotationZX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  rotationZY(xml_util::getAtribute(n, "rotationZY", sct_corr_XML_ERROR_DEFAULT_VALUE)),


  sizeX(xml_util::getAtribute(n, "sizeX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  sizeY(xml_util::getAtribute(n, "sizeY", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  thickness(xml_util::getAtribute(n, "thickness", sct_corr_XML_ERROR_DEFAULT_VALUE))
{

}

Xladder::Xladder()
{
  ID = sct_corr_XML_ERROR_DEFAULT_VALUE;
  positionX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  positionY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  positionZ = sct_corr_XML_ERROR_DEFAULT_VALUE;
  radLength = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotationXY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotationZX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotationZY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  sizeX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  sizeY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  thickness = sct_corr_XML_ERROR_DEFAULT_VALUE;


}

Xsensitive::Xsensitive(rapid_xml_node* n) :

  ID(xml_util::getAtribute(n, "ID", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  npixelX(xml_util::getAtribute(n, "npixelX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  npixelY(xml_util::getAtribute(n, "npixelY", sct_corr_XML_ERROR_DEFAULT_VALUE)),


  pitchX(xml_util::getAtribute(n, "pitchX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  pitchY(xml_util::getAtribute(n, "pitchY", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  positionX(xml_util::getAtribute(n, "positionX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  positionY(xml_util::getAtribute(n, "positionY", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  positionZ(xml_util::getAtribute(n, "positionZ", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  radLength(xml_util::getAtribute(n, "radLength", sct_corr_XML_ERROR_DEFAULT_VALUE)),

  resolution(xml_util::getAtribute(n, "resolution", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  rotation1(xml_util::getAtribute(n, "rotation1", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  rotation2(xml_util::getAtribute(n, "rotation2", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  rotation3(xml_util::getAtribute(n, "rotation3", sct_corr_XML_ERROR_DEFAULT_VALUE)),


  rotation4(xml_util::getAtribute(n, "rotation4", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  sizeX(xml_util::getAtribute(n, "sizeX", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  sizeY(xml_util::getAtribute(n, "sizeY", sct_corr_XML_ERROR_DEFAULT_VALUE)),
  thickness(xml_util::getAtribute(n, "thickness", sct_corr_XML_ERROR_DEFAULT_VALUE))
{

}

Xsensitive::Xsensitive()
{
  ID = sct_corr_XML_ERROR_DEFAULT_VALUE;
  npixelX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  npixelY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  pitchX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  pitchY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  positionX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  positionY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  positionZ = sct_corr_XML_ERROR_DEFAULT_VALUE;
  radLength = sct_corr_XML_ERROR_DEFAULT_VALUE;
  resolution = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotation1 = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotation2 = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotation3 = sct_corr_XML_ERROR_DEFAULT_VALUE;
  rotation4 = sct_corr_XML_ERROR_DEFAULT_VALUE;
  sizeX = sct_corr_XML_ERROR_DEFAULT_VALUE;
  sizeY = sct_corr_XML_ERROR_DEFAULT_VALUE;
  thickness = sct_corr_XML_ERROR_DEFAULT_VALUE;

}

Xlayer::Xlayer(rapid_xml_node* n) 
{
  auto lad = rapid_xml_node(n->value->first_node("ladder"));
  ladder = Xladder(&lad);
  auto sen = rapid_xml_node(n->value->first_node("sensitive"));
  sensitive = Xsensitive(&sen);
}

const char* Xlayer::NodeName()
{
  return "layer";
}

Xdetector::Xdetector(rapid_xml_node* n_)
{
  auto n = n_->value;
  geartype = xml_util::getAtribute(n, "geartype", "notSet");
  name = xml_util::getAtribute(n, "name", "notSet");

  siplanesID = xml_util::getAtribute(n->first_node("siplanesID"), "ID", siplanesID);
  siplanesType = xml_util::getAtribute(n->first_node("siplanesType"), "type", "notSet");

  siplanesNumber = xml_util::getAtribute(n->first_node("siplanesNumber"), "number", siplanesNumber);

  layer = xml_util::getVectorOfT<Xlayer>(n->first_node("layers"));
}

Xdetector::Xdetector()
{
  
  siplanesID = 0;
  
  siplanesNumber = 0;
}

Xlayer* Xdetector::layer_by_ID(double ID)
{
  for (auto& e : layer) {
    if (e.ladder.ID == ID) {
      return &e;
    }
  }
  SCT_THROW("Layer not Found. searching for Layer " + std::to_string(ID));
  return nullptr;
}

const Xlayer* Xdetector::layer_by_ID(double ID) const
{
  for (auto& e : layer) {
    if (e.ladder.ID == ID) {
      return &e;
    }
  }
  SCT_THROW("Layer not Found. searching for Layer " + std::to_string(ID));
  return nullptr;
}

XBField::XBField(rapid_xml_node* n) :type(xml_util::getAtribute(n, "type", "notSet")), x(xml_util::getAtribute(n, "x", (double)0.0)), y(xml_util::getAtribute(n, "y", (double)0.0)), z(xml_util::getAtribute(n, "z", (double)0.0))
{

}

XBField::XBField():x(0),y(0),z(0)
{

}

Xgear::Xgear(rapid_xml_node* n) {

  auto glob = rapid_xml_node(n->value->first_node("global"));
  detectorName = xml_util::getAtribute(&glob, "detectorName", "notSet");
  auto bf = rapid_xml_node(n->value->first_node("BField"));

  bfield = XBField(&bf);
  auto det = rapid_xml_node((n->value->first_node("detectors")->first_node("detector")));

  detector= Xdetector(&det);

}

Xgear::Xgear()
{

}

Xgear::Xgear(const char* name)
{
  *this = load_gear(name);
}

Xgear load_gear(const char* name)
{
  rapidxml::file<> m_file(name);
  rapidxml::xml_document<> m_doc;
  m_doc.parse<0>(m_file.data());
  auto g = rapid_xml_node(m_doc.first_node("gear"));
  return Xgear(&g);
}
