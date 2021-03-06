// -*- C++ -*-
//
// Package:    Analysis/DrellYan
// Class:      DrellYan
// 
/**\class DrellYan DrellYan.cc Analysis/DrellYan/plugins/DrellYan.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Prasant Kumar Rout
//         Created:  Mon, 19 Feb 2018 13:46:25 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include "Math/VectorUtil.h"
//header file for taus
#include "DataFormats/TauReco/interface/BaseTau.h"
#include "DataFormats/TauReco/interface/BaseTauFwd.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminatorByIsolation.h"

// header file for muons
#include "DataFormats/MuonReco/interface/MuonIsolation.h"
#include "DataFormats/MuonReco/interface/MuonPFIsolation.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

// header file for PatCandidates for all
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
// header file for vertexreco and trackreco
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h"

// header file for electron & photon
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/ElectronIsolationAssociation.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/PhotonIsolationAssociation.h"
// header for Jet & MET/////////////////////////////////////
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TMath.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class DrellYan : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit DrellYan(const edm::ParameterSet&);
      ~DrellYan();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      template<class T>
       TLorentzVector getP4(const T& obj) {
       TLorentzVector P;
       P.SetPtEtaPhiE(obj.pt(),obj.eta(),obj.phi(),obj.energy());
       return P;
      }
      void selectMuon();
      void select4Mu(); 
      void selectElectron();
      
   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  const edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
  const edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  const edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  const edm::EDGetTokenT<reco::GenParticleCollection> genparticleToken_;
  const edm::EDGetTokenT<pat::IsolatedTrackCollection> isolatedtrackToken_;
  const edm::EDGetTokenT<pat::TauCollection> tauToken_;
  const edm::EDGetTokenT<pat::PhotonCollection> photonToken_;
  const edm::EDGetTokenT<pat::JetCollection> jetToken_;
  const edm::EDGetTokenT<pat::METCollection> metToken_;
  
  bool verbosity_;
  bool isMC_;
  TFileDirectory* vtxDir;
  TFileDirectory* muDir;
  TFileDirectory* eleDir;
  TFileDirectory* tauDir;
  TFileDirectory* photonDir;
  TFileDirectory* jetDir;
  TFileDirectory* metDir;
  TFileDirectory* isolatedTrackDir;
  TH1D *demoHisto_1;  TH1D *Muon_pT; TH1D *M_Probe_charge;  TH1D *Electron_charge; TH1D *E_Tag_pdgId;
  TH1D *demoHisto_2;  TH1D *Muon_Eta; TH1D *Jet_pT;         TH1D *Electron_InVMass; TH1D *E_Probe_pdgId;
  TH1D *demoHisto_3;  TH1D *Muon_Phi;  TH1D *MET_pT;        TH1D *E_Tag_charge;     TH1D *M_Tag_pdgId;
  TH1D *demoHisto_4;  TH1D *Muon_charge; TH1D *Electron_pT;  TH1D *E_Probe_charge;  TH1D *M_Probe_pdgId;
  TH1D *demoHisto_5;  TH1D *Muon_InVMass_all_probe; TH1D *Electron_Eta; TH1D *MuonpT_barrel; 
  TH1D *demoHisto_6;  TH1D *M_Tag_charge; TH1D *Electron_Phi; TH1D *MuonpT_endcap;
  TH1D *genPt_el;     TH1D *Muon_InVMass_passing_probe; TH1D *Muon_InVMass_failing_probe;
  TH1D *genEta_el;    TH1D *h4MuInvMass;
  TH1D *genPhi_el;
  TH1D *DeltaPhi_el_gen;
  std::vector<pat::Muon> selectedMu_;
  std::vector<pat::Muon> selected4Mu_;
  std::vector<pat::Electron> selectedElectron_;
  std::vector<reco::GenParticle>selectedGenElectron_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DrellYan::DrellYan(const edm::ParameterSet& iConfig):
  vertexToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexSrc"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc"))),
  electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electronSrc"))),
  genparticleToken_(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genparticleSrc"))),
  isolatedtrackToken_(consumes<pat::IsolatedTrackCollection>(iConfig.getParameter<edm::InputTag>("isolatedtrackSrc"))),
  tauToken_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("tauSrc"))),
  photonToken_(consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("photonSrc"))),
   jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("JETSrc"))),
   metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("METSrc"))),
  verbosity_(iConfig.getParameter<bool>("verbosity")),
  isMC_(iConfig.getParameter<bool>("isMC"))

{ //now do what ever initialization is needed
  usesResource("TFileService");   
  edm::Service<TFileService> outfile;
  vtxDir = new TFileDirectory(outfile->mkdir("Vertex"));
  muDir = new TFileDirectory(outfile->mkdir("Muon"));
  eleDir = new TFileDirectory(outfile->mkdir("Electron"));
  tauDir = new TFileDirectory(outfile->mkdir("Tau"));
  photonDir = new TFileDirectory(outfile->mkdir("Phton"));
  jetDir = new TFileDirectory(outfile->mkdir("Jet"));
  metDir = new TFileDirectory(outfile->mkdir("MET"));
  isolatedTrackDir = new TFileDirectory(outfile->mkdir("IsolatedTracks"));
  

  demoHisto_1 = eleDir->make<TH1D>("electrons", "Electrons", 100, 0, 20);
  demoHisto_2 = vtxDir->make<TH1D>("primaryVertices", "PrimaryVertices", 100, 0, 50);
  demoHisto_3 = muDir->make<TH1D>("muons", "Muons", 100, 0, 20);
  demoHisto_4 = isolatedTrackDir->make<TH1D>("isolatedtracks", "IsolatedTracks", 100, 0, 20);
  demoHisto_5 = tauDir->make<TH1D>("taus", "Taus", 100, 0, 20);
  demoHisto_6 = photonDir->make<TH1D>("photons", "Photons", 100, 0, 20);
  Muon_pT     = muDir->make<TH1D>("Muon_pT", "Muon pT all", 100, 0, 100);
  MuonpT_barrel  = muDir->make<TH1D>("MuonpT_barrel","Muon pT barrel",250,0.,500.);
  MuonpT_endcap  = muDir->make<TH1D>("MuonpT_endcap","Muon pT endcap",250,0.,500.);

  Muon_Eta     = muDir->make<TH1D>("MUon_Eta", "Muon Eta", 100, -3.0, 3.0);
  Muon_Phi     = muDir->make<TH1D>("Muon_Phi", "Muon phi", 100, -3.0, 3.0);
  Muon_InVMass_all_probe = muDir->make<TH1D>("Inv_Mass_Muon_all_probe", "InV mass (Z -> mumu)", 100, 70.0, 110.0);
  Muon_InVMass_passing_probe = muDir->make<TH1D>("Inv_Mass_Muon_passing_probe", "InV mass (Z -> mumu)", 100, 70.0, 110.0);
  Muon_InVMass_failing_probe = muDir->make<TH1D>("Inv_Mass_Muon_failing_probe", "InV mass (Z -> mumu)", 100, 70.0, 110.0);
  Muon_charge  = muDir->make<TH1D>("Muon_Charge", "Muon charge", 100, -2, 2);
  M_Tag_charge  = muDir->make<TH1D>("M_tagcharge", "Tag Muon charge", 100, -2, 2);
  M_Probe_charge  = muDir->make<TH1D>("M_probecharge", "Probe Muon charge", 100, -2, 2);
  M_Tag_pdgId  = muDir->make<TH1D>("Muon_Tag_pdgId", "Tag Muon pdgId", 100, -15, 15);
  M_Probe_pdgId  = muDir->make<TH1D>("Muon_Probe_pdgId", "Probe Muon pdgId", 100, -15, 15);
  h4MuInvMass = muDir->make<TH1D>("InvMass4MuSystem","Invariant mass of the 4 muons system",200,0,500);


  Electron_pT     = eleDir->make<TH1D>("Electron_pT", "Electron pT", 100, 0, 100);
  Electron_Eta     = eleDir->make<TH1D>("Electron_Eta", "Electron Eta", 100, -3.0, 3.0);
  Electron_Phi     = eleDir->make<TH1D>("Electron_Phi", "Electron phi", 100, -3.0, 3.0);
  Electron_InVMass = eleDir->make<TH1D>("Inv_Mass_Electron", "InV Mass(Z -> ee)", 100, 70.0, 110.0);
  Electron_charge  = eleDir->make<TH1D>("Electron_Charge", "Electron charge", 100, -2, 2);
  E_Tag_charge  = eleDir->make<TH1D>("e_tagcharge", "Tag Electron charge", 100, -2, 2);
  E_Probe_charge  = eleDir->make<TH1D>("e_probecharge", "Probe Electron charge", 100, -2, 2);
  E_Tag_pdgId  = eleDir->make<TH1D>("e_Tag_pdgId", "Tag Electron pdgId", 100, -15, 15);
  E_Probe_pdgId  = eleDir->make<TH1D>("e_Probe_pdgId", "Probe Electron pdgId", 100, -15, 15);
  
  Jet_pT     = jetDir->make<TH1D>("JET_pT", "jet pT", 100, 0, 1000);
  MET_pT     = metDir->make<TH1D>("MET_pT", "Met pT", 100, 0, 1000);
 
  genPt_el = eleDir->make<TH1D>("Gen_pT", "Gen pT", 20, 0, 100);
  genEta_el = eleDir->make<TH1D>("Gen_Eta", "Gen Eta", 30, -3., 3.);
  genPhi_el = eleDir->make<TH1D>("Gen_Phi", "Gen Phi", 35, -3.5, 3.5); 
  DeltaPhi_el_gen = eleDir->make<TH1D>("Gen_Phi_el", "Gen Phi matching electron", 35, -3.5,3.5 ); 


}




DrellYan::~DrellYan()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions

//

// ------------ method called for each event  ------------
void
DrellYan::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  selectedMu_.clear();
  selectedElectron_.clear();
  selected4Mu_.clear();
  //using namespace edm;
  ///////////primary vertices////////////////////////////////////////////////////////////////////////
  std::cout<< "-------------------- primary verices Information-------------------------------------------------"<< std::endl;

  edm::Handle<reco::VertexCollection> primaryVertices; 
  iEvent.getByToken(vertexToken_, primaryVertices);
  const reco::Vertex &PV = primaryVertices->front();
  demoHisto_2->Fill(primaryVertices->size());
  std::cout << "Number of Primary vertices in the event="
	    << primaryVertices->size() << std::endl; 

  std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;

 ////////////  electrons /////////////////////////////////////////////////////////////////////////////

  std::cout<< "-------------------- Electron Information-------------------------------------------------"<< std::endl;
  // get electron collection
  edm::Handle<pat::ElectronCollection> electrons;
  iEvent.getByToken(electronToken_, electrons);
  // get generator particle collection
  edm::Handle<reco::GenParticleCollection> particles;
  iEvent.getByToken(genparticleToken_, particles);

  demoHisto_1->Fill(electrons->size());

  for(const reco::GenParticle &part : *particles){
    const int pdgid = std::fabs(part.pdgId());
    if(part.status()==1 && pdgid ==11 ){
      genPt_el ->Fill( part.pt()  );
      genEta_el->Fill( part.eta() );
      genPhi_el->Fill( part.phi() );
           
    }
   
  }

 
   
  
  for(const pat::Electron &el : *electrons){
  
    Electron_charge->Fill(el.charge());
    Electron_pT->Fill(el.pt());
    Electron_Eta->Fill(el.eta());
    Electron_Phi->Fill(el.phi());
    ///////////////////////missing hits of electron////////////////////////////////////////////////////
    double missingHits = el.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
    std::cout << "missing hits of electron = " << missingHits  << std::endl;

    //////////////////electron stuffs///////////////////////////////////////////////////////////
    reco::GsfTrackRef el_Gsf = el.gsfTrack();
    double dxyWrtPV_el = -99. ;
    double dzWrtPV_el = -99. ;
    double dxy_test_el = -99.;
    double d0_el = -99.;
    if(el_Gsf.isNonnull()){

        dxyWrtPV_el = el_Gsf->dxy(PV.position());
        dxy_test_el = el_Gsf->dxy();
        dzWrtPV_el = el_Gsf->dz(PV.position());
        d0_el = el_Gsf->d0();
    // std::cout << "Dxy_el=" << dxyWrtPV_el << "\tdzWrtPV_el=" << dzWrtPV_el << std::endl;
    std::cout << "Dxy_el =" << dxyWrtPV_el << "\td0_el =" << d0_el << "\tdzWrtPV_el =" << dzWrtPV_el <<  std::endl;
    std::cout << "Dxy_test_el = " << dxy_test_el << std::endl;    // d0_el and dxy_test_el are eqaual and opposite
    }
    /////////////////////////////////////////////////////////////////////////////////
    double sietaieta             =  el.sigmaIetaIeta();
    double full5x5_sigmaIetaIeta = el.full5x5_sigmaIetaIeta();
    double eOverP                = el.eSuperClusterOverP();
    double eSeedOverPin          = el.eSeedClusterOverP();
    double fBrem                 = el.fbrem();
   
    double hcalIso   = el.dr03HcalTowerSumEt();
    double ecalIso   = el.dr03EcalRecHitSumEt();
    double trkIso    = el.dr03TkSumPt();
    double Dphi      = el.deltaPhiSuperClusterTrackAtVtx();
    double Deta      = el.deltaEtaSuperClusterTrackAtVtx();
    double HoE       = el.hadronicOverEm();
    double et        = el.et();
    double dist      = el.convDist();
    double dcot      = el.convDcot();
    bool isConv      = std::fabs(dist) < 0.02 && std::fabs(dcot) < 0.02;
    double relIso = (ecalIso + hcalIso + trkIso) / et;
    std::cout << "relative isolation of electron = " << relIso  << std::endl; 
    ///////////////////Z mass reconstruction : electron selection///////////////////////////////////////
 
    reco::SuperClusterRef ele_SC = el.superCluster();
    double eta = std::fabs(ele_SC->eta());
    double scTheta = (2*atan(exp(-ele_SC->eta())));
    double scEt = ele_SC->energy()*sin(scTheta);

    ///////////////////////////////////checking////////////////////////////////////
    if(!el.isPF()) continue;
    if(el.pt()<= 5.) continue;
 
    if ((eta > 1.479 && eta < 1.566) || eta > 2.5) continue;
    // if(missingHits > 1 && isConv) continue;
    //std::cout << "missing hits of electron = " << missingHits  << "----" << " Electron Conversion = " << isConv << std::endl;
    ///////////////////////////////////////////////////////////////////////////
    // if(!(std::fabs(Deta) < 0.01) && !(std::fabs(Dphi) < 0.8)) continue; 
    // if(!(sietaieta < 0.01) && !(relIso < 0.1)) continue; 
    selectedElectron_.push_back(el);

  }

  if(selectedElectron_.size() > 2) selectElectron();

  std::cout<< "-------------------- ---End-------------------------------------------------"<< std::endl;

 
  //std::cout << "Number of electrons in the event="<< selectedElectron_.size() << std::endl;

  ///////////////////////////////////////////////////////////////////////////////////////////////////
 
  ////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////// muons //////////////////////////////////////////////////////////////////////////

  std::cout<< "-------------------- Muon Information-------------------------------------------------"<< std::endl;

  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(muonToken_, muons);
  // filling number of muons in an event
  demoHisto_3->Fill(muons->size());
  for(const pat::Muon &mu : *muons){
    Muon_charge->Fill(mu.charge());
    // filling muon pT in barrel , andcap and all
    Muon_pT->Fill(mu.pt());
    if(std::fabs(mu.eta()) < 1.2) MuonpT_barrel->Fill(mu.pt());
    else MuonpT_endcap->Fill(mu.pt());

    // filling muon Eta and Phi
    Muon_Eta->Fill(mu.eta());
    Muon_Phi->Fill(mu.phi());
 
    //getting dxy & dz from track w.r.t a vertex
    reco::TrackRef tk = mu.muonBestTrack();
    double dxyWrtPV_mu = -99. ;
    double dzWrtPV_mu = -99. ;
    if(tk.isNonnull()){ 
         dxyWrtPV_mu = tk->dxy(PV.position());
         dzWrtPV_mu = tk->dz(PV.position());
	 std::cout << "Dxy_mu=" << dxyWrtPV_mu << "\tdzWrtPV_mu=" << dzWrtPV_mu << std::endl;
    } 
   
    // std::cout << "Dxy=" << dxyWrtPV << "\tdzWrtPV=" << dzWrtPV << std::endl;

    ///   some muon stuffs /////////////////////////////////////////////////////////////////////////////////////////////////
    double norm_chi2 = 9999999.0;
    int minTrackerLayers =0;
    int minValidMuonHits =0;
    int minPixelHits =0;
    if(mu.globalTrack().isNonnull() && mu.globalTrack().isAvailable()){
      norm_chi2 = mu.normChi2();
      minTrackerLayers = static_cast<int> (mu.track()->hitPattern().trackerLayersWithMeasurement());
      minValidMuonHits = static_cast<int> (mu.globalTrack()->hitPattern().numberOfValidMuonHits());
      minPixelHits = mu.innerTrack()->hitPattern().numberOfValidPixelHits();
      
      std::cout << "norm_chi2 = " << norm_chi2 << std::endl;
      std::cout << "minTrackerLayers = " << minTrackerLayers << std::endl;
      std::cout << "minPixelHits = " << minPixelHits << std::endl;
      std::cout << "minValidMuonHits = " << minValidMuonHits << std::endl;      
    }
    
    // std::cout << "norm_chi2 = " << norm_chi2 << std::endl;
    // std::cout << "minTrackerLayers = " << minTrackerLayers << std::endl;
    // std::cout << "minPixelHits = " << minPixelHits << std::endl;
    // std::cout << "minValidMuonHits = " << minValidMuonHits << std::endl;

    if(mu.isGlobalMuon()){

      if(mu.pt() >= 20 ) 
	selected4Mu_.push_back(mu);

    }

    
 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //gen match muon and  selecting muons pT > 5, |eta| < 2.4, dxy< 0.5, dz < 1, isGlobalMuon ///////////////////////
    if(mu.genLepton() != 0){
    double reso = (mu.pt() - mu.genLepton()->pt())/mu.genLepton()->pt();
    float deltaPhi = ROOT::Math::VectorUtil::DeltaPhi(mu.genLepton()->p4(), mu.p4());
    if(deltaPhi > 0.2) continue;
    std::cout<< "deltaph between reco & Mctruth muon =" << deltaPhi << std::endl;
    if(mu.pt() <= 5.) continue;
    if(std::fabs(mu.eta()) > 2.4) continue;
 
    if(std::fabs(dxyWrtPV_mu) >= 0.5) continue;
    if(std::fabs(dzWrtPV_mu) >= 1.) continue;

    if(!mu.isGlobalMuon() && !mu.isPFMuon() && !mu.isTrackerMuon()) continue;
    //if(!mu.isGlobalMuon()) continue;     
      selectedMu_.push_back(mu);
    }
  }
    if(selectedMu_.size() > 2) selectMuon();
    if(selected4Mu_.size() == 4) select4Mu();
         
  
    std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;

    //std::cout << "Number of Selected Muons in the event="<< selectedMu_.size() << std::endl;
  //  std::cout << "Number of Muons in the event="<< muons->size() << std::endl;
  //std::cout << "pT pf Muons in the event="<< muons->pt() << std::endl;
  //std::cout << "Eta of Muons in the event="<< muons->eta() << std::endl;
  //std::cout << "Phi of Muons in the event="<< muons->phi() << std::endl;
  //std::cout << "charge of Muons in the event="<< muons->charge() << std::endl;

  //////////////////// isolatedtracks //////////////////////////////////////////

  std::cout<< "-------------------IsolatedTrack Information-------------------------------------------------"<< std::endl;

  edm::Handle<pat::IsolatedTrackCollection> isolatedtracks;
  iEvent.getByToken(isolatedtrackToken_, isolatedtracks);
  demoHisto_4->Fill(isolatedtracks->size());

  std::cout << "Number of isolatedtracks in the event="
	    << isolatedtracks->size() << std::endl;

  std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;

  
  /////////////////////// taus ////////////////////////////////////
 

  std::cout<< "---------------------Tau Information-------------------------------------------------"<< std::endl;

  edm::Handle<pat::TauCollection> taus;
  iEvent.getByToken(tauToken_, taus);
  demoHisto_5->Fill(taus->size());

  std::cout << "Number of taus in the event="
	    << taus->size() << std::endl;

  std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;

  ////////////////// photons ////////////////////////////////////////
 
  std::cout<< "-------------------- Photon Information-------------------------------------------------"<< std::endl;

  edm::Handle<pat::PhotonCollection> photons;
  iEvent.getByToken(photonToken_, photons);
  demoHisto_6->Fill(photons->size());

  std::cout << "Number of photons in the event="
	    << photons->size() << std::endl;

  std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;

  ///////////////////////JETS////////////////////////////

  std::cout<< "-------------------- Jets Information-------------------------------------------------"<< std::endl;

  edm::Handle<pat::JetCollection> jets;
  iEvent.getByToken(jetToken_, jets);
  for (const pat::Jet &j : *jets) {
    if (j.pt() < 20) continue;
    Jet_pT->Fill(j.pt());
  }


  std::cout << "Number of jets in the event="
           << jets->size() << std::endl;

  std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;


  ////////////////MET/////////////////////////////////

  std::cout<< "-------------------- MET Information-------------------------------------------------"<< std::endl;

  edm::Handle<pat::METCollection> mets;
  iEvent.getByToken(metToken_, mets);
  const pat::MET &met = mets->front();
  MET_pT->Fill(met.pt());

  std::cout << "Number of METs in the event="
           << mets->size() << std::endl;

  std::cout<< "-------------------- End-------------------------------------------------"<< std::endl;

  //////////////////////////////////////////////////////






#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}
////////////////////// calculation of invariant mass of di muons Z -> mu+ mu- /////////////////////////////
void
DrellYan::selectMuon(){
  for(unsigned int i = 0; i < selectedMu_.size(); i++) {
    // Tag selection pt > 30 , relIso < 0.35 
     
    double Tag_Muon_relIso = (selectedMu_[i].pfIsolationR03().sumChargedHadronPt + std::max(selectedMu_[i].pfIsolationR03().sumNeutralHadronEt + selectedMu_[i].pfIsolationR03().sumPhotonEt - selectedMu_[i].pfIsolationR03().sumPUPt/2.0, 0.0))/(selectedMu_[i].pt()); 
      if(Tag_Muon_relIso >= 0.35 ) continue;
      if(selectedMu_[i].pt() <= 20.) continue;

      TLorentzVector Tag_Muon = getP4(selectedMu_[i]);
      int mu_tagcharge = selectedMu_[i].charge();
      int mu_tag_pdgId = selectedMu_[i].pdgId();

      for(unsigned int j = i+1; j < selectedMu_.size(); j++) {
	// Probe selection relIso < 0.35, pt < = 50
	double Probe_Muon_relIso = (selectedMu_[j].pfIsolationR03().sumChargedHadronPt + std::max(selectedMu_[j].pfIsolationR03().sumNeutralHadronEt + selectedMu_[j].pfIsolationR03().sumPhotonEt - selectedMu_[j].pfIsolationR03().sumPUPt/2.0, 0.0))/(selectedMu_[j].pt());
	if(Probe_Muon_relIso >= 0.35 ) continue;

	int mu_probecharge = selectedMu_[j].charge();
        int mu_probe_pdgId = selectedMu_[j].pdgId();
        if((mu_tagcharge + mu_probecharge != 0) || (mu_tag_pdgId + mu_probe_pdgId != 0)) continue;
          	
        M_Tag_pdgId->Fill(mu_tag_pdgId);
	M_Probe_pdgId->Fill(mu_probe_pdgId);
        M_Tag_charge->Fill(mu_tagcharge);
        M_Probe_charge->Fill(mu_probecharge);
        TLorentzVector Probe_Muon = getP4(selectedMu_[j]);
	TLorentzVector TnP_Muon = (Tag_Muon + Probe_Muon);
	if( TnP_Muon.M() <= 70. || TnP_Muon.M() >= 110. ) continue;
	  Muon_InVMass_all_probe->Fill(TnP_Muon.M());
	  if(selectedMu_[j].pt() <= 50){
	     Muon_InVMass_passing_probe->Fill(TnP_Muon.M());
	  }  
         else Muon_InVMass_failing_probe->Fill(TnP_Muon.M());
	 
      }     
      
  }
}


////////////////////Calculation of Invariant mass of di electrons Z -> e+ e- /////////////////////////////


void
DrellYan::selectElectron(){
  for(unsigned int k = 0; k < selectedElectron_.size(); k++) {
    //if(selectedElectron_[k].pt() <= 20.) continue;

    TLorentzVector Tag_Electron = getP4(selectedElectron_[k]);
    int el_tagcharge = selectedElectron_[k].charge();
    int el_tag_pdgId = selectedElectron_[k].pdgId();
    for(unsigned int l = 0; l < selectedElectron_.size(); l++) {

      int el_probecharge = selectedElectron_[l].charge();
      int el_probe_pdgId = selectedElectron_[l].pdgId();
      if((el_tagcharge + el_probecharge != 0) || (el_tag_pdgId + el_probe_pdgId != 0)) continue;
      E_Tag_pdgId->Fill(el_tag_pdgId);
      E_Probe_pdgId->Fill(el_probe_pdgId);
      E_Tag_charge->Fill(el_tagcharge);
      E_Probe_charge->Fill(el_probecharge);
      TLorentzVector Probe_Electron = getP4(selectedElectron_[l]);
      TLorentzVector TnP_Electron = (Tag_Electron + Probe_Electron);
      if( TnP_Electron.M() <= 70. || TnP_Electron.M() >= 110. ) continue;
      Electron_InVMass->Fill(TnP_Electron.M());

    }

  }
}


////////////////////////////////4 muon selectron //////////////////////////////////////////

void
DrellYan::select4Mu(){

  if(selected4Mu_.size() == 4){
    reco::Candidate::LorentzVector p4CM;
    for (pat::MuonCollection::const_iterator MUON = selected4Mu_.begin();  MUON != selected4Mu_.end(); ++MUON){
      p4CM = p4CM + MUON->p4();
    }
    h4MuInvMass->Fill(p4CM.mass());
  }

}













// ------------ method called once each job just before starting event loop  ------------
void 
DrellYan::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DrellYan::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DrellYan::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DrellYan);
