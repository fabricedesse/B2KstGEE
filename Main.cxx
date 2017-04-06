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

using namespace std;

int main()
{
  // Construct VELO
  VELO myVELO;
  myVELO.PrintStations();
  cout << "Main is done." << endl;
}
