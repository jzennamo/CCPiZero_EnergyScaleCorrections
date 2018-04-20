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

  TF1* fitted = new TF1("f","(x-15.412)/0.725477",0,250);
  TF1* profil = new TF1("p","(x-7.94482)/0.681615",0,250);


  fitted->SetTitle("");
  fitted->GetYaxis()->SetTitle("E^{c}_{clust} [MeV]");
  fitted->GetXaxis()->SetTitle("E_{reco} [MeV]");
  fitted->SetLineStyle(2);
  fitted->Draw("");
  profil->Draw("same");

  TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
  leg->AddEntry(fitted, "Correction Based on Trunc. Mean", "l");
  leg->AddEntry(profil, "Correction Based on Mean", "l");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  leg->Draw("same");

}
