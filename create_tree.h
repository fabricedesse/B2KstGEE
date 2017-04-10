//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-06-05
//
// Class Station: station of the VELO
//
//==============================================================================

#ifndef create_tree_h
#define create_tree_h

#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TClass.h"
#include "TROOT.h"
#include "TBranch.h"
#include "TVector2.h"
#include "TVector3.h"
#include "VELO.h"


TVector3 get_exp_firstMeasurementZ(Double_t PX, Double_t PY, Double_t PZ,
  Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y,
  Double_t mother_ENDVERTEX_Z, VELO myVELO);


void create_tree (TString input_file, TString input_tree, TString output_file);

#endif
