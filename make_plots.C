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

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

//==============================================================================
// Functions
//==============================================================================

void make_plots()
{

  // Input file
  TFile *f = TFile::Open("../data/EE_TRACKZ.root","read");
  if (f == 0) {
    printf("Error: cannot open file");
    return;
  }
  TTree *T = (TTree*)f->Get("Bd2KstGEE");
  Long64_t nentries = T->GetEntries();

  Double_t E1_EXP_TRACK_FirstMeasurementZ;
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementZ;
  Double_t E1_TRACK_FirstMeasurementZ;
  Double_t E1_TRUEORIGINVERTEX_Z;
  Double_t JPs_TRUEORIGINVERTEX;

  T->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ",
                      &E1_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRUE_EXP_TRACK_FirstMeasurementZ",
                      &E1_TRUE_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementZ",
                      &E1_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Z",
                      &E1_TRUEORIGINVERTEX_Z);
  T->SetBranchAddress("JPs_TRUEORIGINVERTEX",
                      &JPs_TRUEORIGINVERTEX);

  // Output file
  TFile *newf = new TFile("../plots/plots.root","RECREATE");

  //Declare histograms
  TH1F *E1_TRUEZvsZ = new TH1F("TRUEZvsZ",
       "MC B2KstGEE: FirstZ_KstGEE_recoTRUE - FirstZ",
       10, -70, 70);
  TH1F *E1_KstEEZ_vs_KstGEEZ = new TH1F("E1_KstEEZ_vs_KstGEEZ",
       "MC B2KstGEE: FirstZ_KstEE_reco - FirstZ",
       30, -500, 100);
  TH1F *E1_TRUEFD_Z_short = new TH1F("E1_TRUEFD_Z_short",
        "MC B2KstGEE: JPs_TRUEFD_Z if |(FirstZ_KstEE_reco - FirstZ)| < 60",
        100, -10, 500);
  TH1F *E1_TRUEFD_Z_long = new TH1F("E1_TRUEFD_Z_long",
        "MC B2KstGEE: JPs_TRUEFD_Z if |(FirstZ_KstEE_reco - FirstZ)| >= 60",
        100, -10, 500);
  TH1F *E1_Is1000 = new TH1F("E1_Is1000",
        "MC B2KstGEE: FirstZ_recoTRUE if |(FirstZ_KstEE_reco - FirstZ)| >= 60 && JPs_TRUEFD_Z < 60 ",
        100, -1100, 500);

  TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);

  for (Long64_t i=0; i<nentries; i++)
  {
    T->GetEntry(i);

    // Compute flight distance Z
    Double_t E1_TRUEFD_Z = E1_TRUEORIGINVERTEX_Z - JPs_TRUEORIGINVERTEX;

    // MC B2KstGEE: FirstZ_KstGEE_recoTRUE - FirstZ
    if (E1_TRUE_EXP_TRACK_FirstMeasurementZ != -1000)
    {
      E1_TRUEZvsZ->Fill(E1_TRUE_EXP_TRACK_FirstMeasurementZ -
                        E1_TRACK_FirstMeasurementZ);
    }


    if (E1_EXP_TRACK_FirstMeasurementZ != -1000)
    {
      // MC B2KstGEE: FirstZ_KstEE_reco - FirstZ
      E1_KstEEZ_vs_KstGEEZ->Fill(E1_EXP_TRACK_FirstMeasurementZ -
                        E1_TRACK_FirstMeasurementZ);


     if (abs((E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ)) < 60)
     {
       E1_TRUEFD_Z_short->Fill(E1_TRUEFD_Z);
     }
     else
     {
       E1_TRUEFD_Z_long->Fill(E1_TRUEFD_Z);

       // E1_Is1000
       if ( E1_TRUEFD_Z < 60 )
       {
         E1_Is1000->Fill(E1_TRUE_EXP_TRACK_FirstMeasurementZ);
       }
     }
  }
}

  newf->Write("",TObject::kOverwrite);

  E1_TRUEZvsZ->GetXaxis()->SetTitle("FirstZ_KstGEE_recoTRUE - FirstZ");
  E1_TRUEZvsZ->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEZvsZ->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEZvsZ->Draw();
  c->SaveAs("../plots/MC_E1_KstGEEreco_KstGEE.png");
  c->SaveAs("../plots/MC_E1_KstGEEreco_KstGEE.pdf");
  c->SaveAs("../plots/MC_E1_KstGEEreco_KstGEE.C");

  E1_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E1_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs("../plots/MC_E1_KstEEreco_KstGEE.png");
  c->SaveAs("../plots/MC_E1_KstEEreco_KstGEE.pdf");
  c->SaveAs("../plots/MC_E1_KstEEreco_KstGEE.C");

  E1_TRUEFD_Z_short->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_short->Draw();
  c->SaveAs("../plots/MC_E1_TRUEFD_Z_short.png");
  c->SaveAs("../plots/MC_E1_TRUEFD_Z_short.pdf");
  c->SaveAs("../plots/MC_E1_TRUEFD_Z_short.C");

  E1_TRUEFD_Z_long->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_long->Draw();
  c->SaveAs("../plots/MC_E1_TRUEFD_Z_long.png");
  c->SaveAs("../plots/MC_E1_TRUEFD_Z_long.pdf");
  c->SaveAs("../plots/MC_E1_TRUEFD_Z_long.C");

  E1_Is1000->GetXaxis()->SetTitle("FirstZ_KstEE_reco");
  E1_Is1000->GetYaxis()->SetTitle("Nb of events");
  E1_Is1000->GetYaxis()->SetTitleOffset(1.6);
  E1_Is1000->Draw();
  c->SaveAs("../plots/MC_E1_Is1000.png");
  c->SaveAs("../plots/MC_E1_Is1000.pdf");
  c->SaveAs("../plots/MC_E1_Is1000.C");

  newf->Close();
  f->Close();

}
