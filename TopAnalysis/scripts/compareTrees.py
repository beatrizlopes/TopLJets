import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array

def compareTrees():

    syst = sys.argv[1]
    files = sys.argv[2:]
    for filename in files:

        inFileName=filename

#        if "TT" in filename: continue
    
        print('....analysing',inFileName)

        fIn=ROOT.TFile.Open(inFileName,"UPDATE")
        #fOut=ROOT.TFile.Open("teste.root","RECREATE")

        sel=fIn.Get("SEL")
        sel_systup=fIn.Get(("SEL_{0}up".format(syst)))
        sel_systdn=fIn.Get(("SEL_{0}dn".format(syst)))
        
        nentries=max(sel.GetEntries(),sel_systup.GetEntries(),sel_systdn.GetEntries())
        nnans=0
        nan_sel=0
        nan_selup=0 
        nan_seldn=0
        nan_sel2=0
        nan_selup2=0 
        nan_seldn2=0
        nan_sel3=0
        nan_selup3=0 
        nan_seldn3=0


        for i in range(0,nentries) :

            sel.GetEntry(i)
            sel_systup.GetEntry(i)
            sel_systdn.GetEntry(i)

            print 'gen_mtt sel:',sel.gen_mtt,' sel_systup:',sel_systup.gen_mtt,' sel_systdn:',sel_systdn.gen_mtt
            print 'yvis sel:',sel.yvis,' sel_systup:',sel_systup.yvis,' sel_systdn:',sel_systdn.yvis
            print 'ysum sel:',sel.ysum,' sel_systup:',sel_systup.ysum,' sel_systdn:',sel_systdn.ysum
            print 'max_dy sel:',sel.max_dy,' sel_systup:',sel_systup.max_dy,' sel_systdn:',sel_systdn.max_dy

            if sel.yvis!=sel.yvis or sel_systup.yvis!=sel_systup.yvis or sel_systdn.yvis!=sel_systdn.yvis : 
                print '>>>>>>>>>>>>>>>>>>>> found nan in yvis in entry ',i
                nnans=nnans+1
                if sel.yvis!=sel.yvis : nan_sel+=1
                if sel_systup.yvis!=sel_systup.yvis : nan_selup+=1
                if sel_systdn.yvis!=sel_systdn.yvis : nan_seldn+=1

            if sel.ysum!=sel.ysum or sel_systup.ysum!=sel_systup.ysum or sel_systdn.ysum!=sel_systdn.ysum : 
                print '>>>>>>>>>>>>>>>>>>>> found nan in ysum in entry ',i
                nnans=nnans+1
                if sel.ysum!=sel.ysum : nan_sel2+=1
                if sel_systup.ysum!=sel_systup.ysum : nan_selup2+=1
                if sel_systdn.ysum!=sel_systdn.ysum : nan_seldn2+=1

            if sel.max_dy!=sel.max_dy or sel_systup.max_dy!=sel_systup.max_dy or sel_systdn.max_dy!=sel_systdn.max_dy : 
                print '>>>>>>>>>>>>>>>>>>>> found nan in max_dy in entry ',i
                nnans=nnans+1
                if sel.max_dy!=sel.max_dy : nan_sel3+=1
                if sel_systup.max_dy!=sel_systup.max_dy : nan_selup3+=1
                if sel_systdn.max_dy!=sel_systdn.max_dy : nan_seldn3+=1

        print sel.GetEntries(), 'events in tree named sel'
        print sel_systup.GetEntries(), 'events in tree named sel_systup'
        print sel_systdn.GetEntries(), 'events in tree named sel_systdn'
        print nnans,' nan values were found'
        print nan_sel,'nan values were found in yvis tree sel'
        print nan_selup,'nan values were found in yvis tree selup'
        print nan_seldn,'nan values were found in yvis tree seldn'
        print nan_sel2,'nan values were found in ysum tree sel'
        print nan_selup2,'nan values were found in ysum tree selup'
        print nan_seldn2,'nan values were found in ysum tree seldn'
        print nan_sel3,'nan values were found in max_dy tree sel'
        print nan_selup3,'nan values were found in max_dy tree selup'
        print nan_seldn3,'nan values were found in max_dy tree seldn'


        fIn.Close()

def main():

        compareTrees()


if __name__ == "__main__":
    main()
