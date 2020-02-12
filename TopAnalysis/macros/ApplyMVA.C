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

bool exists_test (TString name) {
  ifstream f(name);
  return f.good();
}

void BDThistograms(TString fileName)
{
  //  TString fileName ="/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017F_SingleMuon_3.root";                                    
  //TString fileName ="/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017F_SingleMuon_1.root";

  TFile* inputfile = TFile::Open(fileName,"UPDATE");
  TTree* tree = (TTree*)inputfile->Get("BDT");
  TTree* wtree = (TTree*)inputfile->Get("sel");
 
  float ch = 0, BDTout = 0, weight = 1, syst_muUp=1, syst_muDn=1, syst_jerUp=1, syst_jerDn=1, syst_btaglfUp=1, syst_btaglfDn=1, syst_btaghfUp=1, syst_btaghfDn=1, syst_ees1Up=1, syst_ees1Dn=1, syst_mes1Up=1, syst_mes1Dn=1, syst_topptUp=1, syst_topptDn=1, syst_mselUp=1, syst_mselDn=1,syst_eselUp=1, syst_eselDn=1, syst_l1prefireUp=1,syst_l1prefireDn=1, syst_bfragUp=1, syst_bfragDn=1;


  float syst_AbsoluteStatJECup=1,syst_AbsoluteScaleJECup=1, syst_AbsoluteMPFBiasJECup=1, syst_FragmentationJECup=1, syst_SinglePionECALJECup=1,
    syst_SinglePionHCALJECup=1, syst_FlavorPureGluonJECup=1, syst_FlavorPureQuarkJECup=1, syst_FlavorPureCharmJECup=1, syst_FlavorPureBottomJECup=1, 
    syst_TimePtEtaJECup=1, syst_RelativeJEREC1JECup=1, syst_RelativeJEREC2JECup=1, syst_RelativeJERHFJECup=1, syst_RelativePtBBJECup=1, syst_RelativePtEC1JECup=1, 
    syst_RelativePtEC2JECup=1, syst_RelativePtHFJECup=1, syst_RelativeBalJECup=1, syst_RelativeFSRJECup=1, syst_RelativeStatFSRJECup=1, syst_RelativeStatECJECup=1, 
    syst_RelativeStatHFJECup=1, syst_PileUpDataMCJECup=1, syst_PileUpPtRefJECup=1, syst_PileUpPtBBJECup=1, syst_PileUpPtEC1JECup=1, syst_PileUpPtEC2JECup=1, 
    syst_PileUpPtHFJECup=1, syst_AbsoluteStatJECdn=1, syst_AbsoluteScaleJECdn=1, syst_AbsoluteMPFBiasJECdn=1, syst_FragmentationJECdn=1, syst_SinglePionECALJECdn=1, 
    syst_SinglePionHCALJECdn=1, syst_FlavorPureGluonJECdn=1, syst_FlavorPureQuarkJECdn=1, syst_FlavorPureCharmJECdn=1, syst_FlavorPureBottomJECdn=1, 
    syst_TimePtEtaJECdn=1, syst_RelativeJEREC1JECdn=1, syst_RelativeJEREC2JECdn=1, syst_RelativeJERHFJECdn=1, syst_RelativePtBBJECdn=1, syst_RelativePtEC1JECdn=1, 
    syst_RelativePtEC2JECdn=1, syst_RelativePtHFJECdn=1, syst_RelativeBalJECdn=1, syst_RelativeFSRJECdn=1, syst_RelativeStatFSRJECdn=1, syst_RelativeStatECJECdn=1, 
    syst_RelativeStatHFJECdn=1, syst_PileUpDataMCJECdn=1, syst_PileUpPtRefJECdn=1, syst_PileUpPtBBJECdn=1, syst_PileUpPtEC1JECdn=1, syst_PileUpPtEC2JECdn=1, 
    syst_PileUpPtHFJECdn=1;

  TString channel = "";

  tree->SetBranchAddress("channel",&ch);
  tree->SetBranchAddress("BDToutput",&BDTout);
  if(fileName.Contains("MC"))   
    {
      wtree->SetBranchAddress("weight",&weight);
      
      if(fileName.Contains("TT"))
	{
	  wtree->SetBranchAddress("systw_muUp",&syst_muUp);
	  wtree->SetBranchAddress("systw_muDn",&syst_muDn);
	  wtree->SetBranchAddress("systw_topptup",&syst_topptUp);
	  wtree->SetBranchAddress("systw_topptdn",&syst_topptDn);
	}
	
      if(fileName.Contains("TT") || fileName.Contains("FPMC"))
	{
	  wtree->SetBranchAddress("systw_JERup",&syst_jerUp);
	  wtree->SetBranchAddress("systw_JERdn",&syst_jerDn);
	  wtree->SetBranchAddress("systw_btaglfup",&syst_btaglfUp);
	  wtree->SetBranchAddress("systw_btaglfdn",&syst_btaglfDn);
	  wtree->SetBranchAddress("systw_btaghfup",&syst_btaghfUp);
	  wtree->SetBranchAddress("systw_btaghfdn",&syst_btaghfDn);
	  wtree->SetBranchAddress("systw_ees1up",&syst_ees1Up);
	  wtree->SetBranchAddress("systw_ees1dn",&syst_ees1Dn);
	  wtree->SetBranchAddress("systw_mes1up",&syst_mes1Up);
	  wtree->SetBranchAddress("systw_mes1dn",&syst_mes1Dn);

	  wtree->SetBranchAddress("systw_mselup",&syst_mselUp);
	  wtree->SetBranchAddress("systw_mseldn",&syst_mselDn);
	  wtree->SetBranchAddress("systw_eselup",&syst_eselUp);
	  wtree->SetBranchAddress("systw_eseldn",&syst_eselDn);

	  wtree->SetBranchAddress("systw_l1prefireup",&syst_l1prefireUp);
	  wtree->SetBranchAddress("systw_l1prefiredn",&syst_l1prefireDn); 
	  wtree->SetBranchAddress("systw_bfragup",&syst_bfragUp); 
	  wtree->SetBranchAddress("systw_bfragdn",&syst_bfragDn);
	  
	  wtree->SetBranchAddress("systw_AbsoluteStatJECup",&syst_AbsoluteStatJECup);
	  wtree->SetBranchAddress("systw_AbsoluteScaleJECup",&syst_AbsoluteScaleJECup);
	  wtree->SetBranchAddress("systw_AbsoluteMPFBiasJECup",&syst_AbsoluteMPFBiasJECup); 
	  wtree->SetBranchAddress("systw_FragmentationJECup",&syst_FragmentationJECup); 
	  wtree->SetBranchAddress("systw_SinglePionECALJECup",&syst_SinglePionECALJECup);
	  wtree->SetBranchAddress("systw_SinglePionHCALJECup",&syst_SinglePionHCALJECup); 
	  wtree->SetBranchAddress("systw_FlavorPureGluonJECup",&syst_FlavorPureGluonJECup); 
	  wtree->SetBranchAddress("systw_FlavorPureQuarkJECup",&syst_FlavorPureQuarkJECup); 
	  wtree->SetBranchAddress("systw_FlavorPureCharmJECup",&syst_FlavorPureCharmJECup); 
	  wtree->SetBranchAddress("systw_FlavorPureBottomJECup",&syst_FlavorPureBottomJECup); 
	  wtree->SetBranchAddress("systw_TimePtEtaJECup",&syst_TimePtEtaJECup); 
	  wtree->SetBranchAddress("systw_RelativeJEREC1JECup",&syst_RelativeJEREC1JECup); 
	  wtree->SetBranchAddress("systw_RelativeJEREC2JECup",&syst_RelativeJEREC2JECup); 
	  wtree->SetBranchAddress("systw_RelativeJERHFJECup",&syst_RelativeJERHFJECup); 
	  wtree->SetBranchAddress("systw_RelativePtBBJECup",&syst_RelativePtBBJECup); 
	  wtree->SetBranchAddress("systw_RelativePtEC1JECup",&syst_RelativePtEC1JECup); 
	  wtree->SetBranchAddress("systw_RelativePtEC2JECup",&syst_RelativePtEC2JECup); 
	  wtree->SetBranchAddress("systw_RelativePtHFJECup",&syst_RelativePtHFJECup); 
	  wtree->SetBranchAddress("systw_RelativeBalJECup",&syst_RelativeBalJECup); 
	  wtree->SetBranchAddress("systw_RelativeFSRJECup",&syst_RelativeFSRJECup); 
	  wtree->SetBranchAddress("systw_RelativeStatFSRJECup",&syst_RelativeStatFSRJECup); 
	  wtree->SetBranchAddress("systw_RelativeStatECJECu",&syst_RelativeStatECJECup); 
	  wtree->SetBranchAddress("systw_RelativeStatHFJECup",&syst_RelativeStatHFJECup); 
	  wtree->SetBranchAddress("systw_PileUpDataMCJECup",&syst_PileUpDataMCJECup); 
	  wtree->SetBranchAddress("systw_PileUpPtRefJECup",&syst_PileUpPtRefJECup); 
	  wtree->SetBranchAddress("systw_PileUpPtBBJECup",&syst_PileUpPtBBJECup); 
	  wtree->SetBranchAddress("systw_PileUpPtEC1JECup",&syst_PileUpPtEC1JECup); 
	  wtree->SetBranchAddress("systw_PileUpPtEC2JECup",&syst_PileUpPtEC2JECup); 
	  wtree->SetBranchAddress("systw_PileUpPtHFJECup",&syst_PileUpPtHFJECup);
	  
	  wtree->SetBranchAddress("systw_AbsoluteStatJECdn",&syst_AbsoluteStatJECdn);
	  wtree->SetBranchAddress("systw_AbsoluteScaleJECdn",&syst_AbsoluteScaleJECdn);
	  wtree->SetBranchAddress("systw_AbsoluteMPFBiasJECdn",&syst_AbsoluteMPFBiasJECdn); 
	  wtree->SetBranchAddress("systw_FragmentationJECdn",&syst_FragmentationJECdn); 
	  wtree->SetBranchAddress("systw_SinglePionECALJECdn",&syst_SinglePionECALJECdn);
	  wtree->SetBranchAddress("systw_SinglePionHCALJECdn",&syst_SinglePionHCALJECdn); 
	  wtree->SetBranchAddress("systw_FlavorPureGluonJECdn",&syst_FlavorPureGluonJECdn); 
	  wtree->SetBranchAddress("systw_FlavorPureQuarkJECdn",&syst_FlavorPureQuarkJECdn); 
	  wtree->SetBranchAddress("systw_FlavorPureCharmJECdn",&syst_FlavorPureCharmJECdn); 
	  wtree->SetBranchAddress("systw_FlavorPureBottomJECdn",&syst_FlavorPureBottomJECdn); 
	  wtree->SetBranchAddress("systw_TimePtEtaJECdn",&syst_TimePtEtaJECdn); 
	  wtree->SetBranchAddress("systw_RelativeJEREC1JECdn",&syst_RelativeJEREC1JECdn); 
	  wtree->SetBranchAddress("systw_RelativeJEREC2JECdn",&syst_RelativeJEREC2JECdn); 
	  wtree->SetBranchAddress("systw_RelativeJERHFJECdn",&syst_RelativeJERHFJECdn); 
	  wtree->SetBranchAddress("systw_RelativePtBBJECdn",&syst_RelativePtBBJECdn); 
	  wtree->SetBranchAddress("systw_RelativePtEC1JECdn",&syst_RelativePtEC1JECdn); 
	  wtree->SetBranchAddress("systw_RelativePtEC2JECdn",&syst_RelativePtEC2JECdn); 
	  wtree->SetBranchAddress("systw_RelativePtHFJECdn",&syst_RelativePtHFJECdn); 
	  wtree->SetBranchAddress("systw_RelativeBalJECdn",&syst_RelativeBalJECdn); 
	  wtree->SetBranchAddress("systw_RelativeFSRJECdn",&syst_RelativeFSRJECdn); 
	  wtree->SetBranchAddress("systw_RelativeStatFSRJECdn",&syst_RelativeStatFSRJECdn); 
	  wtree->SetBranchAddress("systw_RelativeStatECJECdn",&syst_RelativeStatECJECdn); 
	  wtree->SetBranchAddress("systw_RelativeStatHFJECdn",&syst_RelativeStatHFJECdn); 
	  wtree->SetBranchAddress("systw_PileUpDataMCJECdn",&syst_PileUpDataMCJECdn); 
	  wtree->SetBranchAddress("systw_PileUpPtRefJECdn",&syst_PileUpPtRefJECdn); 
	  wtree->SetBranchAddress("systw_PileUpPtBBJECdn",&syst_PileUpPtBBJECdn); 
	  wtree->SetBranchAddress("systw_PileUpPtEC1JECdn",&syst_PileUpPtEC1JECdn); 
	  wtree->SetBranchAddress("systw_PileUpPtEC2JECdn",&syst_PileUpPtEC2JECdn); 
	  wtree->SetBranchAddress("systw_PileUpPtHFJECdn",&syst_PileUpPtHFJECdn);
	}
    }

  vector< TH1F* > bdt_hists;
  TString systNames[] = { "muUp", "muDn", "jerUp", "jerDn", "btaglfUp", "btaglfDn", "btaghfUp", "btaghfDn", "ees1Up", "ees1Dn", "mes1Up", 
			  "mes1Dn", "topptUp", "topptDn", "mselUp", "mselDn","eselUp", "eselDn", "l1prefireUp","l1prefireDn", "bfragUp", 
			  "bfragDn", "AbsoluteStatJECup",
			  "AbsoluteScaleJECup", "AbsoluteMPFBiasJECup", "FragmentationJECup", "SinglePionECALJECup",
			  "SinglePionHCALJECup", "FlavorPureGluonJECup", "FlavorPureQuarkJECup", "FlavorPureCharmJECup", 
			  "FlavorPureBottomJECup", 
			  "TimePtEtaJECup", "RelativeJEREC1JECup", "RelativeJEREC2JECup", "RelativeJERHFJECup", "RelativePtBBJECup", 
			  "RelativePtEC1JECup", 
			  "RelativePtEC2JECup", "RelativePtHFJECup", "RelativeBalJECup", "RelativeFSRJECup", "RelativeStatFSRJECup", 
			  "RelativeStatECJECup", 
			  "RelativeStatHFJECup", "PileUpDataMCJECup", "PileUpPtRefJECup", "PileUpPtBBJECup", "PileUpPtEC1JECup", 
			  "PileUpPtEC2JECup", 
			  "PileUpPtHFJECup", "AbsoluteStatJECdn", "AbsoluteScaleJECdn", "AbsoluteMPFBiasJECdn", "FragmentationJECdn", 
			  "SinglePionECALJECdn", 
			  "SinglePionHCALJECdn", "FlavorPureGluonJECdn", "FlavorPureQuarkJECdn", "FlavorPureCharmJECdn", 
			  "FlavorPureBottomJECdn", 
			  "TimePtEtaJECdn", "RelativeJEREC1JECdn", "RelativeJEREC2JECdn", "RelativeJERHFJECdn", "RelativePtBBJECdn", 
			  "RelativePtEC1JECdn", 
			  "RelativePtEC2JECdn", "RelativePtHFJECdn", "RelativeBalJECdn", "RelativeFSRJECdn", "RelativeStatFSRJECdn", 
			  "RelativeStatECJECdn", 
			  "RelativeStatHFJECdn", "PileUpDataMCJECdn", "PileUpPtRefJECdn", "PileUpPtBBJECdn", "PileUpPtEC1JECdn", 
			  "PileUpPtEC2JECdn", "PileUpPtHFJECdn"};

  size_t nexpSysts=sizeof(systNames)/sizeof(TString);
  std::vector<TString> expSysts(systNames,systNames+nexpSysts);
  
  for(size_t is=0; is<nexpSysts; is++)
    {
      const char * name = expSysts[is];
      bdt_hists.push_back(new TH1F(Form("2b_BDT_output_%s",name),Form("2b_BDT_output_%s",name),30,-1,1));
    }

  TH1F *hist = new TH1F("2b_BDT_output","2b_BDT_output",30,-1,1);
  
 // TH1F *mm_hist = new TH1F("mm_2b_BDT_output","mm_2b_BDT_output",50,-0.9,0.9);
  // TH1F *em_hist = new TH1F("em_2b_BDT_output","em_2b_BDT_output",50,-0.9,0.9);

  for(int i = 0;i<tree->GetEntries();i++)
    {
      tree->GetEntry(i);
      wtree->GetEntry(i);

      hist->Fill(BDTout,weight);
      
    }

  for(size_t isyst=0; isyst<nexpSysts;isyst++)
    {
      for(int i = 0;i<tree->GetEntries();i++)
	{
	  tree->GetEntry(i);
	  wtree->GetEntry(i);

	  double systWeights[] = {syst_muUp, syst_muDn, syst_jerUp, syst_jerDn, syst_btaglfUp, syst_btaglfDn, syst_btaghfUp, syst_btaghfDn, syst_ees1Up, syst_ees1Dn, syst_mes1Up, syst_mes1Dn, syst_topptUp, syst_topptDn, syst_mselUp, syst_mselDn,syst_eselUp, syst_eselDn, syst_l1prefireUp,syst_l1prefireDn, syst_bfragUp, syst_bfragDn, syst_AbsoluteStatJECup,syst_AbsoluteScaleJECup, syst_AbsoluteMPFBiasJECup, syst_FragmentationJECup, syst_SinglePionECALJECup,
				  syst_SinglePionHCALJECup, syst_FlavorPureGluonJECup, syst_FlavorPureQuarkJECup, syst_FlavorPureCharmJECup, syst_FlavorPureBottomJECup, 
				  syst_TimePtEtaJECup, syst_RelativeJEREC1JECup, syst_RelativeJEREC2JECup, syst_RelativeJERHFJECup, syst_RelativePtBBJECup, syst_RelativePtEC1JECup, 
				  syst_RelativePtEC2JECup, syst_RelativePtHFJECup, syst_RelativeBalJECup, syst_RelativeFSRJECup, syst_RelativeStatFSRJECup, syst_RelativeStatECJECup, 
				  syst_RelativeStatHFJECup, syst_PileUpDataMCJECup, syst_PileUpPtRefJECup, syst_PileUpPtBBJECup, syst_PileUpPtEC1JECup, syst_PileUpPtEC2JECup, 
				  syst_PileUpPtHFJECup, syst_AbsoluteStatJECdn, syst_AbsoluteScaleJECdn, syst_AbsoluteMPFBiasJECdn, syst_FragmentationJECdn, syst_SinglePionECALJECdn, 
				  syst_SinglePionHCALJECdn, syst_FlavorPureGluonJECdn, syst_FlavorPureQuarkJECdn, syst_FlavorPureCharmJECdn, syst_FlavorPureBottomJECdn, 
				  syst_TimePtEtaJECdn, syst_RelativeJEREC1JECdn, syst_RelativeJEREC2JECdn, syst_RelativeJERHFJECdn, syst_RelativePtBBJECdn, syst_RelativePtEC1JECdn, 
				  syst_RelativePtEC2JECdn, syst_RelativePtHFJECdn, syst_RelativeBalJECdn, syst_RelativeFSRJECdn, syst_RelativeStatFSRJECdn, syst_RelativeStatECJECdn, 
				  syst_RelativeStatHFJECdn, syst_PileUpDataMCJECdn, syst_PileUpPtRefJECdn, syst_PileUpPtBBJECdn, syst_PileUpPtEC1JECdn, syst_PileUpPtEC2JECdn, 
				  syst_PileUpPtHFJECdn};

	  //Debug cout
	  //	  std::cout << "systematic var number " << isyst << " is " << systWeights[isyst] << std::endl;   



	  if(expSysts[isyst].Contains("toppt") || expSysts[isyst].Contains("mu"))
	    {
	      if(fileName.Contains("TT")) {
		bdt_hists[isyst]->Fill(BDTout,systWeights[isyst]);
		std::cout << "filling with " << systWeights[isyst] << endl;}
	      else
		bdt_hists[isyst]->Fill(BDTout,weight);
	    }

	  else
	    {
	      if(fileName.Contains("TT") || fileName.Contains("FPMC"))
		bdt_hists[isyst]->Fill(BDTout,systWeights[isyst]);
	      else
		bdt_hists[isyst]->Fill(BDTout,weight);
	    }
	  
	}
      //Else if(ch==143) em_hist->Fill(BDTout,weight);
      //else if(ch==169) mm_hist->Fill(BDTout,weight);
    }

  hist->GetXaxis()->SetTitle("BDT output");
  //mm_hist->GetXaxis()->SetTitle("BDT output");
  //em_hist->GetXaxis()->SetTitle("BDT output");

  hist->GetYaxis()->SetTitle("Events");
  //mm_hist->GetYaxis()->SetTitle("Events");
  //em_hist->GetYaxis()->SetTitle("Events");

  //toppt needs to be normalized
  /*  for(size_t is=0; is<nexpSysts; is++)
    {
      if(expSysts[is].Contains("toppt"))
	 { 
	   if(fileName.Contains("MC")) {
	     cout << "scaling by " << hist->Integral()/bdt_hists[is]->Integral();
	     bdt_hists[is]->Scale(hist->Integral()/bdt_hists[is]->Integral());
	   }
	 }
	 }*/

 //  hist->Draw();

  for(size_t isyst=0; isyst<nexpSysts;isyst++)
    {
      if(fileName.Contains("MC") && expSysts[isyst].Contains("toppt"))    bdt_hists[isyst]->Scale(hist->Integral()/bdt_hists[isyst]->Integral());
      //  bdt_hists[isyst]->SetLineColor(isyst);
      // bdt_hists[isyst]->Draw("same");
    }
 

  inputfile->cd();
  hist->Write(0,TObject::kOverwrite);

  for(size_t isyst=0; isyst<nexpSysts;isyst++)
    bdt_hists[isyst]->Write(0,TObject::kOverwrite);

  inputfile->Close();
  return 0;                                        
}


int ApplyMVA(TString filename)
{

  if(!exists_test(filename)) std::cout << "file does not exist. skipping" << std::endl;  

  else {
  std::cout << "Processing file" << filename << std::endl;  
  //define variable for regression
  //  TString var = "mass"; 
  
  TMVA::Tools::Instance();
  
  //TString filename = "eee";
 
  TString outfileName( filename );
  TFile* outputFile = TFile::Open( outfileName, "UPDATE" );


  TNtuple* OutTree= new TNtuple("BDT","BDT","run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:deltaphibb:b1m:b2pt:b2eta:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt:weight:BDToutput");

  //  signalOutTree->SetDirectory(outputFile);     
  OutTree->SetDirectory(outputFile);     

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );

  Float_t BDToutput;

  std::cout << "==> Start TMVA Reader" << std::endl;

  Float_t run,lumi,ev,rho,channel,mll,nljets,nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,reg_mtt,reg_ytt,weight, deltaphibb;

  // load the input trees
  TChain *bkgchain = new TChain("Reg");
  bkgchain->AddFile(filename);
  
  // Add the feature variables, names reference branches in inputFile ttree
  reader->AddSpectator("run",&run);
  reader->AddSpectator("lumi",&lumi);
  reader->AddSpectator("ev",&ev);
  reader->AddSpectator("rho",&rho);
  //  reader->AddSpectator("nvtx",&nvtx);
  //  reader->AddVariable("channel",&channel);

  //NEW SET OF VARIABLES                                                                                                                    
  reader->AddVariable("mpp",&mpp);
  reader->AddVariable("ypp",&ypp);
  reader->AddVariable("reg_mtt",&reg_mtt);
  reader->AddVariable("reg_ytt",&reg_ytt);
  reader->AddVariable("yvis",&yvis);
  reader->AddVariable("deltarll",&deltarll);
  reader->AddVariable("mll",&mll);
  reader->AddVariable("py2",&py2);
  reader->AddVariable("b2phi-b1phi",&deltaphibb);
  reader->AddVariable("ysum",&ysum);
  reader->AddVariable("metphi",&metphi);
  reader->AddVariable("min_dy",&min_dy);


  //maybe add this                                                                                                                           
  reader->AddVariable("mlb",&mlb);
  //  reader->AddVariable("b2eta",&b2eta);

  /*
  reader->AddVariable("mll",&mll);
  //reader->AddVariable("nljets",&nljets);
  //reader->AddVariable("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                                                                     
  reader->AddVariable("metpt",&metpt);

  reader->AddVariable("l1pt",&l1pt);
  reader->AddVariable("l1eta",&l1eta);
  reader->AddVariable("l1phi",&l1phi);
  reader->AddVariable("l1m",&l1m);
  reader->AddVariable("l2pt",&l2pt);
  reader->AddVariable("l2eta",&l2eta);
  reader->AddVariable("l2phi",&l2phi);
  reader->AddVariable("l2m",&l2m);
  reader->AddVariable("b1pt",&b1pt);
  reader->AddVariable("b1eta",&b1eta);
  reader->AddVariable("b1phi",&b1phi);
  reader->AddVariable("b1m",&b1m);
  reader->AddVariable("b2pt",&b2pt);
  reader->AddVariable("b2eta",&b2eta);
  reader->AddVariable("b2phi",&b2phi);
  reader->AddVariable("b2m",&b2m);
  reader->AddVariable("deltarll",&deltarll);
  reader->AddVariable("deltaphill",&deltaphill);
  reader->AddVariable("mlb",&mlb);
  reader->AddVariable("px2",&px2);
  reader->AddVariable("py2",&py2);
  reader->AddVariable("pz2",&pz2);
  reader->AddVariable("E2",&E2);
  reader->AddVariable("yvis",&yvis);
  reader->AddVariable("ysum",&ysum);
  reader->AddVariable("max_dy",&max_dy);
  reader->AddVariable("min_dy",&min_dy);

  reader->AddVariable("mpp",&mpp);
  reader->AddVariable("ypp",&ypp);
  //  reader->AddSpectator("gen_mtt",&gen_mtt);
  // reader->AddSpectator("gen_ytt",&gen_ytt);
  //reader->AddVariable("rec_mtt",&rec_mtt);
  //reader->AddVariable("rec_ytt",&rec_ytt);
  reader->AddVariable("reg_mtt",&reg_mtt);
  reader->AddVariable("reg_ytt",&reg_ytt);
  reader->AddSpectator("weight",&weight);
  */

  TString method =  "BDT method";
  reader->BookMVA( "BDT method", "dataset/weights/TMVAClassification_BDT.weights.xml" );

  //  Long64_t nSEvent = signalchain->GetEntries();
  Long64_t nBEvent = bkgchain->GetEntries();  
  
  bkgchain->SetBranchAddress("run",&run);
  bkgchain->SetBranchAddress("lumi",&lumi);
  bkgchain->SetBranchAddress("ev",&ev);  
  bkgchain->SetBranchAddress("rho",&rho);
  //  bkgchain->SetBranchAddress("nvtx",&nvtx);
  bkgchain->SetBranchAddress("channel",&channel);
  bkgchain->SetBranchAddress("mll",&mll);
  bkgchain->SetBranchAddress("nljets",&nljets);
  bkgchain->SetBranchAddress("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                           

  bkgchain->SetBranchAddress("metpt",&metpt);
  bkgchain->SetBranchAddress("metphi",&metphi);
  bkgchain->SetBranchAddress("l1pt",&l1pt);
  bkgchain->SetBranchAddress("l1eta",&l1eta);
  bkgchain->SetBranchAddress("l1phi",&l1phi);
  bkgchain->SetBranchAddress("l1m",&l1m);
  bkgchain->SetBranchAddress("l2pt",&l2pt);
  bkgchain->SetBranchAddress("l2eta",&l2eta);
  bkgchain->SetBranchAddress("l2phi",&l2phi);
  bkgchain->SetBranchAddress("l2m",&l2m);
  bkgchain->SetBranchAddress("b1pt",&b1pt);
  bkgchain->SetBranchAddress("b1eta",&b1eta);
  bkgchain->SetBranchAddress("b1phi",&b1phi);
  bkgchain->SetBranchAddress("b1m",&b1m);
  bkgchain->SetBranchAddress("b2pt",&b2pt);
  bkgchain->SetBranchAddress("b2eta",&b2eta);
  bkgchain->SetBranchAddress("b2phi",&b2phi);
  bkgchain->SetBranchAddress("b2m",&b2m);
  bkgchain->SetBranchAddress("deltarll",&deltarll);
  bkgchain->SetBranchAddress("deltaphill",&deltaphill);
  bkgchain->SetBranchAddress("mlb",&mlb);
  bkgchain->SetBranchAddress("px2",&px2);
  bkgchain->SetBranchAddress("py2",&py2);
  bkgchain->SetBranchAddress("pz2",&pz2);
  bkgchain->SetBranchAddress("E2",&E2);
  bkgchain->SetBranchAddress("yvis",&yvis);
  bkgchain->SetBranchAddress("ysum",&ysum);
  bkgchain->SetBranchAddress("max_dy",&max_dy);
  bkgchain->SetBranchAddress("min_dy",&min_dy);

  bkgchain->SetBranchAddress("mpp",&mpp);
  bkgchain->SetBranchAddress("ypp",&ypp);
  bkgchain->SetBranchAddress("gen_mtt",&gen_mtt);
  bkgchain->SetBranchAddress("gen_ytt",&gen_ytt);
  bkgchain->SetBranchAddress("rec_ytt",&rec_ytt);
  bkgchain->SetBranchAddress("rec_mtt",&rec_mtt);  
  bkgchain->SetBranchAddress("reg_ytt",&reg_ytt);
  bkgchain->SetBranchAddress("reg_mtt",&reg_mtt);  
  bkgchain->SetBranchAddress("weight",&weight);  

  for (Long64_t ievt=0; ievt<nBEvent; ievt++) {
    // if(mpp<9000 && ypp<9)
    // { 
	bkgchain->GetEntry(ievt);

	if(mpp<9000 && ypp<9)
	  {

	    if (ievt%10 == 0){
	      std::cout << "--- ... Processing event: " << ievt << std::endl;
	    }
	    // get the classifiers for each of the signal/background classifications
	    BDToutput = reader->EvaluateMVA(method);

	    float vars[47] = {run,lumi,ev,rho,channel,mll,nljets,
			      nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,
			      l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b2phi-b1phi,b1m,
			      b2pt,b2eta,b2m,px2,py2,pz2,E2,
			      yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,mpp,
			      ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,reg_mtt,
			      reg_ytt,weight,BDToutput};

	    OutTree->Fill(vars);
	  }
	//   }
  }
  
  outputFile->cd();                                                                                                                           outputFile->Write();
  outputFile->Close();
  
  BDThistograms(outfileName);

  }

  return 0;
}

