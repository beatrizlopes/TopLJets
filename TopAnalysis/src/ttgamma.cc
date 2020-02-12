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
#include "TopLJets2015/TopAnalysis/interface/ttgamma.h"
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


using namespace std;

#define ADDVAR(x,name,tree) tree->Branch(name,&x);

void RunTTGamma(TString filename,
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
  
  MiniEvent_t ev;

  //PREPARE OUTPUT
  TString baseName=gSystem->BaseName(outname); 
  TString dirName=gSystem->DirName(outname);
  TFile *fOut=TFile::Open(dirName+"/"+baseName,"RECREATE");
  fOut->cd();

  // TTree* outTsel = new TTree("sel","sel"); 
  //  TNtuple *outTsel=new TNtuple("sel","sel","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:ngamma:gammapt:gammaeta:gammaphi");

  //outTsel->SetDirectory(fOut);

  bool hasETrigger,hasMTrigger,hasMMTrigger,hasEETrigger,hasEMTrigger, hasATrigger;
  bool isSS=false,isSF=false, isA=false;
 
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
  if(filename.Contains("TTG")) {isSignal = true; std::cout << "analysing signal file" << std::endl;}
     
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
  ht.addHist("gammapt",         new TH1F("gammapt",        ";Photon transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lpeta",        new TH1F("lpeta",       ";Lepton 2 pseudo-rapidity;Events",10,0,2.5));
  Float_t mllbins[]={0,50,100,150,200,250,300,400,600};
  //ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",sizeof(mllbins)/sizeof(Float_t)-1,mllbins));
  ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",sizeof(mllbins)/sizeof(Float_t)-1,mllbins));
  Float_t drllbins[]={0,0.4,0.8,1.2,1.6,2,2.4,2.8,3.2,3.6,4,4.4,5,5.4,5.8,6};
  ht.addHist("drll",         new TH1F("drll",        ";#DeltaR(l,l');Events",sizeof(drllbins)/sizeof(Float_t)-1,drllbins));
  Float_t Mlbbins[]={0,20,40,60,80,100,120,140,160,180,220,260,300};
  ht.addHist("Mlb",         new TH1F("Mlb",        ";Invariant mass of lb ;Events",sizeof(Mlbbins)/sizeof(Float_t)-1,Mlbbins));
  ht.addHist("jet1pt",         new TH1F("jet1pt",        ";Leading jet transverse momentum [GeV] ;Events",50,0,250));
  Float_t ptbosonbins[]={0,25,50,75,100,125,150,175,200,225,250,300};
  ht.addHist("ptll",         new TH1F("ptll",        ";Transverse momentum [GeV];Events",sizeof(ptbosonbins)/sizeof(Float_t)-1,ptbosonbins));
  //  ht.addHist("phistar",      new TH1F("phistar",     ";Dilepton #phi^{*};Events",50,0,5000));
  // ht.addHist("costhetaCS",   new TH1F("costhetaCS",  ";Dilepton cos#theta^{*}_{CS};Events",50,-1,1));
  ht.addHist("met",          new TH1F("met",         ";Missing transverse energy [GeV];Events",50,0,250));

  Float_t deltaphibins[]={0,0.2,0.4,0.6,0.8,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
  ht.addHist("deltaphill",  new TH1F("deltaphill", ";#Delta#phi(l,l) [rad];Events",sizeof(deltaphibins)/sizeof(Float_t)-1,deltaphibins));
  //ht.addHist("acopl",        new TH1F("acopl",       ";Acoplanarity;Events",50,0,1.0));
      
//  ht.addHist("csirp",        new TH1F("csirp",       ";#xi = #deltap/p; Events",50,0,0.3) );
  // ht.addHist("xangle",       new TH1F("xangle",      ";Crossing angle; Events",10,100,200) );
  ht.addHist("h",        new TH1F("h",       ";h [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtb",        new TH1F("htb",       ";H_T (b) [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtj",        new TH1F("htj",       ";H_T (j) [GeV]; Events",50,0,80) );
  
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
      float gen_pt(-1),gen_m(-1),gen_dr(-1),gen_deltaphill(-1);
      std::vector<TString> gen_cats;
      bool isZ = false;
      
      if(!ev.isData){
        std::vector<Particle> genLeptons=selector.getGenLeptons(ev,20.,2.4);
	//std::vector<Particle> genPhotons=selector.getGenPhotons(ev,50.,2.5);
	//std::vector<Particle> genTops=selector.getGenTops(ev);
        
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
      hasATrigger=(selector.hasTriggerBit("HLT_Photon200_v", ev.triggerBits));
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
      leptons = selector.selLeptons(leptons,SelectionTool::LOOSE,SelectionTool::MVA90,20,2.4);
      std::vector<Particle> photons=selector.flaggedPhotons(ev);
      photons=selector.selPhotons(photons,SelectionTool::MVA90,leptons,200.,2.4);

      //jets
      std::vector<Jet> allJets = selector.getGoodJets(ev,30.,2.4,leptons,photons);

      if(!ev.isData) l1trigprefireProb=l1PrefireWR->getCorrection(allJets);
      //btagWgt= btvSF.getBtagWeightMethod1a(allJets,ev,"central");

      
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
      
      
      //apply selection
      TString selCat("");
      int selCode(0);
      if(leptons.size()<2) continue;
      if(photons.size()<1) continue;
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

      if(photons.size()>0) 
	{
	  isA=true;
	}
    
      //mtll=computeMT(ll,met);
    
      //further selection for dileptons
      if(selCode!=22 && mass<20) continue;
      isZ=( isSF && !isSS && fabs(mass-91)<15);
      //isA=(selCode==22);

      //check again origin of the boson in data to max. efficiency and avoid double counting
      if(ev.isData) {
	if(isA) {
          if( !selector.isPhotonPD() ) continue;
          if( !hasATrigger) continue;
	}
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

      ////////////////////
      // EVENT WEIGHTS //
      //////////////////

      EffCorrection_t trigSF(1.,0.); // = lepEffH.getTriggerCorrection(leptons,{},{},period);
      EffCorrection_t sel1SF(1.,0.),sel2SF(1.,0.);
      EffCorrection_t combinedESF(1.0,0.0), combinedMSF(1.0,0.0);
      if (!ev.isData) {
        
        // norm weight
        wgt  = (normH? normH->GetBinContent(1) : 1.0);
        
	if(isSignal) wgt = 1/ngen;

        // lepton trigger*selection weights
        if(selCode!=22){
          sel1SF = lepEffH.getOfflineCorrection(leptons[l1idx], period);
          sel2SF = lepEffH.getOfflineCorrection(leptons[l2idx], period);
        }/*else{
          sel1SF = lepEffH.getOfflineCorrection(photons[0], period);
	  }*/

	//for signal top pt weights        
   
	//b-fragmentation and semi-leptonic branching fractions
        bfragWgts[0] = computeBFragmentationWeight(ev,fragWeights["downFrag"]);
        bfragWgts[1] = computeBFragmentationWeight(ev,fragWeights["upFrag"]);
        //slbrWgts[0]  = computeSemilepBRWeight(ev,semilepBRwgts_["semilepbrDown"],0,false);
        //slbrWgts[1]  = computeSemilepBRWeight(ev,semilepBRwgts_["semilepbrUp"],0,false);

        wgt *= puWgts[0]*l1trigprefireProb.first*trigSF.first*sel1SF.first*sel2SF.first;
        
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
      ht.fill("gammapt",photons[0].Pt(), plotwgts, cats);       
      
      //      if(isSignal) ht.fill2D("mtt_vs_ytt",gen_mtt,gen_ytt, plotwgts, cats);
      ht.fill("scalarhtj",  scalarhtj,    plotwgts, cats);

      //      pps_info->Fill();

    }

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
  

  //save ntuples w/ selected events to file
  //outTsel->Write();

  //  pps_info->Write();
  fOut->Close();
}
