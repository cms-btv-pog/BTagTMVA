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


void TMVAReader(int vtxCategory=-1){
#ifdef __CINT__
    gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

    TMVA::Tools::Instance(); // loads libraries

    TMVA::Reader *reader = new TMVA::Reader( "!Color" );

    float Jet_pt;
    float Jet_eta;
    float Jet_phi;
    float Jet_mass;
    float Jet_flavour;
    float Jet_nbHadrons;
    float Jet_JP;
    float Jet_JBP;
    float Jet_CSV;
    float Jet_CSVIVF;

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
    float TagVarCSV_trackSip3dSig_0;                      // highest track 3D signed IP of tracks belonging to a given jet   
    float TagVarCSV_trackSip3dSig_1;                      // second highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_2;                      // third highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_3;                      // fourth highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackPtRel_0;                         // highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_1;                         // second highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_2;                         // third highest track transverse momentum, relative to the jet axis
    float TagVarCSV_trackPtRel_3;                         // fourth highest track transverse momentum, relative to the jet axis
    // per jet per etaRel track
    float TagVarCSV_trackEtaRel_0;                        // lowest track eta relative to jet axis
    float TagVarCSV_trackEtaRel_1;                        // second lowest track eta relative to jet axis
    float TagVarCSV_trackEtaRel_2;                        // third lowest track eta relative to jet axis

    reader->AddVariable("TagVarCSV_vertexCategory",&TagVarCSV_vertexCategory);
    reader->AddVariable("TagVarCSV_jetNTracks",&TagVarCSV_jetNTracks);
    //reader->AddVariable("TagVarCSV_trackSip2dSig_0",&TagVarCSV_trackSip2dSig_0);
    //reader->AddVariable("TagVarCSV_trackSip2dSig_1",&TagVarCSV_trackSip2dSig_1);
    //reader->AddVariable("TagVarCSV_trackSip2dSig_2",&TagVarCSV_trackSip2dSig_2);
    //reader->AddVariable("TagVarCSV_trackSip2dSig_3",&TagVarCSV_trackSip2dSig_3);
    reader->AddVariable("TagVarCSV_trackSip3dSig_0",&TagVarCSV_trackSip3dSig_0);
    reader->AddVariable("TagVarCSV_trackSip3dSig_1",&TagVarCSV_trackSip3dSig_1);
    reader->AddVariable("TagVarCSV_trackSip3dSig_2",&TagVarCSV_trackSip3dSig_2);
    reader->AddVariable("TagVarCSV_trackSip3dSig_3",&TagVarCSV_trackSip3dSig_3);
    reader->AddVariable("TagVarCSV_trackPtRel_0",&TagVarCSV_trackPtRel_0);
    reader->AddVariable("TagVarCSV_trackPtRel_1",&TagVarCSV_trackPtRel_1);
    reader->AddVariable("TagVarCSV_trackPtRel_2",&TagVarCSV_trackPtRel_2);
    reader->AddVariable("TagVarCSV_trackPtRel_3",&TagVarCSV_trackPtRel_3);
    reader->AddVariable("TagVarCSV_trackSip2dSigAboveCharm",&TagVarCSV_trackSip2dSigAboveCharm);
    //reader->AddVariable("TagVarCSV_trackSip3dSigAboveCharm",&TagVarCSV_trackSip3dSigAboveCharm);
    reader->AddVariable("TagVarCSV_trackSumJetEtRatio",&TagVarCSV_trackSumJetEtRatio);
    reader->AddVariable("TagVarCSV_trackSumJetDeltaR",&TagVarCSV_trackSumJetDeltaR);
    reader->AddVariable("TagVarCSV_jetNTracksEtaRel",&TagVarCSV_jetNTracksEtaRel);
    reader->AddVariable("TagVarCSV_trackEtaRel_0",&TagVarCSV_trackEtaRel_0);
    reader->AddVariable("TagVarCSV_trackEtaRel_1",&TagVarCSV_trackEtaRel_1);
    reader->AddVariable("TagVarCSV_trackEtaRel_2",&TagVarCSV_trackEtaRel_2);
    reader->AddVariable("TagVarCSV_jetNSecondaryVertices",&TagVarCSV_jetNSecondaryVertices);
    reader->AddVariable("TagVarCSV_vertexMass",&TagVarCSV_vertexMass);
    reader->AddVariable("TagVarCSV_vertexNTracks",&TagVarCSV_vertexNTracks);
    reader->AddVariable("TagVarCSV_vertexEnergyRatio",&TagVarCSV_vertexEnergyRatio);
    reader->AddVariable("TagVarCSV_vertexJetDeltaR",&TagVarCSV_vertexJetDeltaR);
    reader->AddVariable("TagVarCSV_flightDistance2dSig",&TagVarCSV_flightDistance2dSig);
    //reader->AddVariable("TagVarCSV_flightDistance3dSig",&TagVarCSV_flightDistance3dSig);

    reader->AddSpectator("Jet_pt",&Jet_pt);
    reader->AddSpectator("Jet_eta",&Jet_eta);
    reader->AddSpectator("Jet_phi",&Jet_phi);
    reader->AddSpectator("Jet_mass",&Jet_mass);
    reader->AddSpectator("Jet_flavour",&Jet_flavour);
    reader->AddSpectator("Jet_nbHadrons",&Jet_nbHadrons);
    reader->AddSpectator("Jet_JP",&Jet_JP);
    reader->AddSpectator("Jet_JBP",&Jet_JBP);
    reader->AddSpectator("Jet_CSV",&Jet_CSV);
    reader->AddSpectator("Jet_CSVIVF",&Jet_CSVIVF);
    reader->AddSpectator("TagVarCSV_trackSip2dValAboveCharm",&TagVarCSV_trackSip2dValAboveCharm);
    reader->AddSpectator("TagVarCSV_trackSip3dValAboveCharm",&TagVarCSV_trackSip3dValAboveCharm);
    reader->AddSpectator("TagVarCSV_flightDistance2dVal",&TagVarCSV_flightDistance2dVal);
    reader->AddSpectator("TagVarCSV_flightDistance3dVal",&TagVarCSV_flightDistance3dVal);

    reader->BookMVA( "BDTG_T1000D3_BvsL method", "weights/TMVATrainer_AllVtx_BDTG_T1000D3_BvsL.weights.xml" );
    reader->BookMVA( "BDTG_T1000D3_BvsC method", "weights/TMVATrainer_AllVtx_BDTG_T1000D3_BvsC.weights.xml" );

    // input tree and such
    TString infilename="QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_JetTaggingVariables_evaluation.root";
    TFile in(infilename);
    TTree* intree = (TTree*)in.Get("tagVars/ttree");

    // set the branches to point to address of the variables declared above
    intree->SetBranchAddress("Jet_pt",&Jet_pt);
    intree->SetBranchAddress("Jet_eta",&Jet_eta);
    intree->SetBranchAddress("Jet_phi",&Jet_phi);
    intree->SetBranchAddress("Jet_mass",&Jet_mass);
    intree->SetBranchAddress("Jet_flavour",&Jet_flavour);
    intree->SetBranchAddress("Jet_nbHadrons",&Jet_nbHadrons);
    intree->SetBranchAddress("Jet_JP",&Jet_JP);
    intree->SetBranchAddress("Jet_JBP",&Jet_JBP);
    intree->SetBranchAddress("Jet_CSV",&Jet_CSV);
    intree->SetBranchAddress("Jet_CSVIVF",&Jet_CSVIVF);
    intree->SetBranchAddress("TagVarCSV_vertexCategory",&TagVarCSV_vertexCategory);
    intree->SetBranchAddress("TagVarCSV_jetNTracks",&TagVarCSV_jetNTracks);
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_0",&TagVarCSV_trackSip2dSig_0);
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_1",&TagVarCSV_trackSip2dSig_1);
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_2",&TagVarCSV_trackSip2dSig_2);
    intree->SetBranchAddress("TagVarCSV_trackSip2dSig_3",&TagVarCSV_trackSip2dSig_3);
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_0",&TagVarCSV_trackSip3dSig_0);
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_1",&TagVarCSV_trackSip3dSig_1);
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_2",&TagVarCSV_trackSip3dSig_2);
    intree->SetBranchAddress("TagVarCSV_trackSip3dSig_3",&TagVarCSV_trackSip3dSig_3);
    intree->SetBranchAddress("TagVarCSV_trackPtRel_0",&TagVarCSV_trackPtRel_0);
    intree->SetBranchAddress("TagVarCSV_trackPtRel_1",&TagVarCSV_trackPtRel_1);
    intree->SetBranchAddress("TagVarCSV_trackPtRel_2",&TagVarCSV_trackPtRel_2);
    intree->SetBranchAddress("TagVarCSV_trackPtRel_3",&TagVarCSV_trackPtRel_3);
    intree->SetBranchAddress("TagVarCSV_trackSip2dValAboveCharm",&TagVarCSV_trackSip2dValAboveCharm);
    intree->SetBranchAddress("TagVarCSV_trackSip2dSigAboveCharm",&TagVarCSV_trackSip2dSigAboveCharm);
    intree->SetBranchAddress("TagVarCSV_trackSip3dValAboveCharm",&TagVarCSV_trackSip3dValAboveCharm);
    intree->SetBranchAddress("TagVarCSV_trackSip3dSigAboveCharm",&TagVarCSV_trackSip3dSigAboveCharm);
    intree->SetBranchAddress("TagVarCSV_trackSumJetEtRatio",&TagVarCSV_trackSumJetEtRatio);
    intree->SetBranchAddress("TagVarCSV_trackSumJetDeltaR",&TagVarCSV_trackSumJetDeltaR);
    intree->SetBranchAddress("TagVarCSV_jetNTracksEtaRel",&TagVarCSV_jetNTracksEtaRel);
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_0",&TagVarCSV_trackEtaRel_0);
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_1",&TagVarCSV_trackEtaRel_1);
    intree->SetBranchAddress("TagVarCSV_trackEtaRel_2",&TagVarCSV_trackEtaRel_2);
    intree->SetBranchAddress("TagVarCSV_jetNSecondaryVertices",&TagVarCSV_jetNSecondaryVertices);
    intree->SetBranchAddress("TagVarCSV_vertexMass",&TagVarCSV_vertexMass);
    intree->SetBranchAddress("TagVarCSV_vertexNTracks",&TagVarCSV_vertexNTracks);
    intree->SetBranchAddress("TagVarCSV_vertexEnergyRatio",&TagVarCSV_vertexEnergyRatio);
    intree->SetBranchAddress("TagVarCSV_vertexJetDeltaR",&TagVarCSV_vertexJetDeltaR);
    intree->SetBranchAddress("TagVarCSV_flightDistance2dVal",&TagVarCSV_flightDistance2dVal);
    intree->SetBranchAddress("TagVarCSV_flightDistance2dSig",&TagVarCSV_flightDistance2dSig);
    intree->SetBranchAddress("TagVarCSV_flightDistance3dVal",&TagVarCSV_flightDistance3dVal);
    intree->SetBranchAddress("TagVarCSV_flightDistance3dSig",&TagVarCSV_flightDistance3dSig);

    TH1F* hBDTGDiscSig = new TH1F("hBDTGDiscSig","",1000,-5,5);
    TH1F* hBDTGDiscBkg = new TH1F("hBDTGDiscBkg","",1000,-5,5);

    TH1F* hCSVDiscSig = new TH1F("hCSVDiscSig","",1000,-5,5);
    TH1F* hCSVDiscBkg = new TH1F("hCSVDiscBkg","",1000,-5,5);

    TH1F* hCSVIVFDiscSig = new TH1F("hCSVIVFDiscSig","",1000,-5,5);
    TH1F* hCSVIVFDiscBkg = new TH1F("hCSVIVFDiscBkg","",1000,-5,5);

    hBDTGDiscSig->GetXaxis()->SetTitle("BDTG Discriminant");
    hBDTGDiscBkg->GetXaxis()->SetTitle("BDTG Discriminant");

    hCSVDiscSig->GetXaxis()->SetTitle("CSV Discriminant");
    hCSVDiscBkg->GetXaxis()->SetTitle("CSV Discriminant");
    hCSVIVFDiscSig->GetXaxis()->SetTitle("CSV Discriminant");
    hCSVIVFDiscBkg->GetXaxis()->SetTitle("CSV Discriminant");

    std::cout << "Now looping over " << intree->GetEntries() << " entries..." << std::endl;
    for(Long64_t iEntry = 0; iEntry < intree->GetEntries(); iEntry++){
	    if (iEntry % 1000 == 0) std::cout << "Processing Entry #" << iEntry << std::endl;
	    intree->GetEntry(iEntry); // all variables now filled!

	    if (vtxCategory >= 0 && TagVarCSV_vertexCategory != vtxCategory) continue;

	    bool isSig = ( abs(int(Jet_flavour)) == 5 );
	    bool isBkg = ( abs(int(Jet_flavour)) != 5 && abs(int(Jet_flavour)) != 4 );
	    float BDTG_Disc = (0.75*reader->EvaluateMVA("BDTG_T1000D3_BvsL method") + 0.25*reader->EvaluateMVA("BDTG_T1000D3_BvsC method"));

	    if (isSig) {
		    hBDTGDiscSig->Fill(BDTG_Disc);
		    hCSVDiscSig->Fill(Jet_CSV);
		    hCSVIVFDiscSig->Fill(Jet_CSVIVF);
	    }
	    else if (isBkg) {
		    hBDTGDiscBkg->Fill(BDTG_Disc);
		    hCSVDiscBkg->Fill(Jet_CSV);
		    hCSVIVFDiscBkg->Fill(Jet_CSVIVF);
	    }
    }

    TString outname = "QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_";
    TString postfix = "AllVtx";
    if( vtxCategory==0 )
      postfix = "RecoVtx";
    else if( vtxCategory==1 )
      postfix = "PseudoVtx";
    else if( vtxCategory==2 )
      postfix = "NoVtx";
    outname += postfix;
    outname += "_Combined.root";
    TFile out(outname,"RECREATE");

    hBDTGDiscSig->Write();
    hBDTGDiscBkg->Write();

    hCSVDiscSig->Write();
    hCSVDiscBkg->Write();
    hCSVIVFDiscSig->Write();
    hCSVIVFDiscBkg->Write();

    out.Close();

    delete reader;
    delete hBDTGDiscSig;
    delete hBDTGDiscBkg;
    delete hCSVDiscSig;
    delete hCSVDiscBkg;
    delete hCSVIVFDiscSig;
    delete hCSVIVFDiscBkg;

    std::cout << "Done analyzing!" << std::endl;

}