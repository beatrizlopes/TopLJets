import ROOT
import optparse
import json
import sys
import os
import numpy
import array
from TopLJets2015.TopAnalysis.storeTools import getEOSlslist

def copytree():

    inFileName='mvadata.root'
    outFileName='mvainput.root'
    
    fOut=ROOT.TFile.Open(outFileName,'RECREATE')
    fIn=ROOT.TFile.Open(inFileName)    

    tree=fIn.Get("mvainput")
    
    fOut.cd()
    newtree=ROOT.TTree('t','t')

    newtree=tree.CopyTree("")

    #fIn.Close()
    
    newtree.Write()
    fOut.Close()

def main():

        copytree()

if __name__ == "__main__":
        sys.exit(main())
