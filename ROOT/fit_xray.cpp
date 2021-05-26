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

int fit_xray(const char filename[20]){

    gROOT -> Reset();
    gStyle -> SetLineScalePS(1);

    // load input files
    TChain in_files("CloudData");
    in_files.Add("../output/*large*");

    // set binnings
    int numBins = 1000;
    double minE = 4e3; //eV
    double maxE = 3e5; //eV

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
            density -> Fill(energy*1e6);
        }
    }

    // scale every bin

    double bin_height, bin_width, bin_center;

    for(int i = 0; i <= density -> GetNbinsX(); i++){
        bin_height = density -> GetBinContent(i);
        bin_width = density -> GetBinWidth(i);
        bin_center = density -> GetBinCenter(i);

        density -> SetBinContent(i, bin_height/bin_width);

    }

    // define fitting functions
    TF1 *pwrLaw1;
    pwrLaw1 = new TF1("pwrLaw1", "[0]*pow(x/[1], -1*[2])", 1e4, 3e4);
    pwrLaw1 -> SetParName(0, "Amplitude");
    pwrLaw1 -> SetParLimits(0, 200, 9000);
    pwrLaw1 -> SetParName(1, "E_0");
    pwrLaw1 -> SetParLimits(1, 200, 10000);
    pwrLaw1 -> SetParName(2, "#alpha");
    pwrLaw1 -> SetParLimits(2, 0, 5);

    TF1 *pwrLaw2;
    pwrLaw2 = new TF1("pwrLaw2", "[0]*pow(x/[1], -1*[2])", 3e4, 1e5);
    pwrLaw2 -> SetParName(0, "Amplitude");
    pwrLaw2 -> SetParLimits(0, 200, 9000);
    pwrLaw2 -> SetParName(1, "E_0");
    pwrLaw2 -> SetParLimits(1, 200, 10000);
    pwrLaw2 -> SetParName(2, "#alpha");
    pwrLaw2 -> SetParLimits(2, 0, 5);

    density -> Fit("pwrLaw1", "0", "", 1e4, 3e4);
    density -> Fit("pwrLaw2", "0", "", 3e4, 1e5);

    // plot + make fig
    double s = 2.5;
    TCanvas *c3 = new TCanvas("c3","c3", s*1200, s*900);
    c3 -> SetLogy(); c3 -> SetLogx();

    c3 -> SetTopMargin(0.05);
    c3 -> SetBottomMargin(0.15);
    c3 -> SetLeftMargin(0.11);
    c3 -> SetRightMargin(0.09);

    density -> SetStats(0);
    density -> SetLineWidth(1);
    density -> Draw("SAME HIST");
    pwrLaw1 -> DrawF1(1e4, 3e4, "CSAME");
    pwrLaw1 -> SetLineWidth(3);
    pwrLaw2 -> DrawF1(3e4, 1e5, "CSAME");
    pwrLaw2 -> SetLineWidth(3);

    return 0;
}
