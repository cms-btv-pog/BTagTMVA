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

TString getWeightFileName(TString method){
        TString dir = "weights/";
        TString prefix = "TMVATrainer_";
        TString postfix = ".weights.xml";
        TString out =  dir + prefix + method + postfix;
        std::cout << "Reading from weight file: " << out << std::endl;
        return out;
}

void TMVAReaderTest(){
#ifdef __CINT__
        gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

        TMVA::Tools::Instance(); //loads libraries

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
    float TagVarCSV_trackJetPt;                           // track-based jet transverse momentum
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
    float TagVarCSV_trackSip2dSig_Leading;                // highest track 2D signed IP of tracks belonging to a given jet   
    float TagVarCSV_trackSip2dSig_SecondLeading;          // second highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip2dSig_ThirdLeading;           // third highest track 2D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_Leading;                // highest track 3D signed IP of tracks belonging to a given jet   
    float TagVarCSV_trackSip3dSig_SecondLeading;          // second highest track 3D signed IP of tracks belonging to a given jet
    float TagVarCSV_trackSip3dSig_ThirdLeading;           // third highest track 3D signed IP of tracks belonging to a given jet
    // per jet per etaRel track
    float TagVarCSV_trackEtaRel_Lowest;                   // lowest track eta relative to jet axis
    float TagVarCSV_trackEtaRel_SecondLowest;             // second lowest track eta relative to jet axis
    float TagVarCSV_trackEtaRel_ThirdLowest;              // third lowest track eta relative to jet axis

        reader->AddVariable("TagVarCSV_jetNTracks",&TagVarCSV_jetNTracks);
        reader->AddVariable("TagVarCSV_jetNTracksEtaRel",&TagVarCSV_jetNTracksEtaRel);
        reader->AddVariable("TagVarCSV_trackSip3dSig_Leading",&TagVarCSV_trackSip3dSig_Leading);
        reader->AddVariable("TagVarCSV_trackSip3dSig_SecondLeading",&TagVarCSV_trackSip3dSig_SecondLeading);
        reader->AddVariable("TagVarCSV_trackSip3dSig_ThirdLeading",&TagVarCSV_trackSip3dSig_ThirdLeading);
        reader->AddVariable("TagVarCSV_trackSip2dSigAboveCharm",&TagVarCSV_trackSip2dSigAboveCharm);
        reader->AddVariable("TagVarCSV_trackEtaRel_Lowest",&TagVarCSV_trackEtaRel_Lowest);
        reader->AddVariable("TagVarCSV_trackEtaRel_SecondLowest",&TagVarCSV_trackEtaRel_SecondLowest);
        reader->AddVariable("TagVarCSV_trackEtaRel_ThirdLowest",&TagVarCSV_trackEtaRel_ThirdLowest);
        reader->AddVariable("TagVarCSV_vertexMass",&TagVarCSV_vertexMass);
        reader->AddVariable("TagVarCSV_vertexNTracks",&TagVarCSV_vertexNTracks);
        reader->AddVariable("TagVarCSV_vertexEnergyRatio",&TagVarCSV_vertexEnergyRatio);
        reader->AddVariable("TagVarCSV_flightDistance2dSig",&TagVarCSV_flightDistance2dSig);

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
        reader->AddSpectator("TagVarCSV_trackJetPt",&TagVarCSV_trackJetPt);
        reader->AddSpectator("TagVarCSV_trackSumJetEtRatio",&TagVarCSV_trackSumJetEtRatio);
        reader->AddSpectator("TagVarCSV_trackSumJetDeltaR",&TagVarCSV_trackSumJetDeltaR);
        reader->AddSpectator("TagVarCSV_trackSip2dValAboveCharm",&TagVarCSV_trackSip2dValAboveCharm);
        reader->AddSpectator("TagVarCSV_trackSip3dValAboveCharm",&TagVarCSV_trackSip3dValAboveCharm);
        reader->AddSpectator("TagVarCSV_trackSip3dSigAboveCharm",&TagVarCSV_trackSip3dSigAboveCharm);
        reader->AddSpectator("TagVarCSV_vertexCategory",&TagVarCSV_vertexCategory);
        reader->AddSpectator("TagVarCSV_jetNSecondaryVertices",&TagVarCSV_jetNSecondaryVertices);
        reader->AddSpectator("TagVarCSV_vertexJetDeltaR",&TagVarCSV_vertexJetDeltaR);
        reader->AddSpectator("TagVarCSV_flightDistance2dVal",&TagVarCSV_flightDistance2dVal);
        reader->AddSpectator("TagVarCSV_flightDistance3dVal",&TagVarCSV_flightDistance3dVal);
        reader->AddSpectator("TagVarCSV_flightDistance3dSig",&TagVarCSV_flightDistance3dSig);
        reader->AddSpectator("TagVarCSV_trackSip2dSig_Leading",&TagVarCSV_trackSip2dSig_Leading);
        reader->AddSpectator("TagVarCSV_trackSip2dSig_SecondLeading",&TagVarCSV_trackSip2dSig_SecondLeading);
        reader->AddSpectator("TagVarCSV_trackSip2dSig_ThirdLeading",&TagVarCSV_trackSip2dSig_ThirdLeading);

        //book the MVA method(s)
        std::vector< TString > methods;
        methods.push_back("BDTG"); //T1000_D2
        methods.push_back("BDTG_T1000_D5");
        methods.push_back("BDTG_T500_D2");
        methods.push_back("BDTG_T500_D5");
        for (int methodNum = 0; methodNum < methods.size(); methodNum++){
                TString method = methods.at( methodNum );
                reader->BookMVA( method+" method",getWeightFileName(method) );
        }

        // input tree and such
        // TString rootfile = TString::Format("CMSSW_Job_%i.root",jobNum);
        // TString infilename = "/cms/skaplan/BoostedBTagValidation/CMSSW_5_3_18/src/MyAnalysis/TagVarExtractor/test/qcd300-470_output/output/"+rootfile;
        TString infilename="./TagVarTree_RadionM800.root";
        TFile in(infilename);
        TTree* intree = (TTree*)in.Get("tagVars/ttree");

        //set the branches to point to address of the variables declared above
        intree->SetBranchAddress("TagVarCSV_jetNTracks",&TagVarCSV_jetNTracks);
        intree->SetBranchAddress("TagVarCSV_jetNTracksEtaRel",&TagVarCSV_jetNTracksEtaRel);
        intree->SetBranchAddress("TagVarCSV_trackSip3dSig_Leading",&TagVarCSV_trackSip3dSig_Leading);
        intree->SetBranchAddress("TagVarCSV_trackSip3dSig_SecondLeading",&TagVarCSV_trackSip3dSig_SecondLeading);
        intree->SetBranchAddress("TagVarCSV_trackSip3dSig_ThirdLeading",&TagVarCSV_trackSip3dSig_ThirdLeading);
        intree->SetBranchAddress("TagVarCSV_trackSip2dSigAboveCharm",&TagVarCSV_trackSip2dSigAboveCharm);
        intree->SetBranchAddress("TagVarCSV_trackEtaRel_Lowest",&TagVarCSV_trackEtaRel_Lowest);
        intree->SetBranchAddress("TagVarCSV_trackEtaRel_SecondLowest",&TagVarCSV_trackEtaRel_SecondLowest);
        intree->SetBranchAddress("TagVarCSV_trackEtaRel_ThirdLowest",&TagVarCSV_trackEtaRel_ThirdLowest);
        intree->SetBranchAddress("TagVarCSV_vertexMass",&TagVarCSV_vertexMass);
        intree->SetBranchAddress("TagVarCSV_vertexNTracks",&TagVarCSV_vertexNTracks);
        intree->SetBranchAddress("TagVarCSV_vertexEnergyRatio",&TagVarCSV_vertexEnergyRatio);
        intree->SetBranchAddress("TagVarCSV_flightDistance2dSig",&TagVarCSV_flightDistance2dSig);

        //set the branches for the spectator variables also in case they're needed
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
        intree->SetBranchAddress("TagVarCSV_trackJetPt",&TagVarCSV_trackJetPt);
        intree->SetBranchAddress("TagVarCSV_trackSumJetEtRatio",&TagVarCSV_trackSumJetEtRatio);
        intree->SetBranchAddress("TagVarCSV_trackSumJetDeltaR",&TagVarCSV_trackSumJetDeltaR);
        intree->SetBranchAddress("TagVarCSV_trackSip2dValAboveCharm",&TagVarCSV_trackSip2dValAboveCharm);
        intree->SetBranchAddress("TagVarCSV_trackSip3dValAboveCharm",&TagVarCSV_trackSip3dValAboveCharm);
        intree->SetBranchAddress("TagVarCSV_trackSip3dSigAboveCharm",&TagVarCSV_trackSip3dSigAboveCharm);
        intree->SetBranchAddress("TagVarCSV_vertexCategory",&TagVarCSV_vertexCategory);
        intree->SetBranchAddress("TagVarCSV_jetNSecondaryVertices",&TagVarCSV_jetNSecondaryVertices);
        intree->SetBranchAddress("TagVarCSV_vertexJetDeltaR",&TagVarCSV_vertexJetDeltaR);
        intree->SetBranchAddress("TagVarCSV_flightDistance2dVal",&TagVarCSV_flightDistance2dVal);
        intree->SetBranchAddress("TagVarCSV_flightDistance3dVal",&TagVarCSV_flightDistance3dVal);
        intree->SetBranchAddress("TagVarCSV_flightDistance3dSig",&TagVarCSV_flightDistance3dSig);
        intree->SetBranchAddress("TagVarCSV_trackSip2dSig_Leading",&TagVarCSV_trackSip2dSig_Leading);
        intree->SetBranchAddress("TagVarCSV_trackSip2dSig_SecondLeading",&TagVarCSV_trackSip2dSig_SecondLeading);
        intree->SetBranchAddress("TagVarCSV_trackSip2dSig_ThirdLeading",&TagVarCSV_trackSip2dSig_ThirdLeading);

        TH1F* hBDTGDiscSig = new TH1F("hBDTGDiscSig","",1000,-5,5);
        TH1F* hBDTGDiscBkg = new TH1F("hBDTGDiscBkg","",1000,-5,5);

        TH1F* hBDTGT500D2DiscSig = new TH1F("hBDTGT500D2DiscSig","",1000,-5,5);
        TH1F* hBDTGT500D2DiscBkg = new TH1F("hBDTGT500D2DiscBkg","",1000,-5,5);

        TH1F* hBDTGT1000D5DiscSig = new TH1F("hBDTGT1000D5DiscSig","",1000,-5,5);
        TH1F* hBDTGT1000D5DiscBkg = new TH1F("hBDTGT1000D5DiscBkg","",1000,-5,5);

        TH1F* hBDTGT500D5DiscSig = new TH1F("hBDTGT500D5DiscSig","",1000,-5,5);
        TH1F* hBDTGT500D5DiscBkg = new TH1F("hBDTGT500D5DiscBkg","",1000,-5,5);

        TH1F* hCSVDiscSig = new TH1F("hCSVDiscSig","",1000,-5,5);
        TH1F* hCSVDiscBkg = new TH1F("hCSVDiscBkg","",1000,-5,5);

        TH1F* hCSVIVFDiscSig = new TH1F("hCSVIVFDiscSig","",1000,-5,5);
        TH1F* hCSVIVFDiscBkg = new TH1F("hCSVIVFDiscBkg","",1000,-5,5);

        hBDTGDiscSig->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGDiscBkg->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGT500D2DiscSig->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGT500D2DiscBkg->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGT1000D5DiscSig->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGT1000D5DiscBkg->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGT500D5DiscSig->GetXaxis()->SetTitle("BDTG Discriminant");
        hBDTGT500D5DiscBkg->GetXaxis()->SetTitle("BDTG Discriminant");

        hCSVDiscSig->GetXaxis()->SetTitle("CSV Discriminant");
        hCSVDiscBkg->GetXaxis()->SetTitle("CSV Discriminant");
        hCSVIVFDiscSig->GetXaxis()->SetTitle("CSV Discriminant");
        hCSVIVFDiscBkg->GetXaxis()->SetTitle("CSV Discriminant");

        std::cout << "Now looping over " << intree->GetEntries() << " entries..." << std::endl;
        for(Long64_t iEntry = 0; iEntry < intree->GetEntries(); iEntry++){
                if (iEntry % 1000 == 0) std::cout << "Processing Entry #" << iEntry << std::endl;
                intree->GetEntry(iEntry); //all variables now filled!
                if (TagVarCSV_vertexCategory != 0) continue;
                bool isB = ( abs(Jet_flavour) == 5 );
                bool isLight = ( abs(Jet_flavour) == 1 || abs(Jet_flavour) == 2 || abs(Jet_flavour) == 3 || Jet_flavour == 21 );
                float BDTG_Disc = reader->EvaluateMVA("BDTG method");
                //std::cout << reader->EvaluateMVA("BDTG method") << std::endl;
                float BDTG_T500_D5_Disc = reader->EvaluateMVA("BDTG_T500_D5 method");
                float BDTG_T500_D2_Disc = reader->EvaluateMVA("BDTG_T500_D2 method");
                float BDTG_T1000_D5_Disc = reader->EvaluateMVA("BDTG_T1000_D5 method");
                if (isB) {
                        hBDTGDiscSig->Fill(BDTG_Disc);
                        hBDTGT500D5DiscSig->Fill(BDTG_T500_D5_Disc);
                        hBDTGT500D2DiscSig->Fill(BDTG_T500_D2_Disc);
                        hBDTGT1000D5DiscSig->Fill(BDTG_T1000_D5_Disc);
                        hCSVDiscSig->Fill(Jet_CSV);
                        hCSVIVFDiscSig->Fill(Jet_CSVIVF);
                }
                else if (isLight) {
                        hBDTGDiscBkg->Fill(BDTG_Disc);
                        hBDTGT500D5DiscBkg->Fill(BDTG_T500_D5_Disc);
                        hBDTGT500D2DiscBkg->Fill(BDTG_T500_D2_Disc);
                        hBDTGT1000D5DiscBkg->Fill(BDTG_T1000_D5_Disc);
                        hCSVDiscBkg->Fill(Jet_CSV);
                        hCSVIVFDiscBkg->Fill(Jet_CSVIVF);
                }
        }
        // TString outname = TString::Format("TMVAanyl_QCD300-470Plots_%i.root",jobNum);
        TString outname = "TMVAanyl_RadionM800_RadionTraining.root";
        TFile out(outname,"RECREATE");
        
        hBDTGDiscSig->Write();
        hBDTGDiscBkg->Write();
        hBDTGT1000D5DiscSig->Write();
        hBDTGT1000D5DiscBkg->Write();
        hBDTGT500D2DiscSig->Write();
        hBDTGT500D2DiscBkg->Write();
        hBDTGT500D5DiscSig->Write();
        hBDTGT500D5DiscBkg->Write();

        hCSVDiscSig->Write();
        hCSVDiscBkg->Write();

        out.Close();

        delete reader;
        delete hBDTGDiscSig;
        delete hBDTGDiscBkg;
        delete hBDTGT1000D5DiscSig;
        delete hBDTGT1000D5DiscBkg;
        delete hBDTGT500D2DiscSig;
        delete hBDTGT500D2DiscBkg;
        delete hBDTGT500D5DiscSig;
        delete hBDTGT500D5DiscBkg;
        delete hCSVDiscSig;
        delete hCSVDiscBkg;
        delete hCSVIVFDiscSig;
        delete hCSVIVFDiscBkg;

        std::cout << "Done analyzing!" << std::endl;





}