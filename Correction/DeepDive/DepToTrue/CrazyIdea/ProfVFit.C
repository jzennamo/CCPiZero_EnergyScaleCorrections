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

  TF1* fitted = new TF1("f","x*(9.43398e-01+(4.42796e-04)*x)",0,250);
  TF1* profil = new TF1("p","x",0,250);


  fitted->SetTitle("");
  fitted->GetYaxis()->SetTitle("E^{c}_{True} [MeV]");
  fitted->GetXaxis()->SetTitle("E^{c}_{Tot} [MeV]");
  fitted->SetLineStyle(2);
  fitted->Draw("");
  profil->SetLineColor(kBlack);
  profil->SetLineStyle(2);
  profil->Draw("same");

  TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
  leg->AddEntry(fitted, "MPV Based Correction", "l");
  leg->AddEntry(profil, "y = x", "l");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  leg->Draw("same");

}
