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

using namespace std;

Double_t GetPhi(Double_t PX, Double_t PY)
{
  TVector2 PXY(PX, PY);

  if ( PY >= 0 )
  {
    return acos( PX / PXY.Mag() );
  }

  else return TMath::Pi() + acos ( PX / PXY.Mag() );
}

int main()
{
  // Test
  cout << GetPhi(0,1) << endl;
  cout << GetPhi(-0.9, 0) << endl;
  cout << GetPhi(0.1, -0.9) << endl;

  // Create trees

  // create_tree_MC("../data/EE_candidates_gamma_20160928.root", "Bd2KstGEE","../data/MCGEE_TRACKZ.root");
  // create_tree_MC("../data/EE_candidates_jps.root", "Bd2KstJPsEE","../data/MCJPsEE_TRACKZ.root");
  // create_tree_MC("../data/EE_candidates_gamma_20160928.root", "Bd2KstEE","../data/MCEE_TRACKZ.root");
  //
  // create_tree_JPs("../data/EE_candidates_jps.root", "KstJPsEE", "../data/JPsEE_massCut.root");


  // Make plots
  // make_plots_MC("../data/MCGEE_TRACKZ.root", "Bd2KstGEE", "MC_GEE");
  // make_plots_MC("../data/MCEE_TRACKZ.root", "Bd2KstEE", "MC_EE");
  // make_plots_MC("../data/MCJPsEE_TRACKZ.root", "Bd2KstJPsEE", "MC_JPsEE");
  // make_plots_data("../data/JPsEE_massCut.root", "KstJPsEE", "JPsEE");

  // Make efficiency plots
  // plot_cut();


  cout << "Main is done." << endl;
}
