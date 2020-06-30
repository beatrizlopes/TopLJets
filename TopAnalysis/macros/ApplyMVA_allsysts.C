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
  

int ApplyMVA_allsysts(TString filename)
{

  //  if(filename.Contains("TT")) std::cout << "file is ttbar. skipping" << std::endl;
  if(!exists_test(filename)) std::cout << "file does not exist. skipping" << std::endl;

  else {
    std::cout << "Processing file" << filename << std::endl;  
    //define variable for regression
    //  TString var = "mass"; 
  
    TMVA::Tools::Instance();
  
  //TString filename = "eee";
 
  TString outfileName( filename );
  TFile* outputFile = TFile::Open( outfileName, "UPDATE" );

  //  signalOutTree->SetDirectory(outputFile);     

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );

  Float_t BDToutput;

  std::cout << "==> Start TMVA Reader" << std::endl;

  Float_t run,lumi,ev,rho,channel,mll,nljets,nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,reg_mtt,reg_ytt,weight, deltaphibb;

  // load the input trees

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
  //  reader->AddVariable("py2",&py2);
  reader->AddVariable("b2phi-b1phi",&deltaphibb);
  reader->AddVariable("ysum",&ysum);
  reader->AddVariable("metphi",&metphi);
  reader->AddVariable("min_dy",&min_dy);
  //maybe add this                                                                                                                          
  //  reader->AddVariable("mlb",&mlb);
  reader->AddVariable("nljets",&nljets);
  reader->AddVariable("metpt",&metpt);
  //reader->AddVariable("px2",&px2);
  //reader->AddVariable("pz2",&pz2);
  reader->AddVariable("E2",&E2);

  
  TString method =  "BDT method";
  reader->BookMVA( "BDT method", "/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/dataset/weights/TMVAClassification_BDT.weights.xml" );

  //add string of systnames
  TString systNames[] = { "puup",        "pudn",
			  "eetrigup",    "eetrigdn",
			  "emtrigup",    "emtrigdn",
			  "mmtrigup",    "mmtrigdn",
			  "eselup",      "eseldn",
			  "mselup",      "mseldn",
			  "l1prefireup", "l1prefiredn",
			  //"ees1up", "ees1dn", "ees2up", "ees2dn", 
			  "ees3up", "ees3dn", "ees4up", "ees4dn",  
			  //"ees5up", "ees5dn",
			  "ees6up", "ees6dn", 
			  "ees7up", "ees7dn",
			  "mes1up", "mes1dn", "mes2up", "mes2dn", "mes3up", "mes3dn", "mes4up", "mes4dn",
			  "btaglfup",         "btaglfdn",
			  "btaghfup",         "btaghfdn",
			  "JERup",       "JERdn",
			  "topptup",     "topptdn",
			  "AbsoluteStatJECup","AbsoluteScaleJECup","AbsoluteMPFBiasJECup","FragmentationJECup","SinglePionECALJECup",
			  "SinglePionHCALJECup","FlavorPureGluonJECup","FlavorPureQuarkJECup","FlavorPureCharmJECup",
			  "FlavorPureBottomJECup","TimePtEtaJECup","RelativeJEREC1JECup","RelativeJEREC2JECup","RelativeJERHFJECup",
			  "RelativePtBBJECup","RelativePtEC1JECup","RelativePtEC2JECup","RelativePtHFJECup","RelativeBalJECup",
			  "RelativeFSRJECup","RelativeStatFSRJECup","RelativeStatECJECup","RelativeStatHFJECup","PileUpDataMCJECup",
			  "PileUpPtRefJECup","PileUpPtBBJECup","PileUpPtEC1JECup","PileUpPtEC2JECup","PileUpPtHFJECup",
			  "AbsoluteStatJECdn","AbsoluteScaleJECdn","AbsoluteMPFBiasJECdn","FragmentationJECdn","SinglePionECALJECdn",
			  "SinglePionHCALJECdn","FlavorPureGluonJECdn","FlavorPureQuarkJECdn","FlavorPureCharmJECdn",
			  "FlavorPureBottomJECdn","TimePtEtaJECdn","RelativeJEREC1JECdn","RelativeJEREC2JECdn","RelativeJERHFJECdn",
			  "RelativePtBBJECdn","RelativePtEC1JECdn","RelativePtEC2JECdn","RelativePtHFJECdn","RelativeBalJECdn",
			  "RelativeFSRJECdn","RelativeStatFSRJECdn","RelativeStatECJECdn","RelativeStatHFJECdn","PileUpDataMCJECdn",
			  "PileUpPtRefJECdn","PileUpPtBBJECdn","PileUpPtEC1JECdn","PileUpPtEC2JECdn","PileUpPtHFJECdn",
			  "bfragup", "bfragdn"};
  

  vector< TH1F* > bdt_hists;
  size_t nexpSysts=sizeof(systNames)/sizeof(TString);
  
  for(size_t is=0; is<nexpSysts; is++)
    {
      const char * s_name = systNames[is];
      bdt_hists.push_back(new TH1F(Form("2b_BDT_output_%s",s_name),Form("2b_BDT_output_%s",s_name),30,-1,1));
    }

  TH1F *hist = new TH1F("2b_BDT_output","2b_BDT_output",30,-1,1);

  TChain *bkgchain = new TChain("SEL");
  bkgchain->AddFile(filename);
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

	if (ievt%1000 == 0){
	  std::cout << "--- ... Processing event: " << ievt << std::endl;
	}
	// get the classifiers for each of the signal/background classifications
	BDToutput = reader->EvaluateMVA(method);
	hist->Fill(BDToutput,weight);
	
      }
  }
  
  if(filename.Contains("MC"))
    {
      for(size_t is=0; is<nexpSysts; is++)
	{
	  const char * s_name = systNames[is];

	  if(systNames[is].Contains("toppt") && !filename.Contains("TT")) continue;

	  if(!outputFile->GetListOfKeys()->Contains(Form("SEL_%s",s_name))) continue;
	  
	  TTree *sel_syst = (TTree*)outputFile->Get(Form("SEL_%s",s_name));

	  //  Long64_t nSEvent = signalchain->GetEntries();
	  std::cout << "starting syst " << s_name << std::endl;
  
	  sel_syst->SetBranchAddress("run",&run);
	  sel_syst->SetBranchAddress("lumi",&lumi);
	  sel_syst->SetBranchAddress("ev",&ev);  
	  sel_syst->SetBranchAddress("rho",&rho);
	  //  sel_syst->SetBranchAddress("nvtx",&nvtx);
	  sel_syst->SetBranchAddress("channel",&channel);
	  sel_syst->SetBranchAddress("mll",&mll);
	  sel_syst->SetBranchAddress("nljets",&nljets);
	  sel_syst->SetBranchAddress("nbjets",&nbjets);
	  //  loader->AddSpectator("ht");                                                                                                           
	  sel_syst->SetBranchAddress("metpt",&metpt);
	  sel_syst->SetBranchAddress("metphi",&metphi);
	  sel_syst->SetBranchAddress("l1pt",&l1pt);
	  sel_syst->SetBranchAddress("l1eta",&l1eta);
	  sel_syst->SetBranchAddress("l1phi",&l1phi);
	  sel_syst->SetBranchAddress("l1m",&l1m);
	  sel_syst->SetBranchAddress("l2pt",&l2pt);
	  sel_syst->SetBranchAddress("l2eta",&l2eta);
	  sel_syst->SetBranchAddress("l2phi",&l2phi);
	  sel_syst->SetBranchAddress("l2m",&l2m);
	  sel_syst->SetBranchAddress("b1pt",&b1pt);
	  sel_syst->SetBranchAddress("b1eta",&b1eta);
	  sel_syst->SetBranchAddress("b1phi",&b1phi);
	  sel_syst->SetBranchAddress("b1m",&b1m);
	  sel_syst->SetBranchAddress("b2pt",&b2pt);
	  sel_syst->SetBranchAddress("b2eta",&b2eta);
	  sel_syst->SetBranchAddress("b2phi",&b2phi);
	  sel_syst->SetBranchAddress("b2m",&b2m);
	  sel_syst->SetBranchAddress("deltarll",&deltarll);
	  sel_syst->SetBranchAddress("deltaphill",&deltaphill);
	  sel_syst->SetBranchAddress("mlb",&mlb);
	  sel_syst->SetBranchAddress("px2",&px2);
	  sel_syst->SetBranchAddress("py2",&py2);
	  sel_syst->SetBranchAddress("pz2",&pz2);
	  sel_syst->SetBranchAddress("E2",&E2);
	  sel_syst->SetBranchAddress("yvis",&yvis);
	  sel_syst->SetBranchAddress("ysum",&ysum);
	  sel_syst->SetBranchAddress("max_dy",&max_dy);
	  sel_syst->SetBranchAddress("min_dy",&min_dy);
	  
	  sel_syst->SetBranchAddress("mpp",&mpp);
	  sel_syst->SetBranchAddress("ypp",&ypp);
	  sel_syst->SetBranchAddress("gen_mtt",&gen_mtt);
	  sel_syst->SetBranchAddress("gen_ytt",&gen_ytt);
	  sel_syst->SetBranchAddress("rec_ytt",&rec_ytt);
	  sel_syst->SetBranchAddress("rec_mtt",&rec_mtt);  
	  sel_syst->SetBranchAddress("reg_ytt",&reg_ytt);
	  sel_syst->SetBranchAddress("reg_mtt",&reg_mtt);  
	  sel_syst->SetBranchAddress("weight",&weight);  

	  Long64_t nEvent = sel_syst->GetEntries();  
	  
	  for (Long64_t ievt=0; ievt<nEvent; ievt++) {
	    // if(mpp<9000 && ypp<9)
	    // { 
	    sel_syst->GetEntry(ievt);
	    
	    if(mpp<9000 && ypp<9)
	      {
		if (ievt%100000 == 0){
		  std::cout << "--- ... Processing event: " << ievt << std::endl;
		}
	    // get the classifiers for each of the signal/background classifications
		BDToutput = reader->EvaluateMVA(method);
		bdt_hists[is]->Fill(BDToutput,weight);
		bdt_hists[is]->GetXaxis()->SetTitle("BDT output");
		bdt_hists[is]->GetYaxis()->SetTitle("Events");
	      }
	    //   }
	  }
	}
      
    }

  outputFile->cd();                                                                                                                        
  hist->Write(0,TObject::kOverwrite);

  for(size_t isyst=0; isyst<nexpSysts;isyst++)
    bdt_hists[isyst]->Write(0,TObject::kOverwrite);
  
  outputFile->Close();
  
  }

  return 0;
}

  /*
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


  //mm_hist->GetYaxis()->SetTitle("Events");
  //em_hist->GetYaxis()->SetTitle("Events");

  //toppt needs to be normalized
   for(size_t is=0; is<nexpSysts; is++)
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

