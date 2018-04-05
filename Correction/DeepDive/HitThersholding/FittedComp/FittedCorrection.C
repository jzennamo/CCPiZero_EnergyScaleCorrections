void FittedCorrection(){

  std::vector<double> fitted = {21.1463,
				45.2724,
				77.8619,
				115.813,
				147.893,
				174.391,
				212.4,
				249.026,
				308.69,
				317.364,
				373.831,
				401.565,
				406.586,
				37.9073,
				412.619};

  std::vector<double> err = {1.45133,
			     1.1466,
			     1.07412,
			     2.20086,
			     2.29156,
			     7.20009,
			     5.63245,
			     6.66422,
			     4.44788,
			     10.4463,
			     16.187,
			     19.8309,
			     7.96066,
			     59.8725,
			     15.1173};

  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    Fit->SetBinError(i+1,  err[i]);
    
  }
  
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  
}
