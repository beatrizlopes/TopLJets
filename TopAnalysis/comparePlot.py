import ROOT
import sys

inF=sys.argv[1]
var=sys.argv[2]

#open file
fIn=ROOT.TFile.Open(inF)
histList=[]
for c in ['1b','1b_2b','1b_2b_low_mlb']:
    histList.append( fIn.Get('mm_{0}_{1}'.format(c,var)) )
    histList[-1].SetDirectory(0)
fIn.Close()


for i in xrange(0,len(histList)):

    histList[i].Draw( 'hist' if i==0 else 'histsame' )

raw_input()
    
