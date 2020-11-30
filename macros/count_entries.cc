void count_entires(TTree * tree , const char* RunNumber , int condition){
    std::ofstream out("out.csv");
    for (int PlaneID = 2; PlaneID <13; PlaneID+= 10){
        for (int x = 1; x <16; x+= 1){
            for (int y = 1; y <11; y+= 1){
                auto cut = TString::Format("PlaneID==%i&&x==%i&&y==%i",PlaneID,x,y );
                int count = tree->Draw("x", cut.Data(),"");
                out <<condition<< ";"<< RunNumber << ";"<< PlaneID <<';' << x << ";" << y<< ";"<< count<<"\n";
            }
        }
    }
}
