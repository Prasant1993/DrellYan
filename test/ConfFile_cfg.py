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
    input = cms.untracked.int32(10000)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/00F9D855-E293-E711-B625-02163E014200.root'
 #  '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0000BD66-99F4-E711-97DF-24BE05C33C22.root',
#'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/000DD294-E8F5-E711-8B8F-003048F5970A.root'                                                                                                              
 
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
                                       fileName = cms.string('output_histos.root')
                                   )

process.p = cms.Path(process.selectedPrimaryVertices*process.demo)
