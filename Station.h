#ifndef Station_h
#define Station_h

class Station {

public:
//==============================================================================
// Constructur & Destructor
//==============================================================================

// Default constructor
Station();
// Destructor
~Station();
// Full constructor
Station(Int_t station_number, Double_t z_position, Bool_t isLeft) ;

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Int_t GetNumber();
Double_t GetZ();
Bool_t IsLeft();

// Setters
void SetNumber(Int_t station_number);
void SetZ(Double_t z);
void SetIsLeft(Bool_t isLeft);

//==============================================================================
// Private attributes
//==============================================================================
private:
Int_t station_number;
Double_t z_position;
Bool_t isLeft;

};

#endif
