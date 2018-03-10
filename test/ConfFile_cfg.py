import FWCore.ParameterSet.Config as cms
#import FWCore.ParameterSet.Config as cms

process = cms.Process("OnlineAnalysis")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/00F9D855-E293-E711-B625-02163E014200.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/00F55CC9-B694-E711-A550-0CC47A7C3420.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/0C6E4056-9494-E711-BC5F-0CC47AD98C5E.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/22F6175C-F495-E711-89BB-FA163EFA220C.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/10FA79CF-AB94-E711-8A25-0CC47A7C35F8.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/282D466D-B094-E711-BF51-0025905A608E.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/06ED1148-1794-E711-9388-02163E013722.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/16535AEC-8B94-E711-B08C-008CFAE45264.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/0AC33351-A394-E711-A3CF-0CC47AD9908C.root',
#    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/1AAA5A56-9494-E711-B79C-0CC47AA98F92.root'

         # '/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD'
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/00701B6B-E9DB-E711-B111-02163E019D6D.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/064D4B85-E9DB-E711-8B34-02163E019D0E.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/0C1A94F7-B5DB-E711-A77F-02163E019B5C.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/149D288E-90DC-E711-A696-A0B3CCE45C2A.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/1CD7CF1B-2EDC-E711-978C-02163E019E8A.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/1E863310-F8DB-E711-B451-02163E01A288.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/20E9AFEF-95DC-E711-B716-7845C4FC370A.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/28C212C2-C1DB-E711-A527-02163E01419C.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/2C58619E-D9DB-E711-B747-02163E011CA5.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/2EC10401-C8DB-E711-8732-02163E0145EA.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/307C8711-13DC-E711-9980-A0369F83627A.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/347F1E7A-E9DB-E711-BFE4-02163E019BB3.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/36768FF3-D3DB-E711-90CB-02163E019D0E.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/3A72221F-D4DB-E711-AD84-02163E01A762.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/3C67D8C5-C1DB-E711-8DBC-02163E01A42F.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/3CDF977C-CEDB-E711-B024-02163E019D5D.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/3E945133-E3DB-E711-B979-02163E01A5CC.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/447506F9-C7DB-E711-B621-02163E01451A.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/4C96E316-94DC-E711-88BD-90B11CBCFF5B.root',
 #       '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/4E30114C-13DC-E711-B86D-02163E01A762.root'
        '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0000BD66-99F4-E711-97DF-24BE05C33C22.root'
  #      '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/000DD294-E8F5-E711-8B8F-003048F5970A.root',
 #       '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0098E9A5-49FF-E711-9A09-008CFAFBF52E.root',
#        '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/00DB02C9-C7F7-E711-8756-549F3525E81C.root'
     
                                                                                                                 
 
   )
)
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag.globaltag = '94X_mc2017_realistic_v10'

# Primary Vertex Selector
process.selectedPrimaryVertices = cms.EDFilter("VertexSelector",
  src = cms.InputTag('offlineSlimmedPrimaryVertices'),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && abs(position.Rho) <= 2"),
  filter = cms.bool(True)                                          
)



process.load("Analysis.DrellYan.CfiFile_cfi")
process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('output_histos_mc_genmatch_muon.root')
                                   )

process.p = cms.Path(process.selectedPrimaryVertices*process.demo)
