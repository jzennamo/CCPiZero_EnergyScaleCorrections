void FittedCorrectionNew(){

  std::vector<double> fitted = {25.434,
				43.3333,
				69.7821,
				105.572,
				142.222,
				170.122,
				198.464,
				233.924,
				253.92,
				296.854,
				303.261};

  std::vector<double> err = {0.481534,
			     0.0675672,
			     1.07052,
			     1.85219,
			     2.54291,
			     3.68506,
			     7.54939,
			     6.00478,
			     5.79355,
			     6.81752,
			     17.1499};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);    
  }

  TF1* h = new TF1("h","pol1",0,500);
  //  h->SetParLimit(0,0,10);
  Fit->GetXaxis()->SetTitle("Perfectly Clustered Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("MPV of Reconstructed Shower Energy [MeV]");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
