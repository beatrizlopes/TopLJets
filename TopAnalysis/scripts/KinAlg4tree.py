import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *

"""                                                                                                                                                                                
a dummy converter                                                                                                                                                                   
"""
def convertToPtEtaPhiM(lVec,xyz,m=0.):
    en=ROOT.TMath.Sqrt(xyz[0]**2+xyz[1]**2+xyz[2]**2)
    p4=ROOT.TLorentzVector(xyz[0],xyz[1],xyz[2],en)
    return lVec(p4.Pt(),p4.Eta(),p4.Phi(),p4.M())


def KinematicsAlgorithm():

    args = sys.argv[1:]
    for filename in args:

        inFileName=filename
    
        print '....analysing',inFileName
        
        fIn=ROOT.TFile.Open(inFileName,"UPDATE")
        #fOut=ROOT.TFile.Open("teste.root","RECREATE")
        tree=fIn.Get("sel")

        if not fIn.GetListOfKeys().Contains("sel") :
            print "unable to read tree from file. Skipping file ",inFileName
            continue
        #newtree=ROOT.TTree("sel2","sel2")
        newtree=ROOT.TNtuple("sel2","sel2","run:lumi:ev:nvtx:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt")
        newtree.SetDirectory(fIn)

        #branch.SetEntries(tree.GetEntries())
        #fOut.cd();
        #newtree.SetDirectory(fOut);

        #loop over events in the tree and fill histos                                                             

        totalEntries=tree.GetEntries()
        lVec = ROOT.Math.LorentzVector(ROOT.Math.PtEtaPhiM4D('double'))
#        h1=ROOT.TH1F('yttrec-yttgen','[y_{tt} (rec) - y_{tt} (gen)]',50,-2,2)

        for i in xrange(0,totalEntries):
            
            tree.GetEntry(i)
            
            if i%100==0 : sys.stdout.write('\r [ %d/100 ] done' %(int(float(100.*i)/float(totalEntries))) )
            
        #evWeight=puNormSF*tree.weight[0]*filtWeight*filtNormRwgt
            
        #leptons                                                                                                                                                                    
            leptons=[]
            leptons.append( lVec(tree.l1pt,tree.l1eta,tree.l1phi,tree.l1m) )
            leptons.append( lVec(tree.l2pt,tree.l2eta,tree.l2phi,tree.l2m) )
        #if len(leptons)<2 : continue

        #preselect the b-jets (save always the jet and the gen jet)                                                                                                                 
            bjets=[]
            bjets.append( lVec(tree.b1pt,tree.b1eta,tree.b1phi,tree.b1m) )
            bjets.append( lVec(tree.b2pt,tree.b2eta,tree.b2phi,tree.b2m) )
            
        #met                                                                                                                                                                        
            metx,mety=tree.metpt*ROOT.TMath.Cos(tree.metphi),tree.metpt*ROOT.TMath.Sin(tree.metphi)
            
        #try to solve the kinematics (need to swap bl assignments)                                                                                                                  
            allSols=[]
            try:
                sols=doubleNeutrinoSolutions( (bjets[0],   bjets[1]),
                                              (leptons[0], leptons[1]),
                                              (metx,mety) )
                for isol in xrange(0,len(sols.nunu_s)):
                    top  = bjets[0]+leptons[0]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][0],0.)
                    top_ = bjets[1]+leptons[1]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][1],0.)
                    allSols.append( (0,top,top_) )
            except np.linalg.linalg.LinAlgError:
                pass
            try:
                sols=doubleNeutrinoSolutions( (bjets[0],   bjets[1]),
                                              (leptons[1], leptons[0]),
                                              (metx,mety) )
                for isol in xrange(0,len(sols.nunu_s)):
                    top  = bjets[0]+leptons[1]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][0],0.)
                    top_ = bjets[1]+leptons[0]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][1],0.)
                    allSols.append( (1,top,top_) )
            except np.linalg.linalg.LinAlgError :
                pass

        #sort solutions by increasing m(ttbar)                                                                                                                                      

            if len(allSols)==0: continue
            #print "length of allSols", len(allSols)
            allSols=sorted(allSols, key=lambda sol: (sol[1]+sol[2]).mass() )
           # print 'lowest m(ttbar) solution:', (allSols[0][1]+allSols[0][2]).mass()
            lowMtt=(allSols[0][1]+allSols[0][2]).mass()
            lowYtt=(allSols[0][1]+allSols[0][2]).Rapidity()

#            h1.Fill(lowYtt-tree.gen_ytt)


            varsel=[tree.run,tree.lumi,tree.ev,tree.rho,tree.nvtx,tree.channel,tree.mll,tree.nljets,tree.nbjets,tree.ht,
                    tree.metpt,tree.metphi,tree.l1pt,tree.l1eta,tree.l1phi,tree.l1m,tree.l2pt,tree.l2eta,tree.l2phi,tree.l2m,
                    tree.b1pt,tree.b1eta,tree.b1phi,tree.b1m,tree.b2pt,tree.b2eta,tree.b2phi,tree.b2m,
                    tree.px2,tree.py2,tree.pz2,tree.E2,tree.yvis,tree.ysum,tree.max_dy,tree.min_dy,
                    tree.deltarll,tree.deltaphill,tree.mlb,tree.mpp,tree.ypp,tree.gen_mtt,tree.gen_ytt,lowMtt,lowYtt] 

            newtree.Fill(array("f",varsel))
        
        fIn.cd()    
        fIn.Write()
        fIn.Close()
        
def main():

        KinematicsAlgorithm()


if __name__ == "__main__":
    main()
