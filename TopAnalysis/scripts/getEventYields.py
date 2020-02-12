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
                bin1,bin2=1,h.GetNbinsX()
                err=0
                print i
                if ran:
                    bin1=h.GetXaxis().FindBin(ran[0])
                    bin2=h.GetXaxis().FindBin(ran[1])
                n=h.Integral(bin1,bin2)
                for b in [bin1,bin2]:
                    err+=h.GetBinError(b)
                procYields[p]+=n
                if p!='data_obs' and p!='excTT' : totalExp+=n
                print err

            except:
                print "histogram", hName, " does not exist for process ", i
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
    return '%10s'%('%3.1f'%val)

plotter='plots/sel/ul/plotter.root'
fIn=ROOT.TFile.Open(plotter)
#acc_2lep_RP=0.0101
pps_lumi=37500
lumi=41526.280
htRange=(10,100)

procs={'data_obs':[''],
       'qcdTT':['Top'],
       'DY':['DY'],
       'others':['Multiboson','#gamma+jets','QCD'],
       'excTT':['pp#rightarrowppttbar x 1000']
       }

#yields in the DY control region
dyCR_mm = getYields(fIn,'mm_Zpeak_scalarhtj',procs,htRange)
dyCR_ee = getYields(fIn,'ee_Zpeak_scalarhtj',procs,htRange)

dyCR_mm_err = getErrors(fIn,'mm_Zpeak_scalarhtj',procs,htRange)
dyCR_ee_err = getErrors(fIn,'ee_Zpeak_scalarhtj',procs,htRange)

dyCR_tot= getYields(fIn,'',procs,htRange)
dyCR_err= getErrors(fIn,'',procs,htRange)

dyCR_ee_cut = getYields(fIn,'ee_Zpeak_RPcut_mRP',procs)
dyCR_mm_cut = getYields(fIn,'mm_Zpeak_RPcut_mRP',procs)

dyCR_ee_cut_err = getErrors(fIn,'ee_Zpeak_RPcut_mRP',procs)
dyCR_mm_cut_err = getErrors(fIn,'mm_Zpeak_RPcut_mRP',procs)

dyCR_ee_cutht = getYields(fIn,'ee_Zpeak_0ht_RPcut_mRP',procs)
dyCR_mm_cutht = getYields(fIn,'mm_Zpeak_0ht_RPcut_mRP',procs)

dyCR_ee_cutht_err = getErrors(fIn,'ee_Zpeak_0ht_RPcut_mRP',procs)
dyCR_mm_cutht_err = getErrors(fIn,'mm_Zpeak_0ht_RPcut_mRP',procs)

for p in procs:
    dyCR_tot[p]=dyCR_mm[p]+dyCR_ee[p]-dyCR_ee_cut[p]-dyCR_mm_cut[p]+dyCR_ee_cutht[p]+dyCR_mm_cutht[p]
    if p!='data_obs' : dyCR_tot['total']+=dyCR_tot[p]
    dyCR_err[p]=dyCR_mm_err[p]+dyCR_ee_err[p]+dyCR_ee_cut_err[p]+dyCR_mm_cut_err[p]+dyCR_ee_cutht_err[p]+dyCR_mm_cutht_err[p]
    if p!='data_obs' : dyCR_err['total']+=dyCR_err[p]

#dyCR_tot['total']=dyCR_mm['total']+dyCR_ee['total']-dyCR_ee_cut['total']-dyCR_mm_cut['total']+dyCR_ee_cutht['total']+dyCR_mm_cutht['total']

#yields in the ttbar control region
ttCR_ee = getYields(fIn,'ee_1b_notZ_lowMlb_scalarhtj',procs,htRange)
ttCR_em = getYields(fIn,'em_1b_lowMlb_scalarhtj',procs,htRange)
ttCR_mm = getYields(fIn,'mm_1b_notZ_lowMlb_scalarhtj',procs,htRange)

ttCR_ee_err = getErrors(fIn,'ee_1b_notZ_lowMlb_scalarhtj',procs,htRange)
ttCR_em_err = getErrors(fIn,'em_1b_lowMlb_scalarhtj',procs,htRange)
ttCR_mm_err = getErrors(fIn,'mm_1b_notZ_lowMlb_scalarhtj',procs,htRange)

ttCR_ee_cut = getYields(fIn,'ee_1b_notZ_lowMlb_RPcut_mRP',procs)
ttCR_em_cut = getYields(fIn,'em_1b_lowMlb_RPcut_mRP',procs)
ttCR_mm_cut = getYields(fIn,'mm_1b_notZ_lowMlb_RPcut_mRP',procs)

ttCR_ee_cut_err = getErrors(fIn,'ee_1b_notZ_lowMlb_RPcut_mRP',procs)
ttCR_em_cut_err = getErrors(fIn,'em_1b_lowMlb_RPcut_mRP',procs)
ttCR_mm_cut_err = getErrors(fIn,'mm_1b_notZ_lowMlb_RPcut_mRP',procs)

ttCR_ee_cut_ht = getYields(fIn,'ee_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)
ttCR_em_cut_ht = getYields(fIn,'em_1b_lowMlb_0ht_RPcut_mRP',procs)
ttCR_mm_cut_ht = getYields(fIn,'mm_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)

ttCR_ee_cut_ht_err = getErrors(fIn,'ee_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)
ttCR_em_cut_ht_err = getErrors(fIn,'em_1b_lowMlb_0ht_RPcut_mRP',procs)
ttCR_mm_cut_ht_err = getErrors(fIn,'mm_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)

for p in procs:
    #print p,' ',ttCR_ee[p]
    ttCR_ee[p]=ttCR_ee[p]-ttCR_ee_cut[p]+ttCR_ee_cut_ht[p]
    ttCR_em[p]=ttCR_em[p]-ttCR_em_cut[p]+ttCR_em_cut_ht[p]
    ttCR_mm[p]=ttCR_mm[p]-ttCR_mm_cut[p]+ttCR_mm_cut_ht[p]
    ttCR_ee_err[p]=ttCR_ee_err[p]+ttCR_ee_cut_err[p]+ttCR_ee_cut_ht_err[p]
    ttCR_em_err[p]=ttCR_em_err[p]+ttCR_em_cut_err[p]+ttCR_em_cut_ht_err[p]
    ttCR_mm_err[p]=ttCR_mm_err[p]+ttCR_mm_cut_err[p]+ttCR_mm_cut_ht_err[p]

#    if p!='data_obs' : ttCR_mm['total']+=ttCR_mm[p]
    #print p,' ',ttCR_ee[p]

#ttCR_SF['total']=ttCR_mm['total']+ttCR_ee['total']

ttCR_mm['total']=ttCR_mm['total']-ttCR_mm_cut['total']+ttCR_mm_cut_ht['total']
ttCR_ee['total']=ttCR_ee['total']-ttCR_ee_cut['total']+ttCR_ee_cut_ht['total']
ttCR_em['total']=ttCR_em['total']-ttCR_em_cut['total']+ttCR_em_cut_ht['total']

ttCR_mm_err['total']=ttCR_mm_err['total']-ttCR_mm_cut_err['total']+ttCR_mm_cut_ht_err['total']
ttCR_ee_err['total']=ttCR_ee_err['total']-ttCR_ee_cut_err['total']+ttCR_ee_cut_ht_err['total']
ttCR_em_err['total']=ttCR_em_err['total']-ttCR_em_cut_err['total']+ttCR_em_cut_ht_err['total']

#compute fake rate
#zpeak          = getYields(fIn,'ee_Zpeak_mll',procs)
#fake_mRP_zpeak = getYields(fIn,'ee_Zpeak_fake_mRP_mll',procs)
#fakeRate=0.07
#for p in zpeak:
#    fakeRate[p]=fake_mRP_zpeak[p]/zpeak[p]

#yields in the signal region are re-scaled by fake rate
#and by the lumi available with PPS and optical corrections
#substitute for the data with the RP based selection
#SR_ee['data_obs'] = getYields(fIn,'ee_lowMlb_RPcut_mRP',procs)['data_obs']
#SR_mm['data_obs'] = getYields(fIn,'mm_lowMlb_RPcut_mRP',procs)['data_obs']
#SR_em['data_obs'] = getYields(fIn,'em_lowMlb_RPcut_mRP',procs)['data_obs']

SR_ee = getYields(fIn,'ee_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)
SR_mm = getYields(fIn,'mm_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)
SR_em = getYields(fIn,'em_1b_lowMlb_0ht_RPcut_mRP',procs)

SR_ee_err = getErrors(fIn,'ee_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)
SR_mm_err = getErrors(fIn,'mm_1b_notZ_lowMlb_0ht_RPcut_mRP',procs)
SR_em_err = getErrors(fIn,'em_1b_lowMlb_0ht_RPcut_mRP',procs)

#SR_SF= getYields(fIn,'',procs)

#for p in procs:
 #   SR_SF[p]=SR_mm[p]+SR_ee[p]

#SR_SF['total']=SR_mm['total']+SR_ee['total']

#signal selection efficiency (based on ttbar)
#total2l=getYields(fIn,'ee_mll',procs)['qcdTT']
#total2l+=getYields(fIn,'mm_mll',procs)['qcdTT']
#total2l+=getYields(fIn,'em_mll',procs)['qcdTT']
#eff_lowmlb_ee=getYields(fIn,'ee_lowMlb_mll',procs)['qcdTT']/total2l
#eff_lowmlb_mm=getYields(fIn,'mm_lowMlb_mll',procs)['qcdTT']/total2l
#eff_lowmlb_em=getYields(fIn,'em_lowMlb_mll',procs)['qcdTT']/total2l


#printout
print 'Signal'
#print 'acceptance is',acc_2lep_RP
#print 'low mlb selection eff is',eff_lowmlb_ee,'(ee)',eff_lowmlb_mm,'(mm)',eff_lowmlb_em,'(em)'
#print 'lumi x Acc x eff =',pps_lumi*acc_2lep_RP*eff_lowmlb_ee,'(ee)',pps_lumi*acc_2lep_RP*eff_lowmlb_mm,'(mm)',pps_lumi*acc_2lep_RP*eff_lowmlb_em,'(em)'

print 'Background'
#print 'Roman pot fake rate used is:',fakeRate

print '          ','SR_ee      ','SR_mm       ','SR_em       ','ttCR_ee        ','ttCR_mm       ','ttCR_em       ','dyCR_tot       '
print'-'*130

for proc in ['qcdTT','DY','others','total','excTT','data_obs']:

    if proc=='total':print'-'*130
    print '%4s\t'%proc,
    print formatNumber(SR_ee[proc]),
  #  print '+-',SR_ee_err[proc],' ',
    print formatNumber(SR_mm[proc]),
 #   print '+-',SR_mm_err[proc],' ',
    print formatNumber(SR_em[proc]),
#    print '+-',SR_em_err[proc],' ',
    print formatNumber(ttCR_ee[proc]),
    print '+-',ttCR_ee_err[proc],' ',   
    print formatNumber(ttCR_mm[proc]),
    print '+-',ttCR_mm_err[proc],' ',   
    print formatNumber(ttCR_em[proc]),
    print '+-',ttCR_em_err[proc],' ',   
#    print formatNumber(ttCR_ee_cut[proc]),' ',
#    print formatNumber(ttCR_mm_cut[proc]),' ',
#    print formatNumber(ttCR_em_cut[proc]),' ',


#    print formatNumber(dyCR_ee[proc]),' ',
#    print formatNumber(dyCR_mm[proc]),' ',
    print formatNumber(dyCR_tot[proc]),' ',
    print '+-',dyCR_err[proc],
    print ''
    if proc=='total':print'-'*130
    

#dump shape histos for combine
def getHisto(hname,val):
    h=ROOT.TH1F(hname,hname,1,0,1)
    h.SetBinContent(1,val)
    return h
fOut=ROOT.TFile.Open('shapes.root','RECREATE')

for cat,yields in [
        ('zCR',     dyCR_tot),
                   ('ttCR_em', ttCR_em),
                   ('ttCR_ee', ttCR_ee),
                   ('ttCR_mm', ttCR_mm),
                   ('SR_em',   SR_em),
                   ('SR_ee',   SR_ee),
                   ('SR_mm',   SR_mm),
#                               ('SR_em',   SR_em,   pps_lumi*acc_2lep_RP*eff_lowmlb_em),
#                               ('SR_ee',   SR_ee,   pps_lumi*acc_2lep_RP*eff_lowmlb_ee),
 #                              ('SR_mm',   SR_mm,   pps_lumi*acc_2lep_RP*eff_lowmlb_mm),
               ]:

    for proc in ['excTT','qcdTT','DY','others','total','data_obs']:
        getHisto(proc+'_'+cat,yields[proc]).Write()
   # getHisto('excTT_'+cat,excTTyields).Write()


fOut.Close()

