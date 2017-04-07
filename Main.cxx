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

using namespace std;

int main()
{

  // Create trees
  create_tree("../data/EE_candidates_q2gamma_Final.root", "Bd2KstGEE",
              "../data/MCGEE_TRACKZ.root");
  create_tree("../data/EE_candidates_jps.root", "Bd2KstJpsEE",
              "../data/MCJPsEE_TRACKZ.root")

  cout << "Main is done." << endl;
}
