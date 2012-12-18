#!/usr/bin/env python

# plots cumulative distributions of number counts

from void_python_tools.backend import *
from void_python_tools.plotting import *
import void_python_tools.apTools as vp
import imp
import pickle
import os
import matplotlib.pyplot as plt
import numpy as np
import argparse

# ------------------------------------------------------------------------------

plotNameBase = "compdist"

obsFudgeFactor = 1.0 # what fraction of the volume are we *reall* capturing?
#obsFudgeFactor = .66 # what fraction of the volume are we *reall* capturing?

parser = argparse.ArgumentParser(description='Plot.')
parser.add_argument('--show', dest='showPlot', action='store_const',
                   const=True, default=False,
                   help='display the plot (default: just write eps)')
parser.add_argument('--parmFile', dest='parmFile', default='datasetsToPlot.py',
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

if not os.access(figDir, os.F_OK):
  os.makedirs(figDir)

dataSampleList = []

for sampleDir in sampleDirList:
  with open(workDir+sampleDir+"/sample_info.dat", 'rb') as input:
    dataSampleList.append(pickle.load(input))

plt.clf()
plt.xlabel("Void Radius [Mpc/h]")
plt.ylabel(r"N > R [$h^3$ Gpc$^{-3}$]")
plt.yscale('log')
plt.xlim(xmax=120.)

plotName = plotNameBase
allData = []

for (iSample,sample) in enumerate(dataSampleList):

  sampleName = sample.fullName
  lineTitle = sampleName

  if sample.dataType == "observation":
    boxVol = vp.getSurveyProps(sample.maskFile, 
                               sample.zBoundary[0], sample.zBoundary[1], 
                               sample.zRange[0], sample.zRange[1], "all",
                               selectionFuncFile=None)[0]
                               #selectionFuncFile=sample.selFunFile)[0]
    boxVol *= obsFudgeFactor
  else:
    boxVol = sample.boxLen*sample.boxLen*(sample.zBoundaryMpc[1] - 
                                          sample.zBoundaryMpc[0])

  boxVol *= 1.e-9 # Mpc->Gpc

  filename = workDir+"/"+sampleDirList[iSample]+"/centers_"+dataPortion+"_"+\
             sampleName+".out"
  if not os.access(filename, os.F_OK):
    print "File not found: ", filename
    continue

  data = np.loadtxt(filename, comments="#")
  if data.ndim == 1:
    print " Too few!"
    continue
  data = data[:,4]
  indices = np.arange(0, len(data), 1)
  sorted = np.sort(data)

  plt.plot(sorted, indices[::-1]/boxVol, '-',
           label=lineTitle, color=colorList[iSample],
           linewidth=linewidth)

  hist, bin_edges = np.histogram(data, bins=100, range=(0,100)) 
  allData.append(hist)

plt.legend(title = "Samples", loc = "upper right", prop={'size':8})
#plt.title(plotTitle)

plt.savefig(figDir+"/fig_"+plotName+".pdf", bbox_inches="tight")
plt.savefig(figDir+"/fig_"+plotName+".eps", bbox_inches="tight")
plt.savefig(figDir+"/fig_"+plotName+".png", bbox_inches="tight")

dataFile = figDir+"/data_"+plotName+".dat"
fp = open(dataFile, 'w')
fp.write("# R [Mpc/h], N [h^3 Gpc^-3]\n")
fp.write("# ")
for sample in dataSampleList:
  fp.write(sample.fullName+" ")
fp.write("\n")
for i in xrange(100):
  fp.write(str(bin_edges[i]) + " ")
  for iSample in xrange(len(dataSampleList)):
    fp.write(str(allData[iSample][i])+" ")
  fp.write("\n")
fp.close()

if args.showPlot:
  os.system("display %s" % figDir+"/fig_"+plotName+".png")

