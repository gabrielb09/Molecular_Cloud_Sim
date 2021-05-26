#include <iostream>
#include <math.h>

void BinLogX(TH1*h)
{
    TAxis *axis = h -> GetXaxis();
    int bins = axis -> GetNbins();

    Axis_t min = log10(axis -> GetXmin());
    Axis_t max = log10(axis -> GetXmax());
    Axis_t width = (max - min) / bins;
    Axis_t *new_bins = new Axis_t[bins + 1];

    for (int i = 0; i <= bins; i++) {
        new_bins[i] = pow(10, min + i*width);
    }
    axis -> Set(bins, new_bins);
    delete new_bins;

}

int electron_spectrum(const char filename[20])
{
    gROOT -> Reset();
    
    // load input files
    TChain in_files("CloudData");
    in_files.Add("../output/*large*");
    
    // set binnings
    int numBins = 9660;
    double minE = 1e3; //eV
    //double maxE = 1e13; //eV
    double maxE = 3.22e13; //eV
    
    // make spectrum
    TH1D *spectrum = new TH1D();
    spectrum -> SetName("Spectrum");
    spectrum -> GetXaxis() -> SetTitle("Energy [eV]");
    spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/eV]");
    spectrum -> GetXaxis() -> SetLabelSize(spectrum -> GetXaxis() -> GetLabelSize()*1.25);
    spectrum -> GetYaxis() -> SetLabelSize(spectrum -> GetYaxis() -> GetLabelSize()*1.25);
    spectrum -> SetTitleSize(1.25*(spectrum -> GetTitleSize("X")), "X");
    spectrum -> GetYaxis() -> SetTitleOffset(0.85);
    spectrum -> SetTitleSize(1.25*(spectrum -> GetTitleSize("Y")), "Y");
    spectrum -> GetXaxis() -> SetTitleOffset(1.15);

    spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(spectrum);
    
    // load data
    int pID;
    double energy;
    double max_E;

    in_files.SetBranchAddress("particleID", &pID);
    in_files.SetBranchAddress("energy", &energy);

    for(int i = 0; i < in_files.GetEntries(); i++){
        in_files.GetEntry(i);

        if(pID == 11){
            spectrum -> Fill(energy*1e6);
            if(energy >= max_E){
                max_E = energy;
            }
        }
    }
    max_E *= 1e6;
    cout << max_E << endl;
    
    // scale every bin
    
    double bin_height, bin_width;

    for(int i = 0; i <= spectrum -> GetNbinsX(); i++){
        bin_height = spectrum -> GetBinContent(i);
        bin_width = spectrum -> GetBinWidth(i);

        spectrum -> SetBinContent(i, bin_height/bin_width);
    }
    
    // output file
    char outputFile[100];
    sprintf(outputFile, "%s%s", "../output/", "electron_spectrum"); // output file name
    
    // save to a file
    TFile *outFile = new TFile(outputFile,"RECREATE");
    // write histograms to file
    spectrum -> Write("e_Spectrum");
    
    // plot + make fig
    double s = 2.5;
    TCanvas *c1 = new TCanvas("c1","c1", s*1200, s*900);
    c1 -> SetLogy(); c1 -> SetLogx();

    spectrum -> SetStats(0);
    spectrum -> SetLineWidth(1);
    spectrum -> Draw("SAME HIST");
    
    FILE *out_file = fopen("synch_e.txt", "w");

    fprintf(out_file, "Bin Center[eV], Counts/eV\n");
    for (int i = 1; i <= spectrum -> GetNbinsX(); i++) {
        fprintf(out_file, "%g %g\n", spectrum -> GetBinCenter(i), (spectrum -> GetBinContent(i)));
    }
    fclose(out_file);

  
    return 0;
}
