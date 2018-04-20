void Pol2(){

  gStyle->SetOptStat(1000000000);

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
    Fit->SetBinContent(i+1,  1/fitted[i]);
    Fit->SetBinError(i+1,  (1/fitted[i])*(err[i]/fitted[i]));    
  }

  TF1* h = new TF1("h","[0]+[1]*x+[2]*x*x",25,500);
  
  gStyle->SetOptFit(1111);
  Fit->GetXaxis()->SetTitle("E_{Reco} Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Correction To Energy Depoisted in the Detector");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  Fit->Fit("h","R");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
