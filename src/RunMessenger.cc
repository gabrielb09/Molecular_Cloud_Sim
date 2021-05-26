// user headers
#include "RunMessenger.hh"
#include "CloudConstruction.hh"
// Geant headers
#include "G4UIcmdWithAString.hh"


RunMessenger::RunMessenger(CloudRunAction* myRunAct)
:myRunAction(myRunAct)
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
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunMessenger::~RunMessenger()
{
	delete OutDirCmd;
  delete OutFileCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
 // output commands
	if(command == OutDirCmd){myRunAction -> SetOutDir(newValue); };
	if(command == OutFileCmd){myRunAction -> SetOutFile(newValue); };
}
