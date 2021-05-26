#ifndef CloudEventAction_H
#define CloudEventAction_H 1

#include "G4UserEventAction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CloudEventAction : public G4UserEventAction
{
  public:
    CloudEventAction();
   ~CloudEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
};

#endif
