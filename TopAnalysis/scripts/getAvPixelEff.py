import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *


def getAvPixelEff():

    filename = sys.argv[1]

    print('....analysing',filename)
        
    fIn=ROOT.TFile.Open(filename,"READ")

    B_45=fIn.Get("Pixel/2017/2017B/h45_220_2017B_all_1D")
    B_56=fIn.Get("Pixel/2017/2017B/h56_220_2017B_all_1D")
    C1_45=fIn.Get("Pixel/2017/2017C1/h45_220_2017C1_all_1D")
    C1_56=fIn.Get("Pixel/2017/2017C1/h56_220_2017C1_all_1D")
    E_45=fIn.Get("Pixel/2017/2017E/h45_220_2017E_all_1D")
    E_56=fIn.Get("Pixel/2017/2017E/h56_220_2017E_all_1D")
    F1_45=fIn.Get("Pixel/2017/2017F1/h45_220_2017F1_all_1D")
    F1_56=fIn.Get("Pixel/2017/2017F1/h56_220_2017F1_all_1D")

    B_Lumi=2.4
    C1_Lumi=5.3
    E_Lumi=9
    F1_Lumi=1.7
    totalLumi=B_Lumi+C1_Lumi+E_Lumi+F1_Lumi

    fOut=ROOT.TFile.Open("averageEff.root","RECREATE")

    nbins=B_45.GetNbinsX()

    all_45=ROOT.TH1D("eff_45","eff_45",nbins,B_45.GetXaxis().GetXmin(),B_45.GetXaxis().GetXmax())
    all_56=ROOT.TH1D("eff_56","eff_56",nbins,B_56.GetXaxis().GetXmin(),B_56.GetXaxis().GetXmax())

    for i in xrange(0,nbins):
        Beff=B_45.GetBinContent(i)*B_Lumi/totalLumi
        C1eff=C1_45.GetBinContent(i)*C1_Lumi/totalLumi
        Eeff=E_45.GetBinContent(i)*E_Lumi/totalLumi
        F1eff=F1_45.GetBinContent(i)*F1_Lumi/totalLumi
        eff=Beff+C1eff+Eeff+F1eff

        Beff1=B_56.GetBinContent(i)*B_Lumi/totalLumi
        C1eff1=C1_56.GetBinContent(i)*C1_Lumi/totalLumi
        Eeff1=E_56.GetBinContent(i)*E_Lumi/totalLumi
        F1eff1=F1_56.GetBinContent(i)*F1_Lumi/totalLumi
        eff1=Beff1+C1eff1+Eeff1+F1eff1

        all_45.SetBinContent(i,eff)
        all_56.SetBinContent(i,eff1)

    fOut.cd()    

    all_45.Write()
    all_56.Write()

    fOut.Close()
    fIn.Close()

def main():

        getAvPixelEff()


if __name__ == "__main__":
    main()
