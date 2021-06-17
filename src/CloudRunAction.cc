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

  // keV (id = 0)
  analysisManager -> CreateNtuple("keV_Photons", "keV Photon Simulation Data");

  analysisManager -> CreateNtupleDColumn(0, "energy");
  analysisManager -> CreateNtupleDColumn(0, "px");
  analysisManager -> CreateNtupleDColumn(0, "py");
  analysisManager -> CreateNtupleDColumn(0, "pz");

  analysisManager -> CreateNtupleDColumn(0, "t");
  analysisManager -> CreateNtupleDColumn(0, "x");
  analysisManager -> CreateNtupleDColumn(0, "y");
  analysisManager -> CreateNtupleDColumn(0, "z");

  analysisManager -> FinishNtuple(0);

  // GeV (id = 1)
  analysisManager -> CreateNtuple("GeV_Photons", "GeV Photon Simulation Data");

  analysisManager -> CreateNtupleDColumn(1, "energy");
  analysisManager -> CreateNtupleDColumn(1, "px");
  analysisManager -> CreateNtupleDColumn(1, "py");
  analysisManager -> CreateNtupleDColumn(1, "pz");

  analysisManager -> CreateNtupleDColumn(1, "t");

  analysisManager -> FinishNtuple(1);

  // TeV (id = 2)
  analysisManager -> CreateNtuple("TeV_Photons", "TeV Photon Simulation Data");

  analysisManager -> CreateNtupleDColumn(2, "energy");

  analysisManager -> CreateNtupleDColumn(2, "t");

  analysisManager -> FinishNtuple(2);

  // electrons (id = 3)
  analysisManager -> CreateNtuple("Electrons", "Electron Simulation Data");

  analysisManager -> CreateNtupleDColumn(3, "energy");

  analysisManager -> CreateNtupleDColumn(3, "t");
  analysisManager -> CreateNtupleDColumn(3, "x");
  analysisManager -> CreateNtupleDColumn(3, "y");
  analysisManager -> CreateNtupleDColumn(3, "z");

  analysisManager -> CreateNtupleSColumn(3, "creatorProcess");

  analysisManager -> FinishNtuple(3);

  // neutrinos (id = 4)
  analysisManager -> CreateNtuple("Neutrinos", "Neutrino Simulation Data");

  analysisManager -> CreateNtupleDColumn(4, "energy");

  analysisManager -> CreateNtupleDColumn(4, "t");
  analysisManager -> CreateNtupleDColumn(4, "px");
  analysisManager -> CreateNtupleDColumn(4, "py");
  analysisManager -> CreateNtupleDColumn(4, "pz");

  analysisManager -> FinishNtuple(4);

  // protons (id = 5)
  analysisManager -> CreateNtuple("Protons", "Proton Simulation Data");

  analysisManager -> CreateNtupleDColumn(5, "energy");

  analysisManager -> CreateNtupleDColumn(5, "t");
  analysisManager -> CreateNtupleDColumn(5, "x");
  analysisManager -> CreateNtupleDColumn(5, "y");
  analysisManager -> CreateNtupleDColumn(5, "z");

  analysisManager -> FinishNtuple(5);

  // other (id = 6)
  analysisManager -> CreateNtuple("Others", "Other Simulation Data");

  analysisManager -> CreateNtupleIColumn(6, "id");
  analysisManager -> CreateNtupleDColumn(6, "energy");

  analysisManager -> FinishNtuple(6);

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
