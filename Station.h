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

class Station {

public:
//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
Station();

// Full constructor
Station(int number, double z_position, bool isLeft) ;

//==============================================================================
// Public member functions
//==============================================================================

// Getters
int GetNumber();
double GetZ();
bool IsLeft();

// Setters
void SetNumber(int number);
void SetZ(double z);
void SetIsLeft(bool isLeft);

//==============================================================================
// Private attributes
//==============================================================================
private:
int station_number;
double station_z;
bool station_isLeft;

};

#endif
