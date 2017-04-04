//File Edit Options Buffers Tools C++ Help                                                                                                                                                                     
#include<iostream>
using namespace std;
void addFMvariables(TString name)
{
  
  TFile* newFile = new TFile(name, "UPDATE");
  TTree *newTree = (TTree*)newFile->Get("DecayTree");
  cout << "Number of events: " << newTree->GetEntries() ;
  
  
  ULong64_t eventNumber;
  Double_t kstarZ;
  Double_t kstarY;
  Double_t kstarX;
  Double_t l1pX;
  Double_t l2pX;
  Double_t l1pY;
  Double_t l2pY;
  Double_t l1pZ;
  Double_t l2pZ;
  Double_t l1p;
  Double_t l2p;
  Double_t l1pE;
  Double_t l2pE;
  Double_t l1M;
  Double_t l2M;
  Int_t l1ID;
  Int_t l2ID;


  newTree->SetBranchAddress("eventNumber" ,&eventNumber);
  newTree->SetBranchAddress("Kstar_ENDVERTEX_Z" ,&kstarZ);
  newTree->SetBranchAddress("Kstar_ENDVERTEX_Y" ,&kstarY);
  newTree->SetBranchAddress("Kstar_ENDVERTEX_X" ,&kstarX);
  newTree->SetBranchAddress("L1_PX" ,&l1pX);
  newTree->SetBranchAddress("L2_PX" ,&l2pX);
  newTree->SetBranchAddress("L1_PY" ,&l1pY);
  newTree->SetBranchAddress("L2_PY" ,&l2pY);
  newTree->SetBranchAddress("L1_PZ" ,&l1pZ);
  newTree->SetBranchAddress("L2_PZ" ,&l2pZ);
  newTree->SetBranchAddress("L1_PE" ,&l1pE);
  newTree->SetBranchAddress("L2_PE" ,&l2pE);
  newTree->SetBranchAddress("L1_P" ,&l1p);
  newTree->SetBranchAddress("L2_P" ,&l2p);
  newTree->SetBranchAddress("L1_ID" ,&l1ID);
  newTree->SetBranchAddress("L2_ID" ,&l2ID);
  newTree->SetBranchAddress("L1_M" ,&l1M);
  newTree->SetBranchAddress("L2_M" ,&l2M);
  


  Float_t Expl1FirstMeasurementZ;
  Float_t Expl2FirstMeasurementZ;
  Double_t t=-1000;
  Double_t x=-1000;
  Double_t y=-1000;
  Double_t t2=-1000;
  Double_t x2=-1000;
  Double_t y2=-1000;
  Double_t l2t=-1000;
  Double_t l2x=-1000;
  Double_t l2y=-1000;
  Double_t l2t2=-1000;
  Double_t l2x2=-1000;
  Double_t l2y2=-1000;

  Float_t emass=0;
  Float_t epx=0;
  Float_t epy=0;
  Float_t epz=0;
  Float_t epe=0;
  Float_t ep=0;
  Float_t pmass=0;
  Float_t ppx=0;
  Float_t ppy=0;
  Float_t ppz=0;
  Float_t ppe=0;
  Float_t pp=0;




  // z-positions of velo stations
Int_t z[42];
  z[0]=-176;
  z[1]=-174.5;
  z[2]=-146; 
  z[3]=-144;
  z[4]=-116; 
  z[5]=-114;
  z[6]=-86;
  z[7]=-84;
  z[8]=-56;
  z[9]=-54;
  z[10]=-26; 
  z[11]=-24;
  z[12]=4;
  z[13]=6;
  z[14]=34;
  z[15]=36;
  z[16]=64;
  z[17]=66;
  z[18]=94;
  z[19]=95.5;
  z[20]=124; 
  z[21]=125.5;
  z[22]=154;
  z[23]=155.5;
  z[24]=184;
  z[25]=186;
  z[26]=214;
  z[27]=216;
  z[28]=244;
  z[29]=246;
  z[30]=274; 
  z[31]=275.5;
  z[32]=434;
  z[33]=436;
  z[34]=584;
  z[35]=586;
  z[36]=634;
  z[37]=636;
  z[38]=684;
  z[39]=686;
  z[40]=734;
  z[41]=736;
 
  Int_t z2[42];
 
  z2[0]=-161; 
  z2[1]=-159;
  z2[2]=-131; 
  z2[3]=-129;
  z2[4]=-101; 
  z2[5]=-99;
  z2[6]=-70.5;
  z2[7]=-69;
  z2[8]=-41;
  z2[9]=-39;
  z2[10]=-11;
  z2[11]=-9;
  z2[12]=19;
  z2[13]=21;
  z2[14]=49; 
  z2[15]=51;
  z2[16]=79;
  z2[17]=81;
  z2[18]=109;
  z2[19]=111;
  z2[20]=139;
  z2[21]=141;
  z2[22]=169;
  z2[23]=171;
  z2[24]=199; 
  z2[25]=201;
  z2[26]=229;
  z2[27]=231;
  z2[28]=259;
  z2[29]=260.5;
  z2[30]=289;
  z2[31]=291;
  z2[32]=449;
  z2[33]=451;
  z2[34]=599; 
  z2[35]=601;
  z2[36]=649;
  z2[37]=650.5;
  z2[38]=699;
  z2[39]=701;
  z2[40]=749;
  z2[41]=751;



  Int_t signumberOfEntries = newTree->GetEntries();

  TBranch *newbranch1 = newTree->Branch("Expl2FirstMeasurementZ", &Expl2FirstMeasurementZ, "Expl2FirstMeasurementZ");
  TBranch *newbranch2 = newTree->Branch("Expl1FirstMeasurementZ", &Expl1FirstMeasurementZ, "Expl1FirstMeasurementZ");


  for (Int_t loopie=0; loopie < signumberOfEntries; ++loopie)
  {
    newTree->GetEntry(loopie); 
    Expl1FirstMeasurementZ=-1000;
    Expl2FirstMeasurementZ=-1000;
    

    for(Int_t i=0; i<42; ++i) 
    {
      
      t=((z[i]-kstarZ)/l1pZ);
      y=(kstarY+t*l1pY);
      x=(kstarX+t*l1pX);
      
      t2=((z2[i]-kstarZ)/l1pZ);
      y2=(kstarY+t2*l1pY);
      x2=(kstarX+t2*l1pX); 
      
      if(t>0 && x>0 && sqrt((x)*(x)+(y)*(y))>8.2 && sqrt((x)*(x)+(y)*(y))<41.9)
      {Expl1FirstMeasurementZ=z[i];
        break;
      } 
      
      if(t2>0 && x2<0 && sqrt((x2)*(x2)+(y2)*(y2))>8.2 && sqrt((x2)*(x2)+(y2)*(y2))<41.9)
      {Expl1FirstMeasurementZ=z2[i];
        break;
      } 
    }  
    
    for(Int_t j=0; j<42; ++j) 
    {
      
      l2t=((z[j]-kstarZ)/l2pZ);
      l2y=(kstarY+l2t*l2pY);
      l2x=(kstarX+l2t*l2pX);
      
      l2t2=((z2[j]-kstarZ)/l2pZ);
      l2y2=(kstarY+l2t2*l2pY);
      l2x2=(kstarX+l2t2*l2pX); 
      
      
      if(l2t>0 && l2x>0 && sqrt((l2x)*(l2x)+(l2y)*(l2y))>8.2 && sqrt((l2x)*(l2x)+(l2y)*(l2y))<41.9)
      {Expl2FirstMeasurementZ=z[j];
        break;
      } 
      
      if(l2t2>0 && l2x2<0 && sqrt((l2x2)*(l2x2)+(l2y2)*(l2y2))>8.2 && sqrt((l2x2)*(l2x2)+(l2y2)*(l2y2))<41.9)  
      {Expl2FirstMeasurementZ=z2[j];
        break;
      } 
    }
   if(l1ID==11){
      emass=l1M;
      epx=l1pX;
      epy=l1pY;
      epz=l1pZ;
      epe=l1pE;
      ep=l1p;
      pmass=l2M;
      ppx=l2pX;
      ppy=l2pY;
      ppz=l2pZ;
      ppe=l2pE;
      pp=l2p;
    }
    if(l2ID==11){
      emass=l2M;
      epx=l2pX;
      epy=l2pY;
      epz=l2pZ;
      epe=l2pE;
      ep=l2p;
      pmass=l1M;
      ppx=l1pX;
      ppy=l1pY;
      ppz=l1pZ;
      ppe=l1pE;  
      pp=l1p;
    }
    newbranch1->Fill();
    newbranch2->Fill();
  }
  newTree->Write();      
  newFile->Write();  
  cout << "  new Number of events: " << newTree->GetEntries()<< endl ;
}
