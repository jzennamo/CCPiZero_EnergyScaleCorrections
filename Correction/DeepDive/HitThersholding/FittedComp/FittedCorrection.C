void FittedCorrection(){

  std::vector<double> fitted = {11.5619,
				30.5473,
				58.6132,
				99.3284,
				115.568,
				164.777,
				191.284,
				224.894,
				276.272,
				291.653,
				337.887};

  std::vector<double> err = {14.3857,
			     0.968493,
			     1.01999,
			     1.92588,
			     2.18537,
			     6.87013,
			     4.71074,
			     6.20522,
			     5.15144,
			     10.4109,
			     14.2917,
			     23.2907,
			     7.15942,
			     1.41421,
			     12076.5};

  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);
    
  }
  
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  
}
