#ifndef CloudField_h
#define CloudField_h 1

#include "CloudConstruction.hh"
#include "FieldMessenger.hh"

#include "G4UniformMagField.hh"
#include "G4EqMagElectricField.hh"
#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4ThreeVector.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

class CloudField
{

public:
  CloudField(G4double);
  virtual ~CloudField();

  void SetFieldValue(G4ThreeVector fieldVector);

protected:
  G4FieldManager* GetGlobalFieldManager();
  G4MagneticField* fMagneticField;
  G4SDManager* DetectorManager;
  G4FieldManager* FieldManager;
  G4Mag_UsualEqRhs* eqOM;
  G4ChordFinder* chordFinder;
  FieldMessenger* fieldMessenger;
private:
  G4double diameter;

};

#endif
