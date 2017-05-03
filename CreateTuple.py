import ROOT
from ROOT import TChain, TFile, TTree

import os
import glob
import


def MergeTuplesMC( path, oldTreeName, newTreeName ):
    myChain = TChain( oldTreeName )

    for fname in glob.glob(path):
        print(fname)
        myChain.Add(fname)

    myTree = myChain.CloneTree(-1, "fast")
    myTree.SetName( newTreeName )
    return myTree


def CreateRawTuple():
    myFile = TFile("../data/CreateTuple/MCGEE_Raw_gamma.root", "RECREATE")

    Bd2KstGEE = MergeTuplesMC( "../data/Raw/Bd2KstG_EE/*/*/*.root", "DecayTuple", "Bd2KstGEE" )
    Bd2KstEE = MergeTuplesMC( "../data/Raw/Bd2KstEE/*/*/*.root", "DecayTuple", "Bd2KstEE" )
    Bd2KstGEE.Write()
    Bd2KstEE.Write()
    myFile.Write()
