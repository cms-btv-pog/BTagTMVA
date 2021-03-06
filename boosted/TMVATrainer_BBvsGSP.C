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
   TString outfileName = "TMVATrainingResults_BBvsGSP.root";
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
   TMVA::Factory *factory = new TMVA::Factory( "TMVATrainer", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

   factory->AddVariable("TagVarCSV_jetNTracks","TagVarCSV_jetNTracks","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_0","TagVarCSV_trackSip3dSig_0","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_1","TagVarCSV_trackSip3dSig_1","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_2","TagVarCSV_trackSip3dSig_2","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_3","TagVarCSV_trackSip3dSig_3","units",'F');
   //factory->AddVariable("TagVarCSV_trackSip3dSig_4","TagVarCSV_trackSip3dSig_4","units",'F');
   //factory->AddVariable("TagVarCSV_trackSip3dSig_5","TagVarCSV_trackSip3dSig_5","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSigAboveCharm","TagVarCSV_trackSip2dSigAboveCharm","units",'F');
   factory->AddVariable("TagVarCSV_trackSumJetEtRatio","TagVarCSV_trackSumJetEtRatio","units",'F');
   factory->AddVariable("TagVarCSV_trackSumJetDeltaR","TagVarCSV_trackSumJetDeltaR","units",'F');

   //factory->AddVariable("TagVarCSV1_vertexCategory","TagVarCSV1_vertexCategory","units",'F');
   factory->AddVariable("TagVarCSV1_jetNTracks","TagVarCSV1_jetNTracks","units",'F');
   factory->AddVariable("TagVarCSV1_trackSip2dSigAboveCharm","TagVarCSV1_trackSip2dSigAboveCharm","units",'F');
   factory->AddVariable("TagVarCSV1_trackSumJetEtRatio","TagVarCSV1_trackSumJetEtRatio","units",'F');
   //factory->AddVariable("TagVarCSV1_trackSumJetDeltaR","TagVarCSV1_trackSumJetDeltaR","units",'F');
   factory->AddVariable("TagVarCSV1_jetNTracksEtaRel","TagVarCSV1_jetNTracksEtaRel","units",'F');
   factory->AddVariable("TagVarCSV1_trackEtaRel_0","TagVarCSV1_trackEtaRel_0","units",'F');
   factory->AddVariable("TagVarCSV1_trackEtaRel_1","TagVarCSV1_trackEtaRel_1","units",'F');
   factory->AddVariable("TagVarCSV1_trackEtaRel_2","TagVarCSV1_trackEtaRel_2","units",'F');
   //factory->AddVariable("TagVarCSV1_jetNSecondaryVertices","TagVarCSV1_jetNSecondaryVertices","units",'F');
   factory->AddVariable("TagVarCSV1_vertexMass","TagVarCSV1_vertexMass","units",'F');
   factory->AddVariable("TagVarCSV1_vertexNTracks","TagVarCSV1_vertexNTracks","units",'F');
   factory->AddVariable("TagVarCSV1_vertexEnergyRatio","TagVarCSV1_vertexEnergyRatio","units",'F');
   factory->AddVariable("TagVarCSV1_vertexJetDeltaR","TagVarCSV1_vertexJetDeltaR","units",'F');
   factory->AddVariable("TagVarCSV1_flightDistance2dSig","TagVarCSV1_flightDistance2dSig","units",'F');

   //factory->AddVariable("TagVarCSV2_vertexCategory","TagVarCSV2_vertexCategory","units",'F');
   factory->AddVariable("TagVarCSV2_jetNTracks","TagVarCSV2_jetNTracks","units",'F');
   factory->AddVariable("TagVarCSV2_trackSip2dSigAboveCharm","TagVarCSV2_trackSip2dSigAboveCharm","units",'F');
   factory->AddVariable("TagVarCSV2_trackSumJetEtRatio","TagVarCSV2_trackSumJetEtRatio","units",'F');
   //factory->AddVariable("TagVarCSV2_trackSumJetDeltaR","TagVarCSV2_trackSumJetDeltaR","units",'F');
   factory->AddVariable("TagVarCSV2_jetNTracksEtaRel","TagVarCSV2_jetNTracksEtaRel","units",'F');
   factory->AddVariable("TagVarCSV2_trackEtaRel_0","TagVarCSV2_trackEtaRel_0","units",'F');
   factory->AddVariable("TagVarCSV2_trackEtaRel_1","TagVarCSV2_trackEtaRel_1","units",'F');
   factory->AddVariable("TagVarCSV2_trackEtaRel_2","TagVarCSV2_trackEtaRel_2","units",'F');
   //factory->AddVariable("TagVarCSV2_jetNSecondaryVertices","TagVarCSV2_jetNSecondaryVertices","units",'F');
   factory->AddVariable("TagVarCSV2_vertexMass","TagVarCSV2_vertexMass","units",'F');
   factory->AddVariable("TagVarCSV2_vertexNTracks","TagVarCSV2_vertexNTracks","units",'F');
   factory->AddVariable("TagVarCSV2_vertexEnergyRatio","TagVarCSV2_vertexEnergyRatio","units",'F');
   factory->AddVariable("TagVarCSV2_vertexJetDeltaR","TagVarCSV2_vertexJetDeltaR","units",'F');
   factory->AddVariable("TagVarCSV2_flightDistance2dSig","TagVarCSV2_flightDistance2dSig","units",'F');
   
   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   factory->AddSpectator("Jet_pt","Jet_pt","units",'F');
   factory->AddSpectator("Jet_eta","Jet_eta","units",'F');
   factory->AddSpectator("Jet_phi","Jet_phi","units",'F');
   factory->AddSpectator("Jet_mass","Jet_mass","units",'F');
   factory->AddSpectator("Jet_massGroomed","Jet_massGroomed","units",'F');
   factory->AddSpectator("Jet_flavour","Jet_flavour","units",'F');
   factory->AddSpectator("Jet_nbHadrons","Jet_nbHadrons","units",'F');
   factory->AddSpectator("Jet_JP","Jet_JP","units",'F');
   factory->AddSpectator("Jet_JBP","Jet_JBP","units",'F');
   factory->AddSpectator("Jet_CSV","Jet_CSV","units",'F');
   factory->AddSpectator("Jet_CSVIVF","Jet_CSVIVF","units",'F');
   factory->AddSpectator("Jet_tau1","Jet_tau1","units",'F');
   factory->AddSpectator("Jet_tau2","Jet_tau2","units",'F');

   factory->AddSpectator("SubJet1_CSVIVF","SubJet1_CSVIVF","units",'F');
   factory->AddSpectator("SubJet2_CSVIVF","SubJet2_CSVIVF","units",'F');

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TString fnameSig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_JetTaggingVariables_training.root";
   TString fnameBkg = "QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_JetTaggingVariables_training.root";
   TFile *inputSig = TFile::Open( fnameSig );
   TFile *inputBkg = TFile::Open( fnameBkg );
   
   std::cout << "--- TMVAClassification       : Using input files: " << inputSig->GetName() << std::endl
                                                                     << inputBkg->GetName() << std::endl;
   
   // --- Register the training and test trees
   TTree *sigTree = (TTree*)inputSig->Get("tagVars/ttree");
   TTree *bkgTree = (TTree*)inputBkg->Get("tagVars/ttree");
   
   // // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   // factory->SetInputTrees( tree,signalCut,backgroundCut );
   factory->AddSignalTree    ( sigTree, signalWeight     );
   factory->AddBackgroundTree( bkgTree, backgroundWeight );

   // Apply additional cuts on the signal and background samples (can be different)
   TCut signalCut = "Jet_massGroomed>80 && Jet_massGroomed<150";
   TCut backgroundCut = "abs(Jet_flavour)==5 && Jet_nbHadrons>1 && Jet_massGroomed>80 && Jet_massGroomed<150";

   // Tell the factory how to use the training and testing events
   factory->PrepareTrainingAndTestTree( signalCut, backgroundCut,
                                        "nTrain_Signal=22000:nTest_Signal=20000:nTrain_Background=22000:nTest_Background=2730:SplitMode=Random:!V" );

   // Gradient Boost
   factory->BookMethod( TMVA::Types::kBDT, "BDTG_T1000D3_BBvsGSP",
                          "!H:!V:NTrees=1000:MaxDepth=3:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   //factory->BookMethod( TMVA::Types::kBDT, "BDTG_T1000D5_BBvsGSP",
   //                       "!H:!V:NTrees=1000:MaxDepth=5:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20" );

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