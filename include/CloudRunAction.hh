#ifndef CloudRunAction_H
#define CloudRunAction_H 1

#include "G4UserRunAction.hh"
#include "G4String.hh"
#include "RunMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class RunMessenger;

class CloudRunAction : public G4UserRunAction
{
  public:
    CloudRunAction();
   ~CloudRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    void SetOutDir(G4String newDir){ outdir = newDir; };
    void SetOutFile(G4String newFile){ outfile = newFile; };

  private:
    G4String outdir;
    G4String outfile;
    RunMessenger* runMessenger;
};

#endif
