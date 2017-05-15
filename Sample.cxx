//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Implementation file for class : Sample
//
//==============================================================================

#include "Sample.h"

//============================================================================
// Constructor
//============================================================================

// Generic constructor
Sample::Sample()
{

}

// Full constructor
Sample::Sample(TString fileName, TString treeName, Sample::DecayType type, Sample::TriggerCat triggerCat)
{
  sample_fileName = fileName;
  sample_treeName = treeName;
  sample_file = new TFile(fileName, "read");
  sample_tree = (TTree*) sample_file->Get(treeName);
  sample_type = type;
  sample_triggerCat = triggerCat;

  switch(sample_type)
  {
    case DecayType::data_KstEE:
      sample_isMC = false;
      sample_isJPs = false;
      break;

    case DecayType::data_KstJPsEE:
      sample_isMC = false;
      sample_isJPs = true;
      break;

    case DecayType::MC_KstGEE:
      sample_isMC = true;
      sample_isJPs = false;
      break;

    case DecayType::MC_KstEE:
      sample_isMC = true;
      sample_isJPs = false;
      break;

    case DecayType::MC_KstJPsEE:
      sample_isMC = true;
      sample_isJPs = true;
      break;
  }
}

//============================================================================
// Public member functions
//============================================================================

// Getters
TString Sample::GetFileName()
{
  return sample_fileName;
}

TString Sample::GetTreeName()
{
  return sample_treeName;
}

bool Sample::IsMC()
{
  return sample_isMC;
}

Sample::DecayType Sample::GetType()
{
  return sample_type;
}

Sample::TriggerCat Sample::GetTriggerCat()
{
  return sample_triggerCat;
}

TFile* Sample::GetFile()
{
  return sample_file;
}

TTree* Sample::GetTree()
{
  return sample_tree;
}

// Setters

void Sample::SetFileName( TString fileName )
{
  sample_fileName = fileName;
}

void Sample::SetTreeName( TString treeName )
{
  sample_treeName = treeName;
}

void Sample::SetDecayType( Sample::DecayType type )
{
  sample_type = type;
}

void Sample::SetTriggerCat( Sample::TriggerCat triggerCat )
{
  sample_triggerCat = triggerCat;
}

// Updaters

void Sample::Update()
{
  sample_file = new TFile(sample_fileName, "read");
  sample_tree = (TTree*) sample_file->Get(sample_treeName);

  switch(sample_type)
  {
    case DecayType::data_KstEE:
      sample_isMC = false;
      sample_isJPs = false;
      break;

    case DecayType::data_KstJPsEE:
      sample_isMC = false;
      sample_isJPs = true;
      break;

    case DecayType::MC_KstGEE:
      sample_isMC = true;
      sample_isJPs = false;
      break;

    case DecayType::MC_KstEE:
      sample_isMC = true;
      sample_isJPs = false;
      break;

    case DecayType::MC_KstJPsEE:
      sample_isMC = true;
      sample_isJPs = true;
      break;
  }
}

void Sample::UpdateTreeName( DecayType myDecayType, TriggerCat myTriggerCat )
{
  // Construct tree name
  TString myTreeName = "";

  switch(myDecayType)
  {
    case Sample::DecayType::MC_KstGEE:
      myTreeName = "Bd2KstGEE";
      break;

    case Sample::DecayType::MC_KstEE:
      myTreeName = "Bd2KstEE";
      break;

    case Sample::DecayType::data_KstEE:
      myTreeName = "data";
      break;
  }

  switch(myTriggerCat)
  {
    case Sample::TriggerCat::all:
      break;

    case Sample::TriggerCat::L0L:
      myTreeName = myTreeName+"_L0L";
      break;

    case Sample::TriggerCat::L0H:
      myTreeName = myTreeName+"_L0H";
      break;

    case Sample::TriggerCat::L0I:
      myTreeName = myTreeName+"_L0I";
      break;
  }

  sample_treeName = myTreeName;
}

//******************************************************************************

// Create tuples

void Sample::MakePreselection( TFile* newFile, Q2Bin* myQ2Bin, TString triggerCat )
{
  //============================================================================
  // Init new tree
  //============================================================================
  newFile->ReOpen("update");
  TTree *newTree = sample_tree->CloneTree(0);
  std::cout << "Cloned tree " << sample_treeName << " with number of entries = "<< sample_tree->GetEntries() << std::endl ;

  TString newTreeName;
  switch(sample_type)
  {
    case DecayType::data_KstEE:
      newTreeName = "data";
      if ( triggerCat != "" ) newTreeName = "data_"+triggerCat;
      break;

    case DecayType::data_KstJPsEE:
      newTreeName = "data";
      if ( triggerCat != "" ) newTreeName = "data_"+triggerCat;
      break;

    case DecayType::MC_KstGEE:
      newTreeName = "Bd2KstGEE";
      if ( triggerCat != "" ) newTreeName = "Bd2KstGEE_"+triggerCat;
      break;

    case DecayType::MC_KstEE:
      newTreeName = "Bd2KstEE";
      if ( triggerCat != "" ) newTreeName = "Bd2KstEE_"+triggerCat;
      break;

    case DecayType::MC_KstJPsEE:
      newTreeName = "Bd2KstJPsEE";
      if ( triggerCat != "" ) newTreeName = "Bd2KstJPsEE_"+triggerCat;
      break;
  }
  newTree->SetName( newTreeName );

  // Common to all samples
  Int_t K_L0Calo_HCAL_region, Pi_L0Calo_HCAL_region, E1_L0Calo_ECAL_region, E2_L0Calo_ECAL_region;
  Bool_t E1_L0ElectronDecision_TOS, E2_L0ElectronDecision_TOS, K_L0HadronDecision_TOS, Pi_L0HadronDecision_TOS, B0_L0Global_TIS, K_hasRich, Pi_hasRich, E1_hasRich, E2_hasRich, E1_hasCalo, E2_hasCalo, B0_Hlt1TrackAllL0Decision_TOS, B0_Hlt2Topo2BodyBBDTDecision_TOS, B0_Hlt2Topo3BodyBBDTDecision_TOS, B0_Hlt2Topo4BodyBBDTDecision_TOS, B0_Hlt2TopoE2BodyBBDTDecision_TOS, B0_Hlt2TopoE3BodyBBDTDecision_TOS, B0_Hlt2TopoE4BodyBBDTDecision_TOS;
  Double_t K_PT, Pi_PT, E1_PT, E2_PT, K_TRACK_CHI2NDOF, Pi_TRACK_CHI2NDOF, E1_TRACK_CHI2NDOF, E2_TRACK_CHI2NDOF, K_TRACK_GhostProb, Pi_TRACK_GhostProb, E1_TRACK_GhostProb, E2_TRACK_GhostProb, E1_L0Calo_ECAL_xProjection, E1_L0Calo_ECAL_yProjection, E2_L0Calo_ECAL_xProjection, E2_L0Calo_ECAL_yProjection, Kst_M, B0_M23_Subst3_pi2K, B0_M012, B0_M013_Subst3_pi2K, cosThetaL, B0_HOP_M, B0_FDCHI2_OWNPV, JPs_M, B0_PV_M, wNB;

  sample_tree->SetBranchAddress("K_L0Calo_HCAL_region", &K_L0Calo_HCAL_region);
  sample_tree->SetBranchAddress("Pi_L0Calo_HCAL_region", &Pi_L0Calo_HCAL_region);
  sample_tree->SetBranchAddress("E1_L0Calo_ECAL_region", &E1_L0Calo_ECAL_region);
  sample_tree->SetBranchAddress("E2_L0Calo_ECAL_region", &E2_L0Calo_ECAL_region);
  sample_tree->SetBranchAddress("E1_L0ElectronDecision_TOS", &E1_L0ElectronDecision_TOS);
  sample_tree->SetBranchAddress("E2_L0ElectronDecision_TOS", &E2_L0ElectronDecision_TOS);
  sample_tree->SetBranchAddress("K_L0HadronDecision_TOS", &K_L0HadronDecision_TOS);
  sample_tree->SetBranchAddress("Pi_L0HadronDecision_TOS", &Pi_L0HadronDecision_TOS);
  sample_tree->SetBranchAddress("B0_L0Global_TIS", &B0_L0Global_TIS);
  sample_tree->SetBranchAddress("B0_Hlt1TrackAllL0Decision_TOS", &B0_Hlt1TrackAllL0Decision_TOS);
  sample_tree->SetBranchAddress("B0_Hlt2Topo2BodyBBDTDecision_TOS", &B0_Hlt2Topo2BodyBBDTDecision_TOS);
  sample_tree->SetBranchAddress("B0_Hlt2Topo3BodyBBDTDecision_TOS", &B0_Hlt2Topo3BodyBBDTDecision_TOS);
  sample_tree->SetBranchAddress("B0_Hlt2Topo4BodyBBDTDecision_TOS", &B0_Hlt2Topo4BodyBBDTDecision_TOS);
  sample_tree->SetBranchAddress("B0_Hlt2TopoE2BodyBBDTDecision_TOS", &B0_Hlt2TopoE2BodyBBDTDecision_TOS);
  sample_tree->SetBranchAddress("B0_Hlt2TopoE3BodyBBDTDecision_TOS", &B0_Hlt2TopoE3BodyBBDTDecision_TOS);
  sample_tree->SetBranchAddress("B0_Hlt2TopoE4BodyBBDTDecision_TOS", &B0_Hlt2TopoE4BodyBBDTDecision_TOS);
  sample_tree->SetBranchAddress("K_hasRich", &K_hasRich);
  sample_tree->SetBranchAddress("Pi_hasRich", &Pi_hasRich);
  sample_tree->SetBranchAddress("E1_hasRich", &E1_hasRich);
  sample_tree->SetBranchAddress("E2_hasRich", &E2_hasRich);
  sample_tree->SetBranchAddress("E1_hasCalo", &E1_hasCalo);
  sample_tree->SetBranchAddress("E2_hasCalo", &E2_hasCalo);
  sample_tree->SetBranchAddress("K_PT", &K_PT);
  sample_tree->SetBranchAddress("Pi_PT", &Pi_PT);
  sample_tree->SetBranchAddress("E1_PT", &E1_PT);
  sample_tree->SetBranchAddress("E2_PT", &E2_PT);
  sample_tree->SetBranchAddress("K_TRACK_CHI2NDOF", &K_TRACK_CHI2NDOF);
  sample_tree->SetBranchAddress("Pi_TRACK_CHI2NDOF", &Pi_TRACK_CHI2NDOF);
  sample_tree->SetBranchAddress("E1_TRACK_CHI2NDOF", &E1_TRACK_CHI2NDOF);
  sample_tree->SetBranchAddress("E2_TRACK_CHI2NDOF", &E2_TRACK_CHI2NDOF);
  sample_tree->SetBranchAddress("K_TRACK_GhostProb", &K_TRACK_GhostProb);
  sample_tree->SetBranchAddress("Pi_TRACK_GhostProb", &Pi_TRACK_GhostProb);
  sample_tree->SetBranchAddress("E1_TRACK_GhostProb", &E1_TRACK_GhostProb);
  sample_tree->SetBranchAddress("E2_TRACK_GhostProb", &E2_TRACK_GhostProb);
  sample_tree->SetBranchAddress("E1_L0Calo_ECAL_xProjection", &E1_L0Calo_ECAL_xProjection);
  sample_tree->SetBranchAddress("E1_L0Calo_ECAL_yProjection", &E1_L0Calo_ECAL_yProjection);
  sample_tree->SetBranchAddress("E2_L0Calo_ECAL_xProjection", &E2_L0Calo_ECAL_xProjection);
  sample_tree->SetBranchAddress("E2_L0Calo_ECAL_yProjection", &E2_L0Calo_ECAL_yProjection);
  sample_tree->SetBranchAddress("Kst_M", &Kst_M);
  sample_tree->SetBranchAddress("B0_M23_Subst3_pi2K", &B0_M23_Subst3_pi2K);
  sample_tree->SetBranchAddress("B0_M012", &B0_M012);
  sample_tree->SetBranchAddress("B0_M013_Subst3_pi2K", &B0_M013_Subst3_pi2K);
  sample_tree->SetBranchAddress("cosThetaL", &cosThetaL);

  // Jps specific
  Double_t B0_PV_JPs_M;
  Bool_t isB0_PV_JPs_M = true;
  if ( sample_isJPs ) sample_tree->SetBranchAddress("B0_PV_JPs_M", &B0_PV_JPs_M);

  // Q2 specific
  sample_tree->SetBranchAddress("B0_HOP_M", &B0_HOP_M);
  sample_tree->SetBranchAddress("B0_FDCHI2_OWNPV", &B0_FDCHI2_OWNPV);
  sample_tree->SetBranchAddress("JPs_M", &JPs_M);
  sample_tree->SetBranchAddress("B0_PV_M", &B0_PV_M);
  sample_tree->SetBranchAddress("wNB", &wNB);

  // Trigger specific
  Bool_t isL0L = true;
  Bool_t isL0H = true;
  Bool_t isL0I = true;

  // MC specific
  Int_t B0_BKGCAT;
  Bool_t isBKGCAT = true;
  if ( sample_isMC ) sample_tree->SetBranchAddress("B0_BKGCAT", &B0_BKGCAT);

  // Data specific
  Bool_t isPID = true;
  Double_t E1_PIDe;
  Double_t E2_PIDe;
  Double_t E1_MC12TuneV3_ProbNNe;
  Double_t E2_MC12TuneV3_ProbNNe;
  Double_t Pi_MC12TuneV2_ProbNNpi;
  Double_t Pi_MC12TuneV2_ProbNNk;
  Double_t Pi_MC12TuneV2_ProbNNp;
  Double_t K_PIDK;
  Double_t K_MC12TuneV2_ProbNNk;
  Double_t K_MC12TuneV2_ProbNNp;
  if ( !sample_isMC )
  {
    sample_tree->SetBranchAddress("E1_PIDe", &E1_PIDe);
    sample_tree->SetBranchAddress("E2_PIDe", &E2_PIDe);
    sample_tree->SetBranchAddress("E1_MC12TuneV3_ProbNNe", &E1_MC12TuneV3_ProbNNe);
    sample_tree->SetBranchAddress("E2_MC12TuneV3_ProbNNe", &E2_MC12TuneV3_ProbNNe);
    sample_tree->SetBranchAddress("Pi_MC12TuneV2_ProbNNpi", &Pi_MC12TuneV2_ProbNNpi);
    sample_tree->SetBranchAddress("Pi_MC12TuneV2_ProbNNk", &Pi_MC12TuneV2_ProbNNk);
    sample_tree->SetBranchAddress("Pi_MC12TuneV2_ProbNNp", &Pi_MC12TuneV2_ProbNNp);
    sample_tree->SetBranchAddress("K_PIDK", &K_PIDK);
    sample_tree->SetBranchAddress("K_MC12TuneV2_ProbNNk", &K_MC12TuneV2_ProbNNk);
    sample_tree->SetBranchAddress("K_MC12TuneV2_ProbNNp", &K_MC12TuneV2_ProbNNp);
  }

  //============================================================================
  // Fill new tree
  //============================================================================
  // Fill tree and write into file

  int nentries = (int)sample_tree->GetEntries();

  for(int i=0; i<nentries; i++)
  {
    sample_tree->GetEntry(i);

    //==========================================================================
    // Construct cuts
    //==========================================================================

    // Common to all samples
    Bool_t isL0 = (E1_L0ElectronDecision_TOS || E2_L0ElectronDecision_TOS) || (K_L0HadronDecision_TOS || Pi_L0HadronDecision_TOS) || B0_L0Global_TIS;
    Bool_t isHlt = B0_Hlt1TrackAllL0Decision_TOS && ((B0_Hlt2Topo2BodyBBDTDecision_TOS || B0_Hlt2Topo3BodyBBDTDecision_TOS || B0_Hlt2Topo4BodyBBDTDecision_TOS)||(B0_Hlt2TopoE2BodyBBDTDecision_TOS || B0_Hlt2TopoE3BodyBBDTDecision_TOS || B0_Hlt2TopoE4BodyBBDTDecision_TOS));
    Bool_t isCaloRegion = TMath::Min(K_L0Calo_HCAL_region, Pi_L0Calo_HCAL_region) >= 0 && TMath::Min(E1_L0Calo_ECAL_region, E2_L0Calo_ECAL_region) >= 0;
    Bool_t isCaloRich = ( K_hasRich && Pi_hasRich && E1_hasRich && E2_hasRich && E1_hasCalo && E2_hasCalo );
    Bool_t isPt = K_PT > 250 && Pi_PT > 250 && TMath::Min(E1_PT, E2_PT) > 500;
    Bool_t isTrack = K_TRACK_CHI2NDOF < 3 && Pi_TRACK_CHI2NDOF < 3 && E1_TRACK_CHI2NDOF < 3 && E2_TRACK_CHI2NDOF < 3;
    Bool_t isNotGhost = K_TRACK_GhostProb < 0.4 && Pi_TRACK_GhostProb < 0.4 && E1_TRACK_GhostProb < 0.4 && E2_TRACK_GhostProb < 0.4;
    Bool_t isCaloProj = !((TMath::Abs(E1_L0Calo_ECAL_xProjection) < 363.6 && TMath::Abs(E1_L0Calo_ECAL_yProjection) < 282.6) || (TMath::Abs(E2_L0Calo_ECAL_xProjection) < 363.6 && TMath::Abs(E2_L0Calo_ECAL_yProjection) < 282.6));
    Bool_t isMass = TMath::Abs(Kst_M - 895.94) < 100 && B0_M23_Subst3_pi2K > 1040 && TMath::Max(B0_M012, B0_M013_Subst3_pi2K) < 5100;
    Bool_t isCosThetaL = TMath::Abs(cosThetaL) < 0.8;

    // Q2 specific
    Bool_t isHOP = B0_HOP_M > myQ2Bin->GetHOP() + myQ2Bin->GetHOPlog() * TMath::Log(B0_FDCHI2_OWNPV);
    Bool_t isJPs_M = ( TMath::Power(JPs_M/1000.,2) < myQ2Bin->GetQ2Max() ) && (TMath::Power(JPs_M/1000.,2) > myQ2Bin->GetQ2Min() ) ;
    Bool_t isB0_PV_M = ( B0_PV_M > myQ2Bin->GetB0_PV_M_min() ) && ( B0_PV_M < myQ2Bin->GetB0_PV_M_max() );
    Bool_t iswNB = wNB > myQ2Bin->GetwNB();

    // Trigger specific
    if ( triggerCat == "L0L" )
    {
      isL0L = E1_L0ElectronDecision_TOS || E2_L0ElectronDecision_TOS;
    }
    else if ( triggerCat == "L0H" )
    {
      isL0H = K_L0HadronDecision_TOS || Pi_L0HadronDecision_TOS;
    }
    else if ( triggerCat == "L0I" )
    {
      isL0I = B0_L0Global_TIS;
    }

    // MC specific
    if ( sample_isMC )
    {
      isBKGCAT = B0_BKGCAT == 0 || B0_BKGCAT == 10 || B0_BKGCAT == 50;
    }

    // Data specific
    if ( !(sample_isMC) )
    {
      isPID = ( TMath::Min(E1_PIDe, E2_PIDe) > 0 ) && (TMath::Min(E1_MC12TuneV3_ProbNNe, E2_MC12TuneV3_ProbNNe) > 0.2) && (Pi_MC12TuneV2_ProbNNpi * (1 - Pi_MC12TuneV2_ProbNNk) * (1 - Pi_MC12TuneV2_ProbNNp) > 0.1) && K_PIDK > -5 && (K_MC12TuneV2_ProbNNk * (1 - K_MC12TuneV2_ProbNNp) > 0.05 );
    }

    // JPs specific
    if ( sample_isJPs )
    {
      isCosThetaL = true;
      isHOP = true;
      isB0_PV_M = true;
      isB0_PV_JPs_M = ( B0_PV_JPs_M > myQ2Bin->GetB0_PV_M_min() ) && ( B0_PV_JPs_M < myQ2Bin->GetB0_PV_M_max() );
    }

    // Apply cuts
    if( isL0L && isL0H && isL0I && isL0 && isHlt && isCaloRegion && isCaloRich && isPt && isTrack && isNotGhost && isCaloProj && isMass && isCosThetaL && isJPs_M && isHOP && isB0_PV_M && isB0_PV_JPs_M && iswNB && isBKGCAT && isPID )
    {
      newTree->Fill();
    }
  }

  newFile->Write("",TObject::kOverwrite);
  std::cout << "Tree " << newTreeName << " with number of entries = " << newTree->GetEntries() << " written in file " << newFile << std::endl << std::endl ;
}

//******************************************************************************

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

//******************************************************************************

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

//******************************************************************************


void Sample::AddConversionBranches()
{
  // Check if tree is empty
  if ( sample_tree->GetEntries() == 0 ) return;
  sample_file->ReOpen("update");

  //============================================================================
  // Init new tree
  //============================================================================

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
  Double_t E1_PHI = -1000;
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

  // MC specific
  if ( sample_isMC )
  {
    sample_tree->SetBranchAddress("B0_TRUEORIGINVERTEX_X", &B0_TRUEORIGINVERTEX_X);
    sample_tree->SetBranchAddress("B0_TRUEORIGINVERTEX_Y", &B0_TRUEORIGINVERTEX_Y);
    sample_tree->SetBranchAddress("B0_TRUEORIGINVERTEX_Z", &B0_TRUEORIGINVERTEX_Z);

    sample_tree->SetBranchAddress("Kst_TRUEORIGINVERTEX_X", &Kst_TRUEORIGINVERTEX_X);
    sample_tree->SetBranchAddress("Kst_TRUEORIGINVERTEX_Y", &Kst_TRUEORIGINVERTEX_Y);
    sample_tree->SetBranchAddress("Kst_TRUEORIGINVERTEX_Z", &Kst_TRUEORIGINVERTEX_Z);

    sample_tree->SetBranchAddress("Kst_TRUEENDVERTEX_X", &Kst_TRUEENDVERTEX_X);
    sample_tree->SetBranchAddress("Kst_TRUEENDVERTEX_Y", &Kst_TRUEENDVERTEX_Y);
    sample_tree->SetBranchAddress("Kst_TRUEENDVERTEX_Z", &Kst_TRUEENDVERTEX_Z);

    sample_tree->SetBranchAddress("E1_TRUEORIGINVERTEX_X", &E1_TRUEORIGINVERTEX_X);
    sample_tree->SetBranchAddress("E1_TRUEORIGINVERTEX_Y", &E1_TRUEORIGINVERTEX_Y);
    sample_tree->SetBranchAddress("E1_TRUEORIGINVERTEX_Z", &E1_TRUEORIGINVERTEX_Z);

    sample_tree->SetBranchAddress("E2_TRUEORIGINVERTEX_X", &E2_TRUEORIGINVERTEX_X);
    sample_tree->SetBranchAddress("E2_TRUEORIGINVERTEX_Y", &E2_TRUEORIGINVERTEX_Y);
    sample_tree->SetBranchAddress("E2_TRUEORIGINVERTEX_Z", &E2_TRUEORIGINVERTEX_Z);

    sample_tree->SetBranchAddress("E1_TRUEP_X", &E1_TRUEP_X);
    sample_tree->SetBranchAddress("E1_TRUEP_Y", &E1_TRUEP_Y);
    sample_tree->SetBranchAddress("E1_TRUEP_Z", &E1_TRUEP_Z);

    sample_tree->SetBranchAddress("E2_TRUEP_X", &E2_TRUEP_X);
    sample_tree->SetBranchAddress("E2_TRUEP_Y", &E2_TRUEP_Y);
    sample_tree->SetBranchAddress("E2_TRUEP_Z", &E2_TRUEP_Z);

    sample_tree->SetBranchAddress("JPs_TRUEP_X", &JPs_TRUEP_X);
    sample_tree->SetBranchAddress("JPs_TRUEP_Y", &JPs_TRUEP_Y);
    sample_tree->SetBranchAddress("JPs_TRUEP_Z", &JPs_TRUEP_Z);

    sample_tree->SetBranchAddress("JPs_TRUEORIGINVERTEX_X", &JPs_TRUEORIGINVERTEX_X);
    sample_tree->SetBranchAddress("JPs_TRUEORIGINVERTEX_Y", &JPs_TRUEORIGINVERTEX_Y);
    sample_tree->SetBranchAddress("JPs_TRUEORIGINVERTEX_Z", &JPs_TRUEORIGINVERTEX_Z);
  }

  sample_tree->SetBranchAddress("B0_OWNPV_X", &B0_OWNPV_X);
  sample_tree->SetBranchAddress("B0_OWNPV_Y", &B0_OWNPV_Y);
  sample_tree->SetBranchAddress("B0_OWNPV_Z", &B0_OWNPV_Z);

  sample_tree->SetBranchAddress("Kst_ENDVERTEX_X", &Kst_ENDVERTEX_X);
  sample_tree->SetBranchAddress("Kst_ENDVERTEX_Y", &Kst_ENDVERTEX_Y);
  sample_tree->SetBranchAddress("Kst_ENDVERTEX_Z", &Kst_ENDVERTEX_Z);

  sample_tree->SetBranchAddress("B0_ENDVERTEX_X" ,&B0_ENDVERTEX_X);
  sample_tree->SetBranchAddress("B0_ENDVERTEX_Y" ,&B0_ENDVERTEX_Y);
  sample_tree->SetBranchAddress("B0_ENDVERTEX_Z" ,&B0_ENDVERTEX_Z);

  sample_tree->SetBranchAddress("E1_PX", &E1_PX);
  sample_tree->SetBranchAddress("E1_PY", &E1_PY);
  sample_tree->SetBranchAddress("E1_PZ", &E1_PZ);
  sample_tree->SetBranchAddress("E1_P", &E1_P);
  sample_tree->SetBranchAddress("E1_PT", &E1_PT);

  sample_tree->SetBranchAddress("E2_P", &E2_P);
  sample_tree->SetBranchAddress("E2_PT", &E2_PT);

  sample_tree->SetBranchAddress("E2_PX", &E2_PX);
  sample_tree->SetBranchAddress("E2_PY", &E2_PY);
  sample_tree->SetBranchAddress("E2_PZ", &E2_PZ);

  sample_tree->SetBranchAddress("JPs_PX", &JPs_PX);
  sample_tree->SetBranchAddress("JPs_PY", &JPs_PY);
  sample_tree->SetBranchAddress("JPs_PZ", &JPs_PZ);
  sample_tree->SetBranchAddress("JPs_P", &JPs_P);
  sample_tree->SetBranchAddress("JPs_PT", &JPs_PT);

  sample_tree->SetBranchAddress("K_P", &K_P);
  sample_tree->SetBranchAddress("K_PT", &K_PT);
  sample_tree->SetBranchAddress("K_PX", &K_PX);
  sample_tree->SetBranchAddress("K_PY", &K_PY);
  sample_tree->SetBranchAddress("K_PZ", &K_PZ);

  sample_tree->SetBranchAddress("E1_TRACK_FirstMeasurementX", &E1_TRACK_FirstMeasurementX);
  sample_tree->SetBranchAddress("E1_TRACK_FirstMeasurementY", &E1_TRACK_FirstMeasurementY);
  sample_tree->SetBranchAddress("E2_TRACK_FirstMeasurementX", &E2_TRACK_FirstMeasurementX);
  sample_tree->SetBranchAddress("E2_TRACK_FirstMeasurementY", &E2_TRACK_FirstMeasurementY);

  // MC specific
  TBranch *b_E1_TRUE_EXP_TRACK_FirstMeasurementZ(0);
  TBranch *b_E2_TRUE_EXP_TRACK_FirstMeasurementZ(0);
  TBranch *b_E1_TRUE_EXP_TRACK_FirstMeasurementY(0);
  TBranch *b_E2_TRUE_EXP_TRACK_FirstMeasurementY(0);
  TBranch *b_E1_TRUE_EXP_TRACK_FirstMeasurementX(0);
  TBranch *b_E2_TRUE_EXP_TRACK_FirstMeasurementX(0);
  TBranch *b_G_CONV_IN_STATIONS(0);
  TBranch *b_G_CONV_BEFORE(0);

  if ( sample_isMC )
  {
    b_E1_TRUE_EXP_TRACK_FirstMeasurementZ =
      sample_tree->Branch("E1_TRUE_EXP_TRACK_FirstMeasurementZ",
      &E1_TRUE_EXP_TRACK_FirstMeasurementZ);
    b_E2_TRUE_EXP_TRACK_FirstMeasurementZ =
      sample_tree->Branch("E2_TRUE_EXP_TRACK_FirstMeasurementZ",
      &E2_TRUE_EXP_TRACK_FirstMeasurementZ);

    b_E1_TRUE_EXP_TRACK_FirstMeasurementY =
      sample_tree->Branch("E1_TRUE_EXP_TRACK_FirstMeasurementY",
      &E1_TRUE_EXP_TRACK_FirstMeasurementY);
    b_E2_TRUE_EXP_TRACK_FirstMeasurementY =
      sample_tree->Branch("E2_TRUE_EXP_TRACK_FirstMeasurementY",
      &E2_TRUE_EXP_TRACK_FirstMeasurementY);

    b_E1_TRUE_EXP_TRACK_FirstMeasurementX = sample_tree->Branch("E1_TRUE_EXP_TRACK_FirstMeasurementX", &E1_TRUE_EXP_TRACK_FirstMeasurementX);
    b_E2_TRUE_EXP_TRACK_FirstMeasurementX = sample_tree->Branch("E2_TRUE_EXP_TRACK_FirstMeasurementX", &E2_TRUE_EXP_TRACK_FirstMeasurementX);

    b_G_CONV_IN_STATIONS = sample_tree->Branch("G_CONV_IN_STATIONS", &G_CONV_IN_STATIONS);

    b_G_CONV_BEFORE = sample_tree->Branch("G_CONV_BEFORE", &G_CONV_BEFORE);
  }

  TBranch *b_E1_EXP_TRACK_FirstMeasurementZ =
    sample_tree->Branch("E1_EXP_TRACK_FirstMeasurementZ",
    &E1_EXP_TRACK_FirstMeasurementZ);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementZ =
    sample_tree->Branch("E2_EXP_TRACK_FirstMeasurementZ",
    &E2_EXP_TRACK_FirstMeasurementZ);

  TBranch *b_E1_EXP_TRACK_FirstMeasurementY =
    sample_tree->Branch("E1_EXP_TRACK_FirstMeasurementY",
    &E1_EXP_TRACK_FirstMeasurementY);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementY =
    sample_tree->Branch("E2_EXP_TRACK_FirstMeasurementY",
    &E2_EXP_TRACK_FirstMeasurementY);

  TBranch *b_E1_EXP_TRACK_FirstMeasurementX = sample_tree->Branch("E1_EXP_TRACK_FirstMeasurementX", &E1_EXP_TRACK_FirstMeasurementX);
  TBranch *b_E2_EXP_TRACK_FirstMeasurementX = sample_tree->Branch("E2_EXP_TRACK_FirstMeasurementX", &E2_EXP_TRACK_FirstMeasurementX);

  TBranch *b_E1_XY_FROM_BEAM = sample_tree->Branch("E1_XY_FROM_BEAM", &E1_XY_FROM_BEAM);
  TBranch *b_E2_XY_FROM_BEAM = sample_tree->Branch("E2_XY_FROM_BEAM", &E2_XY_FROM_BEAM);

  TBranch *b_E1_PHI = sample_tree->Branch("E1_PHI", &E1_PHI);
  TBranch *b_E2_PHI = sample_tree->Branch("E2_PHI", &E2_PHI);
  TBranch *b_JPs_PHI = sample_tree->Branch("JPs_PHI", &JPs_PHI);
  TBranch *b_K_PHI = sample_tree->Branch("K_PHI", &K_PHI);

  TBranch *b_K_THETA_K = sample_tree->Branch("K_THETA_K", &K_THETA_K);
  TBranch *b_E1_THETA_K = sample_tree->Branch("E1_THETA_K", &E1_THETA_K);
  TBranch *b_E2_THETA_K = sample_tree->Branch("E2_THETA_K", &E2_THETA_K);
  TBranch *b_JPs_THETA_K = sample_tree->Branch("JPs_THETA_K", &JPs_THETA_K);

  TBranch *b_E1_First_PHI = sample_tree->Branch("E1_First_PHI", &E1_First_PHI);
  TBranch *b_E2_First_PHI = sample_tree->Branch("E2_First_PHI", &E2_First_PHI);

  //============================================================================
  // Create LHCb VELO and LHC beam
  //============================================================================

  // Create LHC beam

  // MC scpecific
  Beam myBeamTRUE;

  if ( sample_isMC )
  {
    sample_tree->Draw("B0_TRUEORIGINVERTEX_X>>hTRUE_beamX");
    TH1F *hTRUE_beamX = (TH1F*)gDirectory->Get("hTRUE_beamX");
    myBeamTRUE.SetX( hTRUE_beamX->GetMean() );

    sample_tree->Draw("B0_TRUEORIGINVERTEX_Y>>hTRUE_beamY");
    TH1F *hTRUE_beamY = (TH1F*)gDirectory->Get("hTRUE_beamY");
    myBeamTRUE.SetY( hTRUE_beamY->GetMean() );
  }

  Beam myBeam;

  sample_tree->Draw("B0_OWNPV_X>>h_beamX");
  TH1F *h_beamX = (TH1F*)gDirectory->Get("h_beamX");
  myBeam.SetX( h_beamX->GetMean() );

  sample_tree->Draw("B0_OWNPV_Y>>h_beamY");
  TH1F *h_beamY = (TH1F*)gDirectory->Get("h_beamY");
  myBeam.SetY( h_beamY->GetMean() );

  cout << "LHC beam has been created" << endl;

  // Create LHCb VELO
  VELO myVELO;
  cout << "LHCb VELO has been created" << endl;
  //myVELO.PrintStations();

  //============================================================================
  // Fill and write tree
  //============================================================================
  int nentries = (int)sample_tree->GetEntries();

  for(int i=0; i<nentries; i++)
  {
    sample_tree->GetEntry(i);

    // MC specific
    if ( sample_isMC )
    {
      // FirstMeasurement
      TVector3 E1_TRUE_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E1_TRUEP_X,E1_TRUEP_Y, E1_TRUEP_Z, E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y, E1_TRUEORIGINVERTEX_Z, myVELO, myBeamTRUE);
      TVector3 E2_TRUE_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E2_TRUEP_X,E2_TRUEP_Y, E2_TRUEP_Z, E2_TRUEORIGINVERTEX_X, E2_TRUEORIGINVERTEX_Y, E2_TRUEORIGINVERTEX_Z, myVELO, myBeam);

      E1_TRUE_EXP_TRACK_FirstMeasurementZ = E1_TRUE_EXP_TRACK_FirstMeasurement.Z();
      E2_TRUE_EXP_TRACK_FirstMeasurementZ = E2_TRUE_EXP_TRACK_FirstMeasurement.Z();
      E1_TRUE_EXP_TRACK_FirstMeasurementY = E1_TRUE_EXP_TRACK_FirstMeasurement.Y();
      E2_TRUE_EXP_TRACK_FirstMeasurementY = E2_TRUE_EXP_TRACK_FirstMeasurement.Y();
      E1_TRUE_EXP_TRACK_FirstMeasurementX = E1_TRUE_EXP_TRACK_FirstMeasurement.X();
      E2_TRUE_EXP_TRACK_FirstMeasurementX = E2_TRUE_EXP_TRACK_FirstMeasurement.X();

      // Converts before station
      TVector3 JPs_TRUE_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( JPs_TRUEP_X, JPs_TRUEP_Y, JPs_TRUEP_Z, JPs_TRUEORIGINVERTEX_X, JPs_TRUEORIGINVERTEX_Y, JPs_TRUEORIGINVERTEX_Z, myVELO, myBeamTRUE );

      G_CONV_BEFORE = ConvertsBeforeStation( JPs_TRUE_EXP_TRACK_FirstMeasurement, E1_TRUEORIGINVERTEX_Z, myVELO );

      // G converted in stations
      G_CONV_IN_STATIONS = myVELO.IsInStations(E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y, E1_TRUEORIGINVERTEX_Z, myBeamTRUE);
    }

    // FirstMeasurement
    TVector3 E1_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E1_PX,E1_PY, E1_PZ, Kst_ENDVERTEX_X, Kst_ENDVERTEX_Y, Kst_ENDVERTEX_Z, myVELO, myBeam);
    TVector3 E2_EXP_TRACK_FirstMeasurement = get_exp_firstMeasurement( E2_PX,E2_PY, E2_PZ, Kst_ENDVERTEX_X, Kst_ENDVERTEX_Y, Kst_ENDVERTEX_Z, myVELO, myBeam);

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

    // MC specific
    if ( sample_isMC )
    {
      b_E1_TRUE_EXP_TRACK_FirstMeasurementZ->Fill();
      b_E2_TRUE_EXP_TRACK_FirstMeasurementZ->Fill();
      b_E1_TRUE_EXP_TRACK_FirstMeasurementY->Fill();
      b_E2_TRUE_EXP_TRACK_FirstMeasurementY->Fill();
      b_E1_TRUE_EXP_TRACK_FirstMeasurementX->Fill();
      b_E2_TRUE_EXP_TRACK_FirstMeasurementX->Fill();
      b_G_CONV_IN_STATIONS->Fill();
      b_G_CONV_BEFORE->Fill();

    }

    b_E1_EXP_TRACK_FirstMeasurementZ->Fill();
    b_E2_EXP_TRACK_FirstMeasurementZ->Fill();
    b_E1_EXP_TRACK_FirstMeasurementY->Fill();
    b_E2_EXP_TRACK_FirstMeasurementY->Fill();
    b_E1_EXP_TRACK_FirstMeasurementX->Fill();
    b_E2_EXP_TRACK_FirstMeasurementX->Fill();
    b_E1_XY_FROM_BEAM->Fill();
    b_E2_XY_FROM_BEAM->Fill();
    b_E1_PHI->Fill();
    b_E2_PHI->Fill();
    b_JPs_PHI->Fill();
    b_K_PHI->Fill();
    b_K_THETA_K->Fill();
    b_E1_First_PHI->Fill();
    b_E2_First_PHI->Fill();
    b_E1_THETA_K->Fill();
    b_E2_THETA_K->Fill();
    b_JPs_THETA_K->Fill();
  }

  sample_file->Write();
  std::cout << "Added conversion branches to tree " << sample_treeName << " in file " << sample_fileName << std::endl << std::endl ;

}
