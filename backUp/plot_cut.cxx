//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-16
//
// Makes efficiency S/B plots for cuts in FirstMeasurementZ, X and Y.
//
// Output: Plots
//
// Inputs: None
//
//==============================================================================

#include "plot_cut.h"

void plot_cut()
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
  Double_t EE_JPs_ENDVERTEX_ZERR;
  Double_t EE_E1_XY_FROM_BEAM;
  Double_t EE_E2_XY_FROM_BEAM;

  TEE->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &EE_E1_EXP_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &EE_E2_EXP_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &EE_E1_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &EE_E2_TRACK_FirstMeasurementZ);
  TEE->SetBranchAddress("JPs_ENDVERTEX_ZERR", &EE_JPs_ENDVERTEX_ZERR);
  TEE->SetBranchAddress("E1_XY_FROM_BEAM", &EE_E1_XY_FROM_BEAM);
  TEE->SetBranchAddress("E2_XY_FROM_BEAM", &EE_E2_XY_FROM_BEAM);


  // Bd2KstJPsEE control channel
  TFile *fJPs = TFile::Open("../data/JPsEE_massCut.root","read");
  if (fJPs == 0)
  {
    printf("Error: cannot open file");
    return;
  }

  TTree *TJPs = (TTree*)fJPs->Get("KstJPsEE");

  Double_t JPs_E1_EXP_TRACK_FirstMeasurementZ;
  Double_t JPs_E2_EXP_TRACK_FirstMeasurementZ;
  Double_t JPs_E1_TRACK_FirstMeasurementZ;
  Double_t JPs_E2_TRACK_FirstMeasurementZ;
  Double_t JPs_JPs_ENDVERTEX_ZERR;
  Double_t JPs_E1_XY_FROM_BEAM;
  Double_t JPs_E2_XY_FROM_BEAM;

  TJPs->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &JPs_E1_EXP_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &JPs_E2_EXP_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &JPs_E1_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &JPs_E2_TRACK_FirstMeasurementZ);
  TJPs->SetBranchAddress("JPs_ENDVERTEX_ZERR", &JPs_JPs_ENDVERTEX_ZERR);
  TJPs->SetBranchAddress("E1_XY_FROM_BEAM", &JPs_E1_XY_FROM_BEAM);
  TJPs->SetBranchAddress("E2_XY_FROM_BEAM", &JPs_E2_XY_FROM_BEAM);



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
  Double_t GEE_JPs_ENDVERTEX_ZERR;
  Double_t GEE_E1_XY_FROM_BEAM;
  Double_t GEE_E2_XY_FROM_BEAM;

  TGEE->SetBranchAddress("E1_EXP_TRACK_FirstMeasurementZ", &GEE_E1_EXP_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("E2_EXP_TRACK_FirstMeasurementZ", &GEE_E2_EXP_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &GEE_E1_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("E2_TRACK_FirstMeasurementZ", &GEE_E2_TRACK_FirstMeasurementZ);
  TGEE->SetBranchAddress("JPs_ENDVERTEX_ZERR", &GEE_JPs_ENDVERTEX_ZERR);
  TGEE->SetBranchAddress("E1_XY_FROM_BEAM", &GEE_E1_XY_FROM_BEAM);
  TGEE->SetBranchAddress("E2_XY_FROM_BEAM", &GEE_E2_XY_FROM_BEAM);


  //============================================================================
  // Cuts config
  //============================================================================

  // FirstMeasurementZ cut
  Double_t cut_minZ = -120;
  Double_t cut_maxZ = 10;
  Int_t nb_loopZ = 10;
  Double_t cut_stepZ = ( cut_maxZ - cut_minZ ) / float( nb_loopZ );

  // FirstMeasurementXY cut
  Double_t cut_minXY = 20;
  Double_t cut_maxXY = 5;
  Double_t nb_loopXY = 10;
  Double_t cut_stepXY = ( cut_minXY - cut_maxXY ) / float( nb_loopXY );

  Double_t bkg_rejection;
  Double_t sig_efficiency;
  Double_t control_efficiency;

  //============================================================================
  // Z cut loop
  //============================================================================

  Int_t sig_yield = TEE->GetEntries();
  Int_t control_yield = TJPs->GetEntries();
  Int_t bkg_yield = TGEE->GetEntries();

  TGraph2D *grEE = new TGraph2D();
  TGraph2D *grJPs = new TGraph2D();

  TGraph *grEE1D_E1 = new TGraph();
  TGraph *grJPs1D_E1 = new TGraph();

  TGraph *grEE1D_E2 = new TGraph();
  TGraph *grJPs1D_E2 = new TGraph();

  for (int i = 0; i < nb_loopZ; i++)
  {
    Double_t my_cut = cut_minZ + i*cut_stepZ;
    // convert my_cut into a string
    char output [50];
    sprintf(output, "%f", my_cut);
    TString my_cut_str = output;

    // E1
    TEE->Draw("E1_EXP_TRACK_FirstMeasurementZ>>hEE_E1", "E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+my_cut_str);
    TH1F *hEE_E1 = (TH1F*)gDirectory->Get("hEE_E1");
    TJPs->Draw("E1_EXP_TRACK_FirstMeasurementZ>>hJPs_E1", "E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+my_cut_str);
    TH1F *hJPs_E1 = (TH1F*)gDirectory->Get("hJPs_E1");
    TGEE->Draw("E1_EXP_TRACK_FirstMeasurementZ>>hGEE_E1", "E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+my_cut_str);
    TH1F *hGEE_E1 = (TH1F*)gDirectory->Get("hGEE_E1");

    Double_t sig_efficiency_E1 = float ( hEE_E1->GetEntries() ) / float ( sig_yield );
    Double_t control_efficiency_E1 = float ( hJPs_E1->GetEntries() ) / float ( control_yield );
    Double_t bkg_rejection_E1 = float ( bkg_yield - hGEE_E1->GetEntries() ) / float ( bkg_yield );

    grEE->SetPoint(i, sig_efficiency_E1, my_cut, bkg_rejection_E1 );
    grJPs->SetPoint(i, control_efficiency_E1, my_cut, bkg_rejection_E1 );

    // std::cout << "sig_eff= " << control_efficiency_E1 << " bkg_rej= " << bkg_rejection_E1 << " cut= " << my_cut << std::endl;

    grEE1D_E1->SetPoint( i, sig_efficiency_E1, bkg_rejection_E1 );
    grJPs1D_E1->SetPoint( i, control_efficiency_E1, bkg_rejection_E1 );

    // E2
    TEE->Draw("E2_EXP_TRACK_FirstMeasurementZ>>hEE_E2", "E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+my_cut_str);
    TH1F *hEE_E2 = (TH1F*)gDirectory->Get("hEE_E2");
    TJPs->Draw("E2_EXP_TRACK_FirstMeasurementZ>>hJPs_E2", "E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+my_cut_str);
    TH1F *hJPs_E2 = (TH1F*)gDirectory->Get("hJPs_E2");
    TGEE->Draw("E2_EXP_TRACK_FirstMeasurementZ>>hGEE_E2", "E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+my_cut_str);
    TH1F *hGEE_E2 = (TH1F*)gDirectory->Get("hGEE_E2");

    Double_t sig_efficiency_E2 = float ( hEE_E2->GetEntries() ) / float ( sig_yield );
    Double_t control_efficiency_E2 = float ( hJPs_E2->GetEntries() ) / float ( control_yield );
    Double_t bkg_rejection_E2 = float ( bkg_yield - hGEE_E2->GetEntries() ) / float ( bkg_yield );

    grEE1D_E2->SetPoint( i, sig_efficiency_E2, bkg_rejection_E2 );
    grJPs1D_E2->SetPoint( i, control_efficiency_E2, bkg_rejection_E2 );

  }

  //============================================================================
  // XY cut loop
  //============================================================================

  // Make magic Z cut
  Double_t magic_Zcut = -31;
  char output [50];
  sprintf(output, "%f", magic_Zcut);
  TString magic_Zcut_str = output;

  // E1
  TEE->Draw("E1_EXP_TRACK_FirstMeasurementZ>>hEE_E1_Zcut", "E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
  TH1F *hEE_E1_Zcut = (TH1F*)gDirectory->Get("hEE_E1_Zcut");
  TJPs->Draw("E1_EXP_TRACK_FirstMeasurementZ>>hJPs_E1_Zcut", "E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
  TH1F *hJPs_E1_Zcut = (TH1F*)gDirectory->Get("hJPs_E1_Zcut");
  TGEE->Draw("E1_EXP_TRACK_FirstMeasurementZ>>hGEE_E1_Zcut", "E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
  TH1F *hGEE_E1_Zcut = (TH1F*)gDirectory->Get("hGEE_E1_Zcut");

  Int_t sig_yield_E1 = hEE_E1_Zcut->GetEntries();
  Int_t control_yield_E1 = hJPs_E1_Zcut->GetEntries();
  Int_t bkg_yield_E1 = hGEE_E1_Zcut->GetEntries();

  std::cout << "control_yield_z = " << control_yield_E1 << std::endl;
  std::cout << "bkg_yield_z = " << bkg_yield_E1 << std::endl;

  // E2
  TEE->Draw("E2_EXP_TRACK_FirstMeasurementZ>>hEE_E2_Zcut", "E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
  TH1F *hEE_E2_Zcut = (TH1F*)gDirectory->Get("hEE_E2_Zcut");
  TJPs->Draw("E2_EXP_TRACK_FirstMeasurementZ>>hJPs_E2_Zcut", "E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
  TH1F *hJPs_E2_Zcut = (TH1F*)gDirectory->Get("hJPs_E2_Zcut");
  TGEE->Draw("E2_EXP_TRACK_FirstMeasurementZ>>hGEE_E2_Zcut", "E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
  TH1F *hGEE_E2_Zcut = (TH1F*)gDirectory->Get("hGEE_E2_Zcut");

  Int_t sig_yield_E2 = hEE_E2_Zcut->GetEntries();
  Int_t control_yield_E2 = hJPs_E2_Zcut->GetEntries();
  Int_t bkg_yield_E2 = hGEE_E2_Zcut->GetEntries();

  TGraph *grEE1D_E1_XY = new TGraph();
  TGraph *grJPs1D_E1_XY = new TGraph();

  TGraph *grEE1D_E2_XY = new TGraph();
  TGraph *grJPs1D_E2_XY = new TGraph();

  // Start loop over XY cuts
  for (int i = 0; i < nb_loopXY; i++)
  {
    Double_t my_cut = cut_minXY - i*cut_stepXY;
    // convert my_cut into a string
    char output [50];
    sprintf(output, "%f", my_cut);
    TString my_cut_str = output;

    // E1
    TEE->Draw("E1_XY_FROM_BEAM>>hEE_E1_XY", "E1_XY_FROM_BEAM <"+my_cut_str+" && E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
    TH1F *hEE_E1_XY = (TH1F*)gDirectory->Get("hEE_E1_XY");
    TJPs->Draw("E1_XY_FROM_BEAM>>hJPs_E1_XY","E1_XY_FROM_BEAM <"+my_cut_str+" && E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
    TH1F *hJPs_E1_XY = (TH1F*)gDirectory->Get("hJPs_E1_XY");
    TGEE->Draw("E1_XY_FROM_BEAM>>hGEE_E1_XY","E1_XY_FROM_BEAM <"+my_cut_str+" && E1_EXP_TRACK_FirstMeasurementZ - E1_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
    TH1F *hGEE_E1_XY = (TH1F*)gDirectory->Get("hGEE_E1_XY");

    Double_t sig_efficiency_E1 = float ( hEE_E1_XY->GetEntries() ) / float ( sig_yield_E1 );
    Double_t control_efficiency_E1 = float ( hJPs_E1_XY->GetEntries() ) / float ( control_yield_E1 );
    Double_t bkg_rejection_E1 = float ( bkg_yield_E1 - hGEE_E1_XY->GetEntries() ) / float ( bkg_yield_E1 );

    std::cout << "control_yield = " << hJPs_E1_XY->GetEntries() << std::endl;
    std::cout << "sig_eff= " << control_efficiency_E1 << " bkg_rej= " << bkg_rejection_E1 << " cut= " << my_cut << std::endl;

    grEE1D_E1_XY->SetPoint( i, sig_efficiency_E1, bkg_rejection_E1 );
    grJPs1D_E1_XY->SetPoint( i, control_efficiency_E1, bkg_rejection_E1 );

    // E2
    TEE->Draw("E2_XY_FROM_BEAM>>hEE_E2_XY", "E2_XY_FROM_BEAM <"+my_cut_str+" && E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
    TH1F *hEE_E2_XY = (TH1F*)gDirectory->Get("hEE_E2_XY");
    TJPs->Draw("E2_XY_FROM_BEAM>>hJPs_E2_XY","E2_XY_FROM_BEAM <"+my_cut_str+" && E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
    TH1F *hJPs_E2_XY = (TH1F*)gDirectory->Get("hJPs_E2_XY");
    TGEE->Draw("E2_XY_FROM_BEAM>>hGEE_E2_XY","E2_XY_FROM_BEAM <"+my_cut_str+" && E2_EXP_TRACK_FirstMeasurementZ - E2_TRACK_FirstMeasurementZ >"+magic_Zcut_str);
    TH1F *hGEE_E2_XY = (TH1F*)gDirectory->Get("hGEE_E2_XY");

    Double_t sig_efficiency_E2 = float ( hEE_E2_XY->GetEntries() ) / float ( sig_yield_E2 );
    Double_t control_efficiency_E2 = float ( hJPs_E2_XY->GetEntries() ) / float ( control_yield_E2 );
    Double_t bkg_rejection_E2 = float ( bkg_yield_E2 - hGEE_E2_XY->GetEntries() ) / float ( bkg_yield_E2 );

    // std::cout << "sig_eff= " << control_efficiency_E2 << " bkg_rej= " << bkg_rejection_E2 << " cut= " << my_cut << std::endl;

    grEE1D_E2_XY->SetPoint( i, sig_efficiency_E2, bkg_rejection_E2 );
    grJPs1D_E2_XY->SetPoint( i, control_efficiency_E2, bkg_rejection_E2 );

  }

  TCanvas *c = new TCanvas("c","Plots",100,100,1400,1000);

  grEE->Draw("surf1");
  c->Update();
  grEE->SetTitle("Bkg rejection vs Sig efficiency");
  grEE->GetXaxis()->SetTitle("Sig efficiency");
  grEE->GetYaxis()->SetTitle("cut Zdiff");
  grEE->GetZaxis()->SetTitle("Bkg rejection");
  grEE->GetXaxis()->SetTitleOffset(1.6);
  grEE->GetYaxis()->SetTitleOffset(1.6);
  grEE->GetZaxis()->SetTitleOffset(1.4);
  c->SetTheta(60);
  c->Modified();
  c->SaveAs("../plots/efficiency/E1_EE_zCut_eff3D.png");

  TCanvas *c2 = new TCanvas("c2","Plots",100,100,1400,1000);
  grJPs->Draw("surf1");
  c2->Update();
  grJPs->SetTitle("Bkg rejection vs Sig efficiency (JPs)");
  grJPs->GetXaxis()->SetTitle("Sig efficiency");
  grJPs->GetYaxis()->SetTitle("cut Zdiff");
  grJPs->GetZaxis()->SetTitle("Bkg rejection");
  grJPs->GetXaxis()->SetTitleOffset(1.6);
  grJPs->GetYaxis()->SetTitleOffset(1.6);
  grJPs->GetZaxis()->SetTitleOffset(1.4);
  c2->SetTheta(60);
  c2->Modified();
  c2->SaveAs("../plots/efficiency/E1_JPs_zCut_eff3D.png");

  TCanvas *c3 = new TCanvas("c3","Plots",100,100,1400,1000);
  grEE1D_E1->Draw("APL");
  c3->Update();
  grEE1D_E1->SetTitle("Bkg rejection vs Sig efficiency");
  grEE1D_E1->GetXaxis()->SetTitle("Sig efficiency");
  grEE1D_E1->GetXaxis()->SetRangeUser(0.,1.);
  grEE1D_E1->GetYaxis()->SetTitle("Bkg rejection");
  grEE1D_E1->GetYaxis()->SetRangeUser(0.,1.);
  grEE1D_E1->GetXaxis()->SetTitleOffset(1.6);
  grEE1D_E1->GetYaxis()->SetTitleOffset(1.6);
  grEE1D_E1->SetMarkerStyle(2);
  c3->Modified();
  c3->SaveAs("../plots/efficiency/E1_EE_zCut_eff.png");

  TCanvas *c4 = new TCanvas("c4","Plots",100,100,1400,1000);
  grJPs1D_E1->Draw("APL");
  c4->Update();
  grJPs1D_E1->SetTitle("Bkg rejection vs Sig efficiency (JPs)");
  grJPs1D_E1->GetXaxis()->SetTitle("Sig efficiency");
  grJPs1D_E1->GetXaxis()->SetRangeUser(0.,1.);
  grJPs1D_E1->GetYaxis()->SetTitle("Bkg rejection");
  grJPs1D_E1->GetYaxis()->SetRangeUser(0.,1.);
  grJPs1D_E1->GetXaxis()->SetTitleOffset(1.6);
  grJPs1D_E1->GetYaxis()->SetTitleOffset(1.6);
  grJPs1D_E1->SetMarkerStyle(2);
  c4->Modified();
  c4->SaveAs("../plots/efficiency/E1_JPs_zCut_eff.png");

  TCanvas *c5 = new TCanvas("c3","Plots",100,100,1400,1000);
  grEE1D_E2->Draw("APL");
  c5->Update();
  grEE1D_E2->SetTitle("Bkg rejection vs Sig efficiency");
  grEE1D_E2->GetXaxis()->SetTitle("Sig efficiency");
  grEE1D_E2->GetXaxis()->SetRangeUser(0.,1.);
  grEE1D_E2->GetYaxis()->SetTitle("Bkg rejection");
  grEE1D_E2->GetYaxis()->SetRangeUser(0.,1.);
  grEE1D_E2->GetXaxis()->SetTitleOffset(1.6);
  grEE1D_E2->GetYaxis()->SetTitleOffset(1.6);
  grEE1D_E2->SetMarkerStyle(2);
  c5->Modified();
  c5->SaveAs("../plots/efficiency/E2_EE_zCut_eff.png");

  TCanvas *c6 = new TCanvas("c4","Plots",100,100,1400,1000);
  grJPs1D_E2->Draw("APL");
  c6->Update();
  grJPs1D_E2->SetTitle("Bkg rejection vs Sig efficiency (JPs)");
  grJPs1D_E2->GetXaxis()->SetTitle("Sig efficiency");
  grJPs1D_E2->GetXaxis()->SetRangeUser(0.,1.);
  grJPs1D_E2->GetYaxis()->SetTitle("Bkg rejection");
  grJPs1D_E2->GetYaxis()->SetRangeUser(0.,1.);
  grJPs1D_E2->GetXaxis()->SetTitleOffset(1.6);
  grJPs1D_E2->GetYaxis()->SetTitleOffset(1.6);
  grJPs1D_E2->SetMarkerStyle(2);
  c6->Modified();
  c6->SaveAs("../plots/efficiency/E2_JPs_zCut_eff.png");

  TCanvas *c7 = new TCanvas("c3","Plots",100,100,1400,1000);
  grEE1D_E1_XY->Draw("APL");
  c7->Update();
  grEE1D_E1_XY->SetTitle("Bkg rejection vs Sig efficiency");
  grEE1D_E1_XY->GetXaxis()->SetTitle("Sig efficiency");
  grEE1D_E1_XY->GetXaxis()->SetRangeUser(0.,1.);
  grEE1D_E1_XY->GetYaxis()->SetTitle("Bkg rejection");
  grEE1D_E1_XY->GetYaxis()->SetRangeUser(0.,1.);
  grEE1D_E1_XY->GetXaxis()->SetTitleOffset(1.6);
  grEE1D_E1_XY->GetYaxis()->SetTitleOffset(1.6);
  grEE1D_E1_XY->SetMarkerStyle(2);
  c7->Modified();
  c7->SaveAs("../plots/efficiency/E1_XY_EE_zCut_eff.png");

  TCanvas *c8 = new TCanvas("c4","Plots",100,100,1400,1000);
  grJPs1D_E1_XY->Draw("APL");
  c8->Update();
  grJPs1D_E1_XY->SetTitle("Bkg rejection vs Sig efficiency (JPs)");
  grJPs1D_E1_XY->GetXaxis()->SetTitle("Sig efficiency");
  grJPs1D_E1_XY->GetXaxis()->SetRangeUser(0.,1.);
  grJPs1D_E1_XY->GetYaxis()->SetTitle("Bkg rejection");
  grJPs1D_E1_XY->GetYaxis()->SetRangeUser(0.,1.);
  grJPs1D_E1_XY->GetXaxis()->SetTitleOffset(1.6);
  grJPs1D_E1_XY->GetYaxis()->SetTitleOffset(1.6);
  grJPs1D_E1_XY->SetMarkerStyle(2);
  c8->Modified();
  c8->SaveAs("../plots/efficiency/E1_XY_JPs_zCut_eff.png");

  TCanvas *c9 = new TCanvas("c3","Plots",100,100,1400,1000);
  grEE1D_E2_XY->Draw("APL");
  c9->Update();
  grEE1D_E2_XY->SetTitle("Bkg rejection vs Sig efficiency");
  grEE1D_E2_XY->GetXaxis()->SetTitle("Sig efficiency");
  grEE1D_E2_XY->GetXaxis()->SetRangeUser(0.,1.);
  grEE1D_E2_XY->GetYaxis()->SetTitle("Bkg rejection");
  grEE1D_E2_XY->GetYaxis()->SetRangeUser(0.,1.);
  grEE1D_E2_XY->GetXaxis()->SetTitleOffset(1.6);
  grEE1D_E2_XY->GetYaxis()->SetTitleOffset(1.6);
  grEE1D_E2_XY->SetMarkerStyle(2);
  c9->Modified();
  c9->SaveAs("../plots/efficiency/E2_XY_EE_zCut_eff.png");

  TCanvas *c10 = new TCanvas("c4","Plots",100,100,1400,1000);
  grJPs1D_E2_XY->Draw("APL");
  c10->Update();
  grJPs1D_E2_XY->SetTitle("Bkg rejection vs Sig efficiency (JPs)");
  grJPs1D_E2_XY->GetXaxis()->SetTitle("Sig efficiency");
  grJPs1D_E2_XY->GetXaxis()->SetRangeUser(0.,1.);
  grJPs1D_E2_XY->GetYaxis()->SetTitle("Bkg rejection");
  grJPs1D_E2_XY->GetYaxis()->SetRangeUser(0.,1.);
  grJPs1D_E2_XY->GetXaxis()->SetTitleOffset(1.6);
  grJPs1D_E2_XY->GetYaxis()->SetTitleOffset(1.6);
  grJPs1D_E2_XY->SetMarkerStyle(2);
  c10->Modified();
  c10->SaveAs("../plots/efficiency/E2_XY_JPs_zCut_eff.png");

}
