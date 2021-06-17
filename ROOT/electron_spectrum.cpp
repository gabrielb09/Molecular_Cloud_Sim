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

int electron_spectrum()
{
    gROOT -> Reset();

    // load input files
    TChain in_files("Electrons");
    in_files.Add("../output/TeV_E_Search*");

    // set binnings
    int numBins = 75;
    double minE = 0.001; //TeV
    double maxE = 51.0; //TeV

    // make spectrum
    TH1D *spectrum = new TH1D();
    spectrum -> SetName("Spectrum");
    spectrum -> SetTitle("Spectrum");
    spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(spectrum);

    TH1D *hIon_spectrum = new TH1D();
    hIon_spectrum -> SetName("hIon_Spectrum");
    hIon_spectrum -> SetTitle("hIoni");
    hIon_spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    hIon_spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    hIon_spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(hIon_spectrum);

    TH1D *eIon_spectrum = new TH1D();
    eIon_spectrum -> SetName("eIon_Spectrum");
    eIon_spectrum -> SetTitle("eIoni");
    eIon_spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    eIon_spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    eIon_spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(eIon_spectrum);

    TH1D *decay_spectrum = new TH1D();
    decay_spectrum -> SetName("decay_Spectrum");
    decay_spectrum -> SetTitle("Decay");
    decay_spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    decay_spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    decay_spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(decay_spectrum);

    TH1D *conv_spectrum = new TH1D();
    conv_spectrum -> SetName("conv_Spectrum");
    conv_spectrum -> SetTitle("Conv");
    conv_spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    conv_spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    conv_spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(conv_spectrum);

    TH1D *hPairProd_spectrum = new TH1D();
    hPairProd_spectrum -> SetName("hPairProd_Spectrum");
    hPairProd_spectrum -> SetTitle("hPairProd");
    hPairProd_spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    hPairProd_spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    hPairProd_spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(hPairProd_spectrum);

    TH1D *compt_spectrum = new TH1D();
    compt_spectrum -> SetName("compt_Spectrum");
    compt_spectrum -> SetTitle("compt");
    compt_spectrum -> GetXaxis() -> SetTitle("Energy [TeV]");
    compt_spectrum -> GetYaxis() -> SetTitle("#frac{dN}{dE} [counts/TeV]");
    compt_spectrum -> SetBins(numBins, minE, maxE);
    BinLogX(compt_spectrum);

    // load data
    double energy;
    Char_t creatorProcess[20];

    in_files.SetBranchAddress("creatorProcess", &creatorProcess);
    in_files.SetBranchAddress("energy", &energy);

    double max_E, min_E;
    int num_E;

    for(int i = 0; i < in_files.GetEntries(); i++){
        in_files.GetEntry(i);
        if (energy*1e-6 > max_E){
          max_E = energy*1e-6;
        }
        if (energy*1e-6 < min_E){
          min_E = energy*1e-6;
        }
        if (energy*1e-6 >= 0.25){
          num_E += 1;
        }
        spectrum -> Fill(energy*1e-6);
          if (strncmp(creatorProcess, "hIoni", 20) == 0){
            hIon_spectrum -> Fill(energy*1e-6);
          }
          else if (strncmp(creatorProcess, "eIoni", 20) == 0){
            eIon_spectrum -> Fill(energy*1e-6);
          }
          else if (strncmp(creatorProcess, "Decay", 20) == 0){
            decay_spectrum -> Fill(energy*1e-6);
          }
          else if (strncmp(creatorProcess, "conv", 20) == 0){
            conv_spectrum -> Fill(energy*1e-6);
          }
          else if (strncmp(creatorProcess, "hPairProd", 20) == 0){
            hPairProd_spectrum -> Fill(energy*1e-6);
          }
          else if (strncmp(creatorProcess, "compt", 20) == 0){
            compt_spectrum -> Fill(energy*1e-6);
          }
          else{
            cout << creatorProcess << endl;
          }
    }

    cout << "Maximum electron Energy: " << max_E << " TeV" << endl;
    cout << "Minimum electron Energy: " << min_E << " TeV" << endl;
    cout << "Total num of > 250 GeV e-: " << num_E << endl;

    // scale every bin

    double bin_height, bin_width;
    for(int i = 0; i <= spectrum -> GetNbinsX(); i++){

        bin_height = spectrum -> GetBinContent(i);
        bin_width = spectrum -> GetBinWidth(i);
        spectrum -> SetBinContent(i, bin_height/bin_width);

        bin_height = hIon_spectrum -> GetBinContent(i);
        bin_width = hIon_spectrum -> GetBinWidth(i);
        hIon_spectrum -> SetBinContent(i, bin_height/bin_width);

        bin_height = eIon_spectrum -> GetBinContent(i);
        bin_width = eIon_spectrum -> GetBinWidth(i);
        eIon_spectrum -> SetBinContent(i, bin_height/bin_width);

        bin_height = decay_spectrum -> GetBinContent(i);
        bin_width = decay_spectrum -> GetBinWidth(i);
        decay_spectrum -> SetBinContent(i, bin_height/bin_width);

        bin_height = conv_spectrum -> GetBinContent(i);
        bin_width = conv_spectrum -> GetBinWidth(i);
        conv_spectrum -> SetBinContent(i, bin_height/bin_width);

        bin_height = hPairProd_spectrum -> GetBinContent(i);
        bin_width = hPairProd_spectrum -> GetBinWidth(i);
        hPairProd_spectrum -> SetBinContent(i, bin_height/bin_width);

        bin_height = compt_spectrum -> GetBinContent(i);
        bin_width = compt_spectrum -> GetBinWidth(i);
        compt_spectrum -> SetBinContent(i, bin_height/bin_width);
    }

    TCanvas *c1 = new TCanvas("c1", "c1", 2400, 1800);
    c1 -> SetLogx(); c1 -> SetLogy();

    spectrum -> SetStats(0);
    spectrum -> SetLineWidth(4);
    spectrum -> SetLineColor(1);
    spectrum -> SetLineStyle(1);
    spectrum -> Draw("SAME HIST");


    hIon_spectrum -> SetStats(0);
    hIon_spectrum -> SetLineWidth(2);
    hIon_spectrum -> SetLineColor(2);
    hIon_spectrum -> SetLineStyle(2);
    hIon_spectrum -> Draw("SAME HIST");


    eIon_spectrum -> SetStats(0);
    eIon_spectrum -> SetLineWidth(2);
    eIon_spectrum -> SetLineColor(3);
    eIon_spectrum -> SetLineStyle(2);
    eIon_spectrum -> Draw("SAME HIST");


    decay_spectrum -> SetStats(0);
    decay_spectrum -> SetLineWidth(2);
    decay_spectrum -> SetLineColor(4);
    decay_spectrum -> SetLineStyle(2);
    decay_spectrum -> Draw("SAME HIST");


    conv_spectrum -> SetStats(0);
    conv_spectrum -> SetLineWidth(2);
    conv_spectrum -> SetLineColor(8);
    conv_spectrum -> SetLineStyle(2);
    conv_spectrum -> Draw("SAME HIST");


    hPairProd_spectrum -> SetStats(0);
    hPairProd_spectrum -> SetLineWidth(2);
    hPairProd_spectrum -> SetLineColor(6);
    hPairProd_spectrum -> SetLineStyle(2);
    hPairProd_spectrum -> Draw("SAME HIST");


    compt_spectrum -> SetStats(0);
    compt_spectrum -> SetLineWidth(2);
    compt_spectrum -> SetLineColor(7);
    compt_spectrum -> SetLineStyle(2);
    compt_spectrum -> Draw("SAME HIST");

    TLegend* legend = new TLegend(0.2, 0.2);
    legend -> AddEntry(spectrum, "Total Spectrum", "l");
    legend -> AddEntry(hIon_spectrum, "Hadron Ionization", "l");
    legend -> AddEntry(eIon_spectrum, "Electron Ionization", "l");
    legend -> AddEntry(decay_spectrum, "Decay", "l");
    legend -> AddEntry(conv_spectrum, "#gamma Pair Production", "l");
    legend -> AddEntry(hPairProd_spectrum, "Hadron Pair Production", "l");
    legend -> AddEntry(compt_spectrum, "Compton", "l");
    legend -> Draw();

    TF1 *pwrLaw;
    pwrLaw = new TF1("pwrLaw", "[0]*pow(x/[1], -1*[2])", 1e-3, 10.0);
    pwrLaw -> SetParName(0, "Amplitude");
    pwrLaw -> SetParLimits(0, 1e1, 1e4);
    pwrLaw -> SetParName(1, "E_0");
    pwrLaw -> SetParLimits(1, 1.0, 10.0);
    pwrLaw -> SetParName(2, "#alpha");
    pwrLaw -> SetParLimits(2, 0, 5);

    spectrum -> Fit("pwrLaw", "0", "", 1.0, 10.0);
    pwrLaw -> SetLineColor(kBlue);
    pwrLaw -> DrawF1(1e-3, 10.0, "CSAME");

    TF1 *pwrLawVar;
    pwrLawVar = new TF1("pwrLawVar", "[0]*pow(x/[1], [2] + [3]*(x/[1]) + [4]*(x/[1])*(x/[1])*(x/[1]))", 1e-3, 30.0);
    pwrLawVar -> SetParName(0, "Amplitude");
    pwrLawVar -> SetParLimits(0, 1e1, 1e4);
    pwrLawVar -> SetParName(1, "E_0");
    pwrLawVar -> SetParLimits(1, 1.0, 10.0);
    pwrLawVar -> SetParName(2, "#alpha");
    //pwrLawVar -> SetParLimits(2, -5, 5);
    pwrLawVar -> SetParName(3, "#beta");
    //pwrLawVar -> SetParLimits(3, 0, -5);
    pwrLawVar -> SetParName(3, "#gamma");
    //pwrLawVar -> SetParLimits(3, 0, -5);

    spectrum -> Fit("pwrLawVar", "0", "", 1.0, 30.0);
    pwrLawVar -> SetLineColor(kRed);
    pwrLawVar -> DrawF1(1e-3, 30.0, "CSAME");

    return 0;
}
