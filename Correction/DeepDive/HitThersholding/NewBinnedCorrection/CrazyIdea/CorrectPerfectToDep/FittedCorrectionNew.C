void FittedCorrectionNew(){

  gStyle->SetOptStat(1000000000);

  std::vector<double> fitted = {0.915862,
				0.935691,
				0.922304,
				0.926828,
				0.924394,
				0.924444,
				0.91436,
				0.927509,
				0.916573,
				0.918985,
				0.905438,
				0.914083};

  std::vector<double> err = {0.0312313,
			     0.0063543,
			     0.00322669,
			     0.00497651,
			     0.00526641,
			     0.0044415,
			     0.00482318,
			     0.0102151,
			     0.0254003,
			     0.00297882,
			     0.0611702,
			     0.0244877};
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
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
