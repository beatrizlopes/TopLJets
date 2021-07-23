#ifndef _ExclusiveTop_h_
#define _ExclusiveTop_h_

#include "TLorentzVector.h"
#include "TopLJets2015/TopAnalysis/interface/ObjectTools.h"
#include "TopLJets2015/TopAnalysis/interface/SelectionTools.h"

void RunExclusiveTop(TString filename,
                     TString outname,
                     Int_t channelSelection, 
                     Int_t chargeSelection, 
                     TH1F *normH, 
                     TH1F *genPU,
                     TString era,
                     Bool_t debug=false,
                     TString systVar="");

std::vector<int> ComputeLBcombination(std::vector<Particle>, std::vector<Jet>);

//std::vector<double> pixelEff(double, double);

bool do_kin_reco(std::vector<Particle>& leptons, std::vector<Jet>& jets, std::vector<Jet>& bjets, TLorentzVector& met, Bool_t debug, double& kinReco_ttbar_mass, double& kinReco_ttbar_rapidity);

//double kinReco_ttbar_pt = 0.;
//double kinReco_ttbar_mass = 0.;
//double kinReco_ttbar_rapidity = 0.;

bool passedKinReco;
//gen level objects
double ptTrueTop, ptTrueAntiTop;


#endif
