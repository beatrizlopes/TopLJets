
void drawSystVar(TString var, TString process, TString filename)
{
  TFile *f = TFile::Open(filename);
  const char* Var = var;

  const char* Pro = "";
  if(process.Contains("ttbar")) Pro="Top";
  if(process.Contains("sig")) Pro="pp#rightarrowppttbar x 1000";

  TH1F* nom = (TH1F*)f->Get(Form("2b_BDT_output/2b_BDT_output_%s",Pro));
  nom->Rebin(2);

  vector<TH1F*> systs;

  for(int i=102; i>0;i--)
    {
      if(i==22) Var="PD";
      systs.push_back((TH1F*)f->Get(Form("2b_BDT_output_%s%03d/2b_BDT_output_%s%03d_%s",Var,i,Var,i,Pro)));
      systs.back()->Rebin(2);
      for(size_t nbin=0;nbin<nom->GetNbinsX(); nbin++)
	{
	  double variation =(systs.back()->GetBinContent(nbin)-nom->GetBinContent(nbin))/nom->GetBinContent(nbin);
	  cout << "for systematic PDF" << i << " in bin "<< nbin << " the variation is " <<  variation << endl;
	}
    }

}
