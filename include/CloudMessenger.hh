#ifndef CloudMessenger_H
#define CloudMessenger_H 1

#include "G4UImessenger.hh"

class CloudConstruction;
class G4UIdirectory;
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

    G4UIdirectory*              cloudDir;
    G4UIcmdWithADoubleAndUnit*  DiameterCmd;
    G4UIcmdWithADoubleAndUnit*  ColDensityCmd;
    G4UIcmdWithADoubleAndUnit*  DensityCmd;
    G4UIcmdWithADoubleAndUnit*  TempCmd;
    G4UIcmdWithADoubleAndUnit*  PressCmd;
    G4UIcmdWithoutParameter*    PressSolve;
};

#endif
