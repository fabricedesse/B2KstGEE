//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Creates a tree with kinematic information on the dielectron pair in B2KstGEE
// adding expected first z measurement in the VELO and phi angle.
//
// Output: None
//
// Inputs:
// TString input_file
// TString input_tree
// TString output_file
//
//==============================================================================

#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

void create_tree (TString input_file, TString input_tree, TString output_file)
{

  //============================================================================
  // Open and clone tree, set branch addresses
  //============================================================================

  TFile *f = new TFile(input_file,"read");
  TTree *T = (TTree*)f->Get(input_tree);

  TFile newFile(output_file,"RECREATE");
  TTree *newTree = T->CloneTree(0);

  cout << "Cloned tree " << input_tree << "with number of entries = "
  << T->GetEntries() << endl ;

  // Kst vertex
  Double_t Kst_TRUEORIGINVERTEX_X;
  Double_t Kst_TRUEORIGINVERTEX_Y;
  Double_t Kst_TRUEORIGINVERTEX_Z;

  Double_t B0_ENDVERTEX_X;
  Double_t B0_ENDVERTEX_Y;
  Double_t B0_ENDVERTEX_Z;

  // E momentum
  Double_t E1_TRUEP_X;
  Double_t E1_TRUEP_Y;
  Double_t E1_TRUEP_Z;

  Double_t E1_PX;
  Double_t E1_PY;
  Double_t E1_PZ;

  Double_t E2_TRUEP_X;
  Double_t E2_TRUEP_Y;
  Double_t E2_TRUEP_Z;

  Double_t E2_PX;
  Double_t E2_PY;
  Double_t E2_PZ;

  // New variables
  Double_t E1_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E2_TRUE_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E1_TRUE_PHI = -1000;
  Double_t E1_PHI = -1000;
  Double_t E1_TRUE_PHI = -1000;
  Double_t E1_PHI = -1000;



  newTree->SetBranchAddress("Kst_TRUEORIGINVERTEX_X", &Kst_TRUEORIGINVERTEX_X);
  newTree->SetBranchAddress("Kst_TRUEORIGINVERTEX_Y", &Kst_TRUEORIGINVERTEX_Y);
  newTree->SetBranchAddress("Kst_TRUEORIGINVERTEX_Z", &Kst_TRUEORIGINVERTEX_Z);

  newTree->SetBranchAddress("B0_ENDVERTEX_X" ,&B0_ENDVERTEX_X);
  newTree->SetBranchAddress("B0_ENDVERTEX_Y" ,&B0_ENDVERTEX_Y);
  newTree->SetBranchAddress("B0_ENDVERTEX_Z" ,&B0_ENDVERTEX_Z);

  newTree->SetBranchAddress("E1_TRUEP_X", &E1_TRUEP_X);
  newTree->SetBranchAddress("E1_TRUEP_Y", &E1_TRUEP_Y);
  newTree->SetBranchAddress("E1_TRUEP_Z", &E1_TRUEP_Z);

  newTree->SetBranchAddress("E1_PX", &E1_PX);
  newTree->SetBranchAddress("E1_PY", &E1_PY);
  newTree->SetBranchAddress("E1_PZ", &E1_PZ);

  newTree->SetBranchAddress("E2_TRUEP_X", &E2_TRUEP_X);
  newTree->SetBranchAddress("E2_TRUEP_Y", &E2_TRUEP_Y);
  newTree->SetBranchAddress("E2_TRUEP_Z", &E2_TRUEP_Z);

  newTree->SetBranchAddress("E2_PX", &E2_PX);
  newTree->SetBranchAddress("E2_PY", &E2_PY);
  newTree->SetBranchAddress("E2_PZ", &E2_PZ);

  TBranch *newbranch1 = newTree->Branch("Expl2FirstMeasurementZ", &Expl2FirstMeasurementZ, "Expl2FirstMeasurementZ");
  TBranch *newbranch2 = newTree->Branch("Expl1FirstMeasurementZ", &Expl1FirstMeasurementZ, "Expl1FirstMeasurementZ");




  //============================================================================
  // Fill and write tree
  //============================================================================
  int nentries = (int)T->GetEntries();

    for(int i=0; i<nentries; i++)
    {
      T->GetEntry(i);
      newTree->Fill();
    }

  newTree->Write();
  newFile.Write();
  cout << "Tree " << input_tree << " with number of entries = "
  << newTree->GetEntries() << " written in file " << output_file << endl ;

}
