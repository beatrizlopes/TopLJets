#!/bin/bash

#combineCards.py zCR=/afs/cern.ch/user/p/psilva/public/forBeatriz/exclusive_top_zpeak.dat \
#    OF=/afs/cern.ch/user/p/psilva/public/forBeatriz/exclusive_top_OF.dat \
#    SF=/afs/cern.ch/user/p/psilva/public/forBeatriz/exclusive_top_SF.dat \
#    > exclusive_top.dat

#combineCards.py  mm=exclusive_top_mm.dat ee=exclusive_top_ee.dat em=exclusive_top_em.dat DY=exclusive_top_zpeak.dat > exclusive_top.dat

#text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel \
 #   --PO verbose \
  #  --PO 'map=.*/excTT:r[0.5,0,1]' \
   # --PO 'map=.*/DY:muDY[1,0,2]' \
    #--PO 'map=.*/qcdTT:muqcdTT[1,0,2]' \
    #exclusive_top_BDT.dat -o exclusive_top_BDT.root 

#combine exclusive_top_BDT.root -M MultiDimFit -t -1 \
 #  --algo grid --points 10000 \
  # -P muDY -P muqcdTT \
   #--setParameterRanges muDY=0,2:muqcdTT=0,2

combine exclusive_top_BDT.root -M MultiDimFit -m 0 -t -1\
    --algo grid --points 500 \
    -P r --setParameters r=0.5142 \
    --setParameterRanges muDY=0,2:muqcdTT=0,2:r=0,2

#combine -M AsymptoticLimits exclusive_top_BDT.root --run=blind --redefineSignalPOIs r
#combine -M AsymptoticLimits exclusive_top_BDT.dat --redefineSignalPOIs r
combine -M AsymptoticLimits exclusive_top_BDT.dat -t 100
