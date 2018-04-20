void MPV_Values(){

  gStyle->SetOptStat(0);
  
  std::vector<double> fitted = {0.974245,
				0.98801,
				1.00362,
				0.958411,
				0.981684,
				0.937358,
				0.952028,
				0.961386,
				0.896942,
				0.886966,
				0.914072,
				0.883261};

  std::vector<double> err = {0.0167454,
			     0.00219261,
			     0.00524271,
			     0.00887365,
			     0.0186157,
			     0.011178,
			     0.00935893,
			     0.0194991,
			     0.0175929,
			     0.0144452,
			     0.0316716,
			     0.291625};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);    
  }

  TF1* h = new TF1("h","pol0",0,500);
  //  h->SetParLimit(0,0,10);
  Fit->GetXaxis()->SetTitle("Reconstructed Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Fitted MPV Fraction of Charge in Cluster");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  //  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
