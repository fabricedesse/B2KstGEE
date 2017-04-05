#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TVector2.h"

using namespace std;

Double_t get_exp_firstMeasurementZ(Double_t PX, Double_t PY, Double_t PZ,
  Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y,
  Double_t mother_ENDVERTEX_Z)
{
  //============================================================================
  // z-positions of velo stations (in mm). (0,0,0) is the position of the pp
  // interaction
  //============================================================================
  // CHECK VALUES in TUPLES
  Int_t nb_VELO_station = 21;
  Int_t z_VELO_left[nb_VELO_station];
  Int_t z_VELO_right[nb_VELO_station];
  // left stations (x > 0)
    // central stations
    z_VELO_left[0]=-175;
    z_VELO_left[1]=-145;
    z_VELO_left[2]=-115;
    z_VELO_left[3]=-85;
    z_VELO_left[4]=-55;
    z_VELO_left[5]=-25;
    z_VELO_left[6]=5;
    z_VELO_left[7]=35;
    z_VELO_left[8]=65;
    z_VELO_left[9]=95;
    z_VELO_left[10]=125;
    z_VELO_left[11]=155;
    z_VELO_left[12]=185;
    z_VELO_left[13]=215;
    z_VELO_left[14]=245;
    z_VELO_left[15]=275;
    // low angle stations
    z_VELO_left[16]=435;
    z_VELO_left[17]=585;
    z_VELO_left[18]=635;
    z_VELO_left[19]=685;
    z_VELO_left[20]=735;
  // right stations
    // central stations
    z_VELO_right[1]=-160;
    z_VELO_right[3]=-130;
    z_VELO_right[5]=-100;
    z_VELO_right[7]=-70;
    z_VELO_right[9]=-40;
    z_VELO_right[11]=-10;
    z_VELO_right[13]=20;
    z_VELO_right[15]=50;
    z_VELO_right[17]=80;
    z_VELO_right[19]=110;
    z_VELO_right[21]=140;
    z_VELO_right[23]=170;
    z_VELO_right[25]=200;
    z_VELO_right[27]=230;
    z_VELO_right[29]=260;
    z_VELO_right[31]=290;
    // low angle stations
    z_VELO_right[33]=450;
    z_VELO_right[35]=600;
    z_VELO_right[37]=650;
    z_VELO_right[39]=700;
    z_VELO_right[41]=750;

  //============================================================================
  // Calculate expected first measurement in z if the particle originates from
  // the vertex of the input mother
  //============================================================================

  Double_t exp_FirstMeasurementZ = -1000;

  for ( Int_t i = 0; i < nb_VELO_station; i++ )
  {
    // Extrapolate x and y for all VELO positions upstream of the mother
    // z position
    if ( ( z_VELO[i] - mother_ENDVERTEX_Z ) >= 0 )
    {
      Double_t exp_x = mother_ENDVERTEX_X
        + ( PX/PZ ) * ( z_VELO[i] - mother_ENDVERTEX_Z ) ;
      Double_t exp_y = mother_ENDVERTEX_Y
        + ( PY/PZ ) * ( z_VELO[i] - mother_ENDVERTEX_Z ) ;

      TVector2 XY(exp_x,exp_y);

      // If (x,y) is in the VELO acceptance this is the expected first
      // measurement in z
      if ( XY.Mod() > 8.2 && XY.Mod() < 41.9 )
      {
        exp_FirstMeasurementZ = z_VELO[i] ;
      }
    }
  }

return exp_FirstMeasurementZ ;

}
