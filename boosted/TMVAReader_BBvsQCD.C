#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace TMVA;


void TMVAReader(){
#ifdef __CINT__
    gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

    TMVA::Tools::Instance(); // loads libraries

    //######################################
    // Fat jet variables
    //######################################
    float Jet_pt;
    float Jet_eta;
    float Jet_phi;
    float Jet_mass;
    float Jet_massGroomed;
    float Jet_flavour;
    float Jet_nbHadrons;
    float Jet_JP;
    float Jet_JBP;
    float Jet_CSV;
    float Jet_CSVIVF;
    float Jet_tau1;
    float Jet_tau2;

    // CSV TaggingVariables
    // per jet
    float TagVarCSV_jetNTracks;                           // tracks associated to jet
    float TagVarCSV_jetNTracksEtaRel;                     // tracks associated to jet for which trackEtaRel is calculated
    float TagVarCSV_trackSumJetEtRatio;                   // ratio of track sum transverse energy over jet energy
    float TagVarCSV_trackSumJetDeltaR;                    // pseudoangular distance between jet axis and track fourvector sum
    float TagVarCSV_trackSip2dValAboveCharm;              // track 2D signed impact parameter of first track lifting mass above charm
    float TagVarCSV_trackSip2dSigAboveCharm;              // track 2D signed impact parameter significance of first track lifting mass above charm
    float TagVarCSV_trackSip3dValAboveCharm;              // track 3D signed impact parameter of first track lifting mass above charm
    float TagVarCSV_trackSip3dSigAboveCharm;              // track 3D signed impact parameter significance of first track lifting mass above charm
    float TagVarCSV_vertexCategory;                       // category of secondary vertex (Reco, Pseudo, No)
    float TagVarCSV_jetNSecondaryVertices;                // number of reconstructed possible secondary vertices in jet
    float TagVarCSV_vertexMass;                           // mass of track sum at secondary vertex
    float TagVarCSV_vertexNTracks;                        // number of tracks at secondary vertex
    float TagVarCSV_vertexEnergyRatio;                    // ratio of energy at secondary vertex over total energy
    float TagVarCSV_vertexJetDeltaR;                      // pseudoangular distance between jet axis and secondary vertex direction
    float TagVarCSV_flightDistance2dVal;                  // transverse distance between primary and secondary vertex
    float TagVarCSV_flightDistance2dSig;                  // transverse distance significance between primary and secondary vertex
    float TagVarCSV_flightDistance3dVal;                  // distance between primary and secondary vertex
    float TagVarCSV_flightDistance3dSig;                  // distance significance between primary and secondary vertex
    // per jet per track
    float TagVarCSV_trackSip2dSig_0;                      // highest track 2D signed IP of tracks belonging to a given jet   
    float TagVarCSV_trackSip2dSig_1;                      // second highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip2dSig_2;                      // third highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip2dSig_3;                      // fourth highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip2dSig_4;                      // fifth highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip2dSig_5;                      // sixth highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_0;                      // highest track 3D signed IP of tracks belonging to a given jet   
    float TagVarCSV_trackSip3dSig_1;                      // second highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_2;                      // third highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_3;                      // fourth highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_4;                      // fifth highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_5;                      // sixth highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackPtRel_0;                         // highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_1;                         // second highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_2;                         // third highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_3;                         // fourth highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_4;                         // fifth highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_5;                         // sixth highest track transverse momentum, relative to the jet axis
    // per jet per etaRel track
    float TagVarCSV_trackEtaRel_0;                        // lowest track eta relative to jet axis
    float TagVarCSV_trackEtaRel_1;                        // second lowest track eta relative to jet axis
    float TagVarCSV_trackEtaRel_2;                        // third lowest track eta relative to jet axis

    //######################################
    // Subjet1 variables
    //######################################
    float SubJet1_pt;
    float SubJet1_eta;
    float SubJet1_phi;
    float SubJet1_mass;
    float SubJet1_flavour;
    float SubJet1_nbHadrons;
    float SubJet1_JP;
    float SubJet1_JBP;
    float SubJet1_CSV;
    float SubJet1_CSVIVF;

    // CSV TaggingVariables
    // per jet
    float TagVarCSV1_jetNTracks;                           // tracks associated to jet
    float TagVarCSV1_jetNTracksEtaRel;                     // tracks associated to jet for which trackEtaRel is calculated
    float TagVarCSV1_trackSumJetEtRatio;                   // ratio of track sum transverse energy over jet energy
    float TagVarCSV1_trackSumJetDeltaR;                    // pseudoangular distance between jet axis and track fourvector sum
    float TagVarCSV1_trackSip2dValAboveCharm;              // track 2D signed impact parameter of first track lifting mass above charm
    float TagVarCSV1_trackSip2dSigAboveCharm;              // track 2D signed impact parameter significance of first track lifting mass above charm
    float TagVarCSV1_trackSip3dValAboveCharm;              // track 3D signed impact parameter of first track lifting mass above charm
    float TagVarCSV1_trackSip3dSigAboveCharm;              // track 3D signed impact parameter significance of first track lifting mass above charm
    float TagVarCSV1_vertexCategory;                       // category of secondary vertex (Reco, Pseudo, No)
    float TagVarCSV1_jetNSecondaryVertices;                // number of reconstructed possible secondary vertices in jet
    float TagVarCSV1_vertexMass;                           // mass of track sum at secondary vertex
    float TagVarCSV1_vertexNTracks;                        // number of tracks at secondary vertex
    float TagVarCSV1_vertexEnergyRatio;                    // ratio of energy at secondary vertex over total energy
    float TagVarCSV1_vertexJetDeltaR;                      // pseudoangular distance between jet axis and secondary vertex direction
    float TagVarCSV1_flightDistance2dVal;                  // transverse distance between primary and secondary vertex
    float TagVarCSV1_flightDistance2dSig;                  // transverse distance significance between primary and secondary vertex
    float TagVarCSV1_flightDistance3dVal;                  // distance between primary and secondary vertex
    float TagVarCSV1_flightDistance3dSig;                  // distance significance between primary and secondary vertex
    // per jet per etaRel track
    float TagVarCSV1_trackEtaRel_0;                        // lowest track eta relative to jet axis
    float TagVarCSV1_trackEtaRel_1;                        // second lowest track eta relative to jet axis
    float TagVarCSV1_trackEtaRel_2;                        // third lowest track eta relative to jet axis

    //######################################
    // Subjet2 variables
    //######################################
    float SubJet2_pt;
    float SubJet2_eta;
    float SubJet2_phi;
    float SubJet2_mass;
    float SubJet2_flavour;
    float SubJet2_nbHadrons;
    float SubJet2_JP;
    float SubJet2_JBP;
    float SubJet2_CSV;
    float SubJet2_CSVIVF;

    // CSV TaggingVariables
    // per jet
    float TagVarCSV2_jetNTracks;                           // tracks associated to jet
    float TagVarCSV2_jetNTracksEtaRel;                     // tracks associated to jet for which trackEtaRel is calculated
    float TagVarCSV2_trackSumJetEtRatio;                   // ratio of track sum transverse energy over jet energy
    float TagVarCSV2_trackSumJetDeltaR;                    // pseudoangular distance between jet axis and track fourvector sum
    float TagVarCSV2_trackSip2dValAboveCharm;              // track 2D signed impact parameter of first track lifting mass above charm
    float TagVarCSV2_trackSip2dSigAboveCharm;              // track 2D signed impact parameter significance of first track lifting mass above charm
    float TagVarCSV2_trackSip3dValAboveCharm;              // track 3D signed impact parameter of first track lifting mass above charm
    float TagVarCSV2_trackSip3dSigAboveCharm;              // track 3D signed impact parameter significance of first track lifting mass above charm
    float TagVarCSV2_vertexCategory;                       // category of secondary vertex (Reco, Pseudo, No)
    float TagVarCSV2_jetNSecondaryVertices;                // number of reconstructed possible secondary vertices in jet
    float TagVarCSV2_vertexMass;                           // mass of track sum at secondary vertex
    float TagVarCSV2_vertexNTracks;                        // number of tracks at secondary vertex
    float TagVarCSV2_vertexEnergyRatio;                    // ratio of energy at secondary vertex over total energy
    float TagVarCSV2_vertexJetDeltaR;                      // pseudoangular distance between jet axis and secondary vertex direction
    float TagVarCSV2_flightDistance2dVal;                  // transverse distance between primary and secondary vertex
    float TagVarCSV2_flightDistance2dSig;                  // transverse distance significance between primary and secondary vertex
    float TagVarCSV2_flightDistance3dVal;                  // distance between primary and secondary vertex
    float TagVarCSV2_flightDistance3dSig;                  // distance significance between primary and secondary vertex
    // per jet per etaRel track
    float TagVarCSV2_trackEtaRel_0;                        // lowest track eta relative to jet axis
    float TagVarCSV2_trackEtaRel_1;                        // second lowest track eta relative to jet axis
    float TagVarCSV2_trackEtaRel_2;                        // third lowest track eta relative to jet axis


    TMVA::Reader *reader = new TMVA::Reader( "!Color" );
    
    reader->AddVariable("TagVarCSV_jetNTracks", &TagVarCSV_jetNTracks);
    reader->AddVariable("TagVarCSV_trackSip3dSig_0", &TagVarCSV_trackSip3dSig_0);
    reader->AddVariable("TagVarCSV_trackSip3dSig_1", &TagVarCSV_trackSip3dSig_1);
    reader->AddVariable("TagVarCSV_trackSip3dSig_2", &TagVarCSV_trackSip3dSig_2);
    reader->AddVariable("TagVarCSV_trackSip3dSig_3", &TagVarCSV_trackSip3dSig_3);
    //reader->AddVariable("TagVarCSV_trackSip3dSig_4", &TagVarCSV_trackSip3dSig_4);
    //reader->AddVariable("TagVarCSV_trackSip3dSig_5", &TagVarCSV_trackSip3dSig_5);
    reader->AddVariable("TagVarCSV_trackSip2dSigAboveCharm", &TagVarCSV_trackSip2dSigAboveCharm);
    reader->AddVariable("TagVarCSV_trackSumJetEtRatio", &TagVarCSV_trackSumJetEtRatio);
    reader->AddVariable("TagVarCSV_trackSumJetDeltaR", &TagVarCSV_trackSumJetDeltaR);

    //reader->AddVariable("TagVarCSV1_vertexCategory", &TagVarCSV1_vertexCategory);
    reader->AddVariable("TagVarCSV1_jetNTracks", &TagVarCSV1_jetNTracks);
    reader->AddVariable("TagVarCSV1_trackSip2dSigAboveCharm", &TagVarCSV1_trackSip2dSigAboveCharm);
    reader->AddVariable("TagVarCSV1_trackSumJetEtRatio", &TagVarCSV1_trackSumJetEtRatio);
    //reader->AddVariable("TagVarCSV1_trackSumJetDeltaR", &TagVarCSV1_trackSumJetDeltaR);
    reader->AddVariable("TagVarCSV1_jetNTracksEtaRel", &TagVarCSV1_jetNTracksEtaRel);
    reader->AddVariable("TagVarCSV1_trackEtaRel_0", &TagVarCSV1_trackEtaRel_0);
    reader->AddVariable("TagVarCSV1_trackEtaRel_1", &TagVarCSV1_trackEtaRel_1);
    reader->AddVariable("TagVarCSV1_trackEtaRel_2", &TagVarCSV1_trackEtaRel_2);
    //reader->AddVariable("TagVarCSV1_jetNSecondaryVertices", &TagVarCSV1_jetNSecondaryVertices);
    reader->AddVariable("TagVarCSV1_vertexMass", &TagVarCSV1_vertexMass);
    reader->AddVariable("TagVarCSV1_vertexNTracks", &TagVarCSV1_vertexNTracks);
    reader->AddVariable("TagVarCSV1_vertexEnergyRatio", &TagVarCSV1_vertexEnergyRatio);
    reader->AddVariable("TagVarCSV1_vertexJetDeltaR", &TagVarCSV1_vertexJetDeltaR);
    reader->AddVariable("TagVarCSV1_flightDistance2dSig", &TagVarCSV1_flightDistance2dSig);

    //reader->AddVariable("TagVarCSV2_vertexCategory", &TagVarCSV2_vertexCategory);
    reader->AddVariable("TagVarCSV2_jetNTracks", &TagVarCSV2_jetNTracks);
    reader->AddVariable("TagVarCSV2_trackSip2dSigAboveCharm", &TagVarCSV2_trackSip2dSigAboveCharm);
    reader->AddVariable("TagVarCSV2_trackSumJetEtRatio", &TagVarCSV2_trackSumJetEtRatio);
    //reader->AddVariable("TagVarCSV2_trackSumJetDeltaR", &TagVarCSV2_trackSumJetDeltaR);
    reader->AddVariable("TagVarCSV2_jetNTracksEtaRel", &TagVarCSV2_jetNTracksEtaRel);
    reader->AddVariable("TagVarCSV2_trackEtaRel_0", &TagVarCSV2_trackEtaRel_0);
    reader->AddVariable("TagVarCSV2_trackEtaRel_1", &TagVarCSV2_trackEtaRel_1);
    reader->AddVariable("TagVarCSV2_trackEtaRel_2", &TagVarCSV2_trackEtaRel_2);
    //reader->AddVariable("TagVarCSV2_jetNSecondaryVertices", &TagVarCSV2_jetNSecondaryVertices);
    reader->AddVariable("TagVarCSV2_vertexMass", &TagVarCSV2_vertexMass);
    reader->AddVariable("TagVarCSV2_vertexNTracks", &TagVarCSV2_vertexNTracks);
    reader->AddVariable("TagVarCSV2_vertexEnergyRatio", &TagVarCSV2_vertexEnergyRatio);
    reader->AddVariable("TagVarCSV2_vertexJetDeltaR", &TagVarCSV2_vertexJetDeltaR);
    reader->AddVariable("TagVarCSV2_flightDistance2dSig", &TagVarCSV2_flightDistance2dSig);
    
    reader->AddSpectator("Jet_pt", &Jet_pt);
    reader->AddSpectator("Jet_eta", &Jet_eta);
    reader->AddSpectator("Jet_phi", &Jet_phi);
    reader->AddSpectator("Jet_mass", &Jet_mass);
    reader->AddSpectator("Jet_massGroomed", &Jet_massGroomed);
    reader->AddSpectator("Jet_flavour", &Jet_flavour);
    reader->AddSpectator("Jet_nbHadrons", &Jet_nbHadrons);
    reader->AddSpectator("Jet_JP", &Jet_JP);
    reader->AddSpectator("Jet_JBP", &Jet_JBP);
    reader->AddSpectator("Jet_CSV", &Jet_CSV);
    reader->AddSpectator("Jet_CSVIVF", &Jet_CSVIVF);
    reader->AddSpectator("Jet_tau1", &Jet_tau1);
    reader->AddSpectator("Jet_tau2", &Jet_tau2);

    reader->AddSpectator("SubJet1_CSVIVF", &SubJet1_CSVIVF);
    reader->AddSpectator("SubJet2_CSVIVF", &SubJet2_CSVIVF);

    reader->BookMVA( "BDTG_T1000D3_BBvsQCD method", "weights/TMVATrainer_BDTG_T1000D3_BBvsQCD.weights.xml" );

    // histograms
    TH1F* hBDTGDiscSig = new TH1F("hBDTGDiscSig","",1000,-5,5);
    TH1F* hBDTGDiscBkg = new TH1F("hBDTGDiscBkg","",1000,-5,5);

    TH1F* hFatCSVIVFDiscSig = new TH1F("hFatCSVIVFDiscSig","",1000,-5,5);
    TH1F* hFatCSVIVFDiscBkg = new TH1F("hFatCSVIVFDiscBkg","",1000,-5,5);

    TH1F* hSubCSVIVFDiscSig = new TH1F("hSubCSVIVFDiscSig","",1000,-5,5);
    TH1F* hSubCSVIVFDiscBkg = new TH1F("hSubCSVIVFDiscBkg","",1000,-5,5);

    hBDTGDiscSig->GetXaxis()->SetTitle("BDTG Discriminant");
    hBDTGDiscBkg->GetXaxis()->SetTitle("BDTG Discriminant");

    hFatCSVIVFDiscSig->GetXaxis()->SetTitle("CSV Discriminant");
    hFatCSVIVFDiscBkg->GetXaxis()->SetTitle("CSV Discriminant");

    hSubCSVIVFDiscSig->GetXaxis()->SetTitle("CSV Discriminant");
    hSubCSVIVFDiscBkg->GetXaxis()->SetTitle("CSV Discriminant");
    
    // background input tree
    TString infilenameBkg="QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_JetTaggingVariables_evaluation.root";
    TFile inBkg(infilenameBkg);
    TTree* intree = (TTree*)inBkg.Get("tagVars/ttree");

    // set the branches to point to address of the variables declared above
    //######################################
    // Fat jet variables
    //######################################
    intree->SetBranchAddress("Jet_pt"          ,&Jet_pt          );
    intree->SetBranchAddress("Jet_eta"         ,&Jet_eta         );
    intree->SetBranchAddress("Jet_phi"         ,&Jet_phi         );
    intree->SetBranchAddress("Jet_mass"        ,&Jet_mass        );
    intree->SetBranchAddress("Jet_massGroomed" ,&Jet_massGroomed );
    intree->SetBranchAddress("Jet_flavour"     ,&Jet_flavour     );
    intree->SetBranchAddress("Jet_nbHadrons"   ,&Jet_nbHadrons   );
    intree->SetBranchAddress("Jet_JP"          ,&Jet_JP          );
    intree->SetBranchAddress("Jet_JBP"         ,&Jet_JBP         );
    intree->SetBranchAddress("Jet_CSV"         ,&Jet_CSV         );
    intree->SetBranchAddress("Jet_CSVIVF"      ,&Jet_CSVIVF      );
    intree->SetBranchAddress("Jet_tau1"        ,&Jet_tau1        );
    intree->SetBranchAddress("Jet_tau2"        ,&Jet_tau2        );
    //--------------------------------------
    // CSV TaggingVariables
    //--------------------------------------
    intree->SetBranchAddress("TagVarCSV_jetNTracks"               ,&TagVarCSV_jetNTracks              );
    intree->SetBranchAddress("TagVarCSV_jetNTracksEtaRel"         ,&TagVarCSV_jetNTracksEtaRel        );
    intree->SetBranchAddress("TagVarCSV_trackSumJetEtRatio"       ,&TagVarCSV_trackSumJetEtRatio      );
    intree->SetBranchAddress("TagVarCSV_trackSumJetDeltaR"        ,&TagVarCSV_trackSumJetDeltaR       );
    intree->SetBranchAddress("TagVarCSV_trackSip2dValAboveCharm"  ,&TagVarCSV_trackSip2dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSigAboveCharm"  ,&TagVarCSV_trackSip2dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV_trackSip3dValAboveCharm"  ,&TagVarCSV_trackSip3dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSigAboveCharm"  ,&TagVarCSV_trackSip3dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV_vertexCategory"           ,&TagVarCSV_vertexCategory          );
    intree->SetBranchAddress("TagVarCSV_jetNSecondaryVertices"    ,&TagVarCSV_jetNSecondaryVertices   );
    intree->SetBranchAddress("TagVarCSV_vertexMass"               ,&TagVarCSV_vertexMass              );
    intree->SetBranchAddress("TagVarCSV_vertexNTracks"            ,&TagVarCSV_vertexNTracks           );
    intree->SetBranchAddress("TagVarCSV_vertexEnergyRatio"        ,&TagVarCSV_vertexEnergyRatio       );
    intree->SetBranchAddress("TagVarCSV_vertexJetDeltaR"          ,&TagVarCSV_vertexJetDeltaR         );
    intree->SetBranchAddress("TagVarCSV_flightDistance2dVal"      ,&TagVarCSV_flightDistance2dVal     );
    intree->SetBranchAddress("TagVarCSV_flightDistance2dSig"      ,&TagVarCSV_flightDistance2dSig     );
    intree->SetBranchAddress("TagVarCSV_flightDistance3dVal"      ,&TagVarCSV_flightDistance3dVal     );
    intree->SetBranchAddress("TagVarCSV_flightDistance3dSig"      ,&TagVarCSV_flightDistance3dSig     );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_0"          ,&TagVarCSV_trackSip2dSig_0         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_1"          ,&TagVarCSV_trackSip2dSig_1         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_2"          ,&TagVarCSV_trackSip2dSig_2         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_3"          ,&TagVarCSV_trackSip2dSig_3         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_4"          ,&TagVarCSV_trackSip2dSig_4         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_5"          ,&TagVarCSV_trackSip2dSig_5         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_0"          ,&TagVarCSV_trackSip3dSig_0         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_1"          ,&TagVarCSV_trackSip3dSig_1         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_2"          ,&TagVarCSV_trackSip3dSig_2         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_3"          ,&TagVarCSV_trackSip3dSig_3         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_4"          ,&TagVarCSV_trackSip3dSig_4         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_5"          ,&TagVarCSV_trackSip3dSig_5         );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_0"             ,&TagVarCSV_trackPtRel_0            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_1"             ,&TagVarCSV_trackPtRel_1            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_2"             ,&TagVarCSV_trackPtRel_2            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_3"             ,&TagVarCSV_trackPtRel_3            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_4"             ,&TagVarCSV_trackPtRel_4            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_5"             ,&TagVarCSV_trackPtRel_5            );
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_0"            ,&TagVarCSV_trackEtaRel_0           );
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_1"            ,&TagVarCSV_trackEtaRel_1           );
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_2"            ,&TagVarCSV_trackEtaRel_2           );
    //######################################
    // Subjet1 variables
    //######################################
    intree->SetBranchAddress("SubJet1_pt"          ,&SubJet1_pt          );
    intree->SetBranchAddress("SubJet1_eta"         ,&SubJet1_eta         );
    intree->SetBranchAddress("SubJet1_phi"         ,&SubJet1_phi         );
    intree->SetBranchAddress("SubJet1_mass"        ,&SubJet1_mass        );
    intree->SetBranchAddress("SubJet1_flavour"     ,&SubJet1_flavour     );
    intree->SetBranchAddress("SubJet1_nbHadrons"   ,&SubJet1_nbHadrons   );
    intree->SetBranchAddress("SubJet1_JP"          ,&SubJet1_JP          );
    intree->SetBranchAddress("SubJet1_JBP"         ,&SubJet1_JBP         );
    intree->SetBranchAddress("SubJet1_CSV"         ,&SubJet1_CSV         );
    intree->SetBranchAddress("SubJet1_CSVIVF"      ,&SubJet1_CSVIVF      );
    //--------------------------------------
    // CSV TaggingVariables
    //--------------------------------------
    intree->SetBranchAddress("TagVarCSV1_jetNTracks"               ,&TagVarCSV1_jetNTracks              );
    intree->SetBranchAddress("TagVarCSV1_jetNTracksEtaRel"         ,&TagVarCSV1_jetNTracksEtaRel        );
    intree->SetBranchAddress("TagVarCSV1_trackSumJetEtRatio"       ,&TagVarCSV1_trackSumJetEtRatio      );
    intree->SetBranchAddress("TagVarCSV1_trackSumJetDeltaR"        ,&TagVarCSV1_trackSumJetDeltaR       );
    intree->SetBranchAddress("TagVarCSV1_trackSip2dValAboveCharm"  ,&TagVarCSV1_trackSip2dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_trackSip2dSigAboveCharm"  ,&TagVarCSV1_trackSip2dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_trackSip3dValAboveCharm"  ,&TagVarCSV1_trackSip3dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_trackSip3dSigAboveCharm"  ,&TagVarCSV1_trackSip3dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_vertexCategory"           ,&TagVarCSV1_vertexCategory          );
    intree->SetBranchAddress("TagVarCSV1_jetNSecondaryVertices"    ,&TagVarCSV1_jetNSecondaryVertices   );
    intree->SetBranchAddress("TagVarCSV1_vertexMass"               ,&TagVarCSV1_vertexMass              );
    intree->SetBranchAddress("TagVarCSV1_vertexNTracks"            ,&TagVarCSV1_vertexNTracks           );
    intree->SetBranchAddress("TagVarCSV1_vertexEnergyRatio"        ,&TagVarCSV1_vertexEnergyRatio       );
    intree->SetBranchAddress("TagVarCSV1_vertexJetDeltaR"          ,&TagVarCSV1_vertexJetDeltaR         );
    intree->SetBranchAddress("TagVarCSV1_flightDistance2dVal"      ,&TagVarCSV1_flightDistance2dVal     );
    intree->SetBranchAddress("TagVarCSV1_flightDistance2dSig"      ,&TagVarCSV1_flightDistance2dSig     );
    intree->SetBranchAddress("TagVarCSV1_flightDistance3dVal"      ,&TagVarCSV1_flightDistance3dVal     );
    intree->SetBranchAddress("TagVarCSV1_flightDistance3dSig"      ,&TagVarCSV1_flightDistance3dSig     );
    intree->SetBranchAddress("TagVarCSV1_trackEtaRel_0"            ,&TagVarCSV1_trackEtaRel_0           );
    intree->SetBranchAddress("TagVarCSV1_trackEtaRel_1"            ,&TagVarCSV1_trackEtaRel_1           );
    intree->SetBranchAddress("TagVarCSV1_trackEtaRel_2"            ,&TagVarCSV1_trackEtaRel_2           );
    //######################################
    // Subjet2 variables
    //######################################
    intree->SetBranchAddress("SubJet2_pt"          ,&SubJet2_pt          );
    intree->SetBranchAddress("SubJet2_eta"         ,&SubJet2_eta         );
    intree->SetBranchAddress("SubJet2_phi"         ,&SubJet2_phi         );
    intree->SetBranchAddress("SubJet2_mass"        ,&SubJet2_mass        );
    intree->SetBranchAddress("SubJet2_flavour"     ,&SubJet2_flavour     );
    intree->SetBranchAddress("SubJet2_nbHadrons"   ,&SubJet2_nbHadrons   );
    intree->SetBranchAddress("SubJet2_JP"          ,&SubJet2_JP          );
    intree->SetBranchAddress("SubJet2_JBP"         ,&SubJet2_JBP         );
    intree->SetBranchAddress("SubJet2_CSV"         ,&SubJet2_CSV         );
    intree->SetBranchAddress("SubJet2_CSVIVF"      ,&SubJet2_CSVIVF      );
    //--------------------------------------
    // CSV TaggingVariables
    //--------------------------------------
    intree->SetBranchAddress("TagVarCSV2_jetNTracks"               ,&TagVarCSV2_jetNTracks              );
    intree->SetBranchAddress("TagVarCSV2_jetNTracksEtaRel"         ,&TagVarCSV2_jetNTracksEtaRel        );
    intree->SetBranchAddress("TagVarCSV2_trackSumJetEtRatio"       ,&TagVarCSV2_trackSumJetEtRatio      );
    intree->SetBranchAddress("TagVarCSV2_trackSumJetDeltaR"        ,&TagVarCSV2_trackSumJetDeltaR       );
    intree->SetBranchAddress("TagVarCSV2_trackSip2dValAboveCharm"  ,&TagVarCSV2_trackSip2dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_trackSip2dSigAboveCharm"  ,&TagVarCSV2_trackSip2dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_trackSip3dValAboveCharm"  ,&TagVarCSV2_trackSip3dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_trackSip3dSigAboveCharm"  ,&TagVarCSV2_trackSip3dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_vertexCategory"           ,&TagVarCSV2_vertexCategory          );
    intree->SetBranchAddress("TagVarCSV2_jetNSecondaryVertices"    ,&TagVarCSV2_jetNSecondaryVertices   );
    intree->SetBranchAddress("TagVarCSV2_vertexMass"               ,&TagVarCSV2_vertexMass              );
    intree->SetBranchAddress("TagVarCSV2_vertexNTracks"            ,&TagVarCSV2_vertexNTracks           );
    intree->SetBranchAddress("TagVarCSV2_vertexEnergyRatio"        ,&TagVarCSV2_vertexEnergyRatio       );
    intree->SetBranchAddress("TagVarCSV2_vertexJetDeltaR"          ,&TagVarCSV2_vertexJetDeltaR         );
    intree->SetBranchAddress("TagVarCSV2_flightDistance2dVal"      ,&TagVarCSV2_flightDistance2dVal     );
    intree->SetBranchAddress("TagVarCSV2_flightDistance2dSig"      ,&TagVarCSV2_flightDistance2dSig     );
    intree->SetBranchAddress("TagVarCSV2_flightDistance3dVal"      ,&TagVarCSV2_flightDistance3dVal     );
    intree->SetBranchAddress("TagVarCSV2_flightDistance3dSig"      ,&TagVarCSV2_flightDistance3dSig     );
    intree->SetBranchAddress("TagVarCSV2_trackEtaRel_0"            ,&TagVarCSV2_trackEtaRel_0           );
    intree->SetBranchAddress("TagVarCSV2_trackEtaRel_1"            ,&TagVarCSV2_trackEtaRel_1           );
    intree->SetBranchAddress("TagVarCSV2_trackEtaRel_2"            ,&TagVarCSV2_trackEtaRel_2           );
    
    std::cout << "Now looping over " << intree->GetEntries() << " entries..." << std::endl;
    for(Long64_t iEntry = 0; iEntry < intree->GetEntries(); iEntry++){
	    if (iEntry % 1000 == 0) std::cout << "Processing Entry #" << iEntry << std::endl;
	    intree->GetEntry(iEntry); // all variables now filled!

	    bool isBkg = ( Jet_massGroomed>80 && Jet_massGroomed<150 );
	    float BDTG_Disc = reader->EvaluateMVA("BDTG_T1000D3_BBvsQCD method");

	    if (isBkg) {
		    hBDTGDiscBkg->Fill(BDTG_Disc);
		    hFatCSVIVFDiscBkg->Fill(Jet_CSVIVF);
		    hSubCSVIVFDiscBkg->Fill(std::min(SubJet1_CSVIVF,SubJet2_CSVIVF));
	    }
    }

    // signal input tree
    TString infilenameSig="RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_JetTaggingVariables_evaluation.root";
    TFile inSig(infilenameSig);
    intree = (TTree*)inSig.Get("tagVars/ttree");

    // set the branches to point to address of the variables declared above
    //######################################
    // Fat jet variables
    //######################################
    intree->SetBranchAddress("Jet_pt"          ,&Jet_pt          );
    intree->SetBranchAddress("Jet_eta"         ,&Jet_eta         );
    intree->SetBranchAddress("Jet_phi"         ,&Jet_phi         );
    intree->SetBranchAddress("Jet_mass"        ,&Jet_mass        );
    intree->SetBranchAddress("Jet_massGroomed" ,&Jet_massGroomed );
    intree->SetBranchAddress("Jet_flavour"     ,&Jet_flavour     );
    intree->SetBranchAddress("Jet_nbHadrons"   ,&Jet_nbHadrons   );
    intree->SetBranchAddress("Jet_JP"          ,&Jet_JP          );
    intree->SetBranchAddress("Jet_JBP"         ,&Jet_JBP         );
    intree->SetBranchAddress("Jet_CSV"         ,&Jet_CSV         );
    intree->SetBranchAddress("Jet_CSVIVF"      ,&Jet_CSVIVF      );
    intree->SetBranchAddress("Jet_tau1"        ,&Jet_tau1        );
    intree->SetBranchAddress("Jet_tau2"        ,&Jet_tau2        );
    //--------------------------------------
    // CSV TaggingVariables
    //--------------------------------------
    intree->SetBranchAddress("TagVarCSV_jetNTracks"               ,&TagVarCSV_jetNTracks              );
    intree->SetBranchAddress("TagVarCSV_jetNTracksEtaRel"         ,&TagVarCSV_jetNTracksEtaRel        );
    intree->SetBranchAddress("TagVarCSV_trackSumJetEtRatio"       ,&TagVarCSV_trackSumJetEtRatio      );
    intree->SetBranchAddress("TagVarCSV_trackSumJetDeltaR"        ,&TagVarCSV_trackSumJetDeltaR       );
    intree->SetBranchAddress("TagVarCSV_trackSip2dValAboveCharm"  ,&TagVarCSV_trackSip2dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSigAboveCharm"  ,&TagVarCSV_trackSip2dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV_trackSip3dValAboveCharm"  ,&TagVarCSV_trackSip3dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSigAboveCharm"  ,&TagVarCSV_trackSip3dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV_vertexCategory"           ,&TagVarCSV_vertexCategory          );
    intree->SetBranchAddress("TagVarCSV_jetNSecondaryVertices"    ,&TagVarCSV_jetNSecondaryVertices   );
    intree->SetBranchAddress("TagVarCSV_vertexMass"               ,&TagVarCSV_vertexMass              );
    intree->SetBranchAddress("TagVarCSV_vertexNTracks"            ,&TagVarCSV_vertexNTracks           );
    intree->SetBranchAddress("TagVarCSV_vertexEnergyRatio"        ,&TagVarCSV_vertexEnergyRatio       );
    intree->SetBranchAddress("TagVarCSV_vertexJetDeltaR"          ,&TagVarCSV_vertexJetDeltaR         );
    intree->SetBranchAddress("TagVarCSV_flightDistance2dVal"      ,&TagVarCSV_flightDistance2dVal     );
    intree->SetBranchAddress("TagVarCSV_flightDistance2dSig"      ,&TagVarCSV_flightDistance2dSig     );
    intree->SetBranchAddress("TagVarCSV_flightDistance3dVal"      ,&TagVarCSV_flightDistance3dVal     );
    intree->SetBranchAddress("TagVarCSV_flightDistance3dSig"      ,&TagVarCSV_flightDistance3dSig     );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_0"          ,&TagVarCSV_trackSip2dSig_0         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_1"          ,&TagVarCSV_trackSip2dSig_1         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_2"          ,&TagVarCSV_trackSip2dSig_2         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_3"          ,&TagVarCSV_trackSip2dSig_3         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_4"          ,&TagVarCSV_trackSip2dSig_4         );
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_5"          ,&TagVarCSV_trackSip2dSig_5         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_0"          ,&TagVarCSV_trackSip3dSig_0         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_1"          ,&TagVarCSV_trackSip3dSig_1         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_2"          ,&TagVarCSV_trackSip3dSig_2         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_3"          ,&TagVarCSV_trackSip3dSig_3         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_4"          ,&TagVarCSV_trackSip3dSig_4         );
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_5"          ,&TagVarCSV_trackSip3dSig_5         );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_0"             ,&TagVarCSV_trackPtRel_0            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_1"             ,&TagVarCSV_trackPtRel_1            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_2"             ,&TagVarCSV_trackPtRel_2            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_3"             ,&TagVarCSV_trackPtRel_3            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_4"             ,&TagVarCSV_trackPtRel_4            );
    intree->SetBranchAddress("TagVarCSV_trackPtRel_5"             ,&TagVarCSV_trackPtRel_5            );
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_0"            ,&TagVarCSV_trackEtaRel_0           );
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_1"            ,&TagVarCSV_trackEtaRel_1           );
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_2"            ,&TagVarCSV_trackEtaRel_2           );
    //######################################
    // Subjet1 variables
    //######################################
    intree->SetBranchAddress("SubJet1_pt"          ,&SubJet1_pt          );
    intree->SetBranchAddress("SubJet1_eta"         ,&SubJet1_eta         );
    intree->SetBranchAddress("SubJet1_phi"         ,&SubJet1_phi         );
    intree->SetBranchAddress("SubJet1_mass"        ,&SubJet1_mass        );
    intree->SetBranchAddress("SubJet1_flavour"     ,&SubJet1_flavour     );
    intree->SetBranchAddress("SubJet1_nbHadrons"   ,&SubJet1_nbHadrons   );
    intree->SetBranchAddress("SubJet1_JP"          ,&SubJet1_JP          );
    intree->SetBranchAddress("SubJet1_JBP"         ,&SubJet1_JBP         );
    intree->SetBranchAddress("SubJet1_CSV"         ,&SubJet1_CSV         );
    intree->SetBranchAddress("SubJet1_CSVIVF"      ,&SubJet1_CSVIVF      );
    //--------------------------------------
    // CSV TaggingVariables
    //--------------------------------------
    intree->SetBranchAddress("TagVarCSV1_jetNTracks"               ,&TagVarCSV1_jetNTracks              );
    intree->SetBranchAddress("TagVarCSV1_jetNTracksEtaRel"         ,&TagVarCSV1_jetNTracksEtaRel        );
    intree->SetBranchAddress("TagVarCSV1_trackSumJetEtRatio"       ,&TagVarCSV1_trackSumJetEtRatio      );
    intree->SetBranchAddress("TagVarCSV1_trackSumJetDeltaR"        ,&TagVarCSV1_trackSumJetDeltaR       );
    intree->SetBranchAddress("TagVarCSV1_trackSip2dValAboveCharm"  ,&TagVarCSV1_trackSip2dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_trackSip2dSigAboveCharm"  ,&TagVarCSV1_trackSip2dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_trackSip3dValAboveCharm"  ,&TagVarCSV1_trackSip3dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_trackSip3dSigAboveCharm"  ,&TagVarCSV1_trackSip3dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV1_vertexCategory"           ,&TagVarCSV1_vertexCategory          );
    intree->SetBranchAddress("TagVarCSV1_jetNSecondaryVertices"    ,&TagVarCSV1_jetNSecondaryVertices   );
    intree->SetBranchAddress("TagVarCSV1_vertexMass"               ,&TagVarCSV1_vertexMass              );
    intree->SetBranchAddress("TagVarCSV1_vertexNTracks"            ,&TagVarCSV1_vertexNTracks           );
    intree->SetBranchAddress("TagVarCSV1_vertexEnergyRatio"        ,&TagVarCSV1_vertexEnergyRatio       );
    intree->SetBranchAddress("TagVarCSV1_vertexJetDeltaR"          ,&TagVarCSV1_vertexJetDeltaR         );
    intree->SetBranchAddress("TagVarCSV1_flightDistance2dVal"      ,&TagVarCSV1_flightDistance2dVal     );
    intree->SetBranchAddress("TagVarCSV1_flightDistance2dSig"      ,&TagVarCSV1_flightDistance2dSig     );
    intree->SetBranchAddress("TagVarCSV1_flightDistance3dVal"      ,&TagVarCSV1_flightDistance3dVal     );
    intree->SetBranchAddress("TagVarCSV1_flightDistance3dSig"      ,&TagVarCSV1_flightDistance3dSig     );
    intree->SetBranchAddress("TagVarCSV1_trackEtaRel_0"            ,&TagVarCSV1_trackEtaRel_0           );
    intree->SetBranchAddress("TagVarCSV1_trackEtaRel_1"            ,&TagVarCSV1_trackEtaRel_1           );
    intree->SetBranchAddress("TagVarCSV1_trackEtaRel_2"            ,&TagVarCSV1_trackEtaRel_2           );
    //######################################
    // Subjet2 variables
    //######################################
    intree->SetBranchAddress("SubJet2_pt"          ,&SubJet2_pt          );
    intree->SetBranchAddress("SubJet2_eta"         ,&SubJet2_eta         );
    intree->SetBranchAddress("SubJet2_phi"         ,&SubJet2_phi         );
    intree->SetBranchAddress("SubJet2_mass"        ,&SubJet2_mass        );
    intree->SetBranchAddress("SubJet2_flavour"     ,&SubJet2_flavour     );
    intree->SetBranchAddress("SubJet2_nbHadrons"   ,&SubJet2_nbHadrons   );
    intree->SetBranchAddress("SubJet2_JP"          ,&SubJet2_JP          );
    intree->SetBranchAddress("SubJet2_JBP"         ,&SubJet2_JBP         );
    intree->SetBranchAddress("SubJet2_CSV"         ,&SubJet2_CSV         );
    intree->SetBranchAddress("SubJet2_CSVIVF"      ,&SubJet2_CSVIVF      );
    //--------------------------------------
    // CSV TaggingVariables
    //--------------------------------------
    intree->SetBranchAddress("TagVarCSV2_jetNTracks"               ,&TagVarCSV2_jetNTracks              );
    intree->SetBranchAddress("TagVarCSV2_jetNTracksEtaRel"         ,&TagVarCSV2_jetNTracksEtaRel        );
    intree->SetBranchAddress("TagVarCSV2_trackSumJetEtRatio"       ,&TagVarCSV2_trackSumJetEtRatio      );
    intree->SetBranchAddress("TagVarCSV2_trackSumJetDeltaR"        ,&TagVarCSV2_trackSumJetDeltaR       );
    intree->SetBranchAddress("TagVarCSV2_trackSip2dValAboveCharm"  ,&TagVarCSV2_trackSip2dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_trackSip2dSigAboveCharm"  ,&TagVarCSV2_trackSip2dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_trackSip3dValAboveCharm"  ,&TagVarCSV2_trackSip3dValAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_trackSip3dSigAboveCharm"  ,&TagVarCSV2_trackSip3dSigAboveCharm );
    intree->SetBranchAddress("TagVarCSV2_vertexCategory"           ,&TagVarCSV2_vertexCategory          );
    intree->SetBranchAddress("TagVarCSV2_jetNSecondaryVertices"    ,&TagVarCSV2_jetNSecondaryVertices   );
    intree->SetBranchAddress("TagVarCSV2_vertexMass"               ,&TagVarCSV2_vertexMass              );
    intree->SetBranchAddress("TagVarCSV2_vertexNTracks"            ,&TagVarCSV2_vertexNTracks           );
    intree->SetBranchAddress("TagVarCSV2_vertexEnergyRatio"        ,&TagVarCSV2_vertexEnergyRatio       );
    intree->SetBranchAddress("TagVarCSV2_vertexJetDeltaR"          ,&TagVarCSV2_vertexJetDeltaR         );
    intree->SetBranchAddress("TagVarCSV2_flightDistance2dVal"      ,&TagVarCSV2_flightDistance2dVal     );
    intree->SetBranchAddress("TagVarCSV2_flightDistance2dSig"      ,&TagVarCSV2_flightDistance2dSig     );
    intree->SetBranchAddress("TagVarCSV2_flightDistance3dVal"      ,&TagVarCSV2_flightDistance3dVal     );
    intree->SetBranchAddress("TagVarCSV2_flightDistance3dSig"      ,&TagVarCSV2_flightDistance3dSig     );
    intree->SetBranchAddress("TagVarCSV2_trackEtaRel_0"            ,&TagVarCSV2_trackEtaRel_0           );
    intree->SetBranchAddress("TagVarCSV2_trackEtaRel_1"            ,&TagVarCSV2_trackEtaRel_1           );
    intree->SetBranchAddress("TagVarCSV2_trackEtaRel_2"            ,&TagVarCSV2_trackEtaRel_2           );
    
    std::cout << "Now looping over " << intree->GetEntries() << " entries..." << std::endl;
    for(Long64_t iEntry = 0; iEntry < intree->GetEntries(); iEntry++){
	    if (iEntry % 1000 == 0) std::cout << "Processing Entry #" << iEntry << std::endl;
	    intree->GetEntry(iEntry); // all variables now filled!

	    bool isSig = ( Jet_massGroomed>80 && Jet_massGroomed<150 );
	    float BDTG_Disc = reader->EvaluateMVA("BDTG_T1000D3_BBvsQCD method");

	    if (isSig) {
		    hBDTGDiscSig->Fill(BDTG_Disc);
		    hFatCSVIVFDiscSig->Fill(Jet_CSVIVF);
		    hSubCSVIVFDiscSig->Fill(std::min(SubJet1_CSVIVF,SubJet2_CSVIVF));
	    }
    }
    
    TString outname = "BDTG_vs_CSVv2IVF_BBvsQCD.root";
    TFile out(outname,"RECREATE");

    hBDTGDiscSig->Write();
    hBDTGDiscBkg->Write();

    hFatCSVIVFDiscSig->Write();
    hFatCSVIVFDiscBkg->Write();
    hSubCSVIVFDiscSig->Write();
    hSubCSVIVFDiscBkg->Write();

    out.Close();

    delete reader;
    delete hBDTGDiscSig;
    delete hBDTGDiscBkg;
    delete hFatCSVIVFDiscSig;
    delete hFatCSVIVFDiscBkg;
    delete hSubCSVIVFDiscSig;
    delete hSubCSVIVFDiscBkg;

    std::cout << "Done analyzing!" << std::endl;

}