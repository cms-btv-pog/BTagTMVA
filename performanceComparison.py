from ROOT import *

def getPerformanceCurve(fFileS1, fFileB1, fPlotS1, fPlotB1, fXMin=0, fXMax=0):
    #get files and histograms
    file_S1 = TFile(fFileS1)
    file_B1 = TFile(fFileB1)

    h2_S_1 = file_S1.Get(fPlotS1)
    h2_B_1 = file_B1.Get(fPlotB1)

    #total jet count for denominator of efficiency calculation
    denom_S_1 = float( h2_S_1.Integral(380,610) )
    denom_B_1 = float( h2_B_1.Integral(380,610) )

    g_eff_1 = TGraph(49)

    for i in range(5):
        num_S = float( h2_S_1.Integral(602-i,602) )
        num_B = float( h2_B_1.Integral(602-i,602) )
        g_eff_1.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )

    for i in range(1,40):
        num_S = float( h2_S_1.Integral(602-(i*5),602) )
        num_B = float( h2_B_1.Integral(602-(i*5),602) )
        g_eff_1.SetPoint( i+4,(num_S/denom_S_1),(num_B/denom_B_1) )

    for i in range(1,6):
        num_S = float( h2_S_1.Integral(407-i,602) )
        num_B = float( h2_B_1.Integral(407-i,602) )
        g_eff_1.SetPoint(i+43,(num_S/denom_S_1),(num_B/denom_B_1))

    return g_eff_1

def formatGraph(graph, graphNum):
    colors = [ kGreen+2, kRed, kBlue, kBlack, kMagenta, kOrange+2, kCyan ]
    graphColor = colors[graphNum % 7]
    lineStyle = (graphNum % 11) + 1
    graph.SetLineColor(graphColor)
    graph.SetLineStyle(lineStyle)
    graph.SetLineWidth(2)

def plotPerformanceCurves(graphs, ordering, fTitle, fXAxisTitle, fYAxisTitle, fExtraInfo, fOutputFile, fXmin, fXmax, fYmin, fYmax, fLogy=0):

    gROOT.SetBatch(kTRUE)
    gStyle.SetGridColor(kGray)
    gStyle.SetOptStat(kFALSE)
    gStyle.SetPadTopMargin(0.07)
    gStyle.SetPadBottomMargin(0.13)
    gStyle.SetPadLeftMargin(0.14)
    gStyle.SetPadRightMargin(0.06)
    gROOT.ForceStyle()

    c = TCanvas("c", "",800,800)
    c.cd()
    bkg = TH2D("bkg","",100,fXmin,fXmax,100,fYmin,fYmax)
    bkg.GetXaxis().SetTitle(fXAxisTitle)
    bkg.GetYaxis().SetTitle(fYAxisTitle)
    bkg.SetTitleOffset(1.1,"Y")
    bkg.Draw()
    c.SetGridx()
    c.SetGridy()

    legend = TLegend(.16,.64,.36,.77)
    legend.SetBorderSize(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.021)

    graphCounter = 0
    for g in ordering:
        graph = graphs[g]
        legend.AddEntry(graph, g,"l")
        formatGraph(graph,graphCounter)
        graph.Draw("L")
        graphCounter += 1

    if (fLogy):
        c.SetLogy()
    legend.Draw()
    l1 = TLatex()
    l1.SetTextAlign(13)
    l1.SetTextFont(42)
    l1.SetNDC()
    l1.SetTextSize(0.04)
    l1.DrawLatex(0.14+0.03,0.90, fTitle)

    l1.SetTextAlign(12)
    l1.SetTextSize(0.045)
    l1.SetTextFont(62)
    l1.DrawLatex(0.14,0.96, "CMS Simulation Preliminary, #sqrt{s} = 8 TeV")

    l1.SetTextFont(42)
    l1.SetTextSize(0.025)
    l1.DrawLatex(0.48,0.18, fExtraInfo)

    c.SaveAs(fOutputFile)


def makePlots():
    # for multiple plots on the same canvas

    # vectors storing the order of legend entries
    ordering = []
    # maps to hold legend entries and TGraph*s
    graphMap = {}

    #-------------------------------
    # All vertices

    graphMap["CSV"]          = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV.root","hCSVDiscSig","hCSVDiscBkg")
    graphMap["CSVv2+IVF"]    = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV.root","hCSVIVFDiscSig","hCSVIVFDiscBkg")
    graphMap["BDTG T1000D5"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV.root","hBDTGDiscSig","hBDTGDiscBkg")
    #graphMap["BDTG T1000D5 VtxCategory"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_AllVtxCategory.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_AllVtxCategory.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("CSV")
    ordering.append("CSVv2+IVF")
    ordering.append("BDTG T1000D5")
    #ordering.append("BDTG T1000D5 VtxCategory")

    plotPerformanceCurves(graphMap,ordering,"","b-tagging efficiency (b jets)","mistag rate (QCD light jets)","All vtx categories","tmvacomp_BDTG_CSV.pdf",0, 1, 1E-4, 1,1)

    #-------------------------------
    # RecoVertex category
    ordering = []
    graphMap = {}

    graphMap["CSV"]          = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0.root","hCSVDiscSig","hCSVDiscBkg")
    graphMap["CSVv2+IVF"]    = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0.root","hCSVIVFDiscSig","hCSVIVFDiscBkg")
    graphMap["BDTG T1000D5"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG T1000D5 RecoVtxTraining"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0_VtxCat0Training.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat0_VtxCat0Training.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("CSV")
    ordering.append("CSVv2+IVF")
    ordering.append("BDTG T1000D5")
    ordering.append("BDTG T1000D5 RecoVtxTraining")

    plotPerformanceCurves(graphMap,ordering,"","b-tagging efficiency (b jets)","mistag rate (QCD light jets)","RecoVertex category","tmvacomp_BDTG_CSV_RecoVtx.pdf",0, 1, 1E-4, 1,1)

    #-------------------------------
    # PseudoVertex category
    ordering = []
    graphMap = {}

    graphMap["CSV"]          = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1.root","hCSVDiscSig","hCSVDiscBkg")
    graphMap["CSVv2+IVF"]    = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1.root","hCSVIVFDiscSig","hCSVIVFDiscBkg")
    graphMap["BDTG T1000D5"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG T1000D5 PseudoVtxTraining"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1_VtxCat1Training.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat1_VtxCat1Training.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("CSV")
    ordering.append("CSVv2+IVF")
    ordering.append("BDTG T1000D5")
    ordering.append("BDTG T1000D5 PseudoVtxTraining")

    plotPerformanceCurves(graphMap,ordering,"","b-tagging efficiency (b jets)","mistag rate (QCD light jets)","PseudoVertex category","tmvacomp_BDTG_CSV_PseudoVtx.pdf",0, 1, 1E-4, 1,1)

    #-------------------------------
    # NoVertex category
    ordering = []
    graphMap = {}

    graphMap["CSV"]          = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2.root","hCSVDiscSig","hCSVDiscBkg")
    graphMap["CSVv2+IVF"]    = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2.root","hCSVIVFDiscSig","hCSVIVFDiscBkg")
    graphMap["BDTG T1000D5"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG T1000D5 NoVtxTraining"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2_VtxCat2Training.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTG_vs_CSV_VtxCat2_VtxCat2Training.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("CSV")
    ordering.append("CSVv2+IVF")
    ordering.append("BDTG T1000D5")
    ordering.append("BDTG T1000D5 NoVtxTraining")

    plotPerformanceCurves(graphMap,ordering,"","b-tagging efficiency (b jets)","mistag rate (QCD light jets)","NoVertex category","tmvacomp_BDTG_CSV_NoVtx.pdf",0, 1, 1E-4, 1,1)

    #-------------------------------
    # All vertices v2
    ordering = []
    graphMap = {}

    graphMap["CSV"]          = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTGv2_vs_CSV.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTGv2_vs_CSV.root","hCSVDiscSig","hCSVDiscBkg")
    graphMap["CSVv2+IVF"]    = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTGv2_vs_CSV.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTGv2_vs_CSV.root","hCSVIVFDiscSig","hCSVIVFDiscBkg")
    graphMap["BDTGv2 T1000D5"] = getPerformanceCurve("QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTGv2_vs_CSV.root","QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_BDTGv2_vs_CSV.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("CSV")
    ordering.append("CSVv2+IVF")
    ordering.append("BDTGv2 T1000D5")

    plotPerformanceCurves(graphMap,ordering,"","b-tagging efficiency (b jets)","mistag rate (QCD light jets)","All vtx categories","tmvacomp_BDTGv2_CSV.pdf",0, 1, 1E-4, 1,1)


if __name__ == "__main__":
    makePlots()
