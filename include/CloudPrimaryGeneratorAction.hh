#ifndef CloudPrimaryGeneratorAction_H
#define CloudPrimaryGeneratorAction_H 1

#include "G4VUserPrimaryGeneratorAction.hh"

class ConstructCloud;
class G4GeneralParticleSource;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CloudPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    CloudPrimaryGeneratorAction();
   ~CloudPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

  private:
		G4GeneralParticleSource* GeneralParticleSource;

};

#endif
