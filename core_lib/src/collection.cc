#include "sct/collection.h"
#include "sct/internal/TTreeVectorExtractor.hh"
#include "TTree.h"
#include "TBranch.h"
#include "sct/generic_plane.hh"
#include "sct/axis.hh"
#include "sct/processor_prob.hh"


std::vector<double> *getAxisByName(const axesName_t& name, std::vector<std::shared_ptr<TTreeVectorExtractor>>& data) {
  for (auto&e : data) {
    if (axesName_t(e->getName()) == name) {
      return e->getVec();
    }
  }
  return nullptr;
}
collection::collection(TTree* tree, ProcessorCollection* pc) :m_pc(pc),m_tree(tree), m_collectionName(collectionName_t( tree->GetName())) {
  auto entries = tree->GetListOfBranches()->GetEntries();
  
  for (int i = 0; i < entries; i++)
  {
    auto br = dynamic_cast<TBranch*>(tree->GetListOfBranches()->At(i));
    if (!br) {
      continue;
    }
    auto className = br->GetClassName();
    if (strcmp("vector<double>", className) != 0) {
      continue;
    }

    m_data.push_back(_MAKE_SHARED1(TTreeVectorExtractor, sct_type::AxesName_t(br->GetName()), tree));
  }
  m_event_nr = _MAKE_SHARED1(int, 0);

  tree->SetBranchAddress("event_nr", m_event_nr.get());

}

collection::collection(const collectionName_t& collectionName, const std::vector<axesName_t>& axis_list, ProcessorCollection* pc, SaveOption save) :m_collectionName(collectionName), m_pc(pc) {
  for (auto&e : axis_list) {
    m_data.push_back(_MAKE_SHARED1(TTreeVectorExtractor,necessary_CONVERSION(e)));
  }
  m_event_nr = _MAKE_SHARED1(int,0);

  if (save == save2Disk) {
    outPutTree = _MAKE_SHARED1(TTree, necessary_CONVERSION(collectionName).c_str(), necessary_CONVERSION(collectionName).c_str());
    for (auto& e : m_data) {
      e->push2TTree(outPutTree.get());
    }
    outPutTree->Branch("event_nr", m_event_nr.get());
  }
  m_tree = outPutTree.get();
}

collection::collection(const collection& coll) :
  m_collectionName(coll.m_collectionName), m_pc(coll.m_pc) ,m_event_nr(coll.m_event_nr),m_data(coll.m_data),m_tree(coll.m_tree), outPutTree(coll.outPutTree)
{

}

collection::collection(const processor_prob& pprob):collection(strong_cast<collectionName_t>( pprob.name),pprob.axisNames,pprob.ProcessorColl,pprob.getSave())
{

}

collection& collection::operator=(const collection& coll)
{
  m_collectionName=coll.m_collectionName;
  m_pc=coll.m_pc;
  m_event_nr=coll.m_event_nr;
  m_data=coll.m_data; 
  m_tree=coll.m_tree; 
  outPutTree=coll.outPutTree;

    return *this;
}


void collection::add_Axis(const axesName_t& axis_name)
{
  auto newAxis = Snew TTreeVectorExtractor(necessary_CONVERSION(axis_name));
  m_data.push_back(newAxis);
  if (outPutTree) {
    newAxis->push2TTree(outPutTree.get());
  }
}

generic_plane collection::getPlane(ID_t planeID) {
  auto ID = getAxisByName(axesName_t("ID"), m_data);

  auto ret = generic_plane(planeID, ID, m_pc, get_tree());

  for (auto&e : m_data) {
    if (e->getName() != "ID") {
      ret.add_axis(axesName_t(e->getName()), e->getVec());
    }
  }

  return ret;
}

axis collection::getAxis(ID_t planeID, const axesName_t& axis_name) {
  auto ID = getAxisByName(axesName_t("ID"), m_data);
  auto axis_ = getAxisByName(axis_name, m_data);
  return axis(planeID, ID, axis_name, axis_, m_pc,get_tree());
}

void collection::set_Event_Nr(int EventNR)
{
  *m_event_nr = EventNR;
}


int collection::get_Event_Nr() const {
  return *m_event_nr;
}

void collection::clear_event(){
  for (auto& e:m_data)  {
    e->reset();
  }
}

void collection::clear_collection()
{
  if (outPutTree) {
    outPutTree->Reset();
  }
}

#ifdef _DEBUG
void collection::load() {
  for (auto& e : m_data) {
    e->loadFromVector();
  }
}
#endif // _DEBUG

void collection::save() {


  if (outPutTree) {
#ifdef _DEBUG
    for (auto& e : m_data) {
      e->PushToVector();
    }
#endif // _DEBUG
    outPutTree->Fill();
  }
}

collectionName_t collection::get_name() {
  return m_collectionName;

}

ProcessorCollection* collection::get_ProcessorCollection()
{
  return m_pc;
}

TTree* collection::get_tree(){
  return m_tree;
}
