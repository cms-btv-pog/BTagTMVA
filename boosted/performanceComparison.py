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
    bkg.SetTitleOffset(1.2,"X")
    bkg.SetTitleOffset(1.5,"Y")
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
    l1.DrawLatex(0.58,0.18, fExtraInfo)

    c.SaveAs(fOutputFile)


def makePlots():
    # for multiple plots on the same canvas

    #-------------------------------
    # BB vs QCD
    ordering = [] # vectors storing the order of legend entries
    graphMap = {} # maps to hold legend entries and TGraph*s

    graphMap["Fat jet CSVv2+IVF"]       = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsQCD.root","BDTG_vs_CSVv2IVF_BBvsQCD.root","hFatCSVIVFDiscSig","hFatCSVIVFDiscBkg")
    graphMap["Subjet CSVv2+IVF"]        = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsQCD.root","BDTG_vs_CSVv2IVF_BBvsQCD.root","hSubCSVIVFDiscSig","hSubCSVIVFDiscBkg")
    graphMap["BDTG fat+sub BBvsQCD"]    = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsQCD.root","BDTG_vs_CSVv2IVF_BBvsQCD.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG fat BBvsQCD"]        = getPerformanceCurve("BDTG_vs_CSVv2IVF_fat_BBvsQCD.root","BDTG_vs_CSVv2IVF_fat_BBvsQCD.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG fat+subCSV BBvsQCD"] = getPerformanceCurve("BDTG_vs_CSVv2IVF_fat_subCSV_BBvsQCD.root","BDTG_vs_CSVv2IVF_fat_subCSV_BBvsQCD.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("Fat jet CSVv2+IVF")
    ordering.append("Subjet CSVv2+IVF")
    ordering.append("BDTG fat BBvsQCD")
    ordering.append("BDTG fat+sub BBvsQCD")
    ordering.append("BDTG fat+subCSV BBvsQCD")

    plotPerformanceCurves(graphMap,ordering,"","tagging rate (H#rightarrowb#bar{b})","mistag rate (inclusive QCD)","","tmvacomp_BDTG_CSV_BBvsQCD.pdf",0, 1, 1E-3, 1, 1)

    #-------------------------------
    # BB vs B
    ordering = [] # vectors storing the order of legend entries
    graphMap = {} # maps to hold legend entries and TGraph*s

    graphMap["Fat jet CSVv2+IVF"]     = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsB.root","BDTG_vs_CSVv2IVF_BBvsB.root","hFatCSVIVFDiscSig","hFatCSVIVFDiscBkg")
    graphMap["Subjet CSVv2+IVF"]      = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsB.root","BDTG_vs_CSVv2IVF_BBvsB.root","hSubCSVIVFDiscSig","hSubCSVIVFDiscBkg")
    graphMap["BDTG fat+sub BBvsB"]    = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsB.root","BDTG_vs_CSVv2IVF_BBvsB.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG fat BBvsB"]        = getPerformanceCurve("BDTG_vs_CSVv2IVF_fat_BBvsB.root","BDTG_vs_CSVv2IVF_fat_BBvsB.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG fat+subCSV BBvsB"] = getPerformanceCurve("BDTG_vs_CSVv2IVF_fat_subCSV_BBvsB.root","BDTG_vs_CSVv2IVF_fat_subCSV_BBvsB.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("Fat jet CSVv2+IVF")
    ordering.append("Subjet CSVv2+IVF")
    ordering.append("BDTG fat BBvsB")
    ordering.append("BDTG fat+sub BBvsB")
    ordering.append("BDTG fat+subCSV BBvsB")

    plotPerformanceCurves(graphMap,ordering,"","tagging rate (H#rightarrowb#bar{b})","mistag rate (b jets)","","tmvacomp_BDTG_CSV_BBvsB.pdf",0, 1, 1E-3, 1, 0)

    #-------------------------------
    # BB vs GSP
    ordering = [] # vectors storing the order of legend entries
    graphMap = {} # maps to hold legend entries and TGraph*s

    graphMap["Fat jet CSVv2+IVF"]       = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsGSP.root","BDTG_vs_CSVv2IVF_BBvsGSP.root","hFatCSVIVFDiscSig","hFatCSVIVFDiscBkg")
    graphMap["Subjet CSVv2+IVF"]        = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsGSP.root","BDTG_vs_CSVv2IVF_BBvsGSP.root","hSubCSVIVFDiscSig","hSubCSVIVFDiscBkg")
    graphMap["BDTG fat+sub BBvsGSP"]    = getPerformanceCurve("BDTG_vs_CSVv2IVF_BBvsGSP.root","BDTG_vs_CSVv2IVF_BBvsGSP.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG fat BBvsGSP"]        = getPerformanceCurve("BDTG_vs_CSVv2IVF_fat_BBvsGSP.root","BDTG_vs_CSVv2IVF_fat_BBvsGSP.root","hBDTGDiscSig","hBDTGDiscBkg")
    graphMap["BDTG fat+subCSV BBvsGSP"] = getPerformanceCurve("BDTG_vs_CSVv2IVF_fat_subCSV_BBvsGSP.root","BDTG_vs_CSVv2IVF_fat_subCSV_BBvsGSP.root","hBDTGDiscSig","hBDTGDiscBkg")

    ordering.append("Fat jet CSVv2+IVF")
    ordering.append("Subjet CSVv2+IVF")
    ordering.append("BDTG fat BBvsGSP")
    ordering.append("BDTG fat+sub BBvsGSP")
    ordering.append("BDTG fat+subCSV BBvsGSP")

    plotPerformanceCurves(graphMap,ordering,"","tagging rate (H#rightarrowb#bar{b})","mistag rate (g#rightarrowb#bar{b} splitting)","","tmvacomp_BDTG_CSV_BBvsGSP.pdf",0, 1, 1E-3, 1, 0)

    #-------------------------------

if __name__ == "__main__":
    makePlots()
