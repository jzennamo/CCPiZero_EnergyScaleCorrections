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
  
   // Clustering Effect
  TH2D* E_resClusCheck = new TH2D("EresClusCheck","; Perfect Clustered Energy [MeV]; E^{c}_{clus} Reco. Shower Energy [MeV];",50,0,500,50,0,1000);

  //Corrections
  
  // Fitted 
  // Clustering
  //TF1* E_corr_clus
  // = new TF1("E_corr_clus","(x-15.412)/0.725477",0,5000);
  // Hit Thersholding
  // TF1* E_corr_hit =
  // new TF1("f","0.000785133*(sqrt(2547340000.*x + 665667863369.) - 798389.)",0,5000);
  

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
       shr_trueE_detProf        < 0  ) continue;
       //|| 
       //shr_perfect_clustering_E > 500 || 
       //shr_trueE_detProf        > 500) continue; 
   
    E_resClusCheck->Fill(shr_perfect_clustering_E, E_corr_clus->Eval(shr_energy));

  //E_resClus->Fill(shr_energy,shr_perfect_clustering_E);
  }
  
  TF1* perf = new TF1("perf","[0]*x",0,300);
  perf->SetParameter(0,1);
  perf->SetParameter(1,0);

  TLine *line = new TLine(0,0,250,250);
  line->SetLineColor(kWhite);
  line->SetLineStyle(2);

  // Reco to Perfect Clusters
  TProfile *E_resClusCheckProf = E_resClusCheck->ProfileX("E_resClusCheckProf",0,250,"");
  E_resClusCheckProf->SetLineColor(kRed);
  E_resClusCheckProf->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1");
  E_resClusCheck->Draw("colz");
  E_resClusCheckProf->Draw("same");
  line->Draw("same");
  perf->Draw("same");

  double chi2=0;
  int dof=0;
  double res[10];
  int igood=0;
  
  E_resClusCheckProf->Fit(perf,"R");

  
 //std::cout << E_resClusCheckProf->Chisquare(perf,"R") << std::endl;

     
}
