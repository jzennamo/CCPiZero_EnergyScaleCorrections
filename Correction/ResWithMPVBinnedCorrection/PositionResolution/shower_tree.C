#define shower_tree_cxx
#include "shower_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void shower_tree::Loop()
{
  gStyle->SetOptStat(1000000000);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleXSize(0.045);
  gStyle->SetTitleYSize(0.045);
  gStyle->SetTitleX(0.1f);
  gStyle->SetTitleW(0.8f);
  gStyle->SetNumberContours(999);
  
//   In a ROOT session, you can do:
//      root> .L shower_tree.C
//      root> shower_tree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//
  
  // Overall Energy Resolution
  TH2D* EresPos = new TH2D("EresPos",";Shower Start Z [cm]; Shower Start Y [cm]; <(E_{r}-E_{d})/E_{d}> [%]", 45,0,1050,45,-120,120);
  TH2D* EresTotPos = new TH2D("EresTotPos",";Shower Start Z [cm]; Shower Start Y [cm]; <(E^{c}_{T}-E_{d})/E_{d}> [%]", 45,0,1050,45,-120,120);
  TH2D* CorrPos = new TH2D("CorrPos",";Shower Start Z [cm]; Shower Start Y [cm]; <E^{c}_{T}/E_{reco}>", 45,0,1050,45,-120,120);


  TH2D* EresPosN = new TH2D("EresPosN",";Shower Start Z [cm]; Shower Start Y [cm]; <(E_{r}-E_{d})/E_{d}> [%]", 45,0,1050,45,-120,120);
  TH2D* EresTotPosN = new TH2D("EresTotPosN",";Shower Start Z [cm]; Shower Start Y [cm]; <(E^{c}_{T}-E_{d})/E_{d}> [%]", 45,0,1050,45,-120,120);
  TH2D* CorrPosN = new TH2D("CorrPosN",";Shower Start Z [cm]; Shower Start Y [cm]; <E^{c}_{T}/E_{reco}>", 45,0,1050,45,-120,120);

  TF1* go = new TF1("go","(9.93885e-01+x*(3.07774e-04))*x",0,250);
  TF1* gogo = new TF1("gogo","(1.24497+x*(-2.01225e-04))*x",0,250);
  TF1* gogogo = new TF1("gogogo","x*(9.43398e-01+(4.42796e-04)*x)",0,250);

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();

  double AvgCorr = 0;
  int NCorr = 0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    

      
    if(shr_n_reco != 1 ||           // Number of reco showers
       shr_type   != 1 ||           // Tracks back to Shower-like particle
       shr_origin != 1 ||           // From a neutrino
       bkgd_id    != 2) continue;   // CCpizero interaction
    
    if(shr_perfect_clustering_E < 0   || 
       shr_trueE_detProf        < 0) continue; 
    
       double clusE = go->Eval(shr_energy);       
       double hitE = gogo->Eval(clusE);
       double truE = gogogo->Eval(hitE);
       
       double perDiff = 100*(shr_energy-shr_trueE_detProf)/shr_trueE_detProf;
       double perDiffTot = 100*(truE-shr_trueE)/shr_trueE;
       double corr = truE/shr_energy;

       AvgCorr += corr;
       NCorr++;

       
    if(corr > 0){
      CorrPos->Fill(shr_startz,shr_starty,corr);
      CorrPosN->Fill(shr_startz,shr_starty);
    }

       EresPos->Fill(shr_startz,shr_starty,perDiff);    
       EresTotPos->Fill(shr_startz,shr_starty,perDiffTot);    
       
       EresPosN->Fill(shr_startz,shr_starty);    
       EresTotPosN->Fill(shr_startz,shr_starty);    
    
  //E_resClus->Fill(shr_energy,shr_perfect_clustering_E);
  }

  TCanvas* c1 = new TCanvas("c1");
  EresPos->Divide(EresPosN);
  EresPos->Draw("colz");


  TCanvas* c2 = new TCanvas("c2");
  EresTotPos->Divide(EresTotPosN);
  EresTotPos->Draw("colz");


  TCanvas* c3 = new TCanvas("c3");
  CorrPos->Divide(CorrPosN);
  CorrPos->Draw("colz");

  std::cout << "Average Correction : " << AvgCorr/double(NCorr) << std::endl;

}
