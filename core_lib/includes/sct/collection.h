#ifndef collection_h__
#define collection_h__
#ifndef __CINT__
#include <memory>
#include "sct/internal/TTreeVectorExtractor.hh"
#endif // !__CINT__


#include <string>
#include <vector>
#include "sct/platform.hh"
#include "sct/axis.hh"
#include "sct/generic_plane.hh"
class TTree;
class generic_plane;
class processor_prob;
class ProcessorCollection;
class TTreeVectorExtractor;
enum SaveOption {
  save2Disk,
  DontSave2Disk

};
class DllExport collection {
public:

  collection(TTree* tree, ProcessorCollection* pc);
  collection(const std::string& collectionName, const  std::vector<std::string>& axis_list, ProcessorCollection* pc, SaveOption save = DontSave2Disk);
  collection(const processor_prob& pprob);
  collection(const collection& coll);
  collection& operator=(const collection& coll);
  generic_plane getPlane(double planeID);
  axis getAxis(double planeID, const std::string& axis_name);
  void set_Event_Nr(int EventNR);
  int get_Event_Nr() const;
  void clear();
#ifndef __CINT__
#ifdef _DEBUG
  void load();
#endif
#endif
  void save();
  std::string get_name();
  ProcessorCollection* get_ProcessorCollection();
  TTree* get_tree();
private:
#ifndef __CINT__
  ProcessorCollection* m_pc = nullptr;
  std::shared_ptr<int> m_event_nr;
  std::vector<std::shared_ptr<TTreeVectorExtractor>> m_data;
  std::string m_collectionName;
  std::shared_ptr<TTree> outPutTree;
  TTree* m_tree;
#endif


};



#endif // collection_h__
