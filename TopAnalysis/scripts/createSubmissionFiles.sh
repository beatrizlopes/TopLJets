

for file in /eos/user/b/bribeiro/f439f08_ul/Chunks/*.root
do
    f = open(submission/${file}, "w")
    f.write('#!/bin/bash')
    f.write('WORKDIR=`pwd` ')
    f.write('echo "Working directory is ${WORKDIR}"')
    f.write("FILENAME='",${file},"'")
    f.write('cp /eos/user/b/bribeiro/f439f08_ul/Chunks/${FILENAME} ${WORKDIR}')
    f.write('cd /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11')
    f.write('eval `scram r -sh`')
    f.write('cd ${WORKDIR}')
    f.write('python /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/scripts/KinAlg4tree.py ${WORKDIR}/${FILENAME}')
    f.write(mv -v ${WORKDIR}/${FILENAME} /eos/user/b/bribeiro/f439f08_ul/Chunks/)
    f.close()
	
done


