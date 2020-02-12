import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist
from TopLJets2015.TopAnalysis.nuSolutions import *

def drawshapes():

    inFileName="plots/sel/plotter.root"
    
    print('....analysing',inFileName)
    
    fIn=ROOT.TFile.Open(inFileName,"READ")
    #fOut=ROOT.TFile.Open("teste.root","RECREATE")

    hDY_after=fIn.Get("em_1b_lowMlb_newmRP/em_1b_lowMlb_newmRP_DY")
    hTT_after=fIn.Get("em_1b_lowMlb_newmRP/em_1b_lowMlb_newmRP_Top")

    hDY=fIn.Get("em_newmRP/em_newmRP_DY")
    hTT=fIn.Get("em_newmRP/em_newmRP_Top")

    hdata=fIn.Get("em_1b_lowMlb_newmRP/em_1b_lowMlb_newmRP")
    hdata_presel=fIn.Get("em_newmRP/em_newmRP")

    hdata.Scale(1/hdata.Integral())
    hdata_presel.Scale(1/hdata_presel.Integral())
    hTT_after.Scale(1/hTT_after.Integral())
    hDY_after.Scale(1/hDY_after.Integral())
    hTT.Scale(1/hTT.Integral())
    hDY.Scale(1/hDY.Integral())

    hTT_after.SetMarkerSize(2)
    hDY_after.SetMarkerSize(3)
    hTT.SetMarkerSize(3)
    hDY.SetMarkerSize(3)


    hTT_after.SetMarkerStyle(29)
    hDY_after.SetMarkerStyle(29)
    hTT.SetMarkerStyle(2)
    hDY.SetMarkerStyle(2)

    #ttbar in blue and DY in green
    hTT_after.SetMarkerColor(4)
    hDY_after.SetMarkerColor(3)
    hTT.SetMarkerColor(4)
    hDY.SetMarkerColor(3)
    
    hdata_presel.SetMarkerColor(3)
    hdata_presel.SetMarkerSize(1)

    c1=ROOT.TCanvas()
    c1.Divide(2,1)

    c1.cd(1)
    hdata.Draw("")
    hdata_presel.Draw("same")
 
    c1.cd(2)
    hTT_after.Draw("")
#    hDY_after.Draw("same")
    hTT.Draw("same")
    hDY.Draw("same")

    a = input('').split(" ")[0]

def main():

        drawshapes()


if __name__ == "__main__":
    main()
