

#include "CloudPrimaryGeneratorAction.hh"
#include "CloudConstruction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "G4SingleParticleSource.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"
#include <math.h>
#include "global.h"
#include "G4SystemOfUnits.hh"
//#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudPrimaryGeneratorAction::CloudPrimaryGeneratorAction()
:G4VUserPrimaryGeneratorAction()
{
    GeneralParticleSource = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudPrimaryGeneratorAction::~CloudPrimaryGeneratorAction()
{
	delete GeneralParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	extern global_struct global;
  GeneralParticleSource->GeneratePrimaryVertex(anEvent);
}
