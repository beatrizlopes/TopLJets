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
                if p=='signal': procYields[p]+=n
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
drllRange=(2,5)
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

ev_mm_notZ = getYields(fIn,'mm_notZ_mll',procs)
ev_em_notZ = getYields(fIn,'em_mll',procs)
ev_ee_notZ = getYields(fIn,'ee_notZ_mll',procs)

ev_mm_1b = getYields(fIn,'mm_1b_notZ_mll',procs)
ev_em_1b = getYields(fIn,'em_1b_mll',procs)
ev_ee_1b = getYields(fIn,'ee_1b_notZ_mll',procs)

ev_mm_lowMlb = getYields(fIn,'mm_1b_notZ_lowMlb_mll',procs)
ev_em_lowMlb = getYields(fIn,'em_1b_lowMlb_mll',procs)
ev_ee_lowMlb = getYields(fIn,'ee_1b_notZ_lowMlb_mll',procs)

ev_mm_0ht = getYields(fIn,'mm_1b_notZ_lowMlb_0ht_mll',procs)
ev_em_0ht = getYields(fIn,'em_1b_lowMlb_0ht_mll',procs)
ev_ee_0ht = getYields(fIn,'ee_1b_notZ_lowMlb_0ht_mll',procs)

ev_mm_newrpcut = getYields(fIn,'mm_1b_notZ_lowMlb_0ht_newRPcut_newmRP',procs)
ev_em_newrpcut = getYields(fIn,'em_1b_lowMlb_0ht_newRPcut_newmRP',procs)
ev_ee_newrpcut = getYields(fIn,'ee_1b_notZ_lowMlb_0ht_newRPcut_newmRP',procs)

#ev_mm_drll = getYields(fIn,'mm_notZ_lowMlb_drll',procs,ran=drllRange)
#ev_em_drll = getYields(fIn,'em_lowMlb_drll',procs,ran=drllRange)
#ev_ee_drll = getYields(fIn,'ee_notZ_lowMlb_drll',procs,ran=drllRange)

#printout

filename = "yieldtable";
yieldFile=open(filename+".tex","w")

#Begin document

yieldFile.write("\\documentclass{article}\n")
yieldFile.write("\\usepackage[utf8]{inputenc}\n")
yieldFile.write("\\usepackage{geometry}\n")
yieldFile.write("\\usepackage{lscape}\n")
yieldFile.write("\\geometry{a4paper, total={170mm,257mm}, left=20mm, top=20mm,}\n")
yieldFile.write("\\title{CMS SUMMER 2016}\n")
yieldFile.write("\\author{Beatriz Lopes &  Bruno Valeixo Bento}\n")
yieldFile.write("\\date{July 2016}\n")
yieldFile.write("\\begin{document}\n")
yieldFile.write("\\begin{landscape}\n")
yieldFile.write("\\maketitle\n")

# Create table
yieldFile.write("\\begin{table}[!h]\n")
yieldFile.write("\\centering\n")
yieldFile.write("\\begin{tabular}{l||l|l|l||l|l|l||l|l|l|}\n")
yieldFile.write(" & ")

for i in ["Pre-selection","notZ","1b"]:
    yieldFile.write("\\multicolumn{3}{c||}{\\cellcolor[HTML]{EFEFEF} "+i+"}");
    if i!="1b":  yieldFile.write(" & ");

yieldFile.write("\\\\ \\cline{2-10} \n")
yieldFile.write("& $ee$ & $e\mu$ & $\mu\mu$ & $ee$ & $e\mu$ & $\mu\mu$ & $ee$ & $e\mu$ & $\mu\mu$ \\\\ \\hline \n")

for proc in ['qcdTT','DY','others','total','signal','data_obs']:
    yieldFile.write("\\cellcolor[HTML]{EFEFEF} " +proc+" & ")
    yieldFile.write(formatNumber(ev_ee[proc])+" & ")
    yieldFile.write(formatNumber(ev_em[proc])+" & ")
    yieldFile.write(formatNumber(ev_mm[proc]))
    yieldFile.write(" & ")
    yieldFile.write(formatNumber(ev_ee_notZ[proc])+" & ")
    yieldFile.write(formatNumber(ev_em_notZ[proc])+" & ")
    yieldFile.write(formatNumber(ev_mm_notZ[proc]))
    yieldFile.write(" & ")
    yieldFile.write(formatNumber(ev_ee_1b[proc])+" & ")
    yieldFile.write(formatNumber(ev_em_1b[proc])+" & ")
    yieldFile.write(formatNumber(ev_mm_1b[proc]))
    yieldFile.write("\\\\ \\hline \n")

# End table 1
yieldFile.write("\\end{tabular}\n")
yieldFile.write("\\end{table}\n")

yieldFile.write("\\begin{table}[!h]\n")
yieldFile.write("\\centering\n")
yieldFile.write("\\begin{tabular}{l||l|l|l||l|l|l||l|l|l|}\n")
yieldFile.write(" & ")

for i in ["low Mlb","$H_T=0$","mRP cut"]:
    yieldFile.write("\\multicolumn{3}{l||}{"+i+"}");
    if i!="mRP cut":  yieldFile.write(" & ");

yieldFile.write("\\\\ \\cline{2-10} \n")
yieldFile.write("& $ee$ & $e\mu$ & $\mu\mu$ & $ee$ & $e\mu$ & $\mu\mu$ & $ee$ & $e\mu$ & $\mu\mu$ \\\\ \\hline \n")

yieldFile.write(" & ")

for proc in ['qcdTT','DY','others','total','signal','data_obs']:
    yieldFile.write("\\cellcolor[HTML]{EFEFEF}"+proc+" & ")    
    yieldFile.write(formatNumber(ev_ee_lowMlb[proc])+" & ")
    yieldFile.write(formatNumber(ev_em_lowMlb[proc])+" & ")
    yieldFile.write(formatNumber(ev_mm_lowMlb[proc]))
    yieldFile.write(" & ")
    yieldFile.write(formatNumber(ev_ee_0ht[proc])+" & ")
    yieldFile.write(formatNumber(ev_em_0ht[proc])+" & ")
    yieldFile.write(formatNumber(ev_mm_0ht[proc]))
    yieldFile.write(" & ")
    yieldFile.write(formatNumber(ev_ee_newrpcut[proc])+" & ")
    yieldFile.write(formatNumber(ev_em_newrpcut[proc])+" & ")
    yieldFile.write(formatNumber(ev_mm_newrpcut[proc]))
    yieldFile.write("\\\\ \\hline \n")

yieldFile.write("\\end{tabular}\n")
yieldFile.write("\\end{table}\n")
yieldFile.write("\\end{landscape}\n")
yieldFile.write("\\end{document}\n")


f.close()
