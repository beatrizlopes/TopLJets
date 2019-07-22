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


bool fileExists(std::string fileName)
{
  std::ifstream infile(fileName);
  return infile.good();
}

int ApplyRegression(TString filename)
{
  if(fileExists)
    {
  std::cout << "Processing file" << filename << std::endl;  
  //define variable for regression
  //  TString var = "mass"; 

  TMVA::Tools::Instance();

  //TString filename = "eee";
 
  TString outfileName( filename );
  TFile* outputFile = TFile::Open( outfileName, "UPDATE" );
  
  //TNtuple* signalOutTree= new TNtuple("RegSignal","RegSignal","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt");
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
  
  /*  
  TChain *signalchain = new TChain("sel2");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120_0.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_130_0.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_140_0.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_150_0.root");
  */  


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
  

  //if(var=="mass") loader.AddTarget( "target := rec_mtt/gen_mtt" ); // define the target for the regression
  //if(var=="y") loader.AddTarget( "target := rec_ytt-gen_ytt" ); // define the target for the regression

  TString method =  "BDT method";
  reader->BookMVA( "BDT method", "dataset/weights/TMVARegression_BDTG_LS_mass.weights.xml" );
  reader1->BookMVA( "BDT method", "dataset/weights/TMVARegression_BDTG_LS_y.weights.xml" );

  //  Long64_t nSEvent = signalchain->GetEntries();
  Long64_t nBEvent = bkgchain->GetEntries();
  /*
  signalchain->SetBranchAddress("run",&run);
  signalchain->SetBranchAddress("lumi",&lumi);
  signalchain->SetBranchAddress("ev",&ev);  
  signalchain->SetBranchAddress("rho",&rho);
  signalchain->SetBranchAddress("nvtx",&nvtx);
  signalchain->SetBranchAddress("channel",&channel);
  signalchain->SetBranchAddress("mll",&mll);
  signalchain->SetBranchAddress("nljets",&nljets);
  signalchain->SetBranchAddress("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                                                                  
                                                                                                                                                                                    
  signalchain->SetBranchAddress("metpt",&metpt);
  signalchain->SetBranchAddress("metphi",&metphi);
  signalchain->SetBranchAddress("l1pt",&l1pt);
  signalchain->SetBranchAddress("l1eta",&l1eta);
  signalchain->SetBranchAddress("l1phi",&l1phi);
  signalchain->SetBranchAddress("l1m",&l1m);
  signalchain->SetBranchAddress("l2pt",&l2pt);
  signalchain->SetBranchAddress("l2eta",&l2eta);
  signalchain->SetBranchAddress("l2phi",&l2phi);
  signalchain->SetBranchAddress("l2m",&l2m);
  signalchain->SetBranchAddress("b1pt",&b1pt);
  signalchain->SetBranchAddress("b1eta",&b1eta);
  signalchain->SetBranchAddress("b1phi",&b1phi);
  signalchain->SetBranchAddress("b1m",&b1m);
  signalchain->SetBranchAddress("b2pt",&b2pt);
  signalchain->SetBranchAddress("b2eta",&b2eta);
  signalchain->SetBranchAddress("b2phi",&b2phi);
  signalchain->SetBranchAddress("b2m",&b2m);
  signalchain->SetBranchAddress("deltarll",&deltarll);
  signalchain->SetBranchAddress("deltaphill",&deltaphill);
  signalchain->SetBranchAddress("mlb",&mlb);
  signalchain->SetBranchAddress("px2",&px2);
  signalchain->SetBranchAddress("py2",&py2);
  signalchain->SetBranchAddress("pz2",&pz2);
  signalchain->SetBranchAddress("E2",&E2);
  signalchain->SetBranchAddress("yvis",&yvis);
  signalchain->SetBranchAddress("ysum",&ysum);
  signalchain->SetBranchAddress("max_dy",&max_dy);
  signalchain->SetBranchAddress("min_dy",&min_dy);

  signalchain->SetBranchAddress("mpp",&mpp);
  signalchain->SetBranchAddress("ypp",&ypp);
  signalchain->SetBranchAddress("gen_mtt",&gen_mtt);
  signalchain->SetBranchAddress("gen_ytt",&gen_ytt);
  signalchain->SetBranchAddress("rec_ytt",&rec_ytt);
  signalchain->SetBranchAddress("rec_mtt",&rec_mtt);
  */

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

  /*  for (Long64_t ievt=0; ievt<nSEvent; ievt++) {
    if (ievt%1000 == 0){
      std::cout << "--- ... Processing event: " << ievt << std::endl;
    }
    signalchain->GetEntry(ievt);
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

    signalOutTree->Fill(vars);
    }*/

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
    }

  else std::cout << "file does not exist" << std::endl;

  return 0;
}

int FileLoop()
{
  /*    
  for(int i=0;i<4;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_%d.root",120+10*i));

  for(int i=0;i<201;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_%d.root",i));

  for(int i=0;i<3;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_WW_%d.root",i));

  for(int i=0;i<2;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_WZ_%d.root",i));
 
    ApplyRegression("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_ZZ_0.root");

  for(int i=0;i<3;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_80to120_%d.root",i));

    ApplyRegression("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_30to50_0.root");

  for(int i=0;i<2;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_50to80_%d.root",i));

  for(int i=0;i<2;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_300toInf_%d.root",i));

  ApplyRegression("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_20to30_0.root");
  
  ApplyRegression("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_15to20_0.root");

  for(int i=0;i<4;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_QCDEM_120to170_%d.root",i));
  
  for(int i=0;i<2;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_GJets_HT600toInf_%d.root",i));

 for(int i=0;i<30;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_GJets_HT40to100_%d.root",i));

  for(int i=0;i<16;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_GJets_HT400to600_%d.root",i));
  
  
  for(int i=0;i<3;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_DY10to50_mlm_%d.root",i));

  for(int i=0;i<272;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_DY50toInf_fxfx_%d.root",i));
  
  
  
 for(int i=0;i<59;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_GJets_HT200to400_%d.root",i));
 
 for(int i=0;i<28;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_GJets_HT100to200_%d.root",i));

 ApplyRegression("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_201.root");


  char* c = "";
  for(int j=0;j<5;j++)
    {
      for(int i=0;i<12;i++)
	{
      	  if(j==0) c = "B";
	  if(j==1) c = "C";
	  if(j==2) c = "D";
	  if(j==3) c = "E";
	  if(j==4) c = "F";
	  ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017%s_MuonEG_%d.root",c,i));
	}    
    }

  for(int j=0;j<5;j++)
    {
      for(int i=0;i<16;i++)
        {
          if(j==0) c = "B";
          if(j==1) c = "C";
          if(j==2) c = "D";
          if(j==3) c = "E";
          if(j==4) c = "F";
          ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017%s_DoubleEG_%d.root",c,i));
        }
    }

  for(int j=0;j<5;j++)
    {
      for(int i=0;i<25;i++)
        {
          if(j==0) c = "B";
          if(j==1) c = "C";
          if(j==2) c = "D";
          if(j==3) c = "E";
          if(j==4) c = "F";
          ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017%s_DoubleMuon_%d.root",c,i));
        }
    }
*/
  /*
  char* c = "";
  for(int j=0;j<5;j++)
    {
      for(int i=50;i<85;i++)
        {
          if(j==0) c = "B";
          if(j==1) c = "C";
          if(j==2) c = "D";
          if(j==3) c = "E";
          if(j==4) c = "F";
          ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017%s_SingleElectron_%d.root",c,i));
        }
    }

  for(int j=0;j<5;j++)
    {
      for(int i=0;i<151;i++)
        {
          if(j==0) c = "B";
          if(j==1) c = "C";
          if(j==2) c = "D";
          if(j==3) c = "E";
          if(j==4) c = "F";
          ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017%s_SingleMuon_%d.root",c,i));
        }
    }

  for(int j=0;j<5;j++)
    {
      for(int i=0;i<14;i++)
        {
          if(j==0) c = "B";
          if(j==1) c = "C";
          if(j==2) c = "D";
          if(j==3) c = "E";
          if(j==4) c = "F";
          ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data13TeV_2017%s_SinglePhoton_%d.root",c,i));
        }
    }
  */
  for(int i=2;i<6;i++)
    ApplyRegression(Form("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_1%d0_0.root",i));

  return 0;
}
