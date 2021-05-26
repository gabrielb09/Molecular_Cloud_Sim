#include "CloudField.hh"
#include "CloudConstruction.hh"

#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4IntegrationDriver.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

CloudField::CloudField(G4double diameter)
: fMagneticField(0)
{
  // initialize a global uniform field with 100 uG in z direction
  fMagneticField = new G4UniformMagField(G4ThreeVector(0.0,0.0,1e-4*gauss));
  // add field to field manager
  FieldManager = GetGlobalFieldManager();
  FieldManager -> SetDetectorField(fMagneticField);
  double minStepLen = diameter/1000.0;
  // helix
  eqOM = new G4Mag_UsualEqRhs(fMagneticField);
  auto pStepper = new G4HelixImplicitEuler(eqOM);
  auto pIntegrationDriver = new G4IntegrationDriver<G4HelixImplicitEuler>(minStepLen, pStepper, 6);
  chordFinder = new G4ChordFinder(pIntegrationDriver);
  FieldManager -> SetChordFinder(chordFinder);
}

CloudField::~CloudField()
{
}

void CloudField::SetFieldValue(G4ThreeVector fieldVector){

  // delete old field
  if(fMagneticField) delete fMagneticField;

  // create new field
  fMagneticField= new G4UniformMagField(fieldVector);

  // Set this as the field of the global Field Manager
  FieldManager = GetGlobalFieldManager();
  FieldManager -> SetDetectorField(fMagneticField);
  double minStepLen = diameter/1000.0;
  // set up helical stepper
  eqOM = new G4Mag_UsualEqRhs(fMagneticField);
  auto pStepper = new G4HelixImplicitEuler(eqOM);
  auto pIntegrationDriver = new G4IntegrationDriver<G4HelixImplicitEuler>(minStepLen, pStepper, 6);
  chordFinder = new G4ChordFinder(pIntegrationDriver);
  FieldManager -> SetChordFinder(chordFinder);
}

G4FieldManager* CloudField::GetGlobalFieldManager()
{
  //  Utility method
  return G4TransportationManager::GetTransportationManager() -> GetFieldManager();
}
