#include "sct/FileProcessors/rootEventRunOutput.hh"
#include "TTree.h"
#define  X_DEF axesName_t("x")
#define  Y_DEF axesName_t("y")
#define  Occupancy_DEF axesName_t("Occupancy")
#define  Occupancy_error_DEF axesName_t("Occupancy_error")
#define  NumOfEvents_DEF axesName_t("NumOfEvents")
#define  ID_DEF axesName_t("ID")


RunOutput::RunOutput(): x(0), y(0), Occupancy(0), Occupancy_error(0), NumOfEvents(0), ID(0)
{

}

std::vector<axesName_t> getNames() {
  return {
    X_DEF,Y_DEF,Occupancy_DEF,Occupancy_error_DEF,NumOfEvents_DEF,ID_DEF
  };
}
rootEventRunOutput::rootEventRunOutput(const collectionName_t& collectionName, TDirectory* dir):m_collection(collectionName ,getNames(),&m_pc , save2Disk)
{
 m_collection.get_tree()->SetDirectory(dir);
 


 m_rotation =_MAKE_SHARED1(double,0);
 m_totalNumOfEvents =_MAKE_SHARED1(double,0);
 m_total_efficiency =_MAKE_SHARED1(double,0);
 m_error_efficiency =_MAKE_SHARED1(double,0);
 m_residual =_MAKE_SHARED1(double,0);
 m_offset =_MAKE_SHARED1(double,0);
 m_Threshold =_MAKE_SHARED1(double,0);
 m_RunNumber =_MAKE_SHARED1(double,0);
 m_HV =_MAKE_SHARED1(double,0);


 auto outputTree = m_collection.get_tree();

 outputTree->Branch("totalNumOfEvents", m_totalNumOfEvents.get());
 outputTree->Branch("total_efficiency", m_total_efficiency.get());
 outputTree->Branch("error_efficiency", m_error_efficiency.get());
 outputTree->Branch("residual", m_residual.get());
 outputTree->Branch("rotation", m_rotation.get());
 outputTree->Branch("offset", m_offset.get());
 outputTree->Branch("Threshold", m_Threshold.get());
 outputTree->Branch("RunNumber", m_RunNumber.get());
 outputTree->Branch("HV", m_HV.get());



 m_plane = m_collection.getPlane(ID_t(0));
 m_plane.setHitAxisAdress(X_DEF, &m_runOut->x);
 m_plane.setHitAxisAdress(Y_DEF, &m_runOut->y);
 m_plane.setHitAxisAdress(Occupancy_DEF, &m_runOut->Occupancy);
 m_plane.setHitAxisAdress(Occupancy_error_DEF , &m_runOut->Occupancy_error);
 m_plane.setHitAxisAdress(NumOfEvents_DEF, &m_runOut->NumOfEvents);



}




rootEventRunOutput::rootEventRunOutput(const rootEventRunOutput& rhs):m_collection(rhs.m_collection)
{
  m_rotation =_MAKE_SHARED1(double,0);
  m_totalNumOfEvents =_MAKE_SHARED1(double,0);
  m_total_efficiency =_MAKE_SHARED1(double,0);
  m_error_efficiency =_MAKE_SHARED1(double,0);
  m_residual =_MAKE_SHARED1(double,0);
  m_offset =_MAKE_SHARED1(double,0);
  m_Threshold =_MAKE_SHARED1(double,0);
  m_RunNumber =_MAKE_SHARED1(double,0);
  m_HV =_MAKE_SHARED1(double,0);


  auto outputTree = m_collection.get_tree();

  outputTree->Branch("totalNumOfEvents", m_totalNumOfEvents.get());
  outputTree->Branch("total_efficiency", m_total_efficiency.get());
  outputTree->Branch("error_efficiency", m_error_efficiency.get());
  outputTree->Branch("residual", m_residual.get());
  outputTree->Branch("rotation", m_rotation.get());
  outputTree->Branch("offset", m_offset.get());
  outputTree->Branch("Threshold", m_Threshold.get());
  outputTree->Branch("RunNumber", m_RunNumber.get());
  outputTree->Branch("HV", m_HV.get());


  m_plane = m_collection.getPlane(ID_t(0));
  m_plane.setHitAxisAdress(X_DEF, &m_runOut->x);
  m_plane.setHitAxisAdress(Y_DEF, &m_runOut->y);
  m_plane.setHitAxisAdress(Occupancy_DEF, &m_runOut->Occupancy);
  m_plane.setHitAxisAdress(Occupancy_error_DEF, &m_runOut->Occupancy_error);
  m_plane.setHitAxisAdress(NumOfEvents_DEF, &m_runOut->NumOfEvents);
}

rootEventRunOutput& rootEventRunOutput::operator=(const rootEventRunOutput& rhs)
{
  m_collection = rhs.m_collection;
  m_rotation = _MAKE_SHARED1(double,0);
  m_totalNumOfEvents =_MAKE_SHARED1(double,0);
  m_total_efficiency =_MAKE_SHARED1(double,0);
  m_error_efficiency =_MAKE_SHARED1(double,0);
  m_residual =_MAKE_SHARED1(double,0);
  m_offset =_MAKE_SHARED1(double,0);
  m_Threshold =_MAKE_SHARED1(double,0);
  m_RunNumber =_MAKE_SHARED1(double,0);
  m_HV =_MAKE_SHARED1(double,0);


  auto outputTree = m_collection.get_tree();

  outputTree->Branch("totalNumOfEvents", m_totalNumOfEvents.get());
  outputTree->Branch("total_efficiency", m_total_efficiency.get());
  outputTree->Branch("error_efficiency", m_error_efficiency.get());
  outputTree->Branch("residual", m_residual.get());
  outputTree->Branch("rotation", m_rotation.get());
  outputTree->Branch("offset", m_offset.get());
  outputTree->Branch("Threshold", m_Threshold.get());
  outputTree->Branch("RunNumber", m_RunNumber.get());
  outputTree->Branch("HV", m_HV.get());


  m_plane = m_collection.getPlane(ID_t(0));
  m_plane.setHitAxisAdress(X_DEF, &m_runOut->x);
  m_plane.setHitAxisAdress(Y_DEF, &m_runOut->y);
  m_plane.setHitAxisAdress(Occupancy_DEF, &m_runOut->Occupancy);
  m_plane.setHitAxisAdress(Occupancy_error_DEF, &m_runOut->Occupancy_error);
  m_plane.setHitAxisAdress(NumOfEvents_DEF, &m_runOut->NumOfEvents);
  return *this;
}

rootEventRunOutput::~rootEventRunOutput()
{

}

void rootEventRunOutput::set_TotalNumOfEvents(double numOfEvents)
{
  *m_totalNumOfEvents = numOfEvents;
}

void rootEventRunOutput::set_Total_efficiency(double effi)
{
  *m_total_efficiency = effi;
}

void rootEventRunOutput::set_Error_efficiency(double error_effi)
{
  *m_error_efficiency = error_effi;
}

void rootEventRunOutput::set_Threshold(double thr)
{
  *m_Threshold = thr;
}

void rootEventRunOutput::set_rotation(double rotation_)
{
  *m_rotation = rotation_;
}

void rootEventRunOutput::set_HV(double HV__)
{
  *m_HV = HV__;
}

void rootEventRunOutput::set_residual(double res)
{
  *m_residual = res;
}

void rootEventRunOutput::set_offset(double offset)
{
  *m_offset = offset;
}

void rootEventRunOutput::set_RunNumber(double RunNum)
{
  *m_RunNumber = RunNum;
}

void rootEventRunOutput::reset()
{
  m_collection.clear_event();
  *m_rotation = 0;
  *m_totalNumOfEvents = 0;
  *m_total_efficiency = 0;
  *m_error_efficiency = 0;
  *m_residual = 0;
  *m_offset = 0;
  *m_Threshold = 0;
  *m_RunNumber = 0;
  *m_HV = 0;
}

void rootEventRunOutput::fill()
{
  m_collection.save();
}

void rootEventRunOutput::push(double x, double y, double occ, double occ_err, double numOfEfents, ID_t ID)
{
  m_runOut->NumOfEvents = numOfEfents;
  m_runOut->Occupancy = occ;
  m_runOut->Occupancy_error = occ_err;
  m_runOut->x = x;
  m_runOut->y = y;
  
  m_plane.push(ID);
}
