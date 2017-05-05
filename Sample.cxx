//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Implementation file for class : Sample
//
//==============================================================================

#include "Sample.h"

//============================================================================
// Constructor
//============================================================================

// Generic constructor
Sample::Sample()
{

}

// Full constructor
Sample::Sample(TString fileName, TString treeName, bool isMC, Sample::DecayType type)
{
  sample_fileName = fileName;
  sample_treeName = treeName;
  sample_isMC = isMC;
  sample_type = type;
  sample_file = new TFile(fileName, "read");
  sample_tree = (TTree*) sample_file->Get(treeName);
}

//============================================================================
// Public member functions
//============================================================================

// Init

// Getters
TString Sample::GetFileName()
{
  return sample_fileName;
}

TString Sample::GetTreeName()
{
  return sample_treeName;
}

bool Sample::IsMC()
{
  return sample_isMC;
}

Sample::DecayType Sample::GetType()
{
  return sample_type;
}

TFile* Sample::GetFile()
{
  return sample_file;
}

TTree* Sample::GetTree()
{
  return sample_tree;
}
