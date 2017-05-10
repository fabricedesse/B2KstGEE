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
#include<iostream>
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "Q2Bin.h"
#include "TMath.h"

using namespace std;

class Sample
{
  public:

  enum class DecayType {LPT, MC_KstEE, MC_KstGEE, MC_KstJPsEE};

  //============================================================================
  // Constructor
  //============================================================================

  // Generic constructor
  Sample();

  // Full constructor
  Sample(TString fileName, TString treeName, bool isMC, Sample::DecayType type);

  //============================================================================
  // Public member functions
  //============================================================================

  // Getters
  TString GetFileName();
  TString GetTreeName();
  bool IsMC();
  Sample::DecayType GetType();
  TFile* GetFile();
  TTree* GetTree();

  // Tree initializer

  void MakePreselection( TFile* newFile, Q2Bin* myQ2Bin, TString triggerCat = "" );

  //============================================================================
  // Private attributes
  //============================================================================
  private:

  TString sample_fileName;
  TString sample_treeName;
  bool sample_isMC;
  Sample::DecayType sample_type;
  TTree* sample_tree;
  TFile* sample_file;
};

#endif
