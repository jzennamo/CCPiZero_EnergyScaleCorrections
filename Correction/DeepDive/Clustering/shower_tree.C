#define shower_tree_cxx
#include "shower_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Double_t ExpGaus(Double_t *x, Double_t *par){

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

   //   TF1* E_corr_clus =
   //  new TF1("E_corr_clus",Form("(x-%f)/%f",7.94482,0.681615),0,5000);

   std::vector<double> maxR;
   std::vector<double> minR;
  
  //15 
  std::vector<TH1D*> RecoE; RecoE.resize(15);
  std::vector<TH1D*> TrueE; TrueE.resize(15);
  double step = 500./double(RecoE.size());
  std::vector<int> bins = {17,
			   31,
			   29,
			   26,
			   21,
			   19,
			   15,
			   14,
			   12,
			   9,
			   9,
			   9,
			   9,
			   9,
                           9};

  
  for(int i = 0; i < RecoE.size(); i++){
    
    RecoE[i] = new TH1D(Form("reco_%d",i), ";Shower Energy [MeV];", bins[i], 0, 3*step+step*i);
    TrueE[i] = new TH1D(Form("true_%d",i), ";Shower Energy [MeV];", bins[i], 0, 3*step+step*i);       
    maxR.push_back(0);
    minR.push_back(1000000000);
    
  }
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();

  int tot = 0;
  int counted = 0;
  
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

    //    if(shr_energy < 50) continue;
    tot++;
    if(shr_energy < 366.667) counted++; 
    for(int i = 0; i < RecoE.size(); i++){
      if(inRange(step*i, step+step*i, shr_perfect_clustering_E)){	
	//	RecoE[i]->Fill(shr_energy);
	//	RecoE[i]->Fill(shr_perfect_clustering_E);
	RecoE[i]->Fill(shr_energy);
	TrueE[i]->Fill(shr_perfect_clustering_E);
	
	if(shr_energy > maxR[i] && shr_energy < 3*step+step*i) maxR[i] = shr_energy; 
	if(shr_energy < minR[i]) minR[i] = shr_energy; 
	break;
      }      
    }
  }
  
  std::vector<TCanvas*> c; c.resize(RecoE.size());

  TLine line; 
  line.SetLineColor(kBlue);
  line.SetLineStyle(2);
  line.SetLineWidth(2);

  TLine line2; 
  line2.SetLineColor(kGreen);
  line2.SetLineStyle(2);
  line2.SetLineWidth(2);
  
  std::vector<TF1*> fit; fit.resize(RecoE.size());

  for(int i = 0; i < 11; i++){
    c[i] = new TCanvas(Form("c_%d",i));
    gStyle->SetOptFit(1111);
    RecoE[i]->Sumw2();
    RecoE[i]->SetLineColor(kRed);
    RecoE[i]->SetLineWidth(2);
    TrueE[i]->SetLineColor(kBlack);
    TrueE[i]->SetLineWidth(2);

    //    fit[i] = new TF1(Form("f_%d",i),"gaus(0)+expo(3)",0,1000);  
    fit[i] = new TF1(Form("f_%d",i),ExpGaus,TruncMean(RecoE[i])*0.5,TruncMean(RecoE[i])*1.5,4);

    fit[i]->SetParLimits(1,(step+step*i)*0.65,maxR[i]);
    fit[i]->SetParLimits(2,7,30);
    //    fit[i]->SetParLimits(3,0,200);
    //    fit[i]->SetParameter(1,TruncMean(RecoE[i]));
    fit[i]->SetParameter(1,step*i);
    fit[i]->SetParameter(2,RecoE[i]->GetRMS(1));
    fit[i]->SetParameter(3,0.01);
    //fit[i]->SetParameter(3,150);
    //fit[i]->SetParameter(4,150);
    
    TH1F* hist = new TH1F("h","",1,0,1);
    hist->SetLineColor(kBlue);
    hist->SetLineStyle(2);
    hist->SetLineWidth(2);

    TH1F* hist2 = new TH1F("h2","",1,0,1);
    hist2->SetLineColor(kGreen);
    hist2->SetLineStyle(2);
    hist2->SetLineWidth(2);

    
    double max = TMath::Max(TrueE[i]->GetMaximum(),RecoE[i]->GetMaximum())*1.15;
    RecoE[i]->SetMaximum(max);
    RecoE[i]->Draw("");
    RecoE[i]->Fit(Form("f_%d",i),"0");

    fit[i]->SetLineColor(kGreen+3);
    fit[i]->SetLineStyle(2);
    fit[i]->Draw("same");
    TrueE[i]->Draw("same");
    RecoE[i]->Draw("same");

    line.DrawLine(RecoE[i]->GetMean(1),0,RecoE[i]->GetMean(1),max);    
    line2.DrawLine(TruncMean(RecoE[i]),0,TruncMean(RecoE[i]),max);
    TLegend* leg = new TLegend(0.1, 0.7, 0.55, 0.92);
    leg->AddEntry(TrueE[i], Form("Perfect Clus. [%4.0f,%4.0f]",step*i,step+step*i), "l");
    leg->AddEntry(RecoE[i], "E_{Reco}", "l");
    leg->AddEntry(fit[i], Form("GaussExp Fit [%4.0f,%4.0f]",TruncMean(RecoE[i])*0.5,TruncMean(RecoE[i])*1.5), "l");
    leg->AddEntry(hist, "Mean", "l");
    leg->SetTextSize(0.045);
    leg->Draw("same");

    c[i]->Print(Form("Bin_%d.pdf",i),"pdf");
    
  }

  for(int i = 0; i < 11; i++){
    //std::cout << int(sqrt(RecoE[i]->Integral())) << std::endl;
    //std::cout << TruncMean(RecoE[i]) <<"," << std::endl;
    std::cout << fit[i]->GetParameter(1) << std::endl;
  }

  for(int i = 0; i < 11; i++){
    std::cout << fit[i]->GetParError(1)<<"," << std::endl;
  }

  std::cout << counted << " / " << tot << std::endl; 

}
