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

  std::vector<double> fitted = {1.08743,
				1.26646,
				1.12326,
				1.17174,
				1.0508,
				1.10401,
				1.06309,
				1.15131,
				1.09371,
				1.1305,
				1.02281,
				1.12963};

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
  Fit->GetXaxis()->SetTitle("Cluster-Corrected Shower Energy [MeV]");
  Fit->GetYaxis()->SetTitle("Correction Factor");    
  Fit->SetLineColor(kRed);
  Fit->SetLineWidth(2);  
  Fit->Draw("");
  //  Fit->Fit("h");

  TF1* d = new TF1("d","x*0.725477+15.412",0,500);
  
  TF1* R = new TF1("r","h/d",0,500);
  //R->Draw();
}
