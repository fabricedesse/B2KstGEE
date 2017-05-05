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
    myFile = TFile("../data/Raw/Raw.root", "RECREATE")

    Bd2KstGEE = MergeTuples( "../data/Raw/Bd2KstG_EE/*/*/*.root", "DecayTuple", "Bd2KstGEE" )
    Bd2KstEE = MergeTuples( "../data/Raw/Bd2KstEE/*/*/*.root", "DecayTuple", "Bd2KstEE" )
    Bd2KstJPsEE = MergeTuples( "../data/Raw/Bd2KstJPs_EE/*/*/*.root", "DecayTuple", "Bd2KstJPsEE")
    LPT = MergeTuples( "../data/Raw/LPT/*/*/*.root","DecayTuple", "LPT")
    myFile.Write()
