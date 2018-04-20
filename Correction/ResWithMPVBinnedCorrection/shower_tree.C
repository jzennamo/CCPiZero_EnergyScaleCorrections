#define shower_tree_cxx
#include "shower_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Double_t Fit(Double_t *x, Double_t *par){

  Double_t arg = 0;
  Double_t xv = x[0];

  if((xv-par[1])/par[2] >= -par[3]){
    arg = -0.5*(pow(((xv-par[1])/par[2]),2));}
  else{
    arg = (pow(par[3],2)/2.)+par[3]*((xv-par[1])/par[2]);}
  
  return par[0]*exp(arg);  
}

void shower_tree::Loop()
{
  gStyle->SetOptStat(1000000000);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleXSize(0.045);
  gStyle->SetTitleYSize(0.045);
  gStyle->SetTitleX(0.1f);
  gStyle->SetTitleW(0.8f);
  
  TF1* go = new TF1("go","(9.93885e-01+x*(3.07774e-04))*x",0,250);
  TF1* gogo = new TF1("gogo","(1.24497+x*(-2.01225e-04))*x",0,250);
  TF1* gogogo = new TF1("gogogo","x*(9.43398e-01+(4.42796e-04)*x)",0,250);


  // Clustering Effect
  TH2D* E_resPerfToDep = new TH2D("EresPerfToDep","; Deposited Shower Energy [MeV]; Perfect Clustered Energy [MeV];",100,0,500,100,0,500);
  TH2D* PurVEreco = new TH2D("PurVEreco","; Reco Shower Energy [MeV];Purity;",100,0,500,100,0.6,1);

  TH2D* E_resClus = new TH2D("EresClus","; Perfect Clustered Energy [MeV]; Reco Shower Energy [MeV];",100,0,500,100,0,500);
  TH2D* E_resClusCheck = new TH2D("EresClusCheck","; Perfect Clustered Energy [MeV]; E^{c}_{clus} Reco. Shower Energy [MeV];",100,0,500,100,0,500);

  TH2D* E_resHit = new TH2D("EresHit","; Deposited Energy [MeV]; E^{c}_{clus} Reco Shower Energy [MeV];",100,0,500,100,0,500);
  TH2D* E_resHitCheck = new TH2D("EresHitCheck","; Deposited Energy [MeV]; E^{c}_{Tot} Reco. Shower Energy [MeV];",100,0,500,100,0,500);

  TH2D* E_resReal = new TH2D("EresReal","; True Energy [MeV]; E^{c}_{clus} Reco Shower Energy [MeV];",100,0,500,100,0,500);
  TH2D* E_resRealCheck = new TH2D("EresRealCheck","; True Energy [MeV]; E^{c}_{True} Reco. Shower Energy [MeV];",100,0,500,100,0,500);

  TH1D* Eres1D = new TH1D("Eres1D",";Percent Difference [%];",30,-100,150);
  TH1D* EresClus1D = new TH1D("EresClus1D",";(E^{c}_{clus}-E_{dep})/E_{dep} [%];",30,-100,150);
  TH1D* EresTot1D = new TH1D("EresTot1D",";(E^{c}_{tot}-E_{dep})/E_{dep} [%];",30,-100,150);
  TH1D* EresTru1D = new TH1D("EresTru1D",";(E^{c}_{tru}-E_{true})/E_{true} [%];",30,-100,150);


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
       shr_trueE_detProf        < 0) continue; 

    //if(shr_energy < 25) continue;

    E_resClus->Fill(shr_perfect_clustering_E, shr_energy);
    double clusE = go->Eval(shr_energy);
    E_resClusCheck->Fill(shr_perfect_clustering_E, clusE);
  
    E_resHit->Fill(shr_trueE_detProf, clusE);
    double hitE = gogo->Eval(clusE);
    E_resHitCheck->Fill(shr_trueE_detProf, hitE);

    E_resReal->Fill(shr_trueE, clusE);
    double truE = gogogo->Eval(hitE);
    E_resRealCheck->Fill(shr_trueE, truE);

    Eres1D->Fill(100*(shr_energy-shr_trueE_detProf)/shr_trueE_detProf);
    EresClus1D->Fill(100*(clusE-shr_trueE_detProf)/shr_trueE_detProf);
    EresTot1D->Fill(100*(hitE-shr_trueE_detProf)/shr_trueE_detProf);
    EresTru1D->Fill(100*(truE-shr_trueE)/shr_trueE);

    E_resPerfToDep->Fill(shr_trueE_detProf,shr_perfect_clustering_E);

    PurVEreco->Fill(shr_energy,shr_purity);


  }

  TLine *line = new TLine(0,0,250,250);
  line->SetLineColor(kWhite);
  line->SetLineStyle(2);

  TCanvas* c1 = new TCanvas("c1");
  E_resClus->Draw("colz");
  line->Draw("same");

  TCanvas* c2 = new TCanvas("c2");
  E_resClusCheck->Draw("colz");
  line->Draw("same");

  TCanvas* c3 = new TCanvas("c3");
  E_resHit->Draw("colz");
  line->Draw("same");

  TCanvas* c4 = new TCanvas("c4");
  E_resHitCheck->Draw("colz");
  line->Draw("same");

  TCanvas* c5 = new TCanvas("c5");
  E_resReal->Draw("colz");
  line->Draw("same");

  TCanvas* c6 = new TCanvas("c6");
  E_resRealCheck->Draw("colz");
  line->Draw("same");


  TCanvas* c7 = new TCanvas("c7");
  Eres1D->SetLineColor(kRed);
  EresClus1D->SetLineColor(kOrange);
  EresTot1D->SetLineColor(kGreen);
  EresTru1D->SetLineColor(kBlue);
  Eres1D->SetLineWidth(2);
  EresClus1D->SetLineWidth(2);
  EresTot1D->SetLineWidth(2);
  Eres1D->SetLineStyle(2);
  EresClus1D->SetLineStyle(2);
  EresTot1D->SetLineStyle(2);
  EresTru1D->SetLineWidth(2);
  Eres1D->Draw();
  EresClus1D->Draw("same");

  TF1* fit = new TF1("fit",Fit,-50,100,4);
  fit->SetParameter(1, 0);
  fit->SetParameter(2, 20); 
  EresTru1D->Draw("same");
  EresTot1D->Draw("same");
  EresTru1D->Fit("fit","R");
  //  std::cout << "Mean : " << EresTot1D->GetMean() << std::endl;

  TLegend* leg = new TLegend(0.55, 0.15, 0.88, 0.88);
  leg->AddEntry(Eres1D, "#frac{E_{reco}-E_{dep}}{E_{dep}}", "pl");
  leg->AddEntry(EresClus1D, "#frac{E^{c}_{clus}-E_{dep}}{E_{dep}}", "pl");
  leg->AddEntry(EresTot1D, "#frac{E^{c}_{tot}-E_{dep}}{E_{dep}}", "pl");
  leg->AddEntry(EresTru1D, "#frac{E^{c}_{tru}-E_{truth}}{E_{truth}}", "pl");
  leg->AddEntry(fit, Form("Bias: (%4.1f #pm %4.1f) %%", fit->GetParameter(1), fit->GetParError(1)), "l");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  leg->Draw("same");

  TCanvas* c35 = new TCanvas("c35");
  E_resPerfToDep->Draw("colz");
  line->Draw("same");

  TCanvas* c78 = new TCanvas("c78");
  PurVEreco->Draw("colz");
  
}
