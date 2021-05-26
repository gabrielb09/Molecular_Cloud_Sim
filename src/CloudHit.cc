// GC Molecular Cloud Simulation
// GEANT4-10.6.2
// Gabriel Bridges Aug, 2020

// Detector hit handler

// includes
//user header
#include "CloudHit.hh"
#include "global.h"
#include "CloudAnalysis.hh"
// Geant Visualization
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
// Geant units
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

G4Allocator<CloudHit> CloudHitAllocator;

// null constructor and destructor
CloudHit::CloudHit() {}
CloudHit::~CloudHit() {}

// new hit
CloudHit::CloudHit(const CloudHit& right):
	G4VHit()
{
	particleID_   		= right.particleID_;
	copyN_					=right.copyN_;
	energy_       		= right.energy_;
	pos_							= right.pos_;

}

const CloudHit& CloudHit::operator=(const CloudHit& right)
{
	particleID_   		= right.particleID_;
	copyN_					=right.copyN_;
	energy_       		= right.energy_;
	pos_							= right.pos_;

  return *this;
}

G4int CloudHit::operator==(const CloudHit& right) const
{
  return (this == &right) ? 1 : 0;
}

void CloudHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos_);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void CloudHit::Print()
{
  G4cout << "  particleID_: " << particleID_ << "  time_: "
         << "  edep: " << energy_ / keV << G4endl;
}

void CloudHit::fPrint()
{
  extern global_struct global;

	auto analysisManager = G4AnalysisManager::Instance();

	if (((copyN_ == -1) && (particleID_ == 22))||((particleID_ == 11) && (energy_/GeV >= 245.0))){
		analysisManager->FillNtupleIColumn(0, int(particleID_));
		analysisManager->FillNtupleIColumn(1, int(copyN_));
		analysisManager->FillNtupleDColumn(2, double(energy_/MeV));
	  analysisManager->AddNtupleRow();
	}
}
