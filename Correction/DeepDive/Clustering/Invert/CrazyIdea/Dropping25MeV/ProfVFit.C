void ProfVFit(){

  //fit
  /*
    p0 = 15.412
    p1 =  0.725477
   */

  //profile
  /*
    p0 = 7.94482
    p1 = 0.681615 
   */

  TF1* fitted = new TF1("f","(9.93885e-01+x*(3.07774e-04))*x",0,250);
  TF1* profil = new TF1("p","(9.93097e-01+x*(3.14039e-04))*x",0,250);
  TF1* y = new TF1("y","x",0,250);


  fitted->SetTitle("");
  fitted->GetYaxis()->SetTitle("E^{c}_{clust} [MeV]");
  fitted->GetXaxis()->SetTitle("E_{reco} [MeV]");
  fitted->SetLineStyle(2);
  y->SetLineColor(kBlack);
  y->SetLineStyle(2);
  fitted->Draw("");
  profil->Draw("same");
  y->Draw("same");

  TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
  leg->AddEntry(fitted, "Correction Based on MPV Fit", "l");
  leg->AddEntry(profil, "Correction Based on MPV Fit, > 25 MeV", "l");
  leg->AddEntry(y, "y = x", "l");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  leg->Draw("same");

}
