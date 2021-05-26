// user headers
#include "FieldMessenger.hh"
#include "CloudField.hh"
// Geant headers
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

FieldMessenger::FieldMessenger(CloudField* myfield)
:myField(myfield)
{
  fieldDir = new G4UIdirectory("/Bfield");
  fieldDir -> SetGuidance("Magnetic field commands");

  // B field stregth
  BMagCmd = new G4UIcmdWithADoubleAndUnit("/Bfield/mag", this);
  BMagCmd -> SetGuidance("Magntiude of Magnetic Field");
  BMagCmd -> SetParameterName("Bmag", true);
  BMagCmd -> SetUnitCategory("Magnetic flux density");

  // B field vector
  BVecCmd = new G4UIcmdWith3VectorAndUnit("/Bfield/vector", this);
  BVecCmd -> SetGuidance("Magnetic Field Vector");
  BVecCmd -> SetParameterName("BVec", true);
  BVecCmd -> SetUnitCategory("Magnetic flux density");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FieldMessenger::~FieldMessenger()
{
	delete fieldDir;
  delete BMagCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FieldMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == BMagCmd){
    myField -> SetFieldValue(G4ThreeVector(0., 0., BMagCmd -> GetNewDoubleValue(newValue)));
  }

  if(command == BVecCmd){
    myField -> SetFieldValue(BVecCmd -> GetNew3VectorValue(newValue));
  }
}
