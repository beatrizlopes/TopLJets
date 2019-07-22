#!/bin/bash

for file in /afs/cern.ch/work/b/bribeiro/ab05162/*.root
do
    python scripts/KinAlg4tree.py ${file}
  
done
echo "reconstruction done -----------------------------------------------"

for file in /afs/cern.ch/work/b/bribeiro/ab05162/*.root
do
    root -l -q macros/ApplyRegression.C'("'${file}'")'
  
done
echo "regrssion applied -----------------------------------------------"

for file in /afs/cern.ch/work/b/bribeiro/ab05162/*.root
do
    root -l -q macros/ApplyMVA.C'("'${file}'")'
done

echo "BDT output added -----------------------------------------------" 