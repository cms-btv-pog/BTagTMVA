#! /bin/bash

#This script assumes that you will be running from the test directory of a TMVA installation.
export VO_CMS_SW_DIR=/cms/base/cmssoft
export COIN_FULL_INDIRECT_RENDERING=1
export SCRAM_ARCH=slc5_amd64_gcc462
source $VO_CMS_SW_DIR/cmsset_default.sh

#NOTE: CHANGE TO A CMSSW RELEASE IN YOUR OWN AREA!
cd /cms/skaplan/BoostedHiggsNtupleProduction/CMSSW_5_3_18/src/
eval `scramv1 runtime -sh`

#assumes that the second argument is the location of the TMVA installation

cd $2/test
source setup.sh $2
root -l -q -b $1

#root -l -q -b "TMVAReader.C($1)"
