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

int BDTCrossValidation()
{
  
  //define variable for regression
  TString var = "y"; 

  TMVA::Tools::Instance();

  //auto inputFile = TFile::Open("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/signal.root");
  
  auto outputFile = TFile::Open("Higgs_CrossValidationOutput.root", "RECREATE");
  
  //  TMVA::Factory factory("TMVARegression", outputFile,
  //  "!V:!Silent:Color:!DrawProgressBar:AnalysisType=Regression" );

  std::cout << "==> Start TMVARegression" << std::endl;
  
  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TMVA::DataLoader loader("dataset"); 

  // Add the feature variables, names reference branches in inputFile ttree
  //  loader.AddVariable("run");
  //  loader.AddVariable("lumi");
  //  loader.AddVariable("ev");
  //  loader.AddVariable("channel");
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
  //  loader.AddVariable("mpp");
  loader.AddVariable("ypp");
  //  loader.AddVariable("gen_mtt");
  //  loader.AddVariable("gen_ytt");
  loader.AddVariable("rec_ytt");
  loader.AddVariable("rec_mtt");

  if(var=="mass") loader.AddTarget( "target := rec_mtt/gen_mtt" ); // define the target for the regression
  if(var=="y") loader.AddTarget( "target := rec_ytt-gen_ytt" ); // define the target for the regression
 

 //  loader.AddTarget( "target := rec_mtt/gen_mtt" ); // define the target for the regression


  TChain *chain = new TChain("sel2");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_0.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_1.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_2.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_3.root");
  chain->AddFile("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_4.root");
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
  TCut mycuts2 = "ypp>-1";

  loader.AddRegressionTree(chain, 1.0);   // link the TTree to the loader, weight for each event  = 1

  loader.PrepareTrainingAndTestTree(mycuts,"nTrain_Regression=14643:nTest_Regression=1500:SplitMode=Block:NormMode=NumEvents:!V" );
  
  //prepare tmva cross validation
  //  TString cvOptions = "!V:!Silent:ModelPersistence:AnalysisType=Classification:NumFolds=5";
  //                    ":SplitExpr=""";

  auto cv = new TMVA::CrossValidation(&loader);

  //Boosted Decision Trees
  cv->BookMethod(TMVA::Types::kBDT, "BDTG_LS",
		 TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+
		 TString("RegressionLossFunctionBDTG=LeastSquares"));
 
  cv->Evaluate();

  TMVA::CrossValidationResult & result = (TMVA::CrossValidationResult &) cv->GetResults();
  result.Print();

  auto c = new TCanvas();
  result.GetROCCurves()->Draw("AL");
  c->BuildLegend();
  c->Draw();
  
  std::cout << "Average ROC Integral = " << result.GetROCAverage() 
  	    << " +/- " << result.GetROCStandardDeviation()/sqrt(cv->GetNumFolds()) << std::endl;  

  outputFile->Close();
  

  return 0;
}
