#ifndef CloudField_h
#define CloudField_h 1

#include "globals.hh"
#include "G4ElectroMagneticField.hh"

class CloudField : public G4ElectroMagneticField
{

public:
  CloudField(G4double);
  virtual ~CloudField();

  G4double B_mag;

  virtual G4bool DoesFieldChangeEnergy() const { return true; };

  virtual void GetFieldValue(const G4double Point[4], G4double* Bfield) const;

};

#endif
