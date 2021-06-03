// Jupiter Auroral Simulation
// GEANT4-10.6.2
// Gabriel Bridges Aug, 2020

// Defines the physics lists

#include "CloudPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4HadronicParameters.hh"

#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CloudPhysicsList::CloudPhysicsList():  G4VModularPhysicsList()
{
    G4cout << "<<< Geant4 Physics List simulation engine: QGSP_BERT 3.4"<<G4endl;
    G4cout <<G4endl;

    G4int ver = 1;
    SetVerboseLevel(ver);
    SetDefaultCutValue(1.0*pc);

    // EM Physics
    RegisterPhysics( new G4EmStandardPhysics(ver) );

    // Synchroton Radiation & GN Physics
    RegisterPhysics( new G4EmExtraPhysics(ver) );

    // Decays
    RegisterPhysics( new G4DecayPhysics(ver) );

    // Hadron Elastic scattering
    RegisterPhysics( new G4HadronElasticPhysics(ver) );

    // Hadron Physics
    RegisterPhysics( new G4HadronPhysicsQGSP_BERT(ver));

    // Stopping Physics
    RegisterPhysics( new G4StoppingPhysics(ver) );

    // Ion Physics
    RegisterPhysics( new G4IonPhysics(ver));

    // Neutron tracking cut
    RegisterPhysics( new G4NeutronTrackingCut(ver));

    //G4HadronicParameters::Instance()->SetEnableCRCoalescence( true );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CloudPhysicsList::~CloudPhysicsList()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CloudPhysicsList::SetCuts()
{
    // Use default cut values gamma and e processes
    SetCutsWithDefault();
}
