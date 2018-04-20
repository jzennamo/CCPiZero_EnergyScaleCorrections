void RatioPol1(){

  TF1* fitted = new TF1("f","(1.24497+((9.93885e-01+x*(3.07774e-04))*x)*(-2.01225e-04))*((9.93885e-01+x*(3.07774e-04))*x)",0,250);
  TF1* current = new TF1("new","(1.12320 + x*(5.89862e-04))",0,250);
  TF1* profil = new TF1("p","(f-new)/f",0,250);


  fitted->SetTitle("");
  fitted->GetYaxis()->SetTitle("E^{c}_{Tot} [MeV]");
  fitted->GetXaxis()->SetTitle("E_{reco} [MeV]");
  fitted->SetLineStyle(2);
  //fitted->Draw("");
  //  current->Draw("same");
  profil->SetLineColor(kBlack);
  profil->SetLineStyle(2);
  profil->Draw("");

  TLegend* leg = new TLegend(0.45, 0.45, 0.88, 0.88);
  leg->AddEntry(fitted, "MPV Based Correction, Double", "l");
  leg->AddEntry(current, "MPV Based Correction, Single", "l");
  leg->AddEntry(profil, "y = x", "l");
  leg->SetLineColor(kWhite);
  leg->SetTextSize(0.045);
  //  leg->Draw("same");

}
