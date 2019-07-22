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

int CrossValidation()
{

  //define variable for regression
  TString var = "mass"; 

  TMVA::Tools::Instance();

  //auto inputFile = TFile::Open("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/signal.root");

  auto outputFile = TFile::Open("TMVA_ValidationOutput.root", "RECREATE");

  TMVA::Factory factory("TMVARegression", outputFile,
			"!V:!Silent:Color:!DrawProgressBar:AnalysisType=Regression" );

  std::cout << "==> Start TMVARegression-CrossValidation" << std::endl;

  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TMVA::DataLoader loader("dataset"); 

  // Add the feature variables, names reference branches in inputFile ttree
  loader.AddSpectator("run");
  loader.AddSpectator("lumi");
  loader.AddSpectator("ev");
  loader.AddSpectator("rho");
  loader.AddSpectator("nvtx");
  loader.AddSpectator("channel");
  loader.AddVariable("mll");
  loader.AddVariable("nljets");
  loader.AddVariable("nbjets");
  //  loader.AddSpectator("ht");
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
  
  loader.AddSpectator("mpp");
  loader.AddSpectator("ypp");
  loader.AddSpectator("gen_mtt");
  loader.AddSpectator("gen_ytt");
  loader.AddVariable("rec_ytt");
  loader.AddVariable("rec_mtt");

  if(var=="mass") loader.AddTarget( "target := rec_mtt/gen_mtt" ); // define the target for the regression
  if(var=="y") loader.AddTarget( "target := rec_ytt-gen_ytt" ); // define the target for the regression


  TChain *chain = new TChain("sel2");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_5.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_6.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_7.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_8.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_9.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120_0.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_130_0.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_140_0.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_150_0.root");

  TChain *signalchain = new TChain("sel2");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120_0.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_130_0.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_140_0.root");
  signalchain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_150_0.root");

  //TCut mycuts = "abs(ht)<1000";
  TCut mycuts = "";
  //TCut mycuts2 = "ypp>-1";
  TCut mycuts2 = "ypp>-1";

  loader.AddRegressionTree(chain, 1.0);   // link the TTree to the loader, weight for each event  = 1

  loader.PrepareTrainingAndTestTree(mycuts,"nTrain_Regression=14170:nTest_Regression=1500:SplitMode=Block:NormMode=NumEvents:!V" );
  
  //prepare tmva cross validation
  TString cvOptions = "!V:!Silent:ModelPersistence:AnalysisType=Regression:NumFolds=5:SplitExpr=""";

  auto cv = new TMVA::CrossValidation("TMVACrossValidation", &loader, outputFile, cvOptions);

  //Boosted Decision Trees
  cv->BookMethod(TMVA::Types::kBDT, "BDTG_LS",
		 TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+
		 TString("RegressionLossFunctionBDTG=LeastSquares"));

  cv->Evaluate();


  // Process some output programatically, printing the ROC score for each
  // booked method.
  //
  /*  size_t iMethod = 0;
  for (auto && result : cv->GetResults()) {
    std::cout << "Summary for method " << cv->GetMethods()[iMethod++].GetValue<TString>("MethodName")
	      << std::endl;
    for (UInt_t iFold = 0; iFold<cv->GetNumFolds(); ++iFold) {
      std::cout << "\tFold " << iFold << ": "
		<< "ROC int: " << result.GetROCValues()[iFold]
		<< ", "
		<< "BkgEff@SigEff=0.3: " << result.GetEff30Values()[iFold]
		<< std::endl;
    }
    }*/

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;  
  std::cout << "==> TMVACrossValidation is done!" << std::endl;

  outputFile->Close();

  return 0;
}
