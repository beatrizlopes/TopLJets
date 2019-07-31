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
                print i

                if ran:
                    bin1=h.GetXaxis().FindBin(ran[0])
                    bin2=h.GetXaxis().FindBin(ran[1])
                n=h.Integral(bin1,bin2)
                if p!='signal': procYields[p]+=n
                if p!='data_obs': totalExp+=n
                if p=='signal': procYields[p]+=n/1000
            except:
                print "histogram", hName, " does not exist for process ", i            
                bin1,bin2=1,1

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
f=open("yields.txt","w")

procs={'data_obs':[''],
       'qcdTT':['Top'],
       'DY':['DY'],
       'others':['Multiboson','#gamma+jets','QCD'],
       'signal':['pp#rightarrowppttbar x 1000']
       }

ev_mm = getYields(fIn,'mm_mll',procs)
ev_em = getYields(fIn,'em_mll',procs)
ev_ee = getYields(fIn,'ee_mll',procs)

ev_mm_1b = getYields(fIn,'mm_1b_mll',procs)
ev_em_1b = getYields(fIn,'em_1b_mll',procs)
ev_ee_1b = getYields(fIn,'ee_1b_mll',procs)

ev_mm_notZ = getYields(fIn,'mm_1b_notZ_mll',procs)
ev_em_notZ = getYields(fIn,'em_1b_mll',procs)
ev_ee_notZ = getYields(fIn,'ee_1b_notZ_mll',procs)

ev_mm_lowMlb = getYields(fIn,'mm_1b_notZ_lowMlb_mll',procs)
ev_em_lowMlb = getYields(fIn,'em_1b_lowMlb_mll',procs)
ev_ee_lowMlb = getYields(fIn,'ee_1b_notZ_lowMlb_mll',procs)

ev_mm_notZ_RPcut = getYields(fIn,'mm_1b_notZ_lowMlb_RPcut_mRP',procs)
ev_em_notZ_RPcut = getYields(fIn,'em_1b_lowMlb_RPcut_mRP',procs)
ev_ee_notZ_RPcut = getYields(fIn,'ee_1b_notZ_lowMlb_RPcut_mRP',procs)

#printout
f.write( '%15s\t %15s\t %15s\t %15s\t'%('','mm','em','ee'))
f.write('\n')
f.write('-'*130)


for proc in ['qcdTT','DY','others','total','signal','data_obs']:

    if proc=='total': f.write('-'*130)
    f.write("\n")
    f.write( '%15s\t'%proc)
    f.write(formatNumber(ev_ee[proc]))
    f.write( formatNumber(ev_em[proc]))
    f.write( formatNumber(ev_mm[proc]))
    f.write( '\n')
    if proc=='total':
        f.write('-'*130)
        f.write('\n')

f.write('-'*130)
f.write('\n')
f.write('-'*130)

f.write('%15s\t %15s\t %15s\t %15s\t'%('','mm_1b','em_1b','ee_1b'))
f.write('\n')
f.write('-'*130)
f.write('\n')

for proc in ['qcdTT','DY','others','total','signal','data_obs']:

    if proc=='total': f.write('-'*130)
    f.write("\n")    
    f.write( '%15s\t'%proc)
    f.write( formatNumber(ev_ee_1b[proc]))
    f.write( formatNumber(ev_em_1b[proc]))
    f.write( formatNumber(ev_mm_1b[proc]))
    f.write( '\n')
    if proc=='total':
        f.write('-'*130)
        f.write('\n')

f.write('-'*130)
f.write('\n')
f.write('-'*130)

f.write('\n')
f.write( '%15s\t %15s\t %15s\t %15s\t'%('','mm_1b_notZ','em_1b_notZ','ee_1b_notZ'))
f.write('-'*130)
f.write('\n')

for proc in ['qcdTT','DY','others','total','signal','data_obs']:

    if proc=='total': f.write('-'*130)
    f.write("\n")
    f.write( '%15s\t'%proc)
    f.write(formatNumber(ev_ee_notZ[proc]))
    f.write(formatNumber(ev_em_notZ[proc]))
    f.write(formatNumber(ev_mm_notZ[proc]))
    f.write( '\n')
    if proc=='total':
        f.write('-'*130)
        f.write('\n')

f.write('-'*130)
f.write('\n')
f.write('-'*130)

f.write('\n')
f.write( '%15s\t %15s\t %15s\t %15s\t'%('','mm_1b_notZ_lowMlb','em_1b_notZ_lowMlb','ee_1b_notZ_lowMlb'))
f.write('-'*130)


for proc in ['qcdTT','DY','others','total','signal','data_obs']:

    if proc=='total': f.write('-'*130)
    f.write("\n")
    f.write('%15s\t'%proc)
    f.write(formatNumber(ev_ee_lowMlb[proc]))
    f.write(formatNumber(ev_em_lowMlb[proc]))
    f.write(formatNumber(ev_mm_lowMlb[proc]))
    f.write('\n')
    if proc=='total': 
        f.write('-'*130)
        f.write('\n')


f.write('-'*130)
f.write('\n')
f.write('-'*130)

f.write('\n')
f.write( '%15s\t %15s\t %15s\t %15s\t'%('','mm_1b_lowMlb_notZ_RPcut','em_1b_lowMlb_notZ_RPcut','ee_1b_lowMlb_notZ_RPcut'))
f.write('-'*130)


for proc in ['qcdTT','DY','others','total','signal','data_obs']:

    if proc=='total': f.write('-'*130)
    f.write("\n")
    f.write('%15s\t'%proc)
    f.write(formatNumber(ev_ee_notZ_RPcut[proc]))
    f.write(formatNumber(ev_em_notZ_RPcut[proc]))
    f.write(formatNumber(ev_mm_notZ_RPcut[proc]))
    f.write('\n')
    if proc=='total': 
        f.write('-'*130)
        f.write('\n')



f.close()
