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
Station::Station(int number, double z_position, bool isLeft, bool isFront, double min_r, double max_r)
{
  station_number = number;
  station_z = z_position;
  station_isLeft = isLeft;
  station_isFront = isFront;
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

bool Station::IsFront()
{
  return station_isFront;
}

// Setters
void Station::Set( int number, double z, bool isLeft)
{
  station_number = number;
  station_z = z;
  station_isLeft = isLeft;
}

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
