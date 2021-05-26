#include <iostream>
#include <math.h>

using namespace std;

// generates a photon spectrum spanning the NuSTAR energy range and with its approximate energy resolution

int Plot_Synch(const char filename[20])
{
  gROOT -> Reset();

  TFile *inFiles[4]; // adress for input file
  TTree *tree; // adress for root tree stored in file
  TH1D  *spectrum; // adress for array of histograms (one for each particle species)
  TH1D  *eSpectrum;

  // electron spectrum
  eSpectrum = new TH1D();
  eSpectrum -> SetName("SED");
  eSpectrum -> SetTitle("e- Spectrum");
  eSpectrum -> SetBins(1500.0, 245., 15210.); //GeV
  // assign titles to the histogram axes
	eSpectrum -> GetXaxis() -> SetTitle("Energy [GeV]");
	eSpectrum -> GetYaxis() -> SetTitle("Counts");

  // spectrum
  spectrum = new TH1D();
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


  // get electron spectrum
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
       if(pID == 11){
         eSpectrum -> Fill(energy/1000);
       }
     }
   }


   FILE *out_file = fopen("synch_e.txt", "w");

   fprintf(out_file, "Bin Center[MeV], Counts\n");
   for (int i = 1; i <= eSpectrum -> GetNbinsX(); i++) {
     fprintf(out_file, "%g %g\n", eSpectrum -> GetBinCenter(i)*1000.0, (eSpectrum -> GetBinContent(i)));
   }
   fclose(out_file);

   system("python synchrotron.py 100 synch_e.txt 0.001 1000 1000000 synch_rad.txt");


  // save to a file
  TFile *outFile = new TFile(outputFile,"RECREATE");
  // write histograms to file
  eSpectrum -> Write("SED");
  //delete outFile;
  return 0;
}
