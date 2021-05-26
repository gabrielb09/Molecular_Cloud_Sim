#include "CloudField.hh"

#include "G4SystemOfUnits.hh"

CloudField::CloudField(G4double B_field)
: G4ElectroMagneticField()
{
  B_mag = B_mag;
}

CloudField::~CloudField()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudField::GetFieldValue(const G4double Point[4], G4double* Bfield) const
{
  Bfield[0] = 0*gauss;
  Bfield[1] = 0*gauss;
  Bfield[2] = B_mag;

  Bfield[3] = 0;
  Bfield[4] = 0;
  Bfield[5] = 0;

  return;
}
