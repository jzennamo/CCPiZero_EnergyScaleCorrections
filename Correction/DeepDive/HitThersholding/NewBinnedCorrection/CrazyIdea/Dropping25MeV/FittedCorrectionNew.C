void FittedCorrectionNew(){

  gStyle->SetOptStat(1000000000);

  std::vector<double> fitted = {0.977862,
				0.914086,
				0.797754,
				0.8425,
				0.791242,
				0.871363,
				0.889398,
				0.906383,
				0.792463,
				0.863487,
				0.834467,
				0.837337};

  std::vector<double> err = {0.0459424,
			     0.0127385,
			     0.0142242,
			     0.0355419,
			     0.0144796,
			     0.0205587,
			     0.013574,
			     0.0209228,
			     0.0151384,
			     0.0204936,
			     0.0179815,
			     0.0196606};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    if(fitted[i] == 0.79) continue;   
    Fit->SetBinContent(i+1,  1/fitted[i]);
    Fit->SetBinError(i+1,  (1/fitted[i])*(err[i]/fitted[i]));    
  }

  TF1* h = new TF1("h","[0]+[1]*x",25,500);
  //  h->SetParLimits(0,1,10);
  gStyle->SetOptFit(1111);  
  Fit->GetXaxis()->SetTitle("E^{c}_{clus} Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Correction For Energy Missed By Cluster");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  Fit->Fit("h","R");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
