#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TString.h"
#include "TChain.h"

void CreateTupleMCEE()
{
  TChain myChain("Bd2KstGEE");
  myChain.Add("../data/test1/M*.root");

  TFile *f = TFile::Open("../data/test.root", "RECREATE");
  myChain.CloneTree(-1, "fast");
  f->Write();
}
