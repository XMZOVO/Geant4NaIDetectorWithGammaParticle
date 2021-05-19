#include "TFile.h"
#include "TTree.h"
#include "TInterpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
{
////////////////////////////////////////////////////////////////////////////
//Ce code permet de convertir des spectres geant4 et MCNP en spectre avec
// Un FWHM. Cela permet de connaitre le comportement d'un détecteur. Pour 
// Rappel le FWHM peut se calculer comme : 
// FWHM = a + b (E + c E**2)**1/2
// Avec a, b et c qui dépendent du détecteur. 
// Le FWHM est lié au sigma par : FWHM ~ 2.35 sigma
/////////////////////////////////////////////////////////////////////////////

TString dataname= "Co60", fileEx= ".root",Fin= "Fin";
    TString filename= "/Users/roy/Documents/Geant4EX/lrd_v1/build/data/Am241/Am241-35-20000000";
    TString filepath = "/Users/roy/Documents/Geant4EX/lrd_v1/build/data/Am241/Fin/Am241-35-20000000";

TFile f(filename + fileEx);
TRandom *MT=  new TRandom3();
///////Facteur FWHM
double fa=-0.0137257;
double fb=0.0739501;
double fc=-0.152982;
double FWHM=0.0;
double edepG4=0.0;
// double edepMCNP=0.0;
/////////////////////////

//Read G4Spectrum
TH1D* h1 = (TH1D*)f.Get("EDet1");
TH1D *h2 = new TH1D("Geant4","Geant4",4096,0,1.5);
//Spectre Geant4
for (Int_t i=0;i<h1->GetSize();i++) {
    for(Int_t j=0;j<h1->GetBinContent(i);j++){
    edepG4+=h1->GetBinCenter(i);
    FWHM=fa+fb*sqrt(h1->GetBinCenter(i)+fc*h1->GetBinCenter(i)*h1->GetBinCenter(i));
    double sigma=FWHM/2.35482;
    double r= MT ->Gaus();
    double ener= h1->GetBinCenter(i) + sigma* r;
    h2->Fill(ener);
    }
}
//h2->SaveAs(Fin+ filename+ fileEx);

//TFile *f1=new TFile(filepath + Fin+ filename+ fileEx);//includes TH2F *myHist2;
//TH2F *h=(TH2F*)f1->Get("Geant4");
ofstream fout(filepath +  ".csv");
Int_t entries = h2->GetEntries();
for(int i=1;i<=h2->GetNbinsX();i++) {
for(int j=1;j<=h2->GetNbinsY();j++) {
fout<<h2->GetXaxis()->GetBinCenter(i)<<","<<h2->GetBinContent(i,j) / entries <<endl;
}
}
fout.close();
}


