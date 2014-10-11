#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

using namespace TMVA;

void TMVATrainer(){
   // This loads the library
   TMVA::Tools::Instance();

   // --- Here the preparation phase begins
   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName = "TMVATrainingResults_RecoVtx_BvsL.root";
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVATrainer_RecoVtx", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   factory->AddVariable("TagVarCSV_jetNTracks","TagVarCSV_jetNTracks","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSig_0","TagVarCSV_trackSip2dSig_0","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSig_1","TagVarCSV_trackSip2dSig_1","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSig_2","TagVarCSV_trackSip2dSig_2","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSig_3","TagVarCSV_trackSip2dSig_3","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_0","TagVarCSV_trackSip3dSig_0","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_1","TagVarCSV_trackSip3dSig_1","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_2","TagVarCSV_trackSip3dSig_2","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_3","TagVarCSV_trackSip3dSig_3","units",'F');
   factory->AddVariable("TagVarCSV_trackPtRel_0","TagVarCSV_trackPtRel_0","units",'F');
   factory->AddVariable("TagVarCSV_trackPtRel_1","TagVarCSV_trackPtRel_1","units",'F');
   factory->AddVariable("TagVarCSV_trackPtRel_2","TagVarCSV_trackPtRel_2","units",'F');
   factory->AddVariable("TagVarCSV_trackPtRel_3","TagVarCSV_trackPtRel_3","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSigAboveCharm","TagVarCSV_trackSip2dSigAboveCharm","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSigAboveCharm","TagVarCSV_trackSip3dSigAboveCharm","units",'F');
   factory->AddVariable("TagVarCSV_trackSumJetEtRatio","TagVarCSV_trackSumJetEtRatio","units",'F');
   factory->AddVariable("TagVarCSV_trackSumJetDeltaR","TagVarCSV_trackSumJetDeltaR","units",'F');
   factory->AddVariable("TagVarCSV_jetNTracksEtaRel","TagVarCSV_jetNTracksEtaRel","units",'F');
   factory->AddVariable("TagVarCSV_trackEtaRel_0","TagVarCSV_trackEtaRel_0","units",'F');
   factory->AddVariable("TagVarCSV_trackEtaRel_1","TagVarCSV_trackEtaRel_1","units",'F');
   factory->AddVariable("TagVarCSV_trackEtaRel_2","TagVarCSV_trackEtaRel_2","units",'F');
   factory->AddVariable("TagVarCSV_jetNSecondaryVertices","TagVarCSV_jetNSecondaryVertices","units",'F');
   factory->AddVariable("TagVarCSV_vertexMass","TagVarCSV_vertexMass","units",'F');
   factory->AddVariable("TagVarCSV_vertexNTracks","TagVarCSV_vertexNTracks","units",'F');
   factory->AddVariable("TagVarCSV_vertexEnergyRatio","TagVarCSV_vertexEnergyRatio","units",'F');
   factory->AddVariable("TagVarCSV_vertexJetDeltaR","TagVarCSV_vertexJetDeltaR","units",'F');
   factory->AddVariable("TagVarCSV_flightDistance2dSig","TagVarCSV_flightDistance2dSig","units",'F');
   factory->AddVariable("TagVarCSV_flightDistance3dSig","TagVarCSV_flightDistance3dSig","units",'F');

   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   factory->AddSpectator("Jet_pt","Jet_pt","units",'F');
   factory->AddSpectator("Jet_eta","Jet_eta","units",'F');
   factory->AddSpectator("Jet_phi","Jet_phi","units",'F');
   factory->AddSpectator("Jet_mass","Jet_mass","units",'F');
   factory->AddSpectator("Jet_flavour","Jet_flavour","units",'F');
   factory->AddSpectator("Jet_nbHadrons","Jet_nbHadrons","units",'F');
   factory->AddSpectator("Jet_JP","Jet_JP","units",'F');
   factory->AddSpectator("Jet_JBP","Jet_JBP","units",'F');
   factory->AddSpectator("Jet_CSV","Jet_CSV","units",'F');
   factory->AddSpectator("Jet_CSVIVF","Jet_CSVIVF","units",'F');
   factory->AddSpectator("TagVarCSV_vertexCategory","TagVarCSV_vertexCategory","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip2dValAboveCharm","TagVarCSV_trackSip2dValAboveCharm","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip3dValAboveCharm","TagVarCSV_trackSip3dValAboveCharm","units",'F');
   factory->AddSpectator("TagVarCSV_flightDistance2dVal","TagVarCSV_flightDistance2dVal","units",'F');
   factory->AddSpectator("TagVarCSV_flightDistance3dVal","TagVarCSV_flightDistance3dVal","units",'F');

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TString fname = "QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_JetTaggingVariables_training.root";
   TFile *input = TFile::Open( fname );
   
   std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;
   
   // --- Register the training and test trees
   TTree *sigTree = (TTree*)input->Get("tagVars/ttree");
   TTree *bkgTree = (TTree*)input->Get("tagVars/ttree");
   
   // // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   // factory->SetInputTrees( tree,signalCut,backgroundCut );
   factory->AddSignalTree    ( sigTree, signalWeight     );
   factory->AddBackgroundTree( bkgTree, backgroundWeight );

   // Apply additional cuts on the signal and background samples (can be different)
   TCut signalCut = "abs(Jet_flavour)==5 && TagVarCSV_vertexCategory==0";
   TCut backgroundCut = "abs(Jet_flavour)!=5 && abs(Jet_flavour)!=4 && TagVarCSV_vertexCategory==0";

   // Tell the factory how to use the training and testing events
   factory->PrepareTrainingAndTestTree( signalCut, backgroundCut,
                                        "nTrain_Background=40000:nTest_Background=39335:SplitMode=Random:!V" );

   // Gradient Boost
   factory->BookMethod( TMVA::Types::kBDT, "BDTG_T1000D3_BvsL",
                          "!H:!V:NTrees=1000:MaxDepth=3:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   factory->BookMethod( TMVA::Types::kBDT, "BDTG_T1000D5_BvsL",
                          "!H:!V:NTrees=1000:MaxDepth=5:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20" );

//    // Adaptive Boost
//    factory->BookMethod( TMVA::Types::kBDT, "BDT",
//                            "!H:!V:NTrees=1000:MaxDepth=5:MinNodeSize=2.5%:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
//    // Bagging
//    factory->BookMethod( TMVA::Types::kBDT, "BDTB",
//                            "!H:!V:NTrees=1000:MaxDepth=5:MinNodeSize=2.5%:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
//    // Decorrelation + Adaptive Boost
//    factory->BookMethod( TMVA::Types::kBDT, "BDTD",
//                            "!H:!V:NTrees=1000:MaxDepth=5:MinNodeSize=2.5%:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVAGui( outfileName );


}