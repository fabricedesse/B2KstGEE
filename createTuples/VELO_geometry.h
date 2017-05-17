//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-10
//
// Geometry of the VELO
//
//==============================================================================

#ifndef VELO_geometry_h
#define VELO_geometry_h

#include "TVector2.h"
#include "Beam.h"

double* VELO_left();
double* VELO_right();

bool isInAcceptance(TVector2 XY, Beam myBeam, bool makeTriangle);

namespace VELO_geo
{
  //Beam Position
  //static double beamX = 0.6;
  //static double beamY = 0.;

  // Stations carracteristics
  static double station_width = 0.3;

  //Triangle
  static double triangle_height = 2.5;
  static double triangle_baseY = 7.5;
  static double triangle_baseLength = 2.5;
}

#endif
