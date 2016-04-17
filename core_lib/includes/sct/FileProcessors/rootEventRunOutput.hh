#ifndef rootEventRunOutput_h__
#define rootEventRunOutput_h__
#include <string>
#include "sct/generic_plane.hh"
#include "sct/collection.h"
#include "sct/ProcessorCollection.h"
#include "TDirectory.h"

class RunOutput {
public:
  RunOutput();
  double x, y, Occupancy, Occupancy_error, NumOfEvents, ID;
};

class rootEventRunOutput {
public:

  rootEventRunOutput(const collectionName_t& collectionName, TDirectory* dir);
  rootEventRunOutput(const rootEventRunOutput& rhs);
  rootEventRunOutput& operator=(const rootEventRunOutput& rhs);
  virtual ~rootEventRunOutput();
//  virtual std::shared_ptr<plane> createPlane(double ID) override;

  void set_TotalNumOfEvents(double numOfEvents);
  void set_Total_efficiency(double effi);
  void set_Error_efficiency(double error_effi);
  void set_Threshold(double thr);
  void set_rotation(double rotation_);
  void set_HV(double HV__);
  void set_residual(double res);
  void set_offset(double offset);
  void set_RunNumber(double RunNum);
  virtual void reset();
  void fill();
  void push(double x, double y, double occ, double occ_err, double numOfEfents, ID_t ID = ID_t(0));
private:
  std::shared_ptr<double> m_rotation;
  std::shared_ptr<double> m_totalNumOfEvents;
  std::shared_ptr<double> m_total_efficiency;
  std::shared_ptr<double> m_error_efficiency;
  std::shared_ptr<double> m_residual;
  std::shared_ptr<double> m_offset;
  std::shared_ptr<double> m_Threshold;
  std::shared_ptr<double> m_RunNumber;
  std::shared_ptr<double> m_HV;
  ProcessorCollection m_pc;
  generic_plane m_plane;
  collection m_collection;
  std::shared_ptr<RunOutput> m_runOut = std::make_shared<RunOutput>();
};

#endif // rootEventRunOutput_h__
