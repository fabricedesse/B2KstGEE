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

#include "create_tree.h"

using namespace std;

//==============================================================================
// Functions
//==============================================================================

TVector3 get_exp_firstMeasurement(Double_t PX, Double_t PY, Double_t PZ,
  Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y,
  Double_t mother_ENDVERTEX_Z, VELO myVELO)
{
  TVector3 exp_FirstMeasurement(-1000,-1000,-1000);

  for ( Int_t i = 0; i < myVELO.GetNbStations(); i++ )
  {
    Station myStation = myVELO.GetStation(i);
    Double_t z_VELO = myStation.GetZ();

    // Extrapolate x and y for all VELO positions upstream of the mother
    // z position
    if ( ( z_VELO - mother_ENDVERTEX_Z ) >= 0 )
    {
      if (PZ != 0)
      {
        exp_FirstMeasurement.SetX( mother_ENDVERTEX_X
          + ( PX/PZ ) * ( z_VELO - mother_ENDVERTEX_Z ) ) ;
        exp_FirstMeasurement.SetY( mother_ENDVERTEX_Y
          + ( PY/PZ ) * ( z_VELO - mother_ENDVERTEX_Z ) ) ;
      }
      else break;

      TVector2 XY(exp_FirstMeasurement.X(), exp_FirstMeasurement.Y())

      // Check if x is on the left/right and if it corresponds to the
      // isLeft/isRight of the tested VELO station
      if ( ( exp_FirstMeasurement.X() > 0 && myStation.IsLeft() ) ||
           ( exp_FirstMeasurement.X() < 0 && !(myStation.IsLeft() ) ) )
      {
       // If (x,y) is in the VELO acceptance this is the expected first
       // measurement in z
       if ( myStation.IsInAcceptance(XY) )
       {
         exp_FirstMeasurement.SetZ(z_VELO);
         break;
       }
       else continue;
      }
      else continue;
    }
  }
  return exp_FirstMeasurement ;
}

//==============================================================================
// Programm begins here
//==============================================================================

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

  // BKGCAT
  Int_t B0_BKGCAT;

  // Kst vertex
  Double_t Kst_TRUEORIGINVERTEX_X;
  Double_t Kst_TRUEORIGINVERTEX_Y;
  Double_t Kst_TRUEORIGINVERTEX_Z;

  Double_t Kst_TRUEENDVERTEX_X;
  Double_t Kst_TRUEENDVERTEX_Y;
  Double_t Kst_TRUEENDVERTEX_Z;

  Double_t Kst_ENDVERTEX_X;
  Double_t Kst_ENDVERTEX_Y;
  Double_t Kst_ENDVERTEX_Z;

  Double_t B0_ENDVERTEX_X;
  Double_t B0_ENDVERTEX_Y;
  Double_t B0_ENDVERTEX_Z;

  // E vertex
  Double_t E1_TRUEORIGINVERTEX_X;
  Double_t E1_TRUEORIGINVERTEX_Y;
  Double_t E1_TRUEORIGINVERTEX_Z;

  Double_t E2_TRUEORIGINVERTEX_X;
  Double_t E2_TRUEORIGINVERTEX_Y;
  Double_t E2_TRUEORIGINVERTEX_Z;

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
  T->SetBranchAddress("B0_BKGCAT", &B0_BKGCAT);

  T->SetBranchAddress("Kst_TRUEORIGINVERTEX_X", &Kst_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("Kst_TRUEORIGINVERTEX_Y", &Kst_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("Kst_TRUEORIGINVERTEX_Z", &Kst_TRUEORIGINVERTEX_Z);

  T->SetBranchAddress("Kst_TRUEENDVERTEX_X", &Kst_TRUEENDVERTEX_X);
  T->SetBranchAddress("Kst_TRUEENDVERTEX_Y", &Kst_TRUEENDVERTEX_Y);
  T->SetBranchAddress("Kst_TRUEENDVERTEX_Z", &Kst_TRUEENDVERTEX_Z);

  T->SetBranchAddress("Kst_ENDVERTEX_X", &Kst_ENDVERTEX_X);
  T->SetBranchAddress("Kst_ENDVERTEX_Y", &Kst_ENDVERTEX_Y);
  T->SetBranchAddress("Kst_ENDVERTEX_Z", &Kst_ENDVERTEX_Z);

  T->SetBranchAddress("E1_TRUEORIGINVERTEX_X", &E1_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Y", &E1_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Z", &E1_TRUEORIGINVERTEX_Z);

  T->SetBranchAddress("E2_TRUEORIGINVERTEX_X", &E2_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("E2_TRUEORIGINVERTEX_Y", &E2_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("E2_TRUEORIGINVERTEX_Z", &E2_TRUEORIGINVERTEX_Z);

  T->SetBranchAddress("B0_ENDVERTEX_X" ,&B0_ENDVERTEX_X);
  T->SetBranchAddress("B0_ENDVERTEX_Y" ,&B0_ENDVERTEX_Y);
  T->SetBranchAddress("B0_ENDVERTEX_Z" ,&B0_ENDVERTEX_Z);

  T->SetBranchAddress("E1_TRUEP_X", &E1_TRUEP_X);
  T->SetBranchAddress("E1_TRUEP_Y", &E1_TRUEP_Y);
  T->SetBranchAddress("E1_TRUEP_Z", &E1_TRUEP_Z);

  T->SetBranchAddress("E1_PX", &E1_PX);
  T->SetBranchAddress("E1_PY", &E1_PY);
  T->SetBranchAddress("E1_PZ", &E1_PZ);

  T->SetBranchAddress("E2_TRUEP_X", &E2_TRUEP_X);
  T->SetBranchAddress("E2_TRUEP_Y", &E2_TRUEP_Y);
  T->SetBranchAddress("E2_TRUEP_Z", &E2_TRUEP_Z);

  T->SetBranchAddress("E2_PX", &E2_PX);
  T->SetBranchAddress("E2_PY", &E2_PY);
  T->SetBranchAddress("E2_PZ", &E2_PZ);

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

  // Create LHCb VELO
  VELO myVELO;
  cout << "LHCb VELO has been created" << endl;
  myVELO.PrintStations();

  for(int i=0; i<nentries; i++)
  {
    T->GetEntry(i);

    if ( B0_BKGCAT == 0 || B0_BKGCAT == 50 || B0_BKGCAT == 10 )
    {
      // Add expected first measurement z
      E1_TRUE_EXP_TRACK_FirstMeasurementZ =
            get_exp_firstMeasurementZ(E1_TRUEP_X,E1_TRUEP_Y, E1_TRUEP_Z,
                                      E1_TRUEORIGINVERTEX_X,
                                      E1_TRUEORIGINVERTEX_Y,
                                      E1_TRUEORIGINVERTEX_Z, myVELO);

      E1_EXP_TRACK_FirstMeasurementZ =
            get_exp_firstMeasurementZ(E1_PX,E1_PY, E1_PZ,
                                Kst_ENDVERTEX_X,
                                Kst_ENDVERTEX_Y,
                                Kst_ENDVERTEX_Z, myVELO);

      E2_TRUE_EXP_TRACK_FirstMeasurementZ =
            get_exp_firstMeasurementZ(E2_TRUEP_X,E2_TRUEP_Y, E2_TRUEP_Z,
                                      E2_TRUEORIGINVERTEX_X,
                                      E2_TRUEORIGINVERTEX_Y,
                                      E2_TRUEORIGINVERTEX_Z, myVELO);
      E2_EXP_TRACK_FirstMeasurementZ =
            get_exp_firstMeasurementZ(E2_PX,E2_PY, E2_PZ,
                                Kst_ENDVERTEX_X,
                                Kst_ENDVERTEX_Y,
                                Kst_ENDVERTEX_Z, myVELO);

      newTree->Fill();
    }
  }
  newTree->Write();
  newFile.Write();
  cout << "Tree " << input_tree << " with number of entries = "
  << newTree->GetEntries() << " written in file " << output_file << endl ;
}
