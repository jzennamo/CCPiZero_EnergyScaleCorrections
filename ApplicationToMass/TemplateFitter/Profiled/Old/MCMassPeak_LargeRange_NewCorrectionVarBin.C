void MCMassPeak_LargeRange_NewCorrectionVarBin(){

  gStyle->SetOptStat(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatColor(0);
  //  gStyle->SetOptFit(1111);
  //  gStyle->SetTitleFontSize(.08);
  gStyle->SetLabelSize(.045, "XY");
  gStyle->SetTitleSize(.045, "XY");
  gStyle->SetHistLineColor(kBlack);
  gStyle->SetHistLineWidth(2);
  gStyle->SetMarkerColor(kBlack);
  gStyle->SetMarkerStyle(33);
  gStyle->SetMarkerSize(1.3);


  std::vector< string > sel;
  //sel = {"one","two"};
  sel = {"two"};
  std::vector< string > vars;
  //vars = {"Nshw","Mult","Vy","Vx","Vz","Lmu","muCosTheta","muPhi","OpenAngle","ConvDist","Egamma","Mass","EgammaCorr","MassCorr"};
  vars = {"Mass","MassCorr"};

  std::vector< string > bkgds;
  //bkgds = {"sig","fsem","sce","mult","nc","other", "cosplusnu"};
  bkgds = {"sig"};
  //bkgds = {"fsem","sce","mult","nc","other", "cosplusnu"};

  std::vector< string > bkgds_fancy;
  bkgds_fancy = {"#nu_{#mu} CC #pi^{0} ","#nu_{#mu} CC Final State EM","#nu_{#mu} CC Charge Exch.","#nu_{#mu} CC Mult #pi^{0}","#nu_{#mu} NC #pi^{0}","Other", "Cosmic+#nu"};

  std::vector< TFile* >  OnFile; 
  std::vector< TFile* >  OffFile; 
  std::vector< TFile* >  MCFile; 
  OnFile.resize(sel.size()); 
  OffFile.resize(sel.size());
  MCFile.resize(sel.size()); 
  
  for(int i = 0; i < sel.size(); i++){
    OnFile[i]  = 
      new TFile(Form("../TemplateMaker/NewCorrectionVarWidth/output_onbeam_%s.root",sel[i].c_str()));
    OffFile[i] = 
      new TFile(Form("../TemplateMaker/NewCorrectionVarWidth/output_offbeam_%s.root",sel[i].c_str()));
    MCFile[i]  = 
      new TFile(Form("../TemplateMaker/NewCorrectionVarWidth/output_mc_%s.root",sel[i].c_str()));      
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
      On[i][j]->Add(Off[i][j],-1);      

      for(int b = 1; b <= 11; b++){
	On[i][j]->SetBinError(b,On[i][j]->GetBinError(b)/On[i][j]->GetBinWidth(b));
	On[i][j]->SetBinContent(b,On[i][j]->GetBinContent(b)/On[i][j]->GetBinWidth(b));
      }


      //On[i][j]->Rebin(4);
      //Off[i][j]->Rebin(4);
      

      

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
	
	for(int b = 1; b <= 11; b++){
	  MC[i][j][k]->SetBinError(b,MC[i][j][k]->GetBinError(b)/MC[i][j][k]->GetBinWidth(b));
	  MC[i][j][k]->SetBinContent(b, MC[i][j][k]->GetBinContent(b)/ MC[i][j][k]->GetBinWidth(b));
	}


	//MC[i][j][k]->Rebin(4);
	On[i][j]->Add(MC[i][j][k],-1);
	
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
  //  Title.SetTextAlign(23);
  Title.SetTextSize(0.045);
     
  for(int i = 0; i < sel.size(); i++){
    for(int j = 0; j < vars.size(); j++){
      
      if(On[i][j]->Integral() == 0) continue;     
      c[i][j] = new TCanvas(Form("c_%d_%d",i,j));
      c[i][j]->cd();
      // The Stac
      
      MC[i][j][0]->GetYaxis()->SetTitle("Events / MeV");
      MC[i][j][0]->GetXaxis()->SetTitle("M_{12} [MeV]");
      MC[i][j][0]->SetMaximum(MC[i][j][0]->GetMaximum()*1.3);
      MC[i][j][0]->SetMinimum(0.001);
      MC[i][j][0]->Draw("");            
      MC[i][j][0]->UseCurrentStyle();
      //Stack[i][j]->Draw("hist same");
      MC[i][j][0]->Draw("esame");            
      MC[i][j][0]->Draw("e1p same");      
      gPad->RedrawAxis();

      TF1* fit = new TF1("fit","expo(0)+gaus(2)",0,800);
      fit->SetParLimits(2, 0, 500);
      fit->SetParameter(3, 135);
      fit->SetParameter(4, 50);
      MC[i][j][0]->Fit("fit");
      fit->SetLineColor(kRed);
      fit->SetLineWidth(2);
      fit->Draw("same");

      //Signal Only
       /*
       MC[i][j][0]->Draw("");
       */

      TLine line;
      line.SetLineColor(kBlue);
      line.SetLineStyle(2);
      line.SetLineWidth(2);
      line.DrawLine(135,MC[i][j][0]->GetMinimum(),135,MC[i][j][0]->GetMaximum());
      //MC[i][j][0]->Draw("");      
      TLine line2;
      line2.SetLineColor(kRed);
      line2.SetLineStyle(2);
      line2.SetLineWidth(2);
      line2.DrawLine(35,MC[i][j][0]->GetMinimum(),35,MC[i][j][0]->GetMaximum());
      line2.DrawLine(230,MC[i][j][0]->GetMinimum(),230,MC[i][j][0]->GetMaximum());
      
      
      TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
      leg->AddEntry(MC[i][j][0], Form("MC %s",bkgds_fancy[0].c_str()), "pl");
      //      for(int k = 0; k < bkgds.size(); k++){
      //	leg->AddEntry(MC[i][j][0], Form("%s",bkgds_fancy[0].c_str()), "f");
      // }
      leg->SetLineColor(kWhite);
      leg->SetTextSize(0.045);
      leg->Draw("same");


      Title.DrawLatexNDC(0.45,0.35,Form("Fitted Peak : (%4.1f #pm %4.2f) MeV",
				       fit->GetParameter(3),
				       fit->GetParError(3)));
      Title.DrawLatexNDC(0.45,0.30,Form("Fitted Width : (%4.1f #pm %4.2f) MeV",
				       fabs(fit->GetParameter(4)),
				       fit->GetParError(4)));

      Title.DrawLatexNDC(0.45,0.25,Form("#chi^{2}/dof : (%4.1f / %d)",
				       fit->GetChisquare(),
				       fit->GetNDF()));

    }
  }

}
