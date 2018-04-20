void MPV_Values(){

  gStyle->SetOptStat(0);

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
    if(fitted[i] == 0.79) continue;
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);    
  }

  TF1* h = new TF1("h","pol1",0,500);
  //  h->SetParLimit(0,0,10);
  Fit->GetXaxis()->SetTitle("E^{c}_{clus} Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Fitted MPV Fraction of Charge in Cluster");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  //  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
