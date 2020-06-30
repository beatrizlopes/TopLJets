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

int trainBDT4regression()
{

  //define variable for regression
  char* var = "mass"; 

  TMVA::Tools::Instance();

  //auto inputFile = TFile::Open("/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/signal.root");

  auto outputFile = TFile::Open("TMVA_RegressionOutput.root", "RECREATE");

  TMVA::Factory factory("TMVARegression", outputFile,
			"!V:!Silent:Color:!DrawProgressBar:AnalysisType=Regression" );

  std::cout << "==> Start TMVARegression" << std::endl;

  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TMVA::DataLoader loader("dataset"); 

  // Add the feature variables, names reference branches in inputFile ttree
  loader.AddSpectator("run");
  loader.AddSpectator("lumi");
  loader.AddSpectator("ev");
  loader.AddSpectator("rho");
  //  loader.AddSpectator("nvtx");
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
  //  loader.AddSpectator("newmpp");
  //  loader.AddSpectator("newypp");
  loader.AddSpectator("gen_mtt");
  loader.AddSpectator("gen_ytt");
  loader.AddVariable("kinreco_mtt");
  loader.AddVariable("kinreco_ytt");
  loader.AddSpectator("weight");

  if(var=="mass") loader.AddTarget( "target := kinreco_mtt/gen_mtt" ); // define the target for the regression
  if(var=="y") loader.AddTarget( "target := kinreco_ytt-gen_ytt" ); // define the target for the regression


  TChain *chain = new TChain("sel");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_5.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_6.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_7.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_8.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_9.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_10.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_11.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_12.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_13.root");
  chain->AddFile("/eos/user/b/bribeiro/ab05162/Chunks/MC13TeV_2017_TTJets_14.root");


//  chain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120_0.root");
//  chain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_130_0.root");
//  chain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_140_0.root");
//  chain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_150_0.root");
/*
  TChain *signalchain = new TChain("sel2");
  signalchain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120_0.root");
  signalchain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_130_0.root");
  signalchain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_140_0.root");
  signalchain->AddFile("/eos/user/b/bribeiro/955fa95_ul/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_150_0.root");
*/
  //TCut mycuts = "abs(ht)<1000";
  TCut mycuts = "";
  //TCut mycuts2 = "ypp>-1";
  TCut mycuts2 = "ypp>-1 && ypp<9";

  loader.AddRegressionTree(chain, 1.0);   // link the TTree to the loader, weight for each event  = 1

  loader.PrepareTrainingAndTestTree(mycuts,"nTrain_Regression=10000:nTest_Regression=10000:SplitMode=Block:NormMode=NumEvents:!V" );
  
  // Boosted Decision Trees 
  factory.BookMethod(&loader,TMVA::Types::kBDT, "BDTG_HU_mass",
		     TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+
		     TString("RegressionLossFunctionBDTG=Huber"));

  // Boosted Decision Trees 
  factory.BookMethod(&loader,TMVA::Types::kBDT, "BDTG_LS_mass",
		     TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+
		     TString("RegressionLossFunctionBDTG=LeastSquares"));

  factory.TrainAllMethods();
  factory.TestAllMethods();

  factory.EvaluateAllMethods();

  outputFile->Close();
  auto resultsFile = TFile::Open("TMVA_RegressionOutput.root");
  auto resultsTree = (TTree*) resultsFile->Get("dataset/TestTree"); 
  // BDTG-AD is the predicted value, target is the true value
/*
  auto h1 = new TH1D("h1","BDTG",50,0,3);
  //  resultsTree->Draw("BDTG_HU-target >> h1"); 
  auto h2 = (TH1*) h1->Clone("h2");
  resultsTree->Draw("BDTG_LS_mass >> h2"); 
  //auto h3 = (TH1*) h1->Clone("h3");
  //resultsTree->Draw("target >> h3");

  //  if(var=="mass")
  
  auto h4 = new TH2D("old_method","mtt(reco)_vs_mpp(RPs)",50,0,1000,50,0,1000); 
  resultsTree->Draw("kinreco_mtt:mpp >> old_method",mycuts2);
  auto h5 = new TH2D("new_method","mtt(regressed)_vs_mpp(RPs)",50,0,1000,50,0,1000);
  resultsTree->Draw("(kinreco_mtt*1/BDTG_LS_mass):mpp >> new_method",mycuts2);  
*/
  auto h1 = new TH1D("genmtt","genmtt",100,0,1300);
  auto h2 = new TH1D("recomtt","recomtt",100,0,1300);
  auto h3 = new TH1D("regressedmtt","regressedmtt",100,0,1300);
  resultsTree->Draw("gen_mtt >> genmtt"); 
  resultsTree->Draw("kinreco_mtt >> recomtt"); 
  resultsTree->Draw("kinreco_mtt/BDTG_LS_mass >> regressedmtt"); 


  auto h6 = new TH1D("old1","mtt(reco)-mtt(gen)",50,-0.8,0.8);
  resultsTree->Draw("(kinreco_mtt-gen_mtt)/gen_mtt >> old1"); 

  auto h7 = new TH1D("new1","mtt(regressed)-mtt(gen)",50,-0.8,0.8);
  resultsTree->Draw("(kinreco_mtt/BDTG_LS_mass-gen_mtt)/gen_mtt >> new1"); 
  
  
  // else if(var=="y")
  /* 
  auto h4 = new TH2D("old_method","ytt(reco)_vs_ypp(RPs)",50,-2,2,50,-2,2);
  signalchain->Draw("rec_ytt:ypp >> old_method",mycuts2);
  auto h5 = new TH2D("new_method","ytt(regressed)_vs_ypp(RPs)",50,-2,2,50,-2,2);
  resultsTree->Draw("(rec_ytt-BDTG_LS_y):ypp >> new_method",mycuts2);
       
  auto h6 = new TH1D("old2","ytt(reco)-ytt(gen)",50,-1,1);
  signalchain->Draw("rec_ytt-gen_ytt >> old2");
      //resultsTree->Draw("rec_ytt-(rec_ytt-target) >> old"); 

  auto h7 = new TH1D("new2","ytt(regressed)-ytt(gen)",50,-1,1);
  resultsTree->Draw("(rec_ytt-BDTG_LS_y)-gen_ytt >> new2"); 
  */
  
  TCanvas* c1 = new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  h1->SetLineColor(kBlack); h1->Draw(); //gen
  h2->SetLineColor(kBlue); h2->Draw("same"); //reco
  h3->SetLineColor(kRed); h3->Draw("same"); //reg

  //h1->SetLineColor(kBlue); h1->Draw(); h1->Fit("gaus");
  //h2->SetLineColor(kRed); h2->Draw("SAME"); h2->Fit("gaus");
  //h3->SetLineColor(kGreen); h3->Draw("SAME"); h3->Fit("gaus");
  //h4->SetLineColor(kBlack); h4->Draw("SAME"); h4->Fit("gaus");

  
  //c1->cd(2);
  //h4->Draw("COLZ");
  //c1->cd(3);
  //h5->Draw("COLZ");
  

  /* c1->cd(4);
  h3->SetLineColor(kRed); h3->Draw(); h3->Fit("gaus");
  h4->SetLineColor(kBlue);
  h4->Scale((h4->Integral())/(h3->Integral())); 
  h4->Draw("SAME"); h4->Fit("gaus");
  h4->GetFunction("gaus")->SetLineColor(kBlue);
  */

  c1->cd(2);                                                                                                                                                                     
  h7->SetLineColor(kRed); h7->Draw(); h7->Fit("gaus");
  h6->SetLineColor(kBlue);
  h6->Scale((h6->Integral())/(h7->Integral()));
  h6->Draw("SAME"); h6->Fit("gaus");
  h6->GetFunction("gaus")->SetLineColor(kBlue);

  Double_t par[6];

  h6->GetFunction("gaus")->GetParameters(&par[0]);
  h7->GetFunction("gaus")->GetParameters(&par[3]);

  for(int i=0;i<6;i++)      std::cout << "parameter " << i << "= " << par[i] << std::endl;

  //  TF1* DoubleGaussian = new TF1("doublegaussian","[0]/([1]*sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*(x[0]-[2])*(x[0]-[2])/([1]*[1]))+ [3]/([4]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*(x[0]-[5])*(x[0]-[5])/([4]*[4]))",-1.5,1.5);  
  //DoubleGaussian->SetParameters(100,0.05,0,30,0.7,0);
  //h2->Fit(DoubleGaussian);   
  //  h2->Fit(DoubleGaussian);

  gPad->Draw();

  TString name;
  name.Form("bdtregression_%s.png",var);

  c1->SaveAs(name);
    
  std::cout << "==> TMVAClassification is done!" << std::endl;

  //  TNtuple* newtree= new TNtuple("sel2","sel2","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt");
  //#px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt")                                                                            
  //newtree.SetDirectory(fIn)


  return 0;
}
