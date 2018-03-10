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
    #'file:/eos/user/s/sroychow/HZZ4l/Rereco/MuonTnp/ztnpisoAna/00F9D855-E293-E711-B625-02163E014200.root'
   '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0000BD66-99F4-E711-97DF-24BE05C33C22.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/000DD294-E8F5-E711-8B8F-003048F5970A.root',                                                                                                                '/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0098E9A5-49FF-E711-9A09-008CFAFBF52E.root',                                                                                                              
' /store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/00DB02C9-C7F7-E711-8756-549F3525E81C.root',                                                                                                             
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/028E2785-FFFC-E711-8F07-44A842CF0627.root',                                                                                                              
' /store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/043785DE-CDF4-E711-82EB-0CC47AA98F92.root',                                                                                                             
' /store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/04632AD8-91F7-E711-97B3-008CFAE45090.root',                                                                                                             
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/04CD2C41-CBF7-E711-9389-0CC47A13D3B2.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/04CE01CA-2DF5-E711-AE27-001E67E6F909.root',                                                                                                              
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/06C736A2-F600-E811-B3DF-002590E7E01A.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0820DA1A-C4F3-E711-973E-008CFAE45104.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/08643EAC-10F5-E711-971A-00E081CAD378.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/087F8D9E-F4F5-E711-AAC1-FA163EA855C8.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0881A869-D4F6-E711-8AD5-0242AC1C0500.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0A0AE852-CEF3-E711-A795-008CFAC91E74.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0A2BF7B4-BBF6-E711-9FCA-002590E3A286.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0AD2A823-C5F3-E711-B5B4-0CC47AD98F68.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0C0074D2-E7F4-E711-B422-002590E39C46.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0C5F5408-5FF4-E711-A790-0CC47AA989BE.root',
'/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/94X_mc2017_realistic_v10_ext1-v1/00000/0C754A7B-DFF4-E711-93E4-001E6739677A.root'
 
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
                                       fileName = cms.string('Output_histos_genMatch_Muon.root')
                                   )

process.p = cms.Path(process.selectedPrimaryVertices*process.demo)
