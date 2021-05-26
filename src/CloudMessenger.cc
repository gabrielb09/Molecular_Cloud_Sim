// Molecular Cloud Simulation
// GEANT4-10.6.2
// Gabriel Bridges Feb, 2021

// Messenger Manager

//includes
// user headers
#include "CloudMessenger.hh"
#include "CloudConstruction.hh"
#include "global.h"
// Geant headers
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

CloudMessenger::CloudMessenger(CloudConstruction* myDet)
:myDetector(myDet)
{
// output directry
  OutDirCmd = new G4UIcmdWithAString("/OutputDirectory", this);
  OutDirCmd -> SetGuidance("Directory for output files");
  OutDirCmd -> SetParameterName("OutputDirectory", true);
  OutDirCmd -> SetDefaultValue("./tmp");

// output file
  OutFileCmd = new G4UIcmdWithAString("/OutputFile", this );
  OutFileCmd -> SetGuidance("Name of output file");
  OutFileCmd -> SetParameterName("OutputFile", true);
  OutFileCmd -> SetDefaultValue("test");

//--------------------------------//
//       geometry commands        //
//--------------------------------//
  cloudDir = new G4UIdirectory("/cloud/");
  cloudDir -> SetGuidance("Cloud properties commands");

  // cloud size
    DiameterCmd = new G4UIcmdWithADoubleAndUnit("/cloud/diameter", this);
    DiameterCmd -> SetGuidance("Diameter of the cloud");
    DiameterCmd -> SetParameterName("Diameter", false);
    DiameterCmd -> SetRange("Diameter>0.");
    DiameterCmd -> SetUnitCategory("Length");

  // cloud column density
    ColDensityCmd = new G4UIcmdWithADoubleAndUnit("/cloud/columnDensity", this);
    ColDensityCmd -> SetGuidance("Column Density of the cloud");
    ColDensityCmd -> SetParameterName("ColumnDensity", false);
    ColDensityCmd -> SetRange("ColumnDensity>0.");
    ColDensityCmd -> SetUnitCategory("Column Density");

  // cloud density
    DensityCmd = new G4UIcmdWithADoubleAndUnit("/cloud/density", this);
    DensityCmd -> SetGuidance("Density of the cloud");
    DensityCmd -> SetParameterName("Density", false);
    DensityCmd -> SetRange("Density>0.");
    DensityCmd -> SetUnitCategory("Volumic Mass");

  // cloud temperature
    TempCmd = new G4UIcmdWithADoubleAndUnit("/cloud/temperature", this);
    TempCmd -> SetGuidance("Temperature of the cloud");
    TempCmd -> SetParameterName("Temperature", false);
    TempCmd -> SetUnitCategory("Temperature");

  // cloud pressure
    PressCmd = new G4UIcmdWithADoubleAndUnit("/cloud/pressure", this);
    PressCmd -> SetGuidance("Pressure of the cloud");
    PressCmd -> SetParameterName("Pressure", false);
    PressCmd -> SetUnitCategory("Pressure");

//--------------------------------//
//       field commands           //
//--------------------------------//
  fieldDir = new G4UIdirectory("/Bfield");
  fieldDir -> SetGuidance("Magnetic field commands");

  // Simulate with B field
  BOnCmd = new G4UIcmdWithoutParameter("/Bfield/on", this);
  BOnCmd -> SetGuidance("Enable B-Field");

  // B field stregth
  BMagCmd = new G4UIcmdWithADoubleAndUnit("/Bfield/mag", this);
  BMagCmd -> SetGuidance("Magntiude of Magnetic Field");
  BMagCmd -> SetParameterName("Bmag", true);
  BMagCmd -> SetUnitCategory("Magnetic flux density");

//--------------------------------//
//       Simulation commands      //
//--------------------------------//

  // minimum steps
  MinStepsCmd = new G4UIcmdWithAnInteger("/minSteps", this);
  MinStepsCmd -> SetGuidance("The minimum number of steps per track");
  MinStepsCmd -> SetParameterName("Steps", false);
  MinStepsCmd -> SetRange("Steps>0.");

  // maximum steps
  MaxStepsCmd = new G4UIcmdWithAnInteger("/maxSteps", this);
  MaxStepsCmd -> SetGuidance("The maximum number of steps per track");
  MaxStepsCmd -> SetParameterName("Steps", false);
  MaxStepsCmd -> SetRange("Steps>0.");


// update geometry
	UpdateCmd = new G4UIcmdWithoutParameter("/update",this);
  UpdateCmd -> SetGuidance("Update geometry.");
  UpdateCmd -> AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudMessenger::~CloudMessenger()
{
	delete OutDirCmd;
  delete OutFileCmd;
	delete UpdateCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
 extern global_struct global;
 // output commands
	if(command == OutDirCmd) strcpy(global.outdir, newValue );
	if(command == OutFileCmd) strcpy(global.outfile, newValue );

// cloud commands
  if(command == DiameterCmd){
    myDetector -> SetDiameter(DiameterCmd -> GetNewDoubleValue(newValue));
  }
  if(command == ColDensityCmd){
    myDetector -> SetColumnDensity(ColDensityCmd -> GetNewDoubleValue(newValue));
    myDetector -> SetDensity(-1.0);
  }
  if(command == DensityCmd){
    myDetector -> SetDensity(DensityCmd -> GetNewDoubleValue(newValue));
    myDetector -> SetColumnDensity(-1.0);
  }
  if(command == TempCmd){
    myDetector -> SetTemperature(TempCmd -> GetNewDoubleValue(newValue));
  }
  if(command == PressCmd){
    myDetector -> SetPressure(PressCmd -> GetNewDoubleValue(newValue));
  }

// field commands
  if(command == BOnCmd){
    myDetector -> ToggleField();
  }
  if(command == BMagCmd){
    myDetector -> SetFieldStrength(BMagCmd -> GetNewDoubleValue(newValue));
  }

// simulation commands
  if(command == MinStepsCmd){
    myDetector -> SetMinSteps(MinStepsCmd -> GetNewIntValue(newValue));
  }
  if(command == MaxStepsCmd){
    myDetector -> SetMaxSteps(MaxStepsCmd -> GetNewIntValue(newValue));
  }

	if(command == UpdateCmd) myDetector -> UpdateGeometry();
}
