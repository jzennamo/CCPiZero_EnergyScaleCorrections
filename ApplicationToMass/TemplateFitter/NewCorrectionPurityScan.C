void NewCorrectionPurityScan(){

  std::vector< string > sel;
  //sel = {"one","two"};
  sel = {"two"};
  std::vector< string > vars;
  //vars = {"Nshw","Mult","Vy","Vx","Vz","Lmu","muCosTheta","muPhi","OpenAngle","ConvDist","Egamma","Mass","EgammaCorr","MassCorr"};
  vars = {"Mass","MassCorr"};

  std::vector< string > bkgds;
  //bkgds = {"sig","fsem","sce","mult","nc","other", "cosplusnu"};
  //bkgds = {"sig"};
  bkgds = {"fsem","sce","mult","nc","other", "cosplusnu"};

  std::vector< TFile* >  MCFile; 
  MCFile.resize(sel.size()); 
  
  for(int i = 0; i < sel.size(); i++){
    MCFile[i]  = 
      new TFile(Form("../TemplateMaker/NewCorrection/output_mc_%s.root",sel[i].c_str()));      
  }

  std::vector< std::vector< TH1D*> > Sig;
  std::vector< std::vector< TH1D*> > Purity;
  std::vector< std::vector< TH1D*> > MC;

  std::vector< std::vector< TCanvas*> > c;

  Sig.resize(sel.size());
  c.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    c[i].resize(vars.size());
    Sig[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
      Sig[i][j] = (TH1D*)MCFile[i]->Get(Form("%s_sig",
					     vars[j].c_str()));
    }
  }

  std::vector< int > color;
  color = {kRed-9,kBlue,kCyan-2,kCyan-9,kYellow-10,kOrange-6, kGray};
 
  
  
  MC.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    MC[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
      MC[i][j] = new TH1D(Form("%s_MC",vars[j].c_str()),"",80,0,800); 
      for(int k = 0; k < bkgds.size(); k++){
	
	MC[i][j]->Add((TH1D*)MCFile[i]->Get(Form("%s_%s",
						 vars[j].c_str(),
						 bkgds[k].c_str())));
	
	//MC[i][j][k]->Rebin(4);
	//On[i][j]->Add(MC[i][j][k],-1);
	
      }
    }
  }


  TLatex Title;
  Title.SetTextAlign(23);
  Title.SetTextSize(0.05);
     
  for(int i = 0; i < sel.size(); i++){
    for(int j = 0; j < vars.size(); j++){
      
      c[i][j] = new TCanvas(Form("c_%d_%d",i,j));
      c[i][j]->cd();
      Sig[i][j]->Divide(MC[i][j]);
      Sig[i][j]->Draw("same");      
      TLine line;
      line.SetLineColor(kRed);
      line.SetLineStyle(22);
      line.SetLineWidth(2);
      line.DrawLine(0,1,800,1);
     
    }
  }

}
