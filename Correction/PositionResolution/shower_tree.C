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

  //Corrections
  /*
  // Fitted 
  // Clustering
  TF1* E_corr_clus
   = new TF1("E_corr_clus","(x-15.412)/0.725477",0,5000);
  // Hit Thersholding
  TF1* E_corr_hit =
    new TF1("f","0.000785133*(sqrt(2547340000.*x + 665667863369.) - 798389.)",0,5000);
  */

  // Profile 
  // Clustering
  TF1* E_corr_clus
    = new TF1("E_corr_clus","(x-7.94482)/0.681615",0,5000);
  // Hit Thersholding
  TF1* E_corr_hit =
    new TF1("f","-0.000820487*sqrt(2017450716259. - 3805000000.*x) + 1165.35",0,5000);

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
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
       shr_trueE_detProf        < 0   || 
       shr_perfect_clustering_E > 500 || 
       shr_trueE_detProf        > 500) continue; 
    
    double perDiff = 100*(shr_energy-shr_trueE_detProf)/shr_trueE_detProf;
    double perDiffTot = 100*(E_corr_hit->Eval(E_corr_clus->Eval(shr_energy))-shr_trueE_detProf)/shr_trueE_detProf;
    double corr = E_corr_hit->Eval(E_corr_clus->Eval(shr_energy))/shr_energy;

    if(corr > 0){
      CorrPos->Fill(shr_startz,shr_starty,corr);
      CorrPosN->Fill(shr_startz,shr_starty);
    }

    if((fabs(perDiffTot) < 120 && fabs(perDiff) < 120) || perDiffTot > 0){
      EresPos->Fill(shr_startz,shr_starty,perDiff);    
      EresTotPos->Fill(shr_startz,shr_starty,perDiffTot);    
      
      EresPosN->Fill(shr_startz,shr_starty);    
      EresTotPosN->Fill(shr_startz,shr_starty);    
    }
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


}
