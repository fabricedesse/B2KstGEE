//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Initializes the VELO with its stations
//
//==============================================================================

#include <stdlib.h>

#include "VELO.h"
#include "Station.h"
#include "create_tree.h"
#include "make_plots.h"
#include "plot_cut.h"
#include "Sample.h"
#include "Q2Bin.h"

using namespace std;

int main()
{

  //============================================================================
  // Construct samples
  //============================================================================
  TString rawFile = "../data/Raw/Raw.root";

  // Gamma
  TFile fGamma("../data/CreateTuple/EE_candidates_gamma_20170505.root", "RECREATE");
  std::vector<Sample> gammaSamples;
  Q2Bin gamma(0, 0.0004, 3350, 135, 0.49, 4500, 6200);

  Sample Bd2KstGEE(rawFile, "Bd2KstGEE", true, Sample::DecayType::KstGEE);
  gammaSamples.push_back(Bd2KstGEE);
  Sample Bd2KstEE(rawFile, "Bd2KstEE", true, Sample::DecayType::KstEE);
  gammaSamples.push_back(Bd2KstEE);
  Sample KstGEE(rawFile, "LPT", false, Sample::DecayType::KstGEE);
  gammaSamples.push_back(KstGEE);

  // Loop over samples to create trees

  // Low
  TFile fLow("../data/CreateTuple/EE_candidates_low_20170505.root", "RECREATE");

  // Central

  // JPsi


  // Create trees
  // create_tree_MC("../data/EE_candidates_gamma_20160928.root", "Bd2KstGEE","../data/MCGEE_TRACKZ.root");
  // create_tree_MC("../data/EE_candidates_jps.root", "Bd2KstJPsEE","../data/MCJPsEE_TRACKZ.root");
  // create_tree_MC("../data/EE_candidates_gamma_20160928.root", "Bd2KstEE","../data/MCEE_TRACKZ.root");
  //
  // create_tree_MC("../data/EE_candidates_low_20160606.root", "Bd2KstGEE", "../data/MCGEE_low.root");
  //
  // create_tree_JPs("../data/EE_candidates_jps.root", "KstJPsEE", "../data/JPsEE_massCut.root");

  // test 2

  // Make plots
  // make_plots_MC("../data/MCGEE_TRACKZ.root", "Bd2KstGEE", "MC_GEE");
  // make_plots_MC("../data/MCEE_TRACKZ.root", "Bd2KstEE", "MC_EE");
  // make_plots_MC("../data/MCJPsEE_TRACKZ.root", "Bd2KstJPsEE", "MC_JPsEE");
  // make_plots_data("../data/JPsEE_massCut.root", "KstJPsEE", "JPsEE");

  // Make efficiency plots
  // plot_cut();



  cout << "Main is done." << endl;
}
