// GC Molecular Cloud Simulation
// GEANT4-10.6.2
// Gabriel Bridges DEC, 2020

// Sensitive Detector Scripts

//includes
// user headers
#include "CloudSD.hh"
// geant headers
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

CloudSD::CloudSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
	collectionName.insert(HCname = name);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudSD::~CloudSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudSD::Initialize(G4HCofThisEvent* HCE)
{
  DetectorCollection = new CloudHitsCollection(SensitiveDetectorName,collectionName[0]);
  auto hcID = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  HCE -> AddHitsCollection( hcID, DetectorCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CloudSD::ProcessHits(G4Step* step,G4TouchableHistory*)
{

  CloudHit* newHit = new CloudHit();

  newHit -> SetParticleID(step -> GetTrack() -> GetDynamicParticle() -> GetDefinition() -> GetPDGEncoding());
  newHit -> SetStepNumber(step -> GetTrack() -> GetCurrentStepNumber());
  newHit -> SetCopyN(step -> GetPostStepPoint() -> GetTouchableHandle() -> GetCopyNumber());
  newHit -> SetEnergy(step -> GetPreStepPoint() -> GetKineticEnergy());
  newHit -> SetPos(step -> GetPostStepPoint() -> GetPosition());
  newHit -> SetTime(step -> GetTrack() -> GetGlobalTime());
  newHit -> SetMomentum(Step -> GetPostStepPoint() -> GetMomentum());
  if (!(aStep -> GetTrack() -> GetCreatorProcess())){
    newHit -> SetCreatorProc("N/A");
  }
  else{
    newHit -> SetCreatorProc(step -> GetTrack() -> GetCreatorProcess() -> GetProcessName());
  }

  DetectorCollection -> insert( newHit );

  if(((newHit -> GetParticleID()) == 11) && ((newHit -> GetEnergy())/GeV >= 245.0)){
    step -> GetTrack() -> SetTrackStatus(fStopAndKill);
  }

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudSD::EndOfEvent(G4HCofThisEvent*)
{
  NbHits = DetectorCollection -> entries();
  for(G4int i = 0; i<NbHits; i++ )
  {
    (*DetectorCollection)[i] -> fPrint();
  }

  if (verboseLevel > 1)
  {
    G4cout << "\n-------->Hits Collection: in this event there are " << NbHits
		<< " hits in the NaI: " << G4endl;
    for (G4int i=0;i<NbHits;i++) (*DetectorCollection)[i] -> Print();
  }
}
