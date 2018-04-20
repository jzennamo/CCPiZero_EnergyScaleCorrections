//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 13 09:27:35 2018 by ROOT version 6.08/06
// from TTree shower_tree/
// found on file: ../Files/BT_backgrounds_two.root
//////////////////////////////////////////////////////////

#ifndef shower_tree_h
#define shower_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class shower_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Int_t           bkgd_id;
   Float_t         shr_startx;
   Float_t         shr_starty;
   Float_t         shr_startz;
   Float_t         shr_startw;
   Float_t         shr_startt;
   Float_t         shr_dirx;
   Float_t         shr_diry;
   Float_t         shr_dirz;
   Float_t         shr_energy;
   Float_t         shr_true_startx;
   Float_t         shr_true_starty;
   Float_t         shr_true_startz;
   Float_t         shr_true_detProf_startx;
   Float_t         shr_true_detProf_starty;
   Float_t         shr_true_detProf_startz;
   Float_t         shr_trueE;
   Float_t         shr_trueE_detProf;
   Float_t         shr_perfect_clustering_E;
   Float_t         shr_oangle;
   Float_t         shr_dedx;
   Float_t         shr_vtx_dist;
   Float_t         shr_trk_delta_theta;
   Float_t         shr_trk_delta_phi;
   Float_t         shr_ip;
   Float_t         shr_rl;
   Float_t         shr_purity;
   Float_t         shr_complete;
   Float_t         shr_origin;
   Float_t         shr_type;
   Char_t          shr_from_pi0;
   Int_t           shr_pdg;
   Int_t           shr_mother_pdg;
   Int_t           shr_n_true;
   Int_t           shr_n_reco;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_bkgd_id;   //!
   TBranch        *b_shr_startx;   //!
   TBranch        *b_shr_starty;   //!
   TBranch        *b_shr_startz;   //!
   TBranch        *b_shr_startw;   //!
   TBranch        *b_shr_startt;   //!
   TBranch        *b_shr_dirx;   //!
   TBranch        *b_shr_diry;   //!
   TBranch        *b_shr_dirz;   //!
   TBranch        *b_shr_energy;   //!
   TBranch        *b_shr_true_startx;   //!
   TBranch        *b_shr_true_starty;   //!
   TBranch        *b_shr_true_startz;   //!
   TBranch        *b_shr_true_detProf_startx;   //!
   TBranch        *b_shr_true_detProf_starty;   //!
   TBranch        *b_shr_true_detProf_startz;   //!
   TBranch        *b_shr_trueE;   //!
   TBranch        *b_shr_trueE_detProf;   //!
   TBranch        *b_shr_perfect_clustering_E;   //!
   TBranch        *b_shr_oangle;   //!
   TBranch        *b_shr_dedx;   //!
   TBranch        *b_shr_vtx_dist;   //!
   TBranch        *b_shr_trk_delta_theta;   //!
   TBranch        *b_shr_trk_delta_phi;   //!
   TBranch        *b_shr_ip;   //!
   TBranch        *b_shr_rl;   //!
   TBranch        *b_shr_purity;   //!
   TBranch        *b_shr_complete;   //!
   TBranch        *b_shr_origin;   //!
   TBranch        *b_shr_type;   //!
   TBranch        *b_shr_from_pi0;   //!
   TBranch        *b_shr_pdg;   //!
   TBranch        *b_shr_mother_pdg;   //!
   TBranch        *b_shr_n_true;   //!
   TBranch        *b_shr_n_reco;   //!

   shower_tree(TTree *tree=0);
   virtual ~shower_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   bool inRange(unsigned low, unsigned high, unsigned x);
   double TruncMean(TH1D* hist, double xTest = -1);
};

#endif

#ifdef shower_tree_cxx
shower_tree::shower_tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../../Files/BT_backgrounds_two.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../../Files/BT_backgrounds_two.root");
      }
      f->GetObject("shower_tree",tree);

   }
   Init(tree);
}

shower_tree::~shower_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t shower_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t shower_tree::LoadTree(Long64_t entry)
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

bool shower_tree::inRange(unsigned low, unsigned high, unsigned x)
{
  return  ((x-low) <= (high-low));
}

double shower_tree::TruncMean(TH1D* hist, double xTest)
{
  int n = hist->GetXaxis()->GetNbins();  
  std::vector<double>  x(n);
  hist->GetXaxis()->GetCenter( &x[0] );
  const double * y = hist->GetArray(); 
  if(xTest == -1) xTest =  TMath::Median(n, &x[0], &y[1]); 
  double rms = hist->GetRMS(); 
  
  double avg = 0;
  double nt = 0;
  for(int i = 0; i < n; i++){
    if(x[i] < xTest+rms && x[i] > xTest-rms){
      
      avg += x[i]*y[i+1];
      nt += y[i+1];
    }
  }
  
  if(avg != 0 && nt != 0){    
    return avg/nt;
  }

  return 0;

}

void shower_tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("bkgd_id", &bkgd_id, &b_bkgd_id);
   fChain->SetBranchAddress("shr_startx", &shr_startx, &b_shr_startx);
   fChain->SetBranchAddress("shr_starty", &shr_starty, &b_shr_starty);
   fChain->SetBranchAddress("shr_startz", &shr_startz, &b_shr_startz);
   fChain->SetBranchAddress("shr_startw", &shr_startw, &b_shr_startw);
   fChain->SetBranchAddress("shr_startt", &shr_startt, &b_shr_startt);
   fChain->SetBranchAddress("shr_dirx", &shr_dirx, &b_shr_dirx);
   fChain->SetBranchAddress("shr_diry", &shr_diry, &b_shr_diry);
   fChain->SetBranchAddress("shr_dirz", &shr_dirz, &b_shr_dirz);
   fChain->SetBranchAddress("shr_energy", &shr_energy, &b_shr_energy);
   fChain->SetBranchAddress("shr_true_startx", &shr_true_startx, &b_shr_true_startx);
   fChain->SetBranchAddress("shr_true_starty", &shr_true_starty, &b_shr_true_starty);
   fChain->SetBranchAddress("shr_true_startz", &shr_true_startz, &b_shr_true_startz);
   fChain->SetBranchAddress("shr_true_detProf_startx", &shr_true_detProf_startx, &b_shr_true_detProf_startx);
   fChain->SetBranchAddress("shr_true_detProf_starty", &shr_true_detProf_starty, &b_shr_true_detProf_starty);
   fChain->SetBranchAddress("shr_true_detProf_startz", &shr_true_detProf_startz, &b_shr_true_detProf_startz);
   fChain->SetBranchAddress("shr_trueE", &shr_trueE, &b_shr_trueE);
   fChain->SetBranchAddress("shr_trueE_detProf", &shr_trueE_detProf, &b_shr_trueE_detProf);
   fChain->SetBranchAddress("shr_perfect_clustering_E", &shr_perfect_clustering_E, &b_shr_perfect_clustering_E);
   fChain->SetBranchAddress("shr_oangle", &shr_oangle, &b_shr_oangle);
   fChain->SetBranchAddress("shr_dedx", &shr_dedx, &b_shr_dedx);
   fChain->SetBranchAddress("shr_vtx_dist", &shr_vtx_dist, &b_shr_vtx_dist);
   fChain->SetBranchAddress("shr_trk_delta_theta", &shr_trk_delta_theta, &b_shr_trk_delta_theta);
   fChain->SetBranchAddress("shr_trk_delta_phi", &shr_trk_delta_phi, &b_shr_trk_delta_phi);
   fChain->SetBranchAddress("shr_ip", &shr_ip, &b_shr_ip);
   fChain->SetBranchAddress("shr_rl", &shr_rl, &b_shr_rl);
   fChain->SetBranchAddress("shr_purity", &shr_purity, &b_shr_purity);
   fChain->SetBranchAddress("shr_complete", &shr_complete, &b_shr_complete);
   fChain->SetBranchAddress("shr_origin", &shr_origin, &b_shr_origin);
   fChain->SetBranchAddress("shr_type", &shr_type, &b_shr_type);
   fChain->SetBranchAddress("shr_from_pi0", &shr_from_pi0, &b_shr_from_pi0);
   fChain->SetBranchAddress("shr_pdg", &shr_pdg, &b_shr_pdg);
   fChain->SetBranchAddress("shr_mother_pdg", &shr_mother_pdg, &b_shr_mother_pdg);
   fChain->SetBranchAddress("shr_n_true", &shr_n_true, &b_shr_n_true);
   fChain->SetBranchAddress("shr_n_reco", &shr_n_reco, &b_shr_n_reco);
   Notify();
}

Bool_t shower_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void shower_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t shower_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef shower_tree_cxx
