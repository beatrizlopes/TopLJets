#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TChain.h>
#include <TCut.h>
#include <TString.h>
#include <TObject.h>
#include <TRandom3.h>
#include <TDirectory.h>

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>

int chooseBDTcut()
{

  TString filename = "/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/plots/sel/ul/plotter.root";
  TFile* file =  new TFile(filename);

  std::cout << "Processing file" << filename << std::endl;  

  file->cd();

  TH1F* bdtoutputbkg = (TH1F*)file->Get("2b_BDT_output/2b_BDT_output_Top");
  TH1F* bdtoutputDY = (TH1F*)file->Get("2b_BDT_output/2b_BDT_output_DY");
  TH1F* bdtoutputMB = (TH1F*)file->Get("2b_BDT_output/2b_BDT_output_Multiboson");
  TH1F* bdtoutputsig = (TH1F*)file->Get("2b_BDT_output/2b_BDT_output_pp#rightarrowppttbar x 1000");

  if(!bdtoutputbkg) std::cout << "couldn't read" << std::endl;

  double cut = 0.7;
  double FOM=0;
  double sig,bkg = 9999;
  int j = 0;
  TGraph* FOMgraph = new TGraph(50);

  while(cut>-0.7)
    {
      cout << j << endl;
      sig=0;
      bkg=0;
      FOM=0;

      for(int i =bdtoutputsig->GetNbinsX();i>0;i--)
	{	
	  //cout << "cenas" << endl;
	  bkg+=bdtoutputbkg->GetBinContent(i);
	  bkg+=bdtoutputDY->GetBinContent(i);
	  bkg+=bdtoutputMB->GetBinContent(i);
	  sig+=bdtoutputsig->GetBinContent(i);
	  cout << bdtoutputsig->GetXaxis()->GetBinCenter(i) << endl;
	  if((bdtoutputsig->GetXaxis()->GetBinCenter(i))<cut)  i=0;
	}

      sig=sig/1000;
      cout << "bkg:" << bkg << " sig:" << sig << endl;
      FOM=sig/sqrt(bkg);
      FOMgraph->SetPoint(j,cut,FOM);
      cut=cut-0.05;
      j++;
    }

  TGaxis::SetMaxDigits(3);
  FOMgraph->SetTitle("BDT cut optimizer");
  FOMgraph->GetXaxis()->SetTitle("BDT output cut");
  FOMgraph->GetYaxis()->SetTitle("S/sqrt(B)");
  FOMgraph->GetYaxis()->SetTitleOffset(0.8);
  //  FOMgraph->GetYaxis()->SetMaxDigits(2);
  FOMgraph->Draw("A*");
  //double maxi = TMath::MaxElement(50,FOMgraph->GetY());
  //cout << "MAX " << maxi << endl;
  //  FOMgraph->Print();
  //for(int k=0;k<FOM.size();k++)
  //cout << "FOM" << FOM[k] << endl;

  return 0;
}

