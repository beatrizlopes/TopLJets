
void drawSystVar(TString var, TString process, TString filename)
{
  TFile *f = TFile::Open(filename);
  const char* Var = var;

  const char* Pro = "";
  if(process.Contains("ttbar")) Pro="Top";
  if(process.Contains("sig")) Pro="pp#rightarrowppttbar x 1000";

  TH1F* up = (TH1F*)f->Get(Form("2b_BDT_output_%sup/2b_BDT_output_%sup_%s",Var,Var,Pro));
  TH1F* dn = (TH1F*)f->Get(Form("2b_BDT_output_%sdn/2b_BDT_output_%sdn_%s",Var,Var,Pro));
  TH1F* nom = (TH1F*)f->Get(Form("2b_BDT_output/2b_BDT_output_%s",Pro));

  if(var=="bfrag")
    {
      up->Scale(nom->Integral()/up->Integral());
      dn->Scale(nom->Integral()/dn->Integral());
    }

  nom->SetLineColor(1);
  up->SetLineColor(2);
  dn->SetLineColor(3);


  dn->Draw();
  nom->Draw("same");
  up->Draw("same");
}
