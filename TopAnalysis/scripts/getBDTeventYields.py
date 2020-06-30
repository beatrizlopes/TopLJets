#!/usr/bin/env python

import ROOT

def getYields(fIn,hName,procs,ran=None):
    procYields={}
    totalExp=0
    for p in procs:
        procYields[p]=0.

        for i in procs[p]:
            h=fIn.Get('{0}/{0}{1}'.format(hName,'' if len(i)==0 else '_'+i))
            try:
                if 'bfrag' in hName :
#                    print 'bfrag'
                    hnom=fIn.Get('2b_BDT_output/2b_BDT_output{0}'.format('' if len(i)==0 else '_'+i))
                    h.Scale(hnom.Integral()/h.Integral())

                bin1,bin2=1,h.GetNbinsX()
#                print i
                if ran:
                    bin1=h.GetXaxis().FindBin(ran[0])
                    bin2=h.GetXaxis().FindBin(ran[1])
                n=h.Integral(bin1,bin2)
                procYields[p]+=n
                if p!='data_obs' and p!='excTT' : totalExp+=n
            except:
 #               print "histogram", hName, " does not exist for process ", i
                bin1,bin2=1,1

    procYields['total']=totalExp
    return procYields

def getErrors(fIn,hName,procs,ran=None):
    procErr={}
    errtotal=0
    for p in procs:
        procErr[p]=0.

        for i in procs[p]:
            h=fIn.Get('{0}/{0}{1}'.format(hName,'' if len(i)==0 else '_'+i))
            try:
                if p=='data_obs': continue
                bin1,bin2=1,h.GetNbinsX()
                err=0
                print i
                if ran:
                    bin1=h.GetXaxis().FindBin(ran[0])
                    bin2=h.GetXaxis().FindBin(ran[1])
                for b in [bin1,bin2]:
                    err+=h.GetBinError(b)
                procErr[p]+=err
                print err
                errtotal+=err
            except:
                print "histogram", hName, " does not exist for process ", i
                bin1,bin2=1,1

    procErr['total']=errtotal

    return procErr

def formatNumber(val):
    return '%3.4f'%val

plotter='plots/sel/ul/plotter.root'
fIn=ROOT.TFile.Open(plotter)
#acc_2lep_RP=0.0101
pps_lumi=37500
lumi=41526.280
bdt=0.4
bdtlow=(-1,bdt)
bdthigh=(bdt,1)


procs={'data_obs':[''],
       'qcdTT':['Top'],
       'DY':['DY'],
       'others':['Multiboson','#gamma+jets','QCD'],
       'excTT':['pp#rightarrowppttbar x 1000']
       }


CR = getYields(fIn,'2b_BDT_output',procs,bdtlow)
SR = getYields(fIn,'2b_BDT_output',procs,bdthigh)

CR_err = getErrors(fIn,'2b_BDT_output',procs,bdtlow)
SR_err = getErrors(fIn,'2b_BDT_output',procs,bdthigh)


systNames= {"muR","muF","muRmuF",
            #"PDF000","PDF001","PDF002","PDF003","PDF004","PDF005","PDF006",
            #"PDF007","PDF008","PDF009","PDF010","PDF011","PDF012","PDF013","PDF014","PDF015","PDF016","PDF017","PDF018","PDF019","PDF020",
            #"PDF021","PD022","PDF023","PDF024","PDF025","PDF026","PDF027","PDF028","PDF029","PDF030","PDF031","PDF032","PDF033","PDF034","PDF035","PDF036",
            #"PDF037","PDF038","PDF039","PDF040","PDF041","PDF042","PDF043","PDF044","PDF045","PDF046","PDF047","PDF048","PDF049","PDF050","PDF051","PDF052","PDF053","PDF054","PDF055","PDF056","PDF057","PDF058","PDF059","PDF060","PDF061","PDF062","PDF063","PDF064","PDF065","PDF066","PDF067","PDF068","PDF069","PDF070","PDF071","PDF072","PDF073","PDF074","PDF075","PDF076","PDF077","PDF078","PDF079","PDF080","PDF081","PDF082","PDF083","PDF084","PDF085",
            #"PDF086","PDF087","PDF088","PDF089","PDF090","PDF091","PDF092","PDF093","PDF094","PDF095","PDF096","PDF097","PDF098","PDF099","PDF100","PDF101",
            #"PDF102",
            "pu",
            #            "eetrig",
            #            "emtrig",
            #            "mmtrig",
            "esel",  
            "msel",  
            "l1prefire", 
            #"ees1", "ees2",  
            "ees3", "ees4", 
            #"ees5", 
            "ees6", 
            "mes1", "mes2", "mes3", "mes4",
            #"btagjes",        "btagjesdn",                                                                                   
            "btaglf",
            "btaghf",
            "JER",
            "toppt",   
            "AbsoluteStatJEC","AbsoluteScaleJEC","AbsoluteMPFBiasJEC",
            "FragmentationJEC","SinglePionECALJEC","SinglePionHCALJEC",
            "FlavorPureGluonJEC","FlavorPureQuarkJEC",
            "FlavorPureCharmJEC","FlavorPureBottomJEC","TimePtEtaJEC",
            "RelativeJEREC1JEC","RelativeJEREC2JEC","RelativeJERHFJEC",
            "RelativePtBBJEC","RelativePtEC1JEC","RelativePtEC2JEC",
            "RelativePtHFJEC","RelativeBalJEC","RelativeFSRJEC",
            "RelativeStatFSRJEC","RelativeStatECJEC","RelativeStatHFJEC",
            "PileUpDataMCJEC","PileUpPtRefJEC","PileUpPtBBJEC",
            "PileUpPtEC1JEC","PileUpPtEC2JEC","PileUpPtHFJEC",
            "bfrag"}

for i in systNames :

    print i,"   shape  1 1 1"


#printout
print 'cutting on bdt value:',bdt
print 'Signal'
#print 'acceptance is',acc_2lep_RP
#print 'low mlb selection eff is',eff_lowmlb_ee,'(ee)',eff_lowmlb_mm,'(mm)',eff_lowmlb_em,'(em)'
#print 'lumi x Acc x eff =',pps_lumi*acc_2lep_RP*eff_lowmlb_ee,'(ee)',pps_lumi*acc_2lep_RP*eff_lowmlb_mm,'(mm)',pps_lumi*acc_2lep_RP*eff_lowmlb_em,'(em)'

print 'Background'
        #print 'Roman pot fake rate used is:',fakeRate

print '          ','CR      ','SR      '
print'-'*130

for proc in ['qcdTT','DY','others','total','excTT','data_obs']:

        print'-'*130
        print '%4s\t'%proc,
        print formatNumber(CR[proc]),'+-',CR_err[proc],' ',
        print formatNumber(SR[proc]),'+-',SR_err[proc],' ',
        print ''
        if proc=='total':print'-'*130
        

#dump shape histos for combine
def getHisto(proc,p,syst,var=''):
    if "PDF" not in syst :
        h=fIn.Get("2b_BDT_output{0}/2b_BDT_output{0}{1}".format('' if syst=='nom' else '_'+syst+('up' if var=='Up' else 'dn'), '' if proc=='' else '_'+proc))
    else :
        h=fIn.Get("2b_BDT_output{0}/2b_BDT_output{0}{1}".format('_'+syst, '' if proc=='' else '_'+proc))
        
    hnom=fIn.Get("2b_BDT_output/2b_BDT_output{0}".format('' if proc=='' else '_'+proc))
    if not h :
        h=ROOT.TH1F("dummy","dummy",1,0,1)
        return h
    #    h.SetBinContent(1,val)
    print 'got histogram ',h.GetName()
    h.SetName('{0}{1}'.format(p,'' if syst=='nom' else '_'+syst+var))
    if ('mu' in syst or 'PDF' in syst or 'bfrag' in syst) and hnom.Integral()!=0 :  h.Scale(h.Integral()/hnom.Integral())
    h.Rebin(6)
    return h
    
fOut=ROOT.TFile.Open('shapes.root','RECREATE')

fOut.cd()

for p in procs:
    if len(procs[p])==0 : getHisto('',p,'nom').Write()
    for i in procs[p] :
        getHisto(i,p,'nom').Write()
        if p!='data_obs' :
            for syst in systNames:
                if not (syst=='toppt' and p=='excTT'):
                    if not "PDF" in syst :
                        getHisto(i,p,syst,'Up').Write()
                        getHisto(i,p,syst,'Down').Write()
                    else :
                        getHisto(i,p,syst,'').Write()
                    #        getHisto('excTT_'+cat,excTTyields).Write()

fOut.Close()

#CR_jerup = getYields(fIn,'2b_BDT_output_jerUp',procs,bdtlow)
        #SR_jerup = getYields(fIn,'2b_BDT_output_jerUp',procs,bdthigh)

#CR_err_up = getErrors(fIn,'2b_BDT_output_Up',procs,bdtlow)
        #SR_err_up = getErrors(fIn,'2b_BDT_output_Up',procs,bdthigh)

#CR_dn = getYields(fIn,'2b_BDT_output_muDn',procs,bdtlow)
        #SR_dn = getYields(fIn,'2b_BDT_output_muDn',procs,bdthigh)

#CR_jerdn = getYields(fIn,'2b_BDT_output_jerDn',procs,bdtlow)
        #SR_jerdn = getYields(fIn,'2b_BDT_output_jerDn',procs,bdthigh)

#CR_err_dn = getErrors(fIn,'2b_BDT_output_muDn',procs,bdtlow)
        #SR_err_dn = getErrors(fIn,'2b_BDT_output_muDn',procs,bdthigh)


#CR_btaglfdn = getYields(fIn,'2b_BDT_output_btaglfDn',procs,bdtlow)
        #SR_btaglfdn = getYields(fIn,'2b_BDT_output_btaglfDn',procs,bdthigh)
        #CR_btaglfup = getYields(fIn,'2b_BDT_output_btaglfUp',procs,bdtlow)
        #SR_btaglfup = getYields(fIn,'2b_BDT_output_btaglfUp',procs,bdthigh)

#CR_btaghfdn = getYields(fIn,'2b_BDT_output_btaghfDn',procs,bdtlow)
        #SR_btaghfdn = getYields(fIn,'2b_BDT_output_btaghfDn',procs,bdthigh)
        #CR_btaghfup = getYields(fIn,'2b_BDT_output_btaghfUp',procs,bdtlow)
        #SR_btaghfup = getYields(fIn,'2b_BDT_output_btaghfUp',procs,bdthigh)

#CR_ees1dn = getYields(fIn,'2b_BDT_output_ees1Dn',procs,bdtlow)
        #SR_ees1dn = getYields(fIn,'2b_BDT_output_ees1Dn',procs,bdthigh)
        #CR_ees1up = getYields(fIn,'2b_BDT_output_ees1Up',procs,bdtlow)
        #SR_ees1up = getYields(fIn,'2b_BDT_output_ees1Up',procs,bdthigh)

#CR_mes1dn = getYields(fIn,'2b_BDT_output_mes1Dn',procs,bdtlow)
        #SR_mes1dn = getYields(fIn,'2b_BDT_output_mes1Dn',procs,bdthigh)
        #CR_mes1up = getYields(fIn,'2b_BDT_output_mes1Up',procs,bdtlow)
        #SR_mes1up = getYields(fIn,'2b_BDT_output_mes1Up',procs,bdthigh)

#CR_topptdn = getYields(fIn,'2b_BDT_output_topptDn',procs,bdtlow)
        #SR_topptdn = getYields(fIn,'2b_BDT_output_topptDn',procs,bdthigh)
        #CR_topptup = getYields(fIn,'2b_BDT_output_topptUp',procs,bdtlow)
        #SR_topptup = getYields(fIn,'2b_BDT_output_topptUp',procs,bdthigh)

#CR_mseldn = getYields(fIn,'2b_BDT_output_mselDn',procs,bdtlow)
        #SR_mseldn = getYields(fIn,'2b_BDT_output_mselDn',procs,bdthigh)
        #CR_mselup = getYields(fIn,'2b_BDT_output_mselUp',procs,bdtlow)
        #SR_mselup = getYields(fIn,'2b_BDT_output_mselUp',procs,bdthigh)

#CR_eseldn = getYields(fIn,'2b_BDT_output_eselDn',procs,bdtlow)
        #SR_eseldn = getYields(fIn,'2b_BDT_output_eselDn',procs,bdthigh)
        #CR_eselup = getYields(fIn,'2b_BDT_output_eselUp',procs,bdtlow)
        #SR_eselup = getYields(fIn,'2b_BDT_output_eselUp',procs,bdthigh)
