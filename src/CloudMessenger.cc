// user headers
#include "CloudMessenger.hh"
#include "CloudConstruction.hh"
// Geant headers
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4SystemOfUnits.hh"

CloudMessenger::CloudMessenger(CloudConstruction* myDet)
:myDetector(myDet)
{
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

  // compute pressure
    PressSolve = new G4UIcmdWithoutParameter("/cloud/pressureUpdate", this);
    PressSolve -> SetGuidance("Update the pressure");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudMessenger::~CloudMessenger()
{
  delete cloudDir;
  delete DiameterCmd;
  delete ColDensityCmd;
  delete TempCmd;
  delete PressCmd;
  delete PressSolve;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
// cloud commands
  if(command == DiameterCmd){
    myDetector -> SetDiameter(DiameterCmd -> GetNewDoubleValue(newValue));
  }
  if(command == ColDensityCmd){
    myDetector -> SetColumnDensity(ColDensityCmd -> GetNewDoubleValue(newValue));
  }
  if(command == TempCmd){
    myDetector -> SetTemperature(TempCmd -> GetNewDoubleValue(newValue));
  }
  if(command == PressCmd){
    myDetector -> SetPressure(PressCmd -> GetNewDoubleValue(newValue));
  }
  if(command == PressSolve){
    myDetector -> ComputePressure();
  }
}
