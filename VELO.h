#ifndef VELO_h
#define VELO_h

#include "Station.h"

class VELO {

public:
//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
VELO();
// Destructor
~VELO();
// Full constructor
VELO(Int_t nb_stations, std::vector<Station> VELO_stations) ;

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Station Get_station( Int_t station_number );
Station Get_station_of_Z( Double_t z );

// Setters
void Set_station( Int_t station_number, Station& myStation);
void Set_station_of_Z( Double_t z, Station& myStation) ;

// Functions
Add_station( Station& myStation );

//==============================================================================
// Private attributes
//==============================================================================
private:
Int_t nb_stations;
std::vector<Station> VELO_stations;

};

#endif
