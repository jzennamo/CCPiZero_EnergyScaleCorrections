#define tree_cxx
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree::Loop()
{

  double maxpi0 = 0;
  
  std::vector< string > bkgds;
  if(data){bkgds = {"data"};}
  else{ bkgds = {"sig","fsem","sce","mult","nc","other", "cosplusnu"};}  
  std::vector<TH1D* > Nshw;  Nshw.resize(bkgds.size()); 
  std::vector<TH1D*> Mult;  Mult.resize(bkgds.size()); 
  std::vector<TH1D*> Vy;  Vy.resize(bkgds.size());
  std::vector<TH1D*> Vx;  Vx.resize(bkgds.size());
  std::vector<TH1D*> Vz;  Vz.resize(bkgds.size());
  std::vector<TH1D*> Lmu;  Lmu.resize(bkgds.size());
  std::vector<TH1D*> muCosTheta;  muCosTheta.resize(bkgds.size());
  std::vector<TH1D*> muPhi;  muPhi.resize(bkgds.size());
  std::vector<TH1D*> TrunMeandQdx;  TrunMeandQdx.resize(bkgds.size());
  std::vector<TH1D*> OpenAngle;  OpenAngle.resize(bkgds.size());
  std::vector<TH1D*> ConvDist;  ConvDist.resize(bkgds.size());
  std::vector<TH1D*> Egamma;  Egamma.resize(bkgds.size());
  std::vector<TH1D*> Mass;  Mass.resize(bkgds.size());
  std::vector<TH1D*> EgammaCorr;  EgammaCorr.resize(bkgds.size());
  std::vector<TH1D*> MassCorr;  MassCorr.resize(bkgds.size());
  std::vector<TH1D*> TrueE;  TrueE.resize(bkgds.size());
  
  for(int i = 0; i < bkgds.size(); i++){
              
    Nshw[i] = 
      new TH1D(Form("Nshw_%s",bkgds[i].c_str()),";;",6,0,6);        
    Mult[i] = 
      new TH1D(Form("Mult_%s",bkgds[i].c_str()),";;",5,1,5);        
    Vy[i] = 
      new TH1D(Form("Vy_%s",bkgds[i].c_str()),";;",15,-100,100);          
    Vx[i] = 
      new TH1D(Form("Vx_%s",bkgds[i].c_str()),";;",15,0,240);          
    Vz[i] = 
      new TH1D(Form("Vz_%s",bkgds[i].c_str()),";;",15,0,1000);          
    Lmu[i] = 
      new TH1D(Form("Lmu_%s",bkgds[i].c_str()),";;",15,40,1000);         
    muCosTheta[i] = 
      new TH1D(Form("muCosTheta_%s",bkgds[i].c_str()),";;",15,-1,1);     
    muPhi[i] = 
      new TH1D(Form("muPhi_%s",bkgds[i].c_str()),";;",15,-3.15,3.15);       
    TrunMeandQdx[i] = 
      new TH1D(Form("TrunMeandQdx_%s",bkgds[i].c_str()),";;",15, 0, 70000);
    OpenAngle[i] = 
      new TH1D(Form("OpenAngle_%s",bkgds[i].c_str()),";;",10,0.35,3.15);   
    ConvDist[i] = 
      new TH1D(Form("ConvDist_%s",bkgds[i].c_str()),";;", 15, 3.5, 60);    
    Egamma[i] = 
      new TH1D(Form("Egamma_%s",bkgds[i].c_str()),";;", 15, 0, 1200 );      
    Mass[i] = 
      new TH1D(Form("Mass_%s",bkgds[i].c_str()),";;",80,0,800);        
   EgammaCorr[i] = 
      new TH1D(Form("EgammaCorr_%s",bkgds[i].c_str()),";;", 15, 0, 1200 );      
    MassCorr[i] = 
      new TH1D(Form("MassCorr_%s",bkgds[i].c_str()),";;",80,0,800);        

    TrueE[i] = 
      new TH1D(Form("TrueE_%s",bkgds[i].c_str()),";;",10,0,500);        
    
  }


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   int Sig = 0;
   int All = 0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      int c = -1;
      if(!twoshow){
	if(bkgd_id == 2){ c = 0;} //signal     
	else if(((bkgd_id == 4  || 
		  bkgd_id == 9  || 
		  bkgd_id == 10 || 
		  bkgd_id==11   || 
		  bkgd_id ==12  || 
		  bkgd_id ==13) && (gamma_type == 1))){ c = 1;} //FSEM
	else if(bkgd_id == 8){ c = 2; } // SCE
	else if(bkgd_id == 5){ c = 3; } // mult-pizero
	else if(bkgd_id == 3){ c = 4; } // NC pizero
	else if(bkgd_id == 1 || gamma_origin == 2){ c = 6; } //cos nu
	else if(bkgd_id == 0 || 
		bkgd_id == 6 || 
		bkgd_id == 7 || ((bkgd_id == 4  || 
				  bkgd_id == 9  ||
				  bkgd_id == 10 || 
				  bkgd_id == 11 ||
				  bkgd_id ==12  || 
				  bkgd_id ==13) && gamma_type != 1)){ c = 5;}//other
	else if(data){ c = 0;}
	else{std::cout << "da fuck " << bkgd_id << " is MC? " << data << std::endl; continue;}
      }
      else{
	if(bkgd_id == 2){ c = 0;} //signal     
	else if(bkgd_id == 3){ c = 4; } // NC pizero
	else if(bkgd_id == 5){ c = 3; } // mult-pizero
	else if(bkgd_id == 8){ c = 2; } // SCE
	else if(((bkgd_id == 4  || 
		  bkgd_id == 9  || 
		  bkgd_id == 10 || 
		  bkgd_id==11   || 
		  bkgd_id ==12  || 
		  bkgd_id ==13) && (pi0_low_type == 1 || pi0_high_type == 1))){ c = 1;} //FSEM

	else if(bkgd_id == 1 || pi0_low_origin == 2 || pi0_high_origin == 2){ c = 6;} //cos nu
	else if(bkgd_id == 0 || 
		bkgd_id == 6 || 
		bkgd_id == 7 || ((bkgd_id == 4  || 
				  bkgd_id == 9  ||
				  bkgd_id == 10 || 
				  bkgd_id == 11 ||
				  bkgd_id ==12  || 
				  bkgd_id ==13) && 
				 pi0_low_type != 1 && 
				 pi0_high_type != 1)){ c = 5;}//other
	else if(data){ c = 0;}
	else{std::cout << "da fuck " << bkgd_id << " is MC? " << data << std::endl; continue;}
      }


      if(twoshow){
	if(pi0_high_reco_gammaE < 50 ||
	   pi0_low_reco_gammaE  < 50) continue;
	if(pi0_oangle < 0.35) continue;
	if(pi0_IP > 4) continue;
      }
      else{
	if(gamma_IP_w_vtx > 4) continue;
      }

      Nshw[c]->Fill(nshrs , scale); 
      Mult[c]->Fill(mult, scale); 
      Vy[c]->Fill(vtx_y , scale);
      Vx[c]->Fill(vtx_x , scale);
      Vz[c]->Fill(vtx_z , scale);
      Lmu[c]->Fill(mu_len, scale);
      muCosTheta[c]->Fill(mu_angle, scale);
      muPhi[c]->Fill(mu_phi, scale);
      TrunMeandQdx[c]->Fill(mu_trun_mean_dqdx, scale);
      OpenAngle[c]->Fill(pi0_oangle, scale);
      ConvDist[c]->Fill(gamma_RL, scale);
      Egamma[c]->Fill(gamma_E, scale);
      Mass[c]->Fill(pi0_mass, scale);      
      EgammaCorr[c]->Fill(tree::Ec(gamma_E), scale);
      TrueE[c]->Fill(gamma_trueE, scale);

      // New Two Shower Mass:

      double pi = sqrt(2*tree::Ec(pi0_low_reco_gammaE)*tree::Ec(pi0_high_reco_gammaE)*(1-cos(pi0_oangle))); 

      if(pi < 200){
	All++;
	if(c == 0){Sig++;}
      }

      if(pi > maxpi0) maxpi0 = pi;
      
      MassCorr[c]->Fill(pi, scale);            
   }

   std::cout << "Signal " <<  Sig << " All " << All << std::endl;

   

   TFile* out = new TFile("output_MC.root","RECREATE");
   
   for(int i = 0; i < bkgds.size(); i++){
     
     Nshw[i]->Write();
     Mult[i]->Write();
     Vy[i]->Write();
     Vx[i]->Write();
     Vz[i]->Write();
     Lmu[i]->Write();    
     muCosTheta[i]->Write();
     muPhi[i]->Write();
     OpenAngle[i]->Write();
     ConvDist[i]->Write();
     Egamma[i]->Write();
     Mass[i]->Write();
     EgammaCorr[i]->Write();
     MassCorr[i]->Write();
     TrueE[i]->Write();
   }

   out->Close();
}
