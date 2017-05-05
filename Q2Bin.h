//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class : Q2Bin
//
//==============================================================================

#ifndef Q2BIN_H
#define Q2BIN_H

class Q2Bin
{
  public:
  //============================================================================
  // Constructor
  //============================================================================

  // Generic constructor
  Q2Bin();

  // Full constructor
  Q2Bin(double q2Min, double q2Max, double HOP, double HOPlog, double wNB, double B0_PV_M_min, double B0_PV_M_max);

  //============================================================================
  // Public member functions
  //============================================================================

  // Getters
  double GetQ2Min();
  double GetQ2Max();
  double GetHOP();
  double GetHOPlog();
  double GetwNB();
  double GetB0_PV_M_min();
  double GetB0_PV_M_max();

  //============================================================================
  // Private attributes
  //============================================================================
  private:
  double q2Bin_q2Min;
  double q2Bin_q2Max;
  double q2Bin_HOP;
  double q2Bin_HOPlog;
  double q2Bin_wNB;
  double q2Bin_B0_PV_M_min;
  double q2Bin_B0_PV_M_max;
};

#endif
