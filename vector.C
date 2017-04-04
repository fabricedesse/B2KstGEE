#include "TVector3.h"
#include <iostream>
#include "TMath.h"

void test_vector() {

// Create random vectors
TVector3 v0(1,0,2);
TVector3 v1(32,8,5);
TVector3 v2(0.5,-23,5);
TVector3 v3(67,876,0);

// use formula girl
Double_t x0_increment = v0.X()/v0.Z();
Double_t x1_increment = v1.X()/v1.Z();
Double_t x2_increment = v2.X()/v2.Z();
Double_t x3_increment = v3.X()/v3.Z();

// use my formula
Double_t x0_increment_TRUE = v0.Unit().X()*v0.Mag()/v0.Z();
Double_t x1_increment_TRUE = v1.Unit().X()*v1.Mag()/v1.Z();
Double_t x2_increment_TRUE = v2.Unit().X()*v2.Mag()/v2.Z();
Double_t x3_increment_TRUE = v3.Unit().X()*v3.Mag()/v3.Z();

cout<< "x0_increment = " << x0_increment << endl
    << "x0_increment_TRUE = " << x0_increment_TRUE << endl
    << "x1_increment = " << x1_increment << endl
    << "x1_increment_TRUE = " << x1_increment_TRUE << endl
    << "x2_increment = " << x2_increment << endl
    << "x2_increment_TRUE = " << x2_increment_TRUE << endl
    << "x3_increment = " << x3_increment << endl
    << "x3_increment_TRUE = " << x3_increment_TRUE << endl
    << "master version" << endl;




}
