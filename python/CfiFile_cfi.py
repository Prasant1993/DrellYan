import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('DrellYan',
                      verbosity = cms.bool(False),
                      isMC = cms.bool(True),
                      vertexSrc = cms.InputTag('selectedPrimaryVertices'),
                      muonSrc = cms.InputTag('slimmedMuons'),
                      electronSrc = cms.InputTag('slimmedElectrons'),
                      photonSrc = cms.InputTag('slimmedPhotons'),
                      tauSrc = cms.InputTag('slimmedTaus'), 
                      isolatedtrackSrc = cms.InputTag('isolatedTracks'),
                      METSrc = cms.InputTag('slimmedMETs'),       
                      JETSrc = cms.InputTag('slimmedJets'),
                      genparticleSrc = cms.InputTag('prunedGenParticles')
)
