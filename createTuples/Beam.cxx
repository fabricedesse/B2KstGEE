//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-13
//
// Beam of the LHC
//
//==============================================================================

#include "Beam.h"

//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
Beam::Beam()
{
}

// Full constructor
Beam::Beam(double X, double Y)
{
  beamX = X;
  beamY = Y;
}

//==============================================================================
// Public member functions
//==============================================================================

// Getters
double Beam::GetX()
{
  return beamX;
}
double Beam::GetY()
{
  return beamY;
}

// Setters
void Beam::SetX(double X)
{
  beamX = X;
}
void Beam::SetY(double Y)
{
  beamY = Y;
}
