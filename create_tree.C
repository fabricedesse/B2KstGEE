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
#include "TVector2.h"

using namespace std;

//==============================================================================
// Functions
//==============================================================================

Double_t get_exp_firstMeasurementZ(Double_t PX, Double_t PY, Double_t PZ,
  Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y,
  Double_t mother_ENDVERTEX_Z)
{
  //============================================================================
  // z-positions of velo stations (in mm). (0,0,0) is the position of the pp
  // interaction
  //============================================================================
  // CHECK VALUES
  Int_t nb_VELO_station = 21;
  Int_t z_VELO[2*nb_VELO_station];
  // left stations
    // central stations
    z_VELO[0]=-175;
    z_VELO[2]=-145;
    z_VELO[4]=-115;
    z_VELO[6]=-85;
    z_VELO[8]=-55;
    z_VELO[10]=-25;
    z_VELO[12]=5;
    z_VELO[14]=35;
    z_VELO[16]=65;
    z_VELO[18]=95;
    z_VELO[20]=125;
    z_VELO[22]=155;
    z_VELO[24]=185;
    z_VELO[26]=215;
    z_VELO[28]=245;
    z_VELO[30]=275;
    // low angle stations
    z_VELO[32]=435;
    z_VELO[34]=585;
    z_VELO[36]=635;
    z_VELO[38]=685;
    z_VELO[40]=735;
  // right stations
    // central stations
    z_VELO[1]=-160;
    z_VELO[3]=-130;
    z_VELO[5]=-100;
    z_VELO[7]=-70;
    z_VELO[9]=-40;
    z_VELO[11]=-10;
    z_VELO[13]=20;
    z_VELO[15]=50;
    z_VELO[17]=80;
    z_VELO[19]=110;
    z_VELO[21]=140;
    z_VELO[23]=170;
    z_VELO[25]=200;
    z_VELO[27]=230;
    z_VELO[29]=260;
    z_VELO[31]=290;
    // low angle stations
    z_VELO[33]=450;
    z_VELO[35]=600;
    z_VELO[37]=650;
    z_VELO[39]=700;
    z_VELO[41]=750;

  //============================================================================
  // Calculate expected first measurement in z if the particle originates from
  // the vertex of the input mother
  //============================================================================

  Double_t exp_FirstMeasurementZ = -1000;

  for ( Int_t i = 0; i < nb_VELO_station; i++ )
  {
    // Extrapolate x and y for all VELO positions upstream of the mother
    // z position
    if ( ( z_VELO[i] - mother_ENDVERTEX_Z ) >= 0 )
    {
      TVector2 XY(-1000,-1000);
      XY.SetX( mother_ENDVERTEX_X
        + ( PX/PZ ) * ( z_VELO[i] - mother_ENDVERTEX_Z ) );
      XY.SetY( mother_ENDVERTEX_Y
        + ( PY/PZ ) * ( z_VELO[i] - mother_ENDVERTEX_Z ) );

      // if (x,y) is in the VELO acceptance this is the expected first
      // measurement in z
      if ( XY.Mag() > 8.2 && XY.Mag() < 41.9 )
      {
        exp_FirstMeasurementZ = z[i] ;
      }
    }
  }

return exp_FirstMeasurementZ ;

}


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
  // Fill and write tree
  //============================================================================
  int nentries = (int)T->GetEntries();

    for(int i=0; i<nentries; i++)
    {
      T->GetEntry(i);

      // Add expected first measurement z
      E1_TRUE_EXP_TRACK_FirstMeasurementZ = get_exp_firstMeasurementZ();
      E1_EXP_TRACK_FirstMeasurementZ = get_exp_firstMeasurementZ();
      E2_TRUE_EXP_TRACK_FirstMeasurementZ = get_exp_firstMeasurementZ();
      E2_EXP_TRACK_FirstMeasurementZ = get_exp_firstMeasurementZ();

      newTree->Fill();
    }

  newTree->Write();
  newFile.Write();
  cout << "Tree " << input_tree << " with number of entries = "
  << newTree->GetEntries() << " written in file " << output_file << endl ;

}
