#include <fstream>
void save(TGraph* g, std::string FileName){
    double x,y;
    std::ofstream out(FileName.c_str());
    out << "i,x,y\n";
    for(int i = 0 ; i < g->GetN(); ++i){
        g->GetPoint(i,x, y);
        out << i <<"," << x << "," << y <<"\n";
    }


}


void save(TH1* g, std::string FileName){
    double x,y;
    std::ofstream out(FileName.c_str());
    out << "i,x,y\n";
    for(int i = 0 ; i < g->GetNbinsX(); ++i){
        y = g->GetBinContent(i);
        x = g->GetBinCenter(i);
        
        out << i <<"," << x << "," << y <<"\n";
    }


}

void save(TH2F* g, std::string FileName){
    int x_i,y_i,z_i;
    double x,y,z;
    std::ofstream out(FileName.c_str());
    out << "i,x,y,z\n";

    for(int i = 0 ; i < g->GetSize(); ++i){
        
        g->GetBinXYZ(i,x_i,y_i,z_i);
        
        
        out << i <<"," <<g->GetXaxis()->GetBinCenter(x_i)  << "," << g->GetYaxis()->GetBinCenter(y_i)  << "," << g->GetBinContent(i) <<"\n";
    }


}
void save(TH2D* g, std::string FileName){
    int x_i,y_i,z_i;
    double x,y,z;
    std::ofstream out(FileName.c_str());
    out << "i,x,y,z\n";

    for(int i = 0 ; i < g->GetSize(); ++i){
        
        g->GetBinXYZ(i,x_i,y_i,z_i);
        
        
        out << i <<"," <<g->GetXaxis()->GetBinCenter(x_i)  << "," << g->GetYaxis()->GetBinCenter(y_i)  << "," << g->GetBinContent(i) <<"\n";
    }


}