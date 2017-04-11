//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class VELO
//
//==============================================================================

#include "VELO.h"
#include "VELO_geometry.h"

//==============================================================================
// Constructur & Destructor
//==============================================================================

using namespace VELO_geo;

// Default constructor
VELO::VELO()
{
  // Construct VELO
  double *my_VELO_right = VELO_right();
  double *my_VELO_left = VELO_left();
  for (int i = 0; i < 42; i++)
  {
    Station s_left(i, my_VELO_left[i], 1);
    Station s_right(i, my_VELO_right[i], 0);
    VELO_stations.push_back(s_left);
    VELO_stations.push_back(s_right);
  }

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
  std::cout << "VELO has " << nb_stations << " stations." << std::endl;

  for (int i=0; i<nb_stations; i++)
  {
    std::cout << "Station #" << VELO_stations.at(i).GetNumber()
              << " *** z = " << VELO_stations.at(i).GetZ()
              << " *** IsLeft = " << VELO_stations.at(i).IsLeft()
              << std::endl;
  }
}
