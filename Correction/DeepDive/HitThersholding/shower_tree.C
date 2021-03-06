#define shower_tree_cxx
#include "shower_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void shower_tree::Loop()
{
   gStyle->SetOptStat(1000000000); 
   gStyle->SetStatBorderSize(0);

   TF1* E_corr_clus =
     new TF1("E_corr_clus","(x-15.412)/0.725477",0,5000);

  
  //15 
  std::vector<TH1D*> RecoE; RecoE.resize(15);
  std::vector<TH1D*> TrueE; TrueE.resize(15);
  
  for(int i = 0; i < RecoE.size(); i++){
    
    RecoE[i] = new TH1D(Form("reco_%d",i), ";Shower Energy [MeV];", 25, 0, 500);
    TrueE[i] = new TH1D(Form("true_%d",i), ";Shower Energy [MeV];", 25, 0, 500);       
 
  }
  
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

    //    if(shr_energy < 50) continue;

    double step = 500./double(RecoE.size());

    for(int i = 0; i < RecoE.size(); i++){
      if(inRange(step*i, step+step*i, shr_trueE_detProf)){
	
	//	RecoE[i]->Fill(shr_energy);
	//	RecoE[i]->Fill(shr_perfect_clustering_E);
	RecoE[i]->Fill(E_corr_clus->Eval(shr_energy));
	TrueE[i]->Fill(shr_trueE_detProf);
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

  for(int i = 0; i < RecoE.size(); i++){
    c[i] = new TCanvas(Form("c_%d",i));
    gStyle->SetOptFit(1111);
    RecoE[i]->SetLineColor(kRed);
    RecoE[i]->SetLineWidth(2);
    TrueE[i]->SetLineColor(kBlack);
    TrueE[i]->SetLineWidth(2);

    fit[i] = new TF1(Form("f_%d",i),"gaus(0)+expo(3)",0,500);
    //fit[i] = new TF1(Form("f_%d",i),"gaus(0)",0,500);
    fit[i]->SetParLimits(0,0,250);
    fit[i]->SetParameter(1,TrueE[i]->GetMean(1));
    fit[i]->SetParameter(2,RecoE[i]->GetRMS(1));
    //fit[i]->SetParameter(3,150);
    //fit[i]->SetParameter(4,150);
    
    TH1F* hist = new TH1F("h","",1,0,1);
    hist->SetLineColor(kBlue);
    hist->SetLineStyle(2);
    hist->SetLineWidth(2);

    
    double max = TMath::Max(TrueE[i]->GetMaximum(),RecoE[i]->GetMaximum())*1.15;
    RecoE[i]->SetMaximum(max);
    RecoE[i]->Draw("");
    RecoE[i]->Fit(Form("f_%d",i),"0");
    fit[i]->SetLineColor(kGreen+3);
    fit[i]->SetLineStyle(2);
    fit[i]->Draw("same");
    TrueE[i]->Draw("same");

    line.DrawLine(RecoE[i]->GetMean(1),0,RecoE[i]->GetMean(1),max);    
    line2.DrawLine(TruncMean(RecoE[i]),0,TruncMean(RecoE[i]),max);

    TLegend* leg = new TLegend(0.1, 0.7, 0.45, 0.92);
    leg->AddEntry(TrueE[i], "Deposited Energy", "l");
    leg->AddEntry(RecoE[i], "E^{C}_{Clus}", "l");
    leg->AddEntry(fit[i], "Gaus+Expo Fit", "l");
    leg->AddEntry(hist, "Mean", "l");
    leg->SetTextSize(0.045);
    leg->Draw("same");

    c[i]->Print(Form("Bin_%d.pdf",i),"pdf");
    
  }

  for(int i = 0; i < RecoE.size(); i++){
    std::cout << fit[i]->GetParameter(1) <<"," << std::endl;
  }

  std::cout << "/n /n /n" << std::endl;

  for(int i = 0; i < RecoE.size(); i++){
    std::cout << fit[i]->GetParError(1)<<"," << std::endl;
  }

}
