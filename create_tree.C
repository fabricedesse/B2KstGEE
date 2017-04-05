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
#include "TBranch.h"

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
  Double_t E2_TRUE_PHI = -1000;
  Double_t E2_PHI = -1000;

  // Set branch addresses
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

  TBranch *b_E1_EXP_TRACK_FirstMeasurementZ =
    newTree->Branch("E1_EXP_TRACK_FirstMeasurementZ",
    &E1_EXP_TRACK_FirstMeasurementZ);
  TBranch *b_E1_TRUE_EXP_TRACK_FirstMeasurementZ =
    newTree->Branch("E1_TRUE_EXP_TRACK_FirstMeasurementZ",
    &E1_TRUE_EXP_TRACK_FirstMeasurementZ);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementZ =
    newTree->Branch("E2_EXP_TRACK_FirstMeasurementZ",
    &E2_EXP_TRACK_FirstMeasurementZ);
  TBranch *b_E2_TRUE_EXP_TRACK_FirstMeasurementZ =
    newTree->Branch("E2_TRUE_EXP_TRACK_FirstMeasurementZ",
    &E2_TRUE_EXP_TRACK_FirstMeasurementZ);
  TBranch *b_E1_TRUE_PHI = newTree->Branch("E1_TRUE_PHI", &E1_TRUE_PHI);
  TBranch *b_E1_PHI = newTree->Branch("E1_PHI", &E1_PHI);
  TBranch *b_E2_TRUE_PHI = newTree->Branch("E2_TRUE_PHI", &E2_TRUE_PHI);
  TBranch *b_E2_PHI = newTree->Branch("E2_PHI", &E2_PHI);

  //============================================================================
  // Calculation of expected z first measurement
  //============================================================================

  // z-positions of velo stations (in mm). (0,0,à) is the position of the pp
  // interaction
  Int_t z_VELO_left[42];
  // central stations by pairs (each pair is one layer of width 1.5-2 mm
  // CHECK WHY SOMETIMES 1.5 and 2
  z_VELO_left[0]=-176;
  z_VELO_left[1]=-174.5;

  z_VELO_left[2]=-146;
  z_VELO_left[3]=-144;

  z_VELO_left[4]=-116;
  z_VELO_left[5]=-114;

  z_VELO_left[6]=-86;
  z_VELO_left[7]=-84;

  z_VELO_left[8]=-56;
  z_VELO_left[9]=-54;

  z_VELO_left[10]=-26;
  z_VELO_left[11]=-24;

  z_VELO_left[12]=4;
  z_VELO_left[13]=6;

  z_VELO_left[14]=34;
  z_VELO_left[15]=36;

  z_VELO_left[16]=64;
  z_VELO_left[17]=66;

  z_VELO_left[18]=94;
  z_VELO_left[19]=95.5;

  z_VELO_left[20]=124;
  z_VELO_left[21]=125.5;

  z_VELO_left[22]=154;
  z_VELO_left[23]=155.5;

  z_VELO_left[24]=184;
  z_VELO_left[25]=186;

  z_VELO_left[26]=214;
  z_VELO_left[27]=216;

  z_VELO_left[28]=244;
  z_VELO_left[29]=246;

  z_VELO_left[30]=274;
  z_VELO_left[31]=275.5;

  // low angle stations
  z_VELO_left[32]=434;
  z_VELO_left[33]=436;

  z_VELO_left[34]=584;
  z_VELO_left[35]=586;

  z_VELO_left[36]=634;
  z_VELO_left[37]=636;

  z_VELO_left[38]=684;
  z_VELO_left[39]=686;

  z_VELO_left[40]=734;
  z_VELO_left[41]=736;

  Int_t z_VELO_right2[42];

  z_VELO_right2[0]=-161;
  z_VELO_right2[1]=-159;

  z_VELO_right2[2]=-131;
  z_VELO_right2[3]=-129;

  z_VELO_right2[4]=-101;
  z_VELO_right2[5]=-99;

  z_VELO_right2[6]=-70.5;
  z_VELO_right2[7]=-69;

  z_VELO_right2[8]=-41;
  z_VELO_right2[9]=-39;

  z_VELO_right2[10]=-11;
  z_VELO_right2[11]=-9;

  z_VELO_right2[12]=19;
  z_VELO_right2[13]=21;

  z_VELO_right2[14]=49;
  z_VELO_right2[15]=51;

  z_VELO_right2[16]=79;
  z_VELO_right2[17]=81;

  z_VELO_right2[18]=109;
  z_VELO_right2[19]=111;

  z_VELO_right2[20]=139;
  z_VELO_right2[21]=141;

  z_VELO_right2[22]=169;
  z_VELO_right2[23]=171;

  z_VELO_right2[24]=199;
  z_VELO_right2[25]=201;

  z_VELO_right2[26]=229;
  z_VELO_right2[27]=231;

  z_VELO_right2[28]=259;
  z_VELO_right2[29]=260.5;


  z_VELO_right2[30]=289;
  z_VELO_right2[31]=291;

  // low angle stations
  z_VELO_right2[32]=449;
  z_VELO_right2[33]=451;

  z_VELO_right2[34]=599;
  z_VELO_right2[35]=601;

  z_VELO_right2[36]=649;
  z_VELO_right2[37]=650.5;

  z_VELO_right2[38]=699;
  z_VELO_right2[39]=701;

  z_VELO_right2[40]=749;
  z_VELO_right2[41]=751;

  //============================================================================
  // Fill and write tree
  //============================================================================
  int nentries = (int)T->GetEntries();

    for(int i=0; i<nentries; i++)
    {
      T->GetEntry(i);

      // Add expected first measurement z


      newTree->Fill();
    }

  newTree->Write();
  newFile.Write();
  cout << "Tree " << input_tree << " with number of entries = "
  << newTree->GetEntries() << " written in file " << output_file << endl ;

}
