import ROOT
import optparse
import json
import sys
import os
import numpy as np
from array import array
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

    args = sys.argv[1:]
    for filename in args:

        inFileName=filename

#        if "TT" in filename: continue
    
        print('....analysing',inFileName)

        fIn=ROOT.TFile.Open(inFileName,"UPDATE")
        #fOut=ROOT.TFile.Open("teste.root","RECREATE")


        systNames= {"nom","thsysts","puup",
                    "eetrigup",
                    "emtrigup",
                    "mmtrigup",
                    "eselup",  
                    "mselup",  
                    "l1prefireup", 
                    "ees1up", "ees2up",  "ees3up", "ees4up", "ees5up", "ees6up", 
                    "ees7up",
                    "mes1up", "mes2up", "mes3up", "mes4up",
           #"btagjesup",        "btagjesdnup",                                                                                   
                    "btaglfup",
                    "btaghfup",                                                                           
                    "JERup",
                    "topptup",      
                    "AbsoluteStatJECup","AbsoluteScaleJECup","AbsoluteMPFBiasJECup",
                    "FragmentationJECup","SinglePionECALJECup","SinglePionHCALJECup",
                    "FlavorPureGluonJECup","FlavorPureQuarkJECup",
                    "FlavorPureCharmJECup","FlavorPureBottomJECup","TimePtEtaJECup",
                    "RelativeJEREC1JECup","RelativeJEREC2JECup","RelativeJERHFJECup",
                    "RelativePtBBJECup","RelativePtEC1JECup","RelativePtEC2JECup",
                    "RelativePtHFJECup","RelativeBalJECup","RelativeFSRJECup",
                    "RelativeStatFSRJECup","RelativeStatECJECup","RelativeStatHFJECup",
                    "PileUpDataMCJECup","PileUpPtRefJECup","PileUpPtBBJECup",
                    "PileUpPtEC1JECup","PileUpPtEC2JECup","PileUpPtHFJECup",
                    "bfragup",
                    "pudn",
                    "eetrigdn",
                    "emtrigdn",
                    "mmtrigdn",
                    "eseldn",  
                    "mseldn",  
                    "l1prefiredn", 
                    "ees1dn", "ees2dn",  "ees3dn", "ees4dn", "ees5dn", "ees6dn", 
                    "ees7dn",
                    "mes1dn", "mes2dn", "mes3dn", "mes4dn",
            #"btagjesdn",        "btagjesdndn",                                                                                   
                    "btaglfdn",
                    "btaghfdn",                                                                           
                    "JERdn",
                    "topptdn",      
                    "AbsoluteStatJECdn","AbsoluteScaleJECdn","AbsoluteMPFBiasJECdn",
                    "FragmentationJECdn","SinglePionECALJECdn","SinglePionHCALJECdn",
                    "FlavorPureGluonJECdn","FlavorPureQuarkJECdn",
                    "FlavorPureCharmJECdn","FlavorPureBottomJECdn","TimePtEtaJECdn",
                    "RelativeJEREC1JECdn","RelativeJEREC2JECdn","RelativeJERHFJECdn",
                    "RelativePtBBJECdn","RelativePtEC1JECdn","RelativePtEC2JECdn",
                    "RelativePtHFJECdn","RelativeBalJECdn","RelativeFSRJECdn",
                    "RelativeStatFSRJECdn","RelativeStatECJECdn","RelativeStatHFJECdn",
                    "PileUpDataMCJECdn","PileUpPtRefJECdn","PileUpPtBBJECdn",
                    "PileUpPtEC1JECdn","PileUpPtEC2JECdn","PileUpPtHFJECdn",
                    "bfragdn"
                    }

        if "Data" in inFileName : systNames={"nom"}
        if "training" in inFileName : systNames={"nom"}

        for s in systNames :
                
            if not fIn.GetListOfKeys().Contains("sel{0}".format('' if s=="nom" else '_'+s)) : continue
            
            print 'analysing syst {0}'.format(s)

            syst_tree=fIn.Get("sel{0}".format('' if s=="nom" else '_'+s))
            #                    newtree=ROOT.TTree("sel","sel")
            if 'thsysts' not in s : 
                newtree=ROOT.TNtuple("Sel{0}".format('' if s=="nom" else '_'+s),"Sel{0}".format('' if s=="nom" else '_'+s),"run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:weight")
            else :
                newtree=ROOT.TNtuple("Sel{0}".format('_'+s),"Sel{0}".format('_'+s),"run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:weight:w_muRup:w_muRdn:w_muFup:w_muFdn:w_muRmuFup:w_muRmuFdn:w_PDF000:w_PDF001:w_PDF002:w_PDF003:w_PDF004:w_PDF005:w_PDF006:w_PDF007:w_PDF008:w_PDF009:w_PDF010:w_PDF011:w_PDF012:w_PDF013:w_PDF014:w_PDF015:w_PDF016:w_PDF017:w_PDF018:w_PDF019:w_PDF020:w_PDF021:w_PD022:w_PDF023:w_PDF024:w_PDF025:w_PDF026:w_PDF027:w_PDF028:w_PDF029:w_PDF030:w_PDF031:w_PDF032:w_PDF033:w_PDF034:w_PDF035:w_PDF036:w_PDF037:w_PDF038:w_PDF039:w_PDF040:w_PDF041:w_PDF042:w_PDF043:w_PDF044:w_PDF045:w_PDF046:w_PDF047:w_PDF048:w_PDF049:w_PDF050:w_PDF051:w_PDF052:w_PDF053:w_PDF054:w_PDF055:w_PDF056:w_PDF057:w_PDF058:w_PDF059:w_PDF060:w_PDF061:w_PDF062:w_PDF063:w_PDF064:w_PDF065:w_PDF066:w_PDF067:w_PDF068:w_PDF069:w_PDF070:w_PDF071:w_PDF072:w_PDF073:w_PDF074:w_PDF075:w_PDF076:w_PDF077:w_PDF078:w_PDF079:w_PDF080:w_PDF081:w_PDF082:w_PDF083:w_PDF084:w_PDF085:w_PDF086:w_PDF087:w_PDF088:w_PDF089:w_PDF090:w_PDF091:w_PDF092:w_PDF093:w_PDF094:w_PDF095:w_PDF096:w_PDF097:w_PDF098:w_PDF099:w_PDF100:w_PDF101:w_PDF102")
            
            newtree.SetDirectory(fIn)
                
            #branch.SetEntries(tree.GetEntries())
            #fOut.cd();
            #        newtree.SetDirectory(fOut);
            
            #loop over events in the tree and fill histos                                                             
            
            totalEntries=syst_tree.GetEntries()
            lVec = ROOT.Math.LorentzVector(ROOT.Math.PtEtaPhiM4D('double'))
                #        h1=ROOT.TH1F('yttrec-yttgen','[y_{tt} (rec) - y_{tt} (gen)]',50,-2,2)

            for i in xrange(0,totalEntries):
                    
                syst_tree.GetEntry(i)
                
                if i%100==0 : sys.stdout.write('\r [ %d/100 ] done' %(int(float(100.*i)/float(totalEntries))) )                
                
                #leptons                                                                                                                     
                leptons=[]
                leptons.append( lVec(syst_tree.l1pt,syst_tree.l1eta,syst_tree.l1phi,syst_tree.l1m) )
                leptons.append( lVec(syst_tree.l2pt,syst_tree.l2eta,syst_tree.l2phi,syst_tree.l2m) )
                #if len(leptons)<2 : continue
                    
                #preselect the b-jets (save always the jet and the gen jet)                                                                  
                bjets=[]
                bjets.append( lVec(syst_tree.b1pt,syst_tree.b1eta,syst_tree.b1phi,syst_tree.b1m) )
                bjets.append( lVec(syst_tree.b2pt,syst_tree.b2eta,syst_tree.b2phi,syst_tree.b2m) )
                
                #met                                                                                                                         
                metx,mety=syst_tree.metpt*ROOT.TMath.Cos(syst_tree.metphi),syst_tree.metpt*ROOT.TMath.Sin(syst_tree.metphi)
                    
                #try to solve the kinematics (need to swap bl assignments)                                                                                                                  
                allSols=[]
                    
                if bjets[0].E()!=0 and bjets[1].E()!=0 :
                        
                    try:
                        sols=doubleNeutrinoSolutions( (bjets[0],   bjets[1]),
                                                      (leptons[0], leptons[1]),
                                                      (metx,mety) )
                        for isol in xrange(0,len(sols.nunu_s)):
                            top  = bjets[0]+leptons[0]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][0],0.)
                            top_ = bjets[1]+leptons[1]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][1],0.)
                            allSols.append( (0,top,top_) )
                    except np.linalg.linalg.LinAlgError:
                        pass
                    try:
                        sols=doubleNeutrinoSolutions( (bjets[0],   bjets[1]),
                                                      (leptons[1], leptons[0]),
                                                      (metx,mety) )
                        for isol in xrange(0,len(sols.nunu_s)):
                            top  = bjets[0]+leptons[1]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][0],0.)
                            top_ = bjets[1]+leptons[0]+convertToPtEtaPhiM(lVec,sols.nunu_s[isol][1],0.)
                            allSols.append( (1,top,top_) )
                    except np.linalg.linalg.LinAlgError :
                        pass

                #sort solutions by increasing m(ttbar)                                                                                   
                                                      
                if len(allSols)==0: 
                    lowMtt=-1
                    lowYtt=-10

                else :
                        
                    #print "length of allSols", len(allSols)
                    allSols=sorted(allSols, key=lambda sol: (sol[1]+sol[2]).mass() )
                    # print 'lowest m(ttbar) solution:', (allSols[0][1]+allSols[0][2]).mass()
                    lowMtt=(allSols[0][1]+allSols[0][2]).mass()
                    lowYtt=(allSols[0][1]+allSols[0][2]).Rapidity()

                #            h1.Fill(lowYtt-syst_tree.gen_ytt)
                if 'thsysts' not in s:
                    varsel=[syst_tree.run,syst_tree.lumi,syst_tree.ev,syst_tree.rho,syst_tree.channel,syst_tree.mll,syst_tree.nljets,syst_tree.nbjets,syst_tree.ht,
                        syst_tree.metpt,syst_tree.metphi,syst_tree.l1pt,syst_tree.l1eta,syst_tree.l1phi,syst_tree.l1m,syst_tree.l2pt,syst_tree.l2eta,syst_tree.l2phi,syst_tree.l2m,
                        syst_tree.b1pt,syst_tree.b1eta,syst_tree.b1phi,syst_tree.b1m,syst_tree.b2pt,syst_tree.b2eta,syst_tree.b2phi,syst_tree.b2m,
                        syst_tree.px2,syst_tree.py2,syst_tree.pz2,syst_tree.E2,syst_tree.yvis,syst_tree.ysum,syst_tree.max_dy,syst_tree.min_dy,
                        syst_tree.deltarll,syst_tree.deltaphill,syst_tree.mlb,syst_tree.xi0,syst_tree.xi1,syst_tree.mpp,syst_tree.ypp,syst_tree.gen_mtt,syst_tree.gen_ytt,lowMtt,lowYtt,syst_tree.weight] 
                else :
                    varsel=[syst_tree.run,syst_tree.lumi,syst_tree.ev,syst_tree.rho,syst_tree.channel,syst_tree.mll,syst_tree.nljets,syst_tree.nbjets,syst_tree.ht,
                            syst_tree.metpt,syst_tree.metphi,syst_tree.l1pt,syst_tree.l1eta,syst_tree.l1phi,syst_tree.l1m,syst_tree.l2pt,syst_tree.l2eta,syst_tree.l2phi,syst_tree.l2m,
                            syst_tree.b1pt,syst_tree.b1eta,syst_tree.b1phi,syst_tree.b1m,syst_tree.b2pt,syst_tree.b2eta,syst_tree.b2phi,syst_tree.b2m,
                            syst_tree.px2,syst_tree.py2,syst_tree.pz2,syst_tree.E2,syst_tree.yvis,syst_tree.ysum,syst_tree.max_dy,syst_tree.min_dy,
                            syst_tree.deltarll,syst_tree.deltaphill,syst_tree.mlb,syst_tree.xi0,syst_tree.xi1,syst_tree.mpp,syst_tree.ypp,syst_tree.gen_mtt,syst_tree.gen_ytt,lowMtt,lowYtt,syst_tree.weight,syst_tree.w_muRup,syst_tree.w_muRdn,syst_tree.w_muFup,syst_tree.w_muFdn,syst_tree.w_muRmuFup,syst_tree.w_muRmuFdn,syst_tree.w_PDF000,syst_tree.w_PDF001,syst_tree.w_PDF002,syst_tree.w_PDF003,syst_tree.w_PDF004,syst_tree.w_PDF005,syst_tree.w_PDF006,syst_tree.w_PDF007,syst_tree.w_PDF008,syst_tree.w_PDF009,syst_tree.w_PDF010,syst_tree.w_PDF011,syst_tree.w_PDF012,syst_tree.w_PDF013,syst_tree.w_PDF014,syst_tree.w_PDF015,syst_tree.w_PDF016,syst_tree.w_PDF017,syst_tree.w_PDF018,syst_tree.w_PDF019,syst_tree.w_PDF020,syst_tree.w_PDF021,syst_tree.w_PD022,syst_tree.w_PDF023,syst_tree.w_PDF024,syst_tree.w_PDF025,syst_tree.w_PDF026,syst_tree.w_PDF027,syst_tree.w_PDF028,syst_tree.w_PDF029,syst_tree.w_PDF030,syst_tree.w_PDF031,syst_tree.w_PDF032,syst_tree.w_PDF033,syst_tree.w_PDF034,syst_tree.w_PDF035,syst_tree.w_PDF036,syst_tree.w_PDF037,syst_tree.w_PDF038,syst_tree.w_PDF039,syst_tree.w_PDF040,syst_tree.w_PDF041,syst_tree.w_PDF042,syst_tree.w_PDF043,syst_tree.w_PDF044,syst_tree.w_PDF045,syst_tree.w_PDF046,syst_tree.w_PDF047,syst_tree.w_PDF048,syst_tree.w_PDF049,syst_tree.w_PDF050,syst_tree.w_PDF051,syst_tree.w_PDF052,syst_tree.w_PDF053,syst_tree.w_PDF054,syst_tree.w_PDF055,syst_tree.w_PDF056,syst_tree.w_PDF057,syst_tree.w_PDF058,syst_tree.w_PDF059,syst_tree.w_PDF060,syst_tree.w_PDF061,syst_tree.w_PDF062,syst_tree.w_PDF063,syst_tree.w_PDF064,syst_tree.w_PDF065,syst_tree.w_PDF066,syst_tree.w_PDF067,syst_tree.w_PDF068,syst_tree.w_PDF069,syst_tree.w_PDF070,syst_tree.w_PDF071,syst_tree.w_PDF072,syst_tree.w_PDF073,syst_tree.w_PDF074,syst_tree.w_PDF075,syst_tree.w_PDF076,syst_tree.w_PDF077,syst_tree.w_PDF078,syst_tree.w_PDF079,syst_tree.w_PDF080,syst_tree.w_PDF081,syst_tree.w_PDF082,syst_tree.w_PDF083,syst_tree.w_PDF084,syst_tree.w_PDF085,syst_tree.w_PDF086,syst_tree.w_PDF087,syst_tree.w_PDF088,syst_tree.w_PDF089,syst_tree.w_PDF090,syst_tree.w_PDF091,syst_tree.w_PDF092,syst_tree.w_PDF093,syst_tree.w_PDF094,syst_tree.w_PDF095,syst_tree.w_PDF096,syst_tree.w_PDF097,syst_tree.w_PDF098,syst_tree.w_PDF099,syst_tree.w_PDF100,syst_tree.w_PDF101,syst_tree.w_PDF102]

                newtree.Fill(array("f",varsel))                        
                        
            newtree.Write("",ROOT.TObject.kOverwrite)

            ROOT.gDirectory.Delete("sel_{0}".format(s+";*"))            
            
        fIn.cd()    
        fIn.Write()
        fIn.Close()
        
def main():

        KinematicsAlgorithm()


if __name__ == "__main__":
    main()
