//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Get z coordinates of the VELO station
//
// Output: text file with z coordinates of the VELO stations
//
// Inputs:
// TString input_file
// TString input_tree
//
//==============================================================================

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void get_VELO_stations( TString input_file, TString input_tree)
{
  TFile *f = new TFile(input_file,"read");
  TTree *T = (TTree*)f->Get(input_tree);

  Double_t z_position;

  T->SetBranchAddress("E1_TRACK_FirstMeasurementZ", &z_position);

  std::vector<double> stations;

  int nentries = (int)T->GetEntries();

  // Loop over z first measurement, add them to the stations vector only if they
  // are not already in it.
  for (int i = 0; i < nentries; i++)
  {
    T->GetEntry(i);

    if (std::find(stations.begin(),stations.end(), z_position) == stations.end())
    {
      stations.push_back(z_position);
    }
  }

  // Sort the stations
  std::sort(stations.begin(), stations.end());

  // Write stations in txt file
  ofstream myFile ("VELO_stations.txt");
  if (myFile.is_open())
  {
    /*for (vector<double>::const_iterator i = stations.begin();
          i != stations.end(); i++)
          {
            //myFile << "a line. \n";
            myFile << "\t\t" << "0" << ", " << stations.at(i) << "\n";
          }
          */
    copy(stations.begin(), stations.end(), ostream_iterator<double>(myFile,"\n"));
    myFile.close();

  }
  else cout << "Unable to open file";
}
