void MPV_Values(){

  gStyle->SetOptStat(0);
  
  std::vector<double> fitted = {1.25057,
				0.899165,
				0.845606,
				0.775278,
				0.780134,
				0.798999,
				0.813298,
				0.771334,
				0.76489,
				0.786367,
				0.770258,
				0.78353};

  std::vector<double> err = {0.704096,
			     0.0110184,
			     0.015924,
			     0.0173999,
			     0.0135792,
			     0.026067,
			     0.0302235,
			     0.0184173,
			     0.0127728,
			     0.0150418,
			     0.0194329,
			     0.0300748};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    if(fitted[i] == 0.79) continue;
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);    
  }

  TF1* h = new TF1("h","pol1",0,500);
  //  h->SetParLimit(0,0,10);
  Fit->GetXaxis()->SetTitle("E^{c}_{Tot} Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Fitted MPV Fraction of Dep. Energy in Shower");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  //  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
