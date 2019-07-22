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

void printHelp();
bool fileExists(std::string);

int ApplyRegression(TString filename)
{
  
  //define variable for regression
  //  TString var = "mass"; 

  TMVA::Tools::Instance();

  //TString filename = "eee";

  // Create a new root output file.
  TString outfileName(filename);
  TFile* outputFile = TFile::Open( outfileName, "UPDATE" );
  
  TNtuple* OutTree= new TNtuple("Reg","Reg","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt");

  outputFile->cd();                                                                                                                                                                 
  //  signalOutTree->SetDirectory(outputFile);     
  OutTree->SetDirectory(outputFile);     

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );

  Float_t classifier_m, classifier_y, reg_mtt, reg_ytt;

  std::cout << "==> Start TMVA Reader" << std::endl;

  Float_t run,lumi,ev,nvtx,rho,channel,mll,nljets,nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,correction;

  // load the input trees
  TChain *bkgchain = new TChain("sel2");
  bkgchain->AddFile(filename);
  
  // Add the feature variables, names reference branches in inputFile ttree
  reader->AddSpectator("run",&run);
  reader->AddSpectator("lumi",&lumi);
  reader->AddSpectator("ev",&ev);
  reader->AddSpectator("rho",&rho);
  reader->AddSpectator("nvtx",&nvtx);
  reader->AddSpectator("channel",&channel);
  reader->AddVariable("mll",&mll);
  reader->AddVariable("nljets",&nljets);
  reader->AddVariable("nbjets",&nbjets);
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

  reader->AddSpectator("mpp",&mpp);
  reader->AddSpectator("ypp",&ypp);
  reader->AddSpectator("gen_mtt",&gen_mtt);
  reader->AddSpectator("gen_ytt",&gen_ytt);
  reader->AddVariable("rec_ytt",&rec_ytt);
  reader->AddVariable("rec_mtt",&rec_mtt);
  
  reader1->AddSpectator("run",&run);
  reader1->AddSpectator("lumi",&lumi);
  reader1->AddSpectator("ev",&ev);
  reader1->AddSpectator("rho",&rho);
  reader1->AddSpectator("nvtx",&nvtx);
  reader1->AddSpectator("channel",&channel);
  reader1->AddVariable("mll",&mll);
  reader1->AddVariable("nljets",&nljets);
  reader1->AddVariable("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                                                                  
  reader1->AddVariable("metpt",&metpt);
  reader1->AddVariable("metphi",&metphi);
  reader1->AddVariable("l1pt",&l1pt);
  reader1->AddVariable("l1eta",&l1eta);
  reader1->AddVariable("l1phi",&l1phi);
  reader1->AddVariable("l1m",&l1m);
  reader1->AddVariable("l2pt",&l2pt);
  reader1->AddVariable("l2eta",&l2eta);
  reader1->AddVariable("l2phi",&l2phi);
  reader1->AddVariable("l2m",&l2m);
  reader1->AddVariable("b1pt",&b1pt);
  reader1->AddVariable("b1eta",&b1eta);
  reader1->AddVariable("b1phi",&b1phi);
  reader1->AddVariable("b1m",&b1m);
  reader1->AddVariable("b2pt",&b2pt);
  reader1->AddVariable("b2eta",&b2eta);
  reader1->AddVariable("b2phi",&b2phi);
  reader1->AddVariable("b2m",&b2m);
  reader1->AddVariable("deltarll",&deltarll);
  reader1->AddVariable("deltaphill",&deltaphill);
  reader1->AddVariable("mlb",&mlb);
  reader1->AddVariable("px2",&px2);
  reader1->AddVariable("py2",&py2);
  reader1->AddVariable("pz2",&pz2);
  reader1->AddVariable("E2",&E2);
  reader1->AddVariable("yvis",&yvis);
  reader1->AddVariable("ysum",&ysum);
  reader1->AddVariable("max_dy",&max_dy);
  reader1->AddVariable("min_dy",&min_dy);

  reader1->AddSpectator("mpp",&mpp);
  reader1->AddSpectator("ypp",&ypp);
  reader1->AddSpectator("gen_mtt",&gen_mtt);
  reader1->AddSpectator("gen_ytt",&gen_ytt);
  reader1->AddVariable("rec_ytt",&rec_ytt);
  reader1->AddVariable("rec_mtt",&rec_mtt);
  
  TString method =  "BDT method";
  reader->BookMVA( "BDT method", "dataset/weights/TMVARegression_BDTG_LS_mass.weights.xml" );
  reader1->BookMVA( "BDT method", "dataset/weights/TMVARegression_BDTG_LS_y.weights.xml" );

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

  for (Long64_t ievt=0; ievt<nBEvent; ievt++) {
    if (ievt%10 == 0){
      std::cout << "--- ... Processing event: " << ievt << std::endl;
    }

    bkgchain->GetEntry(ievt);
    // get the classifiers for each of the signal/background classifications
    classifier_m = reader->EvaluateRegression(0, method );
    classifier_y = reader1->EvaluateRegression(0, method );

    reg_mtt=rec_mtt/classifier_m;
    reg_ytt=rec_ytt-classifier_y;

    float vars[47] = {run,lumi,ev,rho,nvtx,channel,mll,nljets,
		      nbjets,ht,
		      metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,
		      l2phi,l2m,
		      b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,
		      px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,
		      deltarll,deltaphill,mlb,mpp,ypp,gen_mtt,gen_ytt,
		      rec_mtt,rec_ytt,reg_mtt,reg_ytt};

    OutTree->Fill(vars);
    }

  outputFile->Write();
  outputFile->Close();

  return 0;
}
