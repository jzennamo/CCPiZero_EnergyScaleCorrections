void ProfVFit(){

  //fit
  /*
    x = 0.000785133* 
    (sqrt(2547340000.*y + 665667863369.) - 798389.)
    
   */

  //profile
  /*
    -0.000820487*
    sqrt(2017450716259. - 3805000000.*x) + 1165.35
   */

  TF1* fitted = new TF1("f","(1.13881+x*(1.48797e-04))*x",0,250);
  TF1* profil = new TF1("p","(1.12977+x*(1.83609e-04))*x",0,250);
  TF1* y = new TF1("y","x",0,250);

  fitted->SetTitle("");
  fitted->GetYaxis()->SetTitle("E^{c}_{Tot} [MeV]");
  fitted->GetXaxis()->SetTitle("E^{c}_{Clust} [MeV]");
  fitted->SetLineStyle(2);
  y->SetLineColor(kBlack);
  y->SetLineStyle(2);
  fitted->Draw("");
  profil->Draw("same");
  y->Draw("same");

  TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
  leg->AddEntry(fitted, "Correction Including Bad Fits, > 25 MeV", "l");
  leg->AddEntry(profil, "Correction Including Bad Fits", "l");
  leg->AddEntry(y, "y = x", "l");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  leg->Draw("same");

}
