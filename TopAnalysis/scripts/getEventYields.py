#!/usr/bin/env python

import ROOT

def getYields(fIn,hName,procs,ran=None):
    procYields={}
    totalExp=0
    for p in procs:
        procYields[p]=0.
        
        for i in procs[p]:
            h=fIn.Get('{0}/{0}{1}'.format(hName,'' if len(i)==0 else '_'+i))
            bin1,bin2=1,h.GetNbinsX()
            if ran:
                bin1=h.GetXaxis().FindBin(ran[0])
                bin2=h.GetXaxis().FindBin(ran[1])
            n=h.Integral(bin1,bin2)
            procYields[p]+=n
            if p!='data_obs': totalExp+=n
    procYields['total']=totalExp
    return procYields

def formatNumber(val):
    return '%15s'%('%3.1f'%val)

plotter='plots/sel/plotter.root'
fIn=ROOT.TFile.Open(plotter)
acc_2lep_RP=0.0101
pps_lumi=18671.647
lumi=41526.280
htRange=(0,10)

procs={'data_obs':[''],
       'qcdTT':['t#bar{t}','tW'],
       'DY':['DY'],
       'others':['Multiboson','W']
       }

#yields in the DY control region
dyCR_mm = getYields(fIn,'mm_Zpeak_mll',procs)
dyCR_ee = getYields(fIn,'ee_Zpeak_mll',procs)

#yields in the ttbar control region
ttCR_ee = getYields(fIn,'ee_1b_lowMlb_mll',procs)
ttCR_em = getYields(fIn,'em_1b_lowMlb_mll',procs)
ttCR_mm = getYields(fIn,'mm_1b_lowMlb_mll',procs)

#compute fake rate
#zpeak          = getYields(fIn,'ee_Zpeak_mll',procs)
#fake_mRP_zpeak = getYields(fIn,'ee_Zpeak_fake_mRP_mll',procs)
fakeRate=0.07
#for p in zpeak:
#    fakeRate[p]=fake_mRP_zpeak[p]/zpeak[p]

#yields in the signal region are re-scaled by fake rate
#and by the lumi available with PPS and optical corrections
SR_ee = getYields(fIn,'ee_lowMlb_ht',procs,ran=htRange)
SR_mm = getYields(fIn,'mm_lowMlb_ht',procs,ran=htRange)
SR_em = getYields(fIn,'em_lowMlb_ht',procs,ran=htRange)
for p in SR_ee : 
    SR_ee[p] *= fakeRate*pps_lumi/lumi
    SR_mm[p] *= fakeRate*pps_lumi/lumi
    SR_em[p] *= fakeRate*pps_lumi/lumi

#substitute for the data with the RP based selection
SR_ee['data_obs'] = getYields(fIn,'ee_lowMlb_mRP',procs,ran=htRange)['data_obs']
SR_mm['data_obs'] = getYields(fIn,'mm_lowMlb_mRP',procs,ran=htRange)['data_obs']
SR_em['data_obs'] = getYields(fIn,'em_lowMlb_mRP',procs,ran=htRange)['data_obs']


#signal selection efficiency (based on ttbar)
total2l=getYields(fIn,'ee_nvtx',procs,ran=htRange)['qcdTT']
total2l=getYields(fIn,'mm_nvtx',procs,ran=htRange)['qcdTT']
total2l+=getYields(fIn,'em_nvtx',procs,ran=htRange)['qcdTT']
eff_lowmlb_ee=getYields(fIn,'ee_lowMlb_nvtx',procs,ran=htRange)['qcdTT']/total2l
eff_lowmlb_mm=getYields(fIn,'mm_lowMlb_nvtx',procs,ran=htRange)['qcdTT']/total2l
eff_lowmlb_em=getYields(fIn,'em_lowMlb_nvtx',procs,ran=htRange)['qcdTT']/total2l


#printout
print 'Signal'
print 'acceptance is',acc_2lep_RP
print 'low mlb selection eff is',eff_lowmlb_ee,'(ee)',eff_lowmlb_mm,'(mm)',eff_lowmlb_em,'(em)'
print 'lumi x Acc x eff =',pps_lumi*acc_2lep_RP*eff_lowmlb_ee,'(ee)',pps_lumi*acc_2lep_RP*eff_lowmlb_mm,'(mm)',pps_lumi*acc_2lep_RP*eff_lowmlb_em,'(em)'

print 'Background'
print 'Roman pot fake rate used is:',fakeRate

print '%15s\t %15s\t %15s\t %15s\t %15s\t %15s\t'%('','SR_ee','SR_mm','SR_em','ttCR_ee','ttCR_mm','ttCR_em','dyCR')
print'-'*130


for proc in ['qcdTT','DY','others','total','data_obs']:

    if proc=='total':print'-'*130
    print '%15s\t'%proc,
    print formatNumber(SR_ee[proc]),'\t',
    print formatNumber(SR_mm[proc]),'\t',
    print formatNumber(SR_em[proc]),'\t',
    print formatNumber(ttCR_ee[proc]),'\t',
    print formatNumber(ttCR_mm[proc]),'\t',
    print formatNumber(ttCR_em[proc]),'\t',
    print formatNumber(dyCR[proc]),'\t',
    print ''
    if proc=='total':print'-'*130
    

#dump shape histos for combine
def getHisto(hname,val):
    h=ROOT.TH1F(hname,hname,1,0,1)
    h.SetBinContent(1,val)
    return h
fOut=ROOT.TFile.Open('shapes.root','RECREATE')

for cat,yields,excTTyields in [('zCR',     dyCR,    1e-4),
                               ('ttCR_em', ttCR_em, 1e-4),
                               ('ttCR_ee', ttCR_ee, 1e-4),
                               ('ttCR_mm', ttCR_mm, 1e-4),
                               ('SR_em',   SR_em,   pps_lumi*acc_2lep_RP*eff_lowmlb_em),
                               ('SR_ee',   SR_ee,   pps_lumi*acc_2lep_RP*eff_lowmlb_ee),
                               ('SR_mm',   SR_mm,   pps_lumi*acc_2lep_RP*eff_lowmlb_mm),
                               ]:

    for proc in ['qcdTT','DY','others','total','data_obs']:
        getHisto(proc+'_'+cat,yields[proc]).Write()
    getHisto('excTT_'+cat,excTTyields).Write()


fOut.Close()

