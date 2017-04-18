//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-16
//
// Makes efficiency S/B plots for cuts in FirstMeasurementZ
//
// Output: Plots
//
// Inputs: None
//
//==============================================================================

#include "cuts_z.h"

void cuts_z()
{

  //============================================================================
  // Open and initialize tree
  //============================================================================

  // Bd2KstEE signal
  TFile *fEE = TFile::Open("../data/MCEE_TRACKZ.root","read");
  if (fEE == 0)
  {
    printf("Error: cannot open file");
    return;
  }

  TTree *TEE = (TTree*)fEE->Get("Bd2KstEE");

  Double_t EE_E1_EXP_TRACK_FirstMeasurementZ;
  Double_t EE_E2_EXP_TRACK_FirstMeasurementZ;
  Double_t EE_E1_TRACK_FirstMeasurementZ;
  Double_t EE_E2_TRACK_FirstMeasurementZ;

  TEE->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &EE_E1_EXP_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &EE_E2_EXP_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &EE_E1_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &EE_E2_TRACK_FirstMeasurementZ);


  // Bd2KstJPsEE control channel
  TFile *fJPs = TFile::Open("../data/MCJPsEE_TRACKZ.root","read");
  if (fJPs == 0)
  {
    printf("Error: cannot open file");
    return;
  }

  TTree *TJPs = (TTree*)fJPs->Get("Bd2KstJPsEE");

  Double_t JPs_E1_EXP_TRACK_FirstMeasurementZ;
  Double_t JPs_E2_EXP_TRACK_FirstMeasurementZ;
  Double_t JPs_E1_TRACK_FirstMeasurementZ;
  Double_t JPs_E2_TRACK_FirstMeasurementZ;

  TJPs->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &JPs_E1_EXP_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &JPs_E2_EXP_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &JPs_E1_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &JPs_E2_TRACK_FirstMeasurementZ);


  // Bd2KstGEE background
  TFile *fGEE = TFile::Open("../data/MCGEE_TRACKZ.root","read");
  if (fGEE == 0)
  {
    printf("Error: cannot open file");
    return;
  }

  TTree *TGEE = (TTree*)fGEE->Get("Bd2KstGEE");

  Double_t GEE_E1_EXP_TRACK_FirstMeasurementZ;
  Double_t GEE_E2_EXP_TRACK_FirstMeasurementZ;
  Double_t GEE_E1_TRACK_FirstMeasurementZ;
  Double_t GEE_E2_TRACK_FirstMeasurementZ;

  TGEE->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &GEE_E1_EXP_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &GEE_E2_EXP_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &GEE_E1_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &GEE_E2_TRACK_FirstMeasurementZ);

  //============================================================================
  // Cuts config
  //============================================================================

  Double_t cut_min = 0;
  Double_t cut_max = -1;
  Int_t nb_loop = 1;
  Double_t cut_step = ( cut_max - cut_min ) / float( nb_loop );

  Double_t bkg_rejection;
  Double_t sig_efficiency;
  Double_t control_efficiency;

  //============================================================================
  // Loop
  //============================================================================

  Int_t sig_yield = TEE->GetEntries();
  Int_t control_yield = TJPs->GetEntries();
  Int_t bkg_yield = TGEE->GetEntries();

  TGraph2D *grEE = new TGraph2D();
  TGraph2D *grJPs = new TGraph2D();

  for (int i = 0; i < nb_loop; i++)
  {
    Double_t my_cut = cut_min - i*cut_step;
    // convert my_cut into a string
    char output [50];
    TString my_cut_str = sprintf(output, "%f", my_cut);

    TEE->Draw("E1_EXP_TRACK_FirstMeasurement>>hEE", "( E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ + E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ ) / 2 < my_cut");
    TH1F *hEE = (TH1F*)gDirectory->Get("hEE");
    TJPs->Draw("E1_EXP_TRACK_FirstMeasurement>>hJPs", "( E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ + E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ ) / 2 < my_cut");
    TH1F *hJPs = (TH1F*)gDirectory->Get("hJPs");
    TGEE->Draw("E1_EXP_TRACK_FirstMeasurement>>hGEE", "( E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ + E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ ) / 2 < my_cut");
    TH1F *hGEE = (TH1F*)gDirectory->Get("hGEE");

    // Double_t sig_efficiency = float ( hEE->GetEntries() ) / float ( sig_yield );
    // Double_t control_efficiency = float ( hJPs->GetEntries() ) / float ( control_yield );
    // Double_t bkg_rejection = float ( bkg_yield - hEE->GetEntries() ) / float ( bkg_yield );

    // grEE->SetPoint(i, my_cut, sig_efficiency, bkg_rejection );
    // grJPs->SetPoint(i, my_cut, control_efficiency, bkg_rejection );
  }

  // TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);
  //
  // grEE->SetTitle("Bkg rejection vs Sig efficiency");
  // grEE->GetXaxis()->SetTitle("cut Zdiff");
  // grEE->GetYaxis()->SetTitle("Sig efficiency");
  // grEE->GetZaxis()->SetTitle("Bkg rejection");
  // //grEE->GetYaxis()->SetTitleOffset(1.6);
  // grEE->Draw("surf1");
  // c->SaveAs("../plots/efficiency/EE_zCut_eff.png");
  //
  // grJPs->SetTitle("Bkg rejection vs Sig efficiency (JPs)");
  // grJPs->GetXaxis()->SetTitle("cut Zdiff");
  // grJPs->GetYaxis()->SetTitle("Sig efficiency");
  // grJPs->GetZaxis()->SetTitle("Bkg rejection");
  // //grJPs->GetYaxis()->SetTitleOffset(1.6);
  // grJPs->Draw("surf1");
  // c->SaveAs("../plots/efficiency/JPs_zCut_eff.png");

}
