void ProfVFit(){

  /* Fitted 
    bin 0 mean 22.0862
    bin 1 mean 38.6409
    bin 2 mean 59.7294
    bin 3 mean 82.3846
    bin 4 mean 109.277
    bin 5 mean 116.98
    bin 6 mean 151.137
    bin 7 mean 178.816
    bin 8 mean 215.863
    bin 9 mean 229.148
    bin 10 mean 254.49
    bin 11 mean 261.827
    bin 12 mean 278.97
    bin 13 mean 262.864
    bin 14 mean 261.243
  */
  std::vector<double> fitted = {22.0862,38.6409,59.7294,82.3846,109.277,116.98,151.137,178.816,215.863,229.148, 254.49, 261.827, 278.97, 262.864, 261.243};

  TH1D* Fit = new TH1D("fit","",15,0,500);

  /* prof
     bin 1 mean 23.1677
     bin 2 mean 38.9281
     bin 3 mean 57.2269
     bin 4 mean 73.8591
     bin 5 mean 95.7621
     bin 6 mean 116.106
     bin 7 mean 129.024
     bin 8 mean 151.245
     bin 9 mean 173.488
    bin 10 mean 185.646
    bin 11 mean 211.373
    bin 12 mean 222
    bin 13 mean 229.701
    bin 14 mean 263.684
    bin 15 mean 259.231
  */
  std::vector<double> prof = {23.1677, 
			      38.9281, 
			      57.2269, 
			      73.8591, 
			      95.7621, 
			      116.106, 
			      129.024 ,
			      151.245, 
			      173.488, 
			      185.646, 
			      211.373 ,
			      222     ,
			      229.701 ,
			      263.684 ,
			      259.231 };

  TH1D* Prof = new TH1D("p","",15,0,500);
  
  TH1D* Diff = new TH1D("d","",15,0,500);

  for(int i = 0; i < prof.size(); i++){
    Prof->SetBinContent(i+1, prof[i]);
    Fit->SetBinContent(i+1,  fitted[i]);
    Diff->SetBinContent(i+1, fabs(fitted[i]-prof[i])/prof[i]);
  }
  
  Prof->SetLineColor(kGreen);
  Fit->SetLineColor(kRed);

  Prof->SetLineWidth(2);
  Fit->SetLineWidth(2);
  
  Prof->Draw();
  Fit->Draw("same");

  Diff->Draw();
  
}
