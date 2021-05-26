#include <string>
#include <cstring>
#include <map>
#include <iostream>
#include <math.h>
# define PI 3.14159265358979323846
#include "getDate.cpp"

using namespace std;

// generates a photon spectrum spanning the NuSTAR energy range and with its approximate energy resolution

int Plot_4(const char filename[20])
{
  gROOT -> Reset();

  TFile *inFiles[4]; // adress for input file
  TTree *tree; // adress for root tree stored in file
  TH1D  *spectrum_keV; // adress for histograms
  TH1D  *spectrum_MeV_low;
  TH1D  *spectrum_MeV_high;
  TH1D  *spectrum_GeV;
  TH1D  *spectrum_TeV;
  TH1D  *spectrum_electron;

  // spectrum
  spectrum_keV = new TH1D();
  spectrum_keV -> SetName("SED_keV");
  spectrum_keV -> SetTitle("KeV #gamma Spectrum");
  spectrum_keV -> SetBins(10000.0, 1., 1000.);
  // assign titles to the histogram axes
	spectrum_keV -> GetXaxis() -> SetTitle("Energy [keV]");
	spectrum_keV -> GetYaxis() -> SetTitle("Counts");


  // spectrum
  spectrum_MeV_low = new TH1D();
  spectrum_MeV_low -> SetName("SED_posi");
  spectrum_MeV_low -> SetTitle("#gamma Spectrum");
  spectrum_MeV_low -> SetBins(1000.0, 0.1, 2.0);
  // assign titles to the histogram axes
	spectrum_MeV_low -> GetXaxis() -> SetTitle("Energy [MeV]");
	spectrum_MeV_low -> GetYaxis() -> SetTitle("Counts");

  // spectrum
  spectrum_MeV_high = new TH1D();
  spectrum_MeV_high -> SetName("SED_MeV");
  spectrum_MeV_high -> SetTitle("MeV #gamma Spectrum");
  spectrum_MeV_high -> SetBins(1000.0, 1, 1000.0);
  // assign titles to the histogram axes
	spectrum_MeV_high -> GetXaxis() -> SetTitle("Energy [MeV]");
	spectrum_MeV_high -> GetYaxis() -> SetTitle("Counts");

  // spectrum
  spectrum_GeV = new TH1D();
  spectrum_GeV -> SetName("SED_GeV");
  spectrum_GeV -> SetTitle("GeV #gamma Spectrum");
  spectrum_GeV -> SetBins(1000.0, 1, 1000.0);
  // assign titles to the histogram axes
	spectrum_GeV -> GetXaxis() -> SetTitle("Energy [GeV]");
	spectrum_GeV -> GetYaxis() -> SetTitle("Counts");

  // spectrum
  spectrum_TeV = new TH1D();
  spectrum_TeV -> SetName("SED_TeV");
  spectrum_TeV -> SetTitle("TeV #gamma Spectrum");
  spectrum_TeV -> SetBins(1000.0, 1, 100.0);
  // assign titles to the histogram axes
	spectrum_TeV -> GetXaxis() -> SetTitle("Energy [TeV]");
	spectrum_TeV -> GetYaxis() -> SetTitle("Counts");

  // spectrum
  spectrum_electron = new TH1D();
  spectrum_electron -> SetName("SED_electron");
  spectrum_electron -> SetTitle("e- Spectrum");
  spectrum_electron -> SetBins(15000.0, 250., 15210.);
  // assign titles to the histogram axes
	spectrum_electron -> GetXaxis() -> SetTitle("Energy [GeV]");
	spectrum_electron -> GetYaxis() -> SetTitle("Counts");

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
         if(energy*1000 <= 1000.0){
           spectrum_keV -> Fill(energy*1000.);
         }
         if((0.1 <= energy) && (energy <= 2.0)){
           spectrum_MeV_low -> Fill(energy);
         }
         if((1. <= energy) && (energy <= 1000.)){
           spectrum_MeV_high -> Fill(energy);
         }
         if((1. <= energy/1000.) && (energy/1000 <= 1000.)){
           spectrum_GeV -> Fill(energy/1000);
         }
         if(1000000. <= energy ){
           spectrum_TeV -> Fill(energy/1000000.);
         }
       }
       else if(pID == 11){
         spectrum_electron -> Fill(energy/1000);
       }
     }
     delete inFiles[j];
   }

  // save to a file
  TFile *outFile = new TFile(outputFile,"RECREATE");
  // write histograms to file
  spectrum_keV -> Write("keV_SED");
  spectrum_MeV_low -> Write("Posi_SED");
  spectrum_MeV_high -> Write("MeV_SED");
  spectrum_GeV -> Write("GeV_SED");
  spectrum_TeV -> Write("TeV_SED");
  spectrum_electron -> Write("Electron_Spectrum");
  //delete outFile;
  return 0;
}
