#ifndef RunMessenger_H
#define RunMessenger_H 1

#include "G4UImessenger.hh"

class CloudConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunMessenger: public G4UImessenger
{
  public:
    RunMessenger(CloudConstruction*);
   ~RunMessenger();

    void SetNewValue(G4UIcommand* command, G4String newValue);

  private:
    CloudRunAction*       myRunAction;
    G4UIcmdWithAString*   OutDirCmd;
    G4UIcmdWithAString*   OutFileCmd;
};

#endif
