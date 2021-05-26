#include <string>
#include <cstring>
#include <map>
#include <iostream>
#include <math.h>
# define PI 3.14159265358979323846
#include "getDate.cpp"

using namespace std;

// generates a photon spectrum spanning the NuSTAR energy range and with its approximate energy resolution

int Plot_Full(const char filename[20])
{
  gROOT -> Reset();

  TFile *inFiles[4]; // adress for input file
  TTree *tree; // adress for root tree stored in file
  TH1F  *spectrum; // adress for array of histograms (one for each particle species)

  // spectrum
  spectrum = new TH1F();
  spectrum -> SetName("SED");
  spectrum -> SetTitle("#gamma Spectrum");
  spectrum -> SetBins(100.0, 1., 1000.);
  // assign titles to the histogram axes
	spectrum -> GetXaxis() -> SetTitle("Energy [GeV]");
	spectrum -> GetYaxis() -> SetTitle("Counts");

  // file paths for input and output files
  const char* dir = "../output/"; // filepath from ROOT directory to output directory

  char outputFile[100]; // output file memory location
  getDate(); // get Date for file name
	sprintf(outputFile, "%s%s%s", dir, filename, "_spectrum.root"); // output file name

  for(int j = 0; j < 4; j++){
	   char inputFile[100]; // input file memory location
     sprintf(inputFile, "%s%s%i%s", dir, filename, j + 1, ".root"); // input file name and directory

     cout << "********* opening " << inputFile << " *********" << endl; // let me know that we are OPENING this bish

     // open data file
     inFiles[j] = (new TFile(inputFile));
     // extract the tree
     tree = (TTree*) inFiles[j] -> Get("CloudData");
     tree -> Print();
     // set variables to hold data
     double energy;
     int pID;

     // setup the variable adresses for branches
     tree -> SetBranchAddress("particleID", &pID);
     tree -> SetBranchAddress("energy", &energy);

     // loop through tree and extract data
     int length = tree -> GetEntries(); // get total number of entries
     tree -> GetEntry(length - 1); // sets pointers to the last event

     for(int i = 0; i < length; i++){
       tree -> GetEntry(i);
       if(pID == 22){
         spectrum -> Fill(energy/1000);
       }
     }
     delete inFiles[j];
   }

  // save to a file
  TFile *outFile = new TFile(outputFile,"RECREATE");
  // write histograms to file
  spectrum -> Write("SED");
  //delete outFile;
  return 0;
}
