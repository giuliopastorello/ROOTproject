R__LOAD_LIBRARY(particletype_cxx.so)
R__LOAD_LIBRARY(resonancetype_cxx.so)
R__LOAD_LIBRARY(particle_cxx.so)
#include <iostream>
#include "particletype.h"
#include "resonancetype.h"
#include "particle.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"

void analysis (){

TFile* file = new TFile("histograms.root", "UPDATE");

TH1F* h1=(TH1F*)file->Get("h1"); 
TH1F* h2=(TH1F*)file->Get("h2"); 
TH1F* h3=(TH1F*)file->Get("h3"); 
TH1F* h4=(TH1F*)file->Get("h4"); 
TH1F* h5=(TH1F*)file->Get("h5"); 
TH1F* h6=(TH1F*)file->Get("h6"); 
TH1F* h7=(TH1F*)file->Get("h7"); 
TH1F* h8=(TH1F*)file->Get("h8"); 
TH1F* h9=(TH1F*)file->Get("h9"); 
TH1F* h10=(TH1F*)file->Get("h10"); 
TH1F* h11=(TH1F*)file->Get("h11"); 
TH1F* h12=(TH1F*)file->Get("h12"); 
//9.1
std::cout << "Entries: " << '\n';
std::cout << "h1)" << '\t' << h1->GetEntries() << '\n';
std::cout << "h2)" << '\t' << h2->GetEntries() << '\n';
std::cout << "h3)" << '\t' << h3->GetEntries() << '\n';
std::cout << "h4)" << '\t' << h4->GetEntries() << '\n';
std::cout << "h5)" << '\t' << h5->GetEntries() << '\n';
std::cout << "h6)" << '\t' << h6->GetEntries() << '\n';
std::cout << "h7)" << '\t' << h7->GetEntries() << '\n';
std::cout << "h8)" << '\t' << h8->GetEntries() << '\n';
std::cout << "h9)" << '\t' << h9->GetEntries() << '\n';
std::cout << "h10)" << '\t' << h10->GetEntries() << '\n';
std::cout << "h11)" << '\t' << h11->GetEntries() << '\n';
std::cout << "h12)" << '\t' << h12->GetEntries() << '\n';
//9.2
std::cout << "Occurrencies per Particle: " << '\n';
std::cout << "pi+) " << h1->GetBinContent(1) << " +/- " << h1->GetBinError(1) << '\n';
std::cout << "pi-) " << h1->GetBinContent(2) << " +/- " << h1->GetBinError(2) << '\n';
std::cout << "K+) " << h1->GetBinContent(3) << " +/- " << h1->GetBinError(3) << '\n';
std::cout << "K-) " << h1->GetBinContent(4) << " +/- " << h1->GetBinError(4) << '\n';
std::cout << "p+) " << h1->GetBinContent(5) << " +/- " << h1->GetBinError(5) << '\n';
std::cout << "p-) " << h1->GetBinContent(6) << " +/- " << h1->GetBinError(6) << '\n';
std::cout << "K*) " << h1->GetBinContent(7) << " +/- " << h1->GetBinError(7) << '\n';
std::cout << '\n';
std::cout << "Percentages: " << '\n';
std::cout << "pi+) " << h1->GetBinContent(1) / h1->GetEntries() * 100 << '\n';
std::cout << "pi-) " << h1->GetBinContent(2) / h1->GetEntries() * 100 << '\n';  
std::cout << "K+) " << h1->GetBinContent(3) / h1->GetEntries() * 100 << '\n';
std::cout << "K-) " << h1->GetBinContent(4) / h1->GetEntries() * 100 << '\n';
std::cout << "p+) " << h1->GetBinContent(5) / h1->GetEntries() * 100 << '\n';
std::cout << "p-) " << h1->GetBinContent(6) / h1->GetEntries() * 100 << '\n';
std::cout << "K*) " << h1->GetBinContent(7) / h1->GetEntries() * 100 << '\n';
//9.3, 9.4
TCanvas *firstCanvas = new TCanvas("fit", "Fit Hisograms");
firstCanvas->Divide (2, 2);

firstCanvas->cd(1);
h1->Draw();

firstCanvas->cd(2);
h2->Fit("pol0", "Q");
h2->Draw("E, SAME");

firstCanvas->cd(3);
h3->Fit("pol0", "Q");
h3->Draw("E, SAME");

firstCanvas->cd(4);
h4->Fit("expo", "Q");
h4->Draw("E, SAME");
//10
TCanvas *secondCanvas = new TCanvas("invariant mas", "Fit InvMass Hisograms");
secondCanvas->Divide (1, 3);

secondCanvas->cd(1);
h12->Draw();

secondCanvas->cd(2);
TH1F *h21(h8);
h21->SetTitle("InvMass: Opposite-Same Charges, All Particles");
h21->Add(h8, h9, 1, -1);
h21->Fit("gaus", "Q");
h21->Draw();

secondCanvas->cd(3);
TH1F *h43(h10);
h43->SetTitle("InvMass: Opposite-Same Charges, pi & k");
h43->Add(h10, h11, 1, -1);
h43->Fit("gaus", "Q");
h43->Draw();
}

















































