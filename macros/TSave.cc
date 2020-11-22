#include <fstream>
void save(TGraph* g, std::string FileName){
    double x,y;
    std::ofstream out(FileName.c_str());
    out << "i, x, y\n";
    for(int i = 0 ; i < g->GetN(); ++i){
        g->GetPoint(i,x, y);
        out << i <<", " << x << ", " << y <<"\n";
    }


}


void save(TH1* g, std::string FileName){
    double x,y;
    std::ofstream out(FileName.c_str());
    out << "i, x, y\n";
    for(int i = 0 ; i < g->GetNbinsX(); ++i){
        y = g->GetBinContent(i);
        x = g->GetBinCenter(i);
        
        out << i <<", " << x << ", " << y <<"\n";
    }


}