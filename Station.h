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
Station(Int_t number, Double_t z_position, Bool_t isLeft) ;

//==============================================================================
// Public member functions
//==============================================================================

// Getters
Int_t GetNumber();
Double_t GetZ();
Bool_t IsLeft();

// Setters
void SetNumber(Int_t number);
void SetZ(Double_t z);
void SetIsLeft(Bool_t isLeft);

//==============================================================================
// Private attributes
//==============================================================================
private:
Int_t station_number;
Double_t station_z;
Bool_t station_isLeft;

};

#endif
