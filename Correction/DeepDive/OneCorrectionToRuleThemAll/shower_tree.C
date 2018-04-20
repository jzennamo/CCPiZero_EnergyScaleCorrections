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

   std::vector<double> maxR;
   std::vector<double> minR;

   std::vector<double> Correction;
   
  //15 
  std::vector<TH1D*> RecoE; RecoE.resize(20);
  std::vector<TH1D*> TrueE; TrueE.resize(20);
  double step = 500./double(RecoE.size());
  std::vector<int> bins = {21,
			   33,
			   29,
			   24,
			   20,
			   17,
			   15,
			   12,
			   11,
			   10,
			   8,
			   8,
			   8,
			   8,
			   8,
			   8,
			   8,
			   8,
			   8,
			   8};
  
  for(int i = 0; i < RecoE.size(); i++){
    
    RecoE[i] = new TH1D(Form("reco_%d",i), ";Shower Energy [MeV];", bins[i], max((step*i-2*step),0.), 600);
    //    TrueE[i] = new TH1D(Form("true_%d",i), ";Shower Energy [MeV];", bins[i], max((step*i-2*step),0.), 600);       
    TrueE[i] = new TH1D(Form("true_%d",i), ";Fraction of Deposited Energy in Reco Shower;", bins[i], 0, 1.3);       
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

    
    if(shr_perfect_clustering_E < 0 || 
       shr_trueE_detProf        < 0 ) continue; 

    //    if(shr_energy < 50) continue;
    tot++;
    if(shr_energy < 300) counted++; 
        
    for(int i = 0; i < RecoE.size(); i++){
      if(inRange(step*i, step+step*i, shr_energy)){	
	//	RecoE[i]->Fill(shr_energy);
	//	RecoE[i]->Fill(shr_perfect_clustering_E);
	RecoE[i]->Fill(shr_energy);
	TrueE[i]->Fill(shr_energy/shr_trueE_detProf);
	
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

    fit[i] = new TF1(Form("f_%d",i),ExpGaus,0.4,1.3,4);  
    //fit[i] = new TF1(Form("f_%d",i),ExpGaus,TruncMean(TrueE[i])*0.5,TruncMean(TrueE[i])*1.5,4);
    //fit[i]->SetParLimits(0,0.1*TrueE[i]->GetMaximum(),2*TrueE[i]->GetMaximum());
    fit[i]->SetParLimits(1,0.4,1.3);
    fit[i]->SetParLimits(2,0,2);
    // fit[i]->SetParLimits(3,-1,2);
    //    fit[i]->SetParameter(1,TruncMean(TrueE[i]));
    fit[i]->SetParameter(0,TrueE[i]->GetMaximum());
    fit[i]->SetParameter(1,1);
    fit[i]->SetParameter(2,TrueE[i]->GetRMS());
    fit[i]->SetParameter(3,0.3);
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
    leg->AddEntry(RecoE[i], Form("E^{C}_{Tot} [%4.1f,%4.1f]",step*i,step+step*i), "l");
    leg->AddEntry(TrueE[i], "True Shower Energy", "l");
    leg->AddEntry(fit[i], Form("Gauss+Exp Fit [%4.1f,%4.1f] : #mu = %4.2f",TruncMean(TrueE[i])*0.5,TruncMean(TrueE[i])*1.5, fit[i]->GetParameter(1)), "l");
    leg->AddEntry(hist, Form("Max Bin : %4.2f",x), "l");
    leg->AddEntry(hist2, Form("Truncated Mean : %4.2f", TruncMean(TrueE[i],x)), "l");
    leg->SetTextSize(0.045);
    leg->Draw("same");

    c[i]->Print(Form("Bin_%d.pdf",i),"pdf");
    
    Correction.push_back(x/RecoE[i]->GetMean());

  }

  for(int i = 0; i < 12; i++){
    //std::cout << int(sqrt(TrueE[i]->Integral())) << std::endl;
    //std::cout << Correction[i] << std::endl;
    std::cout << fit[i]->GetParameter(1) << std::endl;
  }

  for(int i = 0; i < 12; i++){
    std::cout << fit[i]->GetParError(1)<<"," << std::endl;
  }

  //std::cout << counted << " / " << tot << std::endl; 

  TCanvas* can = new TCanvas("can");
  TH2D* hist = new TH2D("hist",";Fraction of Deposited Energy in Reconstructed Showers;",1,0.4,1.3,1,0,250);
  hist->Draw();
  fit[0]->SetLineColor(30);
  fit[0]->Draw("same");

  TLegend* leg = new TLegend(0.12, 0.45, 0.88, 0.88);
 
  leg->SetNColumns(2);
  leg->AddEntry(fit[0], Form("[%4.0f,%4.0f]; #mu = %4.2f",step*0,step+step*0,fit[0]->GetParameter(1)), "l");

  for(int i = 1; i <12; i++){
    fit[i]->SetLineColor(30+i);
    fit[i]->Draw("same");
    leg->AddEntry(fit[i], Form("[%4.0f,%4.0f]; #mu = %4.3f",step*i,step+step*i,fit[i]->GetParameter(1)), "l");
  }  
  leg->SetLineColor(kWhite);  
  leg->SetTextSize(0.04);
  leg->Draw("same");


}
