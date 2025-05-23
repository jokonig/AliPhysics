/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskAO2Dconverter_H
#define AliAnalysisTaskAO2Dconverter_H

#include "AliAnalysisFilter.h"
#include "AliAODRelabelInterface.h"
#include "AliESDMuonTrack.h"
#include "AliEventCuts.h"
#include "AliTriggerAnalysis.h"
#include "AliAODInputHandler.h"
#include "AliAODConversionPhoton.h"
#include "AliAODForwardMult.h"
#include "AliConversionPhotonCuts.h"
#include <TString.h>
#include <TMap.h>

#include "TClass.h"

#include <Rtypes.h>

#include <map>

//< map detector/tower to continuous channel Id
constexpr int IdDummy = -1;
constexpr int IdVoid = -2;

constexpr int IdZNAC = 0;
constexpr int IdZNA1 = 1;
constexpr int IdZNA2 = 2;
constexpr int IdZNA3 = 3;
constexpr int IdZNA4 = 4;
constexpr int IdZNASum = 5;
//
constexpr int IdZPAC = 6;
constexpr int IdZPA1 = 7;
constexpr int IdZPA2 = 8;
constexpr int IdZPA3 = 9;
constexpr int IdZPA4 = 10;
constexpr int IdZPASum = 11;
//
constexpr int IdZEM1 = 12;
constexpr int IdZEM2 = 13;
//
constexpr int IdZNCC = 14;
constexpr int IdZNC1 = 15;
constexpr int IdZNC2 = 16;
constexpr int IdZNC3 = 17;
constexpr int IdZNC4 = 18;
constexpr int IdZNCSum = 19;
//
constexpr int IdZPCC = 20;
constexpr int IdZPC1 = 21;
constexpr int IdZPC2 = 22;
constexpr int IdZPC3 = 23;
constexpr int IdZPC4 = 24;
constexpr int IdZPCSum = 25;

class AliVEvent;
class AliESDEvent;
class AliAODEvent;
class AliGRPObject;
class TFile;
class TDirectory;
class TParticle;
class TH2I;
class AliGenEventHeader;
class V0Reader;

class AliAnalysisTaskAO2Dconverter : public AliAODRelabelInterface
{
public:
  AliAnalysisTaskAO2Dconverter() = default;
  AliAnalysisTaskAO2Dconverter(const char *name);
  virtual ~AliAnalysisTaskAO2Dconverter();

  // commented out because copy constructor of 'AliAnalysisTaskAO2Dconverter' is implicitly deleted because field 'fEventCuts' has an inaccessible copy constructor
  // AliAnalysisTaskAO2Dconverter(const AliAnalysisTaskAO2Dconverter &) = default;
  AliAnalysisTaskAO2Dconverter &operator=(const AliAnalysisTaskAO2Dconverter &) = delete;

  void SetUseEventCuts(Bool_t useEventCuts=kTRUE) { fUseEventCuts = useEventCuts;}
  Bool_t GetUseEventCuts() const {return fUseEventCuts;}

  void SetUseTriggerAnalysis(Bool_t useTriggerAnalysis=kTRUE) { fUseTriggerAnalysis = useTriggerAnalysis;}
  Bool_t GetUseTriggerAnalysis() const {return fUseTriggerAnalysis;}

  virtual void Init();
  virtual void NotifyRun();
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *option);
  virtual void FinishTaskOutput();
  virtual void Terminate(Option_t *option);

  void SetBasketSize(int events, int tracks) { fBasketSizeEvents = events; fBasketSizeTracks = tracks; }

  virtual void SetTruncation(Bool_t trunc=kTRUE) {fTruncate = trunc;}
  virtual void SetCompression(UInt_t compress=101) {fCompress = compress; }
  virtual void SetMaxBytes(ULong_t nbytes = 100000000) {fMaxBytes = nbytes;}
  void SetEMCALAmplitudeThreshold(Double_t threshold) { fEMCALAmplitudeThreshold = threshold; }
  void SetEMCALFractionL1MonitoringEvents(Double_t fraction) { fFractionL1MonitorEventsEMCAL = fraction; }
  void SetEMCALTriggerReducedPayload(Bool_t reduced) { fEMCALReducedTriggerPayload = reduced; }
  void SetUsePHOSTriggerMap(Bool_t toUse=kTRUE) { fUsePHOSBadMap = toUse; }
  void SetReadTR(Bool_t readTR = true) {fReadTR = readTR;};
  void SetSaveEventBitsInAODConversion(Bool_t saveEventBitsInAODConversion = kTRUE) {fSaveEventBitsInAODConversion = saveEventBitsInAODConversion;};
  void SetSaveHybridTracksInAODConversion(Bool_t saveHybridTracksInAODConversion = kTRUE) {fSaveHybridTracksInAODConversion = saveHybridTracksInAODConversion;};

  void SetDisableEMCAL(bool flag = true) { fDisableEMCAL = flag; }

  int8_t packInInt8(float nSigma);

  static AliAnalysisTaskAO2Dconverter* AddTask(TString suffix = "");
  enum TreeIndex { // Index of the output trees
    kEvents = 0,
    kEventsExtra,
    kTracks,
    kTracksCov,
    kTracksExtra,
    kFwdTrack,
    kFwdTrackCov,
    kCalo,
    kCaloTrigger,
    kZdc,
    kFV0A,
    kFV0C,
    kFT0,
    kFDD,
    kV0s,
    kOTFV0s,
    kCascades,
    kTOF,
    kMcParticle,
    kMcCollision,
    kMcTrackLabel,
    kMcFwdTrackLabel,
    kMcCaloLabel,
    kMcCollisionLabel,
    kBC,
    kRun2BCInfo,
    kOrigin,
    kHMPID,
    kHF2Prong,
    kHF3Prong,
    kHFCascade,
    kHFDStar,
    kHepMcCrossSections,
    kHepMcPdfInfo,
    kHepMcHeavyIon,
    kRun2TrackExtras,
    kPMD,
    kTPCpidEl,
    kTPCpidMu,
    kTPCpidPi,
    kTPCpidKa, 
    kTPCpidPr,
    kTPCpidDe,
    kTPCpidTr, 
    kTPCpidHe, 
    kTPCpidAl,
    kCentV0M,
    kCentV0A,
    kCentCL0,
    kCentCL1,
    kCentRefMult5,
    kCentRefMult8,
    kFMD,
    kTrees
  };
  enum TaskModes { // Flag for the task operation mode
    kStandard = 0,
    kMC
  };
  enum MCGeneratorID { // Generator type
    kAliGenEventHeader = 0,
    kAliGenCocktailEventHeader,
    kAliGenDPMjetEventHeader,
    kAliGenEpos3EventHeader,
    kAliGenEposEventHeader,
    kAliGenEventHeaderTunedPbPb,
    kAliGenGeVSimEventHeader,
    kAliGenHepMCEventHeader,
    kAliGenHerwigEventHeader,
    kAliGenHijingEventHeader,
    kAliGenPythiaEventHeader,
    kAliGenToyEventHeader,
    kAliGenBox,
    kGenerators
  };
  enum CollisionFlagsRun2 : uint16_t {
    Run2VertexerTracks = 0x1,
    Run2VertexerZ = 0x2,
    Run2Vertexer3D = 0x4,
    // upper 8 bits for flags
    Run2VertexerTracksWithConstraint = 0x10,
    Run2VertexerTracksOnlyFitter = 0x20,
    Run2VertexerTracksMultiVertex = 0x40
  }; // corresponds to O2/Framework/Core/include/Framework/DataTypes.h
  enum TrackTypeEnum : uint8_t {
    Track = 0,
    ITSStandalone,
    Run2Track = 254,
    Run2Tracklet = 255
  }; // corresponds to O2/Framework/Core/include/Framework/DataTypes.h
  enum TrackFlagsRun2Enum {
    ITSrefit = 0x1,
    FreeClsSPDTracklet = 0x1, // for SPD tracklets, tracklet from cluster not used in tracking
    TPCrefit = 0x2,
    GoldenChi2 = 0x4,
    TPCout = 0x8
    // NOTE Highest 4 bits reservd for PID hypothesis
  }; // corresponds to O2/Framework/Core/include/Framework/DataTypes.h
  enum MCParticleFlags : uint8_t {
    ProducedInTransport = 0x1, // Bit 0: 0 = from generator; 1 = from transport
    FromBackgroundEvent = 0x2, // Particle from background event (may have been used several times)
    PhysicalPrimary = 0x4,     // Particle is a physical primary according to ALICE definition
    FromOutOfBunchPileUpCollision = 0x8
  };
  //Aliases for multiplicity selection criteria
  enum EventSelectionCut {
      kINELgtZERO = 0,
      kPileupInMultBins,
      kConsistencySPDandTrackVertices,
      kTrackletsVsClusters,
      kNonZeroNContribs,
      kIncompleteDAQ,
      kPileUpMV,
      kTPCPileUp,
      kTimeRangeCut,
      kEMCALEDCut,
      kAliEventCutsAccepted,
      kIsPileupFromSPD,
      kIsV0PFPileup,
      kIsTPCHVdip,
      kIsTPCLaserWarmUp,
      kTRDHCO,              // Offline TRD cosmic trigger decision
      kTRDHJT,              // Offline TRD jet trigger decision
      kTRDHSE,              // Offline TRD single electron trigger decision
      kTRDHQU,              // Offline TRD quarkonium trigger decision
      kTRDHEE               // Offline TRD single-electron-in-EMCAL-acceptance trigger decision
  };
  static const TClass* Generator[kGenerators]; // Generators

  TTree* CreateTree(TreeIndex t);
  void EnableTree(TreeIndex t) { fTreeStatus[t] = kTRUE; };
  void DisableTree(TreeIndex t) { fTreeStatus[t] = kFALSE; };
  static const TString TreeName[kTrees];  //! Names of the TTree containers
  static const TString TreeTitle[kTrees]; //! Titles of the TTree containers

  void Prune(TString p) { fPruneList = p; }; // Setter of the pruning list
  void SetMCMode() { fTaskMode = kMC; };     // Setter of the MC running mode
  void SetStoreHF() { fStoreHF = kTRUE; }
  void SetCentralityMethod(const char *method) { fCentralityMethod = method; } // Settter for centrality method
  void SetSkipPileup(Bool_t flag) { fSkipPileup = flag; }
  void SetSkipTPCPileup(Bool_t flag) { fSkipTPCPileup = flag; }
  AliEventCuts& GetEventCuts() { return fEventCuts; }
  Bool_t Select(TParticle* part, Float_t rv, Float_t zv);

  Bool_t GetAODConversionGammas();
  void FindDeltaAODBranchName();
  bool AreAODsRelabeled() const override {return fRelabelAODs;}
  int IsReaderPerformingRelabeling() const override {return fPreviousV0ReaderPerformsAODRelabeling;}
  void SetDeltaAODBranchName(TString string)            {fDeltaAODBranchName = string;
                                                          fRelabelAODs = kTRUE;
                                                          AliInfo(Form("Set DeltaAOD BranchName to: %s",fDeltaAODBranchName.Data()));
                                                          AliInfo(Form("Relabeling of AODs has automatically been switched ON!"));
                                                          return;}
  Bool_t RelabelAODPhotonCandidates(AliAODConversionPhoton *PhotonCandidate);
  void SetConversionCut(const TString cut) {fConversionCut = cut; return;};
  void SetCollSystem(const Int_t val) {fCollSystem=val;return;};

  AliAnalysisFilter fTrackFilter; // Standard track filter object
private:
  Bool_t fUseEventCuts = kFALSE;         // Use or not event cuts
  Bool_t fUseTriggerAnalysis = kTRUE;    // Use or not trigger analysis
  Bool_t fSaveEventBitsInAODConversion = kFALSE;
  Bool_t fSaveHybridTracksInAODConversion = kFALSE;
  Bool_t fReadTR = false;
  Int_t fCollSystem;            // 0 - pp, 1 - PbPb, 2 pPb, 29 UPC
  AliEventCuts fEventCuts;      // Standard event cuts
  AliConversionPhotonCuts fConversionCuts;    // Pointer to the ConversionCut Selection
  TString fConversionCut; // cut string for converted data
  AliTriggerAnalysis fTriggerAnalysis; // Trigger analysis object for event selection
  AliGRPObject *fGRP = nullptr; //! Global run parameters
  AliVEvent *fVEvent = nullptr; //! input ESD or AOD event
  AliESDEvent *fESD  = nullptr; //! input ESD event
  AliAODEvent *fAOD  = nullptr; //! input AOD event
  TList *fOutputList = nullptr; //! output list
  TH2I * fPHOSBadMap[5] = {};   //! PHOS trigger bad map

  Int_t fCollisionCount = 0; //! collision count
  Int_t fBCCount = 0;        //! BC count
  Bool_t fTfInitialized = false; //!
  Int_t fTFCount = 0; //! count TF written

  TClonesArray *fInputGammas = NULL;        // TClonesArray holding input gammas
  TClonesArray *fConversionGammas = NULL;   // TClonesArray holding the reconstructed photons
  TString fDeltaAODBranchName = "GammaConv_00000003_06000008d00100001100000000_gamma";                // File where Gamma Conv AOD is located, if not in default AOD
  TString fDeltaAODFilename = "AliAODGammaConversion.root"; // set filename for delta/satellite aod
  Bool_t fRelabelAODs = kTRUE;                  // flag for relabling in case of AODs
  Int_t fConversionGammaClassDef = 0;           // ClassDef version of ConversionGammas class AliAODConversionPhoton
  Int_t fPreviousV0ReaderPerformsAODRelabeling = 0; //! 0->not set, meaning V0Reader has not yet determined if it should do AODRelabeling, 1-> V0Reader perfomrs relabeling, 2-> previous V0Reader in list perfomrs relabeling

  // Output TF and TTrees
  TTree* fTree[kTrees] = { nullptr }; //! Array with all the output trees
  void Prune();                       // Function to perform tree pruning
  void FillTree(TreeIndex t);         // Function to fill the trees (only the active ones)
  void WriteTree(TreeIndex t);        // Function to write the trees (only the active ones)
  void InitTF(ULong64_t tfId);           // Initialize output subdir and trees for TF tfId
  void FillEventInTF();
  void FinishTF();

  // Task configuration variables
  TString fPruneList = "";                // Names of the branches that will not be saved to output file
  Bool_t fTreeStatus[kTrees] = { kTRUE }; // Status of the trees i.e. kTRUE (enabled) or kFALSE (disabled)
  int fBasketSizeEvents = 1000000;   // Maximum basket size of the trees for events
  int fBasketSizeTracks = 10000000;   // Maximum basket size of the trees for tracks

  TaskModes fTaskMode = kStandard; // Running mode of the task. Useful to set for e.g. MC mode

  // Data structures

  struct {
    // Event data
    Int_t fIndexBCs = 0u;       /// Index to BC table
    // Primary vertex position
    Float_t  fPosX = -999.f;       /// Primary vertex x coordinate
    Float_t  fPosY = -999.f;       /// Primary vertex y coordinate
    Float_t  fPosZ = -999.f;       /// Primary vertex z coordinate
    // Primary vertex covariance matrix
    Float_t  fCovXX = 999.f;    /// cov[0]
    Float_t  fCovXY = 0.f;      /// cov[1]
    Float_t  fCovXZ = 0.f;      /// cov[2]
    Float_t  fCovYY = 999.f;    /// cov[3]
    Float_t  fCovYZ = 0.f;      /// cov[4]
    Float_t  fCovZZ = 999.f;    /// cov[5]
    // Quality parameters
    UShort_t  fFlags = 0;       /// Vertex type
    Float_t  fChi2 = 999.f;     /// Chi2 of the vertex
    UShort_t fN = 0u;           /// Number of contributors

    // The calculation of event time certainly will be modified in Run3
    // The prototype below can be switched on request
    Float_t fCollisionTime = -999.f;    /// Event time (t0) obtained with different methods (best, T0, T0-TOF, ...)
    Float_t fCollisionTimeRes = -999.f; /// Resolution on the event time (t0) obtained with different methods (best, T0, T0-TOF, ...)

    Float_t fCentV0M = 200.f;
    Float_t fCentV0A = 200.f;
    Float_t fCentCL0 = 200.f;
    Float_t fCentCL1 = 200.f;
    Float_t fCentRefMult05 = 200.f;
    Float_t fCentRefMult08 = 200.f;
  } collision; //! structure to keep the primary vertex (avoid name conflicts)

  struct {
    // Start indices and numbers of elements for data in the other trees matching this vertex.
    // Needed for random access of collision-related data, allowing skipping data discarded by the user
    Int_t     fStart[kTrees]    = {0}; /// Start entry indices for data in the other trees matching this vertex
    Int_t     fNentries[kTrees] = {0}; /// Numbers of entries for data in the other trees matching this vertex
  } eventextra; //! structure for benchmarking information

  struct {
    int fRunNumber = -1;         /// Run number
    ULong64_t fGlobalBC = 0u;    /// Unique bunch crossing id. Contains period, orbit and bunch crossing numbers
    ULong64_t fTriggerMask = 0u; /// Trigger class mask
    ULong64_t fInputMask = 0u;   /// Input mask (unused, stored compressed to avoid converter)
  } bc; //! structure to keep trigger-related info

  struct {
    UInt_t fEventCuts = 0;             /// Event selections from AliMultSelection and AliEventCuts
    ULong64_t fTriggerMaskNext50 = 0u; /// Upper 50 trigger class
    UInt_t fL0TriggerInputMask = 0u;   /// L0 trigger input mask
    UShort_t fSPDClustersL0 = 0u;      /// number of clusters in SPD L0
    UShort_t fSPDClustersL1 = 0u;      /// number of clusters in SPD L1
    UShort_t fSPDFiredChipsL0 = 0u;    /// number of fired chips in SPD L0 (offline)
    UShort_t fSPDFiredChipsL1 = 0u;    /// number of fired chips in SPD L1 (offline)
    UShort_t fSPDFiredFastOrL0 = 0u;   /// number of fired FO chips in SPD L0 (online)
    UShort_t fSPDFiredFastOrL1 = 0u;   /// number of fired FO chips in SPD L1 (online)
    UShort_t fV0TriggerChargeA = 0u;   /// V0A trigger charge
    UShort_t fV0TriggerChargeC = 0u;   /// V0C trigger charge
    UInt_t fNTPCClusters = 0u;         /// total number of tpc clusters
    UInt_t fNSDDSSDClusters = 0u;      /// total number of SDD+SSD clusters
  } run2bcinfo; //! structure to keep run 2 only related info

  struct {
    ULong64_t fDataframeID = 0; /// ID of this data frame (important for merging DFs)
  } origin;    //! structure for origin table

  struct {
    // Track data

    Int_t   fIndexCollisions = -1;    /// The index of the collision vertex in the TF, to which the track is attached

    uint8_t fTrackType = 0;       // Type of track: global, ITS standalone, tracklet, ...

    // In case we need connection to TOF clusters, activate next lines
    // Int_t   fTOFclsIndex;     /// The index of the associated TOF cluster
    // Int_t   fNTOFcls;         /// The number of TOF clusters



    // Coordinate system parameters
    Float_t fX = -999.f;     /// X coordinate for the point of parametrisation
    Float_t fAlpha = -999.f; /// Local <--> global coor.system rotation angle

    // Track parameters
    Float_t fY = -999.f;          /// fP[0] local Y-coordinate of a track (cm)
    Float_t fZ = -999.f;          /// fP[1] local Z-coordinate of a track (cm)
    Float_t fSnp = -999.f;        /// fP[2] local sine of the track momentum azimuthal angle
    Float_t fTgl = -999.f;        /// fP[3] tangent of the track momentum dip angle
    Float_t fSigned1Pt = -999.f;  /// fP[4] 1/pt (1/(GeV/c))

    // "Covariance matrix"
    // The diagonal elements represent the errors = Sqrt(C[i,i])
    // The off-diagonal elements are the correlations = C[i,j]/Sqrt(C[i,i])/Sqrt(C[j,j])
    // The off-diagonal elements are multiplied by 128 (7bits) and packed in Char_t
    Float_t fSigmaY      = -999.f; /// Sqrt(fC[0])
    Float_t fSigmaZ      = -999.f; /// Sqrt(fC[2])
    Float_t fSigmaSnp    = -999.f; /// Sqrt(fC[5])
    Float_t fSigmaTgl    = -999.f; /// Sqrt(fC[9])
    Float_t fSigma1Pt    = -999.f; /// Sqrt(fC[14])
    Char_t fRhoZY        = 0;      /// 128*fC[1]/SigmaZ/SigmaY
    Char_t fRhoSnpY      = 0;      /// 128*fC[3]/SigmaSnp/SigmaY
    Char_t fRhoSnpZ      = 0;      /// 128*fC[4]/SigmaSnp/SigmaZ
    Char_t fRhoTglY      = 0;      /// 128*fC[6]/SigmaTgl/SigmaY
    Char_t fRhoTglZ      = 0;      /// 128*fC[7]/SigmaTgl/SigmaZ
    Char_t fRhoTglSnp    = 0;      /// 128*fC[8]/SigmaTgl/SigmaSnp
    Char_t fRho1PtY      = 0;      /// 128*fC[10]/Sigma1Pt/SigmaY
    Char_t fRho1PtZ      = 0;      /// 128*fC[11]/Sigma1Pt/SigmaZ
    Char_t fRho1PtSnp    = 0;      /// 128*fC[12]/Sigma1Pt/SigmaSnp
    Char_t fRho1PtTgl    = 0;      /// 128*fC[13]/Sigma1Pt/SigmaTgl

    // Additional track parameters
    Float_t fTPCinnerP = -999.f; /// Full momentum at the inner wall of TPC for dE/dx PID

    // Track quality parameters
    UInt_t fFlags = 0u;       /// Reconstruction status flags

    // Clusters and tracklets
    UInt_t fITSClusterSizes = 0u;                /// ITS clusters sizes, four bits per a layer, starting from the innermost
    UChar_t fTPCNClsFindable = 0u;               /// number of clusters that could be assigned in the TPC
    Char_t fTPCNClsFindableMinusFound = 0;       /// difference between findable and found clusters
    Char_t fTPCNClsFindableMinusPID = 0;         /// difference between findable and PID clusters
    Char_t fTPCNClsFindableMinusCrossedRows = 0; ///  difference between findable clusters and crossed rows
    UChar_t fTPCNClsShared = 0u;                 /// Number of shared TPC clusters
    UChar_t fITSSharedClusterMap = 0u;           /// shared ITS cluster map
    UChar_t fTRDPattern = 0u;                    /// Bit 0-5 if tracklet from TRD layer used for this track

    // Chi2
    Float_t fITSChi2NCl = -999.f; /// chi2/Ncl ITS
    Float_t fTPCChi2NCl = -999.f; /// chi2/Ncl TPC
    Float_t fTRDChi2 = -999.f;    /// chi2 TRD match (?)
    Float_t fTOFChi2 = -999.f;    /// chi2 TOF match (?)

    // PID
    Float_t fITSSignal = -999.f; /// dE/dX ITS
    Float_t fTPCSignal = -999.f; /// dE/dX TPC
    Float_t fTRDSignal = -999.f; /// dE/dX TRD
    // Float_t fTOFSignal = -999.f; /// TOFsignal
    Float_t fLength = -999.f;    /// Int.Lenght @ TOF
    Float_t fTOFExpMom = -999.f; /// TOF Expected momentum based on the expected time of pions

    // Track extrapolation to EMCAL surface
    Float_t fTrackEtaEMCAL = -999.f; /// Track eta at the EMCAL surface
    Float_t fTrackPhiEMCAL = -999.f; /// Track phi at the EMCAL surface

    // Time information about the track
    Float_t fTrackTime = -999.f;    /// Track time
    Float_t fTrackTimeRes = -999.f; /// Track time reso

    // packed information of TPC dEdx (tiny version) for cross-checks
    int8_t fTPCNSigmaStoreEl;
    int8_t fTPCNSigmaStoreMu;
    int8_t fTPCNSigmaStorePi;
    int8_t fTPCNSigmaStoreKa;
    int8_t fTPCNSigmaStorePr;
    int8_t fTPCNSigmaStoreDe;
    int8_t fTPCNSigmaStoreTr;
    int8_t fTPCNSigmaStoreHe;
    int8_t fTPCNSigmaStoreAl;
  } tracks;                      //! structure to keep track information

  struct {
    // HMPID data

    Int_t fIndexTracks = -1; /// Track ID

    Float_t fHMPIDSignal = -999.f;  /// HMPID signal
    Float_t fHMPIDXTrack = -999.f;  /// Extrapolated track point x coordinate
    Float_t fHMPIDYTrack = -999.f;  /// Extrapolated track point y coordinate
    Float_t fHMPIDXMip = -999.f;     /// Matched MIP track point x coordinate
    Float_t fHMPIDYMip = -999.f;     /// Matched MIP track point y coordinate
    Short_t fHMPIDNPhotons = -999;  /// Number of detected photons in HMPID
    Short_t fHMPIDQMip = -999;      /// Matched MIP cluster charge
    Short_t fHMPIDClusSize = -999;  /// Matched MIP cluster size
    Float_t fHMPIDMom = -999.f;     /// Track momentum at the HMPID
    Float_t fHMPIDPhotsCharge[10] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};  /// Photon cluster charge
  } hmpids; //! structure to keep HMPID info

  //---------------------------------------------------------------------------
  /// MC information
  struct {
    /// MC collision

    Int_t fIndexBCs = 0u;       ///< Index to BC table
    Short_t fGeneratorsID = 0u; ///< Bitmask of generator IDs used for the MC
    Float_t fPosX = -999.f;  ///< Primary vertex x coordinate from MC
    Float_t fPosY = -999.f;  ///< Primary vertex y coordinate from MC
    Float_t fPosZ = -999.f;  ///< Primary vertex z coordinate from MC
    Float_t fT = -999.f;  ///< Time of the collision from MC
    Float_t fWeight = -999.f;  ///< Weight from MC

    /// Generation details (included in HepMC, to be removed)
    Float_t fImpactParameter = -999.f; ///< Impact parameter from MC
  } mccollision;  ///<! MC collisions = vertices

  /// MC labels
  struct {
    /// Track label to find the corresponding MC particle
    Int_t fIndexMcParticles = 0;       ///< Track label
    UShort_t fMcMask = 0;  ///< Bit mask to indicate detector mismatches (bit ON means mismatch)
                           ///< Bit 0-6: mismatch at ITS layer
                           ///< Bit 7-9: # of TPC mismatches in the ranges 0, 1, 2-3, 4-7, 8-15, 16-31, 32-63, >64
                           ///< Bit 10: TRD, bit 11: TOF, bit 15: negative label sign
  } mctracklabel; ///<! Track labels

    struct {
    /// Fwd Track label to find the corresponding MC particle
    Int_t fIndexMcParticles = 0;       ///< Track label
    UShort_t fMcMask = 0;
  } mcfwdtracklabel; ///<! Track labels

  struct {
    /// Calo cluster label to find the corresponding MC particle
    Int_t fIndexMcParticles_size = 0;         /// Calo label size
    Int_t fIndexMcParticles[1] = {-999};      ///< Calo label
    Int_t fAmplitudeFraction_size = 0;        /// Amplitude fraction size
    Float_t fAmplitudeFraction[1] = {1.f};    ///< Amplitude fraction of deposited energy of the mc particle and the total cell
  } mccalolabel; ///<! Calo labels

  struct {
    /// MC collision label
    Int_t fIndexMcCollisions = 0;       ///< Collision label
    UShort_t fMcMask = 0;    ///< Bit mask to indicate collision mismatches (bit ON means mismatch)
                             ///< bit 15: negative label sign
  } mccollisionlabel; ///<! Collision labels

  struct {
    /// MC particle

    Int_t   fIndexMcCollisions = -1;    /// The index of the MC collision

    /// MC information (modified version of TParticle)
    Int_t fPdgCode    = -99999; ///< PDG code of the particle
    Int_t fStatusCode = -99999; ///< generation status code
    uint8_t fFlags    = 0;      ///< See enum MCParticleFlags
    Int_t fIndexArray_Mothers_size     = 0;   ///< Length of fIndexArray_Mothers
    Int_t fIndexArray_Mothers[1]       = {0}; ///< VLA of mothers (length 1 or 0 for Run 2)
    Int_t fIndexSlice_Daughters[2]     = {0}; ///< Slice of daughter particles
    Float_t fWeight   = 1;      ///< particle weight from the generator or ML

    Float_t fPx = -999.f; ///< X component of momentum
    Float_t fPy = -999.f; ///< Y component of momentum
    Float_t fPz = -999.f; ///< Z component of momentum
    Float_t fE  = -999.f; ///< Energy (covers the case of resonances, no need for calculated mass)

    Float_t fVx = -999.f; ///< X of production vertex
    Float_t fVy = -999.f; ///< Y of production vertex
    Float_t fVz = -999.f; ///< Z of production vertex
    Float_t fVt = -999.f; ///< T of production vertex
    /// We do not use the polarisation so far
  } mcparticle;  ///<! MC particles from the kinematics tree

  /// HepMC information
  /// Replacing double by float in the corresponding data members

  struct CrossSections {
    ///  Information about cross-section

    Int_t  fIndexMcCollisions = -1;    /// The index of the MC collision
    Short_t fGeneratorsID = 0u; ///< Generator ID used for this set of parameters

    ULong64_t fAccepted = 0;    ///< The number of events generated so far.
    ULong64_t fAttempted = 0;   ///< The number of events attempted so far.
    Float_t fXsectGen = -999.f;  ///< Cross section in pb
    Float_t fXsectErr = -999.f;  ///< Error associated with this cross section
    Float_t fPtHard = -999.f;    ///< PT-hard (event scale, for pp collisions)
    void Print();
    void Reset();
    void Fill(AliGenEventHeader * genHeader, AliAnalysisTaskAO2Dconverter * task);
  } hepMcCrossSections; ///<! Cross-sections from the generator + Pythia specific PT-hard

  struct PdfInfo {
    /// Additional PDF information for an event

    Int_t   fIndexMcCollisions = -1;    ///< The index of the MC collision
    Short_t fGeneratorsID = 0u; ///< Generator ID used for this set of parameters

    Int_t   fId1 = 0;        ///< flavour code of first parton
    Int_t   fId2 = 0;        ///< flavour code of second parton
    Int_t   fPdfId1 = 0;     ///< LHAPDF set id of first parton
    Int_t   fPdfId2 = 0;     ///< LHAPDF set id of second parton
    Float_t fX1 = 0.f;       ///< fraction of beam momentum carried by first parton ("beam side")
    Float_t fX2 = 0.f;       ///< fraction of beam momentum carried by second parton ("target side")
    Float_t fScalePdf = 0.f; ///< Q-scale used in evaluation of PDF's   (in GeV)
    Float_t fPdf1 = 0.f;     ///< PDF (id1, x1, Q) = x*f(x)
    Float_t fPdf2 = 0.f;     ///< PDF (id2, x2, Q) = x*f(x)
    void Print();
    void Reset();
    void Fill(AliGenEventHeader * genHeader, AliAnalysisTaskAO2Dconverter * task);
  } hepMcPdfInfo; ///<! PDF information (PH: is it really used?)

  struct HeavyIon {
    ///  HepMC information for Heavy Ion generators

    Int_t fIndexMcCollisions = -1; ///< The index of the MC collision
    Short_t fGeneratorsID = 0u; ///< Generator ID used for this set of parameters

    Int_t fNcollHard = -999;              ///< Number of hard scatterings
    Int_t fNpartProj = -999;              ///< Number of projectile participants
    Int_t fNpartTarg = -999;              ///< Number of target participants
    Int_t fNcoll = -999;                  ///< Number of NN (nucleon-nucleon) collisions
    Int_t fNNwoundedCollisions = -999;    ///< Number of N-Nwounded collisions
    Int_t fNwoundedNCollisions = -999;    ///< Number of Nwounded-N collisons
    Int_t fNwoundedNwoundedCollisions = -999; ///< Number of Nwounded-Nwounded collisions
    Int_t fSpectatorNeutrons = -999;          ///< Number of spectator neutrons
    Int_t fSpectatorProtons = -999;           ///< Number of spectator protons
    Float_t fImpactParameter = -999.f;    ///< Impact Parameter(fm) of collision
    Float_t fEventPlaneAngle = 0.f;       ///< Azimuthal angle of event plane
    Float_t fEccentricity = 0.f;          ///< eccentricity of participating nucleons in the transverse plane
                                          ///< (as in phobos nucl-ex/0510031)
    Float_t fSigmaInelNN = -999.f;        ///< nucleon-nucleon inelastic (including diffractive) cross-section
    Float_t fCentrality = -999.f;         ///< centrality (prcentile of geometric cross section)
    void Print();
    void Reset();
    void Fill(AliGenEventHeader * genHeader, AliAnalysisTaskAO2Dconverter * task);
  } hepMcHeavyIon; ///<! HI-specific information in HepMC

  static MCGeneratorID GetMCGeneratorID(AliGenEventHeader * genHeader);
  //---------------------------------------------------------------------------
  // To test the compilation uncoment the line below
  // #define USE_TOF_CLUST 1
#ifdef USE_TOF_CLUST
  struct {
    // TOF clusters
    // PH: Do we store the TOF information per track?
    Int_t fTOFChannel = -1;        /// Index of the matched channel
    Short_t fTOFncls = -1;         /// Number of matchable clusters of the track
    Float_t fDx = -999.f;          /// Residual along x
    Float_t fDz = -999.f;          /// Residual along z
    Float_t fToT = -999.f;         /// ToT
    Float_t fLengthRatio = -999.f; /// Ratio of the integrated track length @ TOF to the cluster with respect to the matched cluster
  } tofClusters;                   //! structure to keep TOF clusters
#endif

  struct {
    // Calorimeter data (EMCAL & PHOS)

    Int_t fIndexBCs = 0u;       /// Index to BC table

    Short_t fCellNumber = -1;     /// Cell absolute Id. number
    Float_t fAmplitude = -999.f;  /// Cell amplitude (= energy!)
    Float_t fTime = -999.f;       /// Cell time
    Char_t fCellType = -1;        /// EMCAL: Low Gain: 0 / High Gain: 1 / TRU: 2 / LEDmon 3 (see DataFromatsEMCAL/Constants.h)
    Char_t fCaloType = -1;        /// Cell type (-1 is undefined, 0 is PHOS, 1 is EMCAL)
  } calo;                         //! structure to keep EMCAL info

  struct {
    // Calorimeter trigger data (EMCAL & PHOS)
    Int_t fIndexBCs = 0u;         /// Index to BC table
    Short_t fFastOrAbsID = - 1;   /// FastOR absolute ID
    Short_t fLnAmplitude = -1;    /// L0 amplitude (ADC) := Peak Amplitude
    Int_t fTriggerBits = 0;       /// Online trigger bits
    Char_t fCaloType = -1;        /// Calorimeter type (-1 is undefined, 0 is PHOS, 1 is EMCAL)
  } calotrigger;                  //! structure to keep calo trigger info

  struct FwdTrackPars {          /// Forward track parameters
    Int_t fIndexCollisions = -1; /// The index of the collision vertex in the TF, to which the track is attached
    Int_t fTrackType = 3;        /// MuonStandaloneTrack on ForwardTrackTypeEnum (O2 Framework/DataTypes.h)
    Float_t fX = -999.f;
    Float_t fY = -999.f;
    Float_t fZ = -999.f;
    Float_t fPhi = -999.f;
    Float_t fTgl = -999.f;
    Float_t fSigned1Pt = -999.f;
    Int_t fNClusters = -1;
    Float_t fPDca = -999.f;
    Float_t fRAtAbsorberEnd = -999.f;
    Float_t fChi2 = -999.f;
    Float_t fChi2MatchMCHMID = -999.f;
    Float_t fChi2MatchMCHMFT = -999.f;
    Float_t fMatchScoreMCHMFT = -999.f;
    // Time information about the track
    Float_t fTrackTime = -999.f;    /// Track time
    Float_t fTrackTimeRes = -999.f; /// Track time reso
    Int_t fIndexMFTTracks = -1;
    Int_t fIndexFwdTracks_MatchMCHTrack = -1;
    UShort_t fMCHBitMap = 0u;
    // MID bit map
    // | non-bending plane (4bit) | bending plane (4bit) |
    // i-th chamber can be tested with: fMIDBitMap & (1<<i)
    UShort_t fMIDBitMap = 0u;
    UInt_t fMIDBoards = 0;


    // "Covariance matrix"
    // The diagonal elements represent the errors = Sqrt(C[i,i])
    // The off-diagonal elements are the correlations = C[i,j]/Sqrt(C[i,i])/Sqrt(C[j,j])
    // The off-diagonal elements are multiplied by 128 (7bits) and packed in Char_t
    Float_t fSigmaX      = -999.f; /// Sqrt(fC[0,0])
    Float_t fSigmaY      = -999.f; /// Sqrt(fC[1,1])
    Float_t fSigmaPhi    = -999.f; /// Sqrt(fC[2,2])
    Float_t fSigmaTgl    = -999.f; /// Sqrt(fC[3,3])
    Float_t fSigma1Pt    = -999.f; /// Sqrt(fC[4,4])
    Char_t fRhoXY        = 0;      /// 128*fC[0,1]/SigmaX/SigmaY
    Char_t fRhoPhiX      = 0;      /// 128*fC[0,2]/SigmaPhi/SigmaX
    Char_t fRhoPhiY      = 0;      /// 128*fC[1,2]/SigmaPhi/SigmaY
    Char_t fRhoTglX      = 0;      /// 128*fC[0,3]/SigmaTgl/SigmaX
    Char_t fRhoTglY      = 0;      /// 128*fC[1,3]/SigmaTgl/SigmaY
    Char_t fRhoTglPhi    = 0;      /// 128*fC[2,3]/SigmaTgl/SigmaPhi
    Char_t fRho1PtX      = 0;      /// 128*fC[0,4]/Sigma1Pt/SigmaX
    Char_t fRho1PtY      = 0;      /// 128*fC[1,4]/Sigma1Pt/SigmaY
    Char_t fRho1PtPhi    = 0;      /// 128*fC[2,4]/Sigma1Pt/SigmaPhi
    Char_t fRho1PtTgl    = 0;      /// 128*fC[3,4]/Sigma1Pt/SigmaTgl

  } fwdtracks; //! structure to keep forward tracks parameters and covariances

  struct {
    Int_t fIndexBCs = 0u;             /// Index to BC table
    Int_t fEnergy_size = 0;           /// Size of fEnergy
    Float_t fEnergy[26] = {0.f};      ///< Energy of non-zero channels. The channel IDs are given in ChannelE (at the same index)
    Int_t fChannelE_size = 0;         /// Size of fChannelE
    uint8_t fChannelE[26] = {0u};     ///< Channel IDs which have reconstructed energy. There are at maximum 26 channels
    Int_t fAmplitude_size = 0;        /// Size of fAmplitude
    Float_t fAmplitude[26] = {0.f};   ///< Amplitudes of non-zero channels. The channel IDs are given in ChannelT (at the same index)
    Int_t fTime_size = 0;             /// Size of fTime
    Float_t fTime[26] = {0.f};        ///< Times of non-zero channels. The channel IDs are given in ChannelT (at the same index)
    Int_t fChannelT_size = 0;         /// Size of fChannelT
    uint8_t fChannelT[26] = {0u};     ///< Channel IDs which had non-zero amplitudes. There are at maximum 26 channels
  } zdc;                              //! structure to keep ZDC information

  struct {
    /// V0A  (32 cells in Run2, 48 cells in Run3)
    Int_t fIndexBCs = 0u;             /// Index to BC table
    Int_t fChannel_size = 0;          /// Size of fChannel and fAmplitude
    uint8_t fChannel[48] = {0};       /// Channel indices of filled amplitudes
    Int_t fAmplitude_size = 0;        /// Size of fChannel and fAmplitude
    Float_t fAmplitude[48] = {0.f};   /// Multiplicity for each filled channel listed in fChannel
    Float_t fTime = 0.f;              /// Average A-side time
    uint8_t fTriggerMask = 0;         /// Trigger info
  } fv0a;                             //! structure to keep V0A information

  struct {
    /// V0C  (32 cells in Run2)
    Int_t fIndexBCs = 0u;             /// Index to BC table
    Int_t fChannel_size = 0;          /// Size of fChannel and fAmplitude
    uint8_t fChannel[32] = {0};       /// Channel indices of filled amplitudes
    Int_t fAmplitude_size = 0;        /// Size of fChannel and fAmplitude
    Float_t fAmplitude[32] = {0.f};   /// Multiplicity for each channel
    Float_t fTime = 0.f;              /// Average C-side time
  } fv0c;                             //! structure to keep V0C information

  struct {
    /// FT0 (12+12 channels in Run2, 96+112 channels in Run3)
    Int_t fIndexBCs = 0u;             /// Index to BC table
    Int_t fChannelA_size = 0;         /// Size of fChannelA and fAmplitudeA
    uint8_t fChannelA[96] = {0};      /// Channel indices of filled amplitudes on the A-side
    Int_t fAmplitudeA_size = 0;       /// Size of fChannelA and fAmplitudeA
    Float_t fAmplitudeA[96] = {0.f};  /// Multiplicity for A-side channels listed in fChannelA
    Int_t fChannelC_size = 0;         /// Size of fChannelC and fAmplitudeC
    uint8_t fChannelC[112] = {0};     /// Channel indices of filled amplitudes on the C-side
    Int_t fAmplitudeC_size = 0;       /// Size of fChannelC and fAmplitudeC
    Float_t fAmplitudeC[112] = {0.f}; /// Multiplicity for C-side channels listed in fChannelC
    Float_t fTimeA = 0.f;             /// Average A-side time
    Float_t fTimeC = 0.f;             /// Average C-side time
    uint8_t fTriggerMask = 0;         /// Trigger info
  } ft0;                              //! structure to keep FT0 information

  struct {
    /// FDD (AD)
    Int_t fIndexBCs = 0u;                /// Index to BC table
    int16_t fChargeA[8] = {0u};   /// Multiplicity for each A-side channel
    int16_t fChargeC[8] = {0u};   /// Multiplicity for each C-side channel
    Float_t fTimeA = 0.f;             /// Average A-side time
    Float_t fTimeC = 0.f;             /// Average C-side time
    uint8_t fTriggerMask = 0;         /// Trigger info
  } fdd;                              //! structure to keep FDD (AD) information

  struct {
    /// V0s (Ks, Lambda)
    Int_t fIndexCollisions = -1; /// The index of the collision vertex in the TF, to which the track is attached
    Int_t fIndexTracksPos = -1; // Positive track ID
    Int_t fIndexTracksNeg = -1; // Negative track ID
    uint8_t fV0Type = 0; //custom bitmap for selection (standard or photon)
  } v0s;               //! structure to keep v0sinformation

  struct {
    /// v0sOTF (Photons)
    Int_t fIndexCollisions = -1; /// The index of the collision vertex in the TF, to which the track is attached
    Int_t fIndexTracksPos = -1;   // Positive track ID
    Int_t fIndexTracksNeg = -1;   // Negative track ID
    Float_t fPx             = 0.f;  // momentum in x
    Float_t fPy             = 0.f;  // momentum in y
    Float_t fPz             = 0.f;  // momentum in z
    Float_t fEnergy         = 0.f;  // energy
    Float_t fQt             = 0.f;  // Qt for Armenteros
    Float_t fAlpha          = 0.f;  // alpha for Armenteros
    Float_t fX              = 0.f;  // conversion point in x
    Float_t fY              = 0.f;  // conversion point in y
    Float_t fZ              = 0.f;  // conversion point in z
    Float_t fChi2NDF        = 0.f;  // Chi2 over NDF
    Float_t fPsiPair        = 0.f;  // psi pair
    Float_t fDCAr           = 0.f;  // DCA to prim vertex in r
    Float_t fDCAz           = 0.f;  // DCA to prim vertex in z
    Float_t fMass           = 0.f;  // mass of conversion photon
  } otfv0s;               //! structure to keep v0sinformation

  struct {
    /// Cascades
    Int_t fIndexCollisions = -1; /// The index of the collision vertex in the TF, to which the track is attached
    Int_t fIndexV0s = -1; // V0 ID
    Int_t fIndexTracks = -1; // Bachelor track ID
  } cascs;             //! structure to keep cascades information

  struct {
    // HF 2 Prong
    Int_t fIndexTracks_0 = -1; /// Track index
    Int_t fIndexTracks_1 = -1; /// Track index
    uint8_t fHFflag = 0;       /// Selection flag
  } hf2Prong;                  //! structure for HF 2 prongs

  struct {
    // HF 3 Prong
    Int_t fIndexTracks_0 = -1; /// Track index
    Int_t fIndexTracks_1 = -1; /// Track index
    Int_t fIndexTracks_2 = -1; /// Track index
    uint8_t fHFflag = 0;       /// Selection flag
  } hf3Prong;                  //! structure for HF 3 prongs

  struct {
    // HF Lc->V0+bach / cascades
    Int_t fIndexV0s = -1;      /// V0 index
    Int_t fIndexTracks_0 = -1; /// Bachelor track index
  } hfCascades;                //! structure for HF Lc->V0+bach / cascades

  struct {
    // D* -> D0pi candidates
    Int_t fIndexHf2Prongs = -1; /// D0 index
    Int_t fIndexTracks_0 = -1;  /// Track index of soft pion
  } hfDStar;                  //! structure for HF Dstar

  struct {
    // pmd information
    Int_t fIndexBCs = 0u;         /// Index to BC table
    Float_t fX = 0.0f;            /// Cluster X position
    Float_t fY = 0.0f;            /// Cluster Y position
    Float_t fZ = 0.0f;            /// Cluster Z position
    Float_t fCluADC = 0.0f;       /// Cluster Energy in ADC
    Float_t fCluPID = 0.0f;       ///[0.,1.,8] Cluster probability, 1: Photon, 0: Hadron
    uint8_t fDet = 0;             /// Detector, 0:PRE, 1:CPV
    uint8_t fNcell = 0;           /// Cluster cells
    Int_t fSmn = 0;               /// Serial module number
    Int_t fTrackNo = -1;          /// Track number assigned to the clus from simulation
    Int_t fTrackPid = 0;          /// Track pid assigned to the clus from simulation
    Float_t fSigX = 0.0f; /// Cluster x-width
    Float_t fSigY = 0.0f; /// Cluster y-width
    Int_t fClMatching = 0; ///Cluster of PRE matching with CPV
  } pmdInfo;                    //! structure to hold PMD information

  constexpr static unsigned short kFMDNeta  = 200;
  constexpr static unsigned short kFMDNphi  = 20;
  constexpr static unsigned short kFMDNbins = kFMDNeta * kFMDNphi;
  struct {
    Int_t fIndexBCs = 0u;             /// Index to BC table
    Float_t fMultiplicity[kFMDNbins]; /// Multiplicity estimate per (eta,phi)
    Float_t fIPz;                     /// Z-coordinate of IP used
    Float_t fCentrality;              /// Centrality used
    UShort_t fNClusters;              /// # SPD clusters
    UInt_t   fFlags;                  /// Event flags
    UChar_t  fConditions;             /// Processing conditions
    Bool_t   fEtaAcceptance[kFMDNeta];/// In eta acceptance
    Float_t  fPhiAcceptance[kFMDNeta];/// phi acceptance
    UChar_t  fSystem;                 /// Collision system
    Float_t  fSNN;                    /// Centre-of-mass energy
  } fmdInfo;

  /// Offsets to convert the IDs within one collision to global IDs
  Int_t fOffsetMuTrackID = 0; ///! Offset of MUON track  (used in the clusters)
  Int_t fOffsetTrack = 0;   ///! Offset of track (used in V0s)
  Int_t fOffsetV0 = 0;      ///! Offset of V0s (used in cascades)
  Int_t fOffsetLabel = 0;     ///! Offset of MC paritcles (used in cascades)
  Int_t fOffsetHF2Prong = 0;      ///! Offset of V0s (used in cascades)

  /// Truncation
  Bool_t fTruncate = kFALSE;
  Bool_t fStoreHF = kFALSE; // produce HF trees
  /// Compression algotythm and level, see TFile.cxx and RZip.cxx
  UInt_t fCompress = 101; /// This is the default level in Root (zip level 1)
  Bool_t fSkipPileup = kFALSE;       /// Skip pileup events
  Bool_t fSkipTPCPileup = kFALSE;    /// Skip TPC pileup (SetRejectTPCPileupWithITSTPCnCluCorr)
  TString fCentralityMethod = "V0M"; /// Centrality method
  TH1F *fCentralityHist = nullptr; ///! Centrality histogram
  TH1F *fCentralityINT7 = nullptr; ///! Centrality histogram for the INT7 triggers
  TH1I *fHistPileupEvents = nullptr; ///! Counter histogram for pileup events
  TH1I *fHistIsCollision = nullptr; ///! Counter histogram for total number of events vs filled events
  TH1F *fNSigmaElectron = nullptr; ///! QA histogram for on the fly V0s to checke NSigma
  TH2F *fDedxVsP = nullptr; ///! QA histogram for on the fly V0s to checke NSigma
  Double_t fEMCALAmplitudeThreshold = 0.1; ///< EMCAL amplitude threshold (for compression - default: 100 MeV := cluster cell threshold)
  Double_t fFractionL1MonitorEventsEMCAL = 0.001; ///< Fraction of monitoring events (full payload) for EMCAL L1 trigger
  Bool_t fEMCALReducedTriggerPayload = kFALSE; ///< Use reduced trigger payload for EMCAL L1 trigger
  Bool_t fUsePHOSBadMap = kTRUE ; ///< read and apply PHOS trigger bad map

  /// skip EMCal altogether (track propag, emcal cells)
  Bool_t fDisableEMCAL = kFALSE;

  /// Byte counter
  ULong_t fBytes = 0; ///! Number of bytes stored in all trees
  ULong_t fMaxBytes = 100000000; ///| Approximative size limit on the total TF output trees

  /// Meta data
  TMap fMetaData; ///! meta data object for output file

  /// Pointer to the output file
  TFile * fOutputFile = 0x0; ///! Pointer to the output file
  TDirectory * fOutputDir = 0x0; ///! Pointer to the output Root subdirectory

  FwdTrackPars MUONtoFwdTrack(AliESDMuonTrack&); // Converts MUON Tracks from ESD between RUN2 and RUN3 coordinates
  FwdTrackPars MUONtoFwdTrack(AliAODTrack&); // Converts MUON Tracks from AOD between RUN2 and RUN3 coordinates

  ClassDef(AliAnalysisTaskAO2Dconverter, 36);
};

#endif
