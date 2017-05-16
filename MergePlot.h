//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Function: MergePlot()
//
//==============================================================================

#ifndef MERGE_PLOT_H
#define MERGE_PLOT_H

#include "TFile.h"
#include "TH1F.h"
#include "TString.h"
#include "TCanvas.h"

void MergePlot( TString file1, TString plot1, TString file2, TString plot2, TString outFile );

#endif
