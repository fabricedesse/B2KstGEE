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
#include <algorithm>

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

// Get station at position i in the vector of stations VELO_stations
Station GetStation( int i );

// Get station with station_number == station_nb
Station GetStationNb ( int station_nb );
Station GetStationAtZ( double station_Z );
int GetNbStations();

// Printers
void PrintStations();

// Others
bool IsInStations( double x, double y, double z, Beam myBeam );

//==============================================================================
// Private attributes
//==============================================================================
private:
int nb_stations;
std::vector<Station> VELO_stations;

};

#endif
