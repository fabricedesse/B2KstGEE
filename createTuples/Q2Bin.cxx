//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Implementation file for class : Q2Bin
//
//==============================================================================

#include "Q2Bin.h"

//============================================================================
// Constructor
//============================================================================

// Generic constructor
Q2Bin::Q2Bin()
{

}

// Full constructor
Q2Bin::Q2Bin(double q2Min, double q2Max, double HOP, double HOPlog, double wNB, double B0_PV_M_min, double B0_PV_M_max)
{
  q2Bin_q2Min = q2Min;
  q2Bin_q2Max = q2Max;
  q2Bin_HOP = HOP;
  q2Bin_HOPlog = HOPlog;
  q2Bin_wNB = wNB;
  q2Bin_B0_PV_M_min = B0_PV_M_min;
  q2Bin_B0_PV_M_max = B0_PV_M_max;
}

//============================================================================
// Public member functions
//============================================================================

// Getters
double Q2Bin::GetQ2Min()
{
  return q2Bin_q2Min;
}

double Q2Bin::GetQ2Max()
{
  return q2Bin_q2Max;
}

double Q2Bin::GetHOP()
{
  return q2Bin_HOP;
}

double Q2Bin::GetHOPlog()
{
  return q2Bin_HOPlog;
}

double Q2Bin::GetwNB()
{
  return q2Bin_wNB;
}

double Q2Bin::GetB0_PV_M_min()
{
  return q2Bin_B0_PV_M_min;
}

double Q2Bin::GetB0_PV_M_max()
{
  return q2Bin_B0_PV_M_max;
}
