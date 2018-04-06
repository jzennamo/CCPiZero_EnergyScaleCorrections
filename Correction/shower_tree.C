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
  
  
//   In a ROOT session, you can do:
//      root> .L shower_tree.C
//      root> shower_tree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//
  
  // Overall Energy Resolution
  TH2D* E_resDep = new TH2D("EresDep",";Deposited Shower Energy [MeV]; Reco Shower Energy [MeV];",50,0,500,50,0,500);

  // Clustering Effect
  TH2D* E_resClus = new TH2D("EresClus","; Perfect Clustered Energy [MeV]; Reco Shower Energy [MeV];",25,0,500,25,0,500);

  // Hit Threshold Correction
  TH2D* E_resHit = new TH2D("EresHit",";Deposited Shower Energy [MeV]; E^{c}_{clus} Reco. Shower Energy [MeV];",25,0,500,25,0,500);

  // Full Correction
  TH2D* E_resTot = new TH2D("EresTot",";Deposited Shower Energy [MeV]; E^{c}_{Tot.} Reco. Shower Energy [MeV];",25,0,500,25,0,500);

  // Full Correction
  TH2D* E_resTrue = new TH2D("EresTrue",";True Shower Energy [MeV]; E^{c}_{Tot.} Reco. Shower Energy [MeV];",25,0,500,25,0,500);


  TH1D* Eres1D = new TH1D("Eres1D",";(E_{reco}-E_{dep})/E_{dep} [%];",25,-100,100);
  TH1D* EresClus1D = new TH1D("EresClus1D",";(E^{c}_{clus}-E_{dep})/E_{dep} [%];",25,-100,100);
  TH1D* EresTot1D = new TH1D("EresTot1D",";(E^{c}_{tot}-E_{dep})/E_{dep} [%];",25,-100,100);


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

    E_resDep->Fill(shr_trueE_detProf,shr_energy);

    E_resClus->Fill(shr_perfect_clustering_E, shr_energy);
    
    E_resHit->Fill(shr_trueE_detProf, E_corr_clus->Eval(shr_energy));

    E_resTot->Fill(shr_trueE_detProf, E_corr_hit->Eval(E_corr_clus->Eval(shr_energy)));
    
    E_resTrue->Fill(shr_trueE, E_corr_hit->Eval(E_corr_clus->Eval(shr_energy)));


    Eres1D->Fill(100*(shr_energy-shr_trueE_detProf)/shr_trueE_detProf);
    EresClus1D->Fill(100*(E_corr_clus->Eval(shr_energy)-shr_trueE_detProf)/shr_trueE_detProf);
    EresTot1D->Fill(100*(E_corr_hit->Eval(E_corr_clus->Eval(shr_energy))-shr_trueE_detProf)/shr_trueE_detProf);


  //E_resClus->Fill(shr_energy,shr_perfect_clustering_E);
  }

  TLine *line = new TLine(0,0,250,250);
  line->SetLineColor(kWhite);
  line->SetLineStyle(2);

  // Reco to Perfect Clusters
  TProfile *E_resClusProf = E_resClus->ProfileX("E_resClusProf",0,250,"");
  E_resClusProf->SetLineColor(kRed);
  E_resClusProf->SetLineWidth(2);

  // Corrected to E dep
  TProfile *E_resHitProf = E_resHit->ProfileX("E_resHitProf",0,250,"");
  E_resHitProf->SetLineColor(kRed);
  E_resHitProf->SetLineWidth(2);

  //Fully Corrected 
  TProfile *E_resTotProf = E_resTot->ProfileX("E_resTotProf",0,250,"");
  E_resTotProf->SetLineColor(kRed);
  E_resTotProf->SetLineWidth(2);

  //Corrected to True Shower
  TProfile *E_resTrueProf = E_resTrue->ProfileX("E_resTrueProf",0,250,"");
  E_resTrueProf->SetLineColor(kRed);
  E_resTrueProf->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1");
  E_resClus->Draw("colz");
  E_resClusProf->Draw("same");
  line->Draw("same");

  TCanvas* c2 = new TCanvas("c2");
  E_resClusProf->Draw();
  TF1* fitClus = new TF1("fitClus","pol1",0,250);
  gStyle->SetOptFit(1111);
  E_resClusProf->Fit("fitClus");
  

  TCanvas* c3 = new TCanvas("c3");
  E_resHit->Draw("colz");
  E_resHitProf->Draw("same");
  line->Draw("same");

  TCanvas* c4 = new TCanvas("c4");
  E_resHitProf->Draw();
  TF1* fitHit = new TF1("fitHit","pol2",0,250);
  E_resHitProf->Fit("fitHit");


  TCanvas* c5 = new TCanvas("c5");
  E_resTot->Draw("colz");
  E_resTotProf->Draw("same");
  line->Draw("same");

  TCanvas* c6 = new TCanvas("c6");
  E_resTotProf->Draw();
  
  TCanvas* c7 = new TCanvas("c7");
  E_resTrue->Draw("colz");
  E_resTrueProf->Draw("same");
  line->Draw("same");

  TCanvas* c8 = new TCanvas("c8");
  Eres1D->SetLineColor(kRed);
  EresClus1D->SetLineColor(kOrange);
  EresTot1D->SetLineColor(kGreen);
  Eres1D->SetLineWidth(2);
  EresClus1D->SetLineWidth(2);
  EresTot1D->SetLineWidth(2);
  Eres1D->Draw();
  //EresClus1D->Draw("same");
  //EresTot1D->Draw("same");

  TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
  leg->AddEntry(Eres1D, "Uncorrected", "pl");
  //  leg->AddEntry(EresClus1D, "Clustering Correction", "pl");
  //leg->AddEntry(EresTot1D, "Total Correction", "pl");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  leg->Draw("same");
  
  TCanvas* c9 = new TCanvas("c9");  
  E_resDep->Draw("colz");

     
}
