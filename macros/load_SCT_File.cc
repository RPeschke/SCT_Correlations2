
#include <fstream>
#include <vector>
#include <string> 
#include <algorithm>
#include <TTree.h>

bool contains_element(std::vector<std::string> const& items, std::string const& item){
  return std::find(items.begin(), items.end(), item) != items.end();
}

void load_SCT_File(TFile* f){
    std::vector<std::string> used_names;
    TIter next(f->GetListOfKeys());
    TKey *key;
    char s[64];
     sprintf(s, "%d", int(gRandom->Rndm(0)*1000000));
    std::ofstream out("dummy.cc");
    
    
    
    
    
    
    
    
    
    
    std::string className = std::string("SCT_File_") + std::string(s);
    out << "class " << className<<" : public EUTFile { public:\n";
    out << "  " << className << "(TFile* inputFile, ProcessorCollection* pc = 0) : EUTFile (inputFile,pc) {} \n\n";
    while ((key=(TKey*)next())) { 
        if (contains_element(used_names, key->GetName())){
            continue;
        }
        TTree* tt = (TTree*)f->Get(key->GetName());
        TIter nextBranch(tt->GetListOfBranches());
        TKey *keyBranch;
        out << "  struct " << key->GetName() <<"_t  {\n";
        while ((keyBranch=(TKey*)nextBranch())) { 
            out << "    generic_plane_slice_handler " << keyBranch->GetName() <<";\n";
        }
        
        
        
        
        out << "  generic_plane " << key->GetName() 
        << " (){ \n    return getCollection(collectionName_t(\"" 
        << key->GetName()  << "\"))->getPlane(ID_t(0));\n" <<
        "  }\n\n";
        used_names.push_back(key->GetName());
        printf("key: %s points to an object of class: %s at %dn \n", key->GetName(), key->GetClassName(),key->GetSeekKey()); 
    }
    out << "};\n";
}