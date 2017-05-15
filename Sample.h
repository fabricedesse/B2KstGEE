//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Class : Sample
//
//==============================================================================

#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>
#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "Q2Bin.h"
#include "TMath.h"
#include "VELO.h"
#include "Beam.h"
#include "TH1F.h"
#include "TVector3.h"

using namespace std;

TVector3 get_exp_firstMeasurement(Double_t PX, Double_t PY, Double_t PZ, Double_t mother_ENDVERTEX_X, Double_t mother_ENDVERTEX_Y, Double_t mother_ENDVERTEX_Z, VELO myVELO, Beam myBeam);

bool ConvertsBeforeStation ( TVector3 JPs_FirstVELOhit, Double_t JPs_ENDVERTEX_Z, VELO myVELO );

class Sample
{
  public:

  enum class DecayType {data_KstEE, data_KstJPsEE, MC_KstEE, MC_KstGEE, MC_KstJPsEE};

  enum class TriggerCat {all, L0L, L0H, L0I};

  //============================================================================
  // Constructor
  //============================================================================

  // Generic constructor
  Sample();

  // Full constructor
  Sample(TString fileName, TString treeName, Sample::DecayType type, Sample::TriggerCat triggerCat = Sample::TriggerCat::all );

  //============================================================================
  // Public member functions
  //============================================================================

  // Getters
  TString GetFileName();
  TString GetTreeName();
  bool IsMC();
  bool IsJPs();
  Sample::DecayType GetType();
  TFile* GetFile();
  TTree* GetTree();
  Sample::TriggerCat GetTriggerCat();

  // Tree initializer

  void MakePreselection( TFile* newFile, Q2Bin* myQ2Bin, TString triggerCat = "" );

  void AddConversionBranches( );

  //============================================================================
  // Private attributes
  //============================================================================
  private:

  TString sample_fileName;
  TString sample_treeName;
  bool sample_isMC;
  bool sample_isJPs;
  Sample::DecayType sample_type;
  Sample::TriggerCat sample_triggerCat;
  TTree* sample_tree;
  TFile* sample_file;
};

#endif
