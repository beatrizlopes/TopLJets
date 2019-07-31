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
 
  float ch = 0, BDTout = 0, weight = 1;
  TString channel = "";
  tree->SetBranchAddress("channel",&ch);
  tree->SetBranchAddress("BDToutput",&BDTout);
  tree->SetBranchAddress("weight",&weight);

  TH1F *ee_hist = new TH1F("ee_2b_BDT_output","ee_2b_BDT_output",50,-0.5,0.5);
  TH1F *mm_hist = new TH1F("mm_2b_BDT_output","mm_2b_BDT_output",50,-0.5,0.5);
  TH1F *em_hist = new TH1F("em_2b_BDT_output","em_2b_BDT_output",50,-0.5,0.5);

  for(int i = 0;i<tree->GetEntries();i++)
    {
      tree->GetEntry(i);
      if(ch==121) ee_hist->Fill(BDTout,weight);
      else if(ch==143) em_hist->Fill(BDTout,weight);
      else if(ch==169) mm_hist->Fill(BDTout,weight);
    }

  ee_hist->GetXaxis()->SetTitle("BDT output");
  mm_hist->GetXaxis()->SetTitle("BDT output");
  em_hist->GetXaxis()->SetTitle("BDT output");

  ee_hist->GetYaxis()->SetTitle("Events");
  mm_hist->GetYaxis()->SetTitle("Events");
  em_hist->GetYaxis()->SetTitle("Events");

  inputfile->cd();
  ee_hist->Write(0,TObject::kOverwrite);
  em_hist->Write(0,TObject::kOverwrite);
  mm_hist->Write(0,TObject::kOverwrite);

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
  
  TNtuple* OutTree= new TNtuple("BDT","BDT","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt:weight:BDToutput");

  //  signalOutTree->SetDirectory(outputFile);     
  OutTree->SetDirectory(outputFile);     

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );

  Float_t BDToutput;

  std::cout << "==> Start TMVA Reader" << std::endl;

  Float_t run,lumi,ev,nvtx,rho,channel,mll,nljets,nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,reg_mtt,reg_ytt,weight;

  // load the input trees
  TChain *bkgchain = new TChain("Reg");
  bkgchain->AddFile(filename);
  
  // Add the feature variables, names reference branches in inputFile ttree
  reader->AddSpectator("run",&run);
  reader->AddSpectator("lumi",&lumi);
  reader->AddSpectator("ev",&ev);
  reader->AddSpectator("rho",&rho);
  reader->AddSpectator("nvtx",&nvtx);
  //  reader->AddVariable("channel",&channel);
  reader->AddVariable("mll",&mll);
  //reader->AddVariable("nljets",&nljets);
  //reader->AddVariable("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                                                                     
  reader->AddVariable("metpt",&metpt);
  reader->AddVariable("metphi",&metphi);
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
  

  TString method =  "BDT method";
  reader->BookMVA( "BDT method", "dataset/weights/TMVAClassification_BDT.weights.xml" );

  //  Long64_t nSEvent = signalchain->GetEntries();
  Long64_t nBEvent = bkgchain->GetEntries();  
  
  bkgchain->SetBranchAddress("run",&run);
  bkgchain->SetBranchAddress("lumi",&lumi);
  bkgchain->SetBranchAddress("ev",&ev);  
  bkgchain->SetBranchAddress("rho",&rho);
  bkgchain->SetBranchAddress("nvtx",&nvtx);
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
    if (ievt%10 == 0){
      std::cout << "--- ... Processing event: " << ievt << std::endl;
    }

    // if(mpp<9000 && ypp<9)
    // { 
	bkgchain->GetEntry(ievt);
	// get the classifiers for each of the signal/background classifications
	BDToutput = reader->EvaluateMVA(method);

	float vars[49] = {run,lumi,ev,rho,nvtx,channel,mll,nljets,
			  nbjets,ht,
			  metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,
			  l2phi,l2m,
			  b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,
			  px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,
			  deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,
			  rec_mtt,rec_ytt,reg_mtt,reg_ytt,weight,BDToutput};

	OutTree->Fill(vars);
	//   }
  }
  
  outputFile->cd();                                                                                                                           outputFile->Write();
  outputFile->Close();
  
  BDThistograms(outfileName);

  }

  return 0;
}

