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
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "Q2Bin.h"

using namespace std;

class Sample
{
  public:

  enum class DecayType {KstEE, KstGEE, KstJPsEE};

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

  void Preselection( &Q2Bin myQ2Bin );

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
