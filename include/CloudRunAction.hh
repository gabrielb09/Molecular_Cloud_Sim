#ifndef CloudRunAction_H
#define CloudRunAction_H 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class CloudRunAction : public G4UserRunAction
{
  public:
    CloudRunAction();
   ~CloudRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};

#endif
