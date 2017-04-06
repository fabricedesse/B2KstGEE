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
  // construct LHCb VELO
  double z_min = -175;
  int nb_central_stations = 16;
  int nb_low_angle_stations = 4;

  // Central stations
  for (int i = 0; i< nb_central_stations; i++)
  {
    Station s_left(i*2, z_min + i*30, 1);
    Station s_right(i*2 + 1, s_left.GetZ() + 15, 0);
    VELO_stations.push_back(s_left);
    VELO_stations.push_back(s_right);
  }

  // First two low angle station
  Station s1_left(VELO_stations.back().GetNumber() +1,
                  VELO_stations.back().GetZ() + 145, 1);
  Station s1_right(VELO_stations.back().GetNumber() +2,
                  VELO_stations.back().GetZ() + 160, 0);
  VELO_stations.push_back(s1_left);
  VELO_stations.push_back(s1_right);

  Station s2_left(VELO_stations.back().GetNumber() +1,
                  VELO_stations.back().GetZ() + 135, 1);
  Station s2_right(VELO_stations.back().GetNumber() +2,
                  VELO_stations.back().GetZ() + 150, 0);
  VELO_stations.push_back(s2_left);
  VELO_stations.push_back(s2_right);

  // Low angle stations (appart from the first two)
  for (int i = 0; i <nb_low_angle_stations - 1; i++ )
  {
    Station s_left(VELO_stations.back().GetNumber() +1,
                   VELO_stations.back().GetZ() + 35,1);
    Station s_right(VELO_stations.back().GetNumber() + 2,
                    VELO_stations.back().GetZ() + 50,0);
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
