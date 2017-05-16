//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-05-16
//
// Utility functions usable in all C files.
//
//==============================================================================

#ifndef UTILITY_H
#define UTILITY_H

#include "TString.h"
#include "Sample.h"

// Standalone functions
static TString GetTreeNameFromType( Sample::DecayType myDecayType, Sample::TriggerCat myTriggerCat )
{
  // Construct tree name
  TString myTreeName = "";

  switch(myDecayType)
  {
    case Sample::DecayType::MC_KstGEE:
      myTreeName = "Bd2KstGEE";
      break;

    case Sample::DecayType::MC_KstEE:
      myTreeName = "Bd2KstEE";
      break;

    case Sample::DecayType::data_KstEE:
      myTreeName = "data";
      break;

    case Sample::DecayType::data_KstJPsEE:
      myTreeName = "data";
      break;

    case Sample::DecayType::MC_KstJPsEE:
      myTreeName = "Bd2KstJPsEE";
      break;
  }

  switch(myTriggerCat)
  {
    case Sample::TriggerCat::all:
      break;

    case Sample::TriggerCat::L0L:
      myTreeName = myTreeName+"_L0L";
      break;

    case Sample::TriggerCat::L0H:
      myTreeName = myTreeName+"_L0H";
      break;

    case Sample::TriggerCat::L0I:
      myTreeName = myTreeName+"_L0I";
      break;
  }

  return myTreeName;
}

#endif
