#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TKey.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TNtuple.h"

#include "TopLJets2015/TopAnalysis/interface/MiniEvent.h"
#include "TopLJets2015/TopAnalysis/interface/GeneratorTools.h"
#include "TopLJets2015/TopAnalysis/interface/CommonTools.h"
#include "TopLJets2015/TopAnalysis/interface/ExclusiveTop.h"
//#include "TopQuarkAnalysis/TopTools/interface/MEzCalculator.h"
#include "TopLJets2015/TopAnalysis/interface/JECTools.h"
#include "TopLJets2015/TopAnalysis/interface/EfficiencyScaleFactorsWrapper.h"
#include "TopLJets2015/TopAnalysis/interface/L1PrefireEfficiencyWrapper.h"
#include "TopLJets2015/TopAnalysis/interface/KinematicReconstruction.h"
#include "TopLJets2015/TopAnalysis/interface/PPSEff.h"

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

//#include "TopLJets2015/TopAnalysis/interface/LHCcondsFac.h"
//#include "TopLJets2015/CTPPSAnalysisTools/interface/LHCConditionsFactory.h"
//#include "TopLJets2015/CTPPSAnalysisTools/interface/AlignmentsFactory.h"
//#include "TopLJets2015/CTPPSAnalysisTools/interface/XiReconstructor.h"

using namespace std;

#define ADDVAR(x,name,tree) tree->Branch(name,&x);


//run DESY KinReco top reconstruction algorithm
bool do_kin_reco(std::vector<Particle>& leptons, std::vector<Jet>& jets, std::vector<Jet>& bjets, TLorentzVector& met, Bool_t debug, double& kinReco_ttbar_mass, double& kinReco_ttbar_rapidity) {
    
    bool hasKinRecoSol = false;
    std::vector<TLorentzVector> allLeptons;
    std::vector<TLorentzVector> allJets;
    std::vector<TLorentzVector> allBJets;

    for (size_t i=0; i < leptons.size(); i++){
      allLeptons.push_back(leptons[i]);
    }

    //Get jets indices
    std::vector<int> jetIndices;
    jetIndices.clear();
    for (size_t i=0; i < jets.size(); i++){
      jetIndices.push_back(i);
      allJets.push_back(jets[i]);
    }

    std::vector<int> bjetIndices;
    bjetIndices.clear();
    for (size_t i=0; i < bjets.size(); i++){
      bjetIndices.push_back(i);
      allBJets.push_back(bjets[i]);
    }

    if(jets.size()<2 || bjets.size()<1) {
      hasKinRecoSol = false;
      return hasKinRecoSol;
    }

    if(debug) std::cout << "now doing ttbar kinematic reconstruction" << std::endl;
    const KinematicReconstruction* kinematicReconstruction(0);
    //For now random-number-based smearing
    kinematicReconstruction = new KinematicReconstruction(1, true, false);
    int idx_l1 = leptons[0].charge()>0 ? 1 : 0 ;
    int idx_l2 = leptons[1].charge()>0 ? 1 : 0 ;
    KinematicReconstructionSolutions kinematicReconstructionSolutions  =
    kinematicReconstruction->solutions({idx_l1}, {idx_l2}, jetIndices, bjetIndices, allLeptons, allJets, met);
    const bool hasSolution = kinematicReconstructionSolutions.numberOfSolutions();
    if (hasSolution) {
      hasKinRecoSol = true;

      TLorentzVector recotop = kinematicReconstructionSolutions.solution().top();
      TLorentzVector recoantitop = kinematicReconstructionSolutions.solution().antiTop();
      TLorentzVector recottbar = recotop + recoantitop; 

      //kinReco_ttbar_pt = recottbar.Pt();
      kinReco_ttbar_mass = recottbar.M();
      kinReco_ttbar_rapidity = recotop.Rapidity();

    }
    return hasKinRecoSol;
}


std::vector<int> ComputeLBcombination(std::vector<Particle> leptons, std::vector<Jet> bJets)
{
  std::vector<int> lb_bestpair(0,0);
  TLorentzVector lb_min(0,0,0,0);
  int bestlepton=0, bestB = 0;

  if(bJets.size()>0) {

    lb_min = leptons[0]+bJets[0];
    //	  minDeltaR = leptons[0].DeltaR(bJets[0]);
    //lb_minDeltaR = leptons[0]+bJets[0];
    for(size_t i=0;i<leptons.size();i++) {
      for(size_t j=0;j<bJets.size();j++) {
	       TLorentzVector lb = leptons[i]+bJets[j];
	      //		   if(debug) cout << "lb mass" << lb.M() << endl;
	       if(lb.M()<lb_min.M()) {
	         lb_min=lb;
            bestlepton=i;
            bestB=j;
        }
      }
    }
    lb_bestpair.push_back(bestlepton);
    lb_bestpair.push_back(bestB);
  }
  
  return lb_bestpair; 
}

void RunExclusiveTop(TString filename,
                     TString outname,
                     Int_t channelSelection, 
                     Int_t chargeSelection, 
                     TH1F *normH, 
                     TH1F *genPU, 
                     TString era,
                     Bool_t debug,
                     TString systVar)
{

  /////////////////////
  // INITIALIZATION //
  ///////////////////
  bool runSysts = true;
  bool prepareTraining = false;
  bool prepareProtonData = false;

  const char* CMSSW_BASE = getenv("CMSSW_BASE");
  
  
  float run_bdt, lumi_bdt, event_bdt, rho_bdt, mpp_bdt, ypp_bdt, reco_mtt_bdt, reco_ytt_bdt, yvis_bdt, deltarll_bdt, mll_bdt,
    ysum_bdt,  min_dy_bdt, nljets_bdt, metpt_bdt, E2_bdt, deltaphibb_bdt;
  //metphi_bdt, 

  TMVA::Tools::Instance();
  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TString method =  "BDT method";
  
  if(!prepareTraining && !prepareProtonData) {
  
    std::cout << "==> Start TMVA Reader" << std::endl;
  
    reader->AddSpectator("run",&run_bdt);
    reader->AddSpectator("lumi",&lumi_bdt);
    reader->AddSpectator("ev",&event_bdt);
    reader->AddSpectator("rho",&rho_bdt);                                                                                                    
    reader->AddVariable("mpp",&mpp_bdt);
    reader->AddVariable("ypp",&ypp_bdt);
    reader->AddVariable("kinreco_mtt",&reco_mtt_bdt);
    reader->AddVariable("kinreco_ytt",&reco_ytt_bdt);
    reader->AddVariable("yvis",&yvis_bdt);
    reader->AddVariable("deltarll",&deltarll_bdt);
    reader->AddVariable("mll",&mll_bdt);
    reader->AddVariable("fabs(b2phi-b1phi)",&deltaphibb_bdt);
    reader->AddVariable("ysum",&ysum_bdt);
    //reader->AddVariable("metphi",&metphi_bdt);
    reader->AddVariable("min_dy",&min_dy_bdt);                                                                                                                           
    reader->AddVariable("nljets",&nljets_bdt);
    reader->AddVariable("metpt",&metpt_bdt);
    reader->AddVariable("E2",&E2_bdt);
    
    reader->BookMVA( "BDT method", "/eos/user/b/bribeiro/exclusiveTTBarDilepton/BDTTrainingResults/TMVAClassification_BDT.weights.xml");
  }

  //ctpps::LHCConditionsFactory lhc_conds;
  //lhc_conds.feedConditions(Form("%s/src/TopLJets2015/CTPPSAnalysisTools/data/2017/xangle_tillTS2.csv", CMSSW_BASE));
  //lhc_conds.feedConditions(Form("%s/src/TopLJets2015/CTPPSAnalysisTools/data/2017/xangle_afterTS2.csv", CMSSW_BASE));

  PPSEff *multiRP_efficiency = new PPSEff("/eos/project/c/ctpps/subsystems/Pixel/RPixTracking/pixelEfficiencies_multiRP.root");
  PPSEff *strip_radiation_efficiency = new PPSEff("/eos/project/c/ctpps/subsystems/Strips/StripsTracking/PreliminaryEfficiencies_July132020_1D2DMultiTrack.root");

  MiniEvent_t ev;

  //PREPARE OUTPUT
  TString baseName=gSystem->BaseName(outname); 
  TString dirName=gSystem->DirName(outname);
  TFile *fOut=TFile::Open(dirName+"/"+baseName,"RECREATE");
  fOut->cd();

  //create output tree
  TNtuple *outTsel=new TNtuple("sel","sel","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:kinreco_mtt:kinreco_ytt:weight");
  outTsel->SetDirectory(fOut);

  //write pps info tree
  TTree *pps_info = new TTree("ppsinfo","ppsinfo");
  int pps_n0, pps_n1 = 0;
  double pps_xi0 = -1;
  double pps_xi1 = -1;

  if(prepareProtonData) {

    pps_info->Branch("pps_ntrk0",&pps_n0);
    pps_info->Branch("pps_ntrk1",&pps_n1);
    pps_info->Branch("pps_xi0",&pps_xi0);
    pps_info->Branch("pps_xi1",&pps_xi1);
  }


  bool hasETrigger,hasMTrigger,hasMMTrigger,hasEETrigger,hasEMTrigger; //hasATrigger;
  bool isSS=false,isSF=false; //isA;
  float beamXangle(0);
  int nRPtk(0);//RPid[50];
  //float RPfarcsi[50]:// RPnearcsi[50];

  L1PrefireEfficiencyWrapper* l1PrefireWR = new L1PrefireEfficiencyWrapper(filename.Contains("Data13TeV"),era);

  //READ TREE FROM FILE
  TFile *f = TFile::Open(filename);  
  TH1 *triggerList=(TH1 *)f->Get("analysis/triggerList");
  TH1 *counter=(TH1 *)f->Get("analysis/counter");
  TTree *t = (TTree*)f->Get("analysis/tree");
  attachToMiniEventTree(t,ev);
  Int_t nentries(t->GetEntriesFast());
  //int entrynumber = -1;
  if (debug) nentries = 1000; //restrict number of entries for testing
  t->GetEntry(0);

  cout << "...producing " << outname << " from " << nentries << " events" << endl;

  //Check if its signal MC
  bool isSignal = false;
  if(filename.Contains("excl_ttbar_dilep_QED") or filename.Contains("FPMC") ) {isSignal = true; std::cout << ">>>>>>>>>>>>analysing signal file" << std::endl;}
  if(isSignal) {
    if(filename.Contains("120")) beamXangle = 120;
    if(filename.Contains("130")) beamXangle = 130;
    if(filename.Contains("140")) beamXangle = 140;
    if(filename.Contains("150")) beamXangle = 150;
    if(debug) cout << "LHC crossing angle is " << beamXangle << "micro rad." << endl;   
  } 
  
  ////Get ntrks and csis from a data file
  TFile *fakefile = TFile::Open("/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/data/protonData.root");
  
  int data_n0 = 0, data_n1 = 0;
  double data_xi0 = -1;
  double data_xi1 = -1;
 
  TRandom3 generator(0);
  TTree* pps_data = (TTree*)fakefile->Get("ppsinfo");

  if(!prepareProtonData) {

    pps_data->SetBranchAddress("pps_ntrk0",&data_n0);
    pps_data->SetBranchAddress("pps_ntrk1",&data_n1);
    pps_data->SetBranchAddress("pps_xi0",&data_xi0);
    pps_data->SetBranchAddress("pps_xi1",&data_xi1);
  
  }

  //LUMINOSITY+PILEUP
  LumiTools lumi(era,genPU);
  std::map<Int_t,Float_t> lumiPerRun=lumi.lumiPerRun();

  //LEPTON EFFICIENCIES
  EfficiencyScaleFactorsWrapper lepEffH(filename.Contains("Data13TeV"),era);

  //B-TAG CALIBRATION
  BTagSFUtil btvSF(era,BTagEntry::OperatingPoint::OP_MEDIUM,"",0);
  std::map<TString,TGraph*>  fragWeights  = getBFragmentationWeights(era);

  //JEC/JER
  JECTools jerTool_(era);  

  //systematics from theory
  bool isTT = filename.Contains("TTJets");

  size_t nthSysts = 0;
  size_t nexpSysts = 0;

  TString thSystNames[]={"muRup",        "muRdn",
                          "muFup",       "muFdn",
                          "muRmuFup",    "muRmuFdn",
                          "isrup",      "isrdn",
                          "fsrup",      "fsrdn"};

  TString expSystNames[]={"puup",        "pudn",
//                          "eetrigup",    "eetrigdn",
//                          "emtrigup",    "emtrigdn",
//                          "mmtrigup",    "mmtrigdn",
                          "eselup",      "eseldn",
                          "mselup",      "mseldn",
                          "l1prefireup", "l1prefiredn",
//                          "ees1up", "ees1dn", "ees2up", "ees2dn", "ees3up", "ees3dn", "ees4up", "ees4dn",  "ees5up", "ees5dn",  "ees6up", "ees6dn",  "ees7up", "ees7dn",
//                          "mes1up", "mes1dn", "mes2up", "mes2dn", "mes3up", "mes3dn", "mes4up", "mes4dn",
                          "btagup",         "btagdn",
//                          "btaghfup",         "btaghfdn",
                          "JERup",       "JERdn",
                          "topptup",     "topptdn",
                          "AbsoluteStatJECup","AbsoluteScaleJECup","AbsoluteMPFBiasJECup","FragmentationJECup","SinglePionECALJECup",
                          "SinglePionHCALJECup","FlavorPureGluonJECup","FlavorPureQuarkJECup","FlavorPureCharmJECup","FlavorPureBottomJECup",
                          "TimePtEtaJECup","RelativeJEREC1JECup","RelativeJEREC2JECup","RelativeJERHFJECup","RelativePtBBJECup","RelativePtEC1JECup",
                          "RelativePtEC2JECup","RelativePtHFJECup","RelativeBalJECup","RelativeFSRJECup","RelativeStatFSRJECup","RelativeStatECJECup",
                          "RelativeStatHFJECup","PileUpDataMCJECup","PileUpPtRefJECup","PileUpPtBBJECup","PileUpPtEC1JECup","PileUpPtEC2JECup","PileUpPtHFJECup",
                          "AbsoluteStatJECdn","AbsoluteScaleJECdn","AbsoluteMPFBiasJECdn","FragmentationJECdn","SinglePionECALJECdn",
                          "SinglePionHCALJECdn","FlavorPureGluonJECdn","FlavorPureQuarkJECdn","FlavorPureCharmJECdn","FlavorPureBottomJECdn",
                          "TimePtEtaJECdn","RelativeJEREC1JECdn","RelativeJEREC2JECdn","RelativeJERHFJECdn","RelativePtBBJECdn","RelativePtEC1JECdn",
                          "RelativePtEC2JECdn","RelativePtHFJECdn","RelativeBalJECdn","RelativeFSRJECdn","RelativeStatFSRJECdn","RelativeStatECJECdn",
                          "RelativeStatHFJECdn","PileUpDataMCJECdn","PileUpPtRefJECdn","PileUpPtBBJECdn","PileUpPtEC1JECdn","PileUpPtEC2JECdn","PileUpPtHFJECdn",
                          "bfragup", "bfragdn"};

  if(runSysts && filename.Contains("MC")) {

    nthSysts = sizeof(thSystNames)/sizeof(TString);
    nexpSysts = sizeof(expSystNames)/sizeof(TString);
  }

  //std::cout << isTT << std::endl;

  //BOOK HISTOGRAMS
  HistTool ht;
  ht.setNsyst(0);
 
  ht.addHist("evt_count",    new TH1F("evt_count",   ";Selection Stage;Events",10,0,10));
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(1,"Total");
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(2,"Sumweighted");
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(3,"preselection");
  ht.getPlots()["evt_count"]->SetBinContent(1,counter->GetBinContent(1));
  ht.getPlots()["evt_count"]->SetBinContent(2,counter->GetBinContent(2));
  ht.getPlots()["evt_count"]->SetBinContent(3,counter->GetBinContent(3)); 

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

  ht.addHist("E2",          new TH1F("E2",         ";E^2 [GeV];Events",50,0,10000));
  ht.addHist("yvis",          new TH1F("yvis",         ";ttbar system rapidity;Events",50,-5,5));
  ht.addHist("ysum",          new TH1F("ysum",         ";summed abs rapidity of ttbar decay products; Events",50,0,20));
  ht.addHist("mindy",          new TH1F("mindy",         ";minimum delta y between (lepton,b-jet) ;Events",50,0,4));

  Float_t deltaphibins[]={0,0.2,0.4,0.6,0.8,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
  ht.addHist("deltaphill",  new TH1F("deltaphill", ";#Delta#phi(l,l) [rad];Events",sizeof(deltaphibins)/sizeof(Float_t)-1,deltaphibins));
  ht.addHist("deltaphibb",  new TH1F("deltaphibb", ";#Delta#phi(b,b) [rad];Events",sizeof(deltaphibins)/sizeof(Float_t)-1,deltaphibins));
  
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

  ht.addHist("kin_reco_ttbar_mass",     new TH1F("kin_reco_ttbar_mass",    ";M_{ttbar}; Events",20,0,2000) );
  ht.addHist("kin_reco_ttbar_rapidity",     new TH1F("kin_reco_ttbar_rapidity",    ";y_{ttbar}; Events",20,-3,3) );

  ht.addHist("gen_ttbar_mass",     new TH1F("gen_ttbar_mass",    ";M_{ttbar}; Events",20,0,2000) );
  ht.addHist("gen_ttbar_rapidity",     new TH1F("gen_ttbar_rapidity",    ";y_{ttbar}; Events",20,-3,3) );

  ht.addHist("gen_mtt_reco_mtt",     new TH1F("(gen_m_{tt}-reco_m_{tt})/gen_m_{tt}",    ";gen_m_{tt}-reco_m_{tt}/gen_m_{tt}; Events",50,-2,2) );
  //Float_t bdtBins[]={-1.,-0.867,-0.733,-0.6,-0.467,-0.333,-0.2,-0.067,0.067,0.2,0.333,0.467,0.867};
  ht.addHist("BDToutput",     new TH1F("BDToutput",    ";BDToutput; Events",15,-1,0.6) );
  ht.addHist("gen_mtt_vs_reco_mtt",      new TH2F("gen m_{tt} vs. kin_reco_m_{tt}",";gen m_{tt} (GeV) ;kin_reco_m_{tt} (GeV);Events",100,0,2000,100,0,2000));

  ht.addHist("evyields",     new TH1F("evyields",    ";Category; Events",7,0,7) );

  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(1,"inc");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(2,"#geq1b");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(3,"lowMlb");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(4,"Z");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(5,"bb");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(6,"passmRP");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(7,"passnewmRP");
  
  ht.addHist("mrp_vs_yrp",      new TH2F("mRP vs. yRP",";m_{RP};y_{RP};Events",100,0,3000,100,-5,5));
  //  ht.addHist("Mlb_minM_vs_minDeltaR",      new TH2F("Mlb min vs. Mlb minDeltaR",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));
  //ht.addHist("Mlb_minM_vs_minDeltaR_match",      new TH2F("Mlb min vs. Mlb minDeltaR matched",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));
  ht.addHist("mtt_vs_ytt",      new TH2F("mtt vs. ytt",";m_{tt};y_{tt};Events",100,0,3000,100,-5,5));
  ht.addHist("mtt_vs_ytt_acc",      new TH2F("mtt vs. ytt (acc)",";m_{tt};y_{tt};Events",100,0,3000,100,-5,5));

  ////////////////////////////////////////////////////////
  //instantiate BDToutput histogram to track with systs//
  //////////////////////////////////////////////////////
  
  TString hoi = "BDToutput";
  TH1 *histo=ht.getPlots()[hoi];
   
  //experimental systs
  ht.addHist(hoi+"_exp",      
                  new TH2D(hoi+"_exp", 
                           Form(";%s;Experimental systematic variation;Events",histo->GetName()),
                           histo->GetNbinsX(),-1,1,
                           nexpSysts,0,nexpSysts));
  
  for(size_t is=0; is<nexpSysts; is++) {
    ht.get2dPlots()[hoi+"_exp"]->GetYaxis()->SetBinLabel(is+1,expSystNames[is]);
    ht.addHist(hoi+"_"+expSystNames[is], new TH1F(hoi+"_"+expSystNames[is],    ";"+hoi+"_"+expSystNames[is]+"; Events",15,-0.8,0.4) );
  }
       
  //theory systs
  if(nthSysts>0){
    ht.addHist(hoi+"_th",      
                  new TH2D(hoi+"_th", 
			   Form(";%s;Theory systematic variation;Events",histo->GetName()),
			   histo->GetNbinsX(),-1,1,
			   nthSysts,0,nthSysts));
    for(size_t is=0; is<nthSysts; is++) {
      ht.get2dPlots()[hoi+"_exp"]->GetYaxis()->SetBinLabel(is+1,thSystNames[is]);
      ht.addHist(hoi+"_"+thSystNames[is], new TH1F(hoi+"_"+thSystNames[is],    ";"+hoi+"_"+thSystNames[is]+"; Events",15,-0.8,0.4) );
    }      
  }

  std::cout << "init done" << std::endl;
  if (debug){std::cout<<"\n DEBUG MODE"<<std::endl;}

  ////////////////////////////
  // Start event selection //
  //////////////////////////

  //EVENT SELECTION WRAPPER
  SelectionTool selector(filename, false, triggerList);

  ////////////////////////////
  /////START EVENT LOOP /////
  //////////////////////////

  for (Int_t iev=0;iev<nentries;iev++) {


    t->GetEntry(iev);
    if(iev%1000==0) { printf("\r [%3.0f%%] done", 100.*(float)iev/(float)nentries); fflush(stdout); }
      
    //save generator level info for ttbar system (mass and rapidity)
    float gen_mtt(-1),gen_ytt(-10);     
      
    if(!ev.isData){
 
 	    std::vector<Particle> genTops=selector.getGenTops(ev);
	
      if(genTops.size()==2){
        gen_mtt=(genTops[0]+genTops[1]).M();
        gen_ytt=(genTops[0]+genTops[1]).Rapidity();
      }
    }
   
    //start weights and pu weight control
    std::vector<double> trivialwgts(1,1.0);
    float wgt(1.0), btagWgt(1.0);
    std::vector<double>plotwgts(1,wgt);
    std::vector<float> puWgts(3,1.0),topptWgts(2,1.0),bfragWgts(2,1.0);
    EffCorrection_t l1trigprefireProb(1.0,0.);
    TString period = lumi.assignRunPeriod();

    //pileup weights for MC
    if(!ev.isData){
      ht.fill("puwgtctr",0,plotwgts);
      puWgts=lumi.pileupWeight(ev.g_pu,period);
      std::vector<double>puPlotWgts(1,puWgts[0]);
      ht.fill("puwgtctr",1,puPlotWgts);
    }  

    //add btag decisions
    btvSF.addBTagDecisions(ev);
    if(!ev.isData) btvSF.updateBTagDecisions(ev,"central","central");      
    jerTool_.smearJetEnergies(ev);

    ///////////////////////////
    // RECO LEVEL SELECTION  //
    ///////////////////////////
    //trigger
    
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
    //identify the offline final state from the leading leptons
    int l1idx(0),l2idx(1);
    std::vector<Particle> leptons = selector.flaggedLeptons(ev);     
    leptons = selector.selLeptons(leptons,SelectionTool::TIGHT,SelectionTool::MVA90,20,2.4);

    //jets
    std::vector<Jet> allJets = selector.getGoodJets(ev,30.,2.4,leptons); //,photons);
      
    //met
    TLorentzVector met(0,0,0,0);
    met.SetPtEtaPhiM(ev.met_pt,0,ev.met_phi,0.);
      
    //
    //OFFLINE SELECTION(S)
    //
    bool passTightSel(false);//passMediumSel(false);
    if(leptons.size()>1){
        
      bool isTrigSafe(leptons[0].Pt()>30 && fabs(leptons[0].Eta())<2.1);

      bool isLeadingTight( (leptons[0].id()==11 && leptons[0].hasQualityFlag(SelectionTool::MVA80)) ||
                             (leptons[0].id()==13 && leptons[0].hasQualityFlag(SelectionTool::TIGHT)) );
      bool isSubLeadingTight( (leptons[1].id()==11 && leptons[1].hasQualityFlag(SelectionTool::MVA80)) ||
                                (leptons[1].id()==13 && leptons[1].hasQualityFlag(SelectionTool::TIGHT)) );
      passTightSel = (isTrigSafe && isLeadingTight && isSubLeadingTight);
        
      //bool isLeadingMedium( (leptons[0].id()==11 && leptons[0].hasQualityFlag(SelectionTool::MVA90)) ||
                           // (leptons[0].id()==13 && leptons[0].hasQualityFlag(SelectionTool::LOOSE)) );        
      //bool isSubLeadingMedium( (leptons[1].id()==11 && leptons[1].hasQualityFlag(SelectionTool::MVA90)) ||
                            //   (leptons[1].id()==13 && leptons[1].hasQualityFlag(SelectionTool::LOOSE)) );
      //passMediumSel = (isTrigSafe && isLeadingMedium && isSubLeadingMedium);        
    }

    //apply selection
    TString selCat("");
    int selCode(0);
    
    //If we don't have 2 tight leptons, we don't consider the event:
    if(leptons.size()<2) continue;
    if(!passTightSel) continue;
    ht.fill("evt_count", 4, plotwgts);

    //set kinematics
    TLorentzVector ll(0,0,0,0);
    TLorentzVector lm(0,0,0,0),lp(0,0,0,0);
    float dilepton_mass(0);
    float dilepton_dr(0); //llht(0),mtll(0);

    selCode=leptons[l1idx].id()*leptons[l2idx].id();
    isSF=( leptons[l1idx].id()==leptons[l2idx].id() );
    isSS=( leptons[l1idx].charge()*leptons[l2idx].charge() > 0 );
      
    //exclude event if leading leptons have the same sign
    if(isSS) continue;
    
    //define ttbar decay channel  
    if(selCode==11*11) selCat="ee";
    if(selCode==11*13) selCat="em";
    if(selCode==13*13) selCat="mm";

    //define dilepton kinematic variables
    lm=TLorentzVector(leptons[l1idx].charge()>0 ? leptons[l1idx] : leptons[l2idx]);
    lp=TLorentzVector (leptons[l1idx].charge()>0 ? leptons[l2idx] : leptons[l1idx]);
    ll=lm+lp;
    dilepton_mass=ll.M();
    dilepton_dr=leptons[l1idx].DeltaR(leptons[l2idx]);
    
    //further selection for dileptons
    if(dilepton_mass<20) continue;
    bool isZ=( isSF && !isSS && fabs(dilepton_mass-91)<15);
    
    //check again triggers to max. efficiency and avoid double counting
    if(ev.isData) {

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
    }
      
    //jets (require PU jet id)
    int njets(0);
    std::vector<Jet> bJets,lightJets,jets;
    float scalarht(0.),scalarhtb(0.),scalarhtj(0.);
    
    for(size_t ij=0; ij<allJets.size(); ij++) {
      int idx=allJets[ij].getJetIndex();
      bool passBtag(ev.j_btag[idx]>0);

      int jid=ev.j_id[idx];
      bool passLoosePu((jid>>2)&0x1);          
      if(!passLoosePu) continue;

      if(passBtag) { bJets.push_back(allJets[ij]);     scalarhtb+=allJets[ij].pt();  }
      else         { lightJets.push_back(allJets[ij]); scalarhtj+= allJets[ij].pt(); }
      njets++;
        
      jets.push_back(allJets[ij]);
      scalarht += jets[ij].pt();          
    }
      
    
    TLorentzVector lb_min(0,0,0,0);
    if(bJets.size()>0) {
      std::vector<int> lbpair = ComputeLBcombination(leptons,bJets);  
      lb_min = leptons[lbpair[0]]+bJets[lbpair[1]];     
    }

    //compute hadronic recoil
    TLorentzVector h = met+ll;
    for(size_t i=0; i<bJets.size();i++) {
	   if(i<3) h+=bJets[i];
    }
    
    //histogram categories for different selection steps
    std::vector<TString> cats(1,selCat);
    int catsize = 1;      

    
    if(bJets.size()>0) {
      catsize = (int)cats.size();
      for(int i=0;i<catsize;i++) cats.push_back(cats[i]+"_1b");
    }
    
    if(bJets.size()>1) {
      catsize = (int)cats.size();
      for(int i=0;i<catsize;i++) cats.push_back(cats[i]+"_2b");
    }

    if(isSF && !isZ) {
      catsize = (int)cats.size();
      for(int i=0;i<catsize;i++) cats.push_back(cats[i]+"_notZ");
    }

    //if(isSF && isZ) {
    //  catsize = (int)cats.size();
    //  for(int i=0;i<catsize;i++) cats.push_back(cats[i]+"_Zpeak");
    //}
      
    if(bJets.size()>0 && lb_min.M()<160) {
      catsize = (int)cats.size();
      for(int i=0;i<catsize;i++) cats.push_back(cats[i]+"_lowMlb");
    }

    //if(scalarhtj<10) {
    //  catsize = (int)cats.size();
    //  for(int i=0;i<catsize;i++) cats.push_back(cats[i]+"_0ht");
    //}      

    ////////////////////
    // Event WEIGHTS //
    //////////////////
    
    EffCorrection_t trigSF(1.,0.);
    trigSF = lepEffH.getTriggerCorrection(leptons,{},{},period);
    EffCorrection_t sel1SF(1.,0.),sel2SF(1.,0.);
    EffCorrection_t combinedESF(1.0,0.0), combinedMSF(1.0,0.0);
    vector <double> pixeff(2,1.0);

    btagWgt= 1;

    if (!ev.isData) {
      l1trigprefireProb=l1PrefireWR->getCorrection(allJets);
      
      // norm weight
      wgt  = (normH? normH->GetBinContent(1) : 1.0);
      
      // lepton trigger*selection weights
      sel1SF = lepEffH.getOfflineCorrection(leptons[l1idx], period);
      sel2SF = lepEffH.getOfflineCorrection(leptons[l2idx], period);
      
      //for ttbar compute top pt SF        
      if(isTT) {
	  
        for(Int_t igen=0; igen<ev.ngtop; igen++) {
          if(abs(ev.gtop_id[igen])!=6) continue;
          double topsf=TMath::Exp(0.156-0.00137*ev.gtop_pt[igen]);
          if(debug) std::cout << "topsf was calculated to be " << topsf << std::endl;
          topptWgts[0] *= topsf;
          topptWgts[1] *= 1./topsf;
        }
      }
      
      //b-fragmentation weights
      bfragWgts[0] = computeBFragmentationWeight(ev,fragWeights["downFrag"]);
      bfragWgts[1] = computeBFragmentationWeight(ev,fragWeights["upFrag"]);
      
      wgt *= puWgts[0]*l1trigprefireProb.first*trigSF.first*sel1SF.first*sel2SF.first*btagWgt;
      //std::cout << "l1trig: " << l1trigprefireProb.first << std::endl;
      //std::cout << "trigSF: " << trigSF.first << std::endl;
      //std::cout << "sel1SF: " << sel1SF.first << std::endl;
      //std::cout << "sel2SF: " << sel2SF.first << std::endl;
      //std::cout << "btagWgt: " << btagWgt << std::endl;
      
      // generator level weights
      wgt *= (ev.g_nw>0 ? ev.g_w[0] : 1.0);
      if(debug) std::cout << "gen_weight: " << ev.g_w[0] << std::endl;

      //update weight for plotter
      if(debug) std::cout << "final weight: " << wgt << std::endl;
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
    double kinReco_m = -1, kinReco_y = -10; 

    if(!prepareProtonData) {
      ht.fill("nvtx",       ev.nvtx,         plotwgts, cats);      
      //event yields
      ht.fill("evyields",  0,  plotwgts, cats);
      
      ht.fill("nlep",       (float)leptons.size(),  plotwgts, cats);        
      if(bJets.size()>0) {
        ht.fill("evyields",  1,  plotwgts, cats);
        ht.fill("Mlb", lb_min.M(),  plotwgts, cats);
        if(lb_min.M()<160)  ht.fill("evyields",  2,  plotwgts, cats);
        if(bJets.size()>1)  ht.fill("evyields",  4,  plotwgts, cats);
      }

      //ht.fill("jet1pt", allJets[0].Pt(),  plotwgts, cats);
      ht.fill("mll",        ll.M(),         plotwgts, cats);        
      ht.fill("drll",       dilepton_dr,plotwgts,cats);
      ht.fill("deltaphill",       fabs(leptons[0].Phi()-leptons[1].Phi()),plotwgts,cats);
      if(bJets.size()>1) ht.fill("deltaphibb",       fabs(bJets[0].Phi()-bJets[1].Phi()),plotwgts,cats);

      ht.fill("ptll",       ll.Pt(),        plotwgts, cats);
        
      //bjets
      ht.fill("nbjets",     bJets.size(),    plotwgts, cats);
      ht.fill("scalarhtb",     scalarhtb,    plotwgts, cats);
        
      //light jets
      ht.fill("nljets",     lightJets.size(),    plotwgts, cats);

      ht.fill("h", h.Pt(), plotwgts, cats);  
      ht.fill("met",           met.Pt(),    plotwgts, cats);
      ht.fill("scalarhtj",  scalarhtj,    plotwgts, cats);

      do_kin_reco(leptons, allJets, bJets, met, debug, kinReco_m, kinReco_y);

      ht.fill("kin_reco_ttbar_mass", kinReco_m, plotwgts, cats);
      ht.fill("kin_reco_ttbar_rapidity", kinReco_y, plotwgts, cats);

      ht.fill("gen_ttbar_mass", gen_mtt, plotwgts, cats);
      ht.fill("gen_ttbar_rapidity", gen_ytt, plotwgts, cats);

      ht.fill("gen_mtt_reco_mtt", (gen_mtt - kinReco_m)/gen_mtt, plotwgts, cats);    

      ht.fill2D("gen_mtt_vs_reco_mtt", gen_mtt, kinReco_m, plotwgts, cats);
    }
    
    ////////////////////////////////////////////
    //fill bkg MC with roman pot information ///
    ////////////////////////////////////////////

    nRPtk=0;
    double goodmRP=10000, goodyRP=10;
    bool passRPcut = false;            
    std::vector<double> nearCsi0, nearCsi1;
           
    //get random entry from pps_data file (with n0,n1,xi0,xi1)
    if(!ev.isData && !isSignal && !prepareProtonData) {
      
      //generate random event from data
      int ent = (int) generator.Uniform(0,pps_data->GetEntriesFast());
      pps_data->GetEntry(ent);  
	
      if(data_n0==1 && data_n1==1) {
	      //	      cout << "event is bkg MC and has 1 track on each side" << endl;
	      nearCsi0.push_back(data_xi0);
	      nearCsi1.push_back(data_xi1);
	    }

      //check if tracks are in PPS acceptance and only then compute mRP and yRP   
      if(nearCsi0.size()==1 && nearCsi1.size()==1) // && nearCsi0[0]>0.03 && nearCsi0[0]<0.12 && nearCsi1[0]>0.03 && nearCsi1[0]<0.16)
      {   
        goodmRP = 13000*sqrt(nearCsi0[0]*nearCsi1[0]);
        goodyRP = 0.5*TMath::Log(nearCsi0[0]/nearCsi1[0]);
      }

    }

    std::map<int,int> ntks;
      
    ntks[3]=0; ntks[103]=0;

    if (ev.isData || isSignal) {
      
      if(debug) std::cout << "entering pps part" << std::endl;

      try{
        if(ev.isData) {
          beamXangle = ev.beamXangle;
          ht.fill("beamXangle", beamXangle, plotwgts, selCat);
        }
          
        //only dispersions for these angles are available (@ CTPPSAnalysisTools/data/2017/dispersions.txt)
        //150 is interpolated
        if(beamXangle==120 || beamXangle==130 || beamXangle==140 || beamXangle==150 || isSignal) {

          for (int ift=0; ift<ev.nfwdtrk; ift++) {
            
            const unsigned short pot_raw_id = ev.fwdtrk_pot[ift];
            
            if(ev.fwdtrk_method[ift]!=1)  continue;  //multi RP
            
            //std::cout << "method is multiRP" << std::endl;

            float xi=ev.fwdtrk_xi[ift];
            
            nRPtk++;
		        if(pot_raw_id < 100) nearCsi0.push_back(xi);
		        if(pot_raw_id > 100) nearCsi1.push_back(xi);
		
		        //monitor track multiplicity and csi values
		        if(ntks.find(pot_raw_id)==ntks.end()) ntks[pot_raw_id]=0;
		        ntks[pot_raw_id]++;
          }

          // compute mRP and yRP for data and signal
          if(ntks[3]==1 && ntks[103]==1) {
		
	    //for signal, need to apply pixel efficiencies
            if(isSignal)
		        {
		         pixeff.push_back(multiRP_efficiency->getEff(nearCsi0[0],0,ev.run) * strip_radiation_efficiency->getEff(nearCsi0[0],0,ev.run));
			       pixeff.push_back(multiRP_efficiency->getEff(nearCsi1[0],1,ev.run) * strip_radiation_efficiency->getEff(nearCsi1[0],1,ev.run));

		         plotwgts[0]=plotwgts[0]*pixeff[0]*pixeff[1];
		         wgt*=pixeff[0]*pixeff[1];
		        }
	         
           //check if tracks are in PPS acceptance and only then compute mRP and yRP 
	    //if(nearCsi0[0]>0.03 && nearCsi0[0]<0.12 && nearCsi1[0]>0.025 && nearCsi1[0]<0.16)
	    //{
		  goodmRP = 13000*sqrt(nearCsi0[0]*nearCsi1[0]);
		  goodyRP = 0.5*TMath::Log(nearCsi0[0]/nearCsi1[0]);////		    
	    //}
	    // else std::cout << "not in acceptance" << std::endl;
          }

          for(auto nit : ntks) 
	         ht.fill("ntkrp", nit.second, plotwgts, Form("%s_%d",selCat.Data(),nit.first));	    
        }
      }catch(...){
      }

    }

    ///////////////////////////////////////////
    // assign PPS info to write in data file //
    ///////////////////////////////////////////
          
    if(prepareProtonData) {

      pps_n0 = ntks[3];
      pps_n1 = ntks[103];
      if(ntks[3]>0) pps_xi0 = nearCsi0[0];
      else pps_xi0 = -1.;

      if(ntks[103]>0) pps_xi1 = nearCsi1[0];
      else pps_xi1 = -1.;

      pps_info->Fill();
    }


    if(nearCsi0.size()>0 && nearCsi1.size()>0) {
  	  ht.fill("xi0",nearCsi0[0],plotwgts,cats);
      ht.fill("xi1",nearCsi1[0],plotwgts,cats);
    }

    if(goodmRP<600 && goodmRP>300) passRPcut = true;

    if(passRPcut) {
      ht.fill("evyields",  6,  plotwgts, cats);
      //int categorysize=(int)cats.size();
      //for(int i=0;i<categorysize;i++) cats.push_back(cats[i]+"_RPcut");
    }

    if(goodmRP<5000 && goodmRP>0) {
      ht.fill("mRP",goodmRP,plotwgts,cats);
      ht.fill("yRP",goodyRP,plotwgts,cats);
    }      
      
    float px2=0,py2=0,pz2=0,E2=0,yvis=0,ysum=0,max_dy=0,min_dy=0;

    if( ( bJets.size()>1 ) && lb_min.M()<160) {
      //iseventselected = true;
      //entrynumber++;
      //compute some other variables
      Jet secondJet = bJets[1];
      
      px2=(bJets[0].Px()+secondJet.Px()+leptons[0].Px()+leptons[1].Px()+met.Px())*(bJets[0].Px()+secondJet.Px()+leptons[0].Px()+leptons[1].Px()+met.Px());
      py2=(bJets[0].Py()+secondJet.Py()+leptons[0].Py()+leptons[1].Py()+met.Py())*(bJets[0].Py()+secondJet.Py()+leptons[0].Py()+leptons[1].Py()+met.Py());
      pz2=(bJets[0].Pz()+secondJet.Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz())*(bJets[0].Pz()+secondJet.Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz());
      E2=(bJets[0].E()+secondJet.E()+leptons[0].E()+leptons[1].E()+met.Pt())*(bJets[0].E()+secondJet.E()+leptons[0].E()+leptons[1].E()+met.Pt());
	    
      yvis=(bJets[0]+secondJet+leptons[0]+leptons[1]).Rapidity();
      ysum=fabs(bJets[0].Rapidity())+fabs(secondJet.Rapidity())+fabs(leptons[0].Rapidity())+fabs(leptons[1].Rapidity());
      max_dy= max(fabs((bJets[0]+leptons[0]).Rapidity())-fabs((secondJet+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((secondJet+leptons[0]).Rapidity()));
      min_dy=min( fabs((bJets[0]+leptons[0]).Rapidity())-fabs((secondJet+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((secondJet+leptons[0]).Rapidity()));
  	
      ht.fill("E2",  E2,    plotwgts, cats);
      ht.fill("yvis",  yvis,    plotwgts, cats);
      ht.fill("ysum",  ysum,    plotwgts, cats);
      ht.fill("mindy",  min_dy,    plotwgts, cats);
  
    }
    
    if(runSysts) {
      
      //experimental systs are computed for MC
      if(!ev.isData) {
  	   for(size_t is=0; is<nexpSysts; is++){
  	  
    	   TString sname=expSystNames[is];
    	   bool isUpVar(sname.EndsWith("up"));
            
    	   //base values and kinematics
    	   bool reSelect(false);        
    	   double iwgt=(normH? normH->GetBinContent(1) : 1.0);
    	   
	       if(isSignal) iwgt = iwgt*pixeff[0]*pixeff[1];
    	   
	       iwgt *= (ev.g_nw>0 ? ev.g_w[0] : 1.0); 

    	   //	  iwgt *= widthWgt;
    	   if(debug) {
          std::cout << "combinedESF is "<< combinedESF.first << ", " << combinedESF.second << std::endl;
          std::cout << "combinedMSF is "<< combinedMSF.first << ", " << combinedMSF.second << std::endl;
          std::cout << "l1prefire is " << l1trigprefireProb.first << ", " << l1trigprefireProb.second << std::endl;
          std::cout << "bfrag weight" << bfragWgts[0] << ", " << bfragWgts[1] << std::endl;
          std::cout << "trigger scale factor (trigSF) is " << trigSF.first << ", " << trigSF.second << std::endl;
    	   }

    	   EffCorrection_t selSF(sel1SF.first*sel2SF.first,0.0);

    	   if(sname=="puup")       iwgt *= puWgts[1]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt;
    	   else if(sname=="pudn")  iwgt *= puWgts[2]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt;
    	   /*else if( (sname.Contains("eetrig") && selCode==11*11) ||
    		   (sname.Contains("emtrig") && selCode==11*13) ||
    		   (sname.Contains("mmtrig") && selCode==13*13) ) {
    	       double newTrigSF( max(double(0.),double(trigSF.first+(isUpVar ? +1 : -1)*trigSF.second)) );
    	       iwgt *= puWgts[0]*newTrigSF*selSF.first*l1trigprefireProb.first*btagWgt;
    	   }*/
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
    	   else if(sname=="topptup")     iwgt *= puWgts[0]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt*topptWgts[0];
    	   else if(sname=="topptdn")     iwgt *= puWgts[0]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt*topptWgts[1];
    	   else if(sname=="bfragup")     iwgt *= puWgts[0]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt*bfragWgts[0];
    	   else if(sname=="bfragdn")     iwgt *= puWgts[0]*trigSF.first*selSF.first*l1trigprefireProb.first*btagWgt*bfragWgts[1];
    	 
    	   else {
    	     iwgt = wgt;           
    	   }
         
    	   //leptons
    	   std::vector<Particle> ileptons(leptons);
    	   
         /*if(sname.BeginsWith("ees") || sname.BeginsWith("mes")) {
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
    	       } else if (sname.BeginsWith("mes") && id==13 ) {
    		        if(isUpVar) eScale=(1+fabs(1-eScale));
    		        else        eScale=(1-fabs(1-eScale));
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
    	    }*/

          //std::cout << "original lepton 1 pt: " << leptons[0].Pt() << ", varied l1pt: " << ileptons[0].Pt() << std::endl;

    	   //jets
    	   TLorentzVector ilb_min(lb_min); 
    	   std::vector<Jet> ijets(allJets);
    	   std::vector<Jet> ibJets(bJets);
    	   std::vector<Jet> iljets(lightJets);
    	
    	   float iE2=0;
	       float iyvis=0,iysum=0,imax_dy=0,imin_dy=0;
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
    	     //	    applyMC2MC(newJets);
    	     std::vector<Jet> newJets = selector.getGoodJets(ev,30.,2.4,leptons);
    	     ijets.clear();
    	     ibJets.clear();
    	     iljets.clear();

           if(sname.Contains("btag")) { 
              string option = isUpVar ? "up" : "dn";
              btvSF.updateBTagDecisions(ev,option,option); 
            }

    	     for(auto j : newJets) {

    	       int idx=j.getJetIndex();
    	       int jflav(abs(ev.j_flav[idx]));

    	       //shift jet energy
    	       double scaleVar(1.0);
    	       if(jecIdx<0) {
    		        if(sname.BeginsWith("JER")) scaleVar = isUpVar ? ev.j_jerUp[idx] : ev.j_jerDn[idx];
    		        if(debug)		std::cout << (isUpVar ? "jet scale var up: " : "jet scale var dn: ")  << scaleVar << endl;
              } 

    	       else {
    		        bool flavorMatches(true);
    		        if(jecIdx==6 && jflav!=21) flavorMatches=false; //FlavorPureGluon
    		        if(jecIdx==7 && jflav>=4)  flavorMatches=false; //FlavorPureQuark
    		        if(jecIdx==8 && jflav!=4)  flavorMatches=false; //FlavorPureCharm
    		        if(jecIdx==9 && jflav!=5)  flavorMatches=false; //FlavorPureGluon
    		        if(flavorMatches) 
                  scaleVar=isUpVar ? ev.j_jecUp[jecIdx][idx] : ev.j_jecDn[jecIdx][idx];
              }

    	       j*=scaleVar;           

    	       int ijid=ev.j_id[idx];
    	       bool ipassLoosePu((ijid>>2)&0x1);
    	       if(!ipassLoosePu) continue;
    	       ijets.push_back(j);
    	       iscalarht += j.Pt();          
    	       if(ev.j_btag[idx]>0) ibJets.push_back(j);
    	       else iljets.push_back(j);
    	     }

           #undef jecVariation
    	   }

      
          //re-select lb pairs if needed
    	    if(reSelect && ibJets.size()>0) {
    	     std::vector<int> newBestLB = ComputeLBcombination(ileptons,ibJets);
    	     ilb_min=ileptons[newBestLB[0]]+ibJets[newBestLB[1]];
    	    }

    	    //fill with new values/weights
    	    std::vector<double> eweights(1,iwgt);
    	  
    	   
    	    if( ( bJets.size()>1 ) && ilb_min.M()<160) {

            Jet isecondJet = ibJets[1];
            
	    if(nearCsi0.size()==0 || nearCsi1.size()==0) {
	      nearCsi0.push_back(-1);
	      nearCsi1.push_back(-1);
            }

    	      //compute some other variables
    	      //ipx2=(ibJets[0].Px()+ibJets[1].Px()+ileptons[0].Px()+ileptons[1].Px()+met.Px())*(ibJets[0].Px()+ibJets[1].Px()+ileptons[0].Px()+ileptons[1].Px()+met.Px());
    	      //ipy2=(ibJets[0].Py()+ibJets[1].Py()+ileptons[0].Py()+ileptons[1].Py()+met.Py())*(ibJets[0].Py()+ibJets[1].Py()+ileptons[0].Py()+ileptons[1].Py()+met.Py());
    	      //ipz2=(ibJets[0].Pz()+ibJets[1].Pz()+ileptons[0].Pz()+ileptons[1].Pz()+met.Pz())*(ibJets[0].Pz()+ibJets[1].Pz()+ileptons[0].Pz()+ileptons[1].Pz()+met.Pz());
    	      iE2=(ibJets[0].E()+isecondJet.E()+ileptons[0].E()+ileptons[1].E()+met.Pt())*(ibJets[0].E()+isecondJet.E()+ileptons[0].E()+ileptons[1].E()+met.Pt());
    	    
    	      iyvis=(ibJets[0]+isecondJet+ileptons[0]+ileptons[1]).Rapidity();
    	      iysum=fabs(ibJets[0].Rapidity())+fabs(isecondJet.Rapidity())+fabs(ileptons[0].Rapidity())+fabs(ileptons[1].Rapidity());
    	      imax_dy= max(fabs((ibJets[0]+ileptons[0]).Rapidity())-fabs((isecondJet+ileptons[1]).Rapidity()),  fabs((ibJets[0]+ileptons[1]).Rapidity())-fabs((isecondJet+ileptons[0]).Rapidity()));
    	      imin_dy=min( fabs((ibJets[0]+ileptons[0]).Rapidity())-fabs((isecondJet+ileptons[1]).Rapidity()),  fabs((ibJets[0]+ileptons[1]).Rapidity())-fabs((isecondJet+ileptons[0]).Rapidity()));

	          if(iE2!=iE2) iE2=E2; 
    	      if(iyvis!=iyvis) iyvis=yvis; 
    	      if(iysum!=iysum) iysum=ysum;
    	      if(imax_dy!=imax_dy) imax_dy=max_dy;
    	      if(imin_dy!=imin_dy) imin_dy=min_dy;
            double ikinReco_m = -1., ikinReco_y = -10.;
            do_kin_reco(ileptons, ijets, ibJets, met, debug,  ikinReco_m, ikinReco_y);
	    
            run_bdt=ev.run;
            lumi_bdt=ev.lumi;
            event_bdt=ev.event;
            rho_bdt=ev.rho;
            mpp_bdt=goodmRP;
            ypp_bdt=goodyRP;
            reco_mtt_bdt=ikinReco_m;
            reco_ytt_bdt=ikinReco_y;
            yvis_bdt=iyvis;
            deltarll_bdt=ileptons[0].DeltaR(ileptons[1]);
            mll_bdt=(ileptons[0]+ileptons[1]).M();
            deltaphibb_bdt=fabs(ibJets[1].Phi()-ibJets[0].Phi());
            ysum_bdt=iysum;
            //metphi_bdt=met.Phi();
            min_dy_bdt=imin_dy;
            nljets_bdt=iljets.size();
            metpt_bdt=met.Pt();
            E2_bdt=iE2;

            std::vector<double> eweights(1,iwgt);

            //std::cout << "BDToutput: " << reader->EvaluateMVA(method) << std::endl;
            //ht.fill(Form("BDToutput_%s",is),reader->EvaluateMVA(method),plotwgts,cats);

            if(mpp_bdt<6000 && !prepareProtonData && !prepareTraining) {
              ht.fill2D("BDToutput_exp", reader->EvaluateMVA(method), is, eweights, cats);
              ht.fill("BDToutput_"+expSystNames[is], reader->EvaluateMVA(method), eweights, cats);
            }
	    
    	      ///Fill all the systematics variation information
    	      //ntuple_vec[is+1]->Fill(varsel_syst);

    	      if(debug) cout << "filled hist for syst" << is << endl;
    	      //delete[] varsel_syst;
    	      //testvariable = 1;
    	      if(debug)	      cout << "event "<<iev << ", syst " << is << endl;
  	      }
        }
      }
    }

    if( bJets.size()>1 )
    {

      Jet secondJet = bJets[1];
      
	    //testvariable=2;
      if(nearCsi0.size()==0 || nearCsi1.size()==0)
	    {
	      nearCsi0.push_back(-1);
	      nearCsi1.push_back(-1);
	    }

	    Float_t varsel[]={(float)ev.run,
			    (float)ev.lumi,(float)ev.event,(float)ev.nvtx,(float)ev.rho,
			    (float)leptons[0].id()*leptons[1].id(),(float) ll.M(),(float)lightJets.size(), (float)bJets.size(), (float) scalarht, 
			    (float) met.Pt(),(float) met.Phi(),
			    (float) leptons[0].Pt(),(float)leptons[0].Eta(),(float)leptons[0].Phi(),(float)leptons[0].M(),(float)
			    leptons[1].Pt(),(float)leptons[1].Eta(),(float)leptons[1].Phi(),(float)leptons[1].M(),
			    (float) bJets[0].Pt(),(float)bJets[0].Eta(),(float)bJets[0].Phi(),(float)bJets[0].M(),(float)
			    secondJet.Pt(),(float)secondJet.Eta(),(float)secondJet.Phi(),(float)secondJet.M(),
			    px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,(float)
			    leptons[0].DeltaR(leptons[1]),(float) leptons[0].DeltaPhi(leptons[1]), (float) lb_min.M(), (float) nearCsi0[0],
			    (float) nearCsi1[0], (float)		    
			    goodmRP,(float) goodyRP, (float) gen_mtt, (float) gen_ytt, (float) kinReco_m, (float) kinReco_y, 
          (float) wgt};
	
      outTsel->Fill(varsel);
      
      run_bdt=ev.run;
      lumi_bdt=ev.lumi;
      event_bdt=ev.event;
      rho_bdt=ev.rho;
      mpp_bdt=goodmRP;
      ypp_bdt=goodyRP;
      reco_mtt_bdt=kinReco_m;
      reco_ytt_bdt=kinReco_y;
      yvis_bdt=yvis;
      deltarll_bdt=leptons[0].DeltaR(leptons[1]);
      mll_bdt=ll.M();
      deltaphibb_bdt=fabs(bJets[1].Phi()-bJets[0].Phi());
      ysum_bdt=ysum;
      //metphi_bdt=met.Phi();
      min_dy_bdt=min_dy;
      nljets_bdt=lightJets.size();
      metpt_bdt=met.Pt();
      E2_bdt=E2;

      if(debug && !prepareTraining && !prepareProtonData) std::cout << "BDToutput: " << reader->EvaluateMVA(method) << std::endl;
      if(mpp_bdt<6000 && !prepareTraining && !prepareProtonData) ht.fill("BDToutput",reader->EvaluateMVA(method),plotwgts,cats);
      
      //theory uncertainties are filled only for MC
      if(!ev.isData && runSysts) {
        if(ev.g_w[0]!=0 && normH!=NULL && normH->GetBinContent(1)!=0) {
          for(size_t is=0; is<nthSysts; is++){
          
            TString sname=thSystNames[is];
            
            std::vector<double> sweights(1,plotwgts[0]);
            
            if(ev.g_nw>7) {
              if(sname=="muRup") sweights[0] *= (ev.g_w[2])/ev.g_w[0]*(normH->GetBinContent(3)/normH->GetBinContent(1));
              if(sname=="muFup") sweights[0] *= (ev.g_w[4])/ev.g_w[0]*(normH->GetBinContent(5)/normH->GetBinContent(1));
              if(sname=="muRmuFup") sweights[0] *= (ev.g_w[6])/ev.g_w[0]*(normH->GetBinContent(7)/normH->GetBinContent(1));
            
              if(sname=="muRdn") sweights[0] *= (ev.g_w[3])/ev.g_w[0]*(normH->GetBinContent(4)/normH->GetBinContent(1));
              if(sname=="muFdn") sweights[0] *= (ev.g_w[5])/ev.g_w[0]*(normH->GetBinContent(6)/normH->GetBinContent(1));
              if(sname=="muRmuFdn") sweights[0] *= (ev.g_w[7])/ev.g_w[0]*(normH->GetBinContent(8)/normH->GetBinContent(1));
            }

            int nW = ev.g_npsw;
            //std::cout << "n of ps weights: " << nW  << std::endl;
            //std::cout << "ps weights nominal: " << ev.g_psw[0] << std::endl;
            //https://github.com/cms-sw/cmssw/blob/master/Configuration/Generator/python/PSweightsPythia/PythiaPSweightsSettings_cfi.py
            if(nW==46 && ev.g_psw[0]){
              if(sname=="isrup") sweights[0] *= (ev.g_psw[8])/ev.g_psw[0];
              if(sname=="fsrup") sweights[0] *= (ev.g_psw[9])/ev.g_psw[0];
              if(sname=="isrdn") sweights[0] *= (ev.g_psw[6])/ev.g_psw[0];
              if(sname=="fsrdn") sweights[0] *= (ev.g_psw[7])/ev.g_psw[0];
            }
            if(nW==24 && ev.g_psw[0]){
              std::cout << "no isr" << std::endl;
              if(sname=="fsrup") sweights[0] *= (ev.g_psw[5])/ev.g_psw[0];
              if(sname=="fsrdn") sweights[0] *= (ev.g_psw[6])/ev.g_psw[0];
            }

            if(mpp_bdt<6000 && !prepareTraining && !prepareProtonData) {
              ht.fill2D("BDToutput_th", reader->EvaluateMVA(method), is, sweights, cats);
              TString bdtname = "BDToutput_"+sname;
              ht.fill(bdtname, reader->EvaluateMVA(method), sweights, cats);
            }
          }
        }
      }
      
    }
  }

if(debug) std::cout << "closing files" << std::endl;
  //close input file
  f->Close(); 
  fakefile->Close();

  //save histos to file  
  fOut->cd();
  
  if( !(prepareProtonData || prepareTraining) ) {
    
    for (auto& it : ht.getPlots())  {
      if(it.second->GetEntries()==0) continue;
      it.second->SetDirectory(fOut); it.second->Write(); 
    }

    for (auto& it : ht.get2dPlots())  {
      if(it.second->GetEntries()==0) continue;
      it.second->SetDirectory(fOut); it.second->Write(); 
    }
  }
  //save ntuples w/ selected events to file
  
  if(!prepareProtonData) outTsel->Write();
  else pps_info->Write();
  
  fOut->Close();
  
}
