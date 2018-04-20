void FittedCorrectionNew(){

  std::vector<double> fitted = {0.46666,
				0.716248,
				0.774517,
				0.808733,
				0.819932,
				0.837077,
				0.845332,
				0.851136,
				0.859249,
				0.877943,
				0.872751,
				0.878515};

  std::vector<double> err = {0.0156941,
			     0.00837566,
			     0.00750822,
			     0.00738083,
			     0.00859927,
			     0.00898355,
			     0.0103864,
			     0.011255,
			     0.0106608,
			     0.011893,
			     0.0134268,
			     0.0149786};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  1/fitted[i]);
    Fit->SetBinError(i+1,  (1/fitted[i])*(err[i]/fitted[i]));    
  }

  TF1* h = new TF1("h","[0]+[1]*x",0,500);
  //  h->SetParLimits(0,1,10);
  Fit->GetXaxis()->SetTitle("Reconstructed Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Correction For Energy Missed By Cluster");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
