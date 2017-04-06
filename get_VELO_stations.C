//==============================================================================
// Author: Fabrice Desse
//
// Date: 2016-04-05
//
// Get z coordinates of the VELO station
//
// Output: z_ccordinates.txt text file with z coordinates of the VELO stations
//
// Inputs: None
//
//==============================================================================


TFile *f = new TFile(input_file,"read");
TTree *T = (TTree*)f->Get(input_tree);
