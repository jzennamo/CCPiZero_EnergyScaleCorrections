void CurrentNorms_LargeRange_NewCorrection(){

  std::vector< string > sel;
  //sel = {"one","two"};
  sel = {"two"};
  std::vector< string > vars;
  //vars = {"Nshw","Mult","Vy","Vx","Vz","Lmu","muCosTheta","muPhi","OpenAngle","ConvDist","Egamma","Mass","EgammaCorr","MassCorr"};
  vars = {"Mass","MassCorr"};

  std::vector< string > bkgds;
  bkgds = {"sig","fsem","sce","mult","nc","other", "cosplusnu"};
  //bkgds = {"sig"};
  //bkgds = {"fsem","sce","mult","nc","other", "cosplusnu"};

  std::vector< TFile* >  OnFile; 
  std::vector< TFile* >  OffFile; 
  std::vector< TFile* >  MCFile; 
  OnFile.resize(sel.size()); 
  OffFile.resize(sel.size());
  MCFile.resize(sel.size()); 
  
  for(int i = 0; i < sel.size(); i++){
    OnFile[i]  = 
      new TFile(Form("../TemplateMaker/NewCorrection/output_onbeam_%s.root",sel[i].c_str()));
    OffFile[i] = 
      new TFile(Form("../TemplateMaker/NewCorrection/output_offbeam_%s.root",sel[i].c_str()));
    MCFile[i]  = 
      new TFile(Form("../TemplateMaker/NewCorrection/output_mc_%s.root",sel[i].c_str()));      
  }

  std::vector< std::vector< TH1D*> > On;
  std::vector< std::vector< TH1D*> > Off;
  std::vector< std::vector< std::vector< TH1D* > > > MC;

  std::vector< std::vector <THStack* > > Stack;

  std::vector< std::vector< TCanvas*> > c;

  On.resize(sel.size());
  Off.resize(sel.size());
  Stack.resize(sel.size());
  c.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    On[i].resize(vars.size());
    Off[i].resize(vars.size());
    Stack[i].resize(vars.size());
    c[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
     
      On[i][j] = (TH1D*)OnFile[i]->Get(Form("%s_data",vars[j].c_str()));
      Off[i][j] = (TH1D*)OffFile[i]->Get(Form("%s_data",vars[j].c_str()));
      //On[i][j]->Rebin(4);
      //Off[i][j]->Rebin(4);
      
      On[i][j]->Add(Off[i][j],-1);
      	
      On[i][j]->SetLineColor(kBlack);
      On[i][j]->SetLineWidth(2);

      Stack[i][j] = new THStack();

    }
  }

  std::vector< int > color;
  color = {kRed-9,kBlue,kCyan-2,kCyan-9,kYellow-10,kOrange-6, kGray};
 
  
  
  MC.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    MC[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
      MC[i][j].resize(bkgds.size());
      for(int k = 0; k < bkgds.size(); k++){
	
	MC[i][j][k] = (TH1D*)MCFile[i]->Get(Form("%s_%s",
						 vars[j].c_str(),
						 bkgds[k].c_str()));
	
	MC[i][j][k]->SetFillColor(color[k]);
	MC[i][j][k]->SetLineColor(color[k]);
	//MC[i][j][k]->Rebin(4);
	//On[i][j]->Add(MC[i][j][k],-1);
	
      }
    }
  }
 
  std::vector< std::vector< double > > integral;
  std::vector< std::vector< std::vector< double > > > bkgd_int;
  integral.resize(sel.size());
  bkgd_int.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    integral[i].resize(vars.size());
    bkgd_int[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
      integral[i][j] = 0;
      bkgd_int[i][j].resize(bkgds.size());      
    }
  }

  for(int i = 0; i < sel.size(); i++){
    for(int j = 0; j < vars.size(); j++){      
      for(int k = 1; k <= bkgds.size(); k++){
	Stack[i][j]->Add(MC[i][j][bkgds.size()-k]);
	integral[i][j]+=MC[i][j][bkgds.size()-k]->Integral(); 
	bkgd_int[i][j][bkgds.size()-k] = MC[i][j][bkgds.size()-k]->Integral();

      }
    }
  }


  TLatex Title;
  Title.SetTextAlign(23);
  Title.SetTextSize(0.05);
     
  for(int i = 0; i < sel.size(); i++){
    for(int j = 0; j < vars.size(); j++){
      
      if(On[i][j]->Integral() == 0) continue;     
      c[i][j] = new TCanvas(Form("c_%d_%d",i,j));
      c[i][j]->cd();
      Stack[i][j]->Draw("hist");
      On[i][j]->Draw("same");      
      TLine line;
      line.SetLineColor(kRed);
      line.SetLineStyle(22);
      line.SetLineWidth(2);
      line.DrawLine(135,0,135,On[i][j]->GetMaximum());
      //On[i][j]->Draw("");      
      
      TLegend* leg = new TLegend(0.57, 0.7, 0.98, 0.92);
      for(int k = 0; k < bkgds.size(); k++){
	leg->AddEntry(MC[i][j][k], Form("%s",bkgds[k].c_str()), "f");
      }
      leg->SetTextSize(0.045);
      leg->Draw("same");


      //Title.DrawLatexNDC(0.5,0.95,Form("%s for the %s shower selection",vars[j].c_str(),sel[i].c_str()));
    

    }
  }

}
