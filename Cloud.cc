#include "CloudConstruction.hh"
#include "CloudPhysicsList.hh"
#include "CloudPrimaryGeneratorAction.hh"
#include "CloudRunAction.hh"
#include "CloudEventAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

//#include "QGSP.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BIC_HP.hh"
//#include "LHEP_BERT.hh"
#include "Shielding.hh"
#include "G4SystemOfUnits.hh"

//#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
//#endif
#include "global.h"


global_struct global;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  CLHEP::HepRandom::setTheSeed(time(NULL));
  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  CloudConstruction* detector = new CloudConstruction;
  runManager -> SetUserInitialization(detector);

  G4VUserPhysicsList* physics = new CloudPhysicsList();

	runManager -> SetUserInitialization(physics);

  G4VisManager* visManager = new G4VisExecutive();
  visManager -> Initialize();

  // User Action classes
  //
  G4VUserPrimaryGeneratorAction* gen_action = new CloudPrimaryGeneratorAction();
  runManager -> SetUserAction(gen_action);
  //
  G4UserRunAction* run_action = new CloudRunAction;
  runManager -> SetUserAction(run_action);
  //
  G4UserEventAction* event_action = new CloudEventAction;
  runManager -> SetUserAction(event_action);
  // Initialize G4 kernel
  //
  runManager -> Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager * UI = G4UImanager::GetUIpointer();

  UI -> ApplyCommand("/control/macroPath ../macro");

  if(argc==1)  // Define (G)UI terminal for interactive mode
  {
    // G4UIterminal is a (dumb) terminal
    //
    G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);
#else
      session = new G4UIterminal();
#endif
    UI -> ApplyCommand("/control/execute");
    session -> SessionStart();
    delete session;
  }
  else   // Batch mode
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI -> ApplyCommand(command+fileName);
  }

  delete visManager;
  delete runManager;

  return 0;
}
