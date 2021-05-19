{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile f("/Users/roy/Documents/Geant4EX/lrd_v1/build/EuCs-35-20000000.root");
    
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->SetLogy(1);
  c1->cd();
  c1->Update();
  
  TH1D* hist = (TH1D*)f.Get("EDet1");
  hist->Draw("HIST");    
}  
