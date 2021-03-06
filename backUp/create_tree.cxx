//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Create tree for MC or data.
//
// void create_tree_MC()
// void create_tree_JPs()
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
  Double_t mother_ENDVERTEX_Z, VELO myVELO, Beam myBeam)
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

      TVector2 XY(exp_FirstMeasurement.X(), exp_FirstMeasurement.Y());

      // Check if x is on the left/right and if it corresponds to the
      // isLeft/isRight of the tested VELO station
      if ((exp_FirstMeasurement.X() > myBeam.GetX() && myStation.IsLeft() ) ||
          (exp_FirstMeasurement.X() < myBeam.GetX() && !(myStation.IsLeft())))
      {
       // If (x,y) is in the VELO acceptance this is the expected first
       // measurement in z
       if ( isInAcceptance(XY, myBeam, false) )
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

bool ConvertsBeforeStation ( TVector3 JPs_FirstVELOhit, Double_t JPs_ENDVERTEX_Z, VELO myVELO )
{
  // Case the JPs never encounters a station
  if ( JPs_FirstVELOhit.Z() == -1000 ) return true;

  else
  {
    // Get station corresponding to JPs_FirstVELOhit
    Station hit_station = myVELO.GetStationAtZ( JPs_FirstVELOhit.Z() );

    // Get end of this station
    Double_t station_end = -1000;
    if ( hit_station.IsFront() )
    {
      Station back_station = myVELO.GetStationNb( hit_station.GetNumber() + 1 );
      station_end = back_station.GetZ() + VELO_geo::station_width;
    }
    else station_end = hit_station.GetZ() + VELO_geo::station_width;

    // Check wether conversion happens before or after the hit station
    if ( JPs_ENDVERTEX_Z < station_end ) return true;
    else return false;
  }
}

//==============================================================================
// Programm begins here
//==============================================================================

void create_tree_MC (TString input_file, TString input_tree, TString output_file)
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

  // B0
  Double_t B0_TRUEORIGINVERTEX_X;
  Double_t B0_TRUEORIGINVERTEX_Y;
  Double_t B0_TRUEORIGINVERTEX_Z;

  Double_t B0_OWNPV_X;
  Double_t B0_OWNPV_Y;
  Double_t B0_OWNPV_Z;

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
  Double_t E1_P;
  Double_t E1_PT;

  Double_t E2_TRUEP_X;
  Double_t E2_TRUEP_Y;
  Double_t E2_TRUEP_Z;
  Double_t E2_P;
  Double_t E2_PT;

  Double_t E2_PX;
  Double_t E2_PY;
  Double_t E2_PZ;

  // JPs
  Double_t JPs_PX;
  Double_t JPs_PY;
  Double_t JPs_PZ;
  Double_t JPs_P;
  Double_t JPs_PT;

  Double_t JPs_TRUEP_X;
  Double_t JPs_TRUEP_Y;
  Double_t JPs_TRUEP_Z;

  Double_t JPs_TRUEORIGINVERTEX_X;
  Double_t JPs_TRUEORIGINVERTEX_Y;
  Double_t JPs_TRUEORIGINVERTEX_Z;

  // K
  Double_t K_PT;
  Double_t K_P;
  Double_t K_PX;
  Double_t K_PY;
  Double_t K_PZ;

  // E FirstMeasurementX
  Double_t E1_TRACK_FirstMeasurementX;
  Double_t E1_TRACK_FirstMeasurementY;
  Double_t E2_TRACK_FirstMeasurementX;
  Double_t E2_TRACK_FirstMeasurementY;

  // New variables
  Double_t E1_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E2_TRUE_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E1_EXP_TRACK_FirstMeasurementY = -1000;
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementY = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementY = -1000;
  Double_t E2_TRUE_EXP_TRACK_FirstMeasurementY = -1000;
  Double_t E1_EXP_TRACK_FirstMeasurementX = -1000;
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementX = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementX = -1000;
  Double_t E2_TRUE_EXP_TRACK_FirstMeasurementX = -1000;
  Double_t E1_XY_FROM_BEAM = -1000;
  Double_t E2_XY_FROM_BEAM = -1000;
  Double_t E1_TRUE_PHI = -1000;
  Double_t E1_PHI = -1000;
  Double_t E2_TRUE_PHI = -1000;
  Double_t E2_PHI = -1000;
  Double_t JPs_PHI = -1000;
  Double_t K_PHI = -1000;
  Double_t K_THETA_K = -1000;
  Bool_t G_CONV_IN_STATIONS;
  Bool_t G_CONV_BEFORE;
  Double_t E1_First_PHI = -1000;
  Double_t E2_First_PHI = -1000;
  Double_t E1_THETA_K = -1000;
  Double_t E2_THETA_K = -1000;
  Double_t JPs_THETA_K = -1000;

  // Set branch addresses
  T->SetBranchAddress("B0_BKGCAT", &B0_BKGCAT);

  T->SetBranchAddress("B0_TRUEORIGINVERTEX_X", &B0_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("B0_TRUEORIGINVERTEX_Y", &B0_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("B0_TRUEORIGINVERTEX_Z", &B0_TRUEORIGINVERTEX_Z);

  T->SetBranchAddress("B0_OWNPV_X", &B0_OWNPV_X);
  T->SetBranchAddress("B0_OWNPV_Y", &B0_OWNPV_Y);
  T->SetBranchAddress("B0_OWNPV_Z", &B0_OWNPV_Z);

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
  T->SetBranchAddress("E1_P", &E1_P);
  T->SetBranchAddress("E1_PT", &E1_PT);

  T->SetBranchAddress("E2_TRUEP_X", &E2_TRUEP_X);
  T->SetBranchAddress("E2_TRUEP_Y", &E2_TRUEP_Y);
  T->SetBranchAddress("E2_TRUEP_Z", &E2_TRUEP_Z);
  T->SetBranchAddress("E2_P", &E2_P);
  T->SetBranchAddress("E2_PT", &E2_PT);

  T->SetBranchAddress("E2_PX", &E2_PX);
  T->SetBranchAddress("E2_PY", &E2_PY);
  T->SetBranchAddress("E2_PZ", &E2_PZ);

  T->SetBranchAddress("JPs_PX", &JPs_PX);
  T->SetBranchAddress("JPs_PY", &JPs_PY);
  T->SetBranchAddress("JPs_PZ", &JPs_PZ);
  T->SetBranchAddress("JPs_P", &JPs_P);
  T->SetBranchAddress("JPs_PT", &JPs_PT);

  T->SetBranchAddress("JPs_TRUEP_X", &JPs_TRUEP_X);
  T->SetBranchAddress("JPs_TRUEP_Y", &JPs_TRUEP_Y);
  T->SetBranchAddress("JPs_TRUEP_Z", &JPs_TRUEP_Z);

  T->SetBranchAddress("JPs_TRUEORIGINVERTEX_X", &JPs_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("JPs_TRUEORIGINVERTEX_Y", &JPs_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("JPs_TRUEORIGINVERTEX_Z", &JPs_TRUEORIGINVERTEX_Z);

  T->SetBranchAddress("K_P", &K_P);
  T->SetBranchAddress("K_PT", &K_PT);
  T->SetBranchAddress("K_PX", &K_PX);
  T->SetBranchAddress("K_PY", &K_PY);
  T->SetBranchAddress("K_PZ", &K_PZ);

  T->SetBranchAddress("E1_TRACK_FirstMeasurementX", &E1_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementY", &E1_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementX", &E2_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementY", &E2_TRACK_FirstMeasurementY);

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

  TBranch *b_E1_EXP_TRACK_FirstMeasurementY =
    newTree->Branch("E1_EXP_TRACK_FirstMeasurementY",
    &E1_EXP_TRACK_FirstMeasurementY);
  TBranch *b_E1_TRUE_EXP_TRACK_FirstMeasurementY =
    newTree->Branch("E1_TRUE_EXP_TRACK_FirstMeasurementY",
    &E1_TRUE_EXP_TRACK_FirstMeasurementY);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementY =
    newTree->Branch("E2_EXP_TRACK_FirstMeasurementY",
    &E2_EXP_TRACK_FirstMeasurementY);
  TBranch *b_E2_TRUE_EXP_TRACK_FirstMeasurementY =
    newTree->Branch("E2_TRUE_EXP_TRACK_FirstMeasurementY",
    &E2_TRUE_EXP_TRACK_FirstMeasurementY);

  TBranch *b_E1_EXP_TRACK_FirstMeasurementX = newTree->Branch("E1_EXP_TRACK_FirstMeasurementX", &E1_EXP_TRACK_FirstMeasurementX);
  TBranch *b_E1_TRUE_EXP_TRACK_FirstMeasurementX = newTree->Branch("E1_TRUE_EXP_TRACK_FirstMeasurementX", &E1_TRUE_EXP_TRACK_FirstMeasurementX);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementX = newTree->Branch("E2_EXP_TRACK_FirstMeasurementX", &E2_EXP_TRACK_FirstMeasurementX);
  TBranch *b_E2_TRUE_EXP_TRACK_FirstMeasurementX = newTree->Branch("E2_TRUE_EXP_TRACK_FirstMeasurementX", &E2_TRUE_EXP_TRACK_FirstMeasurementX);

  TBranch *b_E1_XY_FROM_BEAM = newTree->Branch("E1_XY_FROM_BEAM", &E1_XY_FROM_BEAM);
  TBranch *b_E2_XY_FROM_BEAM = newTree->Branch("E2_XY_FROM_BEAM", &E2_XY_FROM_BEAM);

  TBranch *b_E1_TRUE_PHI = newTree->Branch("E1_TRUE_PHI", &E1_TRUE_PHI);
  TBranch *b_E1_PHI = newTree->Branch("E1_PHI", &E1_PHI);
  TBranch *b_E2_TRUE_PHI = newTree->Branch("E2_TRUE_PHI", &E2_TRUE_PHI);
  TBranch *b_E2_PHI = newTree->Branch("E2_PHI", &E2_PHI);
  TBranch *b_JPs_PHI = newTree->Branch("JPs_PHI", &JPs_PHI);
  TBranch *b_K_PHI = newTree->Branch("K_PHI", &K_PHI);

  TBranch *b_K_THETA_K = newTree->Branch("K_THETA_K", &K_THETA_K);
  TBranch *b_E1_THETA_K = newTree->Branch("E1_THETA_K", &E1_THETA_K);
  TBranch *b_E2_THETA_K = newTree->Branch("E2_THETA_K", &E2_THETA_K);
  TBranch *b_JPs_THETA_K = newTree->Branch("JPs_THETA_K", &JPs_THETA_K);

  TBranch *b_G_CONV_IN_STATIONS = newTree->Branch("G_CONV_IN_STATIONS", &G_CONV_IN_STATIONS);

  TBranch *b_G_CONV_BEFORE = newTree->Branch("G_CONV_BEFORE", &G_CONV_BEFORE);

  TBranch *b_E1_First_PHI = newTree->Branch("E1_First_PHI", &E1_First_PHI);
  TBranch *b_E2_First_PHI = newTree->Branch("E2_First_PHI", &E2_First_PHI);


  //============================================================================
  // Create LHCb VELO and LHC beam
  //============================================================================

  // Create LHC beam
  Beam myBeamTRUE;

  T->Draw("B0_TRUEORIGINVERTEX_X>>hTRUE_beamX",
          "B0_BKGCAT == 0 || B0_BKGCAT == 50 || B0_BKGCAT == 10");
  TH1F *hTRUE_beamX = (TH1F*)gDirectory->Get("hTRUE_beamX");
  myBeamTRUE.SetX( hTRUE_beamX->GetMean() );

  T->Draw("B0_TRUEORIGINVERTEX_Y>>hTRUE_beamY",
          "B0_BKGCAT == 0 || B0_BKGCAT == 50 || B0_BKGCAT == 10");
  TH1F *hTRUE_beamY = (TH1F*)gDirectory->Get("hTRUE_beamY");
  myBeamTRUE.SetY( hTRUE_beamY->GetMean() );

  Beam myBeam;

  T->Draw("B0_OWNPV_X>>h_beamX",
          "B0_BKGCAT == 0 || B0_BKGCAT == 50 || B0_BKGCAT == 10");
  TH1F *h_beamX = (TH1F*)gDirectory->Get("h_beamX");
  myBeam.SetX( h_beamX->GetMean() );

  T->Draw("B0_OWNPV_Y>>h_beamY",
          "B0_BKGCAT == 0 || B0_BKGCAT == 50 || B0_BKGCAT == 10");
  TH1F *h_beamY = (TH1F*)gDirectory->Get("h_beamY");
  myBeam.SetY( h_beamY->GetMean() );

  // Create LHCb VELO
  VELO myVELO;
  cout << "LHCb VELO has been created" << endl;
  myVELO.PrintStations();

  //============================================================================
  // Fill and write tree
  //============================================================================
  int nentries = (int)T->GetEntries();

  for(int i=0; i<nentries; i++)
  {
    T->GetEntry(i);

    if ( B0_BKGCAT == 0 || B0_BKGCAT == 50 || B0_BKGCAT == 10 )
    {
      // FirstMeasurement
      TVector3 E1_TRUE_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E1_TRUEP_X,E1_TRUEP_Y, E1_TRUEP_Z, E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y, E1_TRUEORIGINVERTEX_Z, myVELO, myBeamTRUE);
      TVector3 E1_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E1_PX,E1_PY, E1_PZ, Kst_ENDVERTEX_X, Kst_ENDVERTEX_Y, Kst_ENDVERTEX_Z, myVELO, myBeam);
      TVector3 E2_TRUE_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E2_TRUEP_X,E2_TRUEP_Y, E2_TRUEP_Z, E2_TRUEORIGINVERTEX_X, E2_TRUEORIGINVERTEX_Y, E2_TRUEORIGINVERTEX_Z, myVELO, myBeam);
      TVector3 E2_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E2_PX,E2_PY, E2_PZ, Kst_ENDVERTEX_X, Kst_ENDVERTEX_Y, Kst_ENDVERTEX_Z, myVELO, myBeam);

      E1_TRUE_EXP_TRACK_FirstMeasurementZ = E1_TRUE_EXP_TRACK_FirstMeasurement.Z();
      E1_EXP_TRACK_FirstMeasurementZ = E1_EXP_TRACK_FirstMeasurement.Z();
      E2_TRUE_EXP_TRACK_FirstMeasurementZ = E2_TRUE_EXP_TRACK_FirstMeasurement.Z();
      E2_EXP_TRACK_FirstMeasurementZ = E2_EXP_TRACK_FirstMeasurement.Z();

      E1_TRUE_EXP_TRACK_FirstMeasurementY = E1_TRUE_EXP_TRACK_FirstMeasurement.Y();
      E1_EXP_TRACK_FirstMeasurementY = E1_EXP_TRACK_FirstMeasurement.Y();
      E2_TRUE_EXP_TRACK_FirstMeasurementY = E2_TRUE_EXP_TRACK_FirstMeasurement.Y();
      E2_EXP_TRACK_FirstMeasurementY = E2_EXP_TRACK_FirstMeasurement.Y();

      E1_TRUE_EXP_TRACK_FirstMeasurementX = E1_TRUE_EXP_TRACK_FirstMeasurement.X();
      E1_EXP_TRACK_FirstMeasurementX = E1_EXP_TRACK_FirstMeasurement.X();
      E2_TRUE_EXP_TRACK_FirstMeasurementX = E2_TRUE_EXP_TRACK_FirstMeasurement.X();
      E2_EXP_TRACK_FirstMeasurementX = E2_EXP_TRACK_FirstMeasurement.X();


      // Converts before station
      TVector3 JPs_TRUE_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( JPs_TRUEP_X, JPs_TRUEP_Y, JPs_TRUEP_Z, JPs_TRUEORIGINVERTEX_X, JPs_TRUEORIGINVERTEX_Y, JPs_TRUEORIGINVERTEX_Z, myVELO, myBeam );

      G_CONV_BEFORE = ConvertsBeforeStation( JPs_TRUE_EXP_TRACK_FirstMeasurement, E1_TRUEORIGINVERTEX_Z, myVELO );


      // XY_FROM_BEAM
      // Rescale center (0,0) to (beamX,beamY)
      Double_t beamX = myBeam.GetX();
      Double_t beamY = myBeam.GetY();
      TVector2 XYbeam( -beamX, -beamY );

      // Calculated distance of XY FirstMeasurement from beam axis
      TVector2 E1_XY(E1_TRACK_FirstMeasurementX, E1_TRACK_FirstMeasurementY);
      TVector2 E1_XY_recentered = XYbeam + E1_XY;
      E1_XY_FROM_BEAM = E1_XY_recentered.Mod();

      TVector2 E2_XY(E2_TRACK_FirstMeasurementX, E2_TRACK_FirstMeasurementY);
      TVector2 E2_XY_recentered = XYbeam + E2_XY;
      E2_XY_FROM_BEAM = E2_XY_recentered.Mod();


      // Phi
      TVector3 E1_3P(E1_PX, E1_PY, E1_PZ);
      E1_PHI = E1_3P.Phi();
      TVector3 E2_3P(E2_PX, E2_PY, E2_PZ);
      E2_PHI = E2_3P.Phi();
      TVector3 JPs_3P(JPs_PX, JPs_PY, JPs_PZ);
      JPs_PHI = JPs_3P.Phi();
      TVector3 K_3P(K_PX, K_PY, K_PZ);
      K_PHI = K_3P.Phi();
      TVector3 E1_First_3P(E1_TRACK_FirstMeasurementX, E1_TRACK_FirstMeasurementY, 0);
      E1_First_PHI = E1_First_3P.Phi();
      TVector3 E2_First_3P(E2_TRACK_FirstMeasurementX, E2_TRACK_FirstMeasurementY, 0);
      E2_First_PHI = E2_First_3P.Phi();

      // theta_k
      K_THETA_K = sin( K_PT / K_P );
      E1_THETA_K = sin( E1_PT / E1_P );
      E2_THETA_K = sin( E2_PT / E1_P );
      JPs_THETA_K = sin( JPs_PT / JPs_P );

      // G converted in stations
      G_CONV_IN_STATIONS = myVELO.IsInStations(E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y, E1_TRUEORIGINVERTEX_Z, myBeam);

      newTree->Fill();
    }
  }
  newTree->Write();
  newFile.Write();
  cout << "Tree " << input_tree << " with number of entries = "
  << newTree->GetEntries() << " written in file " << output_file << endl << endl ;
}


void create_tree_JPs(TString input_file, TString input_tree, TString output_file)
{
  //============================================================================
  // Open and clone tree, set branch addresses
  //============================================================================

  TFile *f = new TFile(input_file,"read");
  TTree *T = (TTree*)f->Get(input_tree);

  TFile newFile(output_file,"RECREATE");
  TTree *newTree = T->CloneTree(0);

  cout << "Cloned tree " << input_tree << "with number of entries = " << T->GetEntries() << endl ;

  Double_t E1_PE, E1_PX, E1_PY, E1_PZ, E1_P, E1_PT;
  Double_t E2_PE, E2_PX, E2_PY, E2_PZ, E2_P, E2_PT;
  Double_t K_PE, K_PX, K_PY, K_PZ, K_P, K_PT;
  Double_t Pi_PE, Pi_PX, Pi_PY, Pi_PZ;
  Double_t JPs_PE, JPs_PX, JPs_PY, JPs_PZ, JPs_P, JPs_PT;

  Double_t Kst_ENDVERTEX_X;
  Double_t Kst_ENDVERTEX_Y;
  Double_t Kst_ENDVERTEX_Z;

  Double_t E1_TRACK_FirstMeasurementX;
  Double_t E1_TRACK_FirstMeasurementY;
  Double_t E2_TRACK_FirstMeasurementX;
  Double_t E2_TRACK_FirstMeasurementY;

  Double_t JPs_TRUE_M = 3096.900;
  Double_t B0_M_cut = 5175.;

  T->SetBranchAddress("E1_PE", &E1_PE);
  T->SetBranchAddress("E1_PX", &E1_PX);
  T->SetBranchAddress("E1_PY", &E1_PY);
  T->SetBranchAddress("E1_PZ", &E1_PZ);
  T->SetBranchAddress("E1_P", &E1_P);
  T->SetBranchAddress("E1_PT", &E1_PT);

  T->SetBranchAddress("E2_PE", &E2_PE);
  T->SetBranchAddress("E2_PX", &E2_PX);
  T->SetBranchAddress("E2_PY", &E2_PY);
  T->SetBranchAddress("E2_PZ", &E2_PZ);
  T->SetBranchAddress("E2_P", &E2_P);
  T->SetBranchAddress("E2_PT", &E2_PT);

  T->SetBranchAddress("K_PE", &K_PE);
  T->SetBranchAddress("K_PX", &K_PX);
  T->SetBranchAddress("K_PY", &K_PY);
  T->SetBranchAddress("K_PZ", &K_PZ);
  T->SetBranchAddress("K_P", &K_P);
  T->SetBranchAddress("K_PT", &K_PT);

  T->SetBranchAddress("Pi_PE", &Pi_PE);
  T->SetBranchAddress("Pi_PX", &Pi_PX);
  T->SetBranchAddress("Pi_PY", &Pi_PY);
  T->SetBranchAddress("Pi_PZ", &Pi_PZ);

  T->SetBranchAddress("JPs_PE", &JPs_PE);
  T->SetBranchAddress("JPs_PX", &JPs_PX);
  T->SetBranchAddress("JPs_PY", &JPs_PY);
  T->SetBranchAddress("JPs_PZ", &JPs_PZ);
  T->SetBranchAddress("JPs_P", &JPs_P);
  T->SetBranchAddress("JPs_PT", &JPs_PT);

  T->SetBranchAddress("Kst_ENDVERTEX_X", &Kst_ENDVERTEX_X);
  T->SetBranchAddress("Kst_ENDVERTEX_Y", &Kst_ENDVERTEX_Y);
  T->SetBranchAddress("Kst_ENDVERTEX_Z", &Kst_ENDVERTEX_Z);

  T->SetBranchAddress("E1_TRACK_FirstMeasurementX", &E1_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementY", &E1_TRACK_FirstMeasurementY);

  T->SetBranchAddress("E2_TRACK_FirstMeasurementX", &E2_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementY", &E2_TRACK_FirstMeasurementY);

  // New variables
  Double_t E1_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementZ = -1000;
  Double_t E1_EXP_TRACK_FirstMeasurementY = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementY = -1000;
  Double_t E1_EXP_TRACK_FirstMeasurementX = -1000;
  Double_t E2_EXP_TRACK_FirstMeasurementX = -1000;

  Double_t E1_First_PHI = -1000;
  Double_t E2_First_PHI = -1000;

  Double_t E1_PHI = -1000;
  Double_t E2_PHI = -1000;
  Double_t JPs_PHI = -1000;
  Double_t K_PHI = -1000;

  Double_t E1_XY_FROM_BEAM = -1000;
  Double_t E2_XY_FROM_BEAM = -1000;

  Double_t K_THETA_K = -1000;
  Double_t E1_THETA_K = -1000;
  Double_t E2_THETA_K = -1000;
  Double_t JPs_THETA_K = -1000;

  TBranch *b_E1_EXP_TRACK_FirstMeasurementZ = newTree->Branch("E1_EXP_TRACK_FirstMeasurementZ", &E1_EXP_TRACK_FirstMeasurementZ);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementZ = newTree->Branch("E2_EXP_TRACK_FirstMeasurementZ", &E2_EXP_TRACK_FirstMeasurementZ);

  TBranch *b_E1_EXP_TRACK_FirstMeasurementY = newTree->Branch("E1_EXP_TRACK_FirstMeasurementY", &E1_EXP_TRACK_FirstMeasurementY);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementY = newTree->Branch("E2_EXP_TRACK_FirstMeasurementY", &E2_EXP_TRACK_FirstMeasurementY);

  TBranch *b_E1_EXP_TRACK_FirstMeasurementX = newTree->Branch("E1_EXP_TRACK_FirstMeasurementX", &E1_EXP_TRACK_FirstMeasurementX);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementX = newTree->Branch("E2_EXP_TRACK_FirstMeasurementX", &E2_EXP_TRACK_FirstMeasurementX);

  TBranch *b_E1_XY_FROM_BEAM = newTree->Branch("E1_XY_FROM_BEAM", &E1_XY_FROM_BEAM);
  TBranch *b_E2_XY_FROM_BEAM = newTree->Branch("E2_XY_FROM_BEAM", &E2_XY_FROM_BEAM);

  TBranch *b_E1_First_PHI = newTree->Branch("E1_First_PHI", &E1_First_PHI);
  TBranch *b_E2_First_PHI = newTree->Branch("E2_First_PHI", &E2_First_PHI);

  TBranch *b_E1_PHI = newTree->Branch("E1_PHI", &E1_PHI);
  TBranch *b_E2_PHI = newTree->Branch("E2_PHI", &E2_PHI);
  TBranch *b_JPs_PHI = newTree->Branch("JPs_PHI", &JPs_PHI);
  TBranch *b_K_PHI = newTree->Branch("K_PHI", &K_PHI);

  TBranch *b_E1_THETA_K = newTree->Branch("E1_THETA_K", &E1_THETA_K);
  TBranch *b_E2_THETA_K = newTree->Branch("E2_THETA_K", &E2_THETA_K);
  TBranch *b_JPs_THETA_K = newTree->Branch("JPs_THETA_K", &JPs_THETA_K);
  TBranch *b_K_THETA_K = newTree->Branch("K_THETA_K", &K_THETA_K);


  //============================================================================
  // Fill and write tree
  //============================================================================
  int nentries = (int)T->GetEntries();

  // Create LHCb VELO
  VELO myVELO;
  cout << "LHCb VELO has been created" << endl;
  myVELO.PrintStations();

  // Create LHC beam
  Beam myBeam;

  T->Draw("B0_OWNPV_X>>h_beamX");
  TH1F *h_beamX = (TH1F*)gDirectory->Get("h_beamX");
  myBeam.SetX( h_beamX->GetMean() );

  T->Draw("B0_OWNPV_Y>>h_beamY");
  TH1F *h_beamY = (TH1F*)gDirectory->Get("h_beamY");
  myBeam.SetY( h_beamY->GetMean() );

  for ( int i=0; i<nentries; i++)
  {
    T->GetEntry(i);
    // Force EE to be at JPs mass
    TLorentzVector P_EE_fake;
    P_EE_fake.SetXYZM( E1_PX + E2_PX, E1_PY + E2_PY, E1_PZ + E2_PZ, JPs_TRUE_M );

    // Fake m(KpiEE)
    TLorentzVector P_K( K_PX, K_PY, K_PZ, K_PE );
    TLorentzVector P_Pi( Pi_PX, Pi_PY, Pi_PZ, Pi_PE );
    TLorentzVector P_B0_fake;
    P_B0_fake = P_K + P_Pi + P_EE_fake;
    Double_t B0_M_fake = P_B0_fake.M();

    // Select events
    if ( B0_M_fake > B0_M_cut )
    {
      // FirstMeasurement
      TVector3 E1_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E1_PX, E1_PY, E1_PZ, Kst_ENDVERTEX_X, Kst_ENDVERTEX_Y, Kst_ENDVERTEX_Z, myVELO, myBeam);
      TVector3 E2_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E2_PX, E2_PY, E2_PZ, Kst_ENDVERTEX_X, Kst_ENDVERTEX_Y, Kst_ENDVERTEX_Z, myVELO, myBeam);

      E1_EXP_TRACK_FirstMeasurementZ = E1_EXP_TRACK_FirstMeasurement.Z();
      E2_EXP_TRACK_FirstMeasurementZ = E2_EXP_TRACK_FirstMeasurement.Z();

      E1_EXP_TRACK_FirstMeasurementY = E1_EXP_TRACK_FirstMeasurement.Y();
      E2_EXP_TRACK_FirstMeasurementY = E2_EXP_TRACK_FirstMeasurement.Y();

      E1_EXP_TRACK_FirstMeasurementX = E1_EXP_TRACK_FirstMeasurement.X();
      E2_EXP_TRACK_FirstMeasurementX = E2_EXP_TRACK_FirstMeasurement.X();


      // XY_FROM_BEAM
      // Rescale center (0,0) to (beamX,beamY)
      Double_t beamX = myBeam.GetX();
      Double_t beamY = myBeam.GetY();
      TVector2 XYbeam( -beamX, -beamY );

      // Calculated distance of XY FirstMeasurement from beam axis
      TVector2 E1_XY(E1_TRACK_FirstMeasurementX, E1_TRACK_FirstMeasurementY);
      TVector2 E1_XY_recentered = XYbeam + E1_XY;
      E1_XY_FROM_BEAM = E1_XY_recentered.Mod();

      TVector2 E2_XY(E2_TRACK_FirstMeasurementX, E2_TRACK_FirstMeasurementY);
      TVector2 E2_XY_recentered = XYbeam + E2_XY;
      E2_XY_FROM_BEAM = E2_XY_recentered.Mod();

      // Phi
      TVector3 E1_3P(E1_PX, E1_PY, E1_PZ);
      E1_PHI = E1_3P.Phi();
      TVector3 E2_3P(E2_PX, E2_PY, E2_PZ);
      E2_PHI = E2_3P.Phi();
      TVector3 JPs_3P(JPs_PX, JPs_PY, JPs_PZ);
      JPs_PHI = JPs_3P.Phi();
      TVector3 K_3P(K_PX, K_PY, K_PZ);
      K_PHI = K_3P.Phi();
      TVector3 E1_First_3P(E1_TRACK_FirstMeasurementX, E1_TRACK_FirstMeasurementY, 0);
      E1_First_PHI = E1_First_3P.Phi();
      TVector3 E2_First_3P(E2_TRACK_FirstMeasurementX, E2_TRACK_FirstMeasurementY, 0);
      E2_First_PHI = E2_First_3P.Phi();

      // theta_k
      K_THETA_K = sin( K_PT / K_P );
      E1_THETA_K = sin( E1_PT / E1_P );
      E2_THETA_K = sin( E2_PT / E1_P );
      JPs_THETA_K = sin( JPs_PT / JPs_P );

      newTree->Fill();
    }
  }

  newTree->Write();
  newFile.Write();
  cout << "Tree " << input_tree << " with number of entries = "
  << newTree->GetEntries() << " written in file " << output_file << endl ;

}
