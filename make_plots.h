//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-07-05
//
//
//==============================================================================

#ifndef make_plots_h
#define make_plots_h

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"

void make_plots_MC(TString input_file, TString input_tree, TString output_folder);
void make_plots_data(TString input_file, TString input_tree, TString output_folder);


#endif
