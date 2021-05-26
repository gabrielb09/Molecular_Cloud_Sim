#include "CloudRunAction.hh"
#include "RunMessenger.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "g4root.hh"

using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudRunAction::CloudRunAction()
: G4UserRunAction()
{
  runMessenger = new RunMessenger(this);

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> SetVerboseLevel(1);
  analysisManager -> SetNtupleMerging(true);

  analysisManager -> CreateNtuple("CloudData", "Cloud Simulation Data");
  analysisManager -> CreateNtupleIColumn("particleID");
  analysisManager -> CreateNtupleIColumn("postCopyNb");
  analysisManager -> CreateNtupleDColumn("energy");

  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudRunAction::~CloudRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudRunAction::BeginOfRunAction(const G4Run* aRun)
{

  G4cout << "### Run start." << G4endl;

  char fname[100];
  sprintf(fname, "%s/%s.root", outdir.c_str(), outfile.c_str());

  G4cout << "Output file: " << fname << G4endl;

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> OpenFile(fname);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudRunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> Write();
  analysisManager -> CloseFile();

	G4cout << "Run end  " << G4endl;
}
