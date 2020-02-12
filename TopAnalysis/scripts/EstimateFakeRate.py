import ROOT
import optparse
import json
import sys
import os
import numpy
import array
import math
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *


def EstimateFakeRate():

    inFileName='/afs/cern.ch/work/b/bribeiro/ab05162/Data13TeV_2017E_SingleMuon.root'
    
    print '....analysing',inFileName

    fIn=ROOT.TFile.Open(inFileName)

    #get fake nfwdtrk and xidist in each pixel
    fake_nfwdtrk0 = fIn.Get("mm_23_ntkrp")
    fake_nfwdtrk1 = fIn.Get("mm_123_ntkrp")
  
    fake_xi0 = fIn.Get("mm_newxi0")
    fake_xi1 = fIn.Get("mm_newxi1")

  #  nEv_passSel=fIn.Get("ee_1b_lowMlb_mll")
  #  nEv_passSel_Z=fIn.Get("ee_1b_lowMlb_Zpeak_mll")

 #   nSel = nEv_passSel.GetEntries()-nEv_passSel_Z.GetEntries()
  #  tree=fIn.Get("sel")
    
    if fake_nfwdtrk0!=0 and fake_nfwdtrk1!=0 and fake_xi0!=0 and fake_xi1!=0 :

        print 'Read fwdtrk and xi distributions from file'
        fake_nfwdtrk0.SetDirectory(0)
        fake_nfwdtrk1.SetDirectory(0)
        fake_xi0.SetDirectory(0)
        fake_xi1.SetDirectory(0)
        ntotal=20000
        print 'Number of events:',ntotal

    else:
        print 'Couldnt read histograms from file'

    #close plotter.root
    fIn.Close()
    nfake=0

    fake_y_h=ROOT.TH1F('fake_y','fake_y',20,-4,4)

    for n in xrange(0,ntotal):

        fake_M = 0    
        fake_y = 0  
        fake=None
        ROOT.gRandom.SetSeed(0)
        randomxi0=[]
        randomxi1=[]
        
        #generate n random trks for each pixel 
        nrandomtrks0 = fake_nfwdtrk0.GetRandom()
        nrandomtrks0 = int(nrandomtrks0)
        
        nrandomtrks1 = fake_nfwdtrk1.GetRandom()
        nrandomtrks1 = int(nrandomtrks1)
        
        print 'pixel0 ntrk:', nrandomtrks0
        print 'pixel1 ntrk:', nrandomtrks1        
  
        #generate a random xi for each trk 
        for itrk in xrange(0,nrandomtrks0):
            
            randomxi0.append(fake_xi0.GetRandom())
            #print 'xi0:',randomxi0[itrk]

            for i in xrange(0,nrandomtrks1):
                        
                randomxi1.append(fake_xi1.GetRandom())
                #print 'xi1:',randomxi1[i]

                #for the 2 lists of xis calculate the fake reconstructed mass
                for j in xrange(0,len(randomxi0)):
                    
                    for k in xrange(0,len(randomxi1)):
                        fake_M=0
                        fake_M = 13000*math.sqrt(randomxi0[j]*randomxi1[k])
                        fake_y = 0.5*math.log(randomxi0[j]/randomxi1[k])
                        if fake_M<600 and fake_M>300 :
                            #print 'fake M is',fake_M
                            fake_y_h.Fill(fake_y)
                            fake=True

        if fake==True : nfake=nfake+1

    fake_rate=float(nfake)/float(ntotal)
    #print 'nsel is:',nSel

    print 'nfake is',nfake

    print 'ntotal is',ntotal

    print 'The fake rate is',fake_rate

    fake_y_h.Draw()
    a = input('').split(" ")[0]

def main():

        EstimateFakeRate()

if __name__ == "__main__":
        sys.exit(main())


