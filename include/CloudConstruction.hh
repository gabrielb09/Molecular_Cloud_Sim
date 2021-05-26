//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: LabDetectorConstruction.hh,v 1.8 2006/06/29 17:47:30 gunter Exp $
// GEANT4 tag $Name: geant4-09-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CloudConstruction_h
#define CloudConstruction_h 1

#include "globals.hh"
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

  void ToggleField(){fieldOn = true;};
  void SetFieldStrength(G4double bmag){B_mag = bmag;};

  void SetMinSteps(G4int minStep){min_steps = minStep;};
  void SetMaxSteps(G4int maxStep){max_steps = maxStep;};

  private:

    G4double diameter, column_density, density, temperature, B_mag;
    G4double idealConst, pressure;
    G4int min_steps, max_steps;
    G4int overlap;
    G4int CopyWorld, CopyCloud;
    G4double minStepLen;
    G4bool fieldOn = false;

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
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
