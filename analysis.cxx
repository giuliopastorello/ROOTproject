R__LOAD_LIBRARY(particletype_cxx.so)
R__LOAD_LIBRARY(resonancetype_cxx.so)
R__LOAD_LIBRARY(particle_cxx.so)
#include <iostream>
#include "particletype.h"
#include "resonancetype.h"
#include "particle.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1F.h"
#include "TFile.h"

void analysis (){

TFile* file = new TFile("file.root", "UPDATE");

TH1D* h1=(TH1D*)file->Get("h1"); 
TH1D* h2=(TH1D*)file->Get("h2"); 
TH1D* h3=(TH1D*)file->Get("h3"); 
TH1D* h4=(TH1D*)file->Get("h4"); 
TH1D* h5=(TH1D*)file->Get("h5"); 
TH1D* h6=(TH1D*)file->Get("h6"); 
TH1D* h7=(TH1D*)file->Get("h7"); 
TH1D* h8=(TH1D*)file->Get("h8"); 
TH1D* h9=(TH1D*)file->Get("h9"); 
TH1D* h10=(TH1D*)file->Get("h10"); 
TH1D* h11=(TH1D*)file->Get("h11"); 
TH1D* h12=(TH1D*)file->Get("h12"); 
//9.1
std::cout << "Entries: " << '\n';
std::cout << "h1)" << h1->GetEntries() << '\n';
std::cout << "h2)" << h2->GetEntries() << '\n';
std::cout << "h3)" << h3->GetEntries() << '\n';
std::cout << "h4)" << h4->GetEntries() << '\n';
std::cout << "h5)" << h5->GetEntries() << '\n';
std::cout << "h6)" << h6->GetEntries() << '\n';
std::cout << "h7)" << h7->GetEntries() << '\n';
std::cout << "h8)" << h8->GetEntries() << '\n';
std::cout << "h9)" << h9->GetEntries() << '\n';
std::cout << "h10)" << h10->GetEntries() << '\n';
std::cout << "h11)" << h11->GetEntries() << '\n';
std::cout << "h12)" << h12->GetEntries() << '\n';
//9.2
std::cout << "Occurrencies per Particle: " << '\n';
std::cout << "Pi+) " << h1->GetBinContent(1) << " +/- " << h1->GetBinError(1) << '\n';
std::cout << "Pi-) " << h1->GetBinContent(2) << " +/- " << h1->GetBinError(2) << '\n';
std::cout << "K+) " << h1->GetBinContent(3) << " +/- " << h1->GetBinError(3) << '\n';
std::cout << "K-) " << h1->GetBinContent(4) << " +/- " << h1->GetBinError(4) << '\n';
std::cout << "p+) " << h1->GetBinContent(5) << " +/- " << h1->GetBinError(5) << '\n';
std::cout << "p-) " << h1->GetBinContent(6) << " +/- " << h1->GetBinError(6) << '\n';
std::cout << "K*) " << h1->GetBinContent(7) << " +/- " << h1->GetBinError(7) << '\n';

TCanvas *analysis_canvas = new TCanvas("analysis", "cose");
analysis_canvas->Divide (3, 1);

//9.3
TF1 *phi = new TF1("phi", "[0]/TMath::TwoPi()", 0, TMath::TwoPi());
phi->SetParameter(0, h2->GetEntries());
h2->Fit("phi");
TF1 *fitResultPHI = h2->GetFunction("phi");
analysis_canvas->cd(1);
h2->Draw();
std::cout << "    Chisquare = " << fitResultPHI->GetChisquare() << std::endl;
std::cout << "          NDF = " << fitResultPHI->GetNDF() << std::endl;
std::cout << "Chisquare/NDF = " << fitResultPHI->GetChisquare() / fitResultPHI->GetNDF() << std::endl;
std::cout << "      h2 Mean = " << h2->GetMean() << " +/- " << h2->GetMeanError() << '\n';

TF1 *theta = new TF1("theta", "[0]/TMath::Pi()", 0, TMath::Pi());
theta->SetParameter(0, h3->GetEntries());
h3->Fit("theta");
TF1 *fitResultTHETA = h3->GetFunction("theta");
analysis_canvas->cd(2);
h3->Draw();
std::cout << "    Chisquare = " << fitResultTHETA->GetChisquare() << std::endl;
std::cout << "          NDF = " << fitResultTHETA->GetNDF() << std::endl;
std::cout << "Chisquare/NDF = " << fitResultTHETA->GetChisquare() / fitResultTHETA->GetNDF() << std::endl;
std::cout << "      h3 Mean = " << h3->GetMean() << " +/- " << h3->GetMeanError() << '\n';

//9.4
TF1 * p = new TF1("Momentum", "expo", 0, 10);
h4->Fit("Momentum");
TF1 *fitResultP= h4->GetFunction("Momentum");
analysis_canvas->cd(3);
h4->Draw();
std::cout << "    Chisquare = " << fitResultP->GetChisquare() << std::endl;
std::cout << "          NDF = " << fitResultP->GetNDF() << std::endl;
std::cout << "Chisquare/NDF = " << fitResultP->GetChisquare() / fitResultP->GetNDF() << std::endl;
std::cout << "      h4 Mean = " << h4->GetMean() << " +/- " << h4->GetMeanError() << '\n';

analysis_canvas->Print("cose");

//10
//parte 1: " 3 - 4 "
TH1F *h34 = new TH1F("h34", "10 - 11", 1000, 0, 15);
h34->Add(h10, h11, 1, -1);
h34->Draw();
//TF1 *gaus = ("effe", "1/(sqrt(2*TMath::TwoPi()*pow([0],2))*exp(-")
//h34->Fit("effe");
//FitFunc->GetMean();
//gaus->GetMean();
std::cout << "Peak: " << h34->GetMinimum() << " at mass " << h34->GetMinimumBin() << '\n';
//parte 2: " 2 - 1 "
/*TH1F *h21 = new TH1F("h21", "8-9", 1000, 0, 15);
h21->Add(h8, h9, -1, 1);
h21->Draw();
std::cout << "Peak: " << h21->GetMinimum() << " at mass " << h21->GetMinimumBin() << '\n';*/
}