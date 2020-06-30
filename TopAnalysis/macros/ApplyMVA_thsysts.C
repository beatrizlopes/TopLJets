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
  

int ApplyMVA_thsysts(TString filename)
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

  if(outfileName.Contains("Data")) return 0;

  TFile* outputFile = TFile::Open( outfileName, "UPDATE" );

  //  signalOutTree->SetDirectory(outputFile);     

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );

  Float_t BDToutput;

  std::cout << "==> Start TMVA Reader" << std::endl;

  Float_t run,lumi,ev,rho,channel,mll,nljets,nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,reg_mtt,reg_ytt, deltaphibb,weight;

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
  TString systNames[]={"muRup","muRdn","muFup","muFdn","muRmuFup","muRmuFdn","PDF000","PDF001","PDF002","PDF003","PDF004","PDF005","PDF006","PDF007","PDF008","PDF009","PDF010","PDF011","PDF012","PDF013","PDF014","PDF015","PDF016","PDF017","PDF018","PDF019","PDF020","PDF021","PD022","PDF023","PDF024","PDF025","PDF026","PDF027","PDF028","PDF029","PDF030","PDF031","PDF032","PDF033","PDF034","PDF035","PDF036","PDF037","PDF038","PDF039","PDF040","PDF041","PDF042","PDF043","PDF044","PDF045","PDF046","PDF047","PDF048","PDF049","PDF050","PDF051","PDF052","PDF053","PDF054","PDF055","PDF056","PDF057","PDF058","PDF059","PDF060","PDF061","PDF062","PDF063","PDF064","PDF065","PDF066","PDF067","PDF068","PDF069","PDF070","PDF071","PDF072","PDF073","PDF074","PDF075","PDF076","PDF077","PDF078","PDF079","PDF080","PDF081","PDF082","PDF083","PDF084","PDF085","PDF086","PDF087","PDF088","PDF089","PDF090","PDF091","PDF092","PDF093","PDF094","PDF095","PDF096","PDF097","PDF098","PDF099","PDF100","PDF101","PDF102"};
  
  vector< TH1F* > bdt_hists;
  size_t nthSysts=sizeof(systNames)/sizeof(TString);
  
  for(size_t is=0; is<nthSysts; is++)
    {
      const char * s_name = systNames[is];
      bdt_hists.push_back(new TH1F(Form("2b_BDT_output_%s",s_name),Form("2b_BDT_output_%s",s_name),30,-1,1));
    }

  Float_t weight_s[nthSysts];

  TChain *bkgchain = new TChain("SEL_thsysts");

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

  for(size_t is=0; is<nthSysts; is++)
    {
      const char * s_name = systNames[is];
      bkgchain->SetBranchAddress(Form("w_%s",s_name),&weight_s[is]);  
    }

  Long64_t nEvent = bkgchain->GetEntries();  
	  
  for (Long64_t ievt=0; ievt<nEvent; ievt++) {
    // if(mpp<9000 && ypp<9)
    // { 
    bkgchain->GetEntry(ievt);
       
    if(mpp<9000 && ypp<9)
      {
	if (ievt%100000 == 0){
	  std::cout << "--- ... Processing event: " << ievt << std::endl;
	}
	// get the classifiers for each of the signal/background classifications
	BDToutput = reader->EvaluateMVA(method);
	for(size_t is=0; is<nthSysts; is++)
	  {
	    const char * s_name = systNames[is];
	    //  Long64_t nSEvent = signalchain->GetEntries();
	    bdt_hists[is]->Fill(BDToutput,weight_s[is]);
	  }
      }
	    //   }
  }

  outputFile->cd();                                                                                                                        

  for(size_t isyst=0; isyst<nthSysts;isyst++)
    {  
      bdt_hists[isyst]->GetXaxis()->SetTitle("BDT output");
      bdt_hists[isyst]->GetYaxis()->SetTitle("Events");
      bdt_hists[isyst]->Write(0,TObject::kOverwrite);
    }

  outputFile->Close();
  
  }
  return 0;
}

