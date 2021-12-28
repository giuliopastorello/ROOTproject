#include <iostream>
#include <cmath>
#include "particletype.h"
#include "resonancetype.h"
#include "particle.h"
#include "TH1F.h"
#include "TFile.h"
#include "TRandom.h" 
#include "TMath.h"
R__LOAD_LIBRARY(particletype_cxx.so)
R__LOAD_LIBRARY(resonancetype_cxx.so)
R__LOAD_LIBRARY(particle_cxx.so)

void generate()
{
    TFile *file = new TFile("histograms.root","RECREATE");

    Particle::AddParticleType("pi+", 0.13957, 1, 0);
    Particle::AddParticleType("pi-", 0.13957, -1, 0);
    Particle::AddParticleType("K+", 0.49367, 1, 0); 
    Particle::AddParticleType("K-", 0.49367, -1, 0);
    Particle::AddParticleType("p+", 0.93827, 1, 0);
    Particle::AddParticleType("p-", 0.93827, -1, 0);
    Particle::AddParticleType("k*", 0.89166, 0, 0.050);

    TH1F *h1 = new TH1F ("h1", "Occurencies", 7, 0, 7); 
    TH1F *h2 = new TH1F ("h2", "Azimutal Angle", 100, 0, TMath::TwoPi());
    TH1F *h3 = new TH1F ("h3", "Polar Angle", 100, 0, TMath::Pi());
    TH1F *h4 = new TH1F ("h4", "Momentum", 1E4, 0, 10);
    TH1F *h5 = new TH1F ("h5", "Transverse Momentum", 1E3, 0, 5);
    TH1F *h6 = new TH1F ("h6", "Energy", 1E3, 0, 6);
    TH1F *h7 = new TH1F ("h7", "Invariant Mass (General)", 1E3, 0, 7); 
    TH1F *h8 = new TH1F ("h8", "Invariant Mass Opposite Charges", 1E3, 0, 7);
    TH1F *h9 = new TH1F ("h9", "Invariant Mass Same Charges", 1E3, 0, 7);
    TH1F *h10 = new TH1F ("h10", "Invariant Mass pi & k Opposite Charges", 1E3, 0, 7);
    TH1F *h11 = new TH1F ("h11", "Invariant Mass pi & k Same Charges", 1E3, 0, 7);
    TH1F *h12 = new TH1F ("h12", "Invariant Mass Decayment Particles",1E3, 0.4, 1.4);

    //to avoid errors by using "==" operator on char type
    const char* pi_plus = "pi+";
    const char* pi_minus = "pi-";
    const char* K_plus = "K+";
    const char* K_minus = "K-";

    Particle particella[120];

    for (int i = 0; i < 1E5; ++i) {
        int k = 0;
        for (int j = 0; j < 100; ++j){
            double uniform = gRandom->Uniform(0,1);
            if (uniform < 0.4) {
                particella[j].SetIndex(0);
            } else if (uniform < 0.8) {
                particella[j].SetIndex(1);
            } else if (uniform < 0.85) {
                particella[j].SetIndex(2);
            } else if (uniform < 0.9) {
                particella[j].SetIndex(3);
            } else if (uniform < 0.945) {
                particella[j].SetIndex(4);
            } else if (uniform < 0.99) {
                particella[j].SetIndex(5);
            } else { 
                particella[j].SetIndex(6);
                double uni = gRandom->Uniform(0,1);
                if (uni < 0.5) {
                    particella[100 + k].SetIndex(pi_plus); //pi+
                    particella[100 + k + 1].SetIndex(K_minus); //K-
                } else {
                    particella[100 + k].SetIndex(pi_minus); //pi-
                    particella[100 + k + 1].SetIndex(K_plus); //K+
                }
                particella[j].Decay2body(particella[100 + k], particella[100 + k + 1]);
                h12 -> Fill(particella[100 + k].InvMass(particella[100 + k + 1]));
                k += 2;
            }
            h1 -> Fill(particella[j].GetIndex()); 
            double phi = gRandom->Uniform(0, TMath::TwoPi());
            h2 -> Fill(phi);
            double theta = gRandom->Uniform (0, TMath::TwoPi());
            h3 -> Fill(theta);
            double p = gRandom->Exp(1);
            h4 -> Fill(p);
            particella[j].SetP(p * cos(phi) * sin(theta), p * sin(phi) * sin(theta), p * cos(theta));
            h5 -> Fill(sqrt(pow(particella[j].GetPx(), 2) + pow(particella[j].GetPy(), 2)));
            h6 -> Fill(particella[j].GetEnergy());
        } 
        for (int h = 0;  h < 100 + k; ++h)
        {
          for (int l =  h + 1; l < 100 + k; ++l){
            h7 -> Fill(particella[h].InvMass(particella[l]));
            if (particella[h].GetCharge() * particella[l].GetCharge() == -1) {
                h8 -> Fill(particella[h].InvMass(particella[l]));
            } else if (particella[h].GetCharge() * particella[l].GetCharge() == 1)
            {
                h9 -> Fill(particella[h].InvMass(particella[l]));
            }
            if ((particella[h].GetName() == pi_plus && particella[l].GetName() == K_minus) || (particella[h].GetName() == pi_minus && particella[l].GetName() == K_plus)) {
                h10 -> Fill(particella[h].InvMass(particella[l]));
            } else if ((particella[h].GetName() == pi_plus && particella[l].GetName() == K_plus) || (particella[h].GetName() == pi_minus && particella[l].GetName() == K_minus)) {
                h11 -> Fill(particella[h].InvMass(particella[l]));
            }
          }
        }
    }
    //OCCURRENCIES HISTOGRAM
    h1->GetXaxis()->SetTitle("Particle Type");
    h1->GetYaxis()->SetTitle("Occurrencies");
    h1->GetXaxis()->ChangeLabel(1, 45, -1, -1, -1, -1, "pi+");
    h1->GetXaxis()->ChangeLabel(2, 45, -1, -1, -1, -1, "pi-");
    h1->GetXaxis()->ChangeLabel(3, 45, -1, -1, -1, -1, "K+");
    h1->GetXaxis()->ChangeLabel(4, 45, -1, -1, -1, -1, "K-");
    h1->GetXaxis()->ChangeLabel(5, 45, -1, -1, -1, -1, "p+");
    h1->GetXaxis()->ChangeLabel(6, 45, -1, -1, -1, -1, "p-");
    h1->GetXaxis()->ChangeLabel(7, 45, -1, -1, -1, -1, "K*");
    h1->Draw("E"); //Con errori sugli ingressi nei bin
    h1->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h1->Write(); //scrivere su file ROOT
    std::cout << "h1) Mean = " << h1->GetMean() <<  " +/- " << h1-> GetRMS() << '\n';    
    //AZIMUTAL ANGLE (PHI)
    h2->GetXaxis()->SetTitle("Angle (rad)");
    h2->GetYaxis()->SetTitle("Occurrencies");
    h2->Draw("E"); //Con errori sugli ingressi nei bin
    h2->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h2 ->Write(); //scrivere su file ROOT
    std::cout << "h2) Mean = " << h2->GetMean() <<  " +/- " << h2-> GetRMS() << '\n';
    //POLAR ANGLE (THETA)
    h3 ->GetXaxis()->SetTitle("Angle (rad)");
    h3 ->GetYaxis()->SetTitle("Occurrencies");
    h3 ->Draw("E"); //Con errori sugli ingressi nei bin
    h3 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h3 ->Write(); //scrivere su file ROOT
    std::cout << "h3) Mean = " << h3->GetMean() <<  " +/- " << h3-> GetRMS() << '\n';
    //MOMENTUM
    h4 ->GetXaxis()->SetTitle("Momentum (GeV)");
    h4 ->GetYaxis()->SetTitle("Occurrencies");
    h4 ->Draw("E"); //Con errori sugli ingressi nei bin
    h4 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h4 ->Write(); //scrivere su file ROOT
    std::cout << "h4) Mean = " << h4->GetMean() <<  " +/- " << h4-> GetRMS() << '\n';
    //TRANSVERSE MOMENTUM
    h5 ->GetXaxis()->SetTitle("Transverse Momentum (GeV)");
    h5 ->GetYaxis()->SetTitle("Occurrencies");
    h5 ->Draw("E"); //Con errori sugli ingressi nei bin
    h5 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h5 ->Write(); //scrivere su file ROOT
    std::cout << "h5) Mean = " << h4->GetMean() <<  " +/- " << h5-> GetRMS() << '\n';
    //TOTAL ENERGY
    h6 ->GetXaxis()->SetTitle("Total Energy (GeV?)");
    h6 ->GetYaxis()->SetTitle("Occurrencies");
    h6 ->Draw("E"); //Con errori sugli ingressi nei bin
    h6 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h6 ->Write(); //scrivere su file ROOT
    std::cout << "h6) Mean = " << h6->GetMean() <<  " +/- " << h6-> GetRMS() << '\n';
    //GENERAL INVARIANT MASS
    h7 ->GetXaxis()->SetTitle("Invariant Mass");
    h7 ->GetYaxis()->SetTitle("Occurrencies");
    h7 ->Draw("E"); //Con errori sugli ingressi nei bin
    h7 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h7 ->Write(); //scrivere su file ROOT
    std::cout << "h7) Mean = " << h7->GetMean() <<  " +/- " << h7-> GetRMS() << '\n';
    //INVARIANT MASS FOR OPPOSITE CHARGES
    h8 ->GetXaxis()->SetTitle("Invariant Mass Opposite Charges");
    h8 ->GetYaxis()->SetTitle("Occurrencies");
    h8 ->Draw("E"); //Con errori sugli ingressi nei bin
    h8 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h8 ->Write(); //scrivere su file ROOT
    std::cout << "h8) Mean = " << h8->GetMean() <<  " +/- " << h8-> GetRMS() << '\n';
    //INVARIANT MASS FOR ALIKE CHARGES
    h9 ->GetXaxis()->SetTitle("Invariant Mass Same Charges");
    h9 ->GetYaxis()->SetTitle("Occurrencies");
    h9 ->Draw("E"); //Con errori sugli ingressi nei bin
    h9 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h9 ->Write(); //scrivere su file ROOT
    std::cout << "h9) Mean = " << h9->GetMean() <<  " +/- " << h9-> GetRMS() << '\n';
    //INVARIANT MASS FOR PI+ & K- || PI- & K+
    h10 ->GetXaxis()->SetTitle("Invariant Mass pi & k Opposite Charges");
    h10 ->GetYaxis()->SetTitle("Occurrencies");
    h10 ->Draw("E"); //Con errori sugli ingressi nei bin
    h10 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h10 ->Write(); //scrivere su file ROOT
    std::cout << "h10) Mean = " << h10->GetMean() <<  " +/- " << h10-> GetRMS() << '\n';
    //INVARIANT MASS FOR PI+ & K+ || PI- & K-
    h11 ->GetXaxis()->SetTitle("Invariant Mass pi & k Same Charges");
    h11 ->GetYaxis()->SetTitle("Occurrencies");
    h11 ->Draw("E"); //Con errori sugli ingressi nei bin
    h11 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h11 ->Write(); //scrivere su file ROOT
    std::cout << "h11) Mean = " << h11->GetMean() <<  " +/- " << h11-> GetRMS() << '\n';
    //INVARIANT MASS FOR DAUGHTER PARTICLE (DECAYMENT)
    h12 ->GetXaxis()->SetTitle("Invariant Mass Decayment Particles");
    h12 ->GetYaxis()->SetTitle("Occurrencies");
    h12 ->Draw("E"); //Con errori sugli ingressi nei bin
    h12 ->Draw("HISTO,SAME"); //sovrapporre anche come linea continua
    h12 ->Write(); //scrivere su file ROOT
    std::cout << "h12) Mean = " << h12->GetMean() <<  " +/- " << h12-> GetRMS() << '\n';
    file -> Close();
}   