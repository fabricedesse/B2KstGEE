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
  Int_t z_VELO[2*nb_VELO_station];
  // left stations
    // central stations
    z_VELO[0]=-175;
    z_VELO[2]=-145;
    z_VELO[4]=-115;
    z_VELO[6]=-85;
    z_VELO[8]=-55;
    z_VELO[10]=-25;
    z_VELO[12]=5;
    z_VELO[14]=35;
    z_VELO[16]=65;
    z_VELO[18]=95;
    z_VELO[20]=125;
    z_VELO[22]=155;
    z_VELO[24]=185;
    z_VELO[26]=215;
    z_VELO[28]=245;
    z_VELO[30]=275;
    // low angle stations
    z_VELO[32]=435;
    z_VELO[34]=585;
    z_VELO[36]=635;
    z_VELO[38]=685;
    z_VELO[40]=735;
  // right stations
    // central stations
    z_VELO[1]=-160;
    z_VELO[3]=-130;
    z_VELO[5]=-100;
    z_VELO[7]=-70;
    z_VELO[9]=-40;
    z_VELO[11]=-10;
    z_VELO[13]=20;
    z_VELO[15]=50;
    z_VELO[17]=80;
    z_VELO[19]=110;
    z_VELO[21]=140;
    z_VELO[23]=170;
    z_VELO[25]=200;
    z_VELO[27]=230;
    z_VELO[29]=260;
    z_VELO[31]=290;
    // low angle stations
    z_VELO[33]=450;
    z_VELO[35]=600;
    z_VELO[37]=650;
    z_VELO[39]=700;
    z_VELO[41]=750;

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
