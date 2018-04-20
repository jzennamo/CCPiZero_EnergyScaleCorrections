Double_t ExpGaus(Double_t *x, Double_t *par){

  Double_t arg = 0;
  Double_t xv = x[0];

  if((xv-par[1])/par[2] <= -par[3]){
    arg = -0.5*(pow(((xv-par[1])/par[2]),2));}
  else{
    arg = (pow(par[3],2)/2.)+par[3]*((xv-par[1])/par[2]);}
  
  return par[0]*exp(arg);  
}

void NonFittedCorrectionNew(){

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
  
  std::vector<double> corr;
  double step = 500./15.;
  for(int i = 0; i < fitted.size();i++){
    corr.push_back(double((step/2)+step*i)/fitted[i]);
    std::cout << double((step/2)+step*i) << "/ " << fitted[i] << std::endl;
    
    

  }
  
  TH1D* Fit = new TH1D("f","",15,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  corr[i]);
    Fit->SetBinError(i+1, corr[i]*(err[i]/fitted[i]));
  }

  // TF1* h = new TF1("h","(x<133)*(gaus(0)) + (x>=133)*(pol0(3))",0,500);
  //  TF1* h = new TF1("h",ExpGaus,0,500,4);  
  TF1* h = new TF1("h","gaus(0) + exp(3)",0,300);
  h->SetParameter(0, 1.6);
  h->SetParameter(1, 50);
  h->SetParameter(1, 20);
  //  h->SetParameter(3, 1.15);
  //  h->SetParLimit(0,0,10);
  Fit->GetXaxis()->SetTitle("Reconstructed Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Correction Factor");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  //  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
