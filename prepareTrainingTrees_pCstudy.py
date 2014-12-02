print "Importing ROOT..."
from ROOT import *
from numpy import *
print "done."
print ""

bJetFile = TFile("qcd80-120_training_bjets.root","READ")
cJetFile = TFile("qcd80-120_training_cjets.root","READ")
lightJetFile = TFile("qcd80-120_training_lightjets.root","READ")

bJetTree = bJetFile.Get("ttree")
cJetTree = cJetFile.Get("ttree")
lightJetTree = lightJetFile.Get("ttree")

numBJets = bJetTree.GetEntries()

# percentages of c jets we will consider (light percentage is 1-c)
percentC = (0.05,0.25,0.75)

tr = TRandom2()

for scenario in range( len(percentC) ):

    pC = percentC[scenario]
    pL = 1.-pC

    print "Now building trees where percentC=%.2f and percentLight=%.2f"%(pC,pL)

    newCTree = cJetTree.CloneTree(0)
    newLTree = lightJetTree.CloneTree(0)
 
    for i in range(numBJets):
        keepC = bool( tr.Binomial(1,pC) )
        keepL = bool( tr.Binomial(1,pL) )
        cJetTree.GetEntry(i)
        lightJetTree.GetEntry(i)
        if keepC:
            newCTree.Fill()
        if keepL:
            newLTree.Fill()

    newCFile = TFile("cjets_pC%i.root"%(100*pC),"RECREATE")
    newCTree.Write()
    newCFile.Close()

    newLFile = TFile("lightjets_pC%i.root"%(100*pC),"RECREATE")
    newLTree.Write()
    newLFile.Close()
