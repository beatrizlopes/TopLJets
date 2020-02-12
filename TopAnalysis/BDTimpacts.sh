#!/bin/bash

text2workspace.py exclusive_top_BDT.dat -m 125

mv exclusive_top_BDT.dat.root exclusive_top_BDT.root

combineTool.py -M Impacts -d exclusive_top_BDT.root -m 125 --doInitialFit --robustFit 1 --X-rtd ADDNLL_RECURSIVE=0 --setCrossingTolerance 1E-06 --cminDefaultMinimizerStrategy 0 -t -1
#combineTool.py -M Impacts -d exclusive_top_BDT.root -m 125 --robustFit 1 --doFits
#combineTool.py -M Impacts -d exclusive_top_BDT.root -m 125 -o impacts.json
#plotImpacts.py -i impacts.json -o impacts
