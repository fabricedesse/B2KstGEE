import ROOT
from ROOT import TChain, TFile, TTree

import os
import glob


def MergeTuples( path, oldTreeName, newTreeName ):
    myChain = TChain( oldTreeName )

    for fname in glob.glob(path):
        print(fname)
        myChain.Add(fname)

    myTree = myChain.CloneTree(-1, "fast")
    myTree.SetName( newTreeName )
    return myTree


def CreateRawTuple():
    pathToRaw = "/sps/lhcb/fdesse/tuples_B2KstGEE/raw_tuples/Raw.root"
    pathToSuperRaw = "/sps/lhcb/bifani/RD/Analysis/RKst/jobs/jobs/apply_EE_20/"
    myFile = TFile(pathToRaw, "RECREATE")

    Bd2KstGEE = MergeTuples( pathToSuperRaw+"Bd2KstG_EE/*/*/*.root", "DecayTuple", "Bd2KstGEE" )
    Bd2KstEE = MergeTuples( pathToSuperRaw"Bd2KstEE/*/*/*.root", "DecayTuple", "Bd2KstEE" )
    Bd2KstJPsEE = MergeTuples( pathToSuperRaw"Bd2KstJPs_EE/*/*/*.root", "DecayTuple", "Bd2KstJPsEE")
    LPT = MergeTuples( pathToSuperRaw"LPT/*/*/*.root","DecayTuple", "data")
    myFile.Write()
