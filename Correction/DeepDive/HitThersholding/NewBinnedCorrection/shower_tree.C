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

   std::vector<double> fitted = {1.48784,
				 1.19033,
				 1.15174,
				 1.10616,
				 1.12766,
				 1.11696,
				 1.0697,
				 1.0619,
				 1.13098,
				 1.09084,
				 1.11489,
				 1.05649};

   TH1D* corr = new TH1D("corr","",20,0,500);
   for(int i = 0; i < fitted.size();i++){
     corr->SetBinContent(i+1, fitted[i]);
   }

   std::vector<double> maxR;
   std::vector<double> minR;

   std::vector<double> Correction;
   
  //15 
  std::vector<TH1D*> RecoE; RecoE.resize(20);
  std::vector<TH1D*> TrueE; TrueE.resize(20);
  double step = 500./double(RecoE.size());
  std::vector<int> bins = {13,
			   31,
			   30,
			   26,
			   20,
			   17,
			   17,
			   13,
			   9,
			   11,
			   9,
			   9,
			   9,
			   9,
			   9,
			   9,
			   9,
			   9,
			   9,
			   9};
  
  for(int i = 0; i < RecoE.size(); i++){
    
    RecoE[i] = new TH1D(Form("reco_%d",i), ";Shower Energy [MeV];", bins[i], max((step*i-2*step),0.), 600);
    TrueE[i] = new TH1D(Form("true_%d",i), ";Shower Energy [MeV];", bins[i], max((step*i-2*step),0.), 600);       
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

    double corrected = shr_energy*corr->GetBinContent(corr->GetXaxis()->FindBin(shr_energy));
    
    if(shr_perfect_clustering_E < 0 || 
       shr_trueE_detProf        < 0 || 
       shr_energy               <= 0|| 
       corrected                <= 0) continue; 

    //    if(shr_energy < 50) continue;
    tot++;
    if(shr_energy < 300) counted++; 
    

    
    for(int i = 0; i < RecoE.size(); i++){
      if(inRange(step*i, step+step*i, corrected)){	
	//	RecoE[i]->Fill(shr_energy);
	//	RecoE[i]->Fill(shr_perfect_clustering_E);
	RecoE[i]->Fill(corrected);
	TrueE[i]->Fill(shr_trueE_detProf);
	
	if(shr_trueE_detProf > maxR[i] && shr_trueE_detProf < 3*step+step*i) maxR[i] = shr_trueE_detProf; 
	if(shr_trueE_detProf < minR[i]) minR[i] = shr_trueE_detProf; 
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

  for(int i = 0; i < 12; i++){
    c[i] = new TCanvas(Form("c_%d",i));
    gStyle->SetOptFit(1111);
    TrueE[i]->Sumw2();
    TrueE[i]->SetLineColor(kRed);
    TrueE[i]->SetLineWidth(2);
    RecoE[i]->SetLineColor(kBlack);
    RecoE[i]->SetLineWidth(2);

    int binmax = TrueE[i]->GetMaximumBin(); double x = TrueE[i]->GetXaxis()->GetBinCenter(binmax);

    fit[i] = new TF1(Form("f_%d",i),"gaus(0)+expo(3)",x-1*(TrueE[i]->GetRMS(1)),x+1*(TrueE[i]->GetRMS(1)));  
    //    fit[i] = new TF1(Form("f_%d",i),ExpGaus,TruncMean(TrueE[i])*0.5,TruncMean(TrueE[i])+(TrueE[i]->GetRMS(1)*5),4);  
    //fit[i] = new TF1(Form("f_%d",i),ExpGaus,TruncMean(TrueE[i])*0.5,TruncMean(TrueE[i])*1.5,4);
    fit[i]->SetParLimits(0,0,100);
    fit[i]->SetParLimits(1,x-1*(TrueE[i]->GetRMS(1)),x+1*(TrueE[i]->GetRMS(1)));
    //    fit[i]->SetParLimits(2,7,30);
    //    fit[i]->SetParLimits(3,0,200);
    //    fit[i]->SetParameter(1,TruncMean(TrueE[i]));
    fit[i]->SetParameter(1,x);
    fit[i]->SetParameter(2,TrueE[i]->GetRMS(1));
    //    fit[i]->SetParameter(3,0.01);
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

    
    double max = TMath::Max(RecoE[i]->GetMaximum(),TrueE[i]->GetMaximum())*1.15;
    TrueE[i]->SetMaximum(max);
    TrueE[i]->Draw("");
    TrueE[i]->Fit(Form("f_%d",i),"0");

    fit[i]->SetLineColor(kGreen+3);
    fit[i]->SetLineStyle(2);
    fit[i]->Draw("same");
    RecoE[i]->Draw("same");
    TrueE[i]->Draw("same");

    line.DrawLine(x,0,x,max);    
    line2.DrawLine(TruncMean(TrueE[i],x),0,TruncMean(TrueE[i],x),max);
    TLegend* leg = new TLegend(0.1, 0.7, 0.55, 0.92);
    leg->AddEntry(RecoE[i], Form("E^{C}_{Clust} [%4.0f,%4.0f]",step*i,step+step*i), "l");
    leg->AddEntry(TrueE[i], "Deposited Shower Energy", "l");
    leg->AddEntry(fit[i], Form("Gauss+Exp Fit [%4.0f,%4.0f]",TruncMean(TrueE[i])*0.5,TruncMean(TrueE[i])*1.5), "l");
    leg->AddEntry(hist, Form("Max Bin : %4.1f",x), "l");
    leg->AddEntry(hist2, Form("Truncated Mean : %4.1f", TruncMean(TrueE[i],x)), "l");
    leg->SetTextSize(0.045);
    leg->Draw("same");

    c[i]->Print(Form("Bin_%d.pdf",i),"pdf");
    
    Correction.push_back(x/RecoE[i]->GetMean());

  }

  for(int i = 0; i < 12; i++){
    //std::cout << int(sqrt(TrueE[i]->Integral())) << std::endl;
    std::cout << Correction[i] << std::endl;
    //std::cout << fit[i]->GetParameter(1) << std::endl;
  }

  for(int i = 0; i < 12; i++){
    //    std::cout << fit[i]->GetParError(1)<<"," << std::endl;
  }

  //std::cout << counted << " / " << tot << std::endl; 

}
