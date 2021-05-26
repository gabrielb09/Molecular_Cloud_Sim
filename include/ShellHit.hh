// Shell Auroral Simulation
// GEANT4-10.6.2
// Gabriel Bridges Aug, 2020

// Hit manager header
#ifndef ShellHit_H
#define ShellHit_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4String.hh"
#include "G4VProcess.hh"

class ShellHit : public G4VHit
{
  public:
    ShellHit();
    ~ShellHit();
    ShellHit(const ShellHit&);
    const ShellHit& operator=(const ShellHit&);
    G4int operator==(const ShellHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw();
    void Print();
		void fPrint();

  public:
  	void SetTrackID  		  (G4int track)      	{ trackID_ = track; };
    void SetParticleID  	(G4int PDGid)      	{ particleID_ = PDGid; };
    void SetCreatorProcess	(G4String proc) 	  { creatorProcess_ = proc; };
    void SetPostCopyNb		(G4int PostCopy)    { postCopyNb_ = PostCopy; };
    void SetEnergy   		  (G4double kinE)     { kEnergy_ = kinE; };
		void SetMomentum 		  (G4ThreeVector xyz) { momentum_ = xyz; };
    void SetPos      		  (G4ThreeVector xyz)	{ pos_ = xyz; };
    void SetVertexPos		  (G4ThreeVector xyz)	{ vertexPos_ = xyz; };

  private:
    G4int        	trackID_;
		G4int         particleID_;
    G4String	  	creatorProcess_;
    G4int         postCopyNb_;
    G4double      kEnergy_;
		G4ThreeVector momentum_;
    G4ThreeVector pos_;
		G4ThreeVector vertexPos_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<ShellHit> ShellHitsCollection;

extern G4Allocator<ShellHit> ShellHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* ShellHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) ShellHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void ShellHit::operator delete(void *aHit)
{
  ShellHitAllocator.FreeSingle((ShellHit*) aHit);
}

#endif
