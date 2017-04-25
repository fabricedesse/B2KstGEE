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

  // Output file
  TFile *newf = new TFile("../plots/"+output_folder+".root","RECREATE");

  //Declare histograms
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

  TH2F *G_CONV_VELO = new TH2F("G_CONV_VELO", "Convertion in VELO stations: E1_TRUEORIGINVERTEX_X vs E1_TRUEORIGINVERTEX_Y", 100, -40, 40, 100, -40, 40);
  TH2F * G_CONV_RF = new TH2F("G_CONV_RF", "Convertion in RF shield: E1_TRUEORIGINVERTEX_X vs E1_TRUEORIGINVERTEX_Y", 100, -40, 40, 100, -40, 40);

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
    }

  newf->Write("",TObject::kOverwrite);

  E1_TRUEZvsZ->GetXaxis()->SetTitle("FirstZ_KstGEE_recoTRUE - FirstZ");
  E1_TRUEZvsZ->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEZvsZ->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEZvsZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.C");

  E1_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E1_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.C");

  E1_TRUEFD_Z_short->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_short->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_short->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_short.C");

  E1_TRUEFD_Z_long->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitle("Nb of events");
  E1_TRUEFD_Z_long->GetYaxis()->SetTitleOffset(1.6);
  E1_TRUEFD_Z_long->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_TRUEFD_Z_long.C");


  E2_TRUEZvsZ->GetXaxis()->SetTitle("FirstZ_KstGEE_recoTRUE - FirstZ");
  E2_TRUEZvsZ->GetYaxis()->SetTitle("Nb of events");
  E2_TRUEZvsZ->GetYaxis()->SetTitleOffset(1.6);
  E2_TRUEZvsZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstGEEreco_KstGEE.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstGEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstGEEreco_KstGEE.C");

  E2_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E2_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.C");

  E2_TRUEFD_Z_short->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E2_TRUEFD_Z_short->GetYaxis()->SetTitle("Nb of events");
  E2_TRUEFD_Z_short->GetYaxis()->SetTitleOffset(1.6);
  E2_TRUEFD_Z_short->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_short.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_short.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_short.C");

  E2_TRUEFD_Z_long->GetXaxis()->SetTitle("JPs_TRUEFD_Z");
  E2_TRUEFD_Z_long->GetYaxis()->SetTitle("Nb of events");
  E2_TRUEFD_Z_long->GetYaxis()->SetTitleOffset(1.6);
  E2_TRUEFD_Z_long->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_long.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_long.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_TRUEFD_Z_long.C");

  E1_E2_avg->GetXaxis()->SetTitle("FirstZ_reco - FirstZ");
  E1_E2_avg->GetYaxis()->SetTitle("Nb of events");
  E1_E2_avg->GetYaxis()->SetTitleOffset(1.6);
  E1_E2_avg->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_E2_avg.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstGEEreco_KstGEE.C");


  TCanvas *cSquare = new TCanvas("cSquare","Plots",100,100,1000,1000);
  E1_convertion_pt->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  E1_convertion_pt->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  E1_convertion_pt->GetYaxis()->SetTitleOffset(1.6);
  E1_convertion_pt->Draw("COLZ");
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_convertion_pt.png");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_convertion_pt.pdf");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_convertion_pt.C");

  E1_missed->GetXaxis()->SetTitle("E1_TRACK_FirstMeasurementX");
  E1_missed->GetYaxis()->SetTitle("E1_TRACK_FirstMeasurementY");
  E1_missed->GetYaxis()->SetTitleOffset(1.6);
  E1_missed->Draw();
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_missed.png");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_missed.pdf");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_missed.C");

  E1_false_hits->GetXaxis()->SetTitle("E1_TRUE_EXP_TRACK_FirstMeasurementX");
  E1_false_hits->GetYaxis()->SetTitle("E1_TRUE_EXP_TRACK_FirstMeasurementY");
  E1_false_hits->GetYaxis()->SetTitleOffset(1.6);
  E1_false_hits->Draw();
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_false_hits.png");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_false_hits.pdf");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_false_hits.C");

  E2_convertion_pt->GetXaxis()->SetTitle("E2_TRUEORIGINVERTEX_X");
  E2_convertion_pt->GetYaxis()->SetTitle("E2_TRUEORIGINVERTEX_Y");
  E2_convertion_pt->GetYaxis()->SetTitleOffset(1.6);
  E2_convertion_pt->Draw("COLZ");
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_convertion_pt.png");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_convertion_pt.pdf");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_convertion_pt.C");

  E2_missed->GetXaxis()->SetTitle("E2_TRACK_FirstMeasurementX");
  E2_missed->GetYaxis()->SetTitle("E2_TRACK_FirstMeasurementY");
  E2_missed->GetYaxis()->SetTitleOffset(1.6);
  E2_missed->Draw();
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_missed.png");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_missed.pdf");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_missed.C");

  E2_false_hits->GetXaxis()->SetTitle("E2_TRUE_EXP_TRACK_FirstMeasurementX");
  E2_false_hits->GetYaxis()->SetTitle("E2_TRUE_EXP_TRACK_FirstMeasurementY");
  E2_false_hits->GetYaxis()->SetTitleOffset(1.6);
  E2_false_hits->Draw();
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_false_hits.png");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_false_hits.pdf");
  //cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_false_hits.C");

  G_CONV_VELO->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  G_CONV_VELO->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  G_CONV_VELO->GetYaxis()->SetTitleOffset(1.6);
  G_CONV_VELO->Draw();
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_G_CONV_VELO.png");

  G_CONV_RF->GetXaxis()->SetTitle("E1_TRUEORIGINVERTEX_X");
  G_CONV_RF->GetYaxis()->SetTitle("E1_TRUEORIGINVERTEX_Y");
  G_CONV_RF->GetYaxis()->SetTitleOffset(1.6);
  G_CONV_RF->Draw();
  cSquare->SaveAs("../plots/"+output_folder+"/"+output_folder+"_G_CONV_RF.png");


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

  T->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &E1_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &E1_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementY", &E1_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E1_TRACK_FirstMeasurementX", &E1_TRACK_FirstMeasurementX);


  T->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &E2_EXP_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &E2_TRACK_FirstMeasurementZ);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementY", &E2_TRACK_FirstMeasurementY);
  T->SetBranchAddress("E2_TRACK_FirstMeasurementX", &E2_TRACK_FirstMeasurementX);

  // Output file
  TFile *newf = new TFile("../plots/"+output_folder+".root","RECREATE");

  //Declare histograms
  TH1F *E1_KstEEZ_vs_KstGEEZ = new TH1F("E1_KstEEZ_vs_KstGEEZ", "FirstZ_reco - FirstZ", 100, -500, 100);

  TH1F *E2_KstEEZ_vs_KstGEEZ = new TH1F("E2_KstEEZ_vs_KstGEEZ", "FirstZ_reco - FirstZ", 100, -500, 100);

    TH1F *E1_E2_avg = new TH1F("E1_E2_combi", "E1_E2_avg(FirstZ_reco - FirstZ)", 100, -500, 100);

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
  }

  newf->Write("",TObject::kOverwrite);

  E1_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E1_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E1_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_KstEEreco_KstGEE.C");

  E2_KstEEZ_vs_KstGEEZ->GetXaxis()->SetTitle("FirstZ_KstEE_reco - FirstZ");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitle("Nb of events");
  E2_KstEEZ_vs_KstGEEZ->GetYaxis()->SetTitleOffset(1.6);
  E2_KstEEZ_vs_KstGEEZ->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.png");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.pdf");
  //c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E2_KstEEreco_KstGEE.C");

  E1_E2_avg->GetXaxis()->SetTitle("FirstZ_reco - FirstZ");
  E1_E2_avg->GetYaxis()->SetTitle("Nb of events");
  E1_E2_avg->GetYaxis()->SetTitleOffset(1.6);
  E1_E2_avg->Draw();
  c->SaveAs("../plots/"+output_folder+"/"+output_folder+"_E1_E2_avg.png");
}
