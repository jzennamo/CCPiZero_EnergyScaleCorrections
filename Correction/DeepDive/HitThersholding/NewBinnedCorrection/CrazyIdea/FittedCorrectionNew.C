void FittedCorrectionNew(){

  gStyle->SetOptStat(1000000000);

  std::vector<double> fitted = {0.79,
				0.870124,
				0.797752,
				0.842501,
				0.791242,
				0.79,
				0.79,
				0.906386,
				0.792454,
				0.851825,
				0.834468,
				0.83733};

  std::vector<double> err = {0.142202,
			     0.137914,
			     0.0137232,
			     0.0350338,
			     0.0391157,
			     0.00225099,
			     0.0187623,
			     0.0207938,
			     0.0229837,
			     0.0103621,
			     0.0175051,
			     0.0192006};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    if(fitted[i] == 0.79) continue;   
    Fit->SetBinContent(i+1,  1/fitted[i]);
    Fit->SetBinError(i+1,  (1/fitted[i])*(err[i]/fitted[i]));    
  }

  TF1* h = new TF1("h","[0]+[1]*x",0,500);
  //  h->SetParLimits(0,1,10);
  gStyle->SetOptFit(1111);  
  Fit->GetXaxis()->SetTitle("E^{c}_{clus} Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Correction For Energy Missed By Cluster");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
