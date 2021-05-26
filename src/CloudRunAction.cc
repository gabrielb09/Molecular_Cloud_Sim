#include "CloudRunAction.hh"
#include "CloudAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"
#include "global.h"
#include <fstream>

using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CloudRunAction::CloudRunAction()
: G4UserRunAction()
{

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
  extern global_struct global;
  char fname[100];

  ((G4Run *)(aRun))->SetRunID(global.runnum);
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  sprintf(fname, "%s/%s.root", global.outdir, global.outfile );
  G4cout << "Output file: " << fname << G4endl;

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> OpenFile(fname);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CloudRunAction::EndOfRunAction(const G4Run*)
{
	extern global_struct global;

	auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();

	G4cout << "Run end  " << G4endl;
}
