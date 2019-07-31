#include <TFile.h>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TSystem.h>
#include <TGraph.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>

#include "TopLJets2015/TopAnalysis/interface/CommonTools.h"
#include "TopLJets2015/TopAnalysis/interface/ExclusiveTop.h"
#include "TopQuarkAnalysis/TopTools/interface/MEzCalculator.h"

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

//#define ADDVAR(x,name,t,tree) tree->Branch(name,x,TString(name)+TString(t))

//
vector<double> attributeCombinatorialRPmass(TH1* n0, TH1* n1, TH1* xi0, TH1* xi1)
{
  double fake_M = 10000, fake_y = 10, new_fake_M = 0, new_fake_y = 0;

  vector<double> my;

  gRandom->SetSeed(0);
  vector<double> randomxi0;
  vector<double> randomxi1;

  //generate n random trks for each pixel                                                                                                   
  int nrandomtrks0 = (int)n0->GetRandom();
  int nrandomtrks1 = (int)n1->GetRandom();

  //generate a random xi for each trk                                                                                                       

  for(int itrk=0; itrk<(int)nrandomtrks0; itrk++)
    {
      randomxi0.push_back(xi0->GetRandom());
   
      for(int i=0; i<(int)nrandomtrks1; i++)
	{
	  randomxi1.push_back(xi1->GetRandom());
	}
    }

  for(int i=0;i<(int)nrandomtrks0; i++)
    {
      for(int j=0;j<(int)nrandomtrks1; j++)
	{
	  //for the 2 lists of xis calculate the fake reconstructed mass                                                                  
	  new_fake_M=0;
	  new_fake_M = 13000*TMath::Sqrt(randomxi0[i]*randomxi1[j]);
	  new_fake_y = 0.5*TMath::Log(randomxi0[i]/randomxi1[j]);
	  if(new_fake_M<fake_M) {fake_M = new_fake_M; fake_y = new_fake_y;}
  
	}
    }

  my.push_back(fake_M);
  my.push_back(fake_y);
  
  return my;
} //21May - edited 30Jul

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

  TNtuple *outTsel=new TNtuple("sel","sel","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:weight");
  outTsel->SetDirectory(fOut);

  bool hasETrigger,hasMTrigger,hasMMTrigger,hasEETrigger,hasEMTrigger; //hasATrigger;
  bool isSS=false,isSF=false; //isA;
  float beamXangle(0);
  int nRPtk(0),RPid[50];
  float RPfarcsi[50];//RPnearcsi[50];
  //vector<double> WGTS;

  //READ TREE FROM FILE
  TFile *f = TFile::Open(filename);  
  TH1 *triggerList=(TH1 *)f->Get("analysis/triggerList");
  TTree *t = (TTree*)f->Get("analysis/data");
  attachToMiniEventTree(t,ev,true);
  Int_t nentries(t->GetEntriesFast());
  if (debug) nentries = 10000; //restrict number of entries for testing
  t->GetEntry(0);

  cout << "...producing " << outname << " from " << nentries << " events" << endl;

  ////Get ntrks and csis from a data file
  TFile *fakefile = TFile::Open("/afs/cern.ch/work/b/bribeiro/ab05162/xiData.root");

  TH1* fake_mm_nfwdtrk0 = (TH1*)fakefile->Get("mm_23_ntkrp");
  TH1* fake_mm_nfwdtrk1 = (TH1*)fakefile->Get("mm_123_ntkrp");

  TH1* fake_mm_xi0 = (TH1*)fakefile->Get("mm_23_csirp");
  TH1* fake_mm_xi1 = (TH1*)fakefile->Get("mm_123_csirp");

  TH1* fake_em_nfwdtrk0 = (TH1*)fakefile->Get("em_23_ntkrp");
  TH1* fake_em_nfwdtrk1 = (TH1*)fakefile->Get("em_123_ntkrp");

  TH1* fake_em_xi0 = (TH1*)fakefile->Get("em_23_csirp");
  TH1* fake_em_xi1 = (TH1*)fakefile->Get("em_123_csirp");

  TH1* fake_ee_nfwdtrk0 = (TH1*)fakefile->Get("ee_23_ntkrp");
  TH1* fake_ee_nfwdtrk1 = (TH1*)fakefile->Get("ee_123_ntkrp");

  TH1* fake_ee_xi0 = (TH1*)fakefile->Get("ee_23_csirp");
  TH1* fake_ee_xi1 = (TH1*)fakefile->Get("ee_123_csirp");

  if (fake_mm_nfwdtrk0!=0 && fake_em_nfwdtrk1!=0 && fake_ee_xi0!=0 && fake_em_xi1!=0)
    {
      std::cout << "Read fwdtrk and xi distributions from file" << std::endl;
      fake_mm_nfwdtrk0->SetDirectory(0);
      fake_mm_nfwdtrk1->SetDirectory(0);
      fake_mm_xi0->SetDirectory(0);
      fake_mm_xi1->SetDirectory(0);
      fake_em_nfwdtrk0->SetDirectory(0);
      fake_em_nfwdtrk1->SetDirectory(0);
      fake_em_xi0->SetDirectory(0);
      fake_em_xi1->SetDirectory(0);
      fake_ee_nfwdtrk0->SetDirectory(0);
      fake_ee_nfwdtrk1->SetDirectory(0);
      fake_ee_xi0->SetDirectory(0);
      fake_ee_xi1->SetDirectory(0);
    }
     
  else std::cout << "Couldnt read nfwdtrks and xi histograms from file" << std::endl;                                                                                                                                                              
  fakefile->Close();

  /////////////

  //Check if its signal MC
  bool isSignal = false;
  if(filename.Contains("FPMC")) {isSignal = true; std::cout << "analysing signal file" << std::endl;}
  
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
  
  //BOOK HISTOGRAMS
  HistTool ht;
  ht.setNsyst(0);
  ht.addHist("puwgtctr",     new TH1F("puwgtctr",    ";Weight sums;Events",2,0,2));
  //ht.addHist("nvtx",         new TH1F("nvtx",        ";Vertex multiplicity;Events",50,0,100));
  ht.addHist("nlep",         new TH1F("nlep",        ";Lepton multipliciy;Events",3,2,5));
  ht.addHist("nljets",       new TH1F("nljets",      ";light jet multiplicity;Events",6,0,6)); 
  ht.addHist("nbjets",       new TH1F("nbjets",      ";b jet multiplicity;Events",5,0,5));
  ht.addHist("lmpt",         new TH1F("lmpt",        ";Lepton 1 transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lmeta",        new TH1F("lmeta",       ";Lepton 1 pseudo-rapidity;Events",10,0,2.5));
  ht.addHist("lppt",         new TH1F("lppt",        ";Lepton 2 transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lpeta",        new TH1F("lpeta",       ";Lepton 2 pseudo-rapidity;Events",10,0,2.5));
  //Float_t mllbins[]={0,20,50,60,70,75,85,90,95,100,105,115,125,200,300,500};
  //ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",sizeof(mllbins)/sizeof(Float_t)-1,mllbins));
  ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",50,0,500));
  ht.addHist("drll",         new TH1F("drll",        ";#DeltaR(l,l');Events",50,0,6));
  ht.addHist("Mlb",         new TH1F("Mlb",        ";Invariant mass of lb ;Events",50,0,300));
  ht.addHist("mRP",         new TH1F("mRP",        ";Mass of pp ;Events",50,0,5000));
  ht.addHist("yRP",         new TH1F("yRP",        ";Rapidity of pp ;Events",50,-4,4));
  ht.addHist("jet1pt",         new TH1F("jet1pt",        ";Leading jet transverse momentum [GeV] ;Events",50,0,250));

  Float_t ptbosonbins[]={0,25,50,75,100,150,200,250,500,750,1000};
  ht.addHist("ptll",         new TH1F("ptll",        ";Transverse momentum [GeV];Events",sizeof(ptbosonbins)/sizeof(Float_t)-1,ptbosonbins));
  //  ht.addHist("phistar",      new TH1F("phistar",     ";Dilepton #phi^{*};Events",50,0,5000));
  // ht.addHist("costhetaCS",   new TH1F("costhetaCS",  ";Dilepton cos#theta^{*}_{CS};Events",50,-1,1));
  ht.addHist("met",          new TH1F("met",         ";Missing transverse energy [GeV];Events",50,0,250));

  Float_t deltaphibins[]={0,0.2,0.4,0.6,0.8,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
  ht.addHist("deltaphill",  new TH1F("deltaphill", ";#Delta#phi(l,l) [rad];Events",sizeof(deltaphibins)/sizeof(Float_t)-1,deltaphibins));
  //ht.addHist("acopl",        new TH1F("acopl",       ";Acoplanarity;Events",50,0,1.0));
  ht.addHist("ntkrp",        new TH1F("ntkrp",       ";Track multiplicity; Events",6,0,6) );
  ht.addHist("csirp",        new TH1F("csirp",       ";#csi = #deltap/p; Events",50,0,0.3) );
  // ht.addHist("xangle",       new TH1F("xangle",      ";Crossing angle; Events",10,100,200) );
  ht.addHist("h",        new TH1F("h",       ";h [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtb",        new TH1F("htb",       ";H_T (b) [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtj",        new TH1F("htj",       ";H_T (j) [GeV]; Events",50,0,80) );

  ht.addHist("evyields",     new TH1F("evyields",    ";Category; Events",6,0,6) );
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(1,"inc");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(2,"#geq1b");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(3,"lowMlb");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(4,"Z");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(5,"bb");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(6,"passmRP");
  ht.addHist("ratevsrun",    new TH1F("ratevsrun",   ";Run number; #sigma [pb]",int(lumiPerRun.size()),0,float(lumiPerRun.size())));

  ht.addHist("mrp_vs_mll",      new TH2F("mRP vs. m_{ll}",";m_{RP};m_{ll};Events",100,0,900,100,0,900));
  //ht.addHist("Mlb_minM_vs_minDeltaR",      new TH2F("Mlb min vs. Mlb minDeltaR",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));

  int i=0;
  for(auto key : lumiPerRun) {
    i++;
    ht.getPlots()["ratevsrun"]->GetXaxis()->SetBinLabel(i,Form("%d",key.first));
  }

  std::cout << "init done" << std::endl;
  if (debug){std::cout<<"\n DEBUG MODE"<<std::endl;}

  ///////////////////////
  // LOOP OVER EVENTS //
  /////////////////////
  
  //EVENT SELECTION WRAPPER
  SelectionTool selector(filename, false, triggerList);
  
  for (Int_t iev=0;iev<nentries;iev++)
    {
      t->GetEntry(iev);
      if(iev%1000==0) { printf("\r [%3.0f%%] done", 100.*(float)iev/(float)nentries); fflush(stdout); }

      //particle level dilepton or photon
      std::vector<double> trivialwgts(1,1.0);
      float gen_pt(-1),gen_m(-1),gen_dr(-1),gen_deltaphill(-1),gen_mtt(-1),gen_ytt(-1);
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
      float wgt(1.0);
      std::vector<double>plotwgts(1,wgt);
      double puWgt(1.0);
      TString period = lumi.assignRunPeriod();
      if(!ev.isData){
        ht.fill("puwgtctr",0,plotwgts);
        puWgt=(lumi.pileupWeight(ev.g_pu,period)[0]);
        std::vector<double>puPlotWgts(1,puWgt);
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
      leptons = selector.selLeptons(leptons,SelectionTool::LOOSE,SelectionTool::MVA90,20,2.5);
      //std::vector<Particle> photons=selector.flaggedPhotons(ev);
      //photons=selector.selPhotons(photons,SelectionTool::MVA90,leptons,200.,2.4);

      //jets
      std::vector<Jet> allJets = selector.getGoodJets(ev,30.,2.4,leptons); //,photons);

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

/*else if(photons.size()>0l) 
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
      
      TLorentzVector lb_min(0,0,0,0);      
      TLorentzVector lb_minDeltaR(0,0,0,0);      
      double minDeltaR = 0;
      
      //Compute lb_min and lb_with_min_deltaR
      if(bJets.size()>0)
	{
	  lb_min = leptons[0]+bJets[0];
	  minDeltaR = leptons[0].DeltaR(bJets[0]);
	  lb_minDeltaR = leptons[0]+bJets[0];
	  for(size_t i=0;i<leptons.size();i++)
	    {
	      for(size_t j=0;j<bJets.size();j++)
		{
		  TLorentzVector lb = leptons[i]+bJets[j];
		  //		   if(debug) cout << "lb mass" << lb.M() << endl;
		  if(lb.M()<lb_min.M())
		    lb_min=lb;
		  double deltaR = leptons[i].DeltaR(bJets[j]);
		  if(deltaR<minDeltaR){
		    minDeltaR = deltaR;
		    lb_minDeltaR=lb;
		  }
		}
	    }
	}
    
      //compute hadronic recoil
      TLorentzVector h = met+ll;
      for(size_t i=0; i<bJets.size();i++)
	{
	  if(i<3) 
	    h+=bJets[i];
	};

      //baseline categories and additional stuff produced with the dilepton
      std::vector<TString> cats(1,selCat);
      TString additionalcat = "";
      //if(ll.Pt()>50) {additionalcat+="_highpt";
      //	cats.push_back(selCat+additionalcat);}
      
      if(bJets.size()>0) {additionalcat+="_1b";
	cats.push_back(selCat+additionalcat);}      

      //if(bJets.size()>1) {additionalcat+="_2b";
      // cats.push_back(selCat+additionalcat);}      

      if(isSF && !isZ) {additionalcat+="_notZ";
        cats.push_back(selCat+additionalcat);}

      if(isZ) {additionalcat+="_Zpeak";
        cats.push_back(selCat+additionalcat);}
      
      if(bJets.size()>0 && lb_min.M()<160) {additionalcat+="_lowMlb";      
	cats.push_back(selCat+additionalcat);}

      else if(bJets.size()>0 && lb_min.M()>=160) {additionalcat+="_highMlb";
	  cats.push_back(selCat+additionalcat);}

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
    
      ////////////////////
      // EVENT WEIGHTS //
      //////////////////
      if (!ev.isData) {
        
        // norm weight
        wgt  = (normH? normH->GetBinContent(1) : 1.0);
        
        // lepton trigger*selection weights
        EffCorrection_t trigSF(1.,0.); // = lepEffH.getTriggerCorrection(leptons,{},{},period);
        EffCorrection_t sel1SF(1.,0.),sel2SF(1.,0.);
        if(selCode!=22){
          sel1SF = lepEffH.getOfflineCorrection(leptons[l1idx], period);
          sel2SF = lepEffH.getOfflineCorrection(leptons[l2idx], period);
        }/*else{
          sel1SF = lepEffH.getOfflineCorrection(photons[0], period);
	  }*/

        wgt *= puWgt*trigSF.first*sel1SF.first*sel2SF.first;
        
        // generator level weights
        wgt *= (ev.g_nw>0 ? ev.g_w[0] : 1.0);
        
        //update weight for plotter
        plotwgts[0]=wgt;
	//WGTS.push_back(plotwgts[0]);      
      }
        
      //control histograms
      //ht.fill("nvtx",       ev.nvtx,         plotwgts, cats);
      
      //event yields
      ht.fill("evyields",  0,  plotwgts, cats);

      //dilepton system
      ht.fill("nlep",       leptons.size(),  plotwgts, cats);
      
      if(bJets.size()>0) {
	ht.fill("evyields",  1,  plotwgts, cats);
	ht.fill("Mlb", lb_min.M(),  plotwgts, cats);
	if(lb_min.M()<160)  ht.fill("evyields",  2,  plotwgts, cats);
	if(bJets.size()>1)  ht.fill("evyields",  4,  plotwgts, cats);
	//ht.fill("Mlb_minDeltaR",lb_minDeltaR.M(), plotwgts, cats);
	//ht.fill2D("Mlb_minM_vs_minDeltaR",lb_min.M(),lb_minDeltaR.M(), plotwgts, cats);
	ht.fill("jet1pt", allJets[0].Pt(),  plotwgts, cats);
      }

      ht.fill("lmpt",       lm.Pt(),         plotwgts, cats);
      //ht.fill("lmeta",      fabs(lm.Eta()),  plotwgts, cats);
      ht.fill("lppt",       lp.Pt(),         plotwgts, cats);
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
      ht.fill("scalarhtj",  scalarhtj,    plotwgts, cats);
      /*for(auto &l:lightJets) {
        ht.fill("jpt",     l.Pt(),           plotwgts, cats);
        ht.fill("jeta",    fabs(l.Eta()),    plotwgts, cats);
	}*/
        
      //photons
      /*ht.fill("npho",       photons.size(),  plotwgts, cats);
	for(auto &a:photons) {
        ht.fill("apt",     a.Pt(),           plotwgts, cats);
        ht.fill("aeta",    fabs(a.Eta()),    plotwgts, cats);
	}*/
      
      ht.fill("h", h.Pt(), plotwgts, cats);  
      ht.fill("met",           met.Pt(),    plotwgts, cats);
      //ht.fill("mindphijmet",   mindphijmet, plotwgts, cats);
      //ht.fill("nch",           ev.pf_ch_wgtSum,         plotwgts, cats);
        
      //fill data with roman pot information
       
      nRPtk=0;
      double goodmRP=10000, goodyRP=10;	  
      int ncomptrks=0;
      bool passRPcut = false;            

      if(!ev.isData && !isSignal) 
	{
	  ////////////////////////
	  vector<double> MY;
	  if(selCode==13*13) MY = attributeCombinatorialRPmass(fake_mm_nfwdtrk0, fake_mm_nfwdtrk1, fake_mm_xi0, fake_mm_xi1);
	  if(selCode==11*13) MY = attributeCombinatorialRPmass(fake_em_nfwdtrk0, fake_em_nfwdtrk1, fake_em_xi0, fake_em_xi1);
	  if(selCode==11*11) MY = attributeCombinatorialRPmass(fake_ee_nfwdtrk0, fake_ee_nfwdtrk1, fake_ee_xi0, fake_ee_xi1);
	  goodmRP=MY[0];
	  goodyRP=MY[1];
	}

      if (ev.isData || isSignal) {
        
        //reset information
        for(size_t irp=0; irp<50; irp++) { 
          RPid[irp]=0; 
          RPfarcsi[irp]=0; 
          //RPnearcsi[irp]=0; 
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
          if((beamXangle==120 || beamXangle==130 || beamXangle==140 || beamXangle==150) || isSignal) {

            std::vector< std::pair<int,float> > nearCsis;
	    std::vector<double> farCsi0, farCsi1;
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
		//RPnearcsi[nRPtk]=0;              
		nRPtk++;
		if(pot_raw_id == 23) farCsi0.push_back(xi);
		if(pot_raw_id == 123) farCsi1.push_back(xi);
		
		//monitor track multiplicity and csi values
		if(ntks.find(pot_raw_id)==ntks.end()) ntks[pot_raw_id]=0;

		ntks[pot_raw_id]++;
		ht.fill("csirp",xi,plotwgts, Form("%s_%d",selCat.Data(),pot_raw_id));
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
              //RPnearcsi[matchTk]=stk.second;
            }
          
	    // mRP = 13000*sqrt(pixel0_xi[i]*pixel1_xi[j])
	    // yRP = 0.5*TMath::Log(pixel0_xi[i]/pixel1_xi[j])

	    goodmRP = 10000;
	    goodyRP = 10;

	    for(int i=0; i<ntks[23];i++)
	      {
		for(int j=0;j<ntks[123];j++)
		  {
		    double mRP = 13000*sqrt(farCsi0[i]*farCsi1[j]);
		    double yRP = 0.5*TMath::Log(farCsi0[i]/farCsi1[j]);////		    
		    if(mRP<goodmRP) {goodmRP=mRP; goodyRP=yRP;}
		    ncomptrks++;		    
		  }
	      }
	    
	    std::cout << "mrp: " << goodmRP << std::endl;
	    	    
            for(auto nit : ntks) 
              ht.fill("ntkrp", nit.second, plotwgts, Form("%s_%d",selCat.Data(),nit.first));
          }

	}catch(...){
        }
      }

      //added 14 Jul
      if(goodmRP<600 && goodmRP>300) passRPcut = true;		    

      if(passRPcut)
	{
	  /////////////////////////////////////////////////////////
	  ht.fill("evyields",  5,  plotwgts, cats);
	  additionalcat+="_RPcut";
	  cats.push_back(selCat+additionalcat);
	  ht.fill2D("mrp_vs_mll", goodmRP, ll.M(), plotwgts, cats);
	}///////////////////////


      if(goodmRP<5000 && goodmRP>0)
	{
	  ht.fill("mRP", goodmRP, plotwgts, cats);
	  ht.fill("yRP", goodyRP, plotwgts, cats);	    
	}      

      if(bJets.size()>1 && lb_min.M()<160)
	{

	  //compute some other variables
	  float px2=(bJets[0].Px()+bJets[1].Px()+leptons[0].Px()+leptons[1].Px()+met.Px())*(bJets[0].Px()+bJets[1].Px()+leptons[0].Px()+leptons[1].Px()+met.Px());
	  float py2=(bJets[0].Py()+bJets[1].Py()+leptons[0].Py()+leptons[1].Py()+met.Py())*(bJets[0].Py()+bJets[1].Py()+leptons[0].Py()+leptons[1].Py()+met.Py());
	  float pz2=(bJets[0].Pz()+bJets[1].Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz())*(bJets[0].Pz()+bJets[1].Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz());
	  float E2=(bJets[0].E()+bJets[1].E()+leptons[0].E()+leptons[1].E()+met.Pt())*(bJets[0].E()+bJets[1].E()+leptons[0].E()+leptons[1].E()+met.Pt());
	    
	  float yvis=(bJets[0]+bJets[1]+leptons[0]+leptons[1]).Rapidity();
	  float	ysum=fabs(bJets[0].Rapidity())+fabs(bJets[1].Rapidity())+fabs(leptons[0].Rapidity())+fabs(leptons[1].Rapidity());
	  float max_dy= max(fabs((bJets[0]+leptons[0]).Rapidity())-fabs((bJets[1]+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((bJets[1]+leptons[0]).Rapidity()));
          float	min_dy=min( fabs((bJets[0]+leptons[0]).Rapidity())-fabs((bJets[1]+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((bJets[1]+leptons[0]).Rapidity()));


	  //  TNtuple *outTsel=new TNtuple("sel","sel","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt");

	  Float_t varsel[]={(float)ev.run,
			    (float)ev.lumi,(float)ev.event,(float)ev.nvtx,(float)ev.rho,
			    (float)leptons[0].id()*leptons[1].id(),(float) ll.M(),(float)lightJets.size(), (float)bJets.size(), (float) scalarht, 
			    (float) met.Pt(),(float) met.Phi(),
			    (float) leptons[0].Pt(),(float)leptons[0].Eta(),(float)leptons[0].Phi(),(float)leptons[0].M(),(float)
			    leptons[1].Pt(),(float)leptons[1].Eta(),(float)leptons[1].Phi(),(float)leptons[1].M(),
			    (float) bJets[0].Pt(),(float)bJets[0].Eta(),(float)bJets[0].Phi(),(float)bJets[0].M(),(float)
			    bJets[1].Pt(),(float)bJets[1].Eta(),(float)bJets[1].Phi(),(float)bJets[1].M(),
			    px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,(float)
			    leptons[0].DeltaR(leptons[1]),(float) leptons[0].DeltaPhi(leptons[1]), (float) lb_min.M(), (float)			      
			    goodmRP,(float) goodyRP, (float) gen_mtt, (float) gen_ytt, (float) plotwgts[0]};
	  
	  outTsel->Fill(varsel);
	}
    }
  /*
  ofstream weightfile;
  weightfile.open("MCweights.txt");

  for(int i=0;i<(int)WGTS.size();i++)
    weightfile << i << " " << WGTS[i] << "\n";

  weightfile.close();
  */
  //close input file
  f->Close();
  
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

  outTsel->Write();
  
  fOut->Close();
}
