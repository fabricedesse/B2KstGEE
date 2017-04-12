//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-10
//
// Geometry of the VELO
//
//==============================================================================

#include "VELO_geometry.h"

using namespace VELO_geo;

// Right stations
double *VELO_left()
{
  static double VELO_l[42];
  VELO_l[0]=-176;
  VELO_l[1]=-174.5;
  VELO_l[2]=-146;
  VELO_l[3]=-144;
  VELO_l[4]=-115.809;
  VELO_l[5]=-113.667;
  VELO_l[6]=-85.8839;
  VELO_l[7]=-83.7419;
  VELO_l[8]=-55.6655;
  VELO_l[9]=-53.5235;
  VELO_l[10]=-25.9345;
  VELO_l[11]=-23.7925;
  VELO_l[12]=4.2253;
  VELO_l[13]=6.3674;
  VELO_l[14]=34.218;
  VELO_l[15]=36.36;
  VELO_l[16]=64.3343;
  VELO_l[17]=66.4763;
  VELO_l[18]=93.8843;
  VELO_l[19]=96.0263;
  VELO_l[20]=123.999;
  VELO_l[21]=126.141;
  VELO_l[22]=153.907;
  VELO_l[23]=156.049;
  VELO_l[24]=184.186;
  VELO_l[25]=186.328;
  VELO_l[26]=214.124;
  VELO_l[27]=216.266;
  VELO_l[28]=244.122;
  VELO_l[29]=246.264;
  VELO_l[30]=273.963;
  VELO_l[31]=276.105;
  VELO_l[32]=434.167;
  VELO_l[33]=436.309;
  VELO_l[34]=584.207;
  VELO_l[35]=586.349;
  VELO_l[36]=634.372;
  VELO_l[37]=636;
  VELO_l[38]=684;
  VELO_l[39]=686;
  VELO_l[40]=734;
  VELO_l[41]=736;

  return VELO_l;
}

// Left stations
double *VELO_right()
{
  static double VELO_r[42];
  VELO_r[0]=-161;
  VELO_r[1]=-159;
  VELO_r[2]=-130.753;
  VELO_r[3]=-129;
  VELO_r[4]=-100.971;
  VELO_r[5]=-98.8293;
  VELO_r[6]=-70.6055;
  VELO_r[7]=-68.4635;
  VELO_r[8]=-40.8544;
  VELO_r[9]=-38.7124;
  VELO_r[10]=-10.7414;
  VELO_r[11]=-8.5994;
  VELO_r[12]=19.1023;
  VELO_r[13]=21.2443;
  VELO_r[14]=49.1997;
  VELO_r[15]=51.3417;
  VELO_r[16]=79.2572;
  VELO_r[17]=81.3992;
  VELO_r[18]=109.29;
  VELO_r[19]=111.432;
  VELO_r[20]=139.154;
  VELO_r[21]=141.296;
  VELO_r[22]=169.325;
  VELO_r[23]=171.467;
  VELO_r[24]=198.977;
  VELO_r[25]=201.119;
  VELO_r[26]=229.139;
  VELO_r[27]=231.281;
  VELO_r[28]=258.88;
  VELO_r[29]=261.022;
  VELO_r[30]=289.07;
  VELO_r[31]=291.212;
  VELO_r[32]=449.004;
  VELO_r[33]=451.146;
  VELO_r[34]=599.137;
  VELO_r[35]=601.279;
  VELO_r[36]=648.913;
  VELO_r[37]=650.5;
  VELO_r[38]=699;
  VELO_r[39]=701;
  VELO_r[40]=749;
  VELO_r[41]=751;

  return VELO_r;
}

// Geometry of each station
bool isInAcceptance(TVector2 XY)
{
  // Rescale center (0,0) to (beamX,beamY)
  //TVector2 XYbeam = 
  if ( XY.Mod() < 8.2 || XY.Mod() > 49.1 ) return false;
  // triangle
  else if ( XY.X() > beamX - triangle_baseLength
            && XY.X() < beamX + triangle_baseLength )
  {
    // right triangle
    if ( XY.X() <= beamX )
    {
      // lower triangle
      if ( XY.Y() > beamY
           && XY.Y() < triangle_height/triangle_baseLength*XY.X()
           + beamY+triangle_baseY+triangle_height )
      {
        return false;
      }
      // upper triangle
      if ( XY.Y() < beamY
           && XY.Y() > -triangle_height/triangle_baseLength*XY.X()
           + beamY-triangle_baseY-triangle_height )
      {
        return false;
      }
      else return true;
    }
    // left triangle
    else
    {
      // lower triangle
      if ( XY.Y() > beamY
           && XY.Y() < -triangle_height/triangle_baseLength*XY.X()
           + beamY+triangle_baseY+triangle_height )
      {
        return false;
      }
      //upper triangle
      if ( XY.Y() < beamY
           && XY.Y() > triangle_height/triangle_baseLength*XY.X()
           + beamY-triangle_baseY-triangle_height )
      {
        return false;
      }
      else return true;
    }
  }
  else return true;
}
