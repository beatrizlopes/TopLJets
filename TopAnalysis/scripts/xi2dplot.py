import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *


def xi2dplot():

    args = sys.argv[1:]
    goodevts=0
    c=ROOT.TCanvas()
    c.Divide(2)
    g0=ROOT.TH2D("xi0","xi0",50,0,0.05,50,0,0.05)
    g1=ROOT.TH2D("xi1","xi1",50,0,0.05,50,0,0.05)


    for filename in args:

        print('....analysing',filename)
        

        fIn=ROOT.TFile.Open(filename,"READ")

        reg=fIn.Get("Reg")

        for i in xrange(0,reg.GetEntries()):
            reg.GetEntry(i)

#            if reg.channel==121: g.SetMarkerColor(ROOT.kRed)
#            if reg.channel==143: g.SetMarkerColor(ROOT.kBlack)
#            if reg.channel==169: g.SetMarkerColor(ROOT.kBlue)
            if abs(reg.xi0-reg.xi0tt)<0.01 and abs(reg.xi1-reg.xi1tt)<0.01 :
                g0.Fill(reg.xi0,reg.xi0tt)
                g1.Fill(reg.xi1,reg.xi1tt)
                goodevts+=1
#            print reg.xi0, reg.xi0tt


    line0=ROOT.TLine(0,0,0.2,0.2)
    c.cd(1)
    ROOT.gStyle.SetOptStat(0)
    g0.Draw("*")
    line0.Draw("same")
    c.cd(2)
    g1.Draw("*")
    line0.Draw("same")
    print goodevts

#else: g.Draw("* same")
        
 #       ifile=ifile+1

    c.SaveAs("xi.pdf")
    

def main():

        xi2dplot()


if __name__ == "__main__":
    main()
