/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 23 12:27:00 2018 by ROOT version 6.08/06
// from TTree tree/
// found on file: ../Files/mc/BT_backgrounds_one.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"


class tree {
 public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   bool            data;
   bool            twoshow;
   double          scale;
   
   //Columbia Method
     //TF1* E_corr_hit =
     //new TF1("E_corr_hit",Form("(x-%f)/%f",1.35107,0.843749),0,5000);
      //   TF1* E_corr_clust =
     //Profile
     //     new TF1("E_corr_clust","1889.43 - 0.00164422*sqrt(1334197988317 - 1923270000*x)",0,5000);
     //Fitted
     //new TF1("E_corr_clust","-2167.82 + 7.89369e-9*sqrt(75038342481055095717888. + 90345043648500006912.*x)",0,5000);

   //On shift Method
   //Corrections

   //Profile
   //TF1* E_corr_clus
   //  = new TF1("E_corr_clus","(x-7.94482)/0.681615",0,5000);   
   //TF1* E_corr_hit 
   //  = new TF1("f","-0.000820487*sqrt(2017450716259. - 3805000000.*x) + 1165.35",0,5000);

   //Fitting 
   //   TF1* E_corr_clus= new TF1("E_corr_clus","(x-15.412)/0.725477",0,5000);   
   //TF1* E_corr_hit = new TF1("f","0.000785133*(sqrt(2547340000.*x + 665667863369.) - 798389.)",0,5000);

   //CrazyIdea
   TF1* E_corr_clus = new TF1("clus","(9.93885e-01+x*(3.07774e-04))*x",0,250);
   TF1* E_corr_hit = new TF1("hit","(1.24497+x*(-2.01225e-04))*x",0,250);
   TF1* E_corr_true = new TF1("true","x*(9.43398e-01+(4.42796e-04)*x)",0,250);

   TF1* go = new TF1("go","(1+((1.44655e-02)*x))/(1+((1.03619e-02)*x))*x",0,250);


   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event_id;
   Int_t           subrun_id;
   Int_t           run_id;
   Int_t           event;
   Int_t           bkgd_id;
   Int_t           nu_mode;
   Int_t           nshrs;
   Float_t         vtx_x;
   Float_t         vtx_y;
   Float_t         vtx_z;
   Float_t         mc_vtx_x;
   Float_t         mc_vtx_y;
   Float_t         mc_vtx_z;
   Float_t         mc_scecorr_vtx_x;
   Float_t         mc_scecorr_vtx_y;
   Float_t         mc_scecorr_vtx_z;
   Float_t         flash_time;
   Int_t           flash_pe;
   Float_t         flash_y_center;
   Float_t         flash_z_center;
   Float_t         flash_y_width;
   Float_t         flash_z_width;
   Float_t         mu_true_angle;
   Float_t         mu_true_phi;
   Float_t         mu_true_mom;
   Float_t         mu_true_startx;
   Float_t         mu_true_starty;
   Float_t         mu_true_startz;
   Float_t         mu_true_endx;
   Float_t         mu_true_endy;
   Float_t         mu_true_endz;
   Float_t         mu_angle;
   Float_t         mu_len;
   Float_t         mu_startx;
   Float_t         mu_starty;
   Float_t         mu_startz;
   Float_t         mu_endx;
   Float_t         mu_endy;
   Float_t         mu_endz;
   Float_t         mu_phi;
   Float_t         mult;
   Float_t         mu_purity;
   Float_t         mu_complete;
   Float_t         mu_cw_purity;
   Float_t         mu_cw_complete;
   Float_t         mu_origin;
   Float_t         mu_type;
   Int_t           mu_mother_pdg;
   Float_t         mu_deviation;
   Float_t         mu_trun_mean_dqdx;
   Int_t           mu_pdg;
   Int_t           n_mcs_at_vtx;
   Int_t           n_reco_at_vtx;
   Float_t         pi0_mass;
   Float_t         pi0_oangle;
   Float_t         pi0_true_oangle;
   Float_t         pi0_IP;
   Float_t         pi0_mom;
   Float_t         pi0_low_radL;
   Float_t         pi0_low_IP_w_vtx;
   Float_t         pi0_low_purity;
   Float_t         pi0_low_complete;
   Float_t         pi0_low_cw_purity;
   Float_t         pi0_low_cw_complete;
   Float_t         pi0_low_true_gammaE;
   Float_t         pi0_low_true_detProf_gammaE;
   Float_t         pi0_low_perfect_clustering_E;
   Float_t         pi0_low_reco_gammaE;
   Float_t         pi0_low_origin;
   Float_t         pi0_low_type;
   Char_t          pi0_low_from_pi0;
   Float_t         pi0_low_st_x;
   Float_t         pi0_low_st_y;
   Float_t         pi0_low_st_z;
   Float_t         pi0_low_true_scecorr_st_x;
   Float_t         pi0_low_true_scecorr_st_y;
   Float_t         pi0_low_true_scecorr_st_z;
   Float_t         pi0_low_true_st_x;
   Float_t         pi0_low_true_st_y;
   Float_t         pi0_low_true_st_z;
   Float_t         pi0_low_true_detProf_st_x;
   Float_t         pi0_low_true_detProf_st_y;
   Float_t         pi0_low_true_detProf_st_z;
   Float_t         pi0_low_dist_to_nearest_trk;
   Int_t           pi0_low_mother_pdg;
   Int_t           pi0_low_pdg;
   Float_t         pi0_high_radL;
   Float_t         pi0_high_IP_w_vtx;
   Float_t         pi0_high_purity;
   Float_t         pi0_high_complete;
   Float_t         pi0_high_cw_purity;
   Float_t         pi0_high_cw_complete;
   Float_t         pi0_high_true_gammaE;
   Float_t         pi0_high_true_detProf_gammaE;
   Float_t         pi0_high_perfect_clustering_E;
   Float_t         pi0_high_reco_gammaE;
   Float_t         pi0_high_origin;
   Float_t         pi0_high_type;
   Char_t          pi0_high_from_pi0;
   Float_t         pi0_high_st_x;
   Float_t         pi0_high_st_y;
   Float_t         pi0_high_st_z;
   Float_t         pi0_high_true_scecorr_st_x;
   Float_t         pi0_high_true_scecorr_st_y;
   Float_t         pi0_high_true_scecorr_st_z;
   Float_t         pi0_high_true_st_x;
   Float_t         pi0_high_true_st_y;
   Float_t         pi0_high_true_st_z;
   Float_t         pi0_high_true_detProf_st_x;
   Float_t         pi0_high_true_detProf_st_y;
   Float_t         pi0_high_true_detProf_st_z;
   Float_t         pi0_high_dist_to_nearest_trk;
   Int_t           pi0_high_mother_pdg;
   Int_t           pi0_high_pdg;
   Float_t         gamma_E;
   Float_t         gamma_RL;
   Float_t         gamma_IP_w_vtx;
   Float_t         gamma_startx;
   Float_t         gamma_starty;
   Float_t         gamma_startz;
   Float_t         gamma_true_startx;
   Float_t         gamma_true_starty;
   Float_t         gamma_true_startz;
   Float_t         gamma_true_detProf_startx;
   Float_t         gamma_true_detProf_starty;
   Float_t         gamma_true_detProf_startz;
   Float_t         gamma_purity;
   Float_t         gamma_complete;
   Float_t         gamma_cw_purity;
   Float_t         gamma_cw_complete;
   Float_t         gamma_trueE;
   Float_t         gamma_trueE_detProf;
   Float_t         gamma_perfect_clustering_E;
   Float_t         gamma_origin;
   Float_t         gamma_type;
   Char_t          gamma_from_pi0;
   Int_t           gamma_pdg;
   Int_t           gamma_mother_pdg;
   Int_t           n_track_hits_0;
   Int_t           n_track_hits_1;
   Int_t           n_track_hits_2;
   Int_t           n_shower_hits_0;
   Int_t           n_shower_hits_1;
   Int_t           n_shower_hits_2;
   Int_t           n_shr_pi0;
   Int_t           n_shr_nushr;
   Int_t           n_shr_nutrk;
   Int_t           n_shr_cosmic;
   Int_t           n_shr_noise;
   vector<float>   *sel_evts_m1;
   vector<float>   *sel_evts_p1;
   Char_t          signal;

   // List of branches
   TBranch        *b_event_id;   //!
   TBranch        *b_subrun_id;   //!
   TBranch        *b_run_id;   //!
   TBranch        *b_event;   //!
   TBranch        *b_bkgd_id;   //!
   TBranch        *b_nu_mode;   //!
   TBranch        *b_nshrs;   //!
   TBranch        *b_vtx_x;   //!
   TBranch        *b_vtx_y;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_mc_vtx_x;   //!
   TBranch        *b_mc_vtx_y;   //!
   TBranch        *b_mc_vtx_z;   //!
   TBranch        *b_mc_scecorr_vtx_x;   //!
   TBranch        *b_mc_scecorr_vtx_y;   //!
   TBranch        *b_mc_scecorr_vtx_z;   //!
   TBranch        *b_flash_time;   //!
   TBranch        *b_flash_pe;   //!
   TBranch        *b_flash_y_center;   //!
   TBranch        *b_flash_z_center;   //!
   TBranch        *b_flash_y_width;   //!
   TBranch        *b_flash_z_width;   //!
   TBranch        *b_mu_true_angle;   //!
   TBranch        *b_mu_true_phi;   //!
   TBranch        *b_mu_true_mom;   //!
   TBranch        *b_mu_true_startx;   //!
   TBranch        *b_mu_true_starty;   //!
   TBranch        *b_mu_true_startz;   //!
   TBranch        *b_mu_true_endx;   //!
   TBranch        *b_mu_true_endy;   //!
   TBranch        *b_mu_true_endz;   //!
   TBranch        *b_mu_angle;   //!
   TBranch        *b_mu_len;   //!
   TBranch        *b_mu_startx;   //!
   TBranch        *b_mu_starty;   //!
   TBranch        *b_mu_startz;   //!
   TBranch        *b_mu_endx;   //!
   TBranch        *b_mu_endy;   //!
   TBranch        *b_mu_endz;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mult;   //!
   TBranch        *b_mu_purity;   //!
   TBranch        *b_mu_complete;   //!
   TBranch        *b_mu_cw_purity;   //!
   TBranch        *b_mu_cw_complete;   //!
   TBranch        *b_mu_origin;   //!
   TBranch        *b_mu_type;   //!
   TBranch        *b_mu_mother_pdg;   //!
   TBranch        *b_mu_deviation;   //!
   TBranch        *b_mu_trun_mean_dqdx;   //!
   TBranch        *b_mu_pdg;   //!
   TBranch        *b_n_mcs_at_vtx;   //!
   TBranch        *b_n_reco_at_vtx;   //!
   TBranch        *b_pi0_mass;   //!
   TBranch        *b_pi0_oangle;   //!
   TBranch        *b_pi0_true_oangle;   //!
   TBranch        *b_pi0_IP;   //!
   TBranch        *b_pi0_mom;   //!
   TBranch        *b_pi0_low_radL;   //!
   TBranch        *b_pi0_low_IP_w_vtx;   //!
   TBranch        *b_pi0_low_purity;   //!
   TBranch        *b_pi0_low_complete;   //!
   TBranch        *b_pi0_low_cw_purity;   //!
   TBranch        *b_pi0_low_cw_complete;   //!
   TBranch        *b_pi0_low_true_gammaE;   //!
   TBranch        *b_pi0_low_true_detProf_gammaE;   //!
   TBranch        *b_pi0_low_perfect_clustering_E;   //!
   TBranch        *b_pi0_low_reco_gammaE;   //!
   TBranch        *b_pi0_low_origin;   //!
   TBranch        *b_pi0_low_type;   //!
   TBranch        *b_pi0_low_from_pi0;   //!
   TBranch        *b_pi0_low_st_x;   //!
   TBranch        *b_pi0_low_st_y;   //!
   TBranch        *b_pi0_low_st_z;   //!
   TBranch        *b_pi0_low_true_scecorr_st_x;   //!
   TBranch        *b_pi0_low_true_scecorr_st_y;   //!
   TBranch        *b_pi0_low_true_scecorr_st_z;   //!
   TBranch        *b_pi0_low_true_st_x;   //!
   TBranch        *b_pi0_low_true_st_y;   //!
   TBranch        *b_pi0_low_true_st_z;   //!
   TBranch        *b_pi0_low_true_detProf_st_x;   //!
   TBranch        *b_pi0_low_true_detProf_st_y;   //!
   TBranch        *b_pi0_low_true_detProf_st_z;   //!
   TBranch        *b_pi0_low_dist_to_nearest_trk;   //!
   TBranch        *b_pi0_low_mother_pdg;   //!
   TBranch        *b_pi0_low_pdg;   //!
   TBranch        *b_pi0_high_radL;   //!
   TBranch        *b_pi0_high_IP_w_vtx;   //!
   TBranch        *b_pi0_high_purity;   //!
   TBranch        *b_pi0_high_complete;   //!
   TBranch        *b_pi0_high_cw_purity;   //!
   TBranch        *b_pi0_high_cw_complete;   //!
   TBranch        *b_pi0_high_true_gammaE;   //!
   TBranch        *b_pi0_high_true_detProf_gammaE;   //!
   TBranch        *b_pi0_high_perfect_clustering_E;   //!
   TBranch        *b_pi0_high_reco_gammaE;   //!
   TBranch        *b_pi0_high_origin;   //!
   TBranch        *b_pi0_high_type;   //!
   TBranch        *b_pi0_high_from_pi0;   //!
   TBranch        *b_pi0_high_st_x;   //!
   TBranch        *b_pi0_high_st_y;   //!
   TBranch        *b_pi0_high_st_z;   //!
   TBranch        *b_pi0_high_true_scecorr_st_x;   //!
   TBranch        *b_pi0_high_true_scecorr_st_y;   //!
   TBranch        *b_pi0_high_true_scecorr_st_z;   //!
   TBranch        *b_pi0_high_true_st_x;   //!
   TBranch        *b_pi0_high_true_st_y;   //!
   TBranch        *b_pi0_high_true_st_z;   //!
   TBranch        *b_pi0_high_true_detProf_st_x;   //!
   TBranch        *b_pi0_high_true_detProf_st_y;   //!
   TBranch        *b_pi0_high_true_detProf_st_z;   //!
   TBranch        *b_pi0_high_dist_to_nearest_trk;   //!
   TBranch        *b_pi0_high_mother_pdg;   //!
   TBranch        *b_pi0_high_pdg;   //!
   TBranch        *b_gamma_E;   //!
   TBranch        *b_gamma_RL;   //!
   TBranch        *b_gamma_IP_w_vtx;   //!
   TBranch        *b_gamma_startx;   //!
   TBranch        *b_gamma_starty;   //!
   TBranch        *b_gamma_startz;   //!
   TBranch        *b_gamma_true_startx;   //!
   TBranch        *b_gamma_true_starty;   //!
   TBranch        *b_gamma_true_startz;   //!
   TBranch        *b_gamma_true_detProf_startx;   //!
   TBranch        *b_gamma_true_detProf_starty;   //!
   TBranch        *b_gamma_true_detProf_startz;   //!
   TBranch        *b_gamma_purity;   //!
   TBranch        *b_gamma_complete;   //!
   TBranch        *b_gamma_cw_purity;   //!
   TBranch        *b_gamma_cw_complete;   //!
   TBranch        *b_gamma_trueE;   //!
   TBranch        *b_gamma_trueE_detProf;   //!
   TBranch        *b_gamma_perfect_clustering_E;   //!
   TBranch        *b_gamma_origin;   //!
   TBranch        *b_gamma_type;   //!
   TBranch        *b_gamma_from_pi0;   //!
   TBranch        *b_gamma_pdg;   //!
   TBranch        *b_gamma_mother_pdg;   //!
   TBranch        *b_n_track_hits_0;   //!
   TBranch        *b_n_track_hits_1;   //!
   TBranch        *b_n_track_hits_2;   //!
   TBranch        *b_n_shower_hits_0;   //!
   TBranch        *b_n_shower_hits_1;   //!
   TBranch        *b_n_shower_hits_2;   //!
   TBranch        *b_n_shr_pi0;   //!
   TBranch        *b_n_shr_nushr;   //!
   TBranch        *b_n_shr_nutrk;   //!
   TBranch        *b_n_shr_cosmic;   //!
   TBranch        *b_n_shr_noise;   //!
   TBranch        *b_sel_evts_m1;   //!
   TBranch        *b_sel_evts_p1;   //!
   TBranch        *b_signal;   //!

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   double Ec(double E);

};

#endif

#ifdef tree_cxx
tree::tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

  string mc = "mc";
  string samp = "two";
  
  if(mc.find("beam") != 18446744073709551615){
    data = true;
  }
  else{data = false;}

  if(mc.find("onbeam") != 18446744073709551615){scale = 1;}
  if(mc.find("offbeam") != 18446744073709551615){scale = 0.5467873819;}
  if(mc.find("mc") != 18446744073709551615){scale = 0.07769119;}

  std::cout << " Scale : " << scale << std::endl;

  if(samp.find("two") != 18446744073709551615){
    twoshow = true;
  }
  else{ twoshow = false;}

  std::cout << "Loading file ... " << Form("Files/%s/BT_backgrounds_%s.root",mc.c_str(),samp.c_str()) << std::endl;
  
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(Form("Files/%s/BT_backgrounds_%s.root",mc.c_str(),samp.c_str()));
    if (!f || !f->IsOpen()) {
      f = new TFile(Form("Files/%s/BT_backgrounds_%s.root",mc.c_str(),samp.c_str()));
    }
    f->GetObject("tree",tree);
    
  }
  Init(tree);

}

tree::~tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   sel_evts_m1 = 0;
   sel_evts_p1 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("subrun_id", &subrun_id, &b_subrun_id);
   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("bkgd_id", &bkgd_id, &b_bkgd_id);
   fChain->SetBranchAddress("nu_mode", &nu_mode, &b_nu_mode);
   fChain->SetBranchAddress("nshrs", &nshrs, &b_nshrs);
   fChain->SetBranchAddress("vtx_x", &vtx_x, &b_vtx_x);
   fChain->SetBranchAddress("vtx_y", &vtx_y, &b_vtx_y);
   fChain->SetBranchAddress("vtx_z", &vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("mc_vtx_x", &mc_vtx_x, &b_mc_vtx_x);
   fChain->SetBranchAddress("mc_vtx_y", &mc_vtx_y, &b_mc_vtx_y);
   fChain->SetBranchAddress("mc_vtx_z", &mc_vtx_z, &b_mc_vtx_z);
   fChain->SetBranchAddress("mc_scecorr_vtx_x", &mc_scecorr_vtx_x, &b_mc_scecorr_vtx_x);
   fChain->SetBranchAddress("mc_scecorr_vtx_y", &mc_scecorr_vtx_y, &b_mc_scecorr_vtx_y);
   fChain->SetBranchAddress("mc_scecorr_vtx_z", &mc_scecorr_vtx_z, &b_mc_scecorr_vtx_z);
   fChain->SetBranchAddress("flash_time", &flash_time, &b_flash_time);
   fChain->SetBranchAddress("flash_pe", &flash_pe, &b_flash_pe);
   fChain->SetBranchAddress("flash_y_center", &flash_y_center, &b_flash_y_center);
   fChain->SetBranchAddress("flash_z_center", &flash_z_center, &b_flash_z_center);
   fChain->SetBranchAddress("flash_y_width", &flash_y_width, &b_flash_y_width);
   fChain->SetBranchAddress("flash_z_width", &flash_z_width, &b_flash_z_width);
   fChain->SetBranchAddress("mu_true_angle", &mu_true_angle, &b_mu_true_angle);
   fChain->SetBranchAddress("mu_true_phi", &mu_true_phi, &b_mu_true_phi);
   fChain->SetBranchAddress("mu_true_mom", &mu_true_mom, &b_mu_true_mom);
   fChain->SetBranchAddress("mu_true_startx", &mu_true_startx, &b_mu_true_startx);
   fChain->SetBranchAddress("mu_true_starty", &mu_true_starty, &b_mu_true_starty);
   fChain->SetBranchAddress("mu_true_startz", &mu_true_startz, &b_mu_true_startz);
   fChain->SetBranchAddress("mu_true_endx", &mu_true_endx, &b_mu_true_endx);
   fChain->SetBranchAddress("mu_true_endy", &mu_true_endy, &b_mu_true_endy);
   fChain->SetBranchAddress("mu_true_endz", &mu_true_endz, &b_mu_true_endz);
   fChain->SetBranchAddress("mu_angle", &mu_angle, &b_mu_angle);
   fChain->SetBranchAddress("mu_len", &mu_len, &b_mu_len);
   fChain->SetBranchAddress("mu_startx", &mu_startx, &b_mu_startx);
   fChain->SetBranchAddress("mu_starty", &mu_starty, &b_mu_starty);
   fChain->SetBranchAddress("mu_startz", &mu_startz, &b_mu_startz);
   fChain->SetBranchAddress("mu_endx", &mu_endx, &b_mu_endx);
   fChain->SetBranchAddress("mu_endy", &mu_endy, &b_mu_endy);
   fChain->SetBranchAddress("mu_endz", &mu_endz, &b_mu_endz);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mult", &mult, &b_mult);
   fChain->SetBranchAddress("mu_purity", &mu_purity, &b_mu_purity);
   fChain->SetBranchAddress("mu_complete", &mu_complete, &b_mu_complete);
   fChain->SetBranchAddress("mu_cw_purity", &mu_cw_purity, &b_mu_cw_purity);
   fChain->SetBranchAddress("mu_cw_complete", &mu_cw_complete, &b_mu_cw_complete);
   fChain->SetBranchAddress("mu_origin", &mu_origin, &b_mu_origin);
   fChain->SetBranchAddress("mu_type", &mu_type, &b_mu_type);
   fChain->SetBranchAddress("mu_pdg", &mu_pdg, &b_mu_pdg);
   fChain->SetBranchAddress("mu_mother_pdg", &mu_mother_pdg, &b_mu_mother_pdg);
   fChain->SetBranchAddress("mu_deviation", &mu_deviation, &b_mu_deviation);
   fChain->SetBranchAddress("mu_trun_mean_dqdx", &mu_trun_mean_dqdx, &b_mu_trun_mean_dqdx);
//    fChain->SetBranchAddress("mu_pdg", &mu_pdg, &b_mu_pdg);
   fChain->SetBranchAddress("n_mcs_at_vtx", &n_mcs_at_vtx, &b_n_mcs_at_vtx);
   fChain->SetBranchAddress("n_reco_at_vtx", &n_reco_at_vtx, &b_n_reco_at_vtx);
   fChain->SetBranchAddress("pi0_mass", &pi0_mass, &b_pi0_mass);
   fChain->SetBranchAddress("pi0_oangle", &pi0_oangle, &b_pi0_oangle);
   fChain->SetBranchAddress("pi0_true_oangle", &pi0_true_oangle, &b_pi0_true_oangle);
   fChain->SetBranchAddress("pi0_IP", &pi0_IP, &b_pi0_IP);
   fChain->SetBranchAddress("pi0_mom", &pi0_mom, &b_pi0_mom);
   fChain->SetBranchAddress("pi0_low_radL", &pi0_low_radL, &b_pi0_low_radL);
   fChain->SetBranchAddress("pi0_low_IP_w_vtx", &pi0_low_IP_w_vtx, &b_pi0_low_IP_w_vtx);
   fChain->SetBranchAddress("pi0_low_purity", &pi0_low_purity, &b_pi0_low_purity);
   fChain->SetBranchAddress("pi0_low_complete", &pi0_low_complete, &b_pi0_low_complete);
   fChain->SetBranchAddress("pi0_low_cw_purity", &pi0_low_cw_purity, &b_pi0_low_cw_purity);
   fChain->SetBranchAddress("pi0_low_cw_complete", &pi0_low_cw_complete, &b_pi0_low_cw_complete);
   fChain->SetBranchAddress("pi0_low_true_gammaE", &pi0_low_true_gammaE, &b_pi0_low_true_gammaE);
   fChain->SetBranchAddress("pi0_low_true_detProf_gammaE", &pi0_low_true_detProf_gammaE, &b_pi0_low_true_detProf_gammaE);
   fChain->SetBranchAddress("pi0_low_perfect_clustering_E", &pi0_low_perfect_clustering_E, &b_pi0_low_perfect_clustering_E);
   fChain->SetBranchAddress("pi0_low_reco_gammaE", &pi0_low_reco_gammaE, &b_pi0_low_reco_gammaE);
   fChain->SetBranchAddress("pi0_low_origin", &pi0_low_origin, &b_pi0_low_origin);
   fChain->SetBranchAddress("pi0_low_type", &pi0_low_type, &b_pi0_low_type);
   fChain->SetBranchAddress("pi0_low_from_pi0", &pi0_low_from_pi0, &b_pi0_low_from_pi0);
   fChain->SetBranchAddress("pi0_low_st_x", &pi0_low_st_x, &b_pi0_low_st_x);
   fChain->SetBranchAddress("pi0_low_st_y", &pi0_low_st_y, &b_pi0_low_st_y);
   fChain->SetBranchAddress("pi0_low_st_z", &pi0_low_st_z, &b_pi0_low_st_z);
   fChain->SetBranchAddress("pi0_low_true_scecorr_st_x", &pi0_low_true_scecorr_st_x, &b_pi0_low_true_scecorr_st_x);
   fChain->SetBranchAddress("pi0_low_true_scecorr_st_y", &pi0_low_true_scecorr_st_y, &b_pi0_low_true_scecorr_st_y);
   fChain->SetBranchAddress("pi0_low_true_scecorr_st_z", &pi0_low_true_scecorr_st_z, &b_pi0_low_true_scecorr_st_z);
   fChain->SetBranchAddress("pi0_low_true_st_x", &pi0_low_true_st_x, &b_pi0_low_true_st_x);
   fChain->SetBranchAddress("pi0_low_true_st_y", &pi0_low_true_st_y, &b_pi0_low_true_st_y);
   fChain->SetBranchAddress("pi0_low_true_st_z", &pi0_low_true_st_z, &b_pi0_low_true_st_z);
   fChain->SetBranchAddress("pi0_low_true_detProf_st_x", &pi0_low_true_detProf_st_x, &b_pi0_low_true_detProf_st_x);
   fChain->SetBranchAddress("pi0_low_true_detProf_st_y", &pi0_low_true_detProf_st_y, &b_pi0_low_true_detProf_st_y);
   fChain->SetBranchAddress("pi0_low_true_detProf_st_z", &pi0_low_true_detProf_st_z, &b_pi0_low_true_detProf_st_z);
   fChain->SetBranchAddress("pi0_low_dist_to_nearest_trk", &pi0_low_dist_to_nearest_trk, &b_pi0_low_dist_to_nearest_trk);
   fChain->SetBranchAddress("pi0_low_mother_pdg", &pi0_low_mother_pdg, &b_pi0_low_mother_pdg);
   fChain->SetBranchAddress("pi0_low_pdg", &pi0_low_pdg, &b_pi0_low_pdg);
   fChain->SetBranchAddress("pi0_high_radL", &pi0_high_radL, &b_pi0_high_radL);
   fChain->SetBranchAddress("pi0_high_IP_w_vtx", &pi0_high_IP_w_vtx, &b_pi0_high_IP_w_vtx);
   fChain->SetBranchAddress("pi0_high_purity", &pi0_high_purity, &b_pi0_high_purity);
   fChain->SetBranchAddress("pi0_high_complete", &pi0_high_complete, &b_pi0_high_complete);
   fChain->SetBranchAddress("pi0_high_cw_purity", &pi0_high_cw_purity, &b_pi0_high_cw_purity);
   fChain->SetBranchAddress("pi0_high_cw_complete", &pi0_high_cw_complete, &b_pi0_high_cw_complete);
   fChain->SetBranchAddress("pi0_high_true_gammaE", &pi0_high_true_gammaE, &b_pi0_high_true_gammaE);
   fChain->SetBranchAddress("pi0_high_true_detProf_gammaE", &pi0_high_true_detProf_gammaE, &b_pi0_high_true_detProf_gammaE);
   fChain->SetBranchAddress("pi0_high_perfect_clustering_E", &pi0_high_perfect_clustering_E, &b_pi0_high_perfect_clustering_E);
   fChain->SetBranchAddress("pi0_high_reco_gammaE", &pi0_high_reco_gammaE, &b_pi0_high_reco_gammaE);
   fChain->SetBranchAddress("pi0_high_origin", &pi0_high_origin, &b_pi0_high_origin);
   fChain->SetBranchAddress("pi0_high_type", &pi0_high_type, &b_pi0_high_type);
   fChain->SetBranchAddress("pi0_high_from_pi0", &pi0_high_from_pi0, &b_pi0_high_from_pi0);
   fChain->SetBranchAddress("pi0_high_st_x", &pi0_high_st_x, &b_pi0_high_st_x);
   fChain->SetBranchAddress("pi0_high_st_y", &pi0_high_st_y, &b_pi0_high_st_y);
   fChain->SetBranchAddress("pi0_high_st_z", &pi0_high_st_z, &b_pi0_high_st_z);
   fChain->SetBranchAddress("pi0_high_true_scecorr_st_x", &pi0_high_true_scecorr_st_x, &b_pi0_high_true_scecorr_st_x);
   fChain->SetBranchAddress("pi0_high_true_scecorr_st_y", &pi0_high_true_scecorr_st_y, &b_pi0_high_true_scecorr_st_y);
   fChain->SetBranchAddress("pi0_high_true_scecorr_st_z", &pi0_high_true_scecorr_st_z, &b_pi0_high_true_scecorr_st_z);
   fChain->SetBranchAddress("pi0_high_true_st_x", &pi0_high_true_st_x, &b_pi0_high_true_st_x);
   fChain->SetBranchAddress("pi0_high_true_st_y", &pi0_high_true_st_y, &b_pi0_high_true_st_y);
   fChain->SetBranchAddress("pi0_high_true_st_z", &pi0_high_true_st_z, &b_pi0_high_true_st_z);
   fChain->SetBranchAddress("pi0_high_true_detProf_st_x", &pi0_high_true_detProf_st_x, &b_pi0_high_true_detProf_st_x);
   fChain->SetBranchAddress("pi0_high_true_detProf_st_y", &pi0_high_true_detProf_st_y, &b_pi0_high_true_detProf_st_y);
   fChain->SetBranchAddress("pi0_high_true_detProf_st_z", &pi0_high_true_detProf_st_z, &b_pi0_high_true_detProf_st_z);
   fChain->SetBranchAddress("pi0_high_dist_to_nearest_trk", &pi0_high_dist_to_nearest_trk, &b_pi0_high_dist_to_nearest_trk);
   fChain->SetBranchAddress("pi0_high_mother_pdg", &pi0_high_mother_pdg, &b_pi0_high_mother_pdg);
   fChain->SetBranchAddress("pi0_high_pdg", &pi0_high_pdg, &b_pi0_high_pdg);
   fChain->SetBranchAddress("gamma_E", &gamma_E, &b_gamma_E);
   fChain->SetBranchAddress("gamma_RL", &gamma_RL, &b_gamma_RL);
   fChain->SetBranchAddress("gamma_IP_w_vtx", &gamma_IP_w_vtx, &b_gamma_IP_w_vtx);
   fChain->SetBranchAddress("gamma_startx", &gamma_startx, &b_gamma_startx);
   fChain->SetBranchAddress("gamma_starty", &gamma_starty, &b_gamma_starty);
   fChain->SetBranchAddress("gamma_startz", &gamma_startz, &b_gamma_startz);
   fChain->SetBranchAddress("gamma_true_startx", &gamma_true_startx, &b_gamma_true_startx);
   fChain->SetBranchAddress("gamma_true_starty", &gamma_true_starty, &b_gamma_true_starty);
   fChain->SetBranchAddress("gamma_true_startz", &gamma_true_startz, &b_gamma_true_startz);
   fChain->SetBranchAddress("gamma_true_detProf_startx", &gamma_true_detProf_startx, &b_gamma_true_detProf_startx);
   fChain->SetBranchAddress("gamma_true_detProf_starty", &gamma_true_detProf_starty, &b_gamma_true_detProf_starty);
   fChain->SetBranchAddress("gamma_true_detProf_startz", &gamma_true_detProf_startz, &b_gamma_true_detProf_startz);
   fChain->SetBranchAddress("gamma_purity", &gamma_purity, &b_gamma_purity);
   fChain->SetBranchAddress("gamma_complete", &gamma_complete, &b_gamma_complete);
   fChain->SetBranchAddress("gamma_cw_purity", &gamma_cw_purity, &b_gamma_cw_purity);
   fChain->SetBranchAddress("gamma_cw_complete", &gamma_cw_complete, &b_gamma_cw_complete);
   fChain->SetBranchAddress("gamma_trueE", &gamma_trueE, &b_gamma_trueE);
   fChain->SetBranchAddress("gamma_trueE_detProf", &gamma_trueE_detProf, &b_gamma_trueE_detProf);
   fChain->SetBranchAddress("gamma_perfect_clustering_E", &gamma_perfect_clustering_E, &b_gamma_perfect_clustering_E);
   fChain->SetBranchAddress("gamma_origin", &gamma_origin, &b_gamma_origin);
   fChain->SetBranchAddress("gamma_type", &gamma_type, &b_gamma_type);
   fChain->SetBranchAddress("gamma_from_pi0", &gamma_from_pi0, &b_gamma_from_pi0);
   fChain->SetBranchAddress("gamma_pdg", &gamma_pdg, &b_gamma_pdg);
   fChain->SetBranchAddress("gamma_mother_pdg", &gamma_mother_pdg, &b_gamma_mother_pdg);
   fChain->SetBranchAddress("n_track_hits_0", &n_track_hits_0, &b_n_track_hits_0);
   fChain->SetBranchAddress("n_track_hits_1", &n_track_hits_1, &b_n_track_hits_1);
   fChain->SetBranchAddress("n_track_hits_2", &n_track_hits_2, &b_n_track_hits_2);
   fChain->SetBranchAddress("n_shower_hits_0", &n_shower_hits_0, &b_n_shower_hits_0);
   fChain->SetBranchAddress("n_shower_hits_1", &n_shower_hits_1, &b_n_shower_hits_1);
   fChain->SetBranchAddress("n_shower_hits_2", &n_shower_hits_2, &b_n_shower_hits_2);
   fChain->SetBranchAddress("n_shr_pi0", &n_shr_pi0, &b_n_shr_pi0);
   fChain->SetBranchAddress("n_shr_nushr", &n_shr_nushr, &b_n_shr_nushr);
   fChain->SetBranchAddress("n_shr_nutrk", &n_shr_nutrk, &b_n_shr_nutrk);
   fChain->SetBranchAddress("n_shr_cosmic", &n_shr_cosmic, &b_n_shr_cosmic);
   fChain->SetBranchAddress("n_shr_noise", &n_shr_noise, &b_n_shr_noise);
   fChain->SetBranchAddress("sel_evts_m1", &sel_evts_m1, &b_sel_evts_m1);
   fChain->SetBranchAddress("sel_evts_p1", &sel_evts_p1, &b_sel_evts_p1);
   fChain->SetBranchAddress("signal", &signal, &b_signal);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
double tree::Ec(double E){
  
  return go->Eval(E);
 
}
#endif // #ifdef tree_cxx
