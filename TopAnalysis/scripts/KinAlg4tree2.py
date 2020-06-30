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

#        if "TT" in filename: continue
    
        print('....analysing',inFileName)

        fIn=ROOT.TFile.Open(inFileName,"UPDATE")
        #fOut=ROOT.TFile.Open("teste.root","RECREATE")

                
        newtree=ROOT.TNtuple("Sel","run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:weight")
            
        newtree.SetDirectory(fIn)
                
        totalEntries=newtree.GetEntries()
        lVec = ROOT.Math.LorentzVector(ROOT.Math.PtEtaPhiM4D('double'))

        for i in xrange(0,totalEntries):
            
            syst_tree.GetEntry(i)
            
            if i%100==0 : sys.stdout.write('\r [ %d/100 ] done' %(int(float(100.*i)/float(totalEntries))) )                
            
            #leptons                                                                                                                     
            leptons=[]
            leptons.append( lVec(syst_tree.l1pt,syst_tree.l1eta,syst_tree.l1phi,syst_tree.l1m) )
            leptons.append( lVec(syst_tree.l2pt,syst_tree.l2eta,syst_tree.l2phi,syst_tree.l2m) )
            if len(leptons)<2 : continue
            
            #preselect the b-jets (save always the jet and the gen jet)                                                                  
            bjets=[]
            bjets.append( lVec(syst_tree.b1pt,syst_tree.b1eta,syst_tree.b1phi,syst_tree.b1m) )
            bjets.append( lVec(syst_tree.b2pt,syst_tree.b2eta,syst_tree.b2phi,syst_tree.b2m) )
                
            #met                                                                                                                         
            metx,mety=syst_tree.metpt*ROOT.TMath.Cos(syst_tree.metphi),syst_tree.metpt*ROOT.TMath.Sin(syst_tree.metphi)
            
            #try to solve the kinematics (need to swap bl assignments)                                                                                                                  
            allSols=[]
                    
            if bjets[0].E()!=0 and bjets[1].E()!=0 :
                
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
                                                      
            if len(allSols)==0: 
                lowMtt=-1
                lowYtt=-10

            else :
                        
                #print "length of allSols", len(allSols)
                allSols=sorted(allSols, key=lambda sol: (sol[1]+sol[2]).mass() )
                # print 'lowest m(ttbar) solution:', (allSols[0][1]+allSols[0][2]).mass()
                lowMtt=(allSols[0][1]+allSols[0][2]).mass()
                lowYtt=(allSols[0][1]+allSols[0][2]).Rapidity()
                
                            
            varsel=[syst_tree.run,syst_tree.lumi,syst_tree.ev,syst_tree.rho,syst_tree.channel,syst_tree.mll,syst_tree.nljets,syst_tree.nbjets,syst_tree.ht,
                        syst_tree.metpt,syst_tree.metphi,syst_tree.l1pt,syst_tree.l1eta,syst_tree.l1phi,syst_tree.l1m,syst_tree.l2pt,syst_tree.l2eta,syst_tree.l2phi,syst_tree.l2m,
                        syst_tree.b1pt,syst_tree.b1eta,syst_tree.b1phi,syst_tree.b1m,syst_tree.b2pt,syst_tree.b2eta,syst_tree.b2phi,syst_tree.b2m,
                        syst_tree.px2,syst_tree.py2,syst_tree.pz2,syst_tree.E2,syst_tree.yvis,syst_tree.ysum,syst_tree.max_dy,syst_tree.min_dy,
                        syst_tree.deltarll,syst_tree.deltaphill,syst_tree.mlb,syst_tree.xi0,syst_tree.xi1,syst_tree.mpp,syst_tree.ypp,syst_tree.gen_mtt,syst_tree.gen_ytt,lowMtt,lowYtt,syst_tree.weight] 


            newtree.Fill(array("f",varsel))                        
                
        newtree.Write("",ROOT.TObject.kOverwrite)

        fIn.cd()    
        fIn.Write()
        fIn.Close()
        
def main():

        KinematicsAlgorithm()


if __name__ == "__main__":
    main()
