#include <string>
#include <cstring>
#include <map>
#include <iostream>
#include <math.h>
# define PI 3.14159265358979323846

using namespace std;

// generates a histogram of X-Ray counts by altitude
// also make histogram of X-Ray counts by altitude and energy

int Depth_dist(const char filename[20])
{
  gROOT -> Reset();

  TFile *inFile; // adress for input file
  TTree *tree; // adress for root tree stored in file
  TH1D  *spectrum; // adress for array of histograms (one for each particle species)

  int const num_bin = 1000; // number of bins in a hist
  float min, max, binSize; // maximum and minimun energy values and width of each bin

  spectrum = new TH1D();
  spectrum -> SetName("depth_dist");
  spectrum -> SetTitle("X-Ray Depth Distribution");
  spectrum -> SetBins(num_bin, 0, 0.5);
  // assign titles to the histogram axes
	spectrum -> GetXaxis() -> SetTitle("Depth [pc]");
	spectrum -> GetYaxis() -> SetTitle("Counts");

  // file paths for input and output files
  const char* dir = "../output/"; // filepath from ROOT directory to output directory

  char outputFile[100]; // output file memory location
	sprintf(outputFile, "%s%s%s%s", dir, "plots/", filename ,"_depth.root"); // output file name

	char inputFile[100]; // input file memory location
  sprintf(inputFile, "%s%s%s", dir, filename, ".root"); // input file name and directory

  cout << "********* opening " << inputFile << " *********" << endl; // let me know that we are OPENING this bish

  // open data file
  inFile = (new TFile(inputFile));
  // extract the tree
  tree = (TTree*) inFile -> Get("CloudData");
  tree -> Print();
  // set variables to hold data
  int eventID, trackID, nextVolNum, particleID;
  float px, py, pz, x, y, z;
  double energy, vertex_x, vertex_y, vertex_z;

  // setup the variable adresses for branches
  tree -> SetBranchAddress("eventID", &eventID);
  tree -> SetBranchAddress("trackID", &trackID);
  tree -> SetBranchAddress("particleID", &particleID);
  tree -> SetBranchAddress("postCopyNb", &nextVolNum);
  tree -> SetBranchAddress("energy", &energy);
  tree -> SetBranchAddress("x", &x);
  tree -> SetBranchAddress("y", &y);
  tree -> SetBranchAddress("z", &z);
  tree -> SetBranchAddress("vertex_x", &vertex_x);
  tree -> SetBranchAddress("vertex_y", &vertex_y);
  tree -> SetBranchAddress("vertex_z", &vertex_z);
  // loop through tree and extract data
  int length = tree -> GetEntries(); // get total number of entries
  tree -> GetEntry(length - 1); // sets pointers to the last event
  cout << "last eventID: " << eventID << endl;
  int num_photons = 0;
  float radius;

  for(int i = 0; i < length; i++){
    tree -> GetEntry(i);
    if(eventID < 10 || eventID%10000 == 0) cout << "event " << eventID << " is loaded" << endl;
    cout << particleID << endl;
    if (particleID == 22 && nextVolNum == -1) { // if the particle is leaving the cloud
      num_photons += 1;
      radius = sqrt((vertex_x*vertex_x) + (vertex_y*vertex_y) + (vertex_z*vertex_z));
      cout << radius << endl;
      spectrum -> Fill(1.0 - radius*0.5e-14);
    }
  }

  // save to a file
  TFile *outFile = new TFile(outputFile,"RECREATE");
  // write histograms to file
  spectrum -> Write("Depth_Spect");
  cout << "Number of photons: "<< num_photons << endl;
  delete outFile;
  return 0;
}
