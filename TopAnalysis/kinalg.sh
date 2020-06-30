#!/bin/bash

WORKDIR=`pwd`
echo "Working directory is ${WORKDIR}"
FILENAME='MC13TeV_2017_TTJets_0.root'
cp /eos/user/b/bribeiro/f439f08_ul/Chunks/${FILENAME} ${WORKDIR}
cd /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11
eval `scram r -sh`
cd ${WORKDIR}
python /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/scripts/KinAlg4tree.py ${WORKDIR}/${FILENAME}
root -l -q macros/ApplyRegression_systs.C'("'${FILENAME}'")'
root -l -q macros/ApplyMVA_allsysts.C'("'${FILENAME}'")'
mv -v ${WORKDIR}/${FILENAME} /eos/user/b/bribeiro/f439f08_ul/Chunks/
