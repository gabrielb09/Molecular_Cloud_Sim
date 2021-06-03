//
//  Galactic Center Molecular Cloud Simulation
//              Gabriel Bridges
//              December 2020
//              GEANT 4.10.06
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CloudConstruction.hh"
#include "CloudMessenger.hh"
#include "CloudField.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"

#include "G4SDManager.hh"
#include "G4FieldManager.hh"
#include "G4RunManager.hh"
#include "G4StateManager.hh"
#include "G4TransportationManager.hh"
#include "G4EqMagElectricField.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4ProductionCuts.hh"

#include "G4String.hh"
#include "G4UserLimits.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserLimits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// constructor method
CloudConstruction::CloudConstruction()
:SolidWorld(0), LogicalWorld(0), PhysicalWorld(0), MagField(0)
{
  diameter = 6.0*pc;
  column_density = 9e22/cm2;
  temperature = 10*kelvin;
  pressure = 1.0*bar;
  // messenger to handle detector managment
	cloudMessenger = new CloudMessenger(this);
  // define materials
  DefineMaterials();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// destructor method
CloudConstruction::~CloudConstruction()
{
  delete cloudMessenger;
  delete MagField;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudConstruction::DefineMaterials()
{
    // Material definition with NIST Manager
    G4NistManager* nistManager = G4NistManager::Instance();

    Galactic = nistManager->FindOrBuildMaterial("G4_Galactic");
    G4Element* Hyd = nistManager->FindOrBuildElement("H");

    G4int nel, natoms;

    // ISM
    ISM = new G4Material("Interstellar Medium", 2.376e-15*g/cm3, nel = 1, kStateGas, 10*kelvin, 1.0e-8*bar);
    ISM-> AddMaterial(Galactic, 100*perCent);

    // Hydrogen Cloud
    density = column_density/diameter;
    density *= 2.0*Hyd->GetAtomicMassAmu()*1.66053906660e-27*kg;

    ComputePressure();

    MolecularHydrogen = new G4Material("H_Cloud", density, nel = 1, kStateGas, temperature, pressure);
    MolecularHydrogen -> AddElement(Hyd, 2);

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* CloudConstruction::Construct()
{
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(diameter*1.1);
  //------------------------------------------------
  // Copy Numbers
  //------------------------------------------------

  CopyCloud = 1;
  CopyWorld = -1;

  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------

    //------------------------------------------------
    // World
    //------------------------------------------------

    SolidWorld = new G4Box("SolidWorld", diameter*1.1/2.0, diameter*1.1/2.0, diameter*1.1/2.0);
    LogicalWorld = new G4LogicalVolume(SolidWorld, ISM, "World", 0, 0, 0);
    PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicalWorld, "World", 0, false, CopyWorld, true);

    //------------------------------------------------
    // Cloud
    //------------------------------------------------

    SolidCloud = new G4Sphere("SolidCloud", 0, diameter/2.0, 0.0*degree, 360.0*degree, 0.0*degree, 180.0*degree);
    LogicalCloud = new G4LogicalVolume(SolidCloud, MolecularHydrogen, "CloudLog");
    PhysicalCloud = new G4PVPlacement(0, G4ThreeVector(), LogicalCloud, "CloudPhys", LogicalWorld, false, CopyCloud);

    //------------------------------------------------
    // Visualization attributes
    //------------------------------------------------
    WorldVisAtt = new G4VisAttributes(G4Colour(1.00, 1.00, 1.00, 0.0));
    CloudVisAtt = new G4VisAttributes(G4Colour(0.7, 0.7, 0.7, 0.5));

    LogicalWorld -> SetVisAttributes(WorldVisAtt);
    LogicalCloud -> SetVisAttributes(CloudVisAtt);


    G4double maxStep, maxLength, maxTime, minEkin;
    LogicalCloud -> SetUserLimits(new G4UserLimits(maxStep = DBL_MAX,
                                               maxLength = DBL_MAX,
                                               maxTime = DBL_MAX,
                                               minEkin = 1.0*TeV));

	return PhysicalWorld;
}

void CloudConstruction::ConstructSDandField()
{
  // Sensitive Detectors
  DetectorManager = G4SDManager::GetSDMpointer();
  cloudSD = DetectorManager -> FindSensitiveDetector("SensitiveCloud", false);

  if (!cloudSD){
    cloudSD = new CloudSD("SensitiveCloud");
    DetectorManager -> AddNewDetector(cloudSD);
    SetSensitiveDetector(LogicalCloud, cloudSD);
  }

  // Magnetic Field
//  G4TransportationManager::GetTransportationManager()->GetPropagatorInField()->SetLargestAcceptableStep(diameter*10.0);
  // generate field
//  MagField = new CloudField(diameter);
}

void CloudConstruction::SetDiameter(G4double diam){
  diameter = diam;
  if ( G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit ) {
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }
}
void CloudConstruction::SetColumnDensity(G4double colDen){
  column_density = colDen;
  if ( G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit ) {
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }
}
void CloudConstruction::SetTemperature(G4double temp){
  temperature = temp;
  if ( G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit ) {
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }
}

void CloudConstruction::SetPressure(G4double press){
  pressure = press;
  if ( G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit ) {
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }
}

void CloudConstruction::ComputePressure(){
  pressure = density*temperature*idealConst/mole;
  if ( G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit ) {
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }
}

void CloudConstruction::UpdateGeometry()
{
	// Cleanup old geometry
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

	G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
