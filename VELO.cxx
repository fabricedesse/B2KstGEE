//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class VELO
//
//==============================================================================


#include "VELO.h"

//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
VELO::VELO()
{
  // construct VELO by hand
  // test
  Station s0(0, -150, 1);
  VELO_stations.push_back(s0);
  nb_stations = VELO_stations.size();
}

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Station VELO::GetStation( int station_number )
{
  return VELO_stations.at(station_number);
}

int VELO::GetNbStations()
{
  return nb_stations;
}

// Printers

void VELO::PrintStations()
{
  for (int i=0; i<nb_stations; i++)
  {
    std::cout << "VELO has " << nb_stations << " stations." << std::endl
      << "Station #" << VELO_stations.at(i).GetNumber()
      << " *** z = " << VELO_stations.at(i).GetZ()
      << " *** IsLeft = " << VELO_stations.at(i).IsLeft() << std::endl;
  }
}
