// Jupiter Auroral Simulation
// GEANT4-10.6.2
// Gabriel Bridges Aug, 2020

// Hit manager header
#ifndef CloudHit_H
#define CloudHit_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4String.hh"
#include "G4VProcess.hh"

class CloudHit : public G4VHit
{
  public:
    CloudHit();
    ~CloudHit();
    CloudHit(const CloudHit&);
    const CloudHit& operator=(const CloudHit&);
    G4int operator==(const CloudHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw();
    void Print();
		void fPrint();

  public:
  	void SetParticleID  	(G4int pID)      	  { particleID_ = pID; };
    void SetStepNumber  	(G4int stepN)      	  { stepNumber_ = stepN; };
    void SetCopyN   		  (G4int cpyN)        { copyN_ = cpyN; };
    void SetEnergy      	(G4double e)	      { energy_ = e; };
    void SetPos      	    (G4ThreeVector xyz) { pos_ = xyz; };
    void SetTime      	  (G4double t)        { time_ = t; };
    void SetMomentum      (G4ThreeVector p)   { momentum_ = p; };

    G4int    GetParticleID ()   { return particleID_; };
    G4double GetEnergy     ()	  { return energy_; };

  private:
    G4int        	particleID_;
    G4int         stepNumber_;
    G4int         copyN_;
    G4double      energy_;
    G4ThreeVector pos_;
    G4double      time_;
    G4ThreeVector momentum_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<CloudHit> CloudHitsCollection;

extern G4Allocator<CloudHit> CloudHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* CloudHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) CloudHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void CloudHit::operator delete(void *aHit)
{
  CloudHitAllocator.FreeSingle((CloudHit*) aHit);
}

#endif
