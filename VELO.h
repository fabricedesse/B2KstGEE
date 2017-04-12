//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class VELO
//
//==============================================================================

#ifndef VELO_h
#define VELO_h

#include "Station.h"
#include "VELO_geometry.h"
#include <iostream>
#include <vector>

class VELO {

public:
//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
VELO();

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Station GetStation( int station_number );
int GetNbStations();

// Printers
void PrintStations();

//==============================================================================
// Private attributes
//==============================================================================
private:
int nb_stations;
std::vector<Station> VELO_stations;

};

#endif
