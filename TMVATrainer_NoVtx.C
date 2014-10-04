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

void TMVATrainer(int vtxCategory=2){
   // This loads the library
   TMVA::Tools::Instance();

   // --- Here the preparation phase begins
   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName = TString::Format("TMVATrainingResults_VtxCat%i.root",vtxCategory);
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
   TMVA::Factory *factory = new TMVA::Factory( TString::Format("TMVATrainer_VtxCat%i",vtxCategory), outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   factory->AddVariable("TagVarCSV_jetNTracks","TagVarCSV_jetNTracks","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_Leading","TagVarCSV_trackSip3dSig_Leading","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_SecondLeading","TagVarCSV_trackSip3dSig_SecondLeading","units",'F');
   factory->AddVariable("TagVarCSV_trackSip3dSig_ThirdLeading","TagVarCSV_trackSip3dSig_ThirdLeading","units",'F');
   factory->AddVariable("TagVarCSV_trackSip2dSigAboveCharm","TagVarCSV_trackSip2dSigAboveCharm","units",'F');

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
   factory->AddSpectator("TagVarCSV_trackJetPt","TagVarCSV_trackJetPt","units",'F');
   factory->AddSpectator("TagVarCSV_trackSumJetEtRatio","TagVarCSV_trackSumJetEtRatio","units",'F');
   factory->AddSpectator("TagVarCSV_trackSumJetDeltaR","TagVarCSV_trackSumJetDeltaR","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip2dValAboveCharm","TagVarCSV_trackSip2dValAboveCharm","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip3dValAboveCharm","TagVarCSV_trackSip3dValAboveCharm","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip3dSigAboveCharm","TagVarCSV_trackSip3dSigAboveCharm","units",'F');
   factory->AddSpectator("TagVarCSV_jetNSecondaryVertices","TagVarCSV_jetNSecondaryVertices","units",'F');
   factory->AddSpectator("TagVarCSV_vertexJetDeltaR","TagVarCSV_vertexJetDeltaR","units",'F');
   factory->AddSpectator("TagVarCSV_flightDistance2dVal","TagVarCSV_flightDistance2dVal","units",'F');
   factory->AddSpectator("TagVarCSV_flightDistance2dSig","TagVarCSV_flightDistance2dSig","units",'F');
   factory->AddSpectator("TagVarCSV_flightDistance3dVal","TagVarCSV_flightDistance3dVal","units",'F');
   factory->AddSpectator("TagVarCSV_flightDistance3dSig","TagVarCSV_flightDistance3dSig","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip2dSig_Leading","TagVarCSV_trackSip2dSig_Leading","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip2dSig_SecondLeading","TagVarCSV_trackSip2dSig_SecondLeading","units",'F');
   factory->AddSpectator("TagVarCSV_trackSip2dSig_ThirdLeading","TagVarCSV_trackSip2dSig_ThirdLeading","units",'F');
   factory->AddSpectator("TagVarCSV_jetNTracksEtaRel","TagVarCSV_jetNTracksEtaRel","units",'F');
   factory->AddSpectator("TagVarCSV_trackEtaRel_Lowest","TagVarCSV_trackEtaRel_Lowest","units",'F');
   factory->AddSpectator("TagVarCSV_trackEtaRel_SecondLowest","TagVarCSV_trackEtaRel_SecondLowest","units",'F');
   factory->AddSpectator("TagVarCSV_trackEtaRel_ThirdLowest","TagVarCSV_trackEtaRel_ThirdLowest","units",'F');
   factory->AddSpectator("TagVarCSV_vertexMass","TagVarCSV_vertexMass","units",'F');
   factory->AddSpectator("TagVarCSV_vertexNTracks","TagVarCSV_vertexNTracks","units",'F');
   factory->AddSpectator("TagVarCSV_vertexEnergyRatio","TagVarCSV_vertexEnergyRatio","units",'F');
   factory->AddSpectator("TagVarCSV_vertexCategory","TagVarCSV_vertexCategory","units",'F');

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   // TString fname = "./tmva_class_example.root";
   TString fname = "QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_JetTaggingVariables_training.root";
   TFile *input = TFile::Open( fname );
   // TString signalFileName = "radion_m800_ALLEVENTS.root";
   // TString bkgFileName = "qcd300-470_ALLEVENTS.root";

   // TFile *signalFile = TFile::Open( signalFileName );
   // TFile *bkgFile = TFile::Open( bkgFileName );
   
   // std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;
   
   // --- Register the training and test trees
   // TTree *tree = (TTree*)input->Get("tagVars/ttree");

   TTree *sigTree = (TTree*)input->Get("tagVars/ttree");
   TTree *bkgTree = (TTree*)input->Get("tagVars/ttree");
   
   // // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;


   TCut signalCut = (TString::Format("abs(Jet_flavour)==5 && TagVarCSV_vertexCategory==%i",vtxCategory)).Data();
   TCut backgroundCut = (TString::Format("abs(Jet_flavour)!=5 && abs(Jet_flavour)!=4 && TagVarCSV_vertexCategory==%i",vtxCategory)).Data();

   // factory->SetInputTrees( tree,signalCut,backgroundCut );
   factory->AddSignalTree    ( sigTree, signalWeight     );
   factory->AddBackgroundTree( bkgTree, backgroundWeight );

   // Apply additional cuts on the signal and background samples (can be different)
   // TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   // TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //    factory->PrepareTrainingAndTestTree( mycut,
   //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );

//    //vectors that hold number of events to train for sig/bkg in different vtxCategories
//    std::vector<int> nSigEvents;
//    std::vector<int> nBkgEvents;
// 
//    nSigEvents.push_back(21626); //for 0
//    nSigEvents.push_back(4684); //for 1
//    nSigEvents.push_back(11631); //for 2
// 
//    nBkgEvents.push_back(91033); //for 0
//    nBkgEvents.push_back(131584); //for 1
//    nBkgEvents.push_back(2186422); //for 2


   factory->PrepareTrainingAndTestTree( signalCut, backgroundCut,
                                        "nTrain_Background=25000:nTest_Background=30000:SplitMode=Random:!V" );

   //options from TMVAClassification.C
   // factory->BookMethod( TMVA::Types::kBDT, "BDTG",
   //                      "!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5" );
//    if(method == 0)       factory->BookMethod( TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=2" );
//    else if (method == 1) factory->BookMethod( TMVA::Types::kBDT, "BDTG_T500_D2","!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=2" );
//    else if (method == 2) factory->BookMethod( TMVA::Types::kBDT, "BDTG_T1000_D5","!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=5" );
//    else if (method == 3) factory->BookMethod( TMVA::Types::kBDT, "BDTG_T500_D5","!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:MaxDepth=5" );
//    else{
//       std::cout << "Method input not recognized!";
//       return;
//    }
   // Gradient Boost
   factory->BookMethod( TMVA::Types::kBDT, "BDTG",
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