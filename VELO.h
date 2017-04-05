#ifndef VELO_h
#define VELO_h

#include "Station.h"

#include <vector>

class VELO {

public:
//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
VELO();
// Destructor
~VELO();

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Station GetStation( Int_t station_number );

//==============================================================================
// Private attributes
//==============================================================================
private:
Int_t nb_stations;
std::vector<Station> VELO_stations;

};

#endif
