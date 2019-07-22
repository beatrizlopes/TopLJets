import ROOT
import optparse
import json
import sys
import os
import numpy
import array
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

    #inFileName='/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/Data.root'
    outFileName='outputKinematics.root'
    inMCFileName='/afs/cern.ch/work/b/bribeiro/ab05162/Chunks/MC13TeV_2017_FPMC_HW_QED_ttbar_13TeV_120_0.root'
    #inMCFileName='MCttjets.root'

    print '....analysing',inMCFileName,'with output @',outFileName

    fOut=ROOT.TFile.Open(outFileName,'RECREATE')
    fOut.cd()
    #fIn=ROOT.TFile.Open(inFileName)
    #tree=fIn.Get("sel")
    fInMC=ROOT.TFile.Open(inMCFileName)
    tree=fInMC.Get("sel")
    tree2=fInMC.Get("sel2")


    #book histograms

#    hhh=ROOT.TH1F('DeltaPhill','DeltaPhi(ll)',50,-2,2)

#    histmm = ROOT.TH2F('mm_yttrec_vs_yttgen','y_{tt} (rec) vs. y_{tt} (gen)', 30, -2, 2, 30, -2, 2)        
#    histem = ROOT.TH2F('em_yttrec_vs_yttgen','y_{tt} (rec) vs. y_{tt} (gen)', 30, -2, 2, 30, -2, 2)        
#    histee = ROOT.TH2F('ee_yttrec_vs_yttgen','y_{tt} (rec) vs. y_{tt} (gen)', 30, -2, 2, 30, -2, 2)        
#    h1=ROOT.TH1F('yttrec-yttgen','[y_{tt} (rec) - y_{tt} (gen)]',50,-2,2)

    #if mass
    histmm = ROOT.TH2F('mm_mttrec_vs_mttgen','M_{tt} (rec) vs. M_{tt} (gen) (GeV)', 50, 0, 1200, 50, 0, 1200)        
    histem = ROOT.TH2F('em_mttrec_vs_mttgen','M_{tt} (rec) vs. M_{tt} (gen) (GeV)', 50, 0, 1200, 50, 0, 1200)        
    histee = ROOT.TH2F('ee_mttrec_vs_mttgen','M_{tt} (rec) vs. M_{tt} (gen) (GeV)', 50, 0, 1200, 50, 0, 1200)        
    h1=ROOT.TH1F('mttrec-mttgen','[M_{tt} (rec) - M_{tt} (gen)]',50,-2,2)
    h2=ROOT.TH1F('mttrec-mttgen2','[M_{tt} (rec) - M_{tt} (gen)]',50,-2,2)


    #loop over events in the tree and fill histos                                                                                                                                    
    totalEntries=tree.GetEntries()
    lVec = ROOT.Math.LorentzVector(ROOT.Math.PtEtaPhiM4D('double'))
    for i in xrange(0,totalEntries):

        tree.GetEntry(i)
        tree2.GetEntry(i)

        if i%100==0 : sys.stdout.write('\r [ %d/100 ] done' %(int(float(100.*i)/float(totalEntries))) )

        if abs(tree.channel)<100 : continue
        if abs(tree.channel)==11*13: evcat = 'em'
        if abs(tree.channel)==11*11: evcat = 'ee'
        if abs(tree.channel)==13*13: evcat = 'mm'


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
        except numpy.linalg.linalg.LinAlgError:
            pass
        try:
            sols=doubleNeutrinoSolutions( (bjets[0],   bjets[1]),
                                          (leptons[1], leptons[0]),
                                          (metx,mety) )
            for isol in xrange(0,len(sols.nunu_s)):
                top  = bjets[0]+leptons[1]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][0],0.)
                top_ = bjets[1]+leptons[0]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][1],0.)
                allSols.append( (1,top,top_) )
        except numpy.linalg.linalg.LinAlgError :
            pass
        #sort solutions by increasing m(ttbar)                                                                                                                                      

        if len(allSols)==0: continue
        allSols=sorted(allSols, key=lambda sol: (sol[1]+sol[2]).mass() )
#        print 'lowest m(ttbar) solution:', (allSols[0][1]+allSols[0][2]).mass()
        lowMtt=(allSols[0][1]+allSols[0][2]).mass()
        recytt=(allSols[0][1]+allSols[0][2]).Rapidity()
        
        #MASS
        if evcat=='mm': histmm.Fill(lowMtt,tree.gen_mtt)
        if evcat=='em': histem.Fill(lowMtt,tree.gen_mtt)    
        if evcat=='ee': histee.Fill(lowMtt,tree.gen_mtt)    
        h1.Fill((lowMtt-tree.gen_mtt)/tree.gen_mtt)
        h2.Fill((tree2.rec_mtt-tree2.gen_mtt)/tree2.gen_mtt)

        #y
#        if evcat=='mm': histmm.Fill(recytt,tree.gen_ytt)
#        if evcat=='em': histem.Fill(recytt,tree.gen_ytt)    
#        if evcat=='ee': histee.Fill(recytt,tree.gen_ytt)    
#        h1.Fill(recytt-tree.gen_ytt)
        

    #hhh.Draw()    
    c=ROOT.TCanvas()
    c.Divide(2,2)
    i=1
    #line=ROOT.TLine(0,0,3.1415,3.1415)

    for h in (histmm,histem,histee):        
        h.SetXTitle("y_{tt} (GeV) (Rec. from CMS central data)")
        h.SetYTitle("y_{tt} (GeV) (at generator level)")
        #h.SetXTitle("M_{tt} (GeV) (Rec. from CMS central data)")
        #h.SetYTitle("M_{tt} (GeV) (at generator level)")
        h.SetZTitle("Events")
        c.cd(i)
        i=i+1
        h.Draw("COLZ")
       # line.Draw()

        #st = h.FindObject("stats")
        #st.SetX1NDC(0.0)
        #st.SetX2NDC(1.0)

        c.cd(4)
        h1.Draw()
        h2.Draw("same")
        h1.Fit('gaus')
        h2.Fit("gaus")
  #      Lorentzian = ROOT.TF1('lorentzian','(0.5*[0]*[1]/TMath::Pi()) / TMath::Max(1.e-10,(x[0]-[2])*(x[0]-[2]) + .25*[1]*[1])',-1,1)
   #     Lorentzian.SetParameters(400,1,0)
    #    h1.Fit(Lorentzian)
  #      DoubleGaussian = ROOT.TF1('doublegaussian','[0]/([1]*sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*(x[0]-[2])*(x[0]-[2])/([1]*[1]))+ [3]/([4]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*(x[0]-[5])*(x[0]-[5])/([4]*[4]))',-1.5,1.5)
   #     DoubleGaussian.SetParameters(150,0.71,0,100,0.2,0)
   #     h1.Fit(DoubleGaussian)

    c.SaveAs("KinAlgDeltaPhi.png")
    #c.SaveAs("KinAlgMass.png")
    a = input('').split(" ")[0]
    #fOut.Close()

def main():

        KinematicsAlgorithm()


if __name__ == "__main__":
        sys.exit(main())
