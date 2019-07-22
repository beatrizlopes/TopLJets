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

int trainBDT()
{
  //  std::string signalFileName = "/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/signal.root";
  //std::string backgroundFileName = "/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/bkg.root";

  TMVA::Tools::Instance();


  TChain *bkgchain = new TChain("Reg");
  bkgchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/MC13TeV_2017_TTJets.root");
  /*  bkgchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_6.root");
  bkgchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_7.root");
  bkgchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_8.root");
  bkgchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_9.root");
  */
  TChain *signalchain = new TChain("Reg");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_130.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_140.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_150.root");

  //  TFile* inputfile = TFile::Open( "tmva_applied.root" );
  //  TTree* signaltree = (TTree*) inputfile->Get("RegSignal");
  // TTree* bkgtree = (TTree*) inputfile->Get("RegBkg");

  std::cout << "==> Start TMVAClassification" << std::endl;
  //std::cout << "\tProcessing files:" << std::endl;
  //std::cout << "\t  - Signal: " << signalFileName << std::endl;
  //std::cout << "\t  - Background: " << backgroundFileName << std::endl;

  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TString outfileName( "TMVA_classification.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

  TMVA::DataLoader *dataloader = new TMVA::DataLoader("TMVAClassification");

  TMVA::DataLoader loader("dataset");

  // Add the feature variables, names reference branches in inputFile ttree                                                                                                          
  loader.AddSpectator("run");  
  loader.AddSpectator("lumi");                                                                                                             
  loader.AddSpectator("ev");
  loader.AddSpectator("rho");
  loader.AddSpectator("nvtx");
  loader.AddVariable("channel");
  loader.AddVariable("mll");
    
  loader.AddVariable("nljets");
  

  loader.AddVariable("nbjets");
  //  loader.AddVariable("ht");                                                                                                                                                    
  loader.AddVariable("metpt");
  loader.AddVariable("metphi");
  loader.AddVariable("l1pt");
  loader.AddVariable("l1eta");
  loader.AddVariable("l1phi");
  loader.AddVariable("l1m");
  loader.AddVariable("l2pt");
  loader.AddVariable("l2eta");
  loader.AddVariable("l2phi");
  loader.AddVariable("l2m");
  loader.AddVariable("b1pt");
  loader.AddVariable("b1eta");
  loader.AddVariable("b1phi");
  loader.AddVariable("b1m");
  loader.AddVariable("b2pt");
  loader.AddVariable("b2eta");
  loader.AddVariable("b2phi");
  loader.AddVariable("b2m");
  
loader.AddVariable("deltarll");
  loader.AddVariable("deltaphill");
    
loader.AddVariable("mlb");
  loader.AddVariable("px2");
  loader.AddVariable("py2");
  loader.AddVariable("pz2");
  loader.AddVariable("E2");
  loader.AddVariable("yvis");
  loader.AddVariable("ysum");
  loader.AddVariable("max_dy");
  loader.AddVariable("min_dy");
 
  
  loader.AddVariable("mpp");                                                                                                                                                     
  loader.AddVariable("ypp");                                                                                                                                                       
  //loader.AddVariable("gen_mtt");                                                                                                                                                
  //loader.AddVariable("gen_ytt");                                                                                                                                                 
  loader.AddVariable("rec_mtt");
  loader.AddVariable("rec_ytt");
  loader.AddVariable("reg_mtt");
  loader.AddVariable("reg_ytt");
  
  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 1.0;

  loader.AddSignalTree    ( signalchain,     signalWeight     );
  loader.AddBackgroundTree( bkgchain, backgroundWeight );
  loader.SetBackgroundWeightExpression("832");
  loader.SetSignalWeightExpression("0.00001");

  // Preselection
  //TCut mycuts = "abs(ht) > 100";
  TCut mycutb = "mpp > 2 && ypp>-1";

  loader.PrepareTrainingAndTestTree( "", "", "nTrain_Signal=700:nTrain_Background=5000:nTest_Signal=700:nTest_Background=5000:SplitMode=Random:NormMode=EqualNumEvents" );
  
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification" );

  factory->BookMethod(&loader, TMVA::Types::kBDT, "BDT",
		      "!H:!V:NTrees=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );

  //  factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP_ANN",
  // "" );

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  //  delete factory;
  // delete &loader;

  return 0;
}


/*void printHelp()
{
  std::cout << "The program has the following parameters:" << std::endl;
  std::cout << "\t--help\t- Print this message" << std::endl;

  return;
  }*/

bool fileExists(std::string fileName)
{
  std::ifstream infile(fileName);
  return infile.good();
}
