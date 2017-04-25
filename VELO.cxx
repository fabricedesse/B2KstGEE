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

  bool isFront = true;
  bool isLeft = true;

  // Left stations
  for (int i = 0; i < 42; i++)
  {
    if ( i%2 == 0 )
    {
      Station s_front(i, my_VELO_left[i], isLeft, isFront);
      VELO_stations.push_back(s_front);
    }

    else
    {
      Station s_back(i, my_VELO_left[i], isLeft, !isFront);
      VELO_stations.push_back(s_back);
    }
  }

  // Right stations
  for (int i = 0; i < 42; i++)
    {
      if ( i%2 == 0 )
      {
        Station s_front(i, my_VELO_right[i], !isLeft, isFront);
        VELO_stations.push_back(s_front);
      }

      else
      {
        Station s_back(i, my_VELO_right[i], !isLeft, !isFront);
        VELO_stations.push_back(s_back);
      }

    }

    // Sort stations
    std::sort(VELO_stations.begin(), VELO_stations.end() );

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
    std::cout << "Station #" << VELO_stations.at(i).GetNumber() << " *** z = " << VELO_stations.at(i).GetZ() << " *** IsLeft = " << VELO_stations.at(i).IsLeft() << " *** IsFront = " << VELO_stations.at(i).IsFront() << std::endl;
  }
}

// Others

bool VELO::IsInStations( double x, double y, double z, Beam myBeam)
{
  TVector2 XY(x, y);
  if ( !isInAcceptance( XY, myBeam, 0) ) return false;
  else
  {
    for (int i=0; i<nb_stations; i++)
    {
      Station front_station = VELO_stations.at(i);
      if ( !front_station.IsFront() ) continue;
      else if ( z < front_station.GetZ() ) break;
      else
      {
        Station back_station = VELO_stations.at(i+1);
        if ( front_station.GetZ() <= z && z <= back_station.GetZ() && ( ( x >= myBeam.GetX() && front_station.IsLeft() ) || ( x <= myBeam.GetX() && !front_station.IsLeft() ) ) ) return true;
        else continue;
      }
    }
    return false;
  }

}
