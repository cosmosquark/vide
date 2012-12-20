#!/usr/bin/env python

# plots cumulative distributions of number counts

from void_python_tools.backend import *
from void_python_tools.plotting import *
import imp
import pickle
import os
import matplotlib.pyplot as plt
import numpy as np
import argparse

# ------------------------------------------------------------------------------

dataNameBase = "mergerTree"

parser = argparse.ArgumentParser(description='Analyze.')
parser.add_argument('--parmFile', dest='parmFile', default='datasetsToAnalyze.py',
                    help='path to parameter file')
args = parser.parse_args()

# ------------------------------------------------------------------------------

filename = args.parmFile
print " Loading parameters from", filename
if not os.access(filename, os.F_OK):
  print "  Cannot find parameter file %s!" % filename
  exit(-1)
parms = imp.load_source("name", filename)
globals().update(vars(parms))

if not os.access(dataDir, os.F_OK):
  os.makedirs(dataDir)

outFileName = dataDir + "/" + dataNameBase #+ ".dat"

with open(workDir+baseSampleDir+"/sample_info.dat", 'rb') as input:
  baseSample = pickle.load(input)

for (iSample, sampleDir) in enumerate(sampleDirList):

  with open(workDir+sampleDir+"/sample_info.dat", 'rb') as input:
    sample = pickle.load(input)

  print " Working with", sample.fullName, "...",

  sampleName = sample.fullName

  binPath = CTOOLS_PATH+"/analysis/voidOverlap"
  logFile = os.getcwd()+"/mergerTree.log"
  stepOutputFileName = outFileName + "_" + baseSample.fullName + "_" + \
                       sampleName + "_"
  #stepOutputFileName = os.getcwd()+"/data/overlap_"

  launchVoidOverlap(baseSample, sample, workDir+baseSampleDir, 
                    workDir+sampleDir, binPath, 
                    thisDataPortion="central", logFile=logFile,
                    continueRun=False, workDir=workDir,
                    outputFile=stepOutputFileName)

  # attach columns to summary file
  #if iSample == 1:
  #  os.system("cp %s %s" % (stepOutputFileName, outFileName))
  #else:
  #  outFile = open("temp.out", "w")
  #  stepOutFile1 = open(outFileName, "r")
  #  stepOutFile2 = open(stepOutputFileName, "r")
  #
  #  for line1 in stepOutFile1:
  #    line1 = line1.rstrip()
  #    line2 = stepOutFile2.readline()
  #    outFile.write(line1+" "+line2)
  #
  #  os.system("cp %s %s" % ("temp.out", outFileName))
  #  outFile.close()
  #  stepOutFile1.close()
  #  stepOutFile2.close()

#if os.access("mergerTree.log", os.F_OK): os.unlink("mergerTree.log")
#if os.access("temp.out", os.F_OK): os.unlink("temp.out")
#if os.access("thisStep.out", os.F_OK): os.unlink("thisStep.out")
