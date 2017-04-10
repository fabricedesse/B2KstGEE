//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-07-05
//
// Makes plots for the analysis
//
// Output: Plots
//
// Inputs: None
//
//==============================================================================

#include "make_plots.h"

//==============================================================================
// Functions
//==============================================================================

void make_plots_MC(TString input_file, TString input_tree, TString output_folder)
{

  // Input file
  TFile *f = TFile::Open(input_file,"read");
  if (f == 0) {
    printf("Error: cannot open file");
    return;
  }
  TTree *T = (TTree*)f->Get(input_tree);
  Long64_t nentries = T->GetEntries();

  Double_t E1_EXP_TRACK_FirstMeasurementZ;
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementZ;
  Double_t E1_TRACK_FirstMeasurementZ;
  Double_t E1_TRUEORIGINVERTEX_Z, E1_TRUEORIGINVERTEX_Y, E1_TRUEORIGINVERTEX_X;
  Double_t JPs_TRUEORIGINVERTEX_Z;

  T->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ",
                      &E1_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRUE_EXP_TRACK_FirstMeasurementZ",
                      &E1_TRUE_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementZ",
                      &E1_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Z",
                      &E1_TRUEORIGINVERTEX_Z);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Y",
                      &E1_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_X",
                      &E1_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("JPs_TRUEORIGINVERTEX_Z",
                      &JPs_TRUEORIGINVERTEX_Z);

  // Output file
  TFile *newf = new TFile("../plots/"+output_folder+".root","RECREATE");

  //Declare histograms
  TH1F *E1_TRUEZvsZ = new TH1F("TRUEZvsZ",
       "FirstZ_KstGEE_recoTRUE - FirstZ",
       50, -70, 70);
  TH1F *E1_KstEEZ_vs_KstGEEZ = new TH1F("E1_KstEEZ_vs_KstGEEZ",
       "FirstZ_KstEE_reco - FirstZ",
       50, -500, 100);
  TH1F *E1_TRUEFD_Z_short = new TH1F("E1_TRUEFD_Z_short",
        "JPs_TRUEFD_Z if |(FirstZ_KstEE_reco - FirstZ)| < 60",
        30, -10, 500);
  TH1F *E1_TRUEFD_Z_long = new TH1F("E1_TRUEFD_Z_long",
        "Ps_TRUEFD_Z if |(FirstZ_KstEE_reco - FirstZ)| >= 60",
        30, -10, 700);
  TH2F *E1_convertion_pt = new TH2F("E1_convertion_pt",
        "E1_TRUEORIGINVERTEX_X vs E1_TRUEORIGINVERTEX_Y",
        100, -50, 50, 100, -50, 50);

  TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);

  for (Long64_t i=0; i<nentries; i++)
  {
    T->GetEntry(i);

    // Compute flight distance Z
    Double_t E1_TRUEFD_Z = E1_TRUEORIGINVERTEX_Z - JPs_TRUEORIGINVERTEX_Z;

    if (E1_TRUE_EXP_TRACK_FirstMeasurementZ != -1000)
    {
      E1_TRUEZvsZ->Fill(E1_TRUE_EXP_TRACK_FirstMeasurementZ -
                        E1_TRACK_FirstMeasurementZ);
      E1_convertion_pt->Fill(E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y);
    }


    if (E1_EXP_TRACK_FirstMeasurementZ != -1000)
    {
      // FirstZ_KstEE_reco - FirstZ
      E1_KstEEZ_vs_KstGEEZ->Fill(E1_EXP_TRACK_FirstMeasurementZ -
                        E1_TRACK_FirstMeasurementZ);

      if (abs((E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ)) < 60)
      {
        E1_TRUEFD_Z_short->Fill(E1_TRUEFD_Z);
      }
      else
      {
        E1_TRUEFD_Z_long->Fill(E1_TRUEFD_Z);
      }
     }
   }

  newf->Write("",TObject::kOverwrite);

  E1_TRUEZvsZ->GetXaxis()->SetTitle("FirstZ_KstGEE_recoTRUE - FirstZ");
  E1_TRUEZvsZ->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEZvsZ->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEZvsZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.png");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.pdf");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.C");

  E1_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E1_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.png");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.pdf");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.C");

  E1_TRUEFD_Z_short->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_short->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.png");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.pdf");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.C");

  E1_TRUEFD_Z_long->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_long->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.png");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.pdf");
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.C");

  TCanvas *cSquare = new TCanvas("cSquare","Plots",100,100,1000,1000);
  E1_convertion_pt->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  E1_convertion_pt->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  E1_convertion_pt->GetYaxis()->SetTitleOffset(1.6);
  E1_convertion_pt->Draw("COLZ");
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_convertion_pt.png");
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_convertion_pt.pdf");
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_convertion_pt.C");

  newf->Close();
  f->Close();

}
