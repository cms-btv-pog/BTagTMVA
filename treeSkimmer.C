// Tree skimmer originally written by Dinko Ferencek and altered by Steven Kaplan

// Takes as input a root tree produced with the RecoBTag/TagVarExtractor package
// Outputs a root tree with the same content where each entry is either b, c, or light (specified at runtime)

#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TRFIOFile.h"
#include "TLeaf.h"
#include "TBranch.h"
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include "TChain.h"

using namespace std;

bool keepJet(float _jetFlavour, const string& flavCut){

  if (flavCut == "b") return ( abs(_jetFlavour) == 5 );
  else if (flavCut == "c") return ( abs(_jetFlavour) == 4 );
  else if (flavCut == "l") return ( abs(_jetFlavour) != 5 && abs(_jetFlavour) != 4 ); 
  
}

int skim(const string& infile, const string& outname, const string& flavCut, Int_t nevts = -1){

  if (flavCut != "b" && flavCut != "c" && flavCut != "l"){
    cout << "flavor cut must be either b, c, or l" << endl;
    return 1;
  }

  if (nevts >0)
    cout << "Only considering the first " << nevts << " events!" << endl;
  TFile *oldfile = TFile::Open(infile.c_str());
  TTree *oldtree = (TTree*)oldfile->Get("tagVars/ttree");

  if(oldtree){
    cout << "Filtering file: " << infile << endl;
    cout << "Cut to be made: " << flavCut << endl;
  }
  else {
    cout << "File has no TTree: " << endl;
    return 0;
  }

  TFile *outfile = new TFile(outname.c_str(),"RECREATE","ROOT file with histograms");
  outfile->Close();

  outfile = new TFile(outname.c_str(),"UPDATE","ROOT file with histograms");

  TTree *newtree = oldtree->CloneTree(0);

  Int_t nentries = (Int_t)oldtree->GetEntries();

  float _jetFlavour;
  Int_t nEvents = 0;

  oldtree->SetBranchAddress("Jet_flavour",&_jetFlavour);
  for (Int_t i=0; i<nentries; i++){
    if (nEvents > nevts && nevts > 0) break; 
    if (i%10000 == 0) printf ("Inspecting Entry %d\n", i);

    oldtree->GetEntry(i);
    if ( keepJet(_jetFlavour,flavCut) ) newtree->Fill();
    nEvents++;
  }

  newtree->AutoSave();

  delete outfile;
  delete oldfile;

  return 0;
}
