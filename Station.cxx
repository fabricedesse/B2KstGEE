#include "Station.h"

// Default constructor
Station::Station()
{
}

// Full constructor
Station::Station(Int_t number, Double_t z_position, Bool_t isLeft)
{
  station_number = number;
  station_z = z_position;
  station_isLeft = isLeft;
}

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Int_t Station::GetNumber()
{
  return station_number;
}

Double_t Station::GetZ()
{
  return station_z;
}

Bool_t Station::IsLeft()
{
  return station_isLeft;
}

// Setters
void Station::SetNumber(Int_t number)
{
  station_number = number;
}

void Station::SetZ(Double_t z)
{
  station_z = z;
}

void Station::SetIsLeft(Bool_t isLeft)
{
  station_isLeft = isLeft;
}
