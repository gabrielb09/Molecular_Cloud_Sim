#ifndef CloudSD_H
#define CloudSD_H 1


#include "G4VSensitiveDetector.hh"
#include "CloudHit.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CloudSD : public G4VSensitiveDetector
{
public:
    CloudSD(G4String);
    ~CloudSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    void EndOfEvent(G4HCofThisEvent*);

private:
    CloudHitsCollection* DetectorCollection;
    G4int NbHits;
};

#endif
