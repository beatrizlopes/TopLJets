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
bdtlow=(-1,0.2)
bdthigh=(0.2,1)
bdt=0.3

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


systNames= {"pu",
#            "eetrig",
#            "emtrig",
#            "mmtrig",
            "esel",  
            "msel",  
            "l1prefire", 
            "ees1", "ees2",  "ees3", "ees4", "ees5", "ees6", 
            "ees7",
            "mes1", "mes2", "mes3", "mes4",
            #"btagjes",        "btagjesdn",                                                                                   
            "btaglf",
            "btaghf",
            #"btaghfstats1",   "btaghfstats1dn",                                                                              
            #"btaghfstats2",   "btaghfstats2dn",                                                                              
            #"btaglfstats1",   "btaglfstats1dn",                                                                              
            #"btaglfstats2",   "btaglfstats2dn",                                                                              
            #"btagcferr1",     "btagcferr1dn",                                                                                
            #"btagcferr2",     "btagcferr2dn",                                                                                
            "JER",
#            "JERstat",
 #           "JERJEC",
  #          "JERPU", 
   #         "JERPLI",
    #        "JERptCut",
     #       "JERtrunc",
      #      "JERpTdep",
       #     "JERSTmFE",
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

    CRup_s = getYields(fIn,'2b_BDT_output_{0}up'.format(i),procs,bdtlow)
    SRup_s = getYields(fIn,'2b_BDT_output_{0}up'.format(i),procs,bdthigh)
    CRdn_s = getYields(fIn,'2b_BDT_output_{0}dn'.format(i),procs,bdtlow)
    SRdn_s = getYields(fIn,'2b_BDT_output_{0}dn'.format(i),procs,bdthigh)

    p='qcdTT'
    varup_CR_top=CRup_s[p]/CR[p]
    varup_SR_top=SRup_s[p]/SR[p]
    vardn_CR_top=CRdn_s[p]/CR[p]
    vardn_SR_top=SRdn_s[p]/SR[p]

    p='excTT'
    varup_CR_sig=CRup_s[p]/CR[p]
    varup_SR_sig=SRup_s[p]/SR[p]
    vardn_CR_sig=CRdn_s[p]/CR[p]
    vardn_SR_sig=SRdn_s[p]/SR[p]

    if varup_CR_top!=vardn_CR_top:
        if ("ees" not in i and "mes" not in i and "JEC" not in i and "toppt" not in i and "bfrag" not in i):
            print  i ,"    lnN  ", formatNumber(varup_CR_sig),"/",formatNumber(vardn_CR_sig)," ", formatNumber(varup_CR_top),"/",formatNumber(vardn_CR_top)," -  - ",formatNumber(varup_SR_sig),"/",formatNumber(vardn_SR_sig)," ", formatNumber(varup_SR_top),"/",formatNumber(vardn_SR_top)," - - "
        else : 
            print  i ,"    lnN  - ", formatNumber(varup_CR_top),"/",formatNumber(vardn_CR_top)," -  -  -  ", formatNumber(varup_SR_top),"/",formatNumber(vardn_SR_top)," - - "

#    if ("ees" not in i and "mes" not in i and "JEC" not in i and "toppt" not in i and "bfrag" not in i):
 #       print  i ,"    lnN  ", formatNumber(varup_CR_sig),"/",formatNumber(vardn_CR_sig)," - - - ",formatNumber(varup_SR_sig),"/",formatNumber(vardn_SR_sig)," -  - - "





#    if varup_CR_top!=vardn_CR_top:
#        if ("ees" not in i and "mes" not in i and "JEC" not in i and "toppt" not in i and "bfrag" not in i):
#            print  i ,"    lnN  ", formatNumber(varup_CR_sig),"/",formatNumber(vardn_CR_sig)," ", formatNumber(varup_CR_top),"/",formatNumber(vardn_CR_top)," -  - -  -   - - "
#        else : 
#            print  i ,"    lnN  - ", formatNumber(varup_CR_top),"/",formatNumber(vardn_CR_top)," -  -  -  - - - "




#    if varup_CR_top!=vardn_CR_top:
 #       print  i ,"    lnN  - ", formatNumber(varup_CR_top),"/",formatNumber(vardn_CR_top)," -  -  - -  - - "

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
def getHisto(hname,val):
    h=ROOT.TH1F(hname,hname,1,0,1)
    h.SetBinContent(1,val)
    return h
    
fOut=ROOT.TFile.Open('shapes.root','RECREATE')

fOut.cd()

for proc in ['excTT','qcdTT','DY','others','total','data_obs']:
    getHisto(proc+'_SR',SR[proc]).Write()
    getHisto(proc+'_CR',CR[proc]).Write()

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
