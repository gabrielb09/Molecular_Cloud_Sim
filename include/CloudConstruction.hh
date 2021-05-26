//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CloudConstruction_h
#define CloudConstruction_h 1

#include "CloudSD.hh"
#include "CloudField.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"
#include "G4EqMagElectricField.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"

class G4Box;
class G4Sphere;
class G4Material;
class CloudMessenger;
class CloudField;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CloudConstruction : public G4VUserDetectorConstruction
{
  public:

	CloudConstruction();
  ~CloudConstruction();
	void DefineMaterials();
	void UpdateGeometry();

  public:

	G4VPhysicalVolume* Construct();
  void ConstructSDandField();
	G4double GetWorldFullLength()   {return diameter*1.1;};

  void SetDiameter(G4double);
  void SetColumnDensity(G4double);
  void SetDensity(G4double);
  void SetTemperature(G4double);
  void SetPressure(G4double);
  void ComputePressure();

  private:

    const G4double idealConst = 8.314e1*cm3*bar/kelvin;

    G4double diameter, column_density, density, temperature, B_mag, pressure;
    G4int CopyWorld, CopyCloud;

    G4Box*              SolidWorld;
    G4LogicalVolume*    LogicalWorld;
    G4VPhysicalVolume*  PhysicalWorld;

    G4Sphere*           SolidCloud;
    G4LogicalVolume*    LogicalCloud;
    G4VPhysicalVolume*  PhysicalCloud;

    G4Material* Galactic;
    G4Material* ISM;
    G4Material* MolecularHydrogen;

	  G4VSensitiveDetector*	cloudSD;
	  CloudMessenger* cloudMessenger;        // pointer to the Messenger

    G4VisAttributes* WorldVisAtt;
    G4VisAttributes* CloudVisAtt;

    G4SDManager* DetectorManager;
    CloudField* MagField;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
