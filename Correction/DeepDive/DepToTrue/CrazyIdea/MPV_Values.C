void MPV_Values(){

  gStyle->SetOptStat(0);
  
  std::vector<double> fitted = {0.806368,
				1.10884,
				0.99752,
				0.97294,
				0.912579,
				0.901534,
				0.959848,
				0.97228,
				1.01297,
				0.909436,
				0.965777,
				0.902586};

  std::vector<double> err = {0.25147,
			     0.0210571,
			     0.0223701,
			     0.0223627,
			     0.0208954,
			     0.0225395,
			     0.0278044,
			     0.0574908,
			     0.0268313,
			     0.0163491,
			     0.0369493,
			     0.0176199};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    if(fitted[i] == 0.79) continue;
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);    
  }

  TF1* h = new TF1("h","pol1",0,500);
  //  h->SetParLimit(0,0,10);
  Fit->GetXaxis()->SetTitle("E^{c}_{Tot} Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Fitted MPV Fraction of True Energy in Shower");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  //  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
