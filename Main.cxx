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

using namespace std;

int main()
{
/*
  // Create trees
  create_tree("../data/EE_candidates_q2gamma_Final.root", "Bd2KstGEE",
              "../data/MCGEE_TRACKZ.root");
  create_tree("../data/EE_candidates_jps.root", "Bd2KstJPsEE",
              "../data/MCJPsEE_TRACKZ.root");
  create_tree("../data/EE_candidates_q2gamma_Final.root", "Bd2KstEE",
              "../data/MCEE_TRACKZ.root");
*/
  // Make plots
  make_plots_MC("../data/MCGEE_TRACKZ.root", "Bd2KstGEE", "MC_GEE");
  make_plots_MC("../data/MCEE_TRACKZ.root", "Bd2KstEE", "MC_EE");
  make_plots_MC("../data/MCJPsEE_TRACKZ.root", "Bd2KstJPsEE", "MC_JPsEE");

  cout << "Main is done." << endl;
}
