#!/bin/sh
cd /afs/cern.ch/work/p/prrout/public/IndiaCMS/CMSSW_9_4_2/src/Analysis/DrellYan/test/
eval `scramv1 runtime -sh`
cmsRun ConfFile_cfg_2.py
