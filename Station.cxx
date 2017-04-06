//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class Station: station of the VELO
//
//==============================================================================

#include "Station.h"

// Default constructor
Station::Station()
{
}

// Full constructor
Station::Station(int number, double z_position, bool isLeft,
                 double min_r, double max_r)
{
  station_number = number;
  station_z = z_position;
  station_isLeft = isLeft;
  min_radius = min_r;
  max_radius = max_r;
}

//==============================================================================
// Public member functions
//==============================================================================

// Getters
int Station::GetNumber()
{
  return station_number;
}

double Station::GetZ()
{
  return station_z;
}

bool Station::IsLeft()
{
  return station_isLeft;
}

// Setters
void Station::SetNumber(int number)
{
  station_number = number;
}

void Station::SetZ(double z)
{
  station_z = z;
}

void Station::SetIsLeft(bool isLeft)
{
  station_isLeft = isLeft;
}

// Other
bool Station::IsInAcceptance( TVector2 XY)
{
  if ( XY.Mod() > 8.2 && XY.Mod() < 49.1 ) return 1;
  else return 0;
}
