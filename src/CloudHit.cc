// GC Molecular Cloud Simulation
// GEANT4-10.6.2
// Gabriel Bridges Aug, 2020

// Detector hit handler

// includes
//user header
#include "CloudHit.hh"
// Geant Visualization
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
// Geant units
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "g4root.hh"

G4Allocator<CloudHit> CloudHitAllocator;

// null constructor and destructor
CloudHit::CloudHit() {}
CloudHit::~CloudHit() {}

// new hit
CloudHit::CloudHit(const CloudHit& right):
	G4VHit()
{
	particleID_   	= right.particleID_;
	stepNumber_ 		= right.stepNumber_;
	copyN_					= right.copyN_;
	energy_       	= right.energy_;
	pos_						= right.pos_;
	time_						= right.time_;
	momentum_				= right.momentum_;

}

const CloudHit& CloudHit::operator=(const CloudHit& right)
{
	particleID_   	= right.particleID_;
	stepNumber_   	= right.stepNumber_;
	copyN_					= right.copyN_;
	energy_       	= right.energy_;
	pos_						= right.pos_;
	time_						= right.time_;
	momentum_				= right.momentum_;

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

	auto analysisManager = G4AnalysisManager::Instance();

	if (((copyN_ == -1) && (particleID_ == 22))||((particleID_ == 11) && (energy_/GeV >= 245.0))){
		analysisManager -> FillNtupleIColumn(0, int(particleID_));
		analysisManager -> FillNtupleIColumn(1, int(copyN_));
		analysisManager -> FillNtupleDColumn(2, double(energy_/MeV));
	  analysisManager -> AddNtupleRow();
	}

	switch(particleID_) {
		case 22 : // photon
			if (copyN_ == -1){ // if escaping the cloud
				if (energy_/keV <= 1e3){ // keV range
					analysisManager -> FillNtupleDColumn(0, 0, double(energy_/keV));
					analysisManager -> FillNtupleDColumn(0, 1, double(momentum_.getX()/keV));
					analysisManager -> FillNtupleDColumn(0, 2, double(momentum_.getY()/keV));
					analysisManager -> FillNtupleDColumn(0, 3, double(momentum_.getZ()/keV));

					analysisManager -> FillNtupleDColumn(0, 4, double(time_/s));

					analysisManager -> FillNtupleDColumn(0, 5, double(pos_.getX()/pc));
					analysisManager -> FillNtupleDColumn(0, 6, double(pos_.getY()/pc));
					analysisManager -> FillNtupleDColumn(0, 7, double(pos_.getZ()/pc));

					analysisManager -> AddNtupleRow(0);
				}
				else if (energy_/GeV <= 1e3){ // MeV - GeV range
					analysisManager -> FillNtupleDColumn(1, 0, double(energy_/GeV));
					analysisManager -> FillNtupleDColumn(1, 1, double(momentum_.getX()/GeV));
					analysisManager -> FillNtupleDColumn(1, 2, double(momentum_.getY()/GeV));
					analysisManager -> FillNtupleDColumn(1, 3, double(momentum_.getZ()/GeV));

					analysisManager -> FillNtupleDColumn(1, 4, double(time_/s));

					analysisManager -> AddNtupleRow(1);
				}
				else{ // TeV range
					analysisManager -> FillNtupleDColumn(2, 0, double(energy_/TeV));
					analysisManager -> FillNtupleDColumn(2, 1, double(time_/s));

					analysisManager -> AddNtupleRow(2);
				}
			}
			break;

		case 11 : // electron
			if ((energy_/MeV >= 1.0) && (stepNumber_ <= 1)){
				analysisManager -> FillNtupleDColumn(3, 0, double(energy_/MeV));

				analysisManager -> FillNtupleDColumn(3, 1, double(time_/s));
				analysisManager -> FillNtupleDColumn(3, 2, double(pos_.getX()/pc));
				analysisManager -> FillNtupleDColumn(3, 3, double(pos_.getY()/pc));
				analysisManager -> FillNtupleDColumn(3, 4, double(pos_.getZ()/pc));

				analysisManager -> AddNtupleRow(3);
			}
			break;
		case 12 : // electron neutrino
		case 14 : // muon neutrino
		case 16 : // tau neutrino
			if (copyN_ == -1){
				analysisManager -> FillNtupleDColumn(4, 0, double(energy_/MeV));

				analysisManager -> FillNtupleDColumn(4, 1, double(time_/s));
				analysisManager -> FillNtupleDColumn(4, 2, double(momentum_.getX()/MeV));
				analysisManager -> FillNtupleDColumn(4, 3, double(momentum_.getY()/MeV));
				analysisManager -> FillNtupleDColumn(4, 4, double(momentum_.getZ()/MeV));

				analysisManager -> AddNtupleRow(4);
			}
			break;
		case 2212 : // protons
			if (copyN_ == -1){
				analysisManager -> FillNtupleDColumn(5, 0, double(energy_/MeV));
			}
			break;
		default : // others
			if (copyN_ == -1){
				analysisManager -> FillNtupleIColumn(6, 0, int(particleID_));
				analysisManager -> FillNtupleDColumn(6, 1, double(energy_/MeV));
			}
			break;
	}

}
