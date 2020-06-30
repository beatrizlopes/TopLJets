import sys
import os

def createFiles() :

    submit_file=open("kinalg.sub", "w")
    submit_file.write('executable              = submission/$(cfgFile).sh \n')
    submit_file.write('log                     = kinalg.log \n')
    submit_file.write('output                  = outfile.txt \n')
    submit_file.write('error                   = errors.txt \n')
    submit_file.write('should_transfer_files   = Yes \n')
    submit_file.write('when_to_transfer_output = ON_EXIT \n')
    submit_file.write('+JobFlavour = "longlunch" \n')

    #    filelist={"MC13TeV_2017_ZZ_0.root"}

    #for files in filelist :
    for files in os.listdir("/eos/user/b/bribeiro/f439f08_ul/Chunks/") :

        print 'creating submission file for ',files
        filename=files.replace('.root','')
        f = open("submission/{0}.sh".format(filename), "w")
        f.write('#!/bin/bash \n')
        f.write('WORKDIR=`pwd` \n')
        f.write('echo "Working directory is ${WORKDIR}" \n')
        f.write("FILENAME='{0}.root' \n".format(filename))
        f.write('cp /eos/user/b/bribeiro/f439f08_ul/Chunks/${FILENAME} ${WORKDIR} \n')
        f.write('cd /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11 \n')
        f.write('eval `scram r -sh` \n')
        f.write('cd ${WORKDIR} \n')
        f.write('python /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/scripts/KinAlg4tree.py ${WORKDIR}/${FILENAME} \n')
        f.write('root -l -b -q /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/macros/ApplyRegression_systs.C\'("\'${WORKDIR}/${FILENAME}\'")\' \n')
        f.write('root -l -b -q /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/macros/ApplyMVA_allsysts.C\'("\'${WORKDIR}/${FILENAME}\'")\' \n')
        f.write('root -l -b -q /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/macros/ApplyMVA_thsysts.C\'("\'${WORKDIR}/${FILENAME}\'")\' \n')
        f.write('mv -v ${WORKDIR}/${FILENAME} /eos/user/b/bribeiro/f439f08_ul/Chunks/ \n')
        f.close()
        submit_file.write('cfgFile={0} \n'.format(filename))
        submit_file.write('queue 1 \n')

    submit_file.close()

def main() :
    
    createFiles()


if __name__ == "__main__":
    main()
