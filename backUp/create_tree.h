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
#include "TLorentzVector.h"
#include "VELO.h"
#include "Beam.h"
#include "TH1F.h"
#include "TMath.h"


TVector3 get_exp_firstMeasurement(Double_t PX, Double_t PY, Double_t PZ, Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y, Double_t mother_ENDVERTEX_Z, VELO myVELO, Beam myBeam);

bool ConvertsBeforeStation ( TVector3 JPs_FirstVELOhit, Double_t JPs_ENDVERTEX_Z, VELO myVELO );

void create_tree_MC (TString input_file, TString input_tree, TString output_file);

void create_tree_JPs (TString input_file, TString input_tree, TString output_file);


#endif
