#ifndef __DEF__GLOBAL__
#define __DEF__GLOBAL__

#include <fstream>

using namespace std;

#include "G4Types.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
class G4LogicalVolume;
class G4VPhysicalVolume;

struct global_struct{

	vector<float> inputX,inputY,inputZ,inputPx,inputPy,inputPz,inputE;
	int nLine;
	int runnum;
	int ID1, ID2, ID3;
	int eventID, trackID, parentID, particleID, preCopyNb, postCopyNb;
	double time, energy, edep, px, py, pz, x, y,z;
	G4String creatorProcess;
	int CheckOverlap;
	char outfile[100];
	char outdir[100];
  G4int seed;
};

#endif
