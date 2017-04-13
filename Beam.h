//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-13
//
// Beam of the LHC
//
//==============================================================================

#ifndef Beam_h
#define Beam_h

class Beam
{
  public:
  //==============================================================================
  // Constructur & Destructor
  //==============================================================================

  // Default constructor
  Beam();

  // Full constructor
  Beam(double X, double Y);

  //==============================================================================
  // Public member functions
  //==============================================================================

  // Getters
  double GetX();
  double GetY();

  // Setters
  void SetX(double X);
  void SetY(double Y);

  //==============================================================================
  // Private attributes
  //==============================================================================
  private:
  double beamX;
  double beamY;
};

#endif
