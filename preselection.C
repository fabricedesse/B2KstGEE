#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TMath.h"
#include <iostream>

using namespace std;

void MakePreselection()
{
  Int_t K_L0Calo_HCAL_region, Pi_L0Calo_HCAL_region, E1_L0Calo_ECAL_region, E2_L0Calo_ECAL_region, B0_BKGCAT;
  Bool_t K_hasRich, Pi_hasRich, E1_hasRich, E2_hasRich, E1_hasCalo, E2_hasCalo, B0_Hlt1TrackAllL0Decision_TOS, B0_Hlt2Topo2BodyBBDTDecision_TOS, B0_Hlt2Topo3BodyBBDTDecision_TOS, B0_Hlt2Topo4BodyBBDTDecision_TOS, B0_Hlt2TopoE2BodyBBDTDecision_TOS, B0_Hlt2TopoE3BodyBBDTDecision_TOS, B0_Hlt2TopoE4BodyBBDTDecision_TOS;
  Double_t K_PT, Pi_PT, E1_PT, E2_PT, K_TRACK_CHI2NDOF, Pi_TRACK_CHI2NDOF, E1_TRACK_CHI2NDOF, E2_TRACK_CHI2NDOF, K_TRACK_GhostProb, Pi_TRACK_GhostProb, E1_TRACK_GhostProb, E2_TRACK_GhostProb, E1_L0Calo_ECAL_xProjection, E1_L0Calo_ECAL_yProjection, E2_L0Calo_ECAL_xProjection, E2_L0Calo_ECAL_yProjection, Kst_M, B0_M23_Subst3_pi2K, B0_M012, B0_M013_Subst3_pi2K, cosThetaL, B0_HOP_M, B0_FDCHI2_OWNPV, JPs_M, B0_PV_M, wNB;

  TFile *f = new TFile("../data/Raw/MC_Raw.root","read");
  TFile newFile("../data/CreateTuple/MC_EE_candidates.root","RECREATE");

  // Bd2KstGEE
  TTree *oldTree = (TTree*)f->Get("Bd2KstGEE");
  TTree *newTree = oldTree->CloneTree(0);

  oldTree->SetBranchAddress("K_L0Calo_HCAL_region", &K_L0Calo_HCAL_region);
  oldTree->SetBranchAddress("Pi_L0Calo_HCAL_region", &Pi_L0Calo_HCAL_region);
  oldTree->SetBranchAddress("E1_L0Calo_ECAL_region", &E1_L0Calo_ECAL_region);
  oldTree->SetBranchAddress("E2_L0Calo_ECAL_region", &E2_L0Calo_ECAL_region);
  oldTree->SetBranchAddress("B0_Hlt1TrackAllL0Decision_TOS", &B0_Hlt1TrackAllL0Decision_TOS);
  oldTree->SetBranchAddress("B0_Hlt2Topo2BodyBBDTDecision_TOS", &B0_Hlt2Topo2BodyBBDTDecision_TOS);
  oldTree->SetBranchAddress("B0_Hlt2Topo3BodyBBDTDecision_TOS", &B0_Hlt2Topo3BodyBBDTDecision_TOS);
  oldTree->SetBranchAddress("B0_Hlt2Topo4BodyBBDTDecision_TOS", &B0_Hlt2Topo4BodyBBDTDecision_TOS);
  oldTree->SetBranchAddress("B0_Hlt2TopoE2BodyBBDTDecision_TOS", &B0_Hlt2TopoE2BodyBBDTDecision_TOS);
  oldTree->SetBranchAddress("B0_Hlt2TopoE3BodyBBDTDecision_TOS", &B0_Hlt2TopoE3BodyBBDTDecision_TOS);
  oldTree->SetBranchAddress("B0_Hlt2TopoE4BodyBBDTDecision_TOS", &B0_Hlt2TopoE4BodyBBDTDecision_TOS);
  oldTree->SetBranchAddress("B0_BKGCAT", &B0_BKGCAT);
  oldTree->SetBranchAddress("K_hasRich", &K_hasRich);
  oldTree->SetBranchAddress("Pi_hasRich", &Pi_hasRich);
  oldTree->SetBranchAddress("E1_hasRich", &E1_hasRich);
  oldTree->SetBranchAddress("E2_hasRich", &E2_hasRich);
  oldTree->SetBranchAddress("E1_hasCalo", &E1_hasCalo);
  oldTree->SetBranchAddress("E2_hasCalo", &E2_hasCalo);
  oldTree->SetBranchAddress("K_PT", &K_PT);
  oldTree->SetBranchAddress("Pi_PT", &Pi_PT);
  oldTree->SetBranchAddress("E1_PT", &E1_PT);
  oldTree->SetBranchAddress("E2_PT", &E2_PT);
  oldTree->SetBranchAddress("K_TRACK_CHI2NDOF", &K_TRACK_CHI2NDOF);
  oldTree->SetBranchAddress("Pi_TRACK_CHI2NDOF", &Pi_TRACK_CHI2NDOF);
  oldTree->SetBranchAddress("E1_TRACK_CHI2NDOF", &E1_TRACK_CHI2NDOF);
  oldTree->SetBranchAddress("E2_TRACK_CHI2NDOF", &E2_TRACK_CHI2NDOF);
  oldTree->SetBranchAddress("K_TRACK_GhostProb", &K_TRACK_GhostProb);
  oldTree->SetBranchAddress("Pi_TRACK_GhostProb", &Pi_TRACK_GhostProb);
  oldTree->SetBranchAddress("E1_TRACK_GhostProb", &E1_TRACK_GhostProb);
  oldTree->SetBranchAddress("E2_TRACK_GhostProb", &E2_TRACK_GhostProb);
  oldTree->SetBranchAddress("E1_L0Calo_ECAL_xProjection", &E1_L0Calo_ECAL_xProjection);
  oldTree->SetBranchAddress("E1_L0Calo_ECAL_yProjection", &E1_L0Calo_ECAL_yProjection);
  oldTree->SetBranchAddress("E2_L0Calo_ECAL_xProjection", &E2_L0Calo_ECAL_xProjection);
  oldTree->SetBranchAddress("E2_L0Calo_ECAL_yProjection", &E2_L0Calo_ECAL_yProjection);
  oldTree->SetBranchAddress("Kst_M", &Kst_M);
  oldTree->SetBranchAddress("B0_M23_Subst3_pi2K", &B0_M23_Subst3_pi2K);
  oldTree->SetBranchAddress("B0_M012", &B0_M012);
  oldTree->SetBranchAddress("B0_M013_Subst3_pi2K", &B0_M013_Subst3_pi2K);
  oldTree->SetBranchAddress("cosThetaL", &cosThetaL);
  oldTree->SetBranchAddress("B0_HOP_M", &B0_HOP_M);
  oldTree->SetBranchAddress("B0_FDCHI2_OWNPV", &B0_FDCHI2_OWNPV);
  oldTree->SetBranchAddress("JPs_M", &JPs_M);
  oldTree->SetBranchAddress("B0_PV_M", &B0_PV_M);
  oldTree->SetBranchAddress("wNB", &wNB);

  int nentries = (int)oldTree->GetEntries();

  for(int i=0; i<nentries; i++)
  {
    oldTree->GetEntry(i);

    Bool_t IsBKGCAT = B0_BKGCAT == 0 || B0_BKGCAT == 10 || B0_BKGCAT == 50 || B0_BKGCAT == 60;
    Bool_t IsHlt = B0_Hlt1TrackAllL0Decision_TOS && ((B0_Hlt2Topo2BodyBBDTDecision_TOS || B0_Hlt2Topo3BodyBBDTDecision_TOS || B0_Hlt2Topo4BodyBBDTDecision_TOS)||(B0_Hlt2TopoE2BodyBBDTDecision_TOS || B0_Hlt2TopoE3BodyBBDTDecision_TOS || B0_Hlt2TopoE4BodyBBDTDecision_TOS));
    Bool_t IsCaloRegion = TMath::Min(K_L0Calo_HCAL_region, Pi_L0Calo_HCAL_region) >= 0 && TMath::Min(E1_L0Calo_ECAL_region, E2_L0Calo_ECAL_region) >= 0;
    Bool_t IsCaloRich = K_hasRich && Pi_hasRich && E1_hasRich && E2_hasRich && E1_hasCalo && E2_hasCalo;
    Bool_t IsPt = K_PT > 250 && Pi_PT > 250 && TMath::Min(E1_PT, E2_PT) > 500;
    Bool_t IsTrack = K_TRACK_CHI2NDOF < 3 && Pi_TRACK_CHI2NDOF < 3 && E1_TRACK_CHI2NDOF < 3 && E2_TRACK_CHI2NDOF < 3;
    Bool_t IsNotGhost = K_TRACK_GhostProb < 0.4 && Pi_TRACK_GhostProb < 0.4 && E1_TRACK_GhostProb < 0.4 && E2_TRACK_GhostProb < 0.4;
    Bool_t IsCaloProj = !((TMath::Abs(E1_L0Calo_ECAL_xProjection) < 363.6 && TMath::Abs(E1_L0Calo_ECAL_yProjection) < 282.6) || (TMath::Abs(E2_L0Calo_ECAL_xProjection) < 363.6 && TMath::Abs(E2_L0Calo_ECAL_yProjection) < 282.6));
    Bool_t IsMass = TMath::Abs(Kst_M - 895.94) < 100 && B0_M23_Subst3_pi2K > 1040 && TMath::Max(B0_M012, B0_M013_Subst3_pi2K) < 5100;
    Bool_t IsCosThetaL = TMath::Abs(cosThetaL) < 0.8;
    Bool_t IsHOP = B0_HOP_M > 3350 + 135 * TMath::Log(B0_FDCHI2_OWNPV);
    Bool_t IsJPs_M = TMath::Power(JPs_M/1000.,2) < TMath::Power(4./1000.,2);
    Bool_t IsB0_PV_M = B0_PV_M > 4500. && B0_PV_M < 6200.;
    Bool_t IswNB = wNB > 0.49;

    if( IsBKGCAT && IsHlt && IsCaloRegion && IsCaloRich && IsPt && IsTrack && IsNotGhost && IsCaloProj && IsJPs_M && IsMass && IsCosThetaL && IsHOP && IsB0_PV_M && IswNB )
    {
      newTree->Fill();
    }
  }
  newTree->Write();
  cout << newTree->GetEntries() << endl;
  newFile.Write();
}
