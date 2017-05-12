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
Sample::Sample(TString fileName, TString treeName, Sample::DecayType type)
{
  sample_fileName = fileName;
  sample_treeName = treeName;
  sample_file = new TFile(fileName, "read");
  sample_tree = (TTree*) sample_file->Get(treeName);
  sample_type = type;

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

TFile* Sample::GetFile()
{
  return sample_file;
}

TTree* Sample::GetTree()
{
  return sample_tree;
}

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

  // ADD FIRSTZ AND CONVERTS AND PHI ETC
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
      isBKGCAT = B0_BKGCAT == 0 || B0_BKGCAT == 10 || B0_BKGCAT == 50 || B0_BKGCAT == 60;
    }

    // Data specific
    if ( !(sample_isMC) )
    {
      isPID = ( TMath::Min(E1_PIDe, E2_PIDe) > 0 ) && (TMath::Min(E1_MC12TuneV3_ProbNNe, E2_MC12TuneV3_ProbNNe) > 0.2) && (Pi_MC12TuneV2_ProbNNpi * (1 - Pi_MC12TuneV2_ProbNNk) * (1 - Pi_MC12TuneV2_ProbNNp) > 0.1) && K_PIDK > -5 && (K_MC12TuneV2_ProbNNk * (1 - K_MC12TuneV2_ProbNNp) > 0.05 );
    }

    // JPs specific
    if ( sample_isJPs )
    {
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

  //

  newFile->Write("",TObject::kOverwrite);
  std::cout << "Tree " << newTreeName << " with number of entries = "
  << newTree->GetEntries() << " written in file " << newFile << endl << endl ;
  // newFile->Close();
}
