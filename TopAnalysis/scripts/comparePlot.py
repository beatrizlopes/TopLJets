import sys
import ROOT

   
def main():

#    ROOT.gStyle.SetOptTitle(0)
#    ROOT.gStyle.SetOptStat(0)
#    ROOT.gROOT.SetBatch(True)

    baseDir='./'
    inFiles=ROOT.TFile.Open('testsel.root')
    canvas = ROOT.TCanvas('canvas', '', 500, 500)

    h1=inFiles.Get("mm_mll")
    h1.Draw()
    canvas.SaveAs('plot.png')   
    
