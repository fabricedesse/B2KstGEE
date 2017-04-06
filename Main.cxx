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
#include "exp_z.C"

using namespace std;

int main()
{
  // Construct VELO
  VELO myVELO;
  myVELO.PrintStations();

  // Test of exp_z
  cout << get_exp_firstMeasurementZ(-8.2,0,30,0,0,-175,myVELO) << endl;

  cout << "Main is done." << endl;
}
