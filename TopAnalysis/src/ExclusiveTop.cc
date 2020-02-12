#include <TFile.h>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TSystem.h>
#include <TGraph.h>
#include <TKey.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>
#include "TopLJets2015/TopAnalysis/interface/MiniEvent.h"
#include "TopLJets2015/TopAnalysis/interface/GeneratorTools.h"
#include "TopLJets2015/TopAnalysis/interface/CommonTools.h"
#include "TopLJets2015/TopAnalysis/interface/ExclusiveTop.h"
#include "TopQuarkAnalysis/TopTools/interface/MEzCalculator.h"
#include "TopLJets2015/TopAnalysis/interface/JECTools.h"
#include "TopLJets2015/TopAnalysis/interface/EfficiencyScaleFactorsWrapper.h"
#include "TopLJets2015/TopAnalysis/interface/L1PrefireEfficiencyWrapper.h"

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

#include "TMath.h"
#include <TNtuple.h>

#include "TopLJets2015/CTPPSAnalysisTools/interface/LHCConditionsFactory.h"
//#include "TopLJets2015/CTPPSAnalysisTools/interface/AlignmentsFactory.h"
//#include "TopLJets2015/CTPPSAnalysisTools/interface/XiReconstructor.h"

using namespace std;

#define ADDVAR(x,name,tree) tree->Branch(name,&x);

//get pixel efficiencies
std::vector<double> pixelEff(double xi0, double xi1)
{
  double eff0 = 1;
  double eff1 = 1;
  vector<double> eff;

  TFile *effFile = TFile::Open("/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/averageEff.root");
  TH1D* eff45 = (TH1D*)effFile->Get("eff_45");
  TH1D* eff56 = (TH1D*)effFile->Get("eff_56");

  eff0=eff45->GetBinContent((eff45->FindBin(xi0)));
  eff1=eff56->GetBinContent((eff56->FindBin(xi1)));

  eff.push_back(eff0);
  eff.push_back(eff1);

  effFile->Close();

  return eff;
}

std::vector<int> ComputeLBcombination(std::vector<Particle> leptons, std::vector<Jet> bJets)
{
  std::vector<int> lb_bestpair(0,0);
  TLorentzVector lb_min;
  int bestlepton=-1, bestB = -1;

  if(bJets.size()>0)
    {

      lb_min = leptons[0]+bJets[0];
      //	  minDeltaR = leptons[0].DeltaR(bJets[0]);
      //lb_minDeltaR = leptons[0]+bJets[0];
      for(size_t i=0;i<leptons.size();i++)
	{
	  for(size_t j=0;j<bJets.size();j++)
	    {
	      TLorentzVector lb = leptons[i]+bJets[j];
	      //		   if(debug) cout << "lb mass" << lb.M() << endl;
	      if(lb.M()<lb_min.M())
		lb_min=lb;
	      bestlepton=i;
	      bestB=j;
	      //lbpair=(leptons[i],bJets[j]);
	      //	  double deltaR = leptons[i].DeltaR(bJets[j]);
	      //if(deltaR<minDeltaR){
	      // minDeltaR = deltaR;
	      //lb_minDeltaR=lb;
	    }
	}
    }

  lb_bestpair.push_back(bestlepton);
  lb_bestpair.push_back(bestB);

  return lb_bestpair; 
}

//
/*
double getJERSFBreakdown(TString key,double abseta, std::map<TString, TH1 *> jerSFBreakdown){
  if(jerSFBreakdown.find(key)==jerSFBreakdown.end()) return 0.0;
  abseta=min(fabs(abseta),5.);
  int xbin=jerSFBreakdown[key]->GetXaxis()->FindBin(abseta);
  return jerSFBreakdown[key]->GetBinContent(xbin);
}
*/

void RunExclusiveTop(TString filename,
                     TString outname,
                     Int_t channelSelection, 
                     Int_t chargeSelection, 
                     TH1F *normH, 
                     TH1F *genPU, 
                     TString era,
                     Bool_t debug)
{
  /////////////////////
  // INITIALIZATION //
  ///////////////////
  const char* CMSSW_BASE = getenv("CMSSW_BASE");
  // CTPPS reconstruction part
  /*  ctpps::XiReconstructor proton_reco;
      proton_reco.feedDispersions(Form("%s/src/TopLJets2015/CTPPSAnalysisTools/data/2017/dispersions.txt", CMSSW_BASE));
  proton_reco.interpolateCrossingAngle( 150., 0.046 );

  ctpps::AlignmentsFactory ctpps_aligns;
  ctpps_aligns.feedAlignments(Form("%s/src/TopLJets2015/CTPPSAnalysisTools/data/2017/alignments_21aug2018.txt", CMSSW_BASE));
  */
  ctpps::LHCConditionsFactory lhc_conds;
  lhc_conds.feedConditions(Form("%s/src/TopLJets2015/CTPPSAnalysisTools/data/2017/xangle_tillTS2.csv", CMSSW_BASE));
  lhc_conds.feedConditions(Form("%s/src/TopLJets2015/CTPPSAnalysisTools/data/2017/xangle_afterTS2.csv", CMSSW_BASE));

  MiniEvent_t ev;

  //PREPARE OUTPUT
  TString baseName=gSystem->BaseName(outname); 
  TString dirName=gSystem->DirName(outname);
  TFile *fOut=TFile::Open(dirName+"/"+baseName,"RECREATE");
  fOut->cd();

  // TTree* outTsel = new TTree("sel","sel"); 
  TNtuple *outTsel=new TNtuple("sel","sel","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:weight:systw_muUp:systw_muDn:systw_muRup:systw_muRdn:systw_muFup:systw_muFdn");

  std::vector<TNtuple *> ntuple_vec;

  outTsel->SetDirectory(fOut);

  //uncomment to write pps data file  
  /*
  int pps_n0, pps_n1 = 0;
  double pps_xi0 = -1;
  double pps_xi1 = -1;
  //  double pps_newxi0 = -1;
  //double pps_newxi1 = -1;

  TTree *pps_info = new TTree("ppsinfo","ppsinfo");
  pps_info->Branch("pps_ntrk0",&pps_n0);
  pps_info->Branch("pps_ntrk1",&pps_n1);
  pps_info->Branch("pps_xi0",&pps_xi0);
  pps_info->Branch("pps_xi1",&pps_xi1);
  //  pps_info->Branch("pps_newxi0",&pps_newxi0);
  //  pps_info->Branch("pps_newxi1",&pps_newxi1);
  */
  ////////


  bool hasETrigger,hasMTrigger,hasMMTrigger,hasEETrigger,hasEMTrigger; //hasATrigger;
  bool isSS=false,isSF=false; //isA;
  float beamXangle(0);
  int nRPtk(0),RPid[50];
  float RPfarcsi[50], RPnearcsi[50];

  //READ TREE FROM FILE
  TFile *f = TFile::Open(filename);  
  TH1 *triggerList=(TH1 *)f->Get("analysis/triggerList");
  TTree *t = (TTree*)f->Get("analysis/data");
  attachToMiniEventTree(t,ev,true);
  Int_t nentries(t->GetEntriesFast());
  if (debug) nentries = 10000; //restrict number of entries for testing
  t->GetEntry(0);

  cout << "...producing " << outname << " from " << nentries << " events" << endl;

  L1PrefireEfficiencyWrapper* l1PrefireWR = new L1PrefireEfficiencyWrapper(filename.Contains("Data13TeV"),era);

  //Check if its signal MC
  bool isSignal = false;
  float ngen = 1;
  if(filename.Contains("FPMC")) {isSignal = true; std::cout << "analysing signal file" << std::endl;}
  if(isSignal)
    {
      if(filename.Contains("120")) beamXangle = 120;
      if(filename.Contains("130")) beamXangle = 130;
      if(filename.Contains("140")) beamXangle = 140;
      if(filename.Contains("150")) beamXangle = 150;
      cout << "beam angle" << beamXangle << endl;   
      
      TH1 *h=(TH1 *)f->Get("analysis/counter");
      ngen=h->GetBinContent(1);
    }
    
  ////Get ntrks and csis from a data file
  TFile *fakefile = TFile::Open("/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/test/analysis/pps/xiData_new.root");
  
  int data_n0, data_n1 = 0;
  double data_xi0 = -1;
  double data_xi1 = -1;
  //  double data_newxi0 = -1;
  // double data_newxi1 = -1;
  
  TRandom3 generator(0);
  
  TTree* pps_data = (TTree*)fakefile->Get("ppsinfo");
  pps_data->SetBranchAddress("pps_ntrk0",&data_n0);
  pps_data->SetBranchAddress("pps_ntrk1",&data_n1);
  pps_data->SetBranchAddress("pps_xi0",&data_xi0);
  pps_data->SetBranchAddress("pps_xi1",&data_xi1);
  //pps_data->SetBranchAddress("pps_newxi0",&data_newxi0);
  //pps_data->SetBranchAddress("pps_newxi1",&data_newxi1); 
  
  /////////////
  
  ///Optical corrections - not needed for new NTuples
  /*
  TFile* fXi =TFile::Open("/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/OpticalFunctionsOldVsNew.root");
  TH1F* xi_ratio_45_120 = (TH1F*)fXi->Get("xi_ratio_45_120");
  TH1F* xi_ratio_45_130 = (TH1F*)fXi->Get("xi_ratio_45_130");
  TH1F* xi_ratio_45_140 = (TH1F*)fXi->Get("xi_ratio_45_140");
  TH1F* xi_ratio_45_150 = (TH1F*)fXi->Get("xi_ratio_45_150");
  
  TH1F* xi_ratio_56_120 = (TH1F*)fXi->Get("xi_ratio_56_120");
  TH1F* xi_ratio_56_130 = (TH1F*)fXi->Get("xi_ratio_56_130");
  TH1F* xi_ratio_56_140 = (TH1F*)fXi->Get("xi_ratio_56_140");
  TH1F* xi_ratio_56_150 = (TH1F*)fXi->Get("xi_ratio_56_150");
  
  TH1F* xi_ratio_45 = new TH1F("xi_ratio_45","xi_ratio_45",50,0,0.3);
  TH1F* xi_ratio_56 = new TH1F("xi_ratio_56","xi_ratio_56",50,0,0.3);
  
  if (xi_ratio_56_120!=0)
    {
      std::cout << "Read xi corrections from file" << std::endl;
      xi_ratio_45_120->SetDirectory(0); 
      xi_ratio_45_130->SetDirectory(0); 
      xi_ratio_45_140->SetDirectory(0); 
      xi_ratio_45_150->SetDirectory(0); 
      xi_ratio_56_120->SetDirectory(0); 
      xi_ratio_56_130->SetDirectory(0); 
      xi_ratio_56_140->SetDirectory(0); 
      xi_ratio_56_150->SetDirectory(0); 
    }
  fXi->Close();
  */

  //LUMINOSITY+PILEUP
  LumiTools lumi(era,genPU);
  std::map<Int_t,Float_t> lumiPerRun=lumi.lumiPerRun();

  //LEPTON EFFICIENCIES
  std::map<TString,TString> cfgMap;
  cfgMap["g_id"]="MVAwp90";
  cfgMap["m_id"]="TightID";
  cfgMap["m_iso"]="TightRelIso";
  cfgMap["m_id4iso"]="TightIDandIPCut";
  cfgMap["e_id"]="MVA90";
  EfficiencyScaleFactorsWrapper lepEffH(filename.Contains("Data13TeV"),era,cfgMap);

  //B-TAG CALIBRATION
  BTagSFUtil btvSF(era,BTagEntry::OperatingPoint::OP_MEDIUM,"",0);

  std::map<TString,TGraph*>  fragWeights  = getBFragmentationWeights(era);

  //systematics from theory  
  
  bool isTT = false;
  std::vector< WeightSysts_t > weightSysts;
  std::vector< WeightSysts_t > psWeightSysts;


  if(filename.Contains("TTJets"))
    {
      isTT=true;
      weightSysts = getWeightSysts(f,"TTJets2017");   // 2017 weights
      cout << weightSysts.size() << " matrix element weights are available" << endl;
    }

  if(filename.Contains("MC")) {
    psWeightSysts = getPartonShowerWeightSysts(f);
    cout << psWeightSysts.size() << " parton shower weights are available" << endl;
  }

  std::cout << isTT << std::endl;
  

  //BOOK HISTOGRAMS
  HistTool ht;
  ht.setNsyst(0);
 
  ht.addHist("puwgtctr",     new TH1F("puwgtctr",    ";Weight sums;Events",2,0,2));
  ht.addHist("nvtx",         new TH1F("nvtx",        ";Vertex multiplicity;Events",50,0,100));
  ht.addHist("nlep",         new TH1F("nlep",        ";Lepton multipliciy;Events",3,2,5));
  ht.addHist("nljets",       new TH1F("nljets",      ";light jet multiplicity;Events",6,0,6)); 
  ht.addHist("nbjets",       new TH1F("nbjets",      ";b jet multiplicity;Events",5,0,5));
  ht.addHist("lmpt",         new TH1F("lmpt",        ";Lepton 1 transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lmeta",        new TH1F("lmeta",       ";Lepton 1 pseudo-rapidity;Events",10,0,2.5));
  ht.addHist("lppt",         new TH1F("lppt",        ";Lepton 2 transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lpeta",        new TH1F("lpeta",       ";Lepton 2 pseudo-rapidity;Events",10,0,2.5));
  Float_t mllbins[]={0,50,100,150,200,250,300,400,600};
  //ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",sizeof(mllbins)/sizeof(Float_t)-1,mllbins));
  ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",sizeof(mllbins)/sizeof(Float_t)-1,mllbins));
  Float_t drllbins[]={0,0.4,0.8,1.2,1.6,2,2.4,2.8,3.2,3.6,4,4.4,5,5.4,5.8,6};
  ht.addHist("drll",         new TH1F("drll",        ";#DeltaR(l,l');Events",sizeof(drllbins)/sizeof(Float_t)-1,drllbins));
  Float_t Mlbbins[]={0,20,40,60,80,100,120,140,160,180,220,260,300};
  ht.addHist("Mlb",         new TH1F("Mlb",        ";Invariant mass of lb ;Events",sizeof(Mlbbins)/sizeof(Float_t)-1,Mlbbins));
  ht.addHist("Mlb_dr",         new TH1F("Mlb_dr",        ";Invariant mass of lb ;Events",sizeof(Mlbbins)/sizeof(Float_t)-1,Mlbbins));
  ht.addHist("Mlb_min",         new TH1F("Mlb_min",        ";Invariant mass of lb ;Events",sizeof(Mlbbins)/sizeof(Float_t)-1,Mlbbins));
  ht.addHist("Mlb_same",         new TH1F("Mlb_same",        ";Invariant mass of lb ;Events",sizeof(Mlbbins)/sizeof(Float_t)-1,Mlbbins));
  ht.addHist("mRP",         new TH1F("mRP",        ";Mass of pp ;Events",20,0,3000));
  ht.addHist("yRP",         new TH1F("yRP",        ";Rapidity of pp ;Events",20,-4,4));
  ht.addHist("jet1pt",         new TH1F("jet1pt",        ";Leading jet transverse momentum [GeV] ;Events",50,0,250));

  Float_t ptbosonbins[]={0,25,50,75,100,125,150,175,200,225,250,300};
  ht.addHist("ptll",         new TH1F("ptll",        ";Transverse momentum [GeV];Events",sizeof(ptbosonbins)/sizeof(Float_t)-1,ptbosonbins));
  //  ht.addHist("phistar",      new TH1F("phistar",     ";Dilepton #phi^{*};Events",50,0,5000));
  // ht.addHist("costhetaCS",   new TH1F("costhetaCS",  ";Dilepton cos#theta^{*}_{CS};Events",50,-1,1));
  ht.addHist("met",          new TH1F("met",         ";Missing transverse energy [GeV];Events",50,0,250));

  Float_t deltaphibins[]={0,0.2,0.4,0.6,0.8,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
  ht.addHist("deltaphill",  new TH1F("deltaphill", ";#Delta#phi(l,l) [rad];Events",sizeof(deltaphibins)/sizeof(Float_t)-1,deltaphibins));
  //ht.addHist("acopl",        new TH1F("acopl",       ";Acoplanarity;Events",50,0,1.0));
  
  ht.addHist("ntkrp",        new TH1F("ntkrp",       ";Track multiplicity; Events",6,0,6) );
    
//  ht.addHist("csirp",        new TH1F("csirp",       ";#xi = #deltap/p; Events",50,0,0.3) );
  // ht.addHist("xangle",       new TH1F("xangle",      ";Crossing angle; Events",10,100,200) );
  ht.addHist("h",        new TH1F("h",       ";h [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtb",        new TH1F("htb",       ";H_T (b) [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtj",        new TH1F("htj",       ";H_T (j) [GeV]; Events",50,0,80) );
  
  ht.addHist("xi0",     new TH1F("xi0",    ";#xi_0; Events",50,0,0.3) );
  ht.addHist("xi1",     new TH1F("xi1",    ";#xi_1; Events",50,0,0.3) );
  ht.addHist("newxi0",     new TH1F("newxi0",    ";#xi_0 new; Events",50,0,0.3) );
  ht.addHist("newxi1",     new TH1F("newxi1",    ";#xi_1 new; Events",50,0,0.3) );
    
  ht.addHist("mRP",     new TH1F("mRP",    ";M_{RP}; Events",20,0,3000) );
  ht.addHist("yRP",     new TH1F("yRP",    ";y_{RP}; Events",20,-3,3) );

  ht.addHist("evyields",     new TH1F("evyields",    ";Category; Events",7,0,7) );
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(1,"inc");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(2,"#geq1b");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(3,"lowMlb");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(4,"Z");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(5,"bb");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(6,"passmRP");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(7,"passnewmRP");
  ht.addHist("ratevsrun",    new TH1F("ratevsrun",   ";Run number; #sigma [pb]",int(lumiPerRun.size()),0,float(lumiPerRun.size())));

  ht.addHist("mrp_vs_yrp",      new TH2F("mRP vs. yRP",";m_{RP};y_{RP};Events",100,0,3000,100,-5,5));
  //  ht.addHist("Mlb_minM_vs_minDeltaR",      new TH2F("Mlb min vs. Mlb minDeltaR",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));
  //ht.addHist("Mlb_minM_vs_minDeltaR_match",      new TH2F("Mlb min vs. Mlb minDeltaR matched",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));
  ht.addHist("mtt_vs_ytt",      new TH2F("mtt vs. ytt",";m_{tt};y_{tt};Events",100,0,3000,100,-5,5));
  ht.addHist("mtt_vs_ytt_acc",      new TH2F("mtt vs. ytt (acc)",";m_{tt};y_{tt};Events",100,0,3000,100,-5,5));
  //  ht.addHist("xiold_vs_xinew0",      new TH2F("#xi0_old vs. #xi0_new",";#xi0_old ;#xi0_new ;Events",50,0,0.3,50,0,0.3));
  //ht.addHist("xiold_vs_xinew1",      new TH2F("#xi1_old vs. #xi1_new",";#xi1_old ;#xi1_new ;Events",50,0,0.3,50,0,0.3));
  //ht.addHist("mRPold_vs_mRPnew",      new TH2F("mRP_old vs. mRP_new",";mRP_old ;mRP_new ;Events",50,0,3000,50,0,3000));

  //ht.addHist("mRPold-new",     new TH1F("mRPold-new",    ";old m_{RP} - new m_{RP}; Events",50,0,140) );
  
  int i=0;
  for(auto key : lumiPerRun) {
    i++;
    ht.getPlots()["ratevsrun"]->GetXaxis()->SetBinLabel(i,Form("%d",key.first));
  }
  
  TString expSystNames[]={"puup",        "pudn",
                          "eetrigup",    "eetrigdn",
                          "emtrigup",    "emtrigdn",
                          "mmtrigup",    "mmtrigdn",
                          "eselup",      "eseldn",
                          "mselup",      "mseldn",
                          "l1prefireup", "l1prefiredn",
                          "ees1up", "ees1dn", "ees2up", "ees2dn", "ees3up", "ees3dn", "ees4up", "ees4dn",  "ees5up", "ees5dn",  "ees6up", "ees6dn",  "ees7up", "ees7dn",
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
			  //                          "JERstatup",   "JERstatdn",
                          //"JERJECup",    "JERJECdn", 
                          //"JERPUup",     "JERPUdn", 
                          //"JERPLIup",    "JERPLIdn", 
                          //"JERptCutup",  "JERptCutdn", 
                          //"JERtruncup",  "JERtruncdn",
                          //"JERpTdepup",  "JERpTdepdn",
                          //"JERSTmFEup",  "JERSTmFEdn",
                          "topptup",     "topptdn",
                          "AbsoluteStatJECup","AbsoluteScaleJECup","AbsoluteMPFBiasJECup","FragmentationJECup","SinglePionECALJECup","SinglePionHCALJECup","FlavorPureGluonJECup","FlavorPureQuarkJECup","FlavorPureCharmJECup","FlavorPureBottomJECup","TimePtEtaJECup","RelativeJEREC1JECup","RelativeJEREC2JECup","RelativeJERHFJECup","RelativePtBBJECup","RelativePtEC1JECup","RelativePtEC2JECup","RelativePtHFJECup","RelativeBalJECup","RelativeFSRJECup","RelativeStatFSRJECup","RelativeStatECJECup","RelativeStatHFJECup","PileUpDataMCJECup","PileUpPtRefJECup","PileUpPtBBJECup","PileUpPtEC1JECup","PileUpPtEC2JECup","PileUpPtHFJECup",
                          "AbsoluteStatJECdn","AbsoluteScaleJECdn","AbsoluteMPFBiasJECdn","FragmentationJECdn","SinglePionECALJECdn","SinglePionHCALJECdn","FlavorPureGluonJECdn","FlavorPureQuarkJECdn","FlavorPureCharmJECdn","FlavorPureBottomJECdn","TimePtEtaJECdn","RelativeJEREC1JECdn","RelativeJEREC2JECdn","RelativeJERHFJECdn","RelativePtBBJECdn","RelativePtEC1JECdn","RelativePtEC2JECdn","RelativePtHFJECdn","RelativeBalJECdn","RelativeFSRJECdn","RelativeStatFSRJECdn","RelativeStatECJECdn","RelativeStatHFJECdn","PileUpDataMCJECdn","PileUpPtRefJECdn","PileUpPtBBJECdn","PileUpPtEC1JECdn","PileUpPtEC2JECdn","PileUpPtHFJECdn",
                          "bfragup", "bfragdn"};  
  
  //instantiate 2D histograms for most relevant variables to trace with systs
  TString hoi[]={"drll","Mlb","mll","ptll"};
  size_t nthSysts(weightSysts.size()+psWeightSysts.size()); 
  size_t nexpSysts=sizeof(expSystNames)/sizeof(TString);
  std::vector<TString> expSysts(expSystNames,expSystNames+nexpSysts);

  for(size_t ih=0; ih<sizeof(hoi)/sizeof(TString); ih++)
    {    
      TH1 *histo=ht.getPlots()[hoi[ih]];
      
      //experimental systs
       ht.addHist(hoi[ih]+"_exp",      
		   new TH2D(hoi[ih]+"_exp", 
			    Form(";%s;Experimental systematic variation;Events",histo->GetName()),
			    histo->GetNbinsX(),histo->GetXaxis()->GetXbins()->GetArray(),
			    nexpSysts,0,nexpSysts));
      for(size_t is=0; is<nexpSysts; is++)
        ht.get2dPlots()[hoi[ih]+"_exp"]->GetYaxis()->SetBinLabel(is+1,expSystNames[is]);
     
      //theory systs
      if(nthSysts>0){
        ht.addHist(hoi[ih]+"_th",      
		     new TH2D(hoi[ih]+"_th", 
			      Form(";%s;Theory systematic variation;Events",histo->GetName()),
			      histo->GetNbinsX(),histo->GetXaxis()->GetXbins()->GetArray(),
			      nthSysts,0,nthSysts));
        for(size_t is=0; is<weightSysts.size(); is++) 
	  {
	    ht.get2dPlots()[hoi[ih]+"_th"]->GetYaxis()->SetBinLabel(is+1,weightSysts[is].first);
	    //	    ht.get2dPlots()["weights_th"]->GetYaxis()->SetBinLabel(is+1,weightSysts[is].first);
	  }

        for(size_t is=0; is<psWeightSysts.size(); is++) {
          size_t xbin(is+weightSysts.size());
          ht.get2dPlots()[hoi[ih]+"_th"]->GetYaxis()->SetBinLabel(xbin+1,psWeightSysts[is].first);
        }
      }
      cout << "created histogram " << hoi[ih];
    }
  
  for(size_t is=0; is<nexpSysts; is++)  
    {
      const char* sysname = (const char*)expSystNames[is]; 
      ntuple_vec.push_back(new TNtuple(Form("sel_%s",sysname),Form("sel_%s",sysname),"run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:nom_weight:syst_weight"));
      ntuple_vec[is]->SetDirectory(fOut);
    }

  std::cout << "init done" << std::endl;
  if (debug){std::cout<<"\n DEBUG MODE"<<std::endl;}

  ///////////////////////
  // LOOP OVER EVENTS //
  /////////////////////


  //EVENT SELECTION WRAPPER
  SelectionTool selector(filename, false, triggerList);
  JECTools jerTool_(era);  

  for (Int_t iev=0;iev<nentries;iev++)
    {
      t->GetEntry(iev);
      if(iev%1000==0) { printf("\r [%3.0f%%] done", 100.*(float)iev/(float)nentries); fflush(stdout); }

      //particle level dilepton or photon
      std::vector<double> trivialwgts(1,1.0);
      float gen_pt(-1),gen_m(-1),gen_dr(-1),gen_deltaphill(-1),gen_mtt(-1),gen_ytt(-10);
      std::vector<TString> gen_cats;
      bool isZ = false;
      //bool passmRPcut = false;
      if(!ev.isData){
        std::vector<Particle> genLeptons=selector.getGenLeptons(ev,20.,2.4);
	//   std::vector<Particle> genPhotons=selector.getGenPhotons(ev,50.,2.5);
	std::vector<Particle> genTops=selector.getGenTops(ev);
        
        if(genLeptons.size()>=2 && genLeptons[0].Pt()>30 && fabs(genLeptons[0].Eta())<2.1) {
          gen_pt=(genLeptons[0]+genLeptons[1]).Pt();
          gen_m=(genLeptons[0]+genLeptons[1]).M();
          if (genLeptons[0].id()==genLeptons[1].id() && fabs(gen_m-91)<15) isZ=true;
          gen_dr=genLeptons[0].DeltaR(genLeptons[1]);
	  gen_deltaphill=fabs(genLeptons[0].Phi()-genLeptons[1].Phi());
          int gen_dilcode=abs(genLeptons[0].id()*genLeptons[1].id());
          if(gen_dilcode==11*11) { gen_cats.push_back("genee"); if(isZ) gen_cats.push_back("geneez"); };
          if(gen_dilcode==11*13) { gen_cats.push_back("genem"); }
          if(gen_dilcode==13*13) { gen_cats.push_back("genmm"); if(isZ) gen_cats.push_back("genmmz"); };
        }
	
        if(genTops.size()==2){
	  gen_mtt=(genTops[0]+genTops[1]).M();
	  gen_ytt=(genTops[0]+genTops[1]).Rapidity();
        }

	if(gen_cats.size()>0){
	  ht.fill("ptll", gen_pt, trivialwgts, gen_cats);
          ht.fill("mll",  gen_m,  trivialwgts, gen_cats);
          ht.fill("drll", gen_dr,  trivialwgts, gen_cats);
          ht.fill("deltaphill", gen_deltaphill,  trivialwgts, gen_cats);
	  }
      }

      //start weights and pu weight control
      float wgt(1.0), btagWgt(1.0);
      std::vector<double>plotwgts(1,wgt);
      std::vector<float> puWgts(3,1.0),topptWgts(2,1.0),bfragWgts(2,1.0);
      EffCorrection_t l1trigprefireProb(1.0,0.);
      TString period = lumi.assignRunPeriod();
      if(!ev.isData){
        ht.fill("puwgtctr",0,plotwgts);
	puWgts=lumi.pileupWeight(ev.g_pu,period);
        std::vector<double>puPlotWgts(1,puWgts[0]);
        ht.fill("puwgtctr",1,puPlotWgts);
      }  
	
      //////////////////
      // CORRECTIONS  //
      //////////////////
      btvSF.addBTagDecisions(ev);
      if(!ev.isData) btvSF.updateBTagDecisions(ev);      

      ///////////////////////////
      // RECO LEVEL SELECTION  //
      ///////////////////////////

      //trigger
      //hasATrigger=(selector.hasTriggerBit("HLT_Photon200_v", ev.triggerBits));
      hasETrigger=(selector.hasTriggerBit("HLT_Ele35_WPTight_Gsf_v", ev.triggerBits));
      bool hasHighPtMTrigger=(selector.hasTriggerBit("HLT_Mu50_v",     ev.triggerBits));
      bool hasStdMTrigger=(selector.hasTriggerBit("HLT_IsoMu24_v",     ev.triggerBits) ||
                           selector.hasTriggerBit("HLT_IsoMu24_2p1_v", ev.triggerBits) ||
                           selector.hasTriggerBit("HLT_IsoMu27_v",     ev.triggerBits) );     
      hasMMTrigger=(selector.hasTriggerBit("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ",                  ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",          ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v",        ev.triggerBits) );
      hasEETrigger=(selector.hasTriggerBit("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",             ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v",          ev.triggerBits) );
      hasEMTrigger=(selector.hasTriggerBit("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",    ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v",    ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v",     ev.triggerBits) ||
                    selector.hasTriggerBit("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v",  ev.triggerBits) );

      if (ev.isData) { 
        //use only these unprescaled triggers for these eras
        if(filename.Contains("2017E") || filename.Contains("2017F")){
          hasStdMTrigger=selector.hasTriggerBit("HLT_IsoMu27_v",ev.triggerBits);
        }
        if(!(filename.Contains("2017A") || filename.Contains("2017B"))){
          hasMMTrigger=(selector.hasTriggerBit("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",   ev.triggerBits) ||
                        selector.hasTriggerBit("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v", ev.triggerBits) );
        }
      }
      hasMTrigger=(hasHighPtMTrigger || hasStdMTrigger);

      //trigger efficiency
      for(auto gen_cat : gen_cats) {
        //if( (gen_cat.Contains("gena") && hasATrigger) || 
	if( (gen_cat.Contains("genee") && (hasEETrigger || hasETrigger)) ||
            (gen_cat.Contains("genmm") && (hasMMTrigger || hasMTrigger)) ||
            (gen_cat.Contains("genem") && (hasEMTrigger || hasETrigger || hasMTrigger)) ) { 
          ht.fill("ptll", gen_pt, trivialwgts, gen_cat+"trig");
          ht.fill("mll",  gen_m,  trivialwgts, gen_cat+"trig");
          ht.fill("drll", gen_dr, trivialwgts, gen_cat+"trig");
        }
        //if( (gen_cat.Contains("gena") && hasATrigger) || 
	if( (gen_cat.Contains("genee") && hasETrigger) ||
            (gen_cat.Contains("genmm") && hasStdMTrigger) ||
            (gen_cat.Contains("genem") && (hasETrigger || hasStdMTrigger)) ) { 
          ht.fill("ptll", gen_pt, trivialwgts, gen_cat+"singletrig");
          ht.fill("mll",  gen_m,  trivialwgts, gen_cat+"singletrig");
          ht.fill("drll", gen_dr, trivialwgts, gen_cat+"singletrig");
        }
      }

      //identify the offline final state from the leading leptons
      int l1idx(0),l2idx(1);
      std::vector<Particle> leptons = selector.flaggedLeptons(ev);     
      leptons = selector.selLeptons(leptons,SelectionTool::TIGHT,SelectionTool::MVA90,20,2.4);
      //std::vector<Particle> photons=selector.flaggedPhotons(ev);
      //photons=selector.selPhotons(photons,SelectionTool::MVA90,leptons,200.,2.4);

      //jets
      std::vector<Jet> allJets = selector.getGoodJets(ev,30.,2.4,leptons); //,photons);

      btagWgt= btvSF.getBtagWeight(allJets,ev,"central",BTagSFUtil::METHOD1A);
      if(debug) std::cout << "the btag weight for this ev. is " << btagWgt << std::endl;
      
      //met
      TLorentzVector met(0,0,0,0);
      met.SetPtEtaPhiM(ev.met_pt,0,ev.met_phi,0.);
      
      //
      //OFFLINE SELECTION(S)
      //
      bool passTightSel(false),passMediumSel(false);
      if(leptons.size()>1){
        
        bool isTrigSafe(leptons[0].Pt()>30 && fabs(leptons[0].Eta())<2.1);

        bool isLeadingTight( (leptons[0].id()==11 && leptons[0].hasQualityFlag(SelectionTool::MVA80)) ||
                             (leptons[0].id()==13 && leptons[0].hasQualityFlag(SelectionTool::TIGHT)) );
        bool isSubLeadingTight( (leptons[1].id()==11 && leptons[1].hasQualityFlag(SelectionTool::MVA80)) ||
                                (leptons[1].id()==13 && leptons[1].hasQualityFlag(SelectionTool::TIGHT)) );
        passTightSel = (isTrigSafe && isLeadingTight && isSubLeadingTight);
        
        //bool isLeadingMedium( (leptons[0].id()==11 && leptons[0].hasQualityFlag(SelectionTool::MVA90)) ||
        //                      (leptons[0].id()==13 && leptons[0].hasQualityFlag(SelectionTool::LOOSE)) );        
        //bool isSubLeadingMedium( (leptons[1].id()==11 && leptons[1].hasQualityFlag(SelectionTool::MVA90)) ||
        //                         (leptons[1].id()==13 && leptons[1].hasQualityFlag(SelectionTool::LOOSE)) );
        bool isLeadingMedium( (leptons[0].id()==11 && leptons[0].hasQualityFlag(SelectionTool::MVA90)) ||
                              (leptons[0].id()==13 && leptons[0].hasQualityFlag(SelectionTool::TIGHT)) );        
        bool isSubLeadingMedium( (leptons[1].id()==11 && leptons[1].hasQualityFlag(SelectionTool::MVA90)) ||
                                 (leptons[1].id()==13 && leptons[1].hasQualityFlag(SelectionTool::TIGHT)) );

        passMediumSel = (isTrigSafe && isLeadingMedium && isSubLeadingMedium);        
      }
      /*else if(photons.size()>0){
        bool isTrigSafe(photons[0].Pt()>200 && fabs(photons[0].Eta())<2.4);
        bool isTight(photons[0].hasQualityFlag(SelectionTool::MVA80));
        passTightSel=(isTrigSafe && isTight);
        passMediumSel=isTrigSafe;
	}*/

      //apply selection
      TString selCat("");
      int selCode(0);
      if(leptons.size()<2) continue;
      if(!passMediumSel) continue;

      //set kinematics
      TLorentzVector ll(0,0,0,0);
      TLorentzVector lm(0,0,0,0),lp(0,0,0,0);
      //float lmScaleUnc(0),lpScaleUnc(0),llScaleUnc(0);
      float mass(0);
      //ValueCollection_t llcsi;
      //float llacopl(0),llphistar(0),llcosthetaCS(0),llMR(0),llR(0),mtm(0),mtp(0),
      float drll(0); //llht(0),mtll(0);
      if(leptons.size()>1){
        selCode=leptons[l1idx].id()*leptons[l2idx].id();
        isSF=( leptons[l1idx].id()==leptons[l2idx].id() );
        isSS=( leptons[l1idx].charge()*leptons[l2idx].charge() > 0 );
        if(selCode==11*11) selCat="ee";
        if(selCode==11*13) selCat="em";
        if(selCode==13*13) selCat="mm";

        lm=TLorentzVector(leptons[l1idx].charge()>0 ? leptons[l1idx] : leptons[l2idx]);
        //lmScaleUnc=(leptons[l1idx].charge()>0 ? leptons[l1idx].scaleUnc() : leptons[l2idx].scaleUnc());
        lp=TLorentzVector (leptons[l1idx].charge()>0 ? leptons[l2idx] : leptons[l1idx]);
        //lpScaleUnc=(leptons[l1idx].charge()>0 ? leptons[l2idx].scaleUnc() : leptons[l1idx].scaleUnc());
        if(isSS)  { 
          lm=leptons[l1idx]; 
          //lmScaleUnc=leptons[l1idx].scaleUnc();
          lp=leptons[l2idx];
          //lpScaleUnc=leptons[l2idx].scaleUnc();
        }
        ll=lm+lp;
        //llScaleUnc=TMath::Sqrt( pow(lm.Pt()*lmScaleUnc,2)+pow(lp.Pt()*lpScaleUnc,2) )/ll.Pt();
        //llht=lm.Pt()+lp.Pt();

        //dilepton specific
        mass=ll.M();
        //llcsi=calcCsi(lm,lmScaleUnc,lp,lpScaleUnc);
        //llacopl = computeAcoplanarity(lm,lp);
        drll=leptons[l1idx].DeltaR(leptons[l2idx]);
        //llphistar=computePhiStar(lm,lp);
        //llcosthetaCS=computeCosThetaStar(lm,lp);
        //llMR=computeMR(lm,lp);
        //llR=computeRsq(lm,lp,met);
        //mtm=computeMT(lm,met);
        //mtp=computeMT(lp,met);        
      }

/*else if(photons.size()>0) 
	{
	  selCode=22;
	  isSF=false;
	  isSS=false;
	  selCat="a";
	  boson=photons[0];
	  bosonScaleUnc=photons[0].scaleUnc();
	  bosonht=boson.Pt();
	}
*/    
      //mtll=computeMT(ll,met);
    
      //further selection for dileptons
      if(selCode!=22 && mass<20) continue;
      isZ=( isSF && !isSS && fabs(mass-91)<15);
      //isA=(selCode==22);

      //check again origin of the boson in data to max. efficiency and avoid double counting
      if(ev.isData) {
	/*    if(isA) {
          if( !selector.isPhotonPD() ) continue;
          if( !hasATrigger) continue;
	  }*/
        if(selCode==11*11) {
          if( !selector.isDoubleEGPD()      && !selector.isSingleElectronPD()) continue;
          if( selector.isDoubleEGPD()       && !hasEETrigger ) continue;
          if( selector.isSingleElectronPD() && !(hasETrigger && !hasEETrigger) ) continue;
        }
        if(selCode==13*13) {
          if( !selector.isDoubleMuonPD() && !selector.isSingleMuonPD()) continue;
          if( selector.isDoubleMuonPD()  && !hasMMTrigger ) continue;
          if( selector.isSingleMuonPD()  && !(hasMTrigger && !hasMMTrigger) ) continue;
        }
        if(selCode==11*13) {
          if( !selector.isMuonEGPD()        && !selector.isSingleElectronPD() && !selector.isSingleMuonPD()) continue;
          if( selector.isMuonEGPD()         && !hasEMTrigger ) continue;
          if( selector.isSingleElectronPD() && !(hasETrigger && !hasEMTrigger) ) continue;
          if( selector.isSingleMuonPD()     && !(hasMTrigger && !hasETrigger && !hasEMTrigger) ) continue;
        }
        
        //check trigger rates and final channel assignment
        std::map<Int_t,Float_t>::iterator rIt=lumiPerRun.find(ev.run);
        if(rIt!=lumiPerRun.end()){
          int runBin=std::distance(lumiPerRun.begin(),rIt);
          float lumi=1./rIt->second;
          ht.fill("ratevsrun",runBin,lumi,selCat);
        }else{
          cout << "[Warning] Unable to find run=" << ev.run << endl;
        }
      }
 
      //jets (require PU jet id)
      int njets(0);
      std::vector<Jet> bJets,lightJets,jets;
      float scalarht(0.),scalarhtb(0.),scalarhtj(0.),mindphijmet(99999.);
      float jsumposen(0.),jsumnegen(0.),jsumposhfen(0.),jsumneghfen(0.);
      for(size_t ij=0; ij<allJets.size(); ij++) 
        {
          int idx=allJets[ij].getJetIndex();
          bool passBtag(ev.j_btag[idx]>0);

          int jid=ev.j_id[idx];
          bool passLoosePu((jid>>2)&0x1);          
	  if(!passLoosePu) continue;

          if(passBtag) { bJets.push_back(allJets[ij]);     scalarhtb+=allJets[ij].pt();  }
          else         { lightJets.push_back(allJets[ij]); scalarhtj+= allJets[ij].pt(); }
          njets++;

          bool isFwd(fabs(allJets[ij].eta())>2.5);
          float jen(allJets[ij].E());
          if(allJets[ij].eta()<0) {
            jsumnegen+= jen; 
            if(isFwd) jsumneghfen += jen;
          } else {
            jsumposen+= jen; 
            if(isFwd) jsumposhfen += jen;
          }
          
          jets.push_back(allJets[ij]);
          scalarht += jets[ij].pt();          
          float dphij2met=fabs(allJets[ij].DeltaPhi(met));
          if(dphij2met>mindphijmet) continue;
          mindphijmet=dphij2met;
        }
      
      std::vector<int> lbpair = ComputeLBcombination(leptons,bJets);  

      TLorentzVector lb_min;

      if(bJets.size()>0) lb_min = leptons[lbpair[0]]+bJets[lbpair[1]];      
      //      TLorentzVector lb_minDeltaR(0,0,0,0);      
      // double minDeltaR = 0;

      //      std::vector<LeptonBJetPair> lbpair;      
      //Compute lb_min and lb_with_min_deltaR
    
      //compute hadronic recoil
      TLorentzVector h = met+ll;
      for(size_t i=0; i<bJets.size();i++)
	{
	  if(i<3) 
	    h+=bJets[i];
	};

      //baseline categories and additional stuff produced with the dilepton
      std::vector<TString> cats(1,selCat);
      //if(ll.Pt()>50) {additionalcat+="_highpt";
      //	cats.push_back(selCat+additionalcat);}
      int catsize = 1;      

      //      if(jets.size()>0) {cats.push_back(selCat+"_1j");}

      //if(bJets.size()>1) {additionalcat+="_2b";
      // cats.push_back(selCat+additionalcat);}      

      if(bJets.size()>0) {
	catsize = (int)cats.size();
	for(int i=0;i<catsize;i++)
	  cats.push_back(cats[i]+"_1b");
      }

      if(isSF && !isZ) {
	catsize = (int)cats.size();
	for(int i=0;i<catsize;i++)
	  cats.push_back(cats[i]+"_notZ");
      }

      if(isZ) {
	catsize = (int)cats.size();
	for(int i=0;i<catsize;i++)
	  cats.push_back(cats[i]+"_Zpeak");
      }
      
      else if(bJets.size()>0 && lb_min.M()<160) {
	catsize = (int)cats.size();
	for(int i=0;i<catsize;i++)
	  cats.push_back(cats[i]+"_lowMlb");}

      if(scalarhtj<10) {
	catsize = (int)cats.size();
	for(int i=0;i<catsize;i++)
	  cats.push_back(cats[i]+"_0ht");}      


      //selection efficiency                   
      for(auto gen_cat : gen_cats) {
        ht.fill("mll",  gen_m,  trivialwgts,gen_cat+"rec");
	if(passTightSel) ht.fill("mll",  gen_m,  trivialwgts,gen_cat+"2trec");
        if(isZ) {
          ht.fill("ptll", gen_pt, trivialwgts,gen_cat+"rec");
          ht.fill("drll", gen_dr,  trivialwgts, gen_cat+"rec");
	  ht.fill("deltaphill", gen_deltaphill,  trivialwgts, gen_cat+"rec");
          if(passTightSel) {
            ht.fill("ptll", gen_pt, trivialwgts,gen_cat+"2trec");
            ht.fill("drll", gen_dr,  trivialwgts, gen_cat+"2trec");
	    ht.fill("deltaphill", gen_deltaphill,  trivialwgts, gen_cat+"rec");
          }
        }
      }

      TLorentzVector ilb_min(lb_min); 
      std::vector<Jet> ibJets(bJets), iljets(lightJets);
      int testvariable = 0;

      ////////////////////
      // Event WEIGHTS //
      //////////////////

      EffCorrection_t trigSF(1.,0.);
      trigSF = lepEffH.getTriggerCorrection(leptons,{},{},period);
      EffCorrection_t sel1SF(1.,0.),sel2SF(1.,0.);
      EffCorrection_t combinedESF(1.0,0.0), combinedMSF(1.0,0.0);
      double topsf = 0;
      vector <double> pixeff(2,1.0);

      if (!ev.isData) {
        
	l1trigprefireProb=l1PrefireWR->getCorrection(allJets);

	// norm weight
        wgt  = (normH? normH->GetBinContent(1) : 1.0);
        
	if(isSignal) wgt = 1/ngen;

        // lepton trigger*selection weights
	sel1SF = lepEffH.getOfflineCorrection(leptons[l1idx], period);
	sel2SF = lepEffH.getOfflineCorrection(leptons[l2idx], period);
        /*else{
          sel1SF = lepEffH.getOfflineCorrection(photons[0], period);
	  }*/

	//for signal top pt weights        
        if(isTT) {
	  
          for(Int_t igen=0; igen<ev.ngtop; igen++)
            {
              if(abs(ev.gtop_id[igen])!=6) continue;
	      //debug
              topsf=TMath::Exp(0.156-0.00137*ev.gtop_pt[igen]);
              
	      //debug
	      if(debug)	      std::cout << "topsf was calculated to be " << topsf << std::endl;
	      topptWgts[0] *= topsf;
              topptWgts[1] *= 1./topsf;
            }
        }

	//b-fragmentation and semi-leptonic branching fractions
        bfragWgts[0] = computeBFragmentationWeight(ev,fragWeights["downFrag"]);
        bfragWgts[1] = computeBFragmentationWeight(ev,fragWeights["upFrag"]);
        //slbrWgts[0]  = computeSemilepBRWeight(ev,semilepBRwgts_["semilepbrDown"],0,false);
        //slbrWgts[1]  = computeSemilepBRWeight(ev,semilepBRwgts_["semilepbrUp"],0,false);

        wgt *= puWgts[0]*l1trigprefireProb.first*trigSF.first*sel1SF.first*sel2SF.first*btagWgt;

        // generator level weights
        wgt *= (ev.g_nw>0 ? ev.g_w[0] : 1.0);
        //update weight for plotter
        plotwgts[0]=wgt;

	
	//combined offline efficiencies
	if(abs(leptons[0].id())==11) {
	  combinedESF.second+=pow(combinedESF.first*sel1SF.second,2)+pow(sel1SF.first*combinedESF.second,2);
	  combinedESF.first *=sel1SF.first;
	}
	if(abs(leptons[0].id())==13) {
	  combinedMSF.second+=pow(combinedMSF.first*sel1SF.second,2)+pow(sel1SF.first*combinedMSF.second,2);
	  combinedMSF.first *=sel1SF.first;
	}
	if(abs(leptons[1].id())==11) {
	  combinedESF.second+=pow(combinedESF.first*sel2SF.second,2)+pow(sel2SF.first*combinedESF.second,2);
	  combinedESF.first *=sel2SF.first;
	}
	if(abs(leptons[1].id())==13) {
	  combinedMSF.second+=pow(combinedMSF.first*sel2SF.second,2)+pow(sel2SF.first*combinedMSF.second,2);
	  combinedMSF.first *=sel2SF.first;
	}
	combinedESF.second=sqrt(combinedESF.second);
	combinedMSF.second=sqrt(combinedMSF.second);
      }

      //control histograms
      ht.fill("nvtx",       ev.nvtx,         plotwgts, cats);
      
      //event yields
      ht.fill("evyields",  0,  plotwgts, cats);

      //dilepton system
      ht.fill("nlep",       (float)leptons.size(),  plotwgts, cats);      
      
      if(bJets.size()>0) {
	ht.fill("evyields",  1,  plotwgts, cats);
	//cout << "Mlb is " << lb_min.M() << endl; 
	ht.fill("Mlb", lb_min.M(),  plotwgts, cats);
	//	if(lb_min.M()==lb_minDeltaR.M()) ht.fill("Mlb_same",lb_min.M(),plotwgts,cats);
	//else 
	//{
	//  ht.fill("Mlb_min",lb_min.M(),plotwgts,cats);
	//  ht.fill("Mlb_dr",lb_minDeltaR.M(),plotwgts,cats);
	//}

	if(lb_min.M()<160)  ht.fill("evyields",  2,  plotwgts, cats);
	if(bJets.size()>1)  ht.fill("evyields",  4,  plotwgts, cats);
	//ht.fill("Mlb_minDeltaR",lb_minDeltaR.M(), plotwgts, cats);
	//ht.fill2D("Mlb_minM_vs_minDeltaR",lb_min.M(),lb_minDeltaR.M(), plotwgts, cats);	
	//if(lb_min.M()==lb_minDeltaR.M()) ht.fill2D("Mlb_minM_vs_minDeltaR_match",lb_min.M(),lb_minDeltaR.M(), plotwgts, cats);
	ht.fill("jet1pt", allJets[0].Pt(),  plotwgts, cats);
      }

      //      ht.fill("lmpt",       lm.Pt(),         plotwgts, cats);
      //ht.fill("lmeta",      fabs(lm.Eta()),  plotwgts, cats);
      //ht.fill("lppt",       lp.Pt(),         plotwgts, cats);
      //ht.fill("lpeta",      fabs(lp.Eta()),  plotwgts, cats);
      ht.fill("mll",        ll.M(),         plotwgts, cats);        
      ht.fill("drll",       drll,plotwgts,cats);
      ht.fill("deltaphill",       fabs(leptons[0].Phi()-leptons[1].Phi()),plotwgts,cats);
      //ht.fill("phistar",    llphistar,  plotwgts, cats);
      //ht.fill("costhetaCS", llcosthetaCS,      plotwgts, cats);
      //ht.fill("acopl",      llacopl,           plotwgts, cats);
      
      ht.fill("ptll",       ll.Pt(),        plotwgts, cats);
      
      //bjets
      ht.fill("nbjets",     bJets.size(),    plotwgts, cats);
      ht.fill("scalarhtb",     scalarhtb,    plotwgts, cats);
      /*for(auto &b:bJets) {
        ht.fill("bpt",     b.Pt(),           plotwgts, cats);
        ht.fill("beta",    fabs(b.Eta()),    plotwgts, cats);
	}*/
      
      //light jets
      ht.fill("nljets",     lightJets.size(),    plotwgts, cats);
      
      /*for(auto &l:lightJets) {
        ht.fill("jpt",     l.Pt(),           plotwgts, cats);
        ht.fill("jeta",    fabs(l.Eta()),    plotwgts, cats);
	}*/
        
      ht.fill("h", h.Pt(), plotwgts, cats);  
      ht.fill("met",           met.Pt(),    plotwgts, cats);
      //ht.fill("mindphijmet",   mindphijmet, plotwgts, cats);
      //ht.fill("nch",           ev.pf_ch_wgtSum,         plotwgts, cats);       
      //fill data with roman pot information
       
      nRPtk=0;
      double goodmRP=10000, goodyRP=10;
      // newgoodmRP=10000, newgoodyRP=10;	  
      int ncomptrks=0;
      bool passRPcut = false;            
      //bool passnewRPcut = false;
      //double newfarCsi0=0, newfarCsi1=0;      
      std::vector<double> farCsi0, farCsi1;
           
      if(!ev.isData) 
	{

	  //get random entry from pps_data file (with n0,n1,xi0,xi1,newxi0,newxi1)
	  //	  vector<double> MY, newMY;
	  int ent = (int) generator.Uniform(0,pps_data->GetEntriesFast());
	  pps_data->GetEntry(ent);
	  //	  std::cout << data_n0 << " , " << data_n1 << " , " << data_newxi0 << " , " << data_newxi1 << std::endl;
	  //	  newMY = attributeCombinatorialRPmass(data_n0, data_n1, data_ne, data_newxi1);
      
	  /*
	  if(selCode==13*13) MY = attributeCombinatorialRPmass(fake_mm_nfwdtrk0, fake_mm_nfwdtrk1, fake_mm_xi0, fake_mm_xi1);
	  //else if(selCode==11*13) MY = attributeCombinatorialRPmass(nrandomtrks0,nrandomtrks1,randomxi0,randomxi1);
	  else if(selCode==11*13) MY = attributeCombinatorialRPmass(fake_em_nfwdtrk0, fake_em_nfwdtrk1, fake_em_xi0, fake_em_xi1);
	  else if(selCode==11*11) MY = attributeCombinatorialRPmass(fake_ee_nfwdtrk0, fake_ee_nfwdtrk1, fake_ee_xi0, fake_ee_xi1);
	  

	  //	  if(selCode==13*13) newMY = attributeCombinatorialRPmass(fake_mm_nfwdtrk0, fake_mm_nfwdtrk1, new_fake_mm_xi0, new_fake_mm_xi1);
	  if(selCode==13*13) newMY = attributeCombinatorialRPmass(fake_mm_nfwdtrk0, fake_mm_nfwdtrk1, new_fake_mm_xi0, new_fake_mm_xi1);
	  else if(selCode==11*13) newMY = attributeCombinatorialRPmass(fake_em_nfwdtrk0, fake_em_nfwdtrk1, new_fake_em_xi0, new_fake_em_xi1);
	  else if(selCode==11*11) newMY = attributeCombinatorialRPmass(fake_ee_nfwdtrk0, fake_ee_nfwdtrk1, new_fake_ee_xi0, new_fake_ee_xi1);*/
	  if(!isSignal && data_n0==1 && data_n1==1)
	    {
	      //	      cout << "event is bkg MC and has 1 track on each side" << endl;
	      farCsi0.push_back(data_xi0);
	      farCsi1.push_back(data_xi1);
	    }

	  if(farCsi0.size()==1 && farCsi1.size()==1 && farCsi0[0]>0.02 && farCsi0[0]<0.12 && farCsi1[0]>0.025 && farCsi1[0]<0.16)
	    {	  
	      goodmRP = 13000*sqrt(farCsi0[0]*farCsi1[0]);
	      goodyRP = 0.5*TMath::Log(farCsi0[0]/farCsi1[0]);////		    
	      //debug   cout << goodmRP << endl;
	    }

	  // else if(!isSignal)
	  /*{
	      newgoodmRP=newMY[0];
	      newgoodyRP=newMY[1];
	      }*/

	  
	  //	  goodmRP=MY[0];
	  // goodyRP=MY[1];
	  // std::cout << "mew mRP "<< newMY[0] << std::endl;
	  //newgoodmRP=newMY[0];
	  //newgoodyRP=newMY[1];
	}
      

      if (ev.isData || isSignal) {
        
        //reset information
        for(size_t irp=0; irp<50; irp++) { 
          RPid[irp]=0; 
          RPfarcsi[irp]=0; 
          RPnearcsi[irp]=0; 
        }
      
        try{
	  if(ev.isData)
	    {
	      const edm::EventID ev_id( ev.run, ev.lumi, ev.event );        
	      const ctpps::conditions_t lhc_cond = lhc_conds.get( ev_id );
	      beamXangle = lhc_cond.crossing_angle;
	      ht.fill("beamXangle", beamXangle, plotwgts, selCat);
	    }


          //only dispersions for these angles are available (@ CTPPSAnalysisTools/data/2017/dispersions.txt)
          //150 is interpolated
          if(beamXangle==120 || beamXangle==130 || beamXangle==140 || beamXangle==150 || isSignal) {

            std::vector< std::pair<int,float> > nearCsis;
            std::map<int,int> ntks;
	    
            ntks[23]=0; ntks[123]=0;
            for (int ift=0; ift<ev.nfwdtrk; ift++) {
            
	      if(ev.fwdtrk_method[ift]!=0)  continue;  //single RP (try also combined)
	      //if(ev.fwdtrk_method[ift]!=1) continue; //combined RPs (strips and pixels RP)
	      const unsigned short pot_raw_id = ev.fwdtrk_pot[ift];
	      float xi=ev.fwdtrk_xi[ift];
	      if (pot_raw_id!=3 && pot_raw_id!=23 && pot_raw_id!=103 && pot_raw_id!=123) continue; 

	      if (pot_raw_id==23 || pot_raw_id==123) {
		RPid[nRPtk]=pot_raw_id;
		RPfarcsi[nRPtk]=xi;
		RPnearcsi[nRPtk]=0;              
		nRPtk++;
		if(pot_raw_id == 23) farCsi0.push_back(xi);
		if(pot_raw_id == 123) farCsi1.push_back(xi);
		
		//monitor track multiplicity and csi values
		if(ntks.find(pot_raw_id)==ntks.end()) ntks[pot_raw_id]=0;

		ntks[pot_raw_id]++;
	      }

              else{
                //save near detector info to match to pixel tracks
                nearCsis.push_back( std::pair<int,float>(pot_raw_id,xi) );
              }
            }
            
            //now try to find the best matches for strip in pixels
            for(auto stk : nearCsis) {
              
              int matchTk(-1);
              float minDcsi=1;
              for(int itk=0; itk<nRPtk; itk++) {
                
                //require on the same side of the beam pipe
                if( !( (RPid[itk]==123 && stk.first==103) || (RPid[itk]==23 && stk.first==3) ) )
                  continue;
              
                float dcsi=fabs(stk.second-RPfarcsi[itk]);
                if(dcsi>minDcsi) continue;
                matchTk=itk;
                minDcsi=dcsi;                
             
	      }
              
              if(matchTk<0) continue;
              RPnearcsi[matchTk]=stk.second;
	      if(debug)	      std::cout << "RPnearcsi" << RPnearcsi[matchTk] << std::endl;
	    }
          
	   
	    //formulas (do not uncomment, here just for reference)
	    //mRP = 13000*sqrt(pixel0_xi[i]*pixel1_xi[j])
	    //yRP = 0.5*TMath::Log(pixel0_xi[i]/pixel1_xi[j])
	    
	    //get the new csi corrections from corrections file, for each crossing angle

	    //	    if(!ev.isData)
	    //{
	    /*
	    if(beamXangle==120) {xi_ratio_45 = xi_ratio_45_120; xi_ratio_56 = xi_ratio_56_120;}
	    else if(beamXangle==130) {xi_ratio_45 = xi_ratio_45_130; xi_ratio_56 = xi_ratio_56_130;}
	    else if(beamXangle==140) {xi_ratio_45 = xi_ratio_45_140; xi_ratio_56 = xi_ratio_56_140;}
	    else if(beamXangle==150) {xi_ratio_45 = xi_ratio_45_150; xi_ratio_56 = xi_ratio_56_150;}
	
	    */
	//}

	    /*	    goodmRP = 10000;
	    goodyRP = 10;
	    newgoodmRP = 10000;
	    newgoodyRP = 10;
	    */
	    
	    //pps_n0=ntks[23];
	    //pps_n1=ntks[123];
	    //pps_xi0=-1;
	    //pps_xi1=-1;
	    //pps_newxi0=-1;
	    //pps_newxi1=-1;
	  
	    //uncomment again, just for running signal events for BDT training
	    if(isSignal)
	      {
		ntks[23]+=data_n0;
		ntks[123]+=data_n1;	
		if(debug)		std::cout << "ntks: " << ntks[23] << " " << ntks[123] << std::endl;
	      }
	   

	    if(data_n0==1) farCsi0.push_back(data_xi0);
	    if(data_n1==1) farCsi1.push_back(data_xi1);

	    if(ntks[23]==1 && ntks[123]==1)
	      {
		//ht.fill("xi0",farCsi0[0],plotwgts,cats);
		//ht.fill("xi1",farCsi1[0],plotwgts,cats);
		
		//newfarCsi0=farCsi0[0];
		//newfarCsi1=farCsi1[0];
		//if(!ev.isData)
		  //{
		//	newfarCsi0=farCsi0[0]*xi_ratio_45->GetBinContent(xi_ratio_45->FindBin(farCsi0[0]));
		//newfarCsi1=farCsi1[0]*xi_ratio_56->GetBinContent(xi_ratio_56->FindBin(farCsi1[0]));
		    //}

		if(isSignal)
		  {
		    pixeff = pixelEff(farCsi0[0],farCsi1[0]);
		    //		    cout << "eff0:" << pixeff[0] << endl;
		    //		    cout << "eff1:" << pixeff[1] << endl;
		    plotwgts[0]=plotwgts[0]*pixeff[0]*pixeff[1];
		    wgt*=pixeff[0]*pixeff[1];
		  }
	
		//pps_xi0=farCsi0[0];
		//pps_xi1=farCsi1[0];
		//pps_newxi0=newfarCsi0;
		//pps_newxi1=newfarCsi1;
		
		if(farCsi0[0]>0.02 && farCsi0[0]<0.12 && farCsi1[0]>0.025 && farCsi1[0]<0.16)
		  {
		    goodmRP = 13000*sqrt(farCsi0[0]*farCsi1[0]);
		    //		    newgoodmRP = 13000*sqrt(newfarCsi0*newfarCsi1);
		    goodyRP = 0.5*TMath::Log(farCsi0[0]/farCsi1[0]);////		    
		    //newgoodyRP = 0.5*TMath::Log(newfarCsi0/newfarCsi1);////		    
		  }
		else std::cout << "not in acceptance" << std::endl;
		
	      }

            for(auto nit : ntks) 
	      ht.fill("ntkrp", nit.second, plotwgts, Form("%s_%d",selCat.Data(),nit.first));
	    
	  }

	}catch(...){
        }

      }

      if(farCsi0.size()>0 && farCsi1.size()>0)
	{
	  ht.fill("xi0",farCsi0[0],plotwgts,cats);
	  ht.fill("xi1",farCsi1[0],plotwgts,cats);
	}

      //added 14 Jul
      //      if(goodmRP<600 && goodmRP>300) passRPcut = true;		    
      if(goodmRP<600 && goodmRP>300) passRPcut = true;

      /*
      if(passRPcut)
	{
	  /////////////////////////////////////////////////////////
	  ht.fill("evyields",  5,  plotwgts, cats);
	  int categorysize=(int)cats.size();

	  for(int i=0;i<categorysize;i++)
	      cats.push_back(cats[i]+"_RPcut");

	}///////////////////////
      */
      if(passRPcut)
	{
	  /////////////////////////////////////////////////////////
	  //if(!passRPcut) std::cout << "Passed new cut and not old" << endl;
	  ht.fill("evyields",  6,  plotwgts, cats);
	  int categorysize=(int)cats.size();

	  for(int i=0;i<categorysize;i++)
	      cats.push_back(cats[i]+"_RPcut");

	}///////////////////////

      //      if(isSignal) ht.fill2D("mtt_vs_ytt",gen_mtt,gen_ytt, plotwgts, cats);
      ht.fill("scalarhtj",  scalarhtj,    plotwgts, cats);

      /*
      if(goodmRP<5000 && goodmRP>0)
      	{
	  ht.fill("mRP", goodmRP, plotwgts, cats);
	  ht.fill("yRP", goodyRP, plotwgts, cats);
	}
      */

      if(goodmRP<5000 && goodmRP>0)	    
	{
	  ht.fill("mRP",goodmRP,plotwgts,cats);
	  ht.fill("yRP",goodyRP,plotwgts,cats);
	  //if(isSignal) ht.fill2D("mrp_vs_yrp", newgoodmRP, newgoodyRP, plotwgts, cats);
	  // if(isSignal) ht.fill2D("mtt_vs_ytt_acc",gen_mtt,gen_ytt, plotwgts, cats);
	  // ht.fill("mRPold-new",goodmRP-newgoodmRP,plotwgts,cats);
	  //	  ht.fill2D("mRPold_vs_mRPnew",goodmRP, newgoodmRP, plotwgts,cats);
	}      
      
      //      std::vector< std::pair< string, double > > weights_tree;
      //cout << "values of mpp and ypp" << endl;
      //cout << goodmRP << endl;
      //cout << goodyRP << endl;

      
      int systSize = weightSysts.size()+psWeightSysts.size();
      double systW[systSize];
      double weightSup = 1;
      double weightSdn = 1;
      double weightmuFup = 1, weightmuFdn = 1, weightmuRup = 1, weightmuRdn = 1;
      float px2=0,py2=0,pz2=0,E2=0,yvis=0,ysum=0,max_dy=0,min_dy=0;
      
      if(bJets.size()>1 && lb_min.M()<160)
	{
	  //compute some other variables
	  px2=(bJets[0].Px()+bJets[1].Px()+leptons[0].Px()+leptons[1].Px()+met.Px())*(bJets[0].Px()+bJets[1].Px()+leptons[0].Px()+leptons[1].Px()+met.Px());
	  py2=(bJets[0].Py()+bJets[1].Py()+leptons[0].Py()+leptons[1].Py()+met.Py())*(bJets[0].Py()+bJets[1].Py()+leptons[0].Py()+leptons[1].Py()+met.Py());
	  pz2=(bJets[0].Pz()+bJets[1].Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz())*(bJets[0].Pz()+bJets[1].Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz());
	  E2=(bJets[0].E()+bJets[1].E()+leptons[0].E()+leptons[1].E()+met.Pt())*(bJets[0].E()+bJets[1].E()+leptons[0].E()+leptons[1].E()+met.Pt());
	    
	  yvis=(bJets[0]+bJets[1]+leptons[0]+leptons[1]).Rapidity();
	  ysum=fabs(bJets[0].Rapidity())+fabs(bJets[1].Rapidity())+fabs(leptons[0].Rapidity())+fabs(leptons[1].Rapidity());
	  max_dy= max(fabs((bJets[0]+leptons[0]).Rapidity())-fabs((bJets[1]+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((bJets[1]+leptons[0]).Rapidity()));
          min_dy=min( fabs((bJets[0]+leptons[0]).Rapidity())-fabs((bJets[1]+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((bJets[1]+leptons[0]).Rapidity()));
	}

      //theory uncertainties are filled only for MC
      if(!ev.isData)
	{
	  if(ev.g_w[0]!=0 && normH!=NULL && normH->GetBinContent(1)!=0)
	    {
	      //replicas for theory systs
	      size_t nmeWeights(weightSysts.size());
	      size_t nWeights(nmeWeights+psWeightSysts.size());
	      for(size_t is=0; is<nWeights; is++){
		//cout << is << endl;
		//retrieve the appropriate weight (ME or PS)
		std::vector<double> sweights(1,plotwgts[0]);
		if(is<nmeWeights){
		  int meidx=weightSysts[is].second;
		  sweights[0] *= (ev.g_w[meidx]/ev.g_w[0])*(normH->GetBinContent(meidx+1)/normH->GetBinContent(1));
		  systW[is]=sweights[0];
		  //debug  cout << "weight with syst " << weightSysts[is].first << ": " << systW[is] << endl;

		  if(weightSysts[is].first=="muRmuFdn")	  weightSdn = systW[is];
		  if(weightSysts[is].first=="muRmuFup")	  weightSup = systW[is];
		  if(weightSysts[is].first=="muFdn")	  weightmuFdn = systW[is];
		  if(weightSysts[is].first=="muFup")	  weightmuFup = systW[is];
		  if(weightSysts[is].first=="muRdn")	  weightmuRdn = systW[is];
		  if(weightSysts[is].first=="muRup")	  weightmuRup = systW[is];

		  //weights_tree.push_back(weightSysts[is].first,sweights[0]);
		}else{
		  int psidx=psWeightSysts[is-nmeWeights].second;
		  sweights[0] *= ev.g_psw[psidx];
		  systW[is]=sweights[0];
		  //		  weights_tree.push_back(psWeightSysts[is].first,sweights[0]);
		}
		ht.fill2D("drll_th",  drll, is, sweights);
		//		ht.fill2D("weights_th",  iev, is, sweights, cats);
	
		ht.fill2D("ptll_th",  ll.Pt(), is, sweights);
		if(bJets.size()>0) ht.fill2D("Mlb_th",   lb_min.M(),  is, sweights);
		ht.fill2D("mll_th",   ll.M(),  is, sweights);
	      }
	    }
	}

      //experimental systs are computed for MC
      if(!ev.isData) {
	for(size_t is=0; is<expSysts.size(); is++){
	  
	  //uncertainty
	  TString sname=expSysts[is];
	  bool isUpVar(sname.EndsWith("up"));
        
	  //base values and kinematics
	  bool reSelect(false);        
	  double iwgt=(normH? normH->GetBinContent(1) : 1.0);
	  if(isSignal) iwgt = 1/ngen*pixeff[0]*pixeff[1];
	  iwgt *= (ev.g_nw>0 ? ev.g_w[0] : 1.0); 

	  //	  iwgt *= widthWgt;
	  if(debug)
	    {
	      std::cout << "combinedESF is "<< combinedESF.first << ", " << combinedESF.second << std::endl;
	      std::cout << "combinedMSF is "<< combinedMSF.first << ", " << combinedMSF.second << std::endl;
	      std::cout << "l1prefire is " << l1trigprefireProb.first << ", " << l1trigprefireProb.second << std::endl;
	      std::cout << "bfrag weight" << bfragWgts[0] << ", " << bfragWgts[1] << std::endl;
	      std::cout << "trigger scale factor (trigSF) is " << trigSF.first << ", " << trigSF.second << std::endl;
	    }

	  EffCorrection_t selSF(sel1SF.first*sel2SF.first,0.0);

	  if(sname=="puup")       iwgt *= puWgts[1]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt;
	  else if(sname=="pudn")  iwgt *= puWgts[2]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt;
	  else if( (sname.Contains("eetrig") && selCode==11*11) ||
		   (sname.Contains("emtrig") && selCode==11*13) ||
		   (sname.Contains("mmtrig") && selCode==13*13) ) {
	    double newTrigSF( max(double(0.),double(trigSF.first+(isUpVar ? +1 : -1)*trigSF.second)) );
	    iwgt *= puWgts[0]*newTrigSF*selSF.first*l1trigprefireProb.first*btagWgt;
	  }
	  else if(sname.BeginsWith("esel") ) {
	    double newESF( max(double(0.),double(combinedESF.first+(isUpVar ? +1 : -1)*combinedESF.second)) );
	    iwgt *= puWgts[0]*trigSF.first*newESF*combinedMSF.first*l1trigprefireProb.first*btagWgt;
	  }
	  else if(sname.BeginsWith("msel") ) {
	    double newMSF( max(double(0.),double(combinedMSF.first+(isUpVar ? +1 : -1)*combinedMSF.second)) );
	    iwgt *= puWgts[0]*trigSF.first*combinedESF.first*newMSF*l1trigprefireProb.first*btagWgt;
	  }
	  else if(sname.BeginsWith("l1prefire") ){
	    double newL1PrefireProb( max(double(0.),double(l1trigprefireProb.first+(isUpVar ? +1 : -1)*l1trigprefireProb.second)) );
	    iwgt *= puWgts[0]*trigSF.first*selSF.first*newL1PrefireProb*btagWgt;
	  }
	  else if(sname=="topptup")     iwgt = wgt*topptWgts[0];
	  else if(sname=="topptdn")     iwgt = wgt*topptWgts[1];
	  else if(sname=="bfragup")     iwgt = wgt*bfragWgts[0];
	  else if(sname=="bfragdn")     iwgt = wgt*bfragWgts[1];
	  //	  else if(sname=="slbrup")      iwgt = wgt*slbrWgts[0];
	  //  else if(sname=="slbrdn")      iwgt = wgt*slbrWgts[1];

	  else if(sname.Contains("btag")) {
	    TString btagSys(sname.ReplaceAll("btag",""));
	    if(btagSys.EndsWith("dn")) { btagSys=btagSys.ReplaceAll("dn",""); btagSys="down_"+btagSys;  }
	    if(btagSys.EndsWith("up")) { btagSys=btagSys.ReplaceAll("up",""); btagSys="up_"+btagSys;    }
	    double newBtagWgt=btvSF.getBtagWeight(allJets,ev,btagSys);
	    iwgt *= puWgts[0]*trigSF.first*selSF.first*l1trigprefireProb.first*newBtagWgt;
	  }
	  else {
	    iwgt = wgt;           
	  }
     
	  //leptons
	  std::vector<Particle> ileptons(leptons);
	  if(sname.BeginsWith("ees") || sname.BeginsWith("mes")) {
	    reSelect=true;
	    ileptons.clear();
	    ileptons=selector.flaggedLeptons(ev);
	    for(size_t il=0; il<ileptons.size(); il++) {
	      int id=abs(ileptons[il].id());
	      int idx=ileptons[il].originalReference();
	      double eScale(0.0);
	      if( (id==11 && sname.Contains("ees1")) || (id==13 && sname.Contains("mes1")) ) eScale=ev.l_scaleUnc1[idx];
	      if( (id==11 && sname.Contains("ees2")) || (id==13 && sname.Contains("mes2")) ) eScale=ev.l_scaleUnc2[idx];
	      if( (id==11 && sname.Contains("ees3")) || (id==13 && sname.Contains("mes3")) ) eScale=ev.l_scaleUnc3[idx];
	      if( (id==11 && sname.Contains("ees4")) || (id==13 && sname.Contains("mes4")) ) eScale=ev.l_scaleUnc4[idx];
	      if( (id==11 && sname.Contains("ees5")) || (id==13 && sname.Contains("mes5")) ) eScale=ev.l_scaleUnc5[idx];
	      if( (id==11 && sname.Contains("ees6")) || (id==13 && sname.Contains("mes6")) ) eScale=ev.l_scaleUnc6[idx];
	      if( (id==11 && sname.Contains("ees7")) || (id==13 && sname.Contains("mes7")) ) eScale=ev.l_scaleUnc7[idx];

	      if( sname.BeginsWith("ees") && id==11 ) {
		if(isUpVar) eScale=(1+fabs(eScale)/ileptons[il].Pt());
		else        eScale=(1-fabs(eScale)/ileptons[il].Pt());
		//debug
		std::cout << (isUpVar ? "eScale is for e (up) :" : "eScale is for e (dn) :") << eScale << std::endl;

	      } else if (sname.BeginsWith("mes") && id==13 ) {
		if(isUpVar) eScale=(1+fabs(1-eScale));
		else        eScale=(1-fabs(1-eScale));
		//debug
		std::cout <<  (isUpVar ? "eScale is for m (up) :" : "eScale is for m (dn) :") << eScale << std::endl;

	      } else {
		eScale=1.0;
	      }
	     ileptons[il] *= eScale;
	    }
	   
	    ileptons=selector.selLeptons(ileptons,SelectionTool::TIGHT,SelectionTool::MVA90,20,2.4);        
	    bool isTrigSafe_i(ileptons[0].Pt()>30 && fabs(ileptons[0].Eta())<2.1);
	    if(!isTrigSafe_i) continue;
	    if(ileptons.size()<2) continue;        
	    if((ileptons[0]+ileptons[1]).M()<20) continue;
	  }

	  //jets
	  std::vector<Jet> ijets(allJets);
	  float ipx2=0,ipy2=0,ipz2=0,iE2=0,iyvis=0,iysum=0,imax_dy=0,imin_dy=0;
	  double iscalarht = 0;
	  if(sname.Contains("JEC") || sname.Contains("JER") )  {
	    reSelect=true;
            
	    int jecIdx=-1;
	    if(sname.Contains("AbsoluteStat"))     jecIdx=0;
	    if(sname.Contains("AbsoluteScale"))    jecIdx=1; 
	    if(sname.Contains("AbsoluteMPFBias"))  jecIdx=2; 
	    if(sname.Contains("Fragmentation"))    jecIdx=3; 
	    if(sname.Contains("SinglePionECAL"))   jecIdx=4; 
	    if(sname.Contains("SinglePionHCAL"))   jecIdx=5; 
	    if(sname.Contains("FlavorPureGluon"))  jecIdx=6; 
	    if(sname.Contains("FlavorPureQuark"))  jecIdx=7; 
	    if(sname.Contains("FlavorPureCharm"))  jecIdx=8; 
	    if(sname.Contains("FlavorPureBottom")) jecIdx=9; 
	    if(sname.Contains("TimePtEta"))        jecIdx=10; 
	    if(sname.Contains("RelativeJEREC1"))   jecIdx=11; 
	    if(sname.Contains("RelativeJEREC2"))   jecIdx=12; 
	    if(sname.Contains("RelativeJERHF"))    jecIdx=13; 
	    if(sname.Contains("RelativePtBB"))     jecIdx=14; 
	    if(sname.Contains("RelativePtEC1"))    jecIdx=15; 
	    if(sname.Contains("RelativePtEC2"))    jecIdx=16; 
	    if(sname.Contains("RelativePtHF"))     jecIdx=17; 
	    if(sname.Contains("RelativeBal"))      jecIdx=18; 
	    if(sname.Contains("RelativeFSR"))      jecIdx=19; 
	    if(sname.Contains("RelativeStatFSR"))  jecIdx=20; 
	    if(sname.Contains("RelativeStatEC"))   jecIdx=21; 
	    if(sname.Contains("RelativeStatHF"))   jecIdx=22; 
	    if(sname.Contains("PileUpDataMC"))     jecIdx=23; 
	    if(sname.Contains("PileUpPtRef"))      jecIdx=24; 
	    if(sname.Contains("PileUpPtBB"))       jecIdx=25; 
	    if(sname.Contains("PileUpPtEC1"))      jecIdx=26; 
	    if(sname.Contains("PileUpPtEC2"))      jecIdx=27; 
	    if(sname.Contains("PileUpPtHF"))       jecIdx=28;
        
	    //re-scale and re-select jets
	    std::vector<Jet> newJets = selector.getGoodJets(ev,30.,2.4,ileptons);
	    //	    applyMC2MC(newJets);
	    ijets.clear();
	    for(auto j : newJets) {

	      int idx=j.getJetIndex();
	      int jflav(abs(ev.j_flav[idx]));

	      //shift jet energy
	      double scaleVar(1.0);
	      if(jecIdx<0) {
		float genJet_pt(ev.j_g[idx]>-1 ? ev.g_pt[ ev.j_g[idx] ] : 0);              
		TLorentzVector smearP4=jerTool_.getSmearedJet(j,genJet_pt,ev.rho,isUpVar ? Variation::UP : Variation::DOWN);
		scaleVar= smearP4.Pt()/j.Pt(); ////////??????
		//if(debug)
		std::cout << (isUpVar ? "jet scale var up: " : "jet scale var dn: ")  << scaleVar << endl;
	      } 

	      else {
		bool flavorMatches(true);
		if(jecIdx==6 && jflav!=21) flavorMatches=false; //FlavorPureGluon
		if(jecIdx==7 && jflav>=4)  flavorMatches=false; //FlavorPureQuark
		if(jecIdx==8 && jflav!=4)  flavorMatches=false; //FlavorPureCharm
		if(jecIdx==9 && jflav!=5)  flavorMatches=false; //FlavorPureGluon
		if(flavorMatches)
		  {
		    scaleVar=isUpVar ? ev.j_jecUp[jecIdx][idx] : (2-ev.j_jecUp[jecIdx][idx]);
		  }
	      }

	      if(debug)	      std::cout << (isUpVar ? "jet scale var up: " : "jet scale var dn: ")  << scaleVar << endl;
	      j*=scaleVar;           

	      ijets.push_back(j);
	      iscalarht += j.Pt();          
	    }
	  }
	  //re-select lb pairs if needed

	  if(reSelect) {

	    ibJets.clear();
	    iljets.clear();

	    for(size_t ij=0; ij<ijets.size(); ij++)
	      {
		int idjet=ijets[ij].getJetIndex();
		int ijid=ev.j_id[idjet];
		bool ipassLoosePu((ijid>>2)&0x1);
		if(!ipassLoosePu) continue;

		if(ev.j_btag[idjet]>0) ibJets.push_back(ijets[ij]);
		else iljets.push_back(ijets[ij]);
	      }

	    std::vector<int> newBestLB =  ComputeLBcombination(ileptons,ibJets);
	    if(ibJets.size()>0) ilb_min=ileptons[newBestLB[0]]+ibJets[newBestLB[1]];
	  }

	  //fill with new values/weights
	  std::vector<double> eweights(1,iwgt);
	  
	  //	  ht.fill2D("evcount_exp", 0.,  is, eweights, cats);
	  ht.fill2D("drll_exp",  ileptons[0].DeltaR(ileptons[1]),  is, eweights);
	  ht.fill2D("ptll_exp",  (ileptons[0]+ileptons[1]).Pt(),      is, eweights);
	  if(ibJets.size()>0)  ht.fill2D("Mlb_exp",   ilb_min.M(),      is, eweights);
	
	  if(ibJets.size()>1 && ilb_min.M()<160)
	    {
	      if(farCsi0.size()==0 || farCsi1.size()==0)
		{
		  farCsi0.push_back(-1);
		  farCsi1.push_back(-1);
		}

	      //compute some other variables
	      ipx2=(ibJets[0].Px()+ibJets[1].Px()+ileptons[0].Px()+ileptons[1].Px()+met.Px())*(ibJets[0].Px()+ibJets[1].Px()+ileptons[0].Px()+ileptons[1].Px()+met.Px());
	      ipy2=(ibJets[0].Py()+ibJets[1].Py()+ileptons[0].Py()+ileptons[1].Py()+met.Py())*(ibJets[0].Py()+ibJets[1].Py()+ileptons[0].Py()+ileptons[1].Py()+met.Py());
	      ipz2=(ibJets[0].Pz()+ibJets[1].Pz()+ileptons[0].Pz()+ileptons[1].Pz()+met.Pz())*(ibJets[0].Pz()+ibJets[1].Pz()+ileptons[0].Pz()+ileptons[1].Pz()+met.Pz());
	      iE2=(ibJets[0].E()+ibJets[1].E()+ileptons[0].E()+ileptons[1].E()+met.Pt())*(ibJets[0].E()+ibJets[1].E()+ileptons[0].E()+ileptons[1].E()+met.Pt());
	    
	      iyvis=(ibJets[0]+ibJets[1]+ileptons[0]+ileptons[1]).Rapidity();
	      iysum=fabs(ibJets[0].Rapidity())+fabs(ibJets[1].Rapidity())+fabs(ileptons[0].Rapidity())+fabs(ileptons[1].Rapidity());
	      imax_dy= max(fabs((ibJets[0]+ileptons[0]).Rapidity())-fabs((ibJets[1]+ileptons[1]).Rapidity()),  fabs((ibJets[0]+ileptons[1]).Rapidity())-fabs((ibJets[1]+ileptons[0]).Rapidity()));
	      imin_dy=min( fabs((ibJets[0]+ileptons[0]).Rapidity())-fabs((ibJets[1]+ileptons[1]).Rapidity()),  fabs((ibJets[0]+ileptons[1]).Rapidity())-fabs((ibJets[1]+ileptons[0]).Rapidity()));

	      Float_t varsel_syst[]={(float)ev.run,
				     (float)ev.lumi,(float)ev.event,(float)ev.nvtx,(float)ev.rho,
				     (float)ileptons[0].id()*ileptons[1].id(),(float) (ileptons[0]+ileptons[1]).M(),
				     (float)iljets.size(), (float)ibJets.size(), (float) iscalarht, 
				     (float) met.Pt(),(float) met.Phi(),
				     (float) ileptons[0].Pt(),(float)ileptons[0].Eta(),(float)ileptons[0].Phi(),(float)ileptons[0].M(),(float)
				     ileptons[1].Pt(),(float)ileptons[1].Eta(),(float)ileptons[1].Phi(),(float)ileptons[1].M(),
				     (float) ibJets[0].Pt(),(float)ibJets[0].Eta(),(float)ibJets[0].Phi(),(float)ibJets[0].M(),(float)
				     ibJets[1].Pt(),(float)ibJets[1].Eta(),(float)ibJets[1].Phi(),(float)ibJets[1].M(),
				     ipx2,ipy2,ipz2,iE2,iyvis,iysum,imax_dy,imin_dy,(float)
				     ileptons[0].DeltaR(ileptons[1]),(float) ileptons[0].DeltaPhi(ileptons[1]), 
				     (float) ilb_min.M(), (float) farCsi0[0],
				     (float) farCsi1[0], (float)		    
				     goodmRP,(float) goodyRP, (float) gen_mtt, (float) gen_ytt, (float) wgt, (float) iwgt};

	      ///Fill all the systematics variation information
	      ntuple_vec[is]->Fill(varsel_syst);
	      if(debug) cout << "filled tree for syst" << is << endl;
	      //delete[] varsel_syst;
	      testvariable = 1;
	      cout << "event "<<iev << ", syst " << is << endl;
	    }
	}	
      }

      if(bJets.size()>1 && lb_min.M()<160)
	{
	  testvariable=2;
	  if(farCsi0.size()==0 || farCsi1.size()==0)
	    {
	      farCsi0.push_back(-1);
	      farCsi1.push_back(-1);
	    }

	  Float_t varsel[]={(float)ev.run,
			    (float)ev.lumi,(float)ev.event,(float)ev.nvtx,(float)ev.rho,
			    (float)leptons[0].id()*leptons[1].id(),(float) ll.M(),(float)lightJets.size(), (float)bJets.size(), (float) scalarht, 
			    (float) met.Pt(),(float) met.Phi(),
			    (float) leptons[0].Pt(),(float)leptons[0].Eta(),(float)leptons[0].Phi(),(float)leptons[0].M(),(float)
			    leptons[1].Pt(),(float)leptons[1].Eta(),(float)leptons[1].Phi(),(float)leptons[1].M(),
			    (float) bJets[0].Pt(),(float)bJets[0].Eta(),(float)bJets[0].Phi(),(float)bJets[0].M(),(float)
			    bJets[1].Pt(),(float)bJets[1].Eta(),(float)bJets[1].Phi(),(float)bJets[1].M(),
			    px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,(float)
			    leptons[0].DeltaR(leptons[1]),(float) leptons[0].DeltaPhi(leptons[1]), (float) lb_min.M(), (float) farCsi0[0],
			    (float) farCsi1[0], (float)		    
			    goodmRP,(float) goodyRP, (float) gen_mtt, (float) gen_ytt, (float) wgt,
			    (float) weightSup, (float) weightSdn,(float)weightmuRup,(float)weightmuRdn,(float)weightmuFup,(float)weightmuFdn};

	  outTsel->Fill(varsel);
	  //delete[] varsel;
	  cout << "event "<<iev << endl;
	}

      //      pps_info->Fill();
      if(testvariable==1) cout << "this event has " << bJets.size() << "bjets and Mlb is " << lb_min.M() << endl; 
    }

  //close input file
  f->Close();
  fakefile->Close(); 

  //save histos to file  
  fOut->cd();
  
  for (auto& it : ht.getPlots())  {
    if(it.second->GetEntries()==0) continue;
    it.second->SetDirectory(fOut); it.second->Write(); 
  }

  for (auto& it : ht.get2dPlots())  {
    if(it.second->GetEntries()==0) continue;
    it.second->SetDirectory(fOut); it.second->Write(); 
  }

  //save ntuples w/ selected events to file
  outTsel->Write();

  for(size_t is=0; is<nexpSysts; is++) {
    ntuple_vec[is]->Write();
    if(debug) cout << "wrote tree for syst" << is << endl;}

  //  pps_info->Write();
  fOut->Close();
}
