#ifndef CloudMessenger_H
#define CloudMessenger_H 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "global.h"

class CloudConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CloudMessenger: public G4UImessenger
{
  public:
    CloudMessenger(CloudConstruction*);
   ~CloudMessenger();

    void SetNewValue(G4UIcommand* command, G4String newValue);

  private:
    CloudConstruction*          myDetector;
    G4UIcmdWithAString*         OutDirCmd;
    G4UIcmdWithAString*         OutFileCmd;
    G4UIcmdWithoutParameter*    UpdateCmd;

    G4UIdirectory*              cloudDir;
    G4UIcmdWithADoubleAndUnit*  DiameterCmd;
    G4UIcmdWithADoubleAndUnit*  ColDensityCmd;
    G4UIcmdWithADoubleAndUnit*  DensityCmd;
    G4UIcmdWithADoubleAndUnit*  TempCmd;
    G4UIcmdWithADoubleAndUnit*  PressCmd;

    G4UIdirectory*              fieldDir;
    G4UIcmdWithoutParameter*    BOnCmd;
    G4UIcmdWithADoubleAndUnit*  BMagCmd;

    G4UIcmdWithAnInteger*       MinStepsCmd;
    G4UIcmdWithAnInteger*       MaxStepsCmd;
};

#endif
