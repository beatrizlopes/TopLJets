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

int BDThistograms()
{
  TString fileName ="/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017F_SingleMuon_1.root";
  
  TFile* inputfile = TFile::Open(fileName,"UPDATE");
  TTree* tree = (TTree*)inputfile->Get("BDT");

  float ch = 0, BDTout = 0;
  TString channel = "";  
  tree->SetBranchAddress("channel",&ch);
  tree->SetBranchAddress("BDToutput",&BDTout);

  TH1F *ee_hist = new TH1F("ee_BDT_output","ee_BDT_output",50,-0.5,0.5);
  TH1F *mm_hist = new TH1F("mm_BDT_output","mm_BDT_output",50,-0.5,0.5);
  TH1F *em_hist = new TH1F("em_BDT_output","em_BDT_output",50,-0.5,0.5);

  for(int i = 0;i<tree->GetEntries();i++)
    {
      tree->GetEntry(i);
      if(ch==121) ee_hist->Fill(BDTout,1);
      else if(ch==143) em_hist->Fill(BDTout,1);
      else if(ch==169) mm_hist->Fill(BDTout,1);
    }
  
  inputfile->cd();
  ee_hist->Write();
  em_hist->Write();
  mm_hist->Write();

  inputfile->Close();
  return 0;
}

