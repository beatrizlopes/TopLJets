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
  reader->BookMVA( "BDT method", "dataset/weights/TMVAClassification_BDT.weights.xml" );

  //add string of systnames
  TString systNames[] = { "puup",        "pudn",
			  "eetrigup",    "eetrigdn",
			  "emtrigup",    "emtrigdn",
			  "mmtrigup",    "mmtrigdn",
			  "eselup",      "eseldn",
			  "mselup",      "mseldn",
			  "l1prefireup", "l1prefiredn",
			  "ees1up", "ees1dn", "ees2up", "ees2dn", "ees3up", "ees3dn", "ees4up", "ees4dn",  "ees5up", "ees5dn",  "ees6up", "e\
es6dn",  "ees7up", "ees7dn",
			  "mes1up", "mes1dn", "mes2up", "mes2dn", "mes3up", "mes3dn", "mes4up", "mes4dn",
			  //"btagjesup",        "btagjesdn",                                                                                 
			  "btaglfup",         "btaglfdn",
			  "btaghfup",         "btaghfdn",
    //"btaghfstats1up",   "btaghfstats1dn",                                                                            
    //"btaghfstats2up",   "btaghfstats2dn",                                                                            
    //"btaglfstats1up",   "btaglfstats1dn",                                                                            
    //"btaglfstats2up",   "btaglfstats2dn",                                                                            
    //"btagcferr1up",     "btagcferr1dn",                                                                              
    //"btagcferr2up",     "btagcferr2dn",                                                                              
			  "JERup",       "JERdn",
			  //			  "JERstatup",   "JERstatdn",
			  //			  "JERJECup",    "JERJECdn",
			  //			  "JERPUup",     "JERPUdn",
			  //			  "JERPLIup",    "JERPLIdn",
			  //			  "JERptCutup",  "JERptCutdn",
			  //			  "JERtruncup",  "JERtruncdn",
			  //			  "JERpTdepup",  "JERpTdepdn",
			  //			  "JERSTmFEup",  "JERSTmFEdn",
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

  TTree *sel = (TTree*)outputFile->Get("sel");

  TChain *bkgchain = new TChain("Reg");
  bkgchain->AddFile(filename);
  Long64_t nBEvent = bkgchain->GetEntries();  

  bkgchain->SetBranchAddress("run",&run);
  bkgchain->SetBranchAddress("lumi",&lumi);
  bkgchain->SetBranchAddress("ev",&ev);  
  bkgchain->SetBranchAddress("rho",&rho);
  //  bkgchain->SetBranchAddress("nvtx",&nvtx);
  sel->SetBranchAddress("channel",&channel);
  sel->SetBranchAddress("mll",&mll);
  sel->SetBranchAddress("nljets",&nljets);
  sel->SetBranchAddress("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                           
  sel->SetBranchAddress("metpt",&metpt);
  sel->SetBranchAddress("metphi",&metphi);
  sel->SetBranchAddress("l1pt",&l1pt);
  sel->SetBranchAddress("l1eta",&l1eta);
  sel->SetBranchAddress("l1phi",&l1phi);
  sel->SetBranchAddress("l1m",&l1m);
  sel->SetBranchAddress("l2pt",&l2pt);
  sel->SetBranchAddress("l2eta",&l2eta);
  sel->SetBranchAddress("l2phi",&l2phi);
  sel->SetBranchAddress("l2m",&l2m);
  sel->SetBranchAddress("b1pt",&b1pt);
  sel->SetBranchAddress("b1eta",&b1eta);
  sel->SetBranchAddress("b1phi",&b1phi);
  sel->SetBranchAddress("b1m",&b1m);
  sel->SetBranchAddress("b2pt",&b2pt);
  sel->SetBranchAddress("b2eta",&b2eta);
  sel->SetBranchAddress("b2phi",&b2phi);
  sel->SetBranchAddress("b2m",&b2m);
  sel->SetBranchAddress("deltarll",&deltarll);
  sel->SetBranchAddress("deltaphill",&deltaphill);
  sel->SetBranchAddress("mlb",&mlb);
  sel->SetBranchAddress("px2",&px2);
  sel->SetBranchAddress("py2",&py2);
  sel->SetBranchAddress("pz2",&pz2);
  sel->SetBranchAddress("E2",&E2);
  sel->SetBranchAddress("yvis",&yvis);
  sel->SetBranchAddress("ysum",&ysum);
  sel->SetBranchAddress("max_dy",&max_dy);
  sel->SetBranchAddress("min_dy",&min_dy);
  
  bkgchain->SetBranchAddress("mpp",&mpp);
  bkgchain->SetBranchAddress("ypp",&ypp);
  bkgchain->SetBranchAddress("gen_mtt",&gen_mtt);
  bkgchain->SetBranchAddress("gen_ytt",&gen_ytt);
  bkgchain->SetBranchAddress("rec_ytt",&rec_ytt);
  bkgchain->SetBranchAddress("rec_mtt",&rec_mtt);  
  bkgchain->SetBranchAddress("reg_ytt",&reg_ytt);
  bkgchain->SetBranchAddress("reg_mtt",&reg_mtt);  
  sel->SetBranchAddress("weight",&weight);  
  
  for (Long64_t ievt=0; ievt<nBEvent; ievt++) {
	// if(mpp<9000 && ypp<9)
    // { 
    bkgchain->GetEntry(ievt);
    sel->GetEntry(ievt);

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

	  TTree *sel_syst = (TTree*)outputFile->Get(Form("sel_%s",s_name));
	  
	  //  Long64_t nSEvent = signalchain->GetEntries();
  
	  bkgchain->SetBranchAddress("run",&run);
	  bkgchain->SetBranchAddress("lumi",&lumi);
	  bkgchain->SetBranchAddress("ev",&ev);  
	  bkgchain->SetBranchAddress("rho",&rho);
	  //  bkgchain->SetBranchAddress("nvtx",&nvtx);
	  bkgchain->SetBranchAddress("channel",&channel);
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
	  
	  bkgchain->SetBranchAddress("mpp",&mpp);
	  bkgchain->SetBranchAddress("ypp",&ypp);
	  bkgchain->SetBranchAddress("gen_mtt",&gen_mtt);
	  bkgchain->SetBranchAddress("gen_ytt",&gen_ytt);
	  bkgchain->SetBranchAddress("rec_ytt",&rec_ytt);
	  bkgchain->SetBranchAddress("rec_mtt",&rec_mtt);  
	  bkgchain->SetBranchAddress("reg_ytt",&reg_ytt);
	  bkgchain->SetBranchAddress("reg_mtt",&reg_mtt);  
	  sel_syst->SetBranchAddress("syst_weight",&weight);  
	  
	  for (Long64_t ievt=0; ievt<nBEvent; ievt++) {
	    // if(mpp<9000 && ypp<9)
	    // { 
	    bkgchain->GetEntry(ievt);
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
      
      outputFile->cd();                                                                                                                        
      for(size_t isyst=0; isyst<nexpSysts;isyst++)
	bdt_hists[isyst]->Write(0,TObject::kOverwrite);

    }

  outputFile->cd();                                                                                                                        
  hist->Write(0,TObject::kOverwrite);
  
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

