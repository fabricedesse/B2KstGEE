//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-10
//
// Geometry of the VELO
//
//==============================================================================

#ifndef CalorimeterConstants_h
#define CalorimeterConstants_h

#include "TVector2.h"

double* VELO_left();
double* VELO_right();

bool isInAcceptance(TVector2 XY, bool makeTriangle);

namespace VELO_geo
{
  //Beam Position
  static double beamX = 0.6;
  static double beamY = 0.;

  //Triangle
  static double triangle_height = 2.5;
  static double triangle_baseY = 7.5;
  static double triangle_baseLength = 2.5;
}

#endif
