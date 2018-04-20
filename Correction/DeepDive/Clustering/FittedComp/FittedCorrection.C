void FittedCorrection(){

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);  

  std::vector<double> fitted = {30,
				50,
				69.0438,
				94.948,
				119.358,
				155.407,
				173.536,
				211.948,
				237.103,
				262.174,
				272,
				299.167,
				355};

  std::vector<double> err = {0.510596,
			     0.903513,
			     0.960921,
			     1.08322,
			     3.26726,
			     2.05065,
			     3.97541,
			     3.04515,
			     4.37858,
			     7.62835,
			     12.3472,
			     10.4393,
			     17.3351,
			     491.453,
			     0};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);
    
  }
  Fit->GetXaxis()->SetTitle("Perfectly Clustered Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("MPV of Reconstructed Shower Energy [MeV]");  
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  Fit->Fit("pol1");

}
