//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Initializes the VELO with its stations
//
//==============================================================================

#include <stdlib.h>

#include "VELO.h"
#include "Station.h"
#include "create_tree.h"
#include "make_plots.h"
#include "plot_cut.h"
#include "Sample.h"
#include "Q2Bin.h"

using namespace std;

typedef std::vector<Sample>::iterator SampleIterator;
typedef std::vector<TString>::iterator TStringIterator;

int main()
{

  //============================================================================
  // Construct samples
  //============================================================================

  // Init path
  TString pathToData = "/sps/lhcb/fdesse/tuples_B2KstGEE/";
  TString pathToRKst = pathToData+"RKst_tuples/";
  TString pathToConv = pathToData+"conversion_tuples/";
  TString rawFile = pathToData+"raw_tuples/Raw.root";

  // Init KstEE, KstGEE samples
  Sample Bd2KstGEE( rawFile, "Bd2KstGEE", Sample::DecayType::MC_KstGEE );
  Sample Bd2KstEE( rawFile, "Bd2KstEE", Sample::DecayType::MC_KstEE );
  Sample data_KstEE( rawFile, "LPT", Sample::DecayType::data_KstEE );
  std::vector<Sample> KstEE_samples;
  KstEE_samples.push_back( Bd2KstGEE );
  KstEE_samples.push_back( Bd2KstEE );
  KstEE_samples.push_back( data_KstEE );

  // Init KstJPsEE samples
  Sample Bd2KstJPsEE( rawFile, "Bd2KstJPsEE", Sample::DecayType::MC_KstJPsEE );
  Sample data_JPs( rawFile, "LPT", Sample::DecayType::data_KstJPsEE );
  std::vector<Sample> KstJPsEE_samples;
  KstJPsEE_samples.push_back( Bd2KstJPsEE );
  KstJPsEE_samples.push_back( data_JPs );

  // Init triggerCat
  std::vector<TString> triggerCats;
  triggerCats.push_back("");
  triggerCats.push_back("L0L");
  triggerCats.push_back("L0H");
  triggerCats.push_back("L0I");

  //============================================================================
  // Create tuples
  //============================================================================

  // Gamma
  // std::cout << "########## Create tuples Gamma ##########" << std::endl;
  // TFile fGamma(pathToConv+"EE_candidates_gamma_20170511.root", "RECREATE");
  // Q2Bin gamma( 0, .0004 , 3350, 135, 0.49, 4500, 6200 );
  // for ( SampleIterator mySample = KstEE_samples.begin(); mySample != KstEE_samples.end(); mySample++ )
  // {
  //   for ( TStringIterator myTriggerCat = triggerCats.begin(); myTriggerCat != triggerCats.end(); myTriggerCat++ )
  //   {
  //     mySample->MakePreselection( &fGamma, &gamma, *myTriggerCat );
  //   }
  // }
  // std::cout<<std::endl;
  //
  // // Low
  // std::cout << "########## Create tuples Low ##########" << std::endl;
  // TFile fLow(pathToConv+"EE_candidates_low_20170511.root", "RECREATE");
  // Q2Bin low( .0004, 1.1, 5072, 1, 0.95, 4500, 6200 );
  // for ( SampleIterator mySample = KstEE_samples.begin(); mySample != KstEE_samples.end(); mySample++ )
  // {
  //   for ( TStringIterator myTriggerCat = triggerCats.begin(); myTriggerCat != triggerCats.end(); myTriggerCat++ )
  //   {
  //     mySample->MakePreselection( &fLow, &low, *myTriggerCat );
  //   }
  // }
  // std::cout<<std::endl;
  //
  // // Central
  // std::cout << "########## Create tuples Central ##########" << std::endl;
  // TFile fCentral(pathToConv+"EE_candidates_central_20170511.root", "RECREATE");
  // Q2Bin central( 1.1, 6, 4926, 10, 0.99, 4500, 6200 );
  // for ( SampleIterator mySample = KstEE_samples.begin(); mySample != KstEE_samples.end(); mySample++ )
  // {
  //   for ( TStringIterator myTriggerCat = triggerCats.begin(); myTriggerCat != triggerCats.end(); myTriggerCat++ )
  //   {
  //     mySample->MakePreselection( &fCentral, &central, *myTriggerCat );
  //   }
  // }
  // std::cout<<std::endl;

  // JPs
  std::cout << "########## Create tuples JPs ##########" << std::endl;
  TFile fJPs(pathToConv+"EE_candidates_jps_20170511.root", "RECREATE");
  Q2Bin jps( 6, 11, 0, 0, 0.33, 5150, 5850 );
  for ( SampleIterator mySample = KstJPsEE_samples.begin(); mySample != KstJPsEE_samples.end(); mySample++ )
  {
    for ( TStringIterator myTriggerCat = triggerCats.begin(); myTriggerCat != triggerCats.end(); myTriggerCat++ )
    {
      mySample->MakePreselection( &fJPs, &jps, *myTriggerCat );
    }
  }
  std::cout<<std::endl;

  // Test add branch
  // Sample Bd2KstGEE_conv( pathToConv+"EE_candidates_gamma_20170511.root", "Bd2KstGEE", Sample::DecayType::MC_KstGEE );
  // Sample
  //
  // Bd2KstGEE_conv.AddConversionBranches();

  //============================================================================
  // Create trees (old probably to be removed later)
  //============================================================================

  // create_tree_MC(pathToData+"EE_candidates_gamma_20160928.root", "Bd2KstGEE",pathToData+"MCGEE_TRACKZ.root");
  // create_tree_MC(pathToData+"/EE_candidates_jps.root", "Bd2KstJPsEE",pathToData+"MCJPsEE_TRACKZ.root");
  // create_tree_MC(pathToData+"EE_candidates_gamma_20160928.root", "Bd2KstEE",pathToData+"MCEE_TRACKZ.root");
  //
  // create_tree_MC(pathToData+"/EE_candidates_low_20160606.root", "Bd2KstGEE", "../data/MCGEE_low.root");
  //
  // create_tree_JPs(pathToData+"/EE_candidates_jps.root", "KstJPsEE", pathToData+"/JPsEE_massCut.root");

  // Make plots

  // make_plots_MC(pathToConv+"EE_candidates_gamma_20170511.root", "Bd2KstGEE", "MC_GEE");
  // make_plots_MC(pathToConv+"EE_candidates_gamma_20170511.root", "Bd2KstEE", "MC_EE");
  // make_plots_MC(pathToConv+"EE_candidates_jps_20170511.root", "Bd2KstJPsEE", "MC_JPsEE");
  // make_plots_data(pathToConv+"EE_candidates_jps_20170511.root", "data", "JPsEE");

  // Make efficiency plots
  // plot_cut();

  cout << "Main is done." << endl;
}
