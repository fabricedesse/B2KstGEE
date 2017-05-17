//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Initializes the VELO with its stations
//
//==============================================================================

#include <stdlib.h>
#include <iostream>

#include "make_plots.h"

using namespace std;

int main()
{
  // Make plots
  cout << "Making plots" << endl;

  TString pathToConv = "/sps/lhcb/fdesse/tuples_B2KstGEE/conversion_tuples/";

  make_plots_MC(pathToConv+"EE_candidates_gamma_20170511.root", "Bd2KstGEE", "MC_GEE");
  make_plots_MC(pathToConv+"EE_candidates_gamma_20170511.root", "Bd2KstEE", "MC_EE");
  make_plots_MC(pathToConv+"EE_candidates_jps_20170511.root", "Bd2KstJPsEE", "MC_JPsEE");
  make_plots_data(pathToConv+"EE_candidates_jps_20170511.root", "data", "JPsEE");

  //MergePlot()

  // Make efficiency plots
  // plot_cut();

  cout << "Main is done." << endl;
}
