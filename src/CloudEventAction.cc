// Jupiter Auroral Simulation
// GEANT4-10.6.2
// Gabriel Bridges Aug, 2020

// Handles event actions

//includes
// user headers
#include "CloudEventAction.hh"
// geant headers
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"


CloudEventAction::CloudEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudEventAction::~CloudEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudEventAction::BeginOfEventAction(const G4Event* evt)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudEventAction::EndOfEventAction(const G4Event* evt)
{
    G4int event_id = evt -> GetEventID();
    G4cout << ">>> Event " << evt -> GetEventID() << G4endl;
}
