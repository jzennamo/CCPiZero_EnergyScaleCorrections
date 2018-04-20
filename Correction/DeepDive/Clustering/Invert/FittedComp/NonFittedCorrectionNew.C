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

  std::vector<double> fitted = {1.48784,
				1.19033,
				1.15174,
				1.10616,
				1.12766,
				1.11696,
				1.0697,
				1.0619,
				1.13098,
				1.09084,
				1.11489,
				1.05649};

  TH1D* Fit = new TH1D("f","",20,0,500);
  
  for(int i = 0; i < fitted.size(); i++){
    Fit->SetBinContent(i+1,  fitted[i]);
    //Fit->SetBinError(i+1, corr[i]*(err[i]/fitted[i]));
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
