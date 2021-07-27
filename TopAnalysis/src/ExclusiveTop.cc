#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TKey.h"
#include "TChain.h"
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
#include "TopLJets2015/TopAnalysis/interface/protonTrackRatios.h"

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

TString get_period_from_run(int runNumber) {

  TString period = "";

  if(runNumber>=297050&& runNumber<=299329) period = "B";
  else if(runNumber>=299368&& runNumber<=302029) period = "C";
  else if(runNumber>=302031&& runNumber<=302663) period = "D";
  else if(runNumber>=303825&& runNumber<=304797) period = "E";
  else if(runNumber>=305044&& runNumber<=306460) period = "F";
  else period = "none";

  return period;
}

//run DESY KinReco top reconstruction algorithm
bool do_kin_reco(std::vector<Particle>& leptons, std::vector<Jet>& jets, std::vector<Jet>& bjets, TLorentzVector& met, Bool_t debug, double& kinReco_ttbar_mass, double& kinReco_ttbar_rapidity) {
    
    bool hasKinRecoSol = false;
    std::vector<TLorentzVector> allLeptons={};
    std::vector<TLorentzVector> allJets={};
    std::vector<TLorentzVector> allBJets={};

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

    //if(debug) std::cout << "now doing ttbar kinematic reconstruction" << std::endl;
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


/*std::vector<int> ComputeLBcombination(std::vector<Particle> leptons, std::vector<Jet> bJets)
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
*/

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
  TString data_path = Form("%s/src/TopLJets2015/TopAnalysis/data/era2017/", CMSSW_BASE);
  const char* data_path_char = (const char*) data_path;

  float run_bdt, lumi_bdt, event_bdt, rho_bdt, mpp_bdt, mtt_bdt, ypp_bdt, ytt_bdt, yvis_bdt, 
    deltarll_bdt, mll_bdt,
    ysum_bdt,  min_dy_bdt, nljets_bdt, metpt_bdt, E2_bdt, deltaphibb_bdt,
    extra_ysum_bdt, nprotons_bdt, extrasystem_y_bdt;
  //metphi_bdt,

  TMVA::Tools::Instance();
  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TString method =  "BDT method";
  
  if(!prepareTraining && !prepareProtonData) {
  
    std::cout << "==> Start TMVA Reader" << std::endl;

    //NEW SET OF VARIABLES

    reader->AddSpectator("run",&run_bdt);
    reader->AddSpectator("lumi",&lumi_bdt);
    reader->AddSpectator("ev",&event_bdt);
    reader->AddSpectator("rho",&rho_bdt);
    reader->AddSpectator("nprotons",&nprotons_bdt);

    reader->AddVariable("mpp",&mpp_bdt);
    reader->AddVariable("kinreco_mtt",&mtt_bdt);
    reader->AddVariable("ypp",&ypp_bdt);
    reader->AddVariable("kinreco_ytt",&ytt_bdt);

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

    /*    reader->AddVariable("nbjets",&nbjetsbdt);
	  reader->AddVariable("ht", &ht_bdt);*/
    reader->AddVariable("extra_ysum", &extra_ysum_bdt);
    reader->AddVariable("extrasystem_y", &extrasystem_y_bdt);
    
    reader->BookMVA( "BDT method", "/eos/user/b/bribeiro/exclusiveTTBarDilepton/BDTTrainingResults/TMVAClassification_BDT_only2protons.weights.xml");
  }


  //book PPS efficiency files
  PPSEff *PPS_reco = new PPSEff(Form("%s/src/TopLJets2015/TopAnalysis/data/era2017/reco_charactersitics_version1.root", CMSSW_BASE));
  PPSEff *MultiRP_eff = new PPSEff("/eos/project/c/ctpps/subsystems/Pixel/RPixTracking/pixelEfficiencies_multiRP.root");
  PPSEff *Strip_eff = new PPSEff(Form("%s/PreliminaryEfficiencies_March302021_1D2DMultiTrack.root",data_path_char));
  MiniEvent_t ev;

  //PREPARE OUTPUT
  TString baseName=gSystem->BaseName(outname); 
  TString dirName=gSystem->DirName(outname);
  TFile *fOut=TFile::Open(dirName+"/"+baseName,"RECREATE");
  fOut->cd();

  //create output tree
  TNtuple *outTsel=new TNtuple("sel","sel","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:extrasystem_y:extra_ysum:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:kinreco_mtt:kinreco_ytt:weight:nprotons");
  outTsel->SetDirectory(fOut);

  // BOOK PROTON TREE (DATA ONLY)
  TTree *outPT=new TTree("protons","protons");
  float m_protonVars_p1_xi=0, m_protonVars_p2_xi=0, protonvars_nBjets=0;
  int protonvars_beamXangle = 0;
  int protonvars_run = 0;
  int protonvars_event = 0, protonvars_lumi = 0, protonvars_nvtx = 0;
  float protonvars_rho = 0;
  int protonvars_nchPV = 0;

  outPT->Branch("run",&protonvars_run);
  outPT->Branch("event",&protonvars_event);
  outPT->Branch("lumi",&protonvars_lumi);
  outPT->Branch("nvtx",&protonvars_nvtx);
  outPT->Branch("rho",&protonvars_rho);
  outPT->Branch("nchPV",&protonvars_nchPV);
  outPT->Branch("beamXangle",&protonvars_beamXangle);
  outPT->Branch("p1_xi",&m_protonVars_p1_xi);
  outPT->Branch("p2_xi",&m_protonVars_p2_xi);
  outPT->Branch("nBjets",&protonvars_nBjets);
  
  outPT->SetDirectory(fOut);  
  
  bool hasETrigger,hasMTrigger,hasMMTrigger,hasEETrigger,hasEMTrigger; //hasATrigger;
  bool isSS=false,isSF=false; //isA;
  int beamXangle(0);
  int nRPtk(0);//RPid[50];
  //float RPfarcsi[50]:// RPnearcsi[50];

  L1PrefireEfficiencyWrapper* l1PrefireWR = new L1PrefireEfficiencyWrapper(filename.Contains("Data13TeV"),era);

  //READ TREE FROM FILE
  TFile *f = TFile::Open(filename);  
  TH1 *triggerList=(TH1 *)f->Get("analysis/triggerList");
  TH1 *counter=(TH1 *)f->Get("analysis/counter");
  TTree *t = (TTree*)f->Get("analysis/tree");
  TH2F *RPcount=(TH2F *)f->Get("analysis/RPcount");
  
  TH1F * mc_pu = new TH1F("mc_pu",";nvtx;w",100,0,100);
  t->Draw("nvtx>>mc_pu","","norm");
  mc_pu->SetDirectory(fOut);

  attachToMiniEventTree(t,ev);
  Int_t nentries(t->GetEntriesFast());
  //int entrynumber = -1;
  if (debug) nentries = 5000; //restrict number of entries for testing
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

  // NEW code, create pools from the data files, calculate relative cross-sections and nvtx distributions (era,xangle)
  // Read data, prerare PU trees:
  float era_lumi[] = {2.360910165,8.577154400,4.074834625,1.440661783,13.219864250};

  TString era_period[] = {"2017B","2017C","2017D","2017E","2017F"}; int n_era = (sizeof(era_period)/sizeof(TString));
  int xangle[] = {120, 130, 140, 150}; int n_xa = (sizeof(xangle)/sizeof(int));
   
  const int n_PUregionsMAX = n_era * n_xa; // used in signal normalization
  // Extra normalization factor used for signal since we have dedicated signal samples per era/xangle
  float signal_fraction_regions[n_PUregionsMAX], extra_signal_normalization=0;
  float sig_total_event_per_era[n_PUregionsMAX];

  if(isSignal){
       
    //Get extra normalization
    for(int i_era=0;i_era<n_era;i_era++){

      const char* inDataDir = "/afs/cern.ch/user/b/bribeiro/CMSSW_10_6_16/src/TopLJets2015/TopAnalysis/data/";

      TString name_el = Form("%s/Data13TeV_SingleElectron_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_mu = Form("%s/Data13TeV_SingleMuon_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_elmu = Form("%s/Data13TeV_MuonEG_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_mumu = Form("%s/Data13TeV_DoubleMuon_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_elel = Form("%s/Data13TeV_DoubleEG_%s_0.root",inDataDir,era_period[i_era].Data());

      for(int i_xa=0;i_xa<n_xa;i_xa++){ // create proton pools
	// calculate fraction of Xangle at preselection fpr ALL REGIONS:
	TChain * _ch2 = new TChain("protons"); _ch2->Add(name_el); _ch2->Add(name_mu); _ch2->Add(name_elmu); _ch2->Add(name_mumu);_ch2->Add(name_elel);
	signal_fraction_regions[i_era*n_xa+i_xa] = _ch2->GetEntries(Form("beamXangle==%d",xangle[i_xa]));
	sig_total_event_per_era[i_era*n_xa+i_xa]=_ch2->GetEntries();
      }
      // normalize properly per selected crossing-angle (sometimes data contains unselected values lke 141,142...)
      for(int ii=0;ii<n_xa;ii++) signal_fraction_regions[i_era*n_xa+ii] *= (era_lumi[i_era]/29.673425)/sig_total_event_per_era[i_era*n_xa+ii];
    }

    // reduce the number of regions in case if the sample is a simulated signal
      
    // set crossing angle
    int i_xa = 0;
    if(filename.Contains("xa120")) {xangle[0] = 120; i_xa=0;}
    if(filename.Contains("xa130")) {xangle[0] = 130; i_xa=1;}
    if(filename.Contains("xa140")) {xangle[0] = 140; i_xa=2;}
    if(filename.Contains("xa150")) {xangle[0] = 150; i_xa=3;}  

    // set list of periods
    if(filename.Contains("postTS2")){
      n_era = 2;
      era_lumi[0] = era_lumi[3]; era_period[0] = "2017E";
      era_lumi[1] = era_lumi[4]; era_period[1] = "2017F";
      for(int i_era=3;i_era<5;i_era++)
	     extra_signal_normalization += signal_fraction_regions[i_era*n_xa+i_xa];
    }
    else {
      n_era = 3; // for preTS2 first 3 entries are the same
      for(int i_era=0;i_era<3;i_era++)
	     extra_signal_normalization += signal_fraction_regions[i_era*n_xa+i_xa];
    }
      
    // set to 1 the crossing angle counter
    n_xa=1; 
  }
 
  const int n_PUregions = n_era * n_xa;
  // pileup histograms (used for reweighting)
  
  TString reduced_filename = filename.ReplaceAll(".root","");
  const char* pu_weights_filename = (const char*) reduced_filename.ReplaceAll("36e1539","pu_weights_files");

  float total_lumi=0;
  for(int i_era=0;i_era<n_era;i_era++) total_lumi+=era_lumi[i_era];

  float total_event_per_era[n_PUregions];
  float norm_weight[n_PUregions], norm_weight_err[n_PUregions], fraction_regions[n_PUregions]; int counter_regions[n_PUregions];
  float norm_weight_0p[n_PUregions], norm_weight_0p_err[n_PUregions]; // for signal events
  float norm_weight_1pRP0[n_PUregions], norm_weight_1pRP0_err[n_PUregions]; // for signal events
  float norm_weight_1pRP1[n_PUregions], norm_weight_1pRP1_err[n_PUregions]; // for signal events

  TTree * PUpr_read[n_PUregions];
  TH1F* pu_weights_read[n_PUregions];
  
  // variables to be used to read from PU pools
  int poll_run[n_PUregions]; float poll_p1_xi[n_PUregions],poll_p2_xi[n_PUregions];

  // Parameters for randomizing the proton mixing
  int rndSeed = 1234567890;   
  TRandom3 *rand_gen = new TRandom3(rndSeed);
  protonTrackRatios ptr;
  
  if(!ev.isData) {

    TFile * _puweights = new TFile(Form("%s_pu_weights.root",pu_weights_filename),"recreate"); // dummy file for protons pools to be associated with  

    TH1F * pu_weights[n_PUregions];
    
    TTree * PUpr[n_PUregions];

    for(int i_era=0;i_era<n_era;i_era++){
      
      const char* inDataDir = "/afs/cern.ch/user/b/bribeiro/CMSSW_10_6_16/src/TopLJets2015/TopAnalysis/data/";
      
      TString name_el = Form("%s/Data13TeV_SingleElectron_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_mu = Form("%s/Data13TeV_SingleMuon_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_elmu = Form("%s/Data13TeV_MuonEG_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_mumu = Form("%s/Data13TeV_DoubleMuon_%s_0.root",inDataDir,era_period[i_era].Data());
      TString name_elel = Form("%s/Data13TeV_DoubleEG_%s_0.root",inDataDir,era_period[i_era].Data());
       
      // Read 2 proton hits and total number of events
      int n_p2_e = int(((TH1F*)TFile::Open(name_el)->Get("evt_count"))->GetBinContent(4));
      int n_p2_m = int(((TH1F*)TFile::Open(name_mu)->Get("evt_count"))->GetBinContent(4));
      int n_p2_em = int(((TH1F*)TFile::Open(name_elmu)->Get("evt_count"))->GetBinContent(4));
      int n_p2_mm = int(((TH1F*)TFile::Open(name_mumu)->Get("evt_count"))->GetBinContent(4));
      int n_p2_ee = int(((TH1F*)TFile::Open(name_elel)->Get("evt_count"))->GetBinContent(4));

      int n_e = int(((TH1F*)TFile::Open(name_el)->Get("evt_count"))->GetBinContent(3));
      int n_m = int(((TH1F*)TFile::Open(name_mu)->Get("evt_count"))->GetBinContent(3));
      int n_em = int(((TH1F*)TFile::Open(name_elmu)->Get("evt_count"))->GetBinContent(3));
      int n_mm = int(((TH1F*)TFile::Open(name_mumu)->Get("evt_count"))->GetBinContent(3));
      int n_ee = int(((TH1F*)TFile::Open(name_elel)->Get("evt_count"))->GetBinContent(3));

      int n_p2 = (n_p2_e+n_p2_m+n_p2_em+n_p2_mm+n_p2_ee), n = (n_e+n_m+n_em+n_mm+n_ee);
       
      // Get systematics for n_proton==2 event fraction from sub-selection of nBjet>0 events:
      int n_e_sys = int(((TH1F*)TFile::Open(name_el)->Get("pn_count"))->GetBinContent(5));
      int n_m_sys = int(((TH1F*)TFile::Open(name_mu)->Get("pn_count"))->GetBinContent(5));
      int n_em_sys = int(((TH1F*)TFile::Open(name_elmu)->Get("pn_count"))->GetBinContent(5));
      int n_mm_sys = int(((TH1F*)TFile::Open(name_mumu)->Get("pn_count"))->GetBinContent(5));
      int n_ee_sys = int(((TH1F*)TFile::Open(name_elel)->Get("pn_count"))->GetBinContent(5));

      TChain * _ch_protons = new TChain("protons");
      _ch_protons->Add(name_el);
      _ch_protons->Add(name_mu);
      _ch_protons->Add(name_elmu);
      _ch_protons->Add(name_mumu);
      _ch_protons->Add(name_elel);
      
      int n_sys = (n_e_sys+n_m_sys+n_em_sys+n_mm_sys+n_ee_sys), n_p2_sys = _ch_protons->GetEntries("nBjets>0");
       
      // Get 1 proton hits (depend on the arm)
      int n_p1_eRP0 = int(((TH1F*)TFile::Open(name_el)->Get("pn_count"))->GetBinContent(2));
      int n_p1_mRP0 = int(((TH1F*)TFile::Open(name_mu)->Get("pn_count"))->GetBinContent(2));
      int n_p1_emRP0 = int(((TH1F*)TFile::Open(name_elmu)->Get("pn_count"))->GetBinContent(2));
      int n_p1_mmRP0 = int(((TH1F*)TFile::Open(name_mumu)->Get("pn_count"))->GetBinContent(2));
      int n_p1_eeRP0 = int(((TH1F*)TFile::Open(name_elel)->Get("pn_count"))->GetBinContent(2));
      
      int n_p1_eRP1 = int(((TH1F*)TFile::Open(name_el)->Get("pn_count"))->GetBinContent(3));
      int n_p1_mRP1 = int(((TH1F*)TFile::Open(name_mu)->Get("pn_count"))->GetBinContent(3));
      int n_p1_emRP1 = int(((TH1F*)TFile::Open(name_elmu)->Get("pn_count"))->GetBinContent(3));
      int n_p1_mmRP1 = int(((TH1F*)TFile::Open(name_mumu)->Get("pn_count"))->GetBinContent(3));
      int n_p1_eeRP1 = int(((TH1F*)TFile::Open(name_elel)->Get("pn_count"))->GetBinContent(3));
      
      int n_p1_RP0 = (n_p1_eRP0+n_p1_mRP0+n_p1_emRP0+n_p1_mmRP0+n_p1_eeRP0), n_p1_RP1 = (n_p1_eRP1+n_p1_mRP1+n_p1_emRP1+n_p1_mmRP1+n_p1_eeRP1);
    
      // events with exactly 0 pu tracks
      int n_p0 = n - n_p1_RP0 - n_p1_RP1 - n_p2;

      for(int i_xa=0;i_xa<n_xa;i_xa++){ // create proton pools
	//TChain * _ch = new TChain("protons");
	//_ch->Add(name_el);
	//_ch->Add(name_mu);
	//_ch->Add(name_elmu);
	//_ch->Add(name_mumu);
	//_ch->Add(name_elel);
	
	_puweights->cd();

	PUpr[i_era*n_xa+i_xa] = (_ch_protons->CopyTree(Form("beamXangle==%d",xangle[i_xa])))->CloneTree();
	PUpr[i_era*n_xa+i_xa]->SetName(Form("protons_%d",i_era*n_xa+i_xa));
	pu_weights[i_era*n_xa+i_xa] = new TH1F(Form("data_puw_%d",i_era*n_xa+i_xa),";nvtx;w",100,0,100);
	PUpr[i_era*n_xa+i_xa]->Draw(Form("nvtx>>data_puw_%d",i_era*n_xa+i_xa));
	counter_regions[i_era*n_xa+i_xa] = PUpr[i_era*n_xa+i_xa]->GetEntries();
	pu_weights[i_era*n_xa+i_xa]->Scale(1/float(counter_regions[i_era*n_xa+i_xa]));
	
	// calculate fraction of Xangle at preselection:
	TChain * _ch3 = new TChain("protons"); _ch3->Add(name_el); _ch3->Add(name_mu); _ch3->Add(name_elmu); _ch3->Add(name_mumu); _ch3->Add(name_elel);
	fraction_regions[i_era*n_xa+i_xa] = _ch3->GetEntries(Form("beamXangle==%d",xangle[i_xa]));
	total_event_per_era[i_era*n_xa+i_xa] = isSignal ? fraction_regions[i_era*n_xa+i_xa] : _ch3->GetEntries();
	norm_weight[i_era*n_xa+i_xa] = n_p2/float(n); // probability of 2 tracks
	norm_weight_err[i_era*n_xa+i_xa] = (n_p2_sys/float(n_sys)) / norm_weight[i_era*n_xa+i_xa];
	
	// probabilities for 1 track in signal events
	norm_weight_1pRP0[i_era*n_xa+i_xa] = n_p1_RP0/float(n); // probability of 0 tracks in RP0
	norm_weight_1pRP0_err[i_era*n_xa+i_xa] = 0.95; // 5% flat
	
	norm_weight_1pRP1[i_era*n_xa+i_xa] = n_p1_RP1/float(n); // probability of 0 tracks in RP1
	norm_weight_1pRP1_err[i_era*n_xa+i_xa] = 0.95; // 5% flat
	
	// probabilities for 0 track in signal events
	norm_weight_0p[i_era*n_xa+i_xa] = (n_p0)/float(n); // probability of 0 tracks in both arms
	norm_weight_0p_err[i_era*n_xa+i_xa] = 0.95; // 5% flat
         
      }
      // normalize properly per selected crossing-angle (sometimes data contains unselected values lke 141,142...)
      for(int ii=0;ii<n_xa;ii++) fraction_regions[i_era*n_xa+ii] *= (era_lumi[i_era]/total_lumi)/total_event_per_era[i_era*n_xa+ii];
    }
   
    _puweights->cd();
    std::cout << "write " << _puweights->GetName()  << endl;
    for(int i=0;i<n_PUregions;i++) pu_weights[i]->Write();
    _puweights->Write();
    _puweights->Close();
  }
   
  TFile * _puweights_read = new TFile(Form("%s_pu_weights.root",pu_weights_filename),"read"); // dummy file for protons pools to be associated with 
  
  if(!ev.isData) {  
    std::cout << "read " << _puweights_read->GetName()  << endl;
    for(int i=0; i<n_PUregions;i++) {
      PUpr_read[i] = (TTree*)_puweights_read->Get(Form("protons_%d",i));
      pu_weights_read[i] = (TH1F*)_puweights_read->Get(Form("data_puw_%d",i));
    }

    for(int i=0;i<n_PUregions;i++){
      PUpr_read[i]->SetBranchAddress("run",&poll_run[i]);
      PUpr_read[i]->SetBranchAddress("p1_xi",&poll_p1_xi[i]);
      PUpr_read[i]->SetBranchAddress("p2_xi",&poll_p2_xi[i]);
    }

    // Get pileup proton ratios
    int nLines = ptr.readFromFile(Form("%s/protonRatios_2017.dat",data_path.Data()));
    if (nLines <= 0) {
      cout << "No true-zero-track ratio read from file! No mixing performed." << endl;
    }
    
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
  //JECTools jerTool_(era);  

  /// ISR/FSR Systematic variations, store as a vectors to account comp. split
  // total, [g2gg, g2qq, q2ga, x2xg] X [muR, cNS]. Q=uds, X=cb, NS=non-singular
  // see more info here: https://indico.cern.ch/event/746817/contributions/3101385/attachments/1702410/2742087/psweights_mseidel.pdf
  map<string,int> PSmap;
  // from https://github.com/cms-sw/cmssw/blob/master/Configuration/Generator/python/PSweightsPythia/PythiaPSweightsSettings_cfi.py
  PSmap["nominal"] = 0;
  PSmap["isrDefHi"] = 6;
  PSmap["fsrDefHi"] = 7;
  PSmap["isrDefLo"] = 8;
  PSmap["fsrDefLo"] = 9;
  PSmap["fsr_G2GG_muR_dn"] = 14;
  PSmap["fsr_G2GG_muR_up"] = 15;
  PSmap["fsr_G2QQ_muR_dn"] = 16;
  PSmap["fsr_G2QQ_muR_up"] = 17;
  PSmap["fsr_Q2QG_muR_dn"] = 18;
  PSmap["fsr_Q2QG_muR_up"] = 19;
  PSmap["fsr_X2XG_muR_dn"] = 20;
  PSmap["fsr_X2XG_muR_up"] = 21;
  PSmap["fsr_G2GG_cNS_dn"] = 22;
  PSmap["fsr_G2GG_cNS_up"] = 23;
  PSmap["fsr_G2QQ_cNS_dn"] = 24;
  PSmap["fsr_G2QQ_cNS_up"] = 25;
  PSmap["fsr_Q2QG_cNS_dn"] = 26;
  PSmap["fsr_Q2QG_cNS_up"] = 27;
  PSmap["fsr_X2XG_cNS_dn"] = 28;
  PSmap["fsr_X2XG_cNS_up"] = 29;
  PSmap["isr_G2GG_muR_dn"] = 30;
  PSmap["isr_G2GG_muR_up"] = 31;
  PSmap["isr_G2QQ_muR_dn"] = 32;
  PSmap["isr_G2QQ_muR_up"] = 33;
  PSmap["isr_Q2QG_muR_dn"] = 34;
  PSmap["isr_Q2QG_muR_up"] = 35;
  PSmap["isr_X2XG_muR_dn"] = 36;
  PSmap["isr_X2XG_muR_up"] = 37;
  PSmap["isr_G2GG_cNS_dn"] = 38;
  PSmap["isr_G2GG_cNS_up"] = 39;
  PSmap["isr_G2QQ_cNS_dn"] = 40;
  PSmap["isr_G2QQ_cNS_up"] = 41;
  PSmap["isr_Q2QG_cNS_dn"] = 42;
  PSmap["isr_Q2QG_cNS_up"] = 43;
  PSmap["isr_X2XG_cNS_dn"] = 44;
  PSmap["isr_X2XG_cNS_up"] = 45;

  //systematics from theory
  bool isTT = filename.Contains("TTJets");

  size_t nexpSysts = 0;
  size_t nweightSysts = 0;

  std::vector<TString> weightSystNames ={
			      "eselup",      "eseldn",
			      "mselup",      "mseldn",
			      "trigSFup",    "trigSFdn",
			      "l1prefireup", "l1prefiredn",
			      "protonTagup","protonTagdn",
			      "btaghfup",         "btaghfdn",
			      "btaglfup",         "btaglfdn"};
  
  weightSystNames.push_back("fsrG2GGmuRup");
  weightSystNames.push_back("fsrG2GGmuRdn");
  weightSystNames.push_back("fsrG2QQmuRup");
  weightSystNames.push_back("fsrG2QQmuRdn");
  weightSystNames.push_back("fsrQ2QGmuRup");
  weightSystNames.push_back("fsrQ2QGmuRdn");
  weightSystNames.push_back("fsrX2XGmuRup");
  weightSystNames.push_back("fsrX2XGmuRdn");  
  weightSystNames.push_back("fsrG2GGcNSup");
  weightSystNames.push_back("fsrG2GGcNSdn");
  weightSystNames.push_back("fsrG2QQcNSup");
  weightSystNames.push_back("fsrG2QQcNSdn");
  weightSystNames.push_back("fsrQ2QGcNSup");
  weightSystNames.push_back("fsrQ2QGcNSdn");
  weightSystNames.push_back("fsrX2XGcNSup");
  weightSystNames.push_back("fsrX2XGcNSdn");

  if(isSignal) {
    weightSystNames.push_back("ppsSFup");
    weightSystNames.push_back("ppsSFdn");
  }
  
  if(!isSignal) {
    weightSystNames.push_back("muRup");
    weightSystNames.push_back("muRdn");
    weightSystNames.push_back("muFup");
    weightSystNames.push_back("muFdn");
    weightSystNames.push_back("muRmuFup");
    weightSystNames.push_back("muRmuFdn");

    weightSystNames.push_back("pdfASup");
    weightSystNames.push_back("pdfHSup");
    weightSystNames.push_back("pdfASdn");
    weightSystNames.push_back("pdfHSdn");
  }

  if(isTT) { 
    
    //    weightSystNames.push_back("topptup");
    //weightSystNames.push_back("topptdn");

    weightSystNames.push_back("isrG2GGmuRup");
    weightSystNames.push_back("isrG2GGmuRdn");
    weightSystNames.push_back("isrG2QQmuRup");
    weightSystNames.push_back("isrG2QQmuRdn");
    weightSystNames.push_back("isrQ2QGmuRup");
    weightSystNames.push_back("isrQ2QGmuRdn");
    weightSystNames.push_back("isrX2XGmuRup");
    weightSystNames.push_back("isrX2XGmuRdn");
    weightSystNames.push_back("isrG2GGcNSup");
    weightSystNames.push_back("isrG2GGcNSdn");
    weightSystNames.push_back("isrG2QQcNSup");
    weightSystNames.push_back("isrG2QQcNSdn");
    weightSystNames.push_back("isrQ2QGcNSup");
    weightSystNames.push_back("isrQ2QGcNSdn");
    weightSystNames.push_back("isrX2XGcNSup");
    weightSystNames.push_back("isrX2XGcNSdn");
  }

  TString expSystNames[]={"nominal", //"puup",        "pudn",
			  "protonReco45up","protonReco45dn",
			  "protonReco56up","protonReco56dn",
                          "JERup",       "JERdn",
                          "bfragup", "bfragdn",
  			  "AbsJECup", "AbsJECdn",
			  "HighPtJECup", "HighPtJECdn",
			  "FlavorJECup", "FlavorJECdn",
			  "TimeJECup", "TimeJECdn",
			  "RelJECup", "RelJECdn",
			  "PileupJECup", "PileupJECdn",
			  "UnclMETup", "UnclMETdn"
  };

  nexpSysts = sizeof(expSystNames)/sizeof(TString);
  nweightSysts = weightSystNames.size();
  //std::cout << isTT << std::endl;

  //BOOK HISTOGRAMS
  HistTool ht;
  ht.setNsyst(0);
 
  ht.addHist("evt_count",    new TH1F("evt_count",   ";Selection Stage;Events",4,0,4));
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(1,"Total");
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(2,"Sumweighted");
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(3,"preselection");
  ht.getPlots()["evt_count"]->GetXaxis()->SetBinLabel(4,"=2 p (data)");
  ht.getPlots()["evt_count"]->SetBinContent(1,counter->GetBinContent(1));
  ht.getPlots()["evt_count"]->SetBinContent(2,counter->GetBinContent(2));
  ht.getPlots()["evt_count"]->SetBinContent(3,counter->GetBinContent(3));

  ht.addHist("pn_count",    new TH1F("pn_count",   ";;Events",5,0,5));
  ht.getPlots()["pn_count"]->GetXaxis()->SetBinLabel(1,"0 hits");
  ht.getPlots()["pn_count"]->GetXaxis()->SetBinLabel(2,"RP0 hit");
  ht.getPlots()["pn_count"]->GetXaxis()->SetBinLabel(3,"RP1 hit");
  ht.getPlots()["pn_count"]->GetXaxis()->SetBinLabel(4,"both RP");
  ht.getPlots()["pn_count"]->GetXaxis()->SetBinLabel(5,"pres + nB#geq1");
  int nbin = 0;
  nbin=RPcount->FindBin(0.5,0.5); ht.getPlots()["pn_count"]->SetBinContent(1,RPcount->GetBinContent(nbin));
  nbin=RPcount->FindBin(1.5,0.5); ht.getPlots()["pn_count"]->SetBinContent(2,RPcount->GetBinContent(nbin));
  nbin=RPcount->FindBin(0.5,1.5); ht.getPlots()["pn_count"]->SetBinContent(3,RPcount->GetBinContent(nbin));
  nbin=RPcount->FindBin(1.5,1.5); ht.getPlots()["pn_count"]->SetBinContent(4,RPcount->GetBinContent(nbin));
  ht.getPlots()["pn_count"]->SetBinContent(5,counter->GetBinContent(4));

  ht.addHist("puwgtctr",     new TH1F("puwgtctr",    ";Weight sums;Events",2,0,2));
  ht.addHist("nvtx",         new TH1F("nvtx",        ";Vertex multiplicity;Events",50,0,100));
  ht.addHist("nlep",         new TH1F("nlep",        ";Lepton multipliciy;Events",3,2,5));
  //ht.addHist("nljets",       new TH1F("nljets",      ";light jet multiplicity;Events",6,0,6)); 
  ht.addHist("nbjets",       new TH1F("nbjets",      ";b jet multiplicity;Events",5,0,5));
  ht.addHist("lmpt",         new TH1F("lmpt",        ";Lepton 1 transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lmeta",        new TH1F("lmeta",       ";Lepton 1 pseudo-rapidity;Events",10,0,2.5));
  ht.addHist("lppt",         new TH1F("lppt",        ";Lepton 2 transverse momentum [GeV];Events",56,20,300));
  //ht.addHist("lpeta",        new TH1F("lpeta",       ";Lepton 2 pseudo-rapidity;Events",10,0,2.5));
  //  Float_t mllbins[]={20,30,40,50,60,70,80,90,100,120,140,160,180,200,250,300,400,600};
  //ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",sizeof(mllbins)/sizeof(Float_t)-1,mllbins));
  ht.addHist("mll",          new TH1F("mll",         ";Dilepton invariant mass [GeV];Events",30,0,200));
  ht.addHist("drll",         new TH1F("drll",        ";#DeltaR(l,l');Events",50,0,5.));
  ht.addHist("mRP",         new TH1F("mRP",        ";di-proton mass [TeV] ;Events",25,0.4,1.8));
  ht.addHist("yRP",         new TH1F("yRP",        ";di-proton rapidity ;Events",25,-1,1));
  ht.addHist("jet1pt",         new TH1F("jet1pt",        ";Leading jet transverse momentum [GeV] ;Events",50,0,250));

  Float_t ptbosonbins[]={0,25,50,75,100,125,150,175,200,225,250,300};
  ht.addHist("ptll",         new TH1F("ptll",        ";Transverse momentum [GeV];Events",sizeof(ptbosonbins)/sizeof(Float_t)-1,ptbosonbins));
  //  ht.addHist("phistar",      new TH1F("phistar",     ";Dilepton #phi^{*};Events",50,0,5000));
  // ht.addHist("costhetaCS",   new TH1F("costhetaCS",  ";Dilepton cos#theta^{*}_{CS};Events",50,-1,1));
  ht.addHist("met",          new TH1F("met",         ";Missing transverse energy [GeV];Events",50,0,200));

  ht.addHist("E2",          new TH1F("E2",         ";E^2 [GeV];Events",30,0,10000));
  ht.addHist("yvis",          new TH1F("yvis",         ";ttbar system rapidity;Events",50,-2.2,2.2));
  ht.addHist("mindy",          new TH1F("mindy",         ";minimum delta y between (lepton,b-jet) ;Events",25,0,1.2));
  ht.addHist("ysum",          new TH1F("ysum",         ";sum of rapidity of ttbar decay products; Events",50,0,8));
  ht.addHist("extray_sum",          new TH1F("extray_sum",         ";sum of rapidities of extra (not ttbar) particles; Events",50,0,6));
  ht.addHist("extrasystem_y",          new TH1F("extrasystem_y",         ";rapidity of extra (not ttbar) system; Events",25,-1.8,1.8));

  Float_t deltaphibins[]={0,0.2,0.4,0.6,0.8,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
  ht.addHist("deltaphill",  new TH1F("deltaphill", ";#Delta#phi(l,l) [rad];Events",sizeof(deltaphibins)/sizeof(Float_t)-1,deltaphibins));
			ht.addHist("deltaphibb",  new TH1F("deltaphibb", ";#Delta#phi(b,b) [rad];Events",50,0,3.2));
  
//ht.addHist("acopl",        new TH1F("acopl",       ";Acoplanarity;Events",50,0,1.0));
  
  ht.addHist("ntkrp",        new TH1F("ntkrp",       ";Track multiplicity; Events",6,0,6) );
    
 //  ht.addHist("csirp",        new TH1F("csirp",       ";#xi = #deltap/p; Events",50,0,0.3) );
  // ht.addHist("xangle",       new TH1F("xangle",      ";Crossing angle; Events",10,100,200) );
  ht.addHist("h",        new TH1F("h",       ";h [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtb",        new TH1F("htb",       ";H_T (b) [GeV]; Events",50,0,80) );
  ht.addHist("scalarhtj",        new TH1F("htj",       ";H_T (j) [GeV]; Events",50,0,80) );
  
  ht.addHist("xi0",     new TH1F("xi0",    ";#xi_0; Events",20,0.01,0.14) );
  ht.addHist("xi1",     new TH1F("xi1",    ";#xi_1; Events",20,0.01,0.14) );

  ht.addHist("kin_reco_ttbar_mass",     new TH1F("kin_reco_ttbar_mass",    ";M_{ttbar}; Events",50,300,1500) );
  ht.addHist("kin_reco_ttbar_rapidity",     new TH1F("kin_reco_ttbar_rapidity",    ";y_{ttbar}; Events",50,-2.2,2.2) );

  ht.addHist("gen_ttbar_mass",     new TH1F("gen_ttbar_mass",    ";M_{ttbar}; Events",20,0,2000) );
  ht.addHist("gen_ttbar_rapidity",     new TH1F("gen_ttbar_rapidity",    ";y_{ttbar}; Events",20,-3,3) );

  ht.addHist("cutflow",     new TH1F("cutflow",    ";Category; Events",6,0,6) );

  ht.getPlots()["cutflow"]->GetXaxis()->SetBinLabel(1,"inc");
  ht.getPlots()["cutflow"]->GetXaxis()->SetBinLabel(2,"2lep");
  ht.getPlots()["cutflow"]->GetXaxis()->SetBinLabel(3,"2b");
  ht.getPlots()["cutflow"]->GetXaxis()->SetBinLabel(4,"notZ");
  ht.getPlots()["cutflow"]->GetXaxis()->SetBinLabel(5,"lowMlb");
  ht.getPlots()["cutflow"]->GetXaxis()->SetBinLabel(6,"2protons");

  ht.addHist("evyields",     new TH1F("evyields",    ";Category; Events",20,0,20) );

  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(1,"B120");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(2,"B130");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(3,"B140");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(4,"B150");

  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(5,"C120");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(6,"C130");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(7,"C140");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(8,"C150");

  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(9,"D120");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(10,"D130");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(11,"D140");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(12,"D150");

  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(13,"E120");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(14,"E130");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(15,"E140");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(16,"E150");

  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(17,"F120");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(18,"F130");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(19,"F140");
  ht.getPlots()["evyields"]->GetXaxis()->SetBinLabel(20,"F150");

  //  ht.addHist("Mlb_minM_vs_minDeltaR",      new TH2F("Mlb min vs. Mlb minDeltaR",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));
  //ht.addHist("Mlb_minM_vs_minDeltaR_match",      new TH2F("Mlb min vs. Mlb minDeltaR matched",";m_{lb} min ;m_{lb} min #Delta R;Events",100,0,300,100,0,300));

  ////////////////////////////////////////////////////////
  //instantiate BDToutput histogram to track with systs//
  //////////////////////////////////////////////////////
  
  TString hoi = "BDToutput";
  TString hoi2 = "nljets";
   
  //experimental systs  
  for(size_t is=0; is<nexpSysts; is++) {
    ht.addHist(hoi+"_"+expSystNames[is], new TH1F(hoi+"_"+expSystNames[is],    ";"+hoi+"_"+expSystNames[is]+"; Events",15,-1,0.5) );
    ht.addHist(hoi2+"_"+expSystNames[is], new TH1F(hoi2+"_"+expSystNames[is],    ";"+hoi2+"_"+expSystNames[is]+"; Events",6,0,6) );
  }

  //weight systs  
  for(size_t is=0; is<nweightSysts; is++) {
    ht.addHist(hoi+"_"+weightSystNames[is], new TH1F(hoi+"_"+weightSystNames[is],    ";"+hoi+"_"+weightSystNames[is]+"; Events",15,-1,0.5) );
    ht.addHist(hoi2+"_"+weightSystNames[is], new TH1F(hoi2+"_"+weightSystNames[is],    ";"+hoi2+"_"+weightSystNames[is]+"; Events",6,0,6) );
  }
       
  std::cout << "init done" << std::endl;
  if (debug){std::cout<<"\n DEBUG MODE"<<std::endl;}

  ////////////////////////////
  // Start event selection //
  //////////////////////////

  //EVENT SELECTION WRAPPER
  SelectionTool selector(filename, false, triggerList, SelectionTool::AnalysisType::TOP);

  ////////////////////////////
  /////START EVENT LOOP /////
  //////////////////////////

  for (Int_t iev=0;iev<nentries;iev++) {


    t->GetEntry(iev);
    if(iev%1000==0) { printf("\r [%3.0f%%] done", 100.*(float)iev/(float)nentries); fflush(stdout); }
      
    //save generator level info for ttbar system (mass and rapidity)
    float gen_mtt(-1),gen_ytt(-10);     
    int signal_protons = 0; // additional variables used for signal to indecate if all/part/none of the protons are from pileup  
      
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

    //count all events (no selection)
    ht.fill("evt_count", 3, trivialwgts);

    //pileup weights for MC
    if(!ev.isData){
      ht.fill("puwgtctr",0,plotwgts);
      puWgts=lumi.pileupWeight(ev.g_pu,period);
      std::vector<double>puPlotWgts(1,puWgts[0]);
      ht.fill("puwgtctr",1,puPlotWgts);
    }  

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
    leptons = selector.selLeptons(leptons,SelectionTool::TIGHT,SelectionTool::TIGHT,20,2.4);

    //met
    TLorentzVector nominalmet(0,0,0,0);
    nominalmet.SetPtEtaPhiM(ev.met_pt,0,ev.met_phi,0.);
    //

    //OFFLINE SELECTION(S)
    //
    //If we don't have 2 tight leptons, we don't consider the event:
    if(!prepareProtonData && leptons.size()!=2) continue;

    bool isTrigSafe = false;
    if(leptons.size()>1) isTrigSafe = (leptons[0].Pt()>30 && fabs(leptons[0].Eta())<2.1);
    
    //If we don't have lepton1pt>30 and lepton1eta<2.1, we don't consider the event:
    if(!prepareProtonData && !isTrigSafe) continue;

    TString selCat("");
    int selCode(0);

    //apply met filters
    //bool passMETfilters = ev.met_filterBits==0x3F;
    bool passMETfilters = ( ((ev.met_filterBits >> 3) & 0x1) && //Flag_goodVertices
			    ((ev.met_filterBits >> 5) & 0x1) && //Flag_globalSuperTightHalo2016Filter
			    ((ev.met_filterBits >> 0) & 0x1) && //Flag_HBHENoiseFilter
			    ((ev.met_filterBits >> 1) & 0x1) && //Flag_HBHENoiseIsoFilter
			    ((ev.met_filterBits >> 2) & 0x1) && //Flag_EcalDeadCellTriggerPrimitiveFilter
			    ((ev.met_filterBits >> 4) & 0x1) ); //Flag_eeB

    if(ev.isData && !prepareProtonData && !passMETfilters) continue;

    //set kinematics
    TLorentzVector ll(0,0,0,0);
    TLorentzVector lm(0,0,0,0),lp(0,0,0,0);
    float dilepton_mass(0);
    float dilepton_dr(0); //llht(0),mtll(0);

    if(!prepareProtonData) {
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
      if(isSF && isZ) continue;
      
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
      
    }
    
    EffCorrection_t trigSF(1.,0.);
    
    EffCorrection_t sel1SF(1.,0.),sel2SF(1.,0.);
    EffCorrection_t combinedESF(1.0,0.0), combinedMSF(1.0,0.0);

    if(!ev.isData) {
      
      //compute trigger SFs (to be updated to UL)
      if(!prepareProtonData) trigSF = lepEffH.getDileptonTriggerCorrection(leptons);
      // norm weight
      wgt = (normH? normH->GetBinContent(1) : 1.0);

      // generator level weights
      wgt *= (ev.g_nw>0 ? ev.g_w[0] : 1.0);
    
      //for ttbar compute top pt SF
      if(isTT) {
  
        topptWgts[0] = 1;

        for(Int_t igen=0; igen<ev.ngtop; igen++) {
          if(abs(ev.gtop_id[igen])!=6) continue;
          //double topsf=TMath::Exp(0.0615-0.0005*ev.gtop_pt[igen]);
          double topsf=0.103*TMath::Exp(-0.0118*ev.gtop_pt[igen])-0.000134*ev.gtop_pt[igen]+0.973;
	  if(debug) std::cout << "topsf was calculated to be " << topsf << std::endl;
          topptWgts[0] *= topsf;
	  //topptWgts[1] *= 1./topsf;
        }
      }
    
      //b-fragmentation weights
      bfragWgts[0] = computeBFragmentationWeight(ev,fragWeights["downFrag"]);
      bfragWgts[1] = computeBFragmentationWeight(ev,fragWeights["upFrag"]);
    
      // lepton trigger*selection weights
      sel1SF = lepEffH.getOfflineCorrection(leptons[l1idx], period);
      sel2SF = lepEffH.getOfflineCorrection(leptons[l2idx], period);

      wgt *= trigSF.first*sel1SF.first*sel2SF.first*topptWgts[0];

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

    //EffCorrection_t selSF(sel1SF.first*sel2SF.first,0.0);

    ////////////////////////////////////////////
    ///////////PPS information /////////////////
    ////////////////////////////////////////////

    nRPtk=0;
    double goodmRP=10000, goodyRP=10;

    double p1_xi =0.; // proton in positive pot
    double p2_xi =0.; // proton in negative pot
    
    double p1_x = 0, p1_y =0.; // proton near track position in positive pot
    double p2_x = 0, p2_y =0.; // proton near track position in positive pot
    //double p1_220_x = 0, p1_220_y =0.; // proton near track position in positive pot
    //double p2_220_x = 0, p2_220_y =0.; // proton near track position in positive pot
    
    int pool_run=0;
  
    if (ev.isData || isSignal) {
      
      //if(debug) std::cout << "entering pps part" << std::endl;
      
      if(ev.isData) {
	beamXangle = (int)ev.beamXangle;
	if(prepareProtonData) {
	  protonvars_beamXangle = (int)ev.beamXangle;
	  protonvars_run = ev.run;
	  protonvars_event = ev.event;
	  protonvars_lumi = ev.lumi;
	  protonvars_nvtx = ev.nvtx;
	  protonvars_rho = ev.rho;
	  protonvars_nchPV = ev.nchPV;
	}

	ht.fill("beamXangle", beamXangle, plotwgts, selCat);
	if(!(beamXangle==120 || beamXangle==130 || beamXangle==140 || beamXangle==150)) continue;
      }
		
      //only dispersions for these angles are available (@ CTPPSAnalysisTools/data/2017/dispersions.txt)
      //150 is interpolated
      for (int ift=0; ift<ev.nfwdtrk; ift++) {
            
	if(ev.fwdtrk_method[ift]!=1)  continue;  //multi RP
	const unsigned short pot_raw_id = ev.fwdtrk_pot[ift];
	
	nRPtk++;
	
	if(pot_raw_id < 100) {
	  p1_xi = ev.fwdtrk_xi[ift];
	  p1_x = ev.fwdtrk_NearX[ift];
	  p1_y = ev.fwdtrk_NearY[ift];
	  //p1_220_x = ev.fwdtrk_FarX[ift];
	  //p1_220_y = ev.fwdtrk_FarY[ift];
	}
	else if(pot_raw_id > 100) {
	  p2_xi = ev.fwdtrk_xi[ift];
	  p2_x = ev.fwdtrk_NearX[ift];
	  p2_y = ev.fwdtrk_NearY[ift];
	  //p2_220_x = ev.fwdtrk_FarX[ift];
	  //p2_220_y = ev.fwdtrk_FarY[ift];
	}
	
      }
	  
      // Store proton pool at preselection
      if(ev.isData && prepareProtonData) {
	m_protonVars_p1_xi = p1_xi;
	m_protonVars_p2_xi = p2_xi;
	outPT->Fill();
      }
      
    }
    
    if(ev.isData && p1_xi>0 && p2_xi>0) {
      goodmRP = 13000*sqrt(p1_xi*p2_xi);
      goodyRP = 0.5*TMath::Log(p1_xi/p2_xi);
    }
 
    //use proton mixing to enrich MC samples    
    double ptag_wgt=1, ppsSF_wgt=1;
    double ptag_wgt_err=0, ppsSF_wgt_err=0;

    if(!ev.isData) {

      int i_reg = rand_gen->Rndm() * n_PUregions;
      float _extra_weight = (fraction_regions[i_reg]*float(n_PUregions));
      // -------------------------------------------------- //
      int i_event = rand_gen->Rndm()*counter_regions[i_reg];

      _puweights_read->cd();
      PUpr_read[i_reg]->GetEntry(i_event);

      wgt*=_extra_weight;

      // fix run number and crossing-angle from proton pool
      pool_run = poll_run[i_reg];

      if(!isSignal) {
	beamXangle = xangle[i_reg % n_xa];
      }
      
      // proton efficiency implementation (xi of protons that fail reco. will be set to zero)
      ppsSF_wgt = 1.; ppsSF_wgt_err=0;

      if(p1_xi>0){
	float SF = Strip_eff->getEff(p1_x,p1_y,0,pool_run) * MultiRP_eff->getEff(p1_x,p1_y,0,pool_run);
	if(rand_gen->Rndm()>SF) p1_xi=0;
	else ppsSF_wgt *= SF;
	ppsSF_wgt_err += MultiRP_eff->getRelEffErrSq(p1_x,p1_y,0,pool_run);
      }
      if(p2_xi>0){
	float SF = Strip_eff->getEff(p2_x,p2_y,1,pool_run) * MultiRP_eff->getEff(p2_x,p2_y,1,pool_run);
	if(rand_gen->Rndm()>SF) p2_xi=0;
	else ppsSF_wgt *= SF;
	ppsSF_wgt_err += MultiRP_eff->getRelEffErrSq(p2_x,p2_y,1,pool_run);
      }
      ppsSF_wgt_err = sqrt(ppsSF_wgt_err);
    
      // mixing with the pileup protons (note the different treatment for the signal)

      if(isSignal && p1_xi>0 && p2_xi>0){ // two accepted signal protons

      	ptag_wgt = norm_weight_0p[i_reg];
      	ptag_wgt *= ptr.trueZeroTracksRatio(pool_run, beamXangle, 0) * ptr.trueZeroTracksRatio(pool_run, beamXangle, 1);
      	ptag_wgt_err = norm_weight_0p_err[i_reg];
       
      	//ppsSF_wgt = MultiRP_eff->getEff(p1_x,p1_y,0,pool_run) *  MultiRP_eff->getEff(p2_x,p2_y,1,pool_run);
      	//ppsSF_wgt_err = MultiRP_eff->getRelEffErrSq(p1_x,p1_y,0,pool_run) + 
      	//MultiRP_eff->getRelEffErrSq(p2_x,p2_y,1,pool_run);
      	//ppsSF_wgt_err = sqrt(ppsSF_wgt_err);

      	// strip efficiency
      	//ppsSF_wgt *= Strip_eff->getEff(p1_x,p1_y,0,pool_run) * Strip_eff->getEff(p2_x,p2_y,1,pool_run);
      	//std::cout << "p1_x: " << p1_x << ", p1_y: " << p1_y << ", p2_x: " << p2_x << ", p2_y: " << p2_y << std::endl;
      	//std::cout << "strip efficiency 2p: " <<  Strip_eff->getEff(p1_x,p1_y,0,pool_run) * Strip_eff->getEff(p2_x,p2_y,1,pool_run) << std::endl;
      	signal_protons = 11;
      }
      else if(isSignal && p1_xi==0 && p2_xi>0){ // one signal proton in arm1
      	
	p1_xi = poll_p1_xi[i_reg];
	ptag_wgt = norm_weight_1pRP0[i_reg];
      	ptag_wgt = ptr.trueZeroTracksRatio(pool_run, beamXangle, 1);
      	ptag_wgt_err = norm_weight_1pRP0_err[i_reg];

      	//ppsSF_wgt = MultiRP_eff->getEff(p2_x,p2_y,1,pool_run);
      	//ppsSF_wgt_err = MultiRP_eff->getRelEffErrSq(p2_x,p2_y,1,pool_run);

      	// strip efficiency
      	//ppsSF_wgt *= Strip_eff->getEff(p2_x,p2_y,1,pool_run);
      	//	std::cout << "p1_x: " << p1_x << ", p1_y: " << p1_y << ", p2_x: " << p2_x << ", p2_y: " << p2_y << std::endl;
      	//std::cout << "strip efficiency 1p: " <<  Strip_eff->getEff(p2_x,p2_y,1,pool_run) << std::endl;

      	signal_protons = 1;
      }
      else if(isSignal && p1_xi>0 && p2_xi==0){ // one signal proton in arm0
      	p2_xi = poll_p2_xi[i_reg];
      	ptag_wgt = norm_weight_1pRP1[i_reg];
	ptag_wgt *= ptr.trueZeroTracksRatio(pool_run, beamXangle, 0);
      	ptag_wgt_err = norm_weight_1pRP1_err[i_reg];

      	//ppsSF_wgt = MultiRP_eff->getEff(p1_x,p1_y,0,pool_run);
      	//ppsSF_wgt_err = MultiRP_eff->getRelEffErrSq(p1_x,p1_y,0,pool_run);

      	// strip efficiency
      	//ppsSF_wgt *= Strip_eff->getEff(p1_x,p1_y,0,pool_run);
      	//std::cout << "p1_x: " << p1_x << ", p1_y: " << p1_y << ", p2_x: " << p2_x << ", p2_y: " << p2_y << std::endl;
      	//std::cout << "strip efficiency 1p: " <<  Strip_eff->getEff(p1_x,p1_y,0,pool_run);

      	signal_protons = 10;
      }
      else{ // no signal protons in the acceptance region / other MC

      	p1_xi = poll_p1_xi[i_reg];
      	p2_xi = poll_p2_xi[i_reg];
	ptag_wgt = norm_weight[i_reg];
      	ptag_wgt_err = norm_weight_err[i_reg];
      	signal_protons = 0;
      }

      wgt *= ptag_wgt;

      // Fix ptag weight from w_sys/w_nom to 1 +/- err
      ptag_wgt_err = TMath::Abs(1 - ptag_wgt_err);

      // pileup reweighting 
      float w_mc = mc_pu->GetBinContent(ev.nvtx+1);
      float pu_wgt = (w_mc) ? pu_weights_read[i_reg]->GetBinContent(ev.nvtx+1)/w_mc : 0;
      wgt*= pu_wgt;

      if(isSignal) {
      	//std::cout << "extra_signal_normalization: " << extra_signal_normalization << std::endl;
      	wgt*= extra_signal_normalization;
      }
    
      if(p1_xi>0 && p2_xi>0) {
        goodmRP = 13000*sqrt(p1_xi*p2_xi);
        goodyRP = 0.5*TMath::Log(p1_xi/p2_xi);
      }
    }

    //add b tag decisions
    btvSF.addBTagDecisions(ev);
    //string option = "central";
    //if(!ev.isData) btvSF.updateBTagDecisions(ev,option,option);
    //jerTool_.smearJetEnergies(ev);

    std::vector<Jet> nominalJets = selector.getGoodJets(ev,15.,2.4,leptons,{},0); //,photons);
    //Initiate systematics loop
    double nominalwgt=wgt;
    double nominalmRP=goodmRP;
    double nominalyRP=goodyRP;

    //experimental systs are computed for MC only, else only the nominal
    if(!runSysts || ev.isData) {
      nexpSysts = 1;
      nweightSysts = 0;
    }

    for(size_t is=0; is<nexpSysts; is++){

      TString sname=expSystNames[is];
      bool isUpVar(sname.EndsWith("up"));
      double iwgt = nominalwgt;
      goodmRP=nominalmRP;
      goodyRP=nominalyRP;


      if(sname.Contains("protonReco45")) {
	double ixi0=0, ixi1=0;
	ixi0 = isUpVar ? p1_xi+PPS_reco->getRecoErr(p1_xi,0,ev.run) : p1_xi-PPS_reco->getRecoErr(p1_xi,0,ev.run);
	ixi1 = p2_xi;
	//isUpVar ? p2_xi+PPS_reco->getRecoErr(p2_xi,1,ev.run) : p2_xi-PPS_reco->getRecoErr(p2_xi,1,ev.run);
	goodmRP = 13000*sqrt(ixi0*ixi1);
	goodyRP = 0.5*TMath::Log(ixi0/ixi1);
      }
      else if(sname.Contains("protonReco56")) {
	double ixi0=0, ixi1=0;
	ixi0 = p1_xi;
	ixi1 = isUpVar ? p2_xi+PPS_reco->getRecoErr(p2_xi,1,ev.run) : p2_xi-PPS_reco->getRecoErr(p2_xi,1,ev.run);
	goodmRP = 13000*sqrt(ixi0*ixi1);
	goodyRP = 0.5*TMath::Log(ixi0/ixi1);
      }
      else {
	goodmRP=nominalmRP;
	goodyRP=nominalyRP;
      }

      //select jets
      
      //JEC/JER settings
      int sys = 0;
      if(sname=="JERup") sys = 1;
      else if(sname=="JERdn") sys = -1;
      else if(sname=="JECup") sys = 2;
      else if(sname=="JECdn") sys = -2;
      else if(sname=="AbsJECup") sys = 3;
      else if(sname=="AbsJECdn") sys = -3;
      else if(sname=="RelJECup") sys = 4;
      else if(sname=="RelJECdn") sys = -4;
      else if(sname=="PileupJECup") sys = 5;
      else if(sname=="PileupJECdn") sys = -5;
      else if(sname=="FlavorJECup") sys = 6;
      else if(sname=="FlavorJECdn") sys = -6;
      else if(sname=="HighPtJECup") sys = 7;
      else if(sname=="HighPtJECdn") sys = -7;
      else if(sname=="TimeJECup") sys = 8;
      else if(sname=="TimeJECdn") sys = -8;

      std::vector<Jet> preselJets = selector.getGoodJets(ev,15.,2.4,leptons,{},sys); //,photons);

      std::vector<Jet> allJets = selector.getGoodJets(ev,30.,2.4,leptons,{},sys); //,photons);
      
      //jets (require PU jet id)
      int njets(0);
      std::vector<Jet> bJets,lightJets,jets;
      
      TLorentzVector extra_system(0,0,0,0);
      float scalarht(0.),scalarhtb(0.),scalarhtj(0.);
      float extra_rapidity(0.), extra_rapidity_sum(0.);

      float variedmet_px = nominalmet.Px();
      float variedmet_py = nominalmet.Py();

      for(size_t ij=0; ij<preselJets.size(); ij++) {
	variedmet_px += preselJets[ij].Px();
	variedmet_py += preselJets[ij].Py();
      }

      for(size_t ij=0; ij<nominalJets.size(); ij++) {
	variedmet_px -= nominalJets[ij].Px();
	variedmet_py -= nominalJets[ij].Py();
      }

      TLorentzVector met;
      met.SetPxPyPzE(variedmet_px,variedmet_py,0,-std::sqrt(std::pow(variedmet_px,2) + std::pow(variedmet_py,2)));

      if(sname.Contains("UnclMET")) {
	double met_ptVar = (isUpVar) ? ev.met_ptShifted[10] : ev.met_ptShifted[11];
	double met_phiVar = (isUpVar) ? ev.met_phiShifted[10] : ev.met_phiShifted[11];
	met.SetPtEtaPhiM(met_ptVar,met.Eta(),met_phiVar,met.M());
      }

      for(size_t ij=0; ij<allJets.size(); ij++) {
        int idx=allJets[ij].getJetIndex();
        bool passBtag(ev.j_btag[idx]>0);

        int jid=ev.j_id[idx];
        bool passLoosePu((jid>>2)&0x1);          
        if(!passLoosePu) continue;

        if(passBtag) { bJets.push_back(allJets[ij]);     scalarhtb+=allJets[ij].pt();  }
        else         { 
	         lightJets.push_back(allJets[ij]); 
	         extra_system+=allJets[ij]; 
	         scalarhtj+= allJets[ij].pt();
	         extra_rapidity_sum+=fabs(allJets[ij].Rapidity());
        }
     
        njets++;
     
        jets.push_back(allJets[ij]);
        scalarht += jets[ij].pt();       
      }
     
      if(lightJets.size()>0) extra_rapidity=extra_system.Rapidity();
      else extra_rapidity=0;

      if(!prepareProtonData && bJets.size()<2) continue;
      protonvars_nBjets = bJets.size();

      /*      TLorentzVector lb_min(0,0,0,0);
      if(bJets.size()>0 && leptons.size()>1) {
        std::vector<int> lbpair = ComputeLBcombination(leptons,bJets);  
        lb_min = leptons[lbpair[0]]+bJets[lbpair[1]];     
	}*/

      //compute hadronic recoil
      TLorentzVector h = met+ll;
      for(size_t i=0; i<bJets.size();i++) {
  	   if(i<3) h+=bJets[i];
      }
    
      //histogram categories for different selection steps
      std::vector<TString> cats(1,"");
      //      bool passkinreco = false;
      //int catsize = 1;

      if(isSF) cats.push_back(cats[0]+selCat+"_2b_notZ");
      else cats.push_back(cats[0]+selCat+"_2b");

      float px2=0,py2=0,pz2=0,E2=0,yvis=0,ysum=0,max_dy=0,min_dy=0;
      double kinReco_m = -1, kinReco_y = -10;

      if(bJets.size()>1 && leptons.size()>1) {
      //compute some other high level variables
        px2=(bJets[0].Px()+bJets[1].Px()+leptons[0].Px()+leptons[1].Px()+met.Px())*(bJets[0].Px()+bJets[1].Px()+leptons[0].Px()+leptons[1].Px()+met.Px());
        py2=(bJets[0].Py()+bJets[1].Py()+leptons[0].Py()+leptons[1].Py()+met.Py())*(bJets[0].Py()+bJets[1].Py()+leptons[0].Py()+leptons[1].Py()+met.Py());
        pz2=(bJets[0].Pz()+bJets[1].Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz())*(bJets[0].Pz()+bJets[1].Pz()+leptons[0].Pz()+leptons[1].Pz()+met.Pz());
        E2=(bJets[0].E()+bJets[1].E()+leptons[0].E()+leptons[1].E()+met.Pt())*(bJets[0].E()+bJets[1].E()+leptons[0].E()+leptons[1].E()+met.Pt());
  	    
        yvis=(bJets[0]+bJets[1]+leptons[0]+leptons[1]).Rapidity();
        ysum=fabs(bJets[0].Rapidity())+fabs(bJets[1].Rapidity())+fabs(leptons[0].Rapidity())+fabs(leptons[1].Rapidity());
        max_dy= max(fabs((bJets[0]+leptons[0]).Rapidity())-fabs((bJets[1]+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((bJets[1]+leptons[0]).Rapidity()));
        min_dy=min( fabs((bJets[0]+leptons[0]).Rapidity())-fabs((bJets[1]+leptons[1]).Rapidity()),  fabs((bJets[0]+leptons[1]).Rapidity())-fabs((bJets[1]+leptons[0]).Rapidity()));

        do_kin_reco(leptons, jets, bJets, met, debug, kinReco_m, kinReco_y);
	
	// cats.push_back(cats[1]+"_passKinReco");

	//assign variables for the BDT
	run_bdt=ev.run;
	lumi_bdt=ev.lumi;
	event_bdt=ev.event;
	rho_bdt=ev.rho;
	mpp_bdt=goodmRP;
	mtt_bdt=kinReco_m;
	ypp_bdt=goodyRP;
	ytt_bdt=kinReco_y;
	yvis_bdt=yvis;
	deltarll_bdt=leptons[0].DeltaR(leptons[1]);
	mll_bdt=(leptons[0]+leptons[1]).M();
	deltaphibb_bdt=fabs(bJets[1].Phi()-bJets[0].Phi());
	ysum_bdt=ysum;
	//metphi_bdt=met.Phi();
	min_dy_bdt=min_dy;
	nljets_bdt=lightJets.size();
	metpt_bdt=met.Pt();
	E2_bdt=E2;
	extra_ysum_bdt = extra_rapidity_sum;
	nprotons_bdt = signal_protons;
	extrasystem_y_bdt = extra_rapidity;
      }

      ////////////////////
      // Event WEIGHTS //
      //////////////////
    
      if(!ev.isData) {

        btagWgt= btvSF.getBtagWeight(jets,ev,"central",BTagSFUtil::METHOD1A);
        l1trigprefireProb=l1PrefireWR->getCorrection(allJets);

	std::cout << "btag weight:" << btagWgt << std::endl;
        iwgt *= l1trigprefireProb.first*btagWgt;
	
	double nominalMCweight = iwgt;

	if(sname=="nominal") {

	  //start loop on weight systematics
	  for(size_t wSyst=0;wSyst<nweightSysts;wSyst++) {

	    iwgt = nominalMCweight;
	    TString wsname=weightSystNames[wSyst];
	    isUpVar = wsname.EndsWith("up");

	    if(wsname.BeginsWith("esel") && combinedESF.first!=0) {
	      double newESF( max(double(0.),double(combinedESF.first+(isUpVar ? +1 : -1)*combinedESF.second)) );
	      iwgt *= newESF/combinedESF.first;
	    }
	    else if(wsname.BeginsWith("msel") && combinedMSF.first!=0) {
	      double newMSF( max(double(0.),double(combinedMSF.first+(isUpVar ? +1 : -1)*combinedMSF.second)) );
	      iwgt *= newMSF/combinedMSF.first;
	    }
	    else if(wsname.BeginsWith("trigSF") && trigSF.first!=0) {
	      double newTrigSF( max(double(0.),double(trigSF.first+(isUpVar ? +1 : -1)*trigSF.second)) );
	      iwgt *= newTrigSF/trigSF.first;
	    }
	    else if(wsname.BeginsWith("l1prefire") && l1trigprefireProb.first!=0){
	      double newL1PrefireProb( max(double(0.),double(l1trigprefireProb.first+(isUpVar ? +1 : -1)*l1trigprefireProb.second)) );
	      iwgt *= newL1PrefireProb/l1trigprefireProb.first;
	    }
	    //else if(wsname=="topptup")     iwgt *= topptWgts[0];
	    //else if(wsname=="topptdn")     iwgt *= topptWgts[1];
	    else if(wsname=="bfragup")     iwgt *= bfragWgts[0];
	    else if(wsname=="bfragdn")     iwgt *= bfragWgts[1];
	    
	    //variacao da b-tag efficiency
	    else if(wsname.BeginsWith("btaghf")) {
	      double btagWgt_HFvar = isUpVar ?
		btvSF.getBtagWeight(jets,ev,"up_hf",BTagSFUtil::SFWeightMethod::METHOD1A) :
		btvSF.getBtagWeight(jets,ev,"down_hf",BTagSFUtil::SFWeightMethod::METHOD1A);
	      
	      iwgt *= btagWgt_HFvar/btagWgt;
	    }
	    //variacao da mistag rate
	    else if(wsname.BeginsWith("btaglf")) {
	      double btagWgt_LFvar = isUpVar ? 
		btvSF.getBtagWeight(jets,ev,"up_lf",BTagSFUtil::SFWeightMethod::METHOD1A) :
		btvSF.getBtagWeight(jets,ev,"down_lf",BTagSFUtil::SFWeightMethod::METHOD1A);

	      iwgt *= btagWgt_LFvar/btagWgt;
	    }

	    if(wsname.Contains("ppsSF")) {
	      iwgt*= isUpVar ? (1+ppsSF_wgt_err) : (1-ppsSF_wgt_err);
	    }
	    if(wsname.Contains("protonTag")) {
	      iwgt*= isUpVar ? (1+ptag_wgt_err) : (1-ptag_wgt_err);
	    }
	    
	    if(ev.g_nw>100 && wsname.Contains("pdf")){ // pdf variations
	      	      		
	      float sig_mean = 0; float Nmem=0;
	      float m_factor_pdf = 1;

	      for(unsigned int i=7;i<107;i++){ // envelope
		if (ev.g_w[i]==0) continue;
		sig_mean+=ev.g_w[i];
		Nmem++;
	      }
	      
	      if(Nmem){
		sig_mean /=Nmem;
		
		float sig_var = 0;
		for (int i=7;i<107;i++){
		  if (ev.g_w[i]==0) continue;
		  sig_var+=(ev.g_w[i]-sig_mean)*(ev.g_w[i]-sig_mean);
		}
		
		if(wsname.Contains("pdfHS")) m_factor_pdf = sqrt(sig_var/(Nmem-1))/sig_mean; // eq 21 in https://arxiv.org/pdf/1510.03865.pdf
		
		// for pdf_as use eq 27 in https://arxiv.org/pdf/1510.03865.pdf
		// r=0.75 used to adjust to 68% for d(as)=0.002 as suggested in eq 29 
		else if(wsname.Contains("pdfAS")) m_factor_pdf = 0.75*0.5*(ev.g_w[108]-ev.g_w[107])/sig_mean;
		
	      }
	     
	      m_factor_pdf = isUpVar ? 1+m_factor_pdf : 1-m_factor_pdf;
	      
	      //std::cout << wsname << ": " << m_factor_pdf;

	      iwgt*=m_factor_pdf;
	    }
	    
	    if(ev.g_nw>5 && ev.g_w[1] && wsname.Contains("mu")) {
	      
	      double m_factor_mu = 0;
	      
	      // protect against broken weights
	      
	      if(wsname=="muRup") m_factor_mu = 1+(ev.g_w[2]-ev.g_w[3])/(ev.g_w[2]+ev.g_w[3]);
	      else if(wsname=="muFup") m_factor_mu = 1+(ev.g_w[4]-ev.g_w[5])/(ev.g_w[4]+ev.g_w[5]);
	      else if(wsname=="muRmuFup") m_factor_mu = ( (ev.g_w[6])/ev.g_w[1] -1);
	      
	      else if(wsname=="muRdn") m_factor_mu = 1-(ev.g_w[2]-ev.g_w[3])/(ev.g_w[2]+ev.g_w[3]);
	      else if(wsname=="muFdn") m_factor_mu = 1-(ev.g_w[4]-ev.g_w[5])/(ev.g_w[4]+ev.g_w[5]);
	      else if(wsname=="muRmuFdn") m_factor_mu = (1 - (ev.g_w[7])/ev.g_w[1]);
	      
	      // protect against broken weights 
	      if(m_factor_mu<0 || m_factor_mu>2) m_factor_mu=1;

	      iwgt*=(m_factor_mu);
	    }
	
	    if(wsname.Contains("isr") or wsname.Contains("fsr")) {
	      
	      int nW = ev.g_npsw;
	      float PSnom_weight = ev.g_psw[PSmap["nominal"]];
	  
	      double mult_factor = 1;
	  
	      if(nW==46 && PSnom_weight){ // 46 weights of ISR and FSR, take only the first ones
	  
		if(wsname.BeginsWith("isrG2GGmuRup")) mult_factor = (ev.g_psw[PSmap["isr_G2GG_muR_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2GGmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_muR_up"]])/PSnom_weight;

		else if(wsname.BeginsWith("isrG2QQmuRup")) mult_factor = (ev.g_psw[PSmap["isr_G2QQ_muR_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2QQmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_muR_up"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrQ2QGmuRup")) mult_factor = (ev.g_psw[PSmap["isr_Q2QG_muR_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrQ2QGmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_muR_up"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrX2XGmuRup")) mult_factor = (ev.g_psw[PSmap["isr_X2XG_muR_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrX2XGmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_muR_up"]])/PSnom_weight;
	    
		else if(wsname.BeginsWith("isrG2GGcNSup")) mult_factor = (ev.g_psw[PSmap["isr_G2GG_cNS_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2GGcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_cNS_up"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrG2QQcNSup")) mult_factor = (ev.g_psw[PSmap["isr_G2QQ_cNS_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2QQcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_cNS_up"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrQ2QGcNSup")) mult_factor = (ev.g_psw[PSmap["isr_Q2QG_cNS_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrQ2QGcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_cNS_up"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrX2XGcNSup")) mult_factor = (ev.g_psw[PSmap["isr_X2XG_cNS_up"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrX2XGcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_cNS_up"]])/PSnom_weight;

		else if(wsname.BeginsWith("isrG2GGmuRdn")) mult_factor = (ev.g_psw[PSmap["isr_G2GG_muR_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2GGmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_muR_dn"]])/PSnom_weight;
	    
		else if(wsname.BeginsWith("isrG2QQmuRdn")) mult_factor = (ev.g_psw[PSmap["isr_G2QQ_muR_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2QQmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_muR_dn"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrQ2QGmuRdn")) mult_factor = (ev.g_psw[PSmap["isr_Q2QG_muR_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrQ2QGmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_muR_dn"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrX2XGmuRdn")) mult_factor = (ev.g_psw[PSmap["isr_X2XG_muR_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrX2XGmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_muR_dn"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrG2GGcNSdn")) mult_factor = (ev.g_psw[PSmap["isr_G2GG_cNS_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2GGcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_cNS_dn"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrG2QQcNSdn")) mult_factor = (ev.g_psw[PSmap["isr_G2QQ_cNS_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrG2QQcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_cNS_dn"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrQ2QGcNSdn")) mult_factor = (ev.g_psw[PSmap["isr_Q2QG_cNS_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrQ2QGcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_cNS_dn"]])/PSnom_weight;
		
		else if(wsname.BeginsWith("isrX2XGcNSdn")) mult_factor = (ev.g_psw[PSmap["isr_X2XG_cNS_dn"]])/PSnom_weight;
		else if(wsname.BeginsWith("fsrX2XGcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_cNS_dn"]])/PSnom_weight;
	      }
	  
	      else if(nW==24 && PSnom_weight){ //no isr for signal
		//std::cout << "no isr" << std::endl;
	    
		if(wsname.BeginsWith("fsrG2GGmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_muR_up"]-6])/PSnom_weight;
	    
		else if(wsname.BeginsWith("fsrG2QQmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_muR_up"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrQ2QGmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_muR_up"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrX2XGmuRup")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_muR_up"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrG2GGcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_cNS_up"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrG2QQcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_cNS_up"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrQ2QGcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_cNS_up"]-6])/PSnom_weight;
	    
		else if(wsname.BeginsWith("fsrX2XGcNSup")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_cNS_up"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrG2GGmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_muR_dn"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrG2QQmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_muR_dn"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrQ2QGmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_muR_dn"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrX2XGmuRdn")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_muR_dn"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrG2GGcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2GG_cNS_dn"]-6])/PSnom_weight;
	  
		else if(wsname.BeginsWith("fsrG2QQcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_G2QQ_cNS_dn"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrQ2QGcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_Q2QG_cNS_dn"]-6])/PSnom_weight;
		
		else if(wsname.BeginsWith("fsrX2XGcNSdn")) mult_factor = (ev.g_psw[PSmap["fsr_X2XG_cNS_dn"]-6])/PSnom_weight;
		
	      }
	  
	      //if(isUpVar) mult_factor = mult_factor - 1;
	      //else mult_factor = 1 - mult_factor;
	      
	      //std::cout << "mult_factor " << (isUpVar? "up" : "down") << " is: " << mult_factor << std::endl;
	      iwgt*= mult_factor;
	    }

	    //evaluate and fill BDT
	    plotwgts[0]=iwgt;

	    if(!prepareProtonData && !prepareTraining && bJets.size()>1) {
	      ht.fill("BDToutput_"+weightSystNames[wSyst], reader->EvaluateMVA(method), plotwgts, cats);
	      ht.fill("nljets_"+weightSystNames[wSyst], nljets_bdt, plotwgts, cats);
	    }
	  }
	}
      //finish theory loop	  
      iwgt = nominalMCweight;
      }

      //control histograms for nominal only

      //UPDATE WEIGHTS FOR PLOTTER
      plotwgts[0]=iwgt;

      if(!prepareProtonData && sname=="nominal") {
        ht.fill("nvtx",       ev.nvtx,         plotwgts, cats);      
        //event yields
        ht.fill("nlep",       (float)leptons.size(),  plotwgts, cats);
        //ht.fill("jet1pt", allJets[0].Pt(),  plotwgts, cats);
        ht.fill("ptll",       ll.Pt(),        plotwgts, cats);
          
        //bjets
        ht.fill("nbjets",     bJets.size(),    plotwgts, cats);
        ht.fill("scalarhtb",     scalarhtb,    plotwgts, cats);
          
        //light jets       
        ht.fill("h", h.Pt(), plotwgts, cats);  
        ht.fill("met",      met.Pt(),    plotwgts, cats);
        ht.fill("scalarhtj",  scalarhtj,    plotwgts, cats);

        ht.fill("gen_ttbar_mass", gen_mtt, plotwgts, cats);
        ht.fill("gen_ttbar_rapidity", gen_ytt, plotwgts, cats);
	if(leptons.size()>1) {
        ht.fill("mll",        ll.M(),         plotwgts, cats);
        ht.fill("drll",       dilepton_dr,plotwgts,cats);
        ht.fill("deltaphill",       fabs(leptons[0].Phi()-leptons[1].Phi()),plotwgts,cats);
        ht.fill("nljets",     lightJets.size(),    plotwgts, cats);
	//        ht.fill("Mlb", lb_min.M(),  plotwgts, cats);}
	}
      }
    
      if( bJets.size()>1) {

        //save events in the tree (nominal only)
        if(sname=="nominal" && !prepareProtonData) {

          ht.fill("kin_reco_ttbar_mass", kinReco_m, plotwgts, cats);
          ht.fill("kin_reco_ttbar_rapidity", kinReco_y, plotwgts, cats);
          ht.fill("E2",  E2,    plotwgts, cats);
          ht.fill("yvis",  yvis,    plotwgts, cats);
          ht.fill("ysum",  ysum,    plotwgts, cats);
          ht.fill("extray_sum",  extra_rapidity_sum,    plotwgts, cats);
          ht.fill("extrasystem_y",  extra_rapidity,    plotwgts, cats);
          ht.fill("mindy",  min_dy,    plotwgts, cats);
          ht.fill("xi0",p1_xi,plotwgts,cats);
          ht.fill("xi1",p2_xi,plotwgts,cats);
          ht.fill("mRP",goodmRP/1000.,plotwgts,cats);
          ht.fill("yRP",goodyRP,plotwgts,cats);
	  if(bJets.size()>1) ht.fill("deltaphibb",       fabs(bJets[0].Phi()-bJets[1].Phi()),plotwgts,cats);

          if(prepareTraining) {
            Float_t varsel[]={(float)ev.run,
			      (float)ev.lumi,(float)ev.event,(float)ev.nvtx,(float)ev.rho,
			      (float)leptons[0].id()*leptons[1].id(),(float) ll.M(),(float)lightJets.size(), (float)bJets.size(), (float) scalarht, 
			      (float) extra_rapidity,(float) extra_rapidity_sum,
			      (float) met.Pt(),(float) met.Phi(),
			      (float) leptons[0].Pt(),(float)leptons[0].Eta(),(float)leptons[0].Phi(),(float)leptons[0].M(),(float)
			      leptons[1].Pt(),(float)leptons[1].Eta(),(float)leptons[1].Phi(),(float)leptons[1].M(),
			      (float) bJets[0].Pt(),(float)bJets[0].Eta(),(float)bJets[0].Phi(),(float)bJets[0].M(),(float)
			      bJets[1].Pt(),(float)bJets[1].Eta(),(float)bJets[1].Phi(),(float)bJets[1].M(),
			      px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,(float)
			      leptons[0].DeltaR(leptons[1]),(float) leptons[0].DeltaPhi(leptons[1]),(float) p1_xi,
			      (float) p2_xi, (float)       
			      goodmRP,(float) goodyRP, (float) gen_mtt, (float) gen_ytt, (float) kinReco_m, (float) kinReco_y, 
			      (float) wgt, (float) signal_protons};

            outTsel->Fill(varsel);
          }

          TString ev_period = "";
          if(ev.isData) ev_period = get_period_from_run(ev.run);
          else ev_period = get_period_from_run(pool_run);
	  
          if(!prepareTraining && !prepareProtonData && bJets.size()>1) {
	    
            int region(-1);
            if(ev_period=="B") region=0;
            else if(ev_period=="C") region=4;
            else if(ev_period=="D") region=8;
            else if(ev_period=="E") region=12;
            else if(ev_period=="F") region=16;
	    
            if(beamXangle==120) region+=0;
            else if(beamXangle==130) region+=1;
            else if(beamXangle==140) region+=2;
            else if(beamXangle==150) region+=3;
	    
            if(region>-1) {
	      
              ht.fill("evyields",region, plotwgts, cats);
              
              std::vector<TString> xicats;
              TString regionname=Form("region%d",beamXangle);
              xicats.push_back(regionname);
           
              ht.fill("xi0",p1_xi, plotwgts, xicats);
              ht.fill("xi1",p2_xi, plotwgts, xicats);
            }
            else ht.fill("evyields",-1, plotwgts, cats);

          }

        }

	//evaluate and fill BDT	
	if(!prepareProtonData && !prepareTraining && bJets.size()>1) {
	  ht.fill("BDToutput_"+expSystNames[is], reader->EvaluateMVA(method), plotwgts, cats);
	  ht.fill("nljets_"+expSystNames[is], nljets_bdt, plotwgts, cats);
	}
	    	    
      }//close bsize
   
      //reset all BDT variables
      mpp_bdt=0;
      mtt_bdt=0;
      ypp_bdt=0;
      ytt_bdt=0;
      yvis_bdt=0;
      deltarll_bdt=0;
      mll_bdt=0;
      deltaphibb_bdt=0;
      ysum_bdt=0;
      //metphi_bdt=met.Phi();
      min_dy_bdt=0;
      nljets_bdt=0;
      metpt_bdt=0;
      E2_bdt=0;
      px2=0;
      py2=0;
      pz2=0;
      E2=0;
      extra_ysum_bdt = 0;
      nprotons_bdt = 0;
      extrasystem_y_bdt = 0;
      yvis=0;
      ysum=0;
      max_dy=0;
      min_dy=0;
      kinReco_m=-1;
      kinReco_y=-10;
      allJets.clear();
      bJets.clear();
      lightJets.clear();
      jets.clear();
      iwgt=nominalwgt;

    } // close syst loop
  } //close event loop

  //close input file
  f->Close(); 
  
  //save histos to file  
  fOut->cd();
  if( !prepareTraining ) {
    
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
  else outPT->Write();
  
  fOut->Close();

}
