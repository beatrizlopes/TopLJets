#ifndef _ExclusiveTop_h_
#define _ExclusiveTop_h_

#include "TLorentzVector.h"
#include "TopLJets2015/TopAnalysis/interface/ObjectTools.h"
#include "TopLJets2015/TopAnalysis/interface/SelectionTools.h"

std::vector<int> ComputeLBcombination(std::vector<Particle> leptons, std::vector<Jet> bJets);

void RunExclusiveTop(TString filename,
                     TString outname,
                     Int_t channelSelection, 
                     Int_t chargeSelection, 
                     TH1F *normH, 
                     TH1F *genPU,
                     TString era,
                     Bool_t debug=false);

#endif
