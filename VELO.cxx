#include "VELO.h"

//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
VELO::VELO()
{
  // construct VELO by hand
  // test
  Station s0(0, -150, TRUE);
  VELO_station.push_back(s0);
  nb_stations = VELO_stations.size();
}

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Station VELO::GetStation( Int_t station_number )
{
  return VELO_stations.at(station_number);
}
