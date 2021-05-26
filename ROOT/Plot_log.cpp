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

int Plot_log(const char filename[20]){

    gROOT -> Reset();
    gStyle -> SetLineScalePS(1);

    // load input files
    TChain in_files("CloudData");
    in_files.Add("../output/*large*");
    
    // set binnings
    int numBins = 3000;
    double minE = 1e3; //eV
    double maxE = 1e13; //eV

    // make SED
    TH1D *sed = new TH1D();
    sed -> SetName("SED");
    sed -> GetXaxis() -> SetTitle("Energy [eV]");
	sed -> GetYaxis() -> SetTitle("E^{2}#frac{dN}{dE} [ergs]");
    sed -> GetXaxis() -> SetLabelSize(sed -> GetXaxis() -> GetLabelSize()*1.25);
    sed -> GetYaxis() -> SetLabelSize(sed -> GetYaxis() -> GetLabelSize()*1.25);
    sed -> SetTitleSize(1.25*(sed -> GetTitleSize("X")), "X");
    sed -> GetYaxis() -> SetTitleOffset(1.05);
    sed -> SetTitleSize(1.25*(sed -> GetTitleSize("Y")), "Y");
    sed -> GetXaxis() -> SetTitleOffset(1.2);

    sed -> SetBins(numBins, minE, maxE);
    BinLogX(sed);
    
    // make counts spectrum
    TH1D *counts = new TH1D();
    counts -> SetName("Spectrum");
    counts -> GetXaxis() -> SetTitle("Energy [eV]");
	counts -> GetYaxis() -> SetTitle("Counts");
    counts -> GetXaxis() -> SetLabelSize(counts -> GetXaxis() -> GetLabelSize()*1.25);
    counts -> GetYaxis() -> SetLabelSize(counts -> GetYaxis() -> GetLabelSize()*1.25);
    counts -> SetTitleSize(1.25*(counts -> GetTitleSize("X")), "X");
    counts -> GetYaxis() -> SetTitleOffset(0.85);
    counts -> SetTitleSize(1.25*(counts -> GetTitleSize("Y")), "Y");
    counts -> GetXaxis() -> SetTitleOffset(1.2);

    counts -> SetBins(numBins, minE, maxE);
    BinLogX(counts);
    
    // make counts density spectrum
    TH1D *density = new TH1D();
    density -> SetName("Spectrum");
    density -> GetXaxis() -> SetTitle("Energy [eV]");
    density -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts eV^{-1}]");
    density -> GetXaxis() -> SetLabelSize(density -> GetXaxis() -> GetLabelSize()*1.25);
    density -> GetYaxis() -> SetLabelSize(density -> GetYaxis() -> GetLabelSize()*1.25);
    density -> SetTitleSize(1.25*(density -> GetTitleSize("X")), "X");
    density -> GetYaxis() -> SetTitleOffset(1.2);
    density -> SetTitleSize(1.25*(density -> GetTitleSize("Y")), "Y");
    density -> GetXaxis() -> SetTitleOffset(1.5);

    density -> SetBins(numBins, minE, maxE);
    BinLogX(density);
    

    int pID;
    double energy;

    in_files.SetBranchAddress("particleID", &pID);
    in_files.SetBranchAddress("energy", &energy);

    for(int i = 0; i < in_files.GetEntries(); i++){
        in_files.GetEntry(i);

        if(pID == 22){
            sed -> Fill(energy*1e6);
            counts -> Fill(energy*1e6);
            density -> Fill(energy*1e6);
        }
    }

    // scale every bin
    
    double bin_height, bin_width, bin_center;

    for(int i = 0; i <= sed -> GetNbinsX(); i++){
        bin_height = sed -> GetBinContent(i);
        bin_width = sed -> GetBinWidth(i);
        bin_center = sed -> GetBinCenter(i);

        sed -> SetBinContent(i, bin_center*bin_center*(bin_height/bin_width)*(1.60218e-12));
        density -> SetBinContent(i, bin_height/bin_width);

    }
    
    char outputFile[100]; // output file memory location
	sprintf(outputFile, "%s%s%s", "../output/", filename, "_spectra.root"); // output file name

    // save to a file
    TFile *outFile = new TFile(outputFile,"RECREATE");
    // write histograms to file
    sed -> Write("SED");
    counts -> Write("counts");
    density -> Write("number_density");

    // plot + make fig
    double s = 2.5;
    TCanvas *c1 = new TCanvas("c1","c1", s*1200, s*900);
    c1 -> SetLogy(); c1 -> SetLogx();
    
    c1 -> SetTopMargin(0.05);
    c1 -> SetBottomMargin(0.15);

    sed -> SetStats(0);
    sed -> SetLineWidth(1);
    sed -> Draw("SAME HIST");

    char canvas_name[400];

    sprintf(canvas_name, "../output/%s.root", "SED_Canvas");
    c1 -> SaveAs(canvas_name);

    sprintf(canvas_name, "../output/%s.pdf", "SED");
    c1 -> SaveAs(canvas_name);

    // plot + make fig
    TCanvas *c2 = new TCanvas("c2","c2", s*1200, s*900);
    c2 -> SetLogy(); c2 -> SetLogx();

    c2 -> SetTopMargin(0.05);
    c2 -> SetBottomMargin(0.15);

    counts -> SetStats(0);
    counts -> SetLineWidth(1);
    counts -> Draw("SAME HIST");

    sprintf(canvas_name, "../output/%s.root", "Counts_Canvas");
    c2 -> SaveAs(canvas_name);

    sprintf(canvas_name, "../output/%s.pdf", "Counts");
    c2 -> SaveAs(canvas_name);
    
    // plot + make fig
    TCanvas *c3 = new TCanvas("c3","c3", s*1200, s*900);
    c3 -> SetLogy(); c3 -> SetLogx();

    c3 -> SetTopMargin(0.05);
    c3 -> SetBottomMargin(0.15);
    c3 -> SetLeftMargin(0.11);
    c3 -> SetRightMargin(0.09);

    density -> SetStats(0);
    density -> SetLineWidth(1);
    density -> Draw("SAME HIST");

    sprintf(canvas_name, "../output/%s.root", "NumDensity_Canvas");
    c3 -> SaveAs(canvas_name);

    sprintf(canvas_name, "../output/%s.pdf", "NumDensity");
    c3 -> SaveAs(canvas_name);

    return 0;
}
