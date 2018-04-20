void NewFitter(){

  std::vector< string > sel;
  //  sel = {"one","two"};
  sel = {"one"};
  std::vector< string > vars;
  //vars = {"Nshw","Mult","Vy","Vx","Vz","Lmu","muCosTheta","muPhi","OpenAngle","ConvDist","Egamma","Mass","EgammaCorr","MassCorr"};
  
  vars = {"Vy"};

  std::vector< string > bkgds;
  bkgds = {"sig","fsem","sce","mult","nc","other", "cosplusnu"};


  std::vector< TFile* >  OnFile; 
  std::vector< TFile* >  OffFile; 
  std::vector< TFile* >  MCFile; 
  OnFile.resize(sel.size()); 
  OffFile.resize(sel.size());
  MCFile.resize(sel.size()); 
  
  for(int i = 0; i < sel.size(); i++){
    OnFile[i]  = 
      new TFile(Form("../TemplateMaker/output_beam_%s.root",sel[i].c_str()));
    OffFile[i] = 
      new TFile(Form("../TemplateMaker/output_offbeam_%s.root",sel[i].c_str()));
    MCFile[i]  = 
      new TFile(Form("../TemplateMaker/output_mc_%s.root",sel[i].c_str()));      
  }

  std::vector< std::vector< TH1D*> > On;
  std::vector< std::vector< TH1D*> > Off;
  std::vector< std::vector< std::vector< TH1D* > > > MC;

  std::vector< std::vector< TObjArray* > > mc_temps;
    
  std::vector< std::vector <THStack* > > Stack;
  std::vector< std::vector <THStack* > > StackFitted;
  std::vector< std::vector< TCanvas*> > c;

  On.resize(sel.size());
  Off.resize(sel.size());
  mc_temps.resize(sel.size());
  Stack.resize(sel.size());
  StackFitted.resize(sel.size());
  c.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    On[i].resize(vars.size());
    Off[i].resize(vars.size());
    Stack[i].resize(vars.size());
    StackFitted[i].resize(vars.size());
    mc_temps[i].resize(vars.size());
    c[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
     
      On[i][j] = (TH1D*)OnFile[i]->Get(Form("%s_data",vars[j].c_str()));
      Off[i][j] = (TH1D*)OffFile[i]->Get(Form("%s_data",vars[j].c_str()));
      
      On[i][j]->Add(Off[i][j],-1*(0.7/0.57));
      
      On[i][j]->SetLineColor(kBlack);
      On[i][j]->SetLineWidth(2);

      Stack[i][j] = new THStack();
      StackFitted[i][j] = new THStack();
      mc_temps[i][j] = new TObjArray(bkgds.size());
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
	MC[i][j][k]->Scale(0.1/0.2);
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
	mc_temps[i][j]->Add(MC[i][j][bkgds.size()-k]);
      }
    }
  }
  
  std::vector<std::vector< TFractionFitter*> > fit;
  fit.resize(sel.size());
  for(int i = 0; i < sel.size(); i++){
    fit[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){      
      fit[i][j] = new TFractionFitter(On[i][j], mc_temps[i][j]);
      
      for(int k = 0; k < bkgds.size(); k++){
	fit[i][j]->Constrain(k,0.01,0.2);
      }
      fit[i][j]->Constrain(0,0.3,0.8);
      fit[i][j]->SetRangeX(On[i][j]->GetXaxis()->GetXmin(),
			   On[i][j]->GetXaxis()->GetXmax());

      std::cout << sel[i] << " and " << vars[j] << " and low : " << On[i][j]->GetXaxis()->GetXmin() << " and high : " << On[i][j]->GetXaxis()->GetXmax() << std::endl;
      
      for(int b = 1; b <= On[i][j]->GetNbinsX(); b++){
	if(On[i][j]->GetBinContent(b) <= 0){
	  fit[i][j]->ExcludeBin(b);
	}
      }


      std::cout << "Fitting for " << sel[i] << " sel for " << vars[j] << std::endl;
      fit[i][j]->Fit();
    }
  }

  std::vector< std::vector<std::vector< double > > > fitBkg;
  std::vector< std::vector<std::vector< double > > > fitBkgerr;
  std::vector< std::vector< std::vector< TH1D* > > > MCfitted;

  fitBkg.resize(sel.size());
  fitBkgerr.resize(sel.size());
  MCfitted.resize(sel.size());  
  for(int i = 0; i < sel.size(); i++){
    fitBkg[i].resize(vars.size());
    fitBkgerr[i].resize(vars.size());
    MCfitted[i].resize(vars.size());
    for(int j = 0; j < vars.size(); j++){
      fitBkg[i][j].resize(bkgds.size());
      fitBkgerr[i][j].resize(bkgds.size());
      MCfitted[i][j].resize(bkgds.size());
      for(int k = 0; k < bkgds.size(); k++){
	fit[i][j]->GetResult(k, fitBkg[i][j][k], fitBkgerr[i][j][k]);
	MCfitted[i][j][k] = (TH1D*)MC[i][j][k]->Clone(Form("%s_fitted",MC[i][j][k]->GetTitle()));
	MCfitted[i][j][k]->Scale(fitBkg[i][j][k]*(On[i][j]->Integral()/MC[i][j][k]->Integral()));
      }
    }
  } 


  for(int i = 0; i < sel.size(); i++){
    for(int j = 0; j < vars.size(); j++){      
      for(int k = 1; k <= bkgds.size(); k++){
	StackFitted[i][j]->Add(MCfitted[i][j][bkgds.size()-k]);
	
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
      On[i][j]->SetMinimum(0);
      On[i][j]->Draw("");      
      StackFitted[i][j]->Draw("hist same");
      On[i][j]->Draw("same");      
      
      TLegend* leg = new TLegend(0.57, 0.7, 0.98, 0.92);
      for(int k = 0; k < bkgds.size(); k++){
	leg->AddEntry(MC[i][j][k], Form("%s,\n f : %4.2f",bkgds[k].c_str(),fitBkg[i][j][k]), "f");
      }
      leg->SetTextSize(0.045);
      leg->Draw("same");


      Title.DrawLatexNDC(0.5,0.95,Form("%s for the %s shower selection",vars[j].c_str(),sel[i].c_str()));
    

    }
  }

}
