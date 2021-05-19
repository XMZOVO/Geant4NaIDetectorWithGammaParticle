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
TString filename= "/Users/roy/Documents/Geant4EX/lrd_v1/build/EuCs-35-20000000", fileEx= ".root",Fin= "Fin";

TFile f(filename + fileEx);
TCanvas* c1 = new TCanvas("c1", "My title",800,800);
//c1->SetLogy(1);

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

//Read MCNP Spectrum
// std::ifstream myReadFile;
// TNtuple* a= new TNtuple("a","a","ener:num:err");
// a -> ReadFile("path/file.dat");

// Definition des histogrames
TH1D *h2 = new TH1D("Geant4","Geant4",4096,0,1.5);
// TH1D *h3 = new TH1D("MCNP","MCNP",2000,0,1.6);

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
//Spectre MCNP
// Int_t n=a->GetEntries();
// Float_t num,cps,ener;
// Int_t numpart=500000000;
// a->SetBranchStatus("err*", 0);
//a->SetBranchStatus("ener*", 0);

// for (Int_t k=0; k<n ;k++){
// a->SetBranchAddress("num", &num);
// a->GetEntry(k);
// cps=num*numpart;
// for(Int_t l=0; l<(int)cps ;l++){
//     a->SetBranchAddress("ener", &ener);
//     a->GetEntry(k);
//     edepMCNP+=ener;
//     FWHM=fa+fb*sqrt(ener+fc*ener*ener);
//     double sigma=FWHM/2.35;
//     double r= MT ->Gaus();
//     double ene= ener + sigma* r;
//     h3->Fill(ene);
//     }
// /////////////////////////////////////////////
// }
////////////////////////////////////////////
//////////////////Calcul dose//////////////
// double mevtojoule=1.6021*pow(10,-13);
// double massedet=0.377;
// edepMCNP=edepMCNP*mevtojoule/(numpart*massedet);
// double doset0=edepMCNP*pow(10,13)*60*60;
///////////////////////////////////////////

h2->SetStats(0); //ne display pas la stat box
//h2->SetMaximum(200000);// Max y
h2->SetLineColor(kBlue);
h2->SetTitle("Spectre gamma");
h2->GetXaxis()->SetTitle("Energie [MeV]");
h2->GetYaxis()->SetTitle("Counts");
h2->Draw();
gPad->Update();


// h3->SetLineColor(kRed);
// h3->Draw("same");
// gPad->Update();

auto legend = new TLegend(0.9,0.9,0.68,0.8);
legend->SetHeader("","C"); // option "C" allows to center the header
legend->AddEntry(h2,"Geant4","l");
// legend->AddEntry(h3,"MCNP","l");
legend->Draw();
gPad->Update();
cout<<"Dose Geant4= "<<edepG4<<endl;
// cout<<"Dose MCNP= "<<edepMCNP<<endl;
// cout<<"Dose MCNP= "<<doset0<<endl;
//h2->SaveAs(Fin+ filename+ fileEx);
}