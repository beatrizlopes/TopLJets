import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *

def AddRegVars():

    fInMass=ROOT.TFile.Open("TMVA_RegressionOutput_m.root","UPDATE")
    fInY=ROOT.TFile.Open("TMVA_RegressionOutput_y.root","UPDATE")
    fOut=ROOT.TFile.Open("SignalSample.root","RECREATE")
    tree=fInMass.Get("dataset/TestTree")
    Ytree=fInY.Get("dataset/TestTree")

    newtree=ROOT.TNtuple("sel3","sel3","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt")
    newtree.SetDirectory(fOut)
    
    totalEntries=tree.GetEntries()
    
    for i in xrange(0,totalEntries):
            
        tree.GetEntry(i)
        
        if i%100==0 : sys.stdout.write('\r [ %d/100 ] done' %(int(float(100.*i)/float(totalEntries))) )
            
        varsel=[tree.run,tree.lumi,tree.ev,tree.nvtx,tree.rho,tree.channel,tree.mll,tree.nljets,tree.nbjets,tree.ht,
                tree.metpt,tree.metphi,tree.l1pt,tree.l1eta,tree.l1phi,tree.l1m,tree.l2pt,tree.l2eta,tree.l2phi,tree.l2m,
                tree.b1pt,tree.b1eta,tree.b1phi,tree.b1m,tree.b2pt,tree.b2eta,tree.b2phi,tree.b2m,
                tree.px2,tree.py2,tree.pz2,tree.E2,tree.yvis,tree.ysum,tree.max_dy,tree.min_dy,
                tree.deltarll,tree.deltaphill,tree.mlb,tree.mpp,tree.ypp,tree.gen_mtt,tree.gen_ytt,tree.rec_mtt,tree.rec_ytt,(tree.rec_mtt/tree.BDTG_LS),
                (tree.rec_ytt-BDTG_LS)] 

        newtree.Fill(array("f",varsel))
        
    fOut.cd()    
    fOut.Write()
    fOut.Close()
        
def main():

        AddRegVars()


if __name__ == "__main__":
    main()
