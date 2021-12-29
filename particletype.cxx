#include <iostream>
#include "particletype.h"

ParticleType::ParticleType (const char* name_, double mass_, int charge_) : 
fName {name_}, fMass {mass_}, fCharge {charge_} {} 
const char* ParticleType::GetName () const {return fName;}
double ParticleType::GetMass () const {return fMass;}
int ParticleType::GetCharge () const {return fCharge;}
void ParticleType::Print () {
        std::cout << "Particle Type: " << fName << '\n';  
        std::cout << "Mass: " << fMass << '\n';
        std::cout << "Charge: " << fCharge << '\n';
    }
double ParticleType::GetWidth () const {return 0;};