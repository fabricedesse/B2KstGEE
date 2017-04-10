//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class Station: station of the VELO
//
//==============================================================================

#ifndef Station_h
#define Station_h

#include "TVector2.h"

class Station {

public:
//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
Station();

// Full constructor
Station(int number, double z_position, bool isLeft,
        double min_r = 8.2, double max_r = 49.1) ;

//==============================================================================
// Public member functions
//==============================================================================

// Getters
int GetNumber();
double GetZ();
bool IsLeft();

// Setters
void Set(int number, double z, bool isLeft);
void SetNumber(int number);
void SetZ(double z);
void SetIsLeft(bool isLeft);

// Other
bool IsInAcceptance(TVector2 XY);

//==============================================================================
// Private attributes
//==============================================================================
private:
int station_number;
double station_z;
bool station_isLeft;
double min_radius;
double max_radius;

};

#endif
