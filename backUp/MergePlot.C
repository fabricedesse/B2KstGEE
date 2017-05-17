//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Implementation file for function: MergePlot()
//
//==============================================================================

#include "MergePlot.h"

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
