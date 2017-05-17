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
  Double_t E1_TRUE_EXP_TRACK_FirstMeasurementZ,
           E1_TRUE_EXP_TRACK_FirstMeasurementY,
           E1_TRUE_EXP_TRACK_FirstMeasurementX;
  Double_t E1_TRACK_FirstMeasurementZ, E1_TRACK_FirstMeasurementY, E1_TRACK_FirstMeasurementX;
  Double_t E1_TRUEORIGINVERTEX_Z, E1_TRUEORIGINVERTEX_Y, E1_TRUEORIGINVERTEX_X;
  Double_t E1_TRUEP_X, E1_TRUEP_Y, E1_TRUEP_Z;
  Double_t JPs_TRUEORIGINVERTEX_Z;

  Double_t E2_EXP_TRACK_FirstMeasurementZ;
  Double_t E2_TRUE_EXP_TRACK_FirstMeasurementZ,
           E2_TRUE_EXP_TRACK_FirstMeasurementY,
           E2_TRUE_EXP_TRACK_FirstMeasurementX;
  Double_t E2_TRACK_FirstMeasurementZ, E2_TRACK_FirstMeasurementY, E2_TRACK_FirstMeasurementX;
  Double_t E2_TRUEORIGINVERTEX_Z, E2_TRUEORIGINVERTEX_Y, E2_TRUEORIGINVERTEX_X;
  Double_t E2_TRUEP_X, E2_TRUEP_Y, E2_TRUEP_Z;
  Bool_t G_CONV_IN_STATIONS;

  Double_t K_PHI;
  Double_t E1_PHI;
  Double_t E2_PHI;
  Double_t JPs_PHI;
  Double_t E1_First_PHI;
  Double_t E2_First_PHI;

  Double_t K_THETA_K;
  Double_t E1_THETA_K;
  Double_t E2_THETA_K;
  Double_t JPs_THETA_K;

  T->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ",
                      &E1_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRUE_EXP_TRACK_FirstMeasurementZ",
                      &E1_TRUE_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRUE_EXP_TRACK_FirstMeasurementY",
                      &E1_TRUE_EXP_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E1_TRUE_EXP_TRACK_FirstMeasurementX",
                      &E1_TRUE_EXP_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementZ",
                      &E1_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementY",
                      &E1_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementX",
                      &E1_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Z",
                      &E1_TRUEORIGINVERTEX_Z);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_Y",
                      &E1_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("E1_TRUEORIGINVERTEX_X",
                      &E1_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("JPs_TRUEORIGINVERTEX_Z",
                      &JPs_TRUEORIGINVERTEX_Z);
  T->SetBranchAddress("E1_TRUEP_X", &E1_TRUEP_X);
  T->SetBranchAddress("E1_TRUEP_Y", &E1_TRUEP_Y);
  T->SetBranchAddress("E1_TRUEP_Z", &E1_TRUEP_Z);


  T->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ",
                      &E2_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRUE_EXP_TRACK_FirstMeasurementZ",
                      &E2_TRUE_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRUE_EXP_TRACK_FirstMeasurementY",
                      &E2_TRUE_EXP_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E2_TRUE_EXP_TRACK_FirstMeasurementX",
                      &E2_TRUE_EXP_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementZ",
                      &E2_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementY",
                      &E2_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementX",
                      &E2_TRACK_FirstMeasurementX);
  T->SetBranchAddress("E2_TRUEORIGINVERTEX_Z",
                      &E2_TRUEORIGINVERTEX_Z);
  T->SetBranchAddress("E2_TRUEORIGINVERTEX_Y",
                      &E2_TRUEORIGINVERTEX_Y);
  T->SetBranchAddress("E2_TRUEORIGINVERTEX_X",
                      &E2_TRUEORIGINVERTEX_X);
  T->SetBranchAddress("E2_TRUEP_X", &E2_TRUEP_X);
  T->SetBranchAddress("E2_TRUEP_Y", &E2_TRUEP_Y);
  T->SetBranchAddress("E2_TRUEP_Z", &E2_TRUEP_Z);

  T->SetBranchAddress("G_CONV_IN_STATIONS", &G_CONV_IN_STATIONS);
  T->SetBranchAddress("K_PHI", &K_PHI);
  T->SetBranchAddress("E1_PHI", &E1_PHI);
  T->SetBranchAddress("E2_PHI", &E2_PHI);
  T->SetBranchAddress("JPs_PHI", &JPs_PHI);
  T->SetBranchAddress("E1_First_PHI", &E1_First_PHI);
  T->SetBranchAddress("E2_First_PHI", &E2_First_PHI);

  T->SetBranchAddress("K_THETA_K", &K_THETA_K);
  T->SetBranchAddress("E1_THETA_K", &E1_THETA_K);
  T->SetBranchAddress("E2_THETA_K", &E2_THETA_K);
  T->SetBranchAddress("JPs_THETA_K", &JPs_THETA_K);


  TString pathToPlots = "/exp/LHCb/fdesse/plots/";

  // Output file
  TFile *newf = new TFile(pathToPlots+output_folder+".root","RECREATE");

  //Declare histograms
  // E1
  TH1F *E1_TRUEZvsZ = new TH1F("TRUEZvsZ",
       "FirstZ_recoTRUE - FirstZ",
       50, -70, 70);
  TH1F *E1_KstEEZ_vs_KstGEEZ = new TH1F("E1_KstEEZ_vs_KstGEEZ",
       "FirstZ_reco - FirstZ",
       100, -500, 100);
  TH1F *E1_TRUEFD_Z_short = new TH1F("E1_TRUEFD_Z_short",
        "JPs_TRUEFD_Z if |(FirstZ_reco - FirstZ)| < 60",
        30, -10, 500);
  TH1F *E1_TRUEFD_Z_long = new TH1F("E1_TRUEFD_Z_long",
        "Ps_TRUEFD_Z if |(FirstZ_reco - FirstZ)| >= 60",
        30, -10, 700);
  TH2F *E1_convertion_pt = new TH2F("E1_convertion_pt",
        "E1_TRUEORIGINVERTEX_X vs E1_TRUEORIGINVERTEX_Y",
        100, -50, 50, 100, -50, 50);
  TH2F *E1_missed = new TH2F("E1_missed", "E1 missed hits",
        100, -20, 20, 100, -20, 20);
  TH2F *E1_false_hits = new TH2F("E1_false_hits", "E1 false hits",
        100, -20, 20, 100, -20, 20);

  // E2
  TH1F *E2_TRUEZvsZ = new TH1F("TRUEZvsZ",
       "FirstZ_recoTRUE - FirstZ",
       50, -70, 70);
  TH1F *E2_KstEEZ_vs_KstGEEZ = new TH1F("E2_KstEEZ_vs_KstGEEZ",
       "FirstZ_reco - FirstZ",
       100, -500, 100);
  TH1F *E2_TRUEFD_Z_short = new TH1F("E2_TRUEFD_Z_short",
        "JPs_TRUEFD_Z if |(FirstZ_reco - FirstZ)| < 60",
        30, -10, 500);
  TH1F *E2_TRUEFD_Z_long = new TH1F("E2_TRUEFD_Z_long",
        "Ps_TRUEFD_Z if |(FirstZ_reco - FirstZ)| >= 60",
        30, -10, 700);
  TH2F *E2_convertion_pt = new TH2F("E2_convertion_pt",
        "E2_TRUEORIGINVERTEX_X vs E2_TRUEORIGINVERTEX_Y",
        100, -50, 50, 100, -50, 50);
  TH2F *E2_missed = new TH2F("E2_missed", "E2 missed hits",
        100, -20, 20, 100, -20, 20);
  TH2F *E2_false_hits = new TH2F("E2_false_hits", "E2 false hits",
        100, -20, 20, 100, -20, 20);

  TH1F *E1_E2_avg = new TH1F("E1_E2_combi", "E1_E2_avg(FirstZ_reco - FirstZ)", 100, -500, 100);

  // Conversion
  TH2F *G_CONV_VELO = new TH2F("G_CONV_VELO", "Convertion in VELO stations: E1_TRUEORIGINVERTEX_X vs E1_TRUEORIGINVERTEX_Y", 100, -40, 40, 100, -40, 40);
  TH2F * G_CONV_RF = new TH2F("G_CONV_RF", "Convertion in RF shield: E1_TRUEORIGINVERTEX_X vs E1_TRUEORIGINVERTEX_Y", 100, -40, 40, 100, -40, 40);

  TH1F *E1_E2_Dist = new TH1F("E1_E2_Dist", "Distance of first hit between E1 and E2 in XY plane", 30, 0., 0.02);

  // Phi
  TH1F *K_PHI_VeryLow = new TH1F("K_PHI_VeryLow", "K_PHI {K_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *K_PHI_Low = new TH1F("K_PHI_Low", "K_PHI {0.03 < K_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *K_PHI_High = new TH1F("K_PHI_High", "K_PHI {0.1 < K_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *K_PHI_VeryHigh = new TH1F("K_PHI_VeryHigh", "K_PHI {K_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F *E1_PHI_VeryLow = new TH1F("E1_PHI_VeryLow", "E1_PHI {E1_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *E1_PHI_Low = new TH1F("E1_PHI_Low", "E1_PHI {0.03 < E1_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *E1_PHI_High = new TH1F("E1_PHI_High", "E1_PHI {0.1 < E1_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *E1_PHI_VeryHigh = new TH1F("E1_PHI_VeryHigh", "E1_PHI {E1_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F *E2_PHI_VeryLow = new TH1F("E2_PHI_VeryLow", "E2_PHI {E2_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *E2_PHI_Low = new TH1F("E2_PHI_Low", "E2_PHI {0.03 < E2_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *E2_PHI_High = new TH1F("E2_PHI_High", "E2_PHI {0.1 < E2_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *E2_PHI_VeryHigh = new TH1F("E2_PHI_VeryHigh", "E2_PHI {E2_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F *JPs_PHI_VeryLow = new TH1F("JPs_PHI_VeryLow", "JPs_PHI {JPs_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *JPs_PHI_Low = new TH1F("JPs_PHI_Low", "JPs_PHI {0.03 < JPs_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *JPs_PHI_High = new TH1F("JPs_PHI_High", "JPs_PHI {0.1 < JPs_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *JPs_PHI_VeryHigh = new TH1F("JPs_PHI_VeryHigh", "JPs_PHI {JPs_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F * E1_First_PHI_h = new TH1F("E1_FirstPHI_h", "E1_PHI of first measurement", 100, -3.5, 3.5);
  TH1F * E2_First_PHI_h = new TH1F("E2_FirstPHI_h", "E2_PHI of first measurement", 100, -3.5, 3.5);

  TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);

  for (Long64_t i=0; i<nentries; i++)
  {
    T->GetEntry(i);
    // For E1
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

      // missed and false hits
      if ( (E1_TRUE_EXP_TRACK_FirstMeasurementZ -
            E1_TRACK_FirstMeasurementZ) > 10 &&
            E1_TRUEORIGINVERTEX_Z < E1_TRACK_FirstMeasurementZ )
      {
        E1_missed->Fill(E1_TRACK_FirstMeasurementX, E1_TRACK_FirstMeasurementY);
      }

      if ( (E1_TRUE_EXP_TRACK_FirstMeasurementZ -
            E1_TRACK_FirstMeasurementZ) < -10 &&
            E1_TRUEORIGINVERTEX_Z < E1_TRACK_FirstMeasurementZ )
      {
        E1_false_hits->Fill(E1_TRUE_EXP_TRACK_FirstMeasurementX,
                            E1_TRUE_EXP_TRACK_FirstMeasurementY);
      }

      // G convertion
      if ( G_CONV_IN_STATIONS ) G_CONV_VELO->Fill( E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y );
      else G_CONV_RF->Fill( E1_TRUEORIGINVERTEX_X, E1_TRUEORIGINVERTEX_Y );
     }

     // E1 E2 distance
     TVector2 E1E2( E2_TRACK_FirstMeasurementX - E1_TRACK_FirstMeasurementX, E2_TRACK_FirstMeasurementY - E1_TRACK_FirstMeasurementY );
     if ( E1E2.Mod() < 0.02 ) E1_E2_Dist->Fill( E1E2.Mod() );

     // For E2
     // Compute flight distance Z
     Double_t E2_TRUEFD_Z = E2_TRUEORIGINVERTEX_Z - JPs_TRUEORIGINVERTEX_Z;

     if (E2_TRUE_EXP_TRACK_FirstMeasurementZ != -1000)
     {
       E2_TRUEZvsZ->Fill(E2_TRUE_EXP_TRACK_FirstMeasurementZ -
                         E2_TRACK_FirstMeasurementZ);
       E2_convertion_pt->Fill(E2_TRUEORIGINVERTEX_X, E2_TRUEORIGINVERTEX_Y);
     }


     if (E2_EXP_TRACK_FirstMeasurementZ != -1000)
     {
       // FirstZ_KstEE_reco - FirstZ
       E2_KstEEZ_vs_KstGEEZ->Fill(E2_EXP_TRACK_FirstMeasurementZ -
                         E2_TRACK_FirstMeasurementZ);

       if (abs((E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ)) < 60)
       {
         E2_TRUEFD_Z_short->Fill(E2_TRUEFD_Z);
       }
       else
       {
         E2_TRUEFD_Z_long->Fill(E2_TRUEFD_Z);
       }

       // missed and false hits
       if ( (E2_TRUE_EXP_TRACK_FirstMeasurementZ -
             E2_TRACK_FirstMeasurementZ) > 10 &&
             E2_TRUEORIGINVERTEX_Z < E2_TRACK_FirstMeasurementZ )
       {
         E2_missed->Fill(E2_TRACK_FirstMeasurementX, E2_TRACK_FirstMeasurementY);
       }

       if ( (E2_TRUE_EXP_TRACK_FirstMeasurementZ -
             E2_TRACK_FirstMeasurementZ) < -10 &&
             E2_TRUEORIGINVERTEX_Z < E2_TRACK_FirstMeasurementZ )
       {
         E2_false_hits->Fill(E2_TRUE_EXP_TRACK_FirstMeasurementX,
                             E2_TRUE_EXP_TRACK_FirstMeasurementY);
       }
      }

      // avg of E1 and E2
      if ( E1_EXP_TRACK_FirstMeasurementZ != -1000 && E2_EXP_TRACK_FirstMeasurementZ != -1000 )
      {
        E1_E2_avg->Fill( ( E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ + E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ )/2. );
      }


      // Phi
      if ( K_THETA_K < 0.03 ) K_PHI_VeryLow->Fill(K_PHI);
      else if ( K_THETA_K < 0.1 ) K_PHI_Low->Fill(K_PHI);
      else if ( K_THETA_K < 0.3 ) K_PHI_High->Fill(K_PHI);
      else K_PHI_VeryHigh->Fill(K_PHI);

      if ( E1_THETA_K < 0.03 ) E1_PHI_VeryLow->Fill(E1_PHI);
      else if ( E1_THETA_K < 0.1 ) E1_PHI_Low->Fill(E1_PHI);
      else if ( E1_THETA_K < 0.3 ) E1_PHI_High->Fill(E1_PHI);
      else E1_PHI_VeryHigh->Fill(E1_PHI);

      if ( E2_THETA_K < 0.03 ) E2_PHI_VeryLow->Fill(E2_PHI);
      else if ( E2_THETA_K < 0.1 ) E2_PHI_Low->Fill(E2_PHI);
      else if ( E2_THETA_K < 0.3 ) E2_PHI_High->Fill(E2_PHI);
      else E2_PHI_VeryHigh->Fill(E2_PHI);

      if ( JPs_THETA_K < 0.03 ) JPs_PHI_VeryLow->Fill(JPs_PHI);
      else if ( JPs_THETA_K < 0.1 ) JPs_PHI_Low->Fill(JPs_PHI);
      else if ( JPs_THETA_K < 0.3 ) JPs_PHI_High->Fill(JPs_PHI);
      else JPs_PHI_VeryHigh->Fill(JPs_PHI);

      E1_First_PHI_h->Fill( E1_First_PHI );
      E2_First_PHI_h->Fill( E2_First_PHI );
    }

  newf->Write("",TObject::kOverwrite);

  E1_TRUEZvsZ->GetXaxis()->SetTitle("FirstZ_KstGEE_recoTRUE - FirstZ");
  E1_TRUEZvsZ->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEZvsZ->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEZvsZ->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.png");

  E1_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E1_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.png");

  E1_TRUEFD_Z_short->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_short->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.png");

  E1_TRUEFD_Z_long->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_long->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.png");

  E2_TRUEZvsZ->GetXaxis()->SetTitle("FirstZ_KstGEE_recoTRUE - FirstZ");
  E2_TRUEZvsZ->GetYaxis()->SetTitle("Nb of events");
  E2_TRUEZvsZ->GetYaxis()->SetTitleOffset(1.6);
  E2_TRUEZvsZ->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_KstGEEreco_KstGEE.png");

  E2_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E2_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.png");

  E2_TRUEFD_Z_short->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E2_TRUEFD_Z_short->GetYaxis()->SetTitle("Nb of events");
  E2_TRUEFD_Z_short->GetYaxis()->SetTitleOffset(1.6);
  E2_TRUEFD_Z_short->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_short.png");

  E2_TRUEFD_Z_long->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E2_TRUEFD_Z_long->GetYaxis()->SetTitle("Nb of events");
  E2_TRUEFD_Z_long->GetYaxis()->SetTitleOffset(1.6);
  E2_TRUEFD_Z_long->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_long.png");

  E1_E2_avg->GetXaxis()->SetTitle("FirstZ_reco - FirstZ");
  E1_E2_avg->GetYaxis()->SetTitle("Nb of events");
  E1_E2_avg->GetYaxis()->SetTitleOffset(1.6);
  E1_E2_avg->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_E2_avg.png");

  K_PHI_VeryLow->GetXaxis()->SetTitle("K_PHI");
  K_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  K_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_VeryLow->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_K_PHI_VeryLow.png");

  K_PHI_Low->GetXaxis()->SetTitle("K_PHI");
  K_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  K_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_Low->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_K_PHI_Low.png");

  K_PHI_High->GetXaxis()->SetTitle("K_PHI");
  K_PHI_High->GetYaxis()->SetTitle("Nb of events");
  K_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_High->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_K_PHI_High.png");

  K_PHI_VeryHigh->GetXaxis()->SetTitle("K_PHI");
  K_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  K_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_VeryHigh->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_K_PHI_VeryHigh.png");

  E1_E2_Dist->GetXaxis()->SetTitle("E1_E2_Dist");
  E1_E2_Dist->GetYaxis()->SetTitle("Nb of events");
  E1_E2_Dist->GetYaxis()->SetTitleOffset(1.6);
  E1_E2_Dist->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_E2_Dist.png");

  // Phi

  E1_First_PHI_h->GetXaxis()->SetTitle("E1_First_PHI");
  E1_First_PHI_h->GetYaxis()->SetTitle("Nb of events");
  E1_First_PHI_h->GetYaxis()->SetTitleOffset(1.6);
  E1_First_PHI_h->Draw();
  c->SaveAs(pathToPlots+"Phi/"+output_folder+"_E1_First_PHI_h.png");

  E2_First_PHI_h->GetXaxis()->SetTitle("E2_First_PHI");
  E2_First_PHI_h->GetYaxis()->SetTitle("Nb of events");
  E2_First_PHI_h->GetYaxis()->SetTitleOffset(1.6);
  E2_First_PHI_h->Draw();
  c->SaveAs(pathToPlots+"Phi/"+output_folder+"_E2_First_PHI_h.png");

  TCanvas *cMultiple = new TCanvas("cMultiple","Phi",100,100,1400,1000);
  cMultiple->Divide(4,4);

  cMultiple->cd(1);
  K_PHI_VeryLow->GetXaxis()->SetTitle("K_PHI");
  K_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  K_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_VeryLow->Draw();

  cMultiple->cd(2);
  K_PHI_Low->GetXaxis()->SetTitle("K_PHI");
  K_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  K_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_Low->Draw();

  cMultiple->cd(3);
  K_PHI_High->GetXaxis()->SetTitle("K_PHI");
  K_PHI_High->GetYaxis()->SetTitle("Nb of events");
  K_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_High->Draw();

  cMultiple->cd(4);
  K_PHI_VeryHigh->GetXaxis()->SetTitle("K_PHI");
  K_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  K_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_VeryHigh->Draw();

  cMultiple->cd(5);
  JPs_PHI_VeryLow->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_VeryLow->Draw();

  cMultiple->cd(6);
  JPs_PHI_Low->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_Low->Draw();

  cMultiple->cd(7);
  JPs_PHI_High->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_High->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_High->Draw();

  cMultiple->cd(8);
  JPs_PHI_VeryHigh->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_VeryHigh->Draw();

  cMultiple->cd(9);
  E1_PHI_VeryLow->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_VeryLow->Draw();

  cMultiple->cd(10);
  E1_PHI_Low->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_Low->Draw();

  cMultiple->cd(11);
  E1_PHI_High->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_High->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_High->Draw();

  cMultiple->cd(12);
  E1_PHI_VeryHigh->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_VeryHigh->Draw();

  cMultiple->cd(13);
  E2_PHI_VeryLow->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_VeryLow->Draw();

  cMultiple->cd(14);
  E2_PHI_Low->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_Low->Draw();

  cMultiple->cd(15);
  E2_PHI_High->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_High->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_High->Draw();

  cMultiple->cd(16);
  E2_PHI_VeryHigh->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_VeryHigh->Draw();

  cMultiple->SaveAs(pathToPlots+"Phi/"+output_folder+"_PHI.png");

  // Square

  TCanvas *cSquare = new TCanvas("cSquare","Plots",100,100,1000,1000);
  E1_convertion_pt->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  E1_convertion_pt->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  E1_convertion_pt->GetYaxis()->SetTitleOffset(1.6);
  E1_convertion_pt->Draw("COLZ");
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_convertion_pt.png");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_convertion_pt.pdf");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_convertion_pt.C");

  E1_missed->GetXaxis()->SetTitle("E1_TRACK_FirstMeasurementX");
  E1_missed->GetYaxis()->SetTitle("E1_TRACK_FirstMeasurementY");
  E1_missed->GetYaxis()->SetTitleOffset(1.6);
  E1_missed->Draw();
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_missed.png");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_missed.pdf");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_missed.C");

  E1_false_hits->GetXaxis()->SetTitle("E1_TRUE_EXP_TRACK_FirstMeasurementX");
  E1_false_hits->GetYaxis()->SetTitle("E1_TRUE_EXP_TRACK_FirstMeasurementY");
  E1_false_hits->GetYaxis()->SetTitleOffset(1.6);
  E1_false_hits->Draw();
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_false_hits.png");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_false_hits.pdf");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_false_hits.C");

  E2_convertion_pt->GetXaxis()->SetTitle("E2_TRUEORIGINVERTEX_X");
  E2_convertion_pt->GetYaxis()->SetTitle("E2_TRUEORIGINVERTEX_Y");
  E2_convertion_pt->GetYaxis()->SetTitleOffset(1.6);
  E2_convertion_pt->Draw("COLZ");
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_convertion_pt.png");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_convertion_pt.pdf");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_convertion_pt.C");

  E2_missed->GetXaxis()->SetTitle("E2_TRACK_FirstMeasurementX");
  E2_missed->GetYaxis()->SetTitle("E2_TRACK_FirstMeasurementY");
  E2_missed->GetYaxis()->SetTitleOffset(1.6);
  E2_missed->Draw();
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_missed.png");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_missed.pdf");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_missed.C");

  E2_false_hits->GetXaxis()->SetTitle("E2_TRUE_EXP_TRACK_FirstMeasurementX");
  E2_false_hits->GetYaxis()->SetTitle("E2_TRUE_EXP_TRACK_FirstMeasurementY");
  E2_false_hits->GetYaxis()->SetTitleOffset(1.6);
  E2_false_hits->Draw();
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_false_hits.png");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_false_hits.pdf");
  //cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_false_hits.C");

  G_CONV_VELO->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  G_CONV_VELO->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  G_CONV_VELO->GetYaxis()->SetTitleOffset(1.6);
  G_CONV_VELO->Draw();
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_G_CONV_VELO.png");

  G_CONV_RF->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  G_CONV_RF->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  G_CONV_RF->GetYaxis()->SetTitleOffset(1.6);
  G_CONV_RF->Draw();
  cSquare->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_G_CONV_RF.png");


  newf->Close();
  f->Close();

}

void make_plots_data(TString input_file, TString input_tree, TString output_folder)
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
  Double_t E1_TRACK_FirstMeasurementZ, E1_TRACK_FirstMeasurementY, E1_TRACK_FirstMeasurementX;

  Double_t E2_EXP_TRACK_FirstMeasurementZ;
  Double_t E2_TRACK_FirstMeasurementZ, E2_TRACK_FirstMeasurementY, E2_TRACK_FirstMeasurementX;

  Double_t K_PHI;
  Double_t E1_PHI;
  Double_t E2_PHI;
  Double_t JPs_PHI;
  Double_t E1_First_PHI;
  Double_t E2_First_PHI;

  Double_t K_THETA_K;
  Double_t E1_THETA_K;
  Double_t E2_THETA_K;
  Double_t JPs_THETA_K;

  T->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &E1_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &E1_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementY", &E1_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementX", &E1_TRACK_FirstMeasurementX);


  T->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &E2_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &E2_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementY", &E2_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementX", &E2_TRACK_FirstMeasurementX);

  T->SetBranchAddress("K_PHI", &K_PHI);
  T->SetBranchAddress("E1_PHI", &E1_PHI);
  T->SetBranchAddress("E2_PHI", &E2_PHI);
  T->SetBranchAddress("JPs_PHI", &JPs_PHI);
  T->SetBranchAddress("E1_First_PHI", &E1_First_PHI);
  T->SetBranchAddress("E2_First_PHI", &E2_First_PHI);

  T->SetBranchAddress("K_THETA_K", &K_THETA_K);
  T->SetBranchAddress("E1_THETA_K", &E1_THETA_K);
  T->SetBranchAddress("E2_THETA_K", &E2_THETA_K);
  T->SetBranchAddress("JPs_THETA_K", &JPs_THETA_K);

  TString pathToPlots = "/exp/LHCb/fdesse/plots/";

  // Output file
  TFile *newf = new TFile(pathToPlots+output_folder+".root","RECREATE");

  //Declare histograms
  TH1F *E1_KstEEZ_vs_KstGEEZ = new TH1F("E1_KstEEZ_vs_KstGEEZ", "FirstZ_reco - FirstZ", 100, -500, 100);

  TH1F *E2_KstEEZ_vs_KstGEEZ = new TH1F("E2_KstEEZ_vs_KstGEEZ", "FirstZ_reco - FirstZ", 100, -500, 100);

  TH1F *E1_E2_avg = new TH1F("E1_E2_combi", "E1_E2_avg(FirstZ_reco - FirstZ)", 100, -500, 100);

  // Phi
  TH1F *K_PHI_VeryLow = new TH1F("K_PHI_VeryLow", "K_PHI {K_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *K_PHI_Low = new TH1F("K_PHI_Low", "K_PHI {0.03 < K_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *K_PHI_High = new TH1F("K_PHI_High", "K_PHI {0.1 < K_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *K_PHI_VeryHigh = new TH1F("K_PHI_VeryHigh", "K_PHI {K_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F *E1_PHI_VeryLow = new TH1F("E1_PHI_VeryLow", "E1_PHI {E1_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *E1_PHI_Low = new TH1F("E1_PHI_Low", "E1_PHI {0.03 < E1_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *E1_PHI_High = new TH1F("E1_PHI_High", "E1_PHI {0.1 < E1_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *E1_PHI_VeryHigh = new TH1F("E1_PHI_VeryHigh", "E1_PHI {E1_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F *E2_PHI_VeryLow = new TH1F("E2_PHI_VeryLow", "E2_PHI {E2_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *E2_PHI_Low = new TH1F("E2_PHI_Low", "E2_PHI {0.03 < E2_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *E2_PHI_High = new TH1F("E2_PHI_High", "E2_PHI {0.1 < E2_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *E2_PHI_VeryHigh = new TH1F("E2_PHI_VeryHigh", "E2_PHI {E2_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F *JPs_PHI_VeryLow = new TH1F("JPs_PHI_VeryLow", "JPs_PHI {JPs_THETA_K < 0.03}", 100, -3.5, 3.5);
  TH1F *JPs_PHI_Low = new TH1F("JPs_PHI_Low", "JPs_PHI {0.03 < JPs_THETA_K < 0.1}", 100, -3.5, 3.5);
  TH1F *JPs_PHI_High = new TH1F("JPs_PHI_High", "JPs_PHI {0.1 < JPs_THETA_K < 0.3}", 100, -3.5, 3.5);
  TH1F *JPs_PHI_VeryHigh = new TH1F("JPs_PHI_VeryHigh", "JPs_PHI {JPs_THETAK > 0.3}", 100, -3.5, 3.5);

  TH1F * E1_First_PHI_h = new TH1F("E1_FirstPHI_h", "E1_PHI of first measurement", 100, -3.5, 3.5);
  TH1F * E2_First_PHI_h = new TH1F("E2_FirstPHI_h", "E2_PHI of first measurement", 100, -3.5, 3.5);

  TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);

  for (Long64_t i=0; i<nentries; i++)
  {
    T->GetEntry(i);

    if (E1_EXP_TRACK_FirstMeasurementZ != -1000)
    {
      // FirstZ_KstEE_reco - FirstZ
      E1_KstEEZ_vs_KstGEEZ->Fill(E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ);
    }

    if (E2_EXP_TRACK_FirstMeasurementZ != -1000)
    {
      // FirstZ_KstEE_reco - FirstZ
      E2_KstEEZ_vs_KstGEEZ->Fill(E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ);
    }

    // avg of E1 and E2
    if ( E1_EXP_TRACK_FirstMeasurementZ != -1000 && E2_EXP_TRACK_FirstMeasurementZ != -1000 )
    {
      E1_E2_avg->Fill( ( E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ + E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ )/2. );
    }

    // Phi
    if ( K_THETA_K < 0.03 ) K_PHI_VeryLow->Fill(K_PHI);
    else if ( K_THETA_K < 0.1 ) K_PHI_Low->Fill(K_PHI);
    else if ( K_THETA_K < 0.3 ) K_PHI_High->Fill(K_PHI);
    else K_PHI_VeryHigh->Fill(K_PHI);

    if ( E1_THETA_K < 0.03 ) E1_PHI_VeryLow->Fill(E1_PHI);
    else if ( E1_THETA_K < 0.1 ) E1_PHI_Low->Fill(E1_PHI);
    else if ( E1_THETA_K < 0.3 ) E1_PHI_High->Fill(E1_PHI);
    else E1_PHI_VeryHigh->Fill(E1_PHI);

    if ( E2_THETA_K < 0.03 ) E2_PHI_VeryLow->Fill(E2_PHI);
    else if ( E2_THETA_K < 0.1 ) E2_PHI_Low->Fill(E2_PHI);
    else if ( E2_THETA_K < 0.3 ) E2_PHI_High->Fill(E2_PHI);
    else E2_PHI_VeryHigh->Fill(E2_PHI);

    if ( JPs_THETA_K < 0.03 ) JPs_PHI_VeryLow->Fill(JPs_PHI);
    else if ( JPs_THETA_K < 0.1 ) JPs_PHI_Low->Fill(JPs_PHI);
    else if ( JPs_THETA_K < 0.3 ) JPs_PHI_High->Fill(JPs_PHI);
    else JPs_PHI_VeryHigh->Fill(JPs_PHI);

    E1_First_PHI_h->Fill( E1_First_PHI );
    E2_First_PHI_h->Fill( E2_First_PHI );
  }

  newf->Write("",TObject::kOverwrite);

  E1_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E1_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.png");
  //c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.pdf");
  //c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.C");

  E2_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E2_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.png");
  //c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.pdf");
  //c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.C");

  E1_E2_avg->GetXaxis()->SetTitle("FirstZ_reco - FirstZ");
  E1_E2_avg->GetYaxis()->SetTitle("Nb of events");
  E1_E2_avg->GetYaxis()->SetTitleOffset(1.6);
  E1_E2_avg->Draw();
  c->SaveAs(pathToPlots+output_folder+"/"+output_folder+"_E1_E2_avg.png");

  // Phi

  E1_First_PHI_h->GetXaxis()->SetTitle("E1_First_PHI");
  E1_First_PHI_h->GetYaxis()->SetTitle("Nb of events");
  E1_First_PHI_h->GetYaxis()->SetTitleOffset(1.6);
  E1_First_PHI_h->Draw();
  c->SaveAs(pathToPlots+"Phi/"+output_folder+"_E1_First_PHI_h.png");

  E2_First_PHI_h->GetXaxis()->SetTitle("E2_First_PHI");
  E2_First_PHI_h->GetYaxis()->SetTitle("Nb of events");
  E2_First_PHI_h->GetYaxis()->SetTitleOffset(1.6);
  E2_First_PHI_h->Draw();
  c->SaveAs(pathToPlots+"Phi/"+output_folder+"_E2_First_PHI_h.png");

  TCanvas *cMultiple = new TCanvas("cMultiple","Phi",100,100,1400,1000);
  cMultiple->Divide(4,4);

  cMultiple->cd(1);
  K_PHI_VeryLow->GetXaxis()->SetTitle("K_PHI");
  K_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  K_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_VeryLow->Draw();

  cMultiple->cd(2);
  K_PHI_Low->GetXaxis()->SetTitle("K_PHI");
  K_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  K_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_Low->Draw();

  cMultiple->cd(3);
  K_PHI_High->GetXaxis()->SetTitle("K_PHI");
  K_PHI_High->GetYaxis()->SetTitle("Nb of events");
  K_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_High->Draw();

  cMultiple->cd(4);
  K_PHI_VeryHigh->GetXaxis()->SetTitle("K_PHI");
  K_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  K_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  K_PHI_VeryHigh->Draw();

  cMultiple->cd(5);
  JPs_PHI_VeryLow->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_VeryLow->Draw();

  cMultiple->cd(6);
  JPs_PHI_Low->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_Low->Draw();

  cMultiple->cd(7);
  JPs_PHI_High->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_High->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_High->Draw();

  cMultiple->cd(8);
  JPs_PHI_VeryHigh->GetXaxis()->SetTitle("JPs_PHI");
  JPs_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  JPs_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  JPs_PHI_VeryHigh->Draw();

  cMultiple->cd(9);
  E1_PHI_VeryLow->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_VeryLow->Draw();

  cMultiple->cd(10);
  E1_PHI_Low->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_Low->Draw();

  cMultiple->cd(11);
  E1_PHI_High->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_High->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_High->Draw();

  cMultiple->cd(12);
  E1_PHI_VeryHigh->GetXaxis()->SetTitle("E1_PHI");
  E1_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  E1_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  E1_PHI_VeryHigh->Draw();

  cMultiple->cd(13);
  E2_PHI_VeryLow->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_VeryLow->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_VeryLow->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_VeryLow->Draw();

  cMultiple->cd(14);
  E2_PHI_Low->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_Low->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_Low->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_Low->Draw();

  cMultiple->cd(15);
  E2_PHI_High->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_High->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_High->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_High->Draw();

  cMultiple->cd(16);
  E2_PHI_VeryHigh->GetXaxis()->SetTitle("E2_PHI");
  E2_PHI_VeryHigh->GetYaxis()->SetTitle("Nb of events");
  E2_PHI_VeryHigh->GetYaxis()->SetTitleOffset(1.6);
  E2_PHI_VeryHigh->Draw();

  cMultiple->SaveAs(pathToPlots+"Phi/"+output_folder+"_PHI.png");
}

void MergePlot( TString file1, TString plot1, TString file2, TString plot2, TString outFile )
{
  // Get histograms
  TFile *f1 = new TFile( file1, "read" );
  TFile *f2 = new TFile( file2, "read" );
  TH1F* h1 = (TH1F*) f1->Get( plot1 );
  TH1F* h2 = (TH1F*) f2->Get( plot2 );

  TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);
  h1->DrawNormalized("E");
  h2->SetLineColor(kRed);
  h2->DrawNormalized("E SAME");
  c->SaveAs(outFile);
}
