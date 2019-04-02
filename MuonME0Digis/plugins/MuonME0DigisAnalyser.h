#ifndef MuonTriggering_MuonME0Digis_plugins_MuonME0DigisAnalyser_h
#define MuonTriggering_MuonME0Digis_plugins_MuonME0DigisAnalyser_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Run.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GEMDigiSimLink/interface/ME0DigiSimLink.h"

#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0RecHitCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0SegmentCollection.h"
#include "DataFormats/MuonDetId/interface/ME0DetId.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSet.h"

#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "Geometry/GEMGeometry/interface/ME0EtaPartitionSpecs.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "SimDataFormats/Track/interface/SimTrackContainer.h"


class TTree;


class MuonME0DigisAnalyser : public edm::EDAnalyzer {
 public:
  explicit MuonME0DigisAnalyser(const edm::ParameterSet&);
  ~MuonME0DigisAnalyser();

 private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  void resetBranch();
  Int_t getIndex(Int_t layer_id, Int_t roll_id, Int_t strip);
  Int_t getUniqueId(Int_t region, Int_t chamber,
                    Int_t layer, Int_t roll, Int_t strip);

  // ----------member data ---------------------------
  edm::EDGetTokenT<ME0DigiCollection>                  me0_digi_token_;
  edm::EDGetTokenT<edm::DetSetVector<ME0DigiSimLink> > me0_digi_sim_link_token_;
  edm::EDGetTokenT<edm::SimTrackContainer>             sim_track_token_;

  edm::Service<TFileService> file_service_;
  TTree* tree_;

  // NOTE Branch
  Int_t   b_digi_[18432]; // [layer][ieta][strip] --> 6 * 8 * 384
  Int_t   b_muon_digi_[18432]; // actually SimTrack with abs(PID) == 6

  Float_t b_muon_pt_;
  Float_t b_muon_eta_;
  Float_t b_muon_phi_;

  Float_t b_simhit_pt_[6]; // six layers
  Float_t b_simhit_eta_[6];
  Float_t b_simhit_phi_[6];

  Int_t b_region_;
  Int_t b_chamber_;

  // NOTE Constants

  const Int_t kNumChambers_ = 18; // per region
  const Int_t kNumLayers_ = 6; // per chamber
  const Int_t kNumEtaPartitions_ = 8; // per layer
  const Int_t kNumStrips_ = 384; // per eta partition

  const Int_t kMuonPDGId_ = 13;

  const std::string kLogCategory_ = "MuonME0DigisAnalyser";
};

#endif // MuonTriggering_MuonME0Digis_plugins_MuonME0DigisAnalyser_h