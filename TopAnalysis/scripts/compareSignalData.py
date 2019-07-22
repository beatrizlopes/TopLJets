import ROOT
import optparse
import json
import sys
import os
import numpy
import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *


def compareSignalData():

    plotterFileName='plots/sel/plotter.root'
    signalFileName='signal.root'
    
    print '....analysing',plotterFileName,'and comparing with',signalFileName

    
    plotter=ROOT.TFile.Open(plotterFileName)
    signal=ROOT.TFile.Open(signalFileName)

    #get histograms

    em_mRP=plotter.Get("em_1b_lowMlb_yRP/em_1b_lowMlb_yRP")
    ee_mRP=plotter.Get("ee_1b_lowMlb_yRP/ee_1b_lowMlb_yRP")
    mm_mRP=plotter.Get("mm_1b_lowMlb_yRP/mm_1b_lowMlb_yRP")

    em_mRP_s=signal.Get("em_1b_lowMlb_yRP")
    ee_mRP_s=signal.Get("ee_1b_lowMlb_yRP")
    mm_mRP_s=signal.Get("mm_1b_lowMlb_yRP")

    #normalize them to 1
    em_mRP.Scale(em_mRP_s.GetEntries()/em_mRP.GetEntries())
    ee_mRP.Scale(ee_mRP_s.GetEntries()/ee_mRP.GetEntries())
    mm_mRP.Scale(mm_mRP_s.GetEntries()/mm_mRP.GetEntries())

    em_mRP_s.Scale(1)
    ee_mRP_s.Scale(1)
    mm_mRP_s.Scale(1)

    #draw them
    
    c=ROOT.TCanvas()
    c.Divide(2,2)

    c.cd(1)
    em_mRP.SetMarkerColor(38)
    em_mRP_s.SetMarkerColor(46)
    em_mRP.SetMarkerStyle(33)
    em_mRP_s.SetMarkerStyle(33)
    em_mRP.SetStats(0)
    em_mRP_s.SetStats(0)
    em_mRP.Draw()
    em_mRP_s.Draw("same")

    c.cd(2)
    ee_mRP.SetMarkerColor(38)
    ee_mRP_s.SetMarkerColor(46)
    ee_mRP.SetMarkerStyle(33)
    ee_mRP_s.SetMarkerStyle(33)
    ee_mRP.SetStats(0)
    ee_mRP_s.SetStats(0)
    ee_mRP.Draw()
    ee_mRP_s.Draw("same")

    c.cd(3)
    mm_mRP.SetMarkerColor(38)
    mm_mRP_s.SetMarkerColor(46)
    mm_mRP.SetMarkerStyle(33)
    mm_mRP_s.SetMarkerStyle(33)
    mm_mRP.SetStats(0)
    mm_mRP_s.SetStats(0)    
    mm_mRP.Draw()
    mm_mRP_s.Draw("same")

    c.SaveAs("compareSignalData.png")

    a = input('').split(" ")[0]


def main():

        compareSignalData()


if __name__ == "__main__":
        sys.exit(main())
