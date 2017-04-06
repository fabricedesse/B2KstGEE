#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TVector2.h"
#include "TVector3.h"
#include "VELO.h"

using namespace std;

//==============================================================================
// Functions
//==============================================================================

Double_t get_exp_firstMeasurementZ(Double_t PX, Double_t PY, Double_t PZ,
  Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y,
  Double_t mother_ENDVERTEX_Z, VELO myVELO)
{
  Double_t exp_FirstMeasurementZ = -1000;

  for ( Int_t i = 0; i < myVELO.GetNbStations(); i++ )
  {
    Station myStation = myVELO.GetStation(i);
    Double_t z_VELO = myStation.GetZ();

    // Extrapolate x and y for all VELO positions upstream of the mother
    // z position
    if ( ( z_VELO - mother_ENDVERTEX_Z ) >= 0 )
    {
      Double_t exp_x = mother_ENDVERTEX_X
        + ( PX/PZ ) * ( z_VELO - mother_ENDVERTEX_Z ) ;
      Double_t exp_y = mother_ENDVERTEX_Y
        + ( PY/PZ ) * ( z_VELO - mother_ENDVERTEX_Z ) ;

      TVector2 XY(exp_x,exp_y);
      cout << "(" << exp_x << ", " << exp_y << ")" << endl;
      // Check if (x,y) is on the left/right and if it corresponds to the
      // isLeft/isRight of the tested VELO station
      if ( ( exp_x > 0 && myStation.IsLeft() ) ||
           (exp_x < 0 && !(myStation.IsLeft() ) ) )
           {
             // If (x,y) is in the VELO acceptance this is the expected first
             // measurement in z
             if ( myStation.IsInAcceptance(XY) )
             {
               exp_FirstMeasurementZ = z_VELO;
               break;
             }
      else continue;
    }
    else continue;
  }
  return exp_FirstMeasurementZ ;
}
