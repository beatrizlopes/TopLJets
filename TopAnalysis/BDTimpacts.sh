#!/bin/bash

text2workspace.py exclusive_top_BDT_shape.dat -m 125 -o exclusive_top_BDT.root

combineTool.py -M Impacts -d exclusive_top_BDT.root -m 125 --doInitialFit  --robustFit 1 --rMin=-5 --rMax=20 --X-rtd ADDNLL_RECURSIVE=0 --setCrossingTolerance 1E-06 --cminDefaultMinimizerStrategy 0 --expectSignal 5 -t -1

combineTool.py -M Impacts -d exclusive_top_BDT.root -m 125 --robustFit 1 --doFits -o impacts.json --rMin=-5 --rMax=20 --X-rtd ADDNLL_RECURSIVE=0 --setCrossingTolerance 1E-06 --cminDefaultMinimizerStrategy 0 --expectSignal 5 -t -1

combineTool.py -M Impacts -d exclusive_top_BDT.root -m 125 -o impacts.json
plotImpacts.py -i impacts.json -o impacts

cp impacts.pdf /eos/user/b/bribeiro/www/
