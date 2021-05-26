#ifndef FieldMessenger_H
#define FieldMessenger_H 1

#include "G4UImessenger.hh"

class CloudField;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class FieldMessenger: public G4UImessenger
{
  public:
    FieldMessenger(CloudField*);
   ~FieldMessenger();

    void SetNewValue(G4UIcommand* command, G4String newValue);

  private:
    CloudField*                 myField;

    G4UIdirectory*              fieldDir;
    G4UIcmdWith3VectorAndUnit*  BVecCmd;
    G4UIcmdWithADoubleAndUnit*  BMagCmd;
};

#endif
