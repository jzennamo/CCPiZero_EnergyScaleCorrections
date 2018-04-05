void FittedCorrection(){

  std::vector<double> fitted = {23.8685,
				42.9191,
				66.0417,
				98.1805,
				121.435,
				158.723,
				175.874,
				217.804,
				247.28,
				262.014,
				300.69,
				274.192,
				373.457,
				418.047};

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
			     210.4393,//10.4
			     17.3351,
			     491.453};

  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);
    
  }
  
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  
}
